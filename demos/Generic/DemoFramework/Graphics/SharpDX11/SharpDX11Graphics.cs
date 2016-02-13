using BulletSharp;
using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DXGI;
using SharpDX.Windows;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Buffer = SharpDX.Direct3D11.Buffer;
using Device = SharpDX.Direct3D11.Device;
using Point = System.Drawing.Point;
using Matrix = SharpDX.Matrix;
using Vector3 = SharpDX.Vector3;
using Vector4 = SharpDX.Vector4;

namespace DemoFramework.SharpDX11
{
    public class SharpDX11Graphics : Graphics
    {
        bool shadowsEnabled = true;
        bool depthOfFieldEnabled = false;
        bool deferredLightingEnabled = true;

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
        Texture2D gBufferPostProcess;
        Texture2D gBufferPostProcessBlur1;
        Texture2D gBufferPostProcessBlur2;
        Texture2D depthTexture;
        Texture2D lightDepthTexture;
        //int shadowMapWidth = 2048, shadowMapHeight = 2048;

        EffectShaderResourceVariable lightBufferVar;
        EffectShaderResourceVariable normalBufferVar;
        EffectShaderResourceVariable diffuseBufferVar;
        EffectShaderResourceVariable depthMapVar;
        EffectShaderResourceVariable shadowLightDepthBufferVar;

        EffectVectorVariable sunLightDirectionVar;
        EffectMatrixVariable overlayViewProjectionVar;
        EffectScalarVariable viewportWidthVar;
        EffectScalarVariable viewportHeightVar;
        EffectVectorVariable viewParametersVar;

        RenderTargetView renderView;
        DepthStencilView depthView;
        DepthStencilView lightDepthView;
        RenderTargetView gBufferNormalView;
        RenderTargetView gBufferDiffuseView;
        RenderTargetView gBufferLightView;
        RenderTargetView gBufferPostProcessView;
        RenderTargetView gBufferPostProcessViewBlur1;
        RenderTargetView gBufferPostProcessViewBlur2;
        RenderTargetView[] gBufferViews;
        DepthStencilState depthState;
        DepthStencilState insideLightVolumeDepthState;
        DepthStencilState outsideLightVolumeDepthState;
        DepthStencilState lightDepthStencilState;

        Effect effect;
        EffectPass shadowGenPass;
        EffectPass gBufferGenPass;
        EffectPass gBufferRenderPass;
        EffectPass gBufferPostProcessPass;
        EffectPass gBufferPostProcessPass2;
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

        ShaderResourceView depthBufferRes;
        ShaderResourceView lightDepthRes;
        ShaderResourceView lightBufferRes;
        ShaderResourceView normalBufferRes;
        ShaderResourceView diffuseBufferRes;
        ShaderResourceView postProcessBufferRes;
        ShaderResourceView postProcessBufferBlur1Res;
        ShaderResourceView postProcessBufferBlur2Res;

        // Light accumulation shader
        Effect lightShader;
        EffectPass lightAccumulationPass;
        EffectShaderResourceVariable lightNormalBufferVar;
        EffectShaderResourceVariable lightDepthBufferVar;
        EffectVectorVariable lightViewParametersVar;
        EffectMatrixVariable lightWorldVar;
        EffectVectorVariable lightPositionRadiusVar;
        EffectVectorVariable lightColorVar;
        EffectMatrixVariable lightProjectionVar;
        EffectMatrixVariable lightViewVar;
        EffectMatrixVariable lightViewInverseVar;
        EffectScalarVariable lightViewportWidthVar;
        EffectScalarVariable lightViewportHeightVar;
        EffectVectorVariable lightEyePositionVar;

        int _width;
        int _height;
        float _nearPlane;

        ShaderSceneConstants sceneConstants;
        Buffer sceneConstantsBuffer;
        BlendState alphaBlendState;
        BlendState additiveBlendState;
        RasterizerState backCullState;
        RasterizerState frontCullState;
        RasterizerState noCullState;

        Vector3 sunLightDirection = -Vector3.Normalize(new Vector3(-20, 15, -20));
        Vector3 pointLightPosition = new Vector3(20, 25, 20);
        List<Light> lights = new List<Light>();

        InputLayout lightVolumeInputLayout;
        Vector3[] pointLightVolumeVertices;
        uint[] pointLightVolumeIndices;
        Buffer pointLightVolumeVertexBuffer;
        Buffer pointLightVolumeIndexBuffer;
        VertexBufferBinding pointLightVolumeVertexBufferBinding;

        InfoText info;

        MeshFactory _meshFactory;

        public override IDebugDraw GetPhysicsDebugDrawer()
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
                if (_immediateContext != null)
                {
                    _immediateContext.Rasterizer.State = value ? backCullState : noCullState;
                }

                base.CullingEnabled = value;
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        struct ShaderSceneConstants
        {
            public Matrix View;
            public Matrix Projection;
            public Matrix ViewInverse;
            public Matrix LightViewProjection;
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

            if (gBufferPostProcessView != null)
                gBufferPostProcessView.Dispose();

            if (depthOfFieldEnabled)
            {
                if (gBufferPostProcessViewBlur1 != null)
                    gBufferPostProcessViewBlur1.Dispose();

                if (gBufferPostProcessViewBlur2 != null)
                    gBufferPostProcessViewBlur2.Dispose();
            }

            if (gBufferLight != null)
                gBufferLight.Dispose();

            if (gBufferNormal != null)
                gBufferNormal.Dispose();

            if (gBufferDiffuse != null)
                gBufferDiffuse.Dispose();

            if (gBufferPostProcess != null)
                gBufferPostProcess.Dispose();

            if (gBufferPostProcessBlur1 != null)
                gBufferPostProcessBlur1.Dispose();

            if (gBufferPostProcessBlur2 != null)
                gBufferPostProcessBlur2.Dispose();

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

            if (depthBufferRes != null)
                depthBufferRes.Dispose();

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

            blendStateDesc.RenderTarget[0].IsBlendEnabled = true;
            blendStateDesc.RenderTarget[0].SourceBlend = BlendOption.One;
            blendStateDesc.RenderTarget[0].DestinationBlend = BlendOption.One;
            blendStateDesc.RenderTarget[0].BlendOperation = BlendOperation.Add;
            blendStateDesc.RenderTarget[0].SourceAlphaBlend = BlendOption.One;
            blendStateDesc.RenderTarget[0].DestinationAlphaBlend = BlendOption.Zero;
            blendStateDesc.RenderTarget[0].AlphaBlendOperation = BlendOperation.Add;
            blendStateDesc.RenderTarget[0].RenderTargetWriteMask = ColorWriteMaskFlags.All;
            additiveBlendState = new BlendState(_device, blendStateDesc);
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

            gBufferPostProcess = new Texture2D(_device, gBufferDesc);
            gBufferPostProcessView = new RenderTargetView(_device, gBufferPostProcess);

            if (depthOfFieldEnabled)
            {
                gBufferPostProcessBlur1 = new Texture2D(_device, gBufferDesc);
                gBufferPostProcessViewBlur1 = new RenderTargetView(_device, gBufferPostProcessBlur1);

                gBufferPostProcessBlur2 = new Texture2D(_device, gBufferDesc);
                gBufferPostProcessViewBlur2 = new RenderTargetView(_device, gBufferPostProcessBlur2);
            }

            gBufferViews = new[] { gBufferNormalView, gBufferDiffuseView };

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
            postProcessBufferRes = new ShaderResourceView(_device, gBufferPostProcess, gBufferResourceDesc);
            if (depthOfFieldEnabled)
            {
                postProcessBufferBlur1Res = new ShaderResourceView(_device, gBufferPostProcessBlur1, gBufferResourceDesc);
                postProcessBufferBlur2Res = new ShaderResourceView(_device, gBufferPostProcessBlur2, gBufferResourceDesc);
            }


            Texture2DDescription depthDesc = new Texture2DDescription()
            {
                ArraySize = 1,
                BindFlags = BindFlags.DepthStencil | BindFlags.ShaderResource,
                CpuAccessFlags = CpuAccessFlags.None,
                Format = Format.R32_Typeless,
                Height = _height,
                Width = _width,
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
            depthBufferRes = new ShaderResourceView(_device, depthTexture, resourceDesc);

            lightDepthTexture = new Texture2D(_device, depthDesc);
            lightDepthView = new DepthStencilView(_device, lightDepthTexture, depthViewDesc);
            lightDepthRes = new ShaderResourceView(_device, lightDepthTexture, resourceDesc);

            _immediateContext.Rasterizer.SetViewport(0, 0, _width, _height);
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

            string[] sources = { "shader.fx", "grender.fx" };
            using (var shaderByteCode = ShaderLoader.FromResource(Assembly.GetExecutingAssembly(), sources, shaderFlags))
            {
                effect = new Effect(_device, shaderByteCode);
            }
            EffectTechnique technique = effect.GetTechniqueByName("GBufferCreate");
            shadowGenPass = technique.GetPassByName("ShadowMap");
            gBufferGenPass = technique.GetPassByName("GBufferGen");
            debugDrawPass = technique.GetPassByName("DebugDraw");

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

            RasterizerStateDescription _rasterizerStateDesc = new RasterizerStateDescription()
            {
                CullMode = CullMode.None,
                FillMode = FillMode.Solid,
                DepthBias = 0,
                DepthBiasClamp = 0,
                SlopeScaledDepthBias = 0,
                IsDepthClipEnabled = true,
            };
            noCullState = new RasterizerState(_device, _rasterizerStateDesc);
            _rasterizerStateDesc.CullMode = CullMode.Back;
            backCullState = new RasterizerState(_device, _rasterizerStateDesc);
            _rasterizerStateDesc.CullMode = CullMode.Front;
            frontCullState = new RasterizerState(_device, _rasterizerStateDesc);
            _immediateContext.Rasterizer.State = CullingEnabled ? backCullState : noCullState;

            DepthStencilStateDescription depthDesc = new DepthStencilStateDescription()
            {
                IsDepthEnabled = true,
                IsStencilEnabled = false,
                DepthWriteMask = DepthWriteMask.All,
                DepthComparison = Comparison.Less
            };
            depthState = new DepthStencilState(_device, depthDesc);
            depthDesc.DepthWriteMask = DepthWriteMask.Zero;
            outsideLightVolumeDepthState = new DepthStencilState(_device, depthDesc);
            depthDesc.DepthComparison = Comparison.Greater;
            insideLightVolumeDepthState = new DepthStencilState(_device, depthDesc);

            DepthStencilStateDescription lightDepthStateDesc = new DepthStencilStateDescription()
            {
                IsDepthEnabled = true,
                IsStencilEnabled = false,
                DepthWriteMask = DepthWriteMask.All,
                DepthComparison = Comparison.Less
            };
            lightDepthStencilState = new DepthStencilState(_device, lightDepthStateDesc);


            // grender.fx
            technique = effect.GetTechniqueByName("DeferredShader");
            gBufferRenderPass = technique.GetPassByName("DeferredShader");
            gBufferPostProcessPass = technique.GetPassByName("Blur");
            gBufferPostProcessPass2 = technique.GetPassByName("PostProcess");
            gBufferOverlayPass = technique.GetPassByName("Overlay");

            lightBufferVar = effect.GetVariableByName("lightBuffer").AsShaderResource();
            normalBufferVar = effect.GetVariableByName("normalBuffer").AsShaderResource();
            diffuseBufferVar = effect.GetVariableByName("diffuseBuffer").AsShaderResource();
            depthMapVar = effect.GetVariableByName("depthMap").AsShaderResource();
            shadowLightDepthBufferVar = effect.GetVariableByName("lightDepthMap").AsShaderResource();

            sunLightDirectionVar = effect.GetVariableByName("SunLightDirection").AsVector();
            viewportWidthVar = effect.GetVariableByName("ViewportWidth").AsScalar();
            viewportHeightVar = effect.GetVariableByName("ViewportHeight").AsScalar();
            viewParametersVar = effect.GetVariableByName("ViewParameters").AsVector();

            overlayViewProjectionVar = effect.GetVariableByName("OverlayViewProjection").AsMatrix();


            // light.fx
            using (var shaderByteCode = ShaderLoader.FromResource(Assembly.GetExecutingAssembly(), "light.fx", shaderFlags))
            {
                lightShader = new Effect(_device, shaderByteCode);
            }

            technique = lightShader.GetTechniqueByIndex(0);
            lightAccumulationPass = technique.GetPassByName("Light");

            lightWorldVar = lightShader.GetVariableByName("World").AsMatrix();
            lightPositionRadiusVar = lightShader.GetVariableByName("PositionRadius").AsVector();
            lightColorVar = lightShader.GetVariableByName("Color").AsVector();

            lightProjectionVar = lightShader.GetVariableByName("Projection").AsMatrix();
            lightViewVar = lightShader.GetVariableByName("View").AsMatrix();
            lightViewInverseVar = lightShader.GetVariableByName("ViewInverse").AsMatrix();
            lightViewportWidthVar = lightShader.GetVariableByName("ViewportWidth").AsScalar();
            lightViewportHeightVar = lightShader.GetVariableByName("ViewportHeight").AsScalar();
            lightEyePositionVar = lightShader.GetVariableByName("EyePosition").AsVector();
            lightViewParametersVar = lightShader.GetVariableByName("ViewParameters").AsVector();

            InputElement[] elements = new InputElement[]
            {
                new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0, InputClassification.PerVertexData, 0),
            };
            lightVolumeInputLayout = new InputLayout(Device, lightShader.GetTechniqueByIndex(0).GetPassByName("Light").Description.Signature, elements);

            pointLightVolumeVertices = Light.CreatePointLightVolume(out pointLightVolumeIndices);
            BufferDescription vertexBufferDesc = new BufferDescription()
            {
                SizeInBytes = Vector3.SizeInBytes * pointLightVolumeVertices.Length,
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.VertexBuffer,
            };

            using (var data = new SharpDX.DataStream(vertexBufferDesc.SizeInBytes, false, true))
            {
                data.WriteRange(pointLightVolumeVertices);
                data.Position = 0;
                pointLightVolumeVertexBuffer = new Buffer(Device, data, vertexBufferDesc);
            }
            pointLightVolumeVertexBufferBinding = new VertexBufferBinding(pointLightVolumeVertexBuffer, 12, 0);

            BufferDescription indexBufferDesc = new BufferDescription()
            {
                SizeInBytes = sizeof(uint) * pointLightVolumeIndices.Length,
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.IndexBuffer
            };
            using (var data = new SharpDX.DataStream(indexBufferDesc.SizeInBytes, false, true))
            {
                data.WriteRange(pointLightVolumeIndices);
                data.Position = 0;
                pointLightVolumeIndexBuffer = new Buffer(Device, data, indexBufferDesc);
            }

            lightDepthBufferVar = lightShader.GetVariableByName("depthBuffer").AsShaderResource();
            lightNormalBufferVar = lightShader.GetVariableByName("normalBuffer").AsShaderResource();

            lights.Add(new Light(pointLightPosition, 60, new Vector4(1, 0.95f, 0.9f, 1)));
            //lights.Add(new Light(pointLightPosition, 60, new Vector4(0, 0, 1, 1)));
            //lights.Add(new Light(new Vector3(-10, 10, 10), 30, new Vector4(1, 0, 0, 1)));
            //lights.Add(new Light(new Vector3(10, 5, -10), 20, new Vector4(0, 1, 0, 1)));
            //lights.Add(new Light(new Vector3(-10, 5, -10), 20, new Vector4(1, 0, 1, 1)));


            info = new InfoText(_device, 256, 256);
            _meshFactory = new MeshFactory(this);
            MeshFactory = _meshFactory;

            CreateBuffers();
            GraphicsLibraryManager.LibraryStarted();
        }

        void SetSceneConstants()
        {
            FreeLook freelook = Demo.Freelook;
            Vector3 up = MathHelper.Convert(freelook.Up);
            Vector3 eye = MathHelper.Convert(freelook.Eye);
            Vector4 eyePosition = new Vector4(eye, 1);

            sceneConstants.View = Matrix.LookAtLH(eye, MathHelper.Convert(freelook.Target), up);
            Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, _nearPlane, FarPlane, out sceneConstants.Projection);
            Matrix.Invert(ref sceneConstants.View, out sceneConstants.ViewInverse);

            Texture2DDescription depthBuffer = lightDepthTexture.Description;
            Vector3 lightPosition = sunLightDirection * -60;
            Matrix lightView = Matrix.LookAtLH(lightPosition, Vector3.Zero, up);
            //Matrix lightProjection = Matrix.OrthoLH(depthBuffer.Width / 8.0f, depthBuffer.Height / 8.0f, _nearPlane, FarPlane);
            Matrix lightProjection = Matrix.PerspectiveFovLH(FieldOfView, (float)depthBuffer.Width / (float)depthBuffer.Height, _nearPlane, FarPlane);
            sceneConstants.LightViewProjection = lightView * lightProjection;

            SharpDX.DataStream data;
            _immediateContext.MapSubresource(sceneConstantsBuffer, MapMode.WriteDiscard, SharpDX.Direct3D11.MapFlags.None, out data);
            Marshal.StructureToPtr(sceneConstants, data.DataPointer, false);
            _immediateContext.UnmapSubresource(sceneConstantsBuffer, 0);
            data.Dispose();

            sunLightDirectionVar.Set(new Vector4(sunLightDirection, 1));

            Matrix overlayMatrix = Matrix.Scaling(info.Width / _width, info.Height / _height, 1.0f);
            overlayMatrix *= Matrix.Translation(-(_width - info.Width) / _width, (_height - info.Height) / _height, 0.0f);
            overlayViewProjectionVar.SetMatrix(overlayMatrix);


            lightProjectionVar.SetMatrixTranspose(ref sceneConstants.Projection);
            lightViewVar.SetMatrixTranspose(ref sceneConstants.View);
            lightViewInverseVar.SetMatrix(ref sceneConstants.ViewInverse);
            lightViewportWidthVar.Set(_width);
            lightViewportHeightVar.Set(_height);
            lightEyePositionVar.Set(ref eyePosition);

            float tanHalfFovY = (float)Math.Tan(FieldOfView * 0.5f);
            float tanHalfFovX = tanHalfFovY * AspectRatio;
            float projectionA = FarPlane / (FarPlane - _nearPlane);
            float projectionB = -projectionA * _nearPlane;
            Vector4 viewParameters = new Vector4(tanHalfFovX, tanHalfFovY, projectionA, projectionB);
            lightViewParametersVar.Set(ref viewParameters);


            viewportWidthVar.Set(_width);
            viewportHeightVar.Set(_height);
            viewParametersVar.Set(ref viewParameters);
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
                if (Form.WindowState == FormWindowState.Minimized)
                    return;
                Demo.Clock.StartRender();
                Render();
                Demo.Clock.StopRender();
            });
        }

        protected virtual void OnInitialize()
        {
        }

        void RenderLights()
        {
            inputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleList;
            inputAssembler.InputLayout = lightVolumeInputLayout;
            inputAssembler.SetVertexBuffers(0, pointLightVolumeVertexBufferBinding);
            inputAssembler.SetIndexBuffer(pointLightVolumeIndexBuffer, Format.R32_UInt, 0);

            lightDepthBufferVar.SetResource(depthBufferRes);
            lightNormalBufferVar.SetResource(normalBufferRes);

            var previousState = _immediateContext.Rasterizer.State;

            // Camera outside light volume
            _immediateContext.Rasterizer.State = backCullState;
            outputMerger.SetDepthStencilState(outsideLightVolumeDepthState);
            foreach (var light in lights)
            {
                float radius = light.Radius;
                float bias = radius * 2;
                if ((light.Position - MathHelper.Convert(Demo.Freelook.Eye)).LengthSquared() >= (radius * radius) + bias)
                {
                    RenderLight(light);
                }
            }

            // Camera inside light volume
            _immediateContext.Rasterizer.State = frontCullState;
            outputMerger.SetDepthStencilState(insideLightVolumeDepthState);
            foreach (var light in lights)
            {
                float bias = light.Radius * 2;
                if ((light.Position - MathHelper.Convert(Demo.Freelook.Eye)).LengthSquared() < (light.Radius * light.Radius) + bias)
                {
                    RenderLight(light);
                }
            }

            _immediateContext.Rasterizer.State = previousState;
        }

        void RenderLight(Light light)
        {
            lightWorldVar.SetMatrixTranspose(light.World);
            lightPositionRadiusVar.Set(new Vector4(light.Position, light.Radius));
            lightColorVar.Set(light.Color);
            lightAccumulationPass.Apply(_immediateContext);

            _immediateContext.DrawIndexed(pointLightVolumeIndices.Length, 0, 0);
        }

        void Render()
        {
            // Clear targets
            _immediateContext.ClearDepthStencilView(depthView, DepthStencilClearFlags.Depth, 1.0f, 0);
            //_immediateContext.ClearRenderTargetView(renderView, ambient);
            _immediateContext.ClearRenderTargetView(gBufferLightView, Color4.Black);
            _immediateContext.ClearRenderTargetView(gBufferNormalView, Color4.Black);
            _immediateContext.ClearRenderTargetView(gBufferDiffuseView, Color4.Black);


            // Read collision object transforms, create geometry, etc.
            _meshFactory.InitInstancedRender();


            // Light depth map pass
            _immediateContext.ClearDepthStencilView(lightDepthView, DepthStencilClearFlags.Depth, 1.0f, 0);
            if (shadowsEnabled)
            {
                outputMerger.SetDepthStencilState(lightDepthStencilState);
                outputMerger.SetRenderTargets(lightDepthView);
                shadowGenPass.Apply(_immediateContext);
                OnRender();
                shadowLightDepthBufferVar.SetResource(lightDepthRes);
            }

            // Render geometry (colors, normals, depth) to G-buffer
            outputMerger.SetDepthStencilState(depthState);
            outputMerger.SetTargets(depthView, gBufferViews);
            gBufferGenPass.Apply(_immediateContext);
            OnRender();

            if (Demo.IsDebugDrawEnabled)
            {
                debugDrawPass.Apply(_immediateContext);
                (Demo.World.DebugDrawer as PhysicsDebugDraw).DrawDebugWorld(Demo.World);
            }

            // Light accumulation to G-buffer
            if (deferredLightingEnabled)
            {
                outputMerger.SetBlendState(additiveBlendState);
                // Can't set depthView as render target and shader variable at the same time,
                // so early HW depth test is not available for light volumes.
                //outputMerger.SetTargets(depthView, gBufferLightView);
                outputMerger.SetTargets(gBufferLightView);
                RenderLights();
            }


            // Render G-buffer
            outputMerger.SetBlendState(alphaBlendState);
            outputMerger.SetDepthStencilState(null);
            if (depthOfFieldEnabled)
            {
                outputMerger.SetTargets(gBufferPostProcessView);
            }
            else
            {
                outputMerger.SetTargets(renderView);
            }
            inputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleStrip;

            lightBufferVar.SetResource(lightBufferRes);
            normalBufferVar.SetResource(normalBufferRes);
            diffuseBufferVar.SetResource(diffuseBufferRes);
            depthMapVar.SetResource(depthBufferRes);

            //_immediateContext.ClearRenderTargetView(gBufferPostProcessView, Color4.Black);
            gBufferRenderPass.Apply(_immediateContext);
            _immediateContext.Draw(3, 0);

            if (depthOfFieldEnabled)
            {
                diffuseBufferVar.SetResource(postProcessBufferRes);
                outputMerger.SetTargets(gBufferPostProcessViewBlur1);
                gBufferPostProcessPass.Apply(_immediateContext);
                _immediateContext.Draw(3, 0);

                diffuseBufferVar.SetResource(postProcessBufferBlur1Res);
                outputMerger.SetTargets(gBufferPostProcessViewBlur2);
                gBufferPostProcessPass.Apply(_immediateContext);
                _immediateContext.Draw(3, 0);


                diffuseBufferVar.SetResource(postProcessBufferBlur2Res);
                outputMerger.SetTargets(gBufferPostProcessViewBlur1);
                gBufferPostProcessPass.Apply(_immediateContext);
                _immediateContext.Draw(3, 0);


                diffuseBufferVar.SetResource(postProcessBufferBlur1Res);
                outputMerger.SetTargets(gBufferPostProcessViewBlur2);
                gBufferPostProcessPass.Apply(_immediateContext);
                _immediateContext.Draw(3, 0);


                diffuseBufferVar.SetResource(postProcessBufferRes);
                normalBufferVar.SetResource(postProcessBufferBlur2Res);
                outputMerger.SetTargets(renderView);
                gBufferPostProcessPass2.Apply(_immediateContext);
                _immediateContext.Draw(3, 0);
            }


            // Render overlay
            info.Render();
            outputMerger.SetBlendState(alphaBlendState);
            diffuseBufferVar.SetResource(info.OverlayBufferRes);
            gBufferOverlayPass.Apply(_immediateContext);
            _immediateContext.Draw(4, 0);

            _swapChain.Present(0, PresentFlags.None);
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
