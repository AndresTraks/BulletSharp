using System;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DXGI;
using SharpDX.Windows;
using Buffer = SharpDX.Direct3D11.Buffer;
using Color = System.Drawing.Color;
using Device = SharpDX.Direct3D11.Device;
//using DriverType = SharpDX.Direct3D11.DriverType;
using Matrix = SharpDX.Matrix;
using Vector3 = SharpDX.Vector3;
using Vector4 = SharpDX.Vector4;

namespace DemoFramework.SharpDX11
{
    public class SharpDX11Graphics : Graphics
    {
        Device _device;
        public Device Device
        {
            get { return _device; }
        }
        DeviceContext _immediateContext;
        OutputMergerStage outputMerger;
        InputAssemblerStage inputAssembler;

        SwapChain _swapChain;

        Texture2D gBufferLight;
        Texture2D gBufferNormal;
        Texture2D gBufferDiffuse;
        Texture2D depthTexture;
        Texture2D lightDepthTexture;

        EffectShaderResourceVariable lightBufferVar;
        EffectShaderResourceVariable normalBufferVar;
        EffectShaderResourceVariable diffuseBufferVar;
        EffectShaderResourceVariable depthMapVar;
        EffectShaderResourceVariable lightDepthMapVar;

        RenderTargetView renderView;
        DepthStencilView depthView;
        DepthStencilView lightDepthView;
        RenderTargetView gBufferNormalView;
        RenderTargetView gBufferDiffuseView;
        RenderTargetView gBufferLightView;
        RenderTargetView[] gBufferViews;
        DepthStencilState depthStencilState;
        DepthStencilState lightDepthStencilState;
        bool shadowsEnabled = false;

        Effect effect;
        Effect effect2;
        EffectPass shadowGenPass;
        EffectPass gBufferGenPass;
        EffectPass gBufferRenderPass;
        EffectPass gBufferOverlayPass;
        EffectPass debugDrawPass;

        public EffectPass GetEffectPass()
        {
            return gBufferGenPass;
        }

        public EffectPass GetDebugDrawPass()
        {
            return debugDrawPass;
        }

        ShaderResourceView depthRes;
        ShaderResourceView lightDepthRes;
        ShaderResourceView lightBufferRes;
        ShaderResourceView normalBufferRes;
        ShaderResourceView diffuseBufferRes;

        int _width;
        int _height;
        float _nearPlane;

        ShaderSceneConstants sceneConstants;
        Buffer sceneConstantsBuffer;
        BlendState alphaBlendState;

        InfoText info;

        Color4 ambient;

        MeshFactory _meshFactory;

        [StructLayout(LayoutKind.Sequential)]
        struct ShaderSceneConstants
        {
            public Matrix View;
            public Matrix Projection;
            public Matrix ViewInverse;
            public Matrix LightViewProjection;
        }

        public override BulletSharp.IDebugDraw GetPhysicsDebugDrawer()
        {
            return new PhysicsDebugDraw(this);
        }

        public override bool IsFullScreen
        {
            get
            {
                return !_swapChain.Description.IsWindowed;
            }
            set
            {
                _swapChain.SetFullscreenState(value, null);
            }
        }

        public SharpDX11Graphics(Demo demo)
            : base(demo)
        {
            Form = new RenderForm();
        }

        /// <summary>
        /// Disposes of object resources.
        /// </summary>
        /// <param name="disposeManagedResources">If true, managed resources should be
        /// disposed of in addition to unmanaged resources.</param>
        protected override void Dispose(bool disposeManagedResources)
        {
            if (disposeManagedResources)
            {
                if (info != null)
                    info.Dispose();

                DisposeBuffers();
                //apiContext.Dispose();
                Form.Dispose();
            }
        }

        void DisposeBuffers()
        {
            if (renderView != null)
                renderView.Dispose();

            if (gBufferLightView != null)
                gBufferLightView.Dispose();

            if (gBufferNormalView != null)
                gBufferNormalView.Dispose();

            if (gBufferDiffuseView != null)
                gBufferDiffuseView.Dispose();

            if (gBufferLight != null)
                gBufferLight.Dispose();

            if (gBufferNormal != null)
                gBufferNormal.Dispose();

            if (gBufferDiffuse != null)
                gBufferDiffuse.Dispose();

            if (depthTexture != null)
                depthTexture.Dispose();

            if (lightDepthTexture != null)
                lightDepthTexture.Dispose();

            if (lightBufferRes != null)
                lightBufferRes.Dispose();

            if (normalBufferRes != null)
                normalBufferRes.Dispose();

            if (diffuseBufferRes != null)
                diffuseBufferRes.Dispose();

            if (depthRes != null)
                depthRes.Dispose();

            if (lightDepthRes != null)
                lightDepthRes.Dispose();
        }

        protected void OnInitializeDevice()
        {
            Form.ClientSize = new Size(_width, _height);

            // SwapChain description
            var desc = new SwapChainDescription()
            {
                BufferCount = 1,
                ModeDescription = new ModeDescription(_width, _height, new Rational(60, 1), Format.R8G8B8A8_UNorm),
                IsWindowed = true,
                OutputHandle = Form.Handle,
                SampleDescription = new SampleDescription(1, 0),
                SwapEffect = SwapEffect.Discard,
                Usage = Usage.RenderTargetOutput,
            };

            // Create Device and SwapChain
            SharpDX.Direct3D11.Device.CreateWithSwapChain(DriverType.Hardware, DeviceCreationFlags.None, desc, out _device, out _swapChain);
            _immediateContext = _device.ImmediateContext;
            outputMerger = _immediateContext.OutputMerger;
            inputAssembler = _immediateContext.InputAssembler;

            Factory factory = _swapChain.GetParent<Factory>();
            factory.MakeWindowAssociation(Form.Handle, WindowAssociationFlags.None);


            var blendStateDesc = new BlendStateDescription();
            blendStateDesc.RenderTarget[0].IsBlendEnabled = true;
            blendStateDesc.RenderTarget[0].SourceBlend = BlendOption.SourceAlpha;
            blendStateDesc.RenderTarget[0].DestinationBlend = BlendOption.InverseSourceAlpha;
            blendStateDesc.RenderTarget[0].BlendOperation = BlendOperation.Add;
            blendStateDesc.RenderTarget[0].SourceAlphaBlend = BlendOption.One;
            blendStateDesc.RenderTarget[0].DestinationAlphaBlend = BlendOption.Zero;
            blendStateDesc.RenderTarget[0].AlphaBlendOperation = BlendOperation.Add;
            blendStateDesc.RenderTarget[0].RenderTargetWriteMask = ColorWriteMaskFlags.All;
            alphaBlendState = new BlendState(_device, blendStateDesc);
        }

        void CreateBuffers()
        {
            DisposeBuffers();

            // New RenderTargetView from the backbuffer
            using (var bb = Texture2D.FromSwapChain<Texture2D>(_swapChain, 0))
            {
                renderView = new RenderTargetView(_device, bb);
            }

            Texture2DDescription gBufferDesc = new Texture2DDescription()
            {
                ArraySize = 1,
                BindFlags = BindFlags.RenderTarget | BindFlags.ShaderResource,
                CpuAccessFlags = CpuAccessFlags.None,
                Format = Format.R8G8B8A8_UNorm,
                Width = _width,
                Height = _height,
                MipLevels = 1,
                OptionFlags = ResourceOptionFlags.None,
                SampleDescription = new SampleDescription(1, 0),
                Usage = ResourceUsage.Default
            };

            gBufferLight = new Texture2D(_device, gBufferDesc);
            gBufferLightView = new RenderTargetView(_device, gBufferLight);

            gBufferNormal = new Texture2D(_device, gBufferDesc);
            gBufferNormalView = new RenderTargetView(_device, gBufferNormal);

            gBufferDiffuse = new Texture2D(_device, gBufferDesc);
            gBufferDiffuseView = new RenderTargetView(_device, gBufferDiffuse);

            gBufferViews = new RenderTargetView[] { gBufferLightView, gBufferNormalView, gBufferDiffuseView };

            ShaderResourceViewDescription gBufferResourceDesc = new ShaderResourceViewDescription()
            {
                Format = Format.R8G8B8A8_UNorm,
                Dimension = ShaderResourceViewDimension.Texture2D,
                Texture2D = new ShaderResourceViewDescription.Texture2DResource()
                {
                    MipLevels = 1,
                    MostDetailedMip = 0
                }
            };
            lightBufferRes = new ShaderResourceView(_device, gBufferLight, gBufferResourceDesc);
            normalBufferRes = new ShaderResourceView(_device, gBufferNormal, gBufferResourceDesc);
            diffuseBufferRes = new ShaderResourceView(_device, gBufferDiffuse, gBufferResourceDesc);


            Texture2DDescription depthDesc = new Texture2DDescription()
            {
                ArraySize = 1,
                BindFlags = BindFlags.DepthStencil | BindFlags.ShaderResource,
                CpuAccessFlags = CpuAccessFlags.None,
                Format = Format.R32_Typeless,
                Width = _width,
                Height = _height,
                MipLevels = 1,
                OptionFlags = ResourceOptionFlags.None,
                SampleDescription = new SampleDescription(1, 0),
                Usage = ResourceUsage.Default
            };

            DepthStencilViewDescription depthViewDesc = new DepthStencilViewDescription()
            {
                Dimension = DepthStencilViewDimension.Texture2D,
                Format = Format.D32_Float,
            };

            ShaderResourceViewDescription resourceDesc = new ShaderResourceViewDescription()
            {
                Format = Format.R32_Float,
                Dimension = ShaderResourceViewDimension.Texture2D,
                Texture2D = new ShaderResourceViewDescription.Texture2DResource()
                {
                    MipLevels = 1,
                    MostDetailedMip = 0
                }
            };

            depthTexture = new Texture2D(_device, depthDesc);
            depthView = new DepthStencilView(_device, depthTexture, depthViewDesc);
            depthRes = new ShaderResourceView(_device, depthTexture, resourceDesc);

            lightDepthTexture = new Texture2D(_device, depthDesc);
            lightDepthView = new DepthStencilView(_device, lightDepthTexture, depthViewDesc);
            lightDepthRes = new ShaderResourceView(_device, lightDepthTexture, resourceDesc);

            lightBufferVar = effect2.GetVariableByName("lightBuffer").AsShaderResource();
            normalBufferVar = effect2.GetVariableByName("normalBuffer").AsShaderResource();
            diffuseBufferVar = effect2.GetVariableByName("diffuseBuffer").AsShaderResource();
            depthMapVar = effect2.GetVariableByName("depthMap").AsShaderResource();
            lightDepthMapVar = effect2.GetVariableByName("lightDepthMap").AsShaderResource();

            _immediateContext.Rasterizer.SetViewport(new ViewportF(0, 0, _width, _height));
        }

        ShaderBytecode LoadShader(string name, ShaderFlags flags)
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            StreamReader reader = new StreamReader(assembly.GetManifestResourceStream("DemoFramework.SharpDX11." + name));
            string shaderSource = reader.ReadToEnd();
            return ShaderBytecode.Compile(shaderSource, "fx_5_0", flags, EffectFlags.None);
        }

        public override void Initialize()
        {
            Form.SizeChanged += (o, args) =>
            {
                if (_swapChain == null)
                    return;

                renderView.Dispose();
                depthView.Dispose();
                DisposeBuffers();

                if (Form.WindowState == FormWindowState.Minimized)
                    return;

                _width = Form.ClientSize.Width;
                _height = Form.ClientSize.Height;
                _swapChain.ResizeBuffers(_swapChain.Description.BufferCount, 0, 0, Format.Unknown, 0);

                CreateBuffers();
                SetSceneConstants();
            };

            _width = 1024;
            _height = 768;
            _nearPlane = 1.0f;

            ambient = new Color4(Color.Gray.ToArgb());

            try
            {
                OnInitializeDevice();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "Could not create DirectX 11 device.");
                return;
            }


            // shader.fx

            const ShaderFlags shaderFlags = ShaderFlags.None;
            //const ShaderFlags shaderFlags = ShaderFlags.Debug | ShaderFlags.SkipOptimization;
            ShaderBytecode shaderByteCode = LoadShader("shader.fx", shaderFlags);

            effect = new Effect(_device, shaderByteCode);
            EffectTechnique technique = effect.GetTechniqueByIndex(0);
            shadowGenPass = technique.GetPassByIndex(0);
            gBufferGenPass = technique.GetPassByIndex(1);
            debugDrawPass = technique.GetPassByName("debug");

            BufferDescription sceneConstantsDesc = new BufferDescription()
            {
                SizeInBytes = Marshal.SizeOf(typeof(ShaderSceneConstants)),
                Usage = ResourceUsage.Dynamic,
                BindFlags = BindFlags.ConstantBuffer,
                CpuAccessFlags = CpuAccessFlags.Write,
                OptionFlags = ResourceOptionFlags.None
            };

            sceneConstantsBuffer = new Buffer(_device, sceneConstantsDesc);
            EffectConstantBuffer effectConstantBuffer = effect.GetConstantBufferByName("scene");
            effectConstantBuffer.SetConstantBuffer(sceneConstantsBuffer);

            RasterizerStateDescription desc = new RasterizerStateDescription()
            {
                CullMode = CullMode.None,
                FillMode = FillMode.Solid,
                IsFrontCounterClockwise = true,
                DepthBias = 0,
                DepthBiasClamp = 0,
                SlopeScaledDepthBias = 0,
                IsDepthClipEnabled = true,
            };
            _immediateContext.Rasterizer.State = new RasterizerState(_device, desc);

            DepthStencilStateDescription depthDesc = new DepthStencilStateDescription()
            {
                IsDepthEnabled = true,
                IsStencilEnabled = false,
                DepthWriteMask = DepthWriteMask.All,
                DepthComparison = Comparison.Less
            };
            depthStencilState = new DepthStencilState(_device, depthDesc);

            DepthStencilStateDescription lightDepthStateDesc = new DepthStencilStateDescription()
            {
                IsDepthEnabled = true,
                IsStencilEnabled = false,
                DepthWriteMask = DepthWriteMask.All,
                DepthComparison = Comparison.Less
            };
            lightDepthStencilState = new DepthStencilState(_device, lightDepthStateDesc);


            // grender.fx

            shaderByteCode = LoadShader("grender.fx", shaderFlags);

            effect2 = new Effect(_device, shaderByteCode);
            technique = effect2.GetTechniqueByIndex(0);
            gBufferRenderPass = technique.GetPassByIndex(0);
            gBufferOverlayPass = technique.GetPassByIndex(1);

            info = new InfoText(_device);
            _meshFactory = new MeshFactory(this);
            MeshFactory = _meshFactory;

            CreateBuffers();
            LibraryManager.LibraryStarted();
        }

        void SetSceneConstants()
        {
            FreeLook freelook = Demo.Freelook;
            Vector3 up = MathHelper.Convert(freelook.Up);
            sceneConstants.View = Matrix.LookAtLH(MathHelper.Convert(freelook.Eye), MathHelper.Convert(freelook.Target), up);
            sceneConstants.Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, _nearPlane, FarPlane);
            sceneConstants.ViewInverse = Matrix.Invert(sceneConstants.View);

            Vector3 light = new Vector3(20, 30, 10);
            Texture2DDescription depthBuffer = lightDepthTexture.Description;
            Matrix lightView = Matrix.LookAtLH(light, Vector3.Zero, up);
            Matrix lightProjection = Matrix.OrthoLH(depthBuffer.Width / 8.0f, depthBuffer.Height / 8.0f, _nearPlane, FarPlane);
            sceneConstants.LightViewProjection = lightView * lightProjection;

            DataStream data;
            _immediateContext.MapSubresource(sceneConstantsBuffer, MapMode.WriteDiscard, SharpDX.Direct3D11.MapFlags.None, out data);
            Marshal.StructureToPtr(sceneConstants, data.DataPointer, false);
            _immediateContext.UnmapSubresource(sceneConstantsBuffer, 0);
            data.Dispose();

            effect2.GetVariableByName("InverseProjection").AsMatrix().SetMatrix(Matrix.Invert(sceneConstants.Projection));
            effect2.GetVariableByName("InverseView").AsMatrix().SetMatrix(sceneConstants.ViewInverse);
            effect2.GetVariableByName("LightInverseViewProjection").AsMatrix().SetMatrix(Matrix.Invert(sceneConstants.LightViewProjection));
            effect2.GetVariableByName("LightPosition").AsVector().Set(new Vector4(light, 1));
            effect2.GetVariableByName("EyePosition").AsVector().Set(new Vector4(MathHelper.Convert(freelook.Eye), 1));
            effect2.GetVariableByName("EyeZAxis").AsVector().Set(new Vector4(Vector3.Normalize(MathHelper.Convert(freelook.Target - freelook.Eye)), 1));

            float tanHalfFOVY = (float)Math.Tan(FieldOfView * 0.5f);
            effect2.GetVariableByName("TanHalfFOVX").AsScalar().Set(tanHalfFOVY * AspectRatio);
            effect2.GetVariableByName("TanHalfFOVY").AsScalar().Set(tanHalfFOVY);
            float projectionA = FarPlane / (FarPlane - _nearPlane);
            float projectionB = -projectionA * _nearPlane;
            effect2.GetVariableByName("ProjectionA").AsScalar().Set(projectionA);
            effect2.GetVariableByName("ProjectionB").AsScalar().Set(projectionB);

            Matrix overlayMatrix = Matrix.Scaling(info.Width / _width, info.Height / _height, 1.0f);
            overlayMatrix *= Matrix.Translation(-(_width - info.Width) / _width, (_height - info.Height) / _height, 0.0f);
            effect2.GetVariableByName("OverlayViewProjection").AsMatrix().SetMatrix(overlayMatrix);
        }

        void Render()
        {
            // Clear targets
            _immediateContext.ClearDepthStencilView(depthView, DepthStencilClearFlags.Depth, 1.0f, 0);
            _immediateContext.ClearRenderTargetView(renderView, ambient);
            _immediateContext.ClearRenderTargetView(gBufferLightView, ambient);
            _immediateContext.ClearRenderTargetView(gBufferNormalView, ambient);
            _immediateContext.ClearRenderTargetView(gBufferDiffuseView, ambient);

            _meshFactory.InitInstancedRender(Demo.World.CollisionObjectArray);

            // Light depth map pass
            if (shadowsEnabled)
            {
                _immediateContext.ClearDepthStencilView(lightDepthView, DepthStencilClearFlags.Depth, 1.0f, 0);
                outputMerger.SetDepthStencilState(lightDepthStencilState);
                outputMerger.SetRenderTargets(lightDepthView);
                shadowGenPass.Apply(_immediateContext);
                OnRender();
                lightDepthMapVar.SetResource(lightDepthRes);
            }

            // Render to G-buffer
            lightBufferVar.SetResource(null);
            normalBufferVar.SetResource(null);
            diffuseBufferVar.SetResource(null);
            depthMapVar.SetResource(null);
            lightDepthMapVar.SetResource(null);

            outputMerger.SetDepthStencilState(depthStencilState);
            outputMerger.SetTargets(depthView, gBufferViews);
            gBufferGenPass.Apply(_immediateContext);
            OnRender();

            if (Demo.IsDebugDrawEnabled)
            {
                debugDrawPass.Apply(_immediateContext);
                (Demo.World.DebugDrawer as PhysicsDebugDraw).DrawDebugWorld(Demo.World);
            }

            outputMerger.SetDepthStencilState(null);
            info.OnRender(Demo.FramesPerSecond);


            outputMerger.SetTargets(renderView);
            inputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleStrip;

            // Render G-buffer
            lightBufferVar.SetResource(lightBufferRes);
            normalBufferVar.SetResource(normalBufferRes);
            diffuseBufferVar.SetResource(diffuseBufferRes);
            depthMapVar.SetResource(depthRes);
            lightDepthMapVar.SetResource(lightDepthRes);
            gBufferRenderPass.Apply(_immediateContext);
            _immediateContext.Draw(3, 0);


            // Render overlay
            outputMerger.SetBlendState(alphaBlendState);
            diffuseBufferVar.SetResource(info.OverlayBufferRes);
            gBufferOverlayPass.Apply(_immediateContext);
            _immediateContext.Draw(4, 0);

            _swapChain.Present(0, PresentFlags.None);
        }

        public override void UpdateView()
        {
            SetSceneConstants();
        }

        public override void Run()
        {
            RenderLoop.Run(Form, () =>
            {
                Demo.OnHandleInput();
                Demo.OnUpdate();
                if (Form.WindowState != FormWindowState.Minimized)
                    Render();
            });
        }

        protected virtual void OnRender()
        {
            _meshFactory.RenderInstanced();
        }

        public override void SetInfoText(string text)
        {
            info.Text = text;
        }
    }
}
