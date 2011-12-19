using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using SharpDX.Windows;
using Buffer = SharpDX.Direct3D10.Buffer;
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
        Device.OutputMergerStage outputMerger;
        Device.InputAssemblerStage inputAssembler;

        SwapChain _swapChain;

        Texture2D gBufferLight;
        Texture2D gBufferNormal;
        Texture2D gBufferDiffuse;
        Texture2D depthTexture;
        Texture2D lightDepthTexture;

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
        public RenderTargetView[] renderViews = new RenderTargetView[1];

        VertexBufferBinding quadBinding;
        InputLayout quadBufferLayout;

        Effect effect;
        Effect effect2;
        EffectPass shadowGenPass;
        EffectPass gBufferGenPass;
        EffectPass gBufferRenderPass;

        public EffectPass GetShadowGenPass()
        {
            return shadowGenPass;
        }

        ShaderResourceView depthRes;
        ShaderResourceView lightDepthRes;
        ShaderResourceView lightBufferRes;
        ShaderResourceView normalBufferRes;
        ShaderResourceView diffuseBufferRes;

        protected int Width { get; set; }
        protected int Height { get; set; }
        protected int FullScreenWidth { get; set; }
        protected int FullScreenHeight { get; set; }
        protected float NearPlane { get; set; }
        protected float FarPlane { get; set; }

        ShaderSceneConstants sceneConstants = new ShaderSceneConstants();
        Buffer sceneConstantsBuffer;

        InfoText info;

        Color4 ambient;
        protected Color4 Ambient
        {
            get { return ambient; }
            set { ambient = value; }
        }

        MeshFactory meshFactory;
        protected MeshFactory GetMeshFactory()
        {
            return meshFactory;
        }

        [StructLayout(LayoutKind.Sequential)]
        struct ShaderSceneConstants
        {
            public Matrix View;
            public Matrix Projection;
            public Matrix ViewInverse;
            public Matrix LightViewProjection;
            public Vector4 LightPosition;
        }

        public SharpDXGraphics(Demo demo)
            : base(demo)
        {
            Form = new RenderForm();
        }

        /// <summary>
        /// Disposes of object resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Disposes of object resources.
        /// </summary>
        /// <param name="disposeManagedResources">If true, managed resources should be
        /// disposed of in addition to unmanaged resources.</param>
        protected virtual void Dispose(bool disposeManagedResources)
        {
            if (disposeManagedResources)
            {
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
            Form.ClientSize = new System.Drawing.Size(Width, Height);

            // SwapChain description
            var desc = new SwapChainDescription()
            {
                BufferCount = 1,
                ModeDescription = new ModeDescription(Width, Height, new Rational(60, 1), Format.R8G8B8A8_UNorm),
                IsWindowed = true,
                OutputHandle = Form.Handle,
                SampleDescription = new SampleDescription(1, 0),
                SwapEffect = SwapEffect.Discard,
                Usage = Usage.RenderTargetOutput
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
                Height = Height,
                Width = Width,
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
                Height = Height,
                Width = Width,
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

            effect2.GetVariableByName("lightBuffer").AsShaderResource().SetResource(lightBufferRes);
            effect2.GetVariableByName("normalBuffer").AsShaderResource().SetResource(normalBufferRes);
            effect2.GetVariableByName("diffuseBuffer").AsShaderResource().SetResource(diffuseBufferRes);
            effect2.GetVariableByName("depthMap").AsShaderResource().SetResource(depthRes);
            effect2.GetVariableByName("lightDepthMap").AsShaderResource().SetResource(lightDepthRes);

            _device.Rasterizer.SetViewports(new Viewport(0, 0, Width, Height));
        }

        public override void Initialize()
        {
            Form.ResizeEnd += (o, args) =>
            {
                Width = Form.ClientSize.Width;
                Height = Form.ClientSize.Height;

                renderView.Dispose();
                depthView.Dispose();
                _swapChain.ResizeBuffers(_swapChain.Description.BufferCount, Width, Height, _swapChain.Description.ModeDescription.Format, (int)_swapChain.Description.Flags);

                CreateBuffers();

                SetSceneConstants();
            };

            Width = 1024;
            Height = 768;
            FullScreenWidth = Screen.PrimaryScreen.Bounds.Width;
            FullScreenHeight = Screen.PrimaryScreen.Bounds.Height;
            NearPlane = 1.0f;
            FarPlane = 200.0f;

            ambient = (Color4)Color.Gray;

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

            ShaderFlags shaderFlags = ShaderFlags.None;
            //ShaderFlags shaderFlags = ShaderFlags.Debug | ShaderFlags.SkipOptimization;
            ShaderBytecode shaderByteCode = ShaderBytecode.CompileFromFile(Application.StartupPath + "\\shader.fx", "fx_4_0", shaderFlags, EffectFlags.None);

            effect = new Effect(_device, shaderByteCode);
            EffectTechnique technique = effect.GetTechniqueByIndex(0);
            shadowGenPass = technique.GetPassByIndex(0);
            gBufferGenPass = technique.GetPassByIndex(1);

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
            _device.Rasterizer.State = new RasterizerState(_device, desc);

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

            shaderByteCode = ShaderBytecode.CompileFromFile(Application.StartupPath + "\\grender.fx", "fx_4_0", shaderFlags, EffectFlags.None);

            effect2 = new Effect(_device, shaderByteCode);
            technique = effect2.GetTechniqueByIndex(0);
            gBufferRenderPass = technique.GetPassByIndex(0);

            Buffer quad = MeshFactory.CreateScreenQuad(_device);
            quadBinding = new VertexBufferBinding(quad, 20, 0);
            Matrix quadProjection = Matrix.OrthoLH(1, 1, 0.1f, 1.0f);
            effect2.GetVariableByName("ViewProjection").AsMatrix().SetMatrix(quadProjection);

            InputElement[] elements = new InputElement[]
            {
                new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0, InputClassification.PerVertexData, 0),
                new InputElement("TEXCOORD", 0, Format.R32G32_Float, 12, 0, InputClassification.PerVertexData, 0),
            };
            quadBufferLayout = new InputLayout(_device, gBufferRenderPass.Description.Signature, elements);


            info = new InfoText(_device);
            meshFactory = new MeshFactory(this);

            CreateBuffers();
            SetSceneConstants();
            LibraryManager.LibraryStarted();
        }

        protected void SetSceneConstants()
        {
            FreeLook freelook = Demo.Freelook;
            Vector3 up = MathHelper.Convert(freelook.Up);
            sceneConstants.View = Matrix.LookAtLH(MathHelper.Convert(freelook.Eye), MathHelper.Convert(freelook.Target), MathHelper.Convert(freelook.Up));
            sceneConstants.Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, NearPlane, FarPlane);
            sceneConstants.ViewInverse = Matrix.Invert(sceneConstants.View);

            Vector3 light = new Vector3(20, 30, 10);
            sceneConstants.LightPosition = new Vector4(light, 1);
            Texture2DDescription depthBuffer = lightDepthTexture.Description;
            Matrix lightView = Matrix.LookAtLH(light, Vector3.Zero, up);
            Matrix lightProjection = Matrix.OrthoLH(depthBuffer.Width / 8, depthBuffer.Height / 8, NearPlane, FarPlane);
            sceneConstants.LightViewProjection = lightView * lightProjection;

            using (var data = sceneConstantsBuffer.Map(MapMode.WriteDiscard))
            {
                Marshal.StructureToPtr(sceneConstants, data.DataPointer, false);
                sceneConstantsBuffer.Unmap();
            }

            effect2.GetVariableByName("InverseProjection").AsMatrix().SetMatrix(Matrix.Invert(sceneConstants.View * sceneConstants.Projection));
            effect2.GetVariableByName("InverseView").AsMatrix().SetMatrix(sceneConstants.ViewInverse);
            effect2.GetVariableByName("LightInverseViewProjection").AsMatrix().SetMatrix(Matrix.Invert(sceneConstants.LightViewProjection));
            effect2.GetVariableByName("LightPosition").AsVector().Set(sceneConstants.LightPosition);
        }

        void Render()
        {
            // Clear targets
            _device.ClearDepthStencilView(depthView, DepthStencilClearFlags.Depth, 1.0f, 0);
            _device.ClearRenderTargetView(renderView, ambient);
            _device.ClearRenderTargetView(gBufferLightView, ambient);
            _device.ClearRenderTargetView(gBufferNormalView, ambient);
            _device.ClearRenderTargetView(gBufferDiffuseView, ambient);

            meshFactory.InitInstancedRender(Demo.World.CollisionObjectArray);

            // Depth map pass
            if (shadowsEnabled)
            {
                _device.ClearDepthStencilView(lightDepthView, DepthStencilClearFlags.Depth, 1.0f, 0);
                outputMerger.SetDepthStencilState(lightDepthStencilState, 0);
                outputMerger.SetRenderTargets(0, null, lightDepthView);
                shadowGenPass.Apply();
                OnRender();
                effect2.GetVariableByName("lightDepthMap").AsShaderResource().SetResource(lightDepthRes);
            }

            // Render pass
            outputMerger.SetDepthStencilState(depthStencilState, 0);
            outputMerger.SetRenderTargets(3, gBufferViews, depthView);
            gBufferGenPass.Apply();
            OnRender();


            // G-buffer render pass
            outputMerger.SetDepthStencilState(null, 0);
            outputMerger.SetRenderTargets(1, renderViews, null);
            gBufferRenderPass.Apply();

            inputAssembler.SetVertexBuffers(0, quadBinding);
            inputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleStrip;
            inputAssembler.InputLayout = quadBufferLayout;
            _device.Draw(4, 0);

            info.OnRender(Demo.FramesPerSecond);

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
                Render();
            });
        }

        protected virtual void OnRender()
        {
            meshFactory.RenderInstanced();
        }

        public override void SetInfoText(string text)
        {
            info.Text = text;
        }
    }
}
