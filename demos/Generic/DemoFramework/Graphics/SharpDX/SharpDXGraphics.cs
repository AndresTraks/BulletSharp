using System;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using SharpDX.Windows;
using Buffer = SharpDX.Direct3D10.Buffer;
using Color = System.Drawing.Color;
using Device = SharpDX.Direct3D10.Device;
using DriverType = SharpDX.Direct3D10.DriverType;
using Matrix = SharpDX.Matrix;
using Vector3 = SharpDX.Vector3;
using Vector4 = SharpDX.Vector4;

namespace DemoFramework.SharpDX
{
    public class SharpDXGraphics : Graphics
    {
        Device _device;
        public Device Device
        {
            get { return _device; }
        }
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

        EffectMatrixVariable inverseProjectionVar;
        EffectMatrixVariable inverseViewVar;
        EffectMatrixVariable lightInverseViewProjectionVar;
        EffectVectorVariable lightPositionVar;
        EffectVectorVariable eyePositionVar;
        EffectScalarVariable tanHalfFOVXVar;
        EffectScalarVariable tanHalfFOVYVar;
        EffectScalarVariable projectionAVar;
        EffectScalarVariable projectionBVar;
        EffectMatrixVariable overlayViewProjectionVar;

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
        RenderTargetView[] renderViews = new RenderTargetView[1];

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
        RasterizerStateDescription _rasterizerStateDesc;

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

        public override bool CullingEnabled
        {
            get
            {
                return base.CullingEnabled;
            }
            set
            {
                if (_device != null)
                {
                    _rasterizerStateDesc.CullMode = value ? CullMode.Back : CullMode.None;
                    _device.Rasterizer.State.Dispose();
                    _device.Rasterizer.State = new RasterizerState(_device, _rasterizerStateDesc);
                }

                base.CullingEnabled = value;
            }
        }

        public SharpDXGraphics(Demo demo)
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
            Device.CreateWithSwapChain(DriverType.Hardware, DeviceCreationFlags.None, desc, out _device, out _swapChain);
            outputMerger = _device.OutputMerger;
            inputAssembler = _device.InputAssembler;

            Factory factory = _swapChain.GetParent<Factory>();
            factory.MakeWindowAssociation(Form.Handle, WindowAssociationFlags.None);
        }

        void CreateBuffers()
        {
            DisposeBuffers();

            // New RenderTargetView from the backbuffer
            using (var bb = Texture2D.FromSwapChain<Texture2D>(_swapChain, 0))
            {
                renderView = new RenderTargetView(_device, bb);
                renderViews[0] = renderView;
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

            inverseProjectionVar = effect2.GetVariableByName("InverseProjection").AsMatrix();
            inverseViewVar = effect2.GetVariableByName("InverseView").AsMatrix();
            lightInverseViewProjectionVar = effect2.GetVariableByName("LightInverseViewProjection").AsMatrix();
            lightPositionVar = effect2.GetVariableByName("LightPosition").AsVector();
            eyePositionVar = effect2.GetVariableByName("EyePosition").AsVector();

            tanHalfFOVXVar = effect2.GetVariableByName("TanHalfFOVX").AsScalar();
            tanHalfFOVYVar = effect2.GetVariableByName("TanHalfFOVY").AsScalar();
            projectionAVar = effect2.GetVariableByName("ProjectionA").AsScalar();
            projectionBVar = effect2.GetVariableByName("ProjectionB").AsScalar();

            overlayViewProjectionVar = effect2.GetVariableByName("OverlayViewProjection").AsMatrix();

            _device.Rasterizer.SetViewports(new Viewport(0, 0, _width, _height));
        }

        static ShaderBytecode LoadShader(string name, ShaderFlags flags)
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            StreamReader reader = new StreamReader(assembly.GetManifestResourceStream("DemoFramework.SharpDX." + name));
            string shaderSource = reader.ReadToEnd();
            return ShaderBytecode.Compile(shaderSource, "fx_4_0", flags, EffectFlags.None);
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
                MessageBox.Show(e.ToString(), "Could not create DirectX 10 device.");
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

            _rasterizerStateDesc = new RasterizerStateDescription()
            {
                CullMode = CullingEnabled ? CullMode.Back : CullMode.None,
                FillMode = FillMode.Solid,
                DepthBias = 0,
                DepthBiasClamp = 0,
                SlopeScaledDepthBias = 0,
                IsDepthClipEnabled = true,
            };
            _device.Rasterizer.State = new RasterizerState(_device, _rasterizerStateDesc);

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
            GraphicsLibraryManager.LibraryStarted();
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

            using (var data = sceneConstantsBuffer.Map(MapMode.WriteDiscard))
            {
                Marshal.StructureToPtr(sceneConstants, data.DataPointer, false);
                sceneConstantsBuffer.Unmap();
            }

            inverseProjectionVar.SetMatrix(Matrix.Invert(sceneConstants.Projection));
            inverseViewVar.SetMatrix(sceneConstants.ViewInverse);
            lightInverseViewProjectionVar.SetMatrix(Matrix.Invert(sceneConstants.LightViewProjection));
            lightPositionVar.Set(new Vector4(light, 1));
            eyePositionVar.Set(new Vector4(MathHelper.Convert(freelook.Eye), 1));

            float tanHalfFOVY = (float)Math.Tan(FieldOfView * 0.5f);
            tanHalfFOVXVar.Set(tanHalfFOVY * AspectRatio);
            tanHalfFOVYVar.Set(tanHalfFOVY);
            float projectionA = FarPlane / (FarPlane - _nearPlane);
            float projectionB = -projectionA * _nearPlane;
            projectionAVar.Set(projectionA);
            projectionBVar.Set(projectionB);

            Matrix overlayMatrix = Matrix.Scaling(info.Width / _width, info.Height / _height, 1.0f);
            overlayMatrix *= Matrix.Translation(-(_width - info.Width) / _width, (_height - info.Height) / _height, 0.0f);
            overlayViewProjectionVar.SetMatrix(overlayMatrix);
        }

        void Render()
        {
            // Clear targets
            _device.ClearDepthStencilView(depthView, DepthStencilClearFlags.Depth, 1.0f, 0);
            //_device.ClearRenderTargetView(renderView, ambient);
            //_device.ClearRenderTargetView(gBufferLightView, ambient);
            _device.ClearRenderTargetView(gBufferNormalView, ambient);
            _device.ClearRenderTargetView(gBufferDiffuseView, ambient);

            _meshFactory.InitInstancedRender(Demo.World.CollisionObjectArray);

            // Light depth map pass
            if (shadowsEnabled)
            {
                _device.ClearDepthStencilView(lightDepthView, DepthStencilClearFlags.Depth, 1.0f, 0);
                outputMerger.SetDepthStencilState(lightDepthStencilState, 0);
                outputMerger.SetRenderTargets(0, new RenderTargetView[0], lightDepthView);
                shadowGenPass.Apply();
                OnRender();
                lightDepthMapVar.SetResource(lightDepthRes);
            }

            // Render to G-buffer
            lightBufferVar.SetResource(null);
            normalBufferVar.SetResource(null);
            diffuseBufferVar.SetResource(null);
            depthMapVar.SetResource(null);
            lightDepthMapVar.SetResource(null);

            outputMerger.SetDepthStencilState(depthStencilState, 0);
            outputMerger.SetRenderTargets(3, gBufferViews, depthView);
            gBufferGenPass.Apply();
            OnRender();

            if (Demo.IsDebugDrawEnabled)
            {
                debugDrawPass.Apply();
                (Demo.World.DebugDrawer as PhysicsDebugDraw).DrawDebugWorld(Demo.World);
            }

            outputMerger.SetDepthStencilState(null, 0);
            info.OnRender(Demo.FramesPerSecond);


            outputMerger.SetRenderTargets(1, renderViews, null);
            inputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleStrip;

            // Render G-buffer
            lightBufferVar.SetResource(lightBufferRes);
            normalBufferVar.SetResource(normalBufferRes);
            diffuseBufferVar.SetResource(diffuseBufferRes);
            depthMapVar.SetResource(depthRes);
            lightDepthMapVar.SetResource(lightDepthRes);
            gBufferRenderPass.Apply();
            _device.Draw(3, 0);

            // Render overlay
            diffuseBufferVar.SetResource(info.OverlayBufferRes);
            gBufferOverlayPass.Apply();
            _device.Draw(4, 0);

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
