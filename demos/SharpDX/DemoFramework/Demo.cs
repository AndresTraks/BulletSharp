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

namespace DemoFramework
{
    public class Demo : IDisposable
    {
        bool shadowsEnabled = true;
        bool depthOfFieldEnabled = false;
        bool deferredLightingEnabled = true;

        public Form Form { get; }

        Device _device;
        public Device Device
        {
            get { return _device; }
        }
        DeviceContext _immediateContext;
        OutputMergerStage outputMerger;
        InputAssemblerStage inputAssembler;

        SwapChain _swapChain;

        public float AspectRatio
        {
            get { return (float)Width / (float)Height; }
        }

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

        protected int Width { get; set; }
        protected int Height { get; set; }
        protected float NearPlane { get; set; }
        protected float FarPlane { get; set; }
        protected float FieldOfView { get; set; }

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

        // Info text
        protected InfoText Info { get; set; }
        CultureInfo culture = CultureInfo.InvariantCulture;

        string _demoText = "";
        protected string DemoText
        {
            get { return _demoText; }
            set
            {
                _demoText = value;
                SetInfoText();
            }
        }

        MeshFactory _meshFactory;

        protected Input Input { get; private set; }
        protected FreeLook Freelook { get; set; }

        // Frame counting
        Clock clock = new Clock();
        float frameAccumulator;
        int _interpolatedSteps;

        public float FrameDelta { get; private set; }
        public float FramesPerSecond { get; private set; }

        public PhysicsContext PhysicsContext { get; set; }

        protected BoxShape shootBoxShape;
        protected float shootBoxInitialSpeed = 40;
        RigidBody pickedBody;
        protected TypedConstraint pickConstraint;
        float oldPickingDist;

        // Debug drawing
        DebugDrawModes _debugDrawMode = DebugDrawModes.DrawWireframe;
        IDebugDraw _debugDrawer;

        bool isCullingEnabled = true;
        public bool CullingEnabled
        {
            get
            {
                return isCullingEnabled;
            }
            set
            {
                if (isCullingEnabled != value && _immediateContext != null)
                {
                    _immediateContext.Rasterizer.State = value ? backCullState : noCullState;
                    isCullingEnabled = value;
                }
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

        public Demo()
        {
            Form = new RenderForm();
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
            Form.ClientSize = new Size(Width, Height);

            // SwapChain description
            var desc = new SwapChainDescription()
            {
                BufferCount = 1,
                ModeDescription = new ModeDescription(Width, Height, new Rational(60, 1), Format.R8G8B8A8_UNorm),
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
            depthBufferRes = new ShaderResourceView(_device, depthTexture, resourceDesc);

            lightDepthTexture = new Texture2D(_device, depthDesc);
            lightDepthView = new DepthStencilView(_device, lightDepthTexture, depthViewDesc);
            lightDepthRes = new ShaderResourceView(_device, lightDepthTexture, resourceDesc);

            _immediateContext.Rasterizer.SetViewport(0, 0, Width, Height);
        }

        public void Initialize()
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

                Width = Form.ClientSize.Width;
                Height = Form.ClientSize.Height;
                _swapChain.ResizeBuffers(_swapChain.Description.BufferCount, 0, 0, Format.Unknown, 0);

                CreateBuffers();
                SetSceneConstants();
            };

            Width = 1024;
            Height = 768;
            NearPlane = 1.0f;
            FarPlane = 200.0f;
            FieldOfView = (float)Math.PI / 4;

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

            InputElement[] elements = {
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


            Info = new InfoText(_device, 256, 256);
            _meshFactory = new MeshFactory(this);

            CreateBuffers();
        }

        protected void SetSceneConstants()
        {
            Vector4 eyePosition = new Vector4(Freelook.Eye, 1);

            sceneConstants.View = Matrix.LookAtLH(Freelook.Eye, Freelook.Target, Freelook.Up);
            Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, NearPlane, FarPlane, out sceneConstants.Projection);
            Matrix.Invert(ref sceneConstants.View, out sceneConstants.ViewInverse);

            Texture2DDescription depthBuffer = lightDepthTexture.Description;
            Vector3 lightPosition = sunLightDirection * -60;
            Matrix lightView = Matrix.LookAtLH(lightPosition, Vector3.Zero, Freelook.Up);
            //Matrix lightProjection = Matrix.OrthoLH(depthBuffer.Width / 8.0f, depthBuffer.Height / 8.0f, _nearPlane, FarPlane);
            Matrix lightProjection = Matrix.PerspectiveFovLH(FieldOfView, (float)depthBuffer.Width / (float)depthBuffer.Height, NearPlane, FarPlane);
            sceneConstants.LightViewProjection = lightView * lightProjection;

            SharpDX.DataStream data;
            _immediateContext.MapSubresource(sceneConstantsBuffer, MapMode.WriteDiscard, SharpDX.Direct3D11.MapFlags.None, out data);
            Marshal.StructureToPtr(sceneConstants, data.DataPointer, false);
            _immediateContext.UnmapSubresource(sceneConstantsBuffer, 0);
            data.Dispose();

            sunLightDirectionVar.Set(new Vector4(sunLightDirection, 1));

            Matrix overlayMatrix = Matrix.Scaling(Info.Width / Width, Info.Height / Height, 1.0f);
            overlayMatrix *= Matrix.Translation(-(Width - Info.Width) / Width, (Height - Info.Height) / Height, 0.0f);
            overlayViewProjectionVar.SetMatrix(overlayMatrix);


            lightProjectionVar.SetMatrixTranspose(ref sceneConstants.Projection);
            lightViewVar.SetMatrixTranspose(ref sceneConstants.View);
            lightViewInverseVar.SetMatrix(ref sceneConstants.ViewInverse);
            lightViewportWidthVar.Set(Width);
            lightViewportHeightVar.Set(Height);
            lightEyePositionVar.Set(ref eyePosition);

            float tanHalfFovY = (float)Math.Tan(FieldOfView * 0.5f);
            float tanHalfFovX = tanHalfFovY * AspectRatio;
            float projectionA = FarPlane / (FarPlane - NearPlane);
            float projectionB = -projectionA * NearPlane;
            Vector4 viewParameters = new Vector4(tanHalfFovX, tanHalfFovY, projectionA, projectionB);
            lightViewParametersVar.Set(ref viewParameters);


            viewportWidthVar.Set(Width);
            viewportHeightVar.Set(Height);
            viewParametersVar.Set(ref viewParameters);
        }

        public void UpdateView()
        {
            SetSceneConstants();
        }

        public void Run()
        {
            Input = new Input(Form);
            Freelook = new FreeLook(Input);

            Initialize();
            CullingEnabled = isCullingEnabled;
            OnInitialize();
            if (PhysicsContext.World == null)
            {
                PhysicsContext.InitPhysics();
            }
            /*
            if (_isDebugDrawEnabled)
            {
                if (_debugDrawer == null)
                {
                    _debugDrawer = new PhysicsDebugDraw(this);
                    _debugDrawer.DebugMode = DebugDrawMode;
                }
                if (PhysicsContext.World != null)
                {
                    PhysicsContext.World.DebugDrawer = _debugDrawer;
                }
            }
            */
            UpdateView();
            SetInfoText();

            RenderLoop.Run(Form, () =>
            {
                OnHandleInput();
                OnUpdate();
                if (Form.WindowState != FormWindowState.Minimized)
                {
                    clock.StartRender();
                    Render();
                    clock.StopRender();
                }
            });
        }

        protected virtual void OnInitialize()
        {
        }

        void SetInfoText()
        {
            //FramesPerSecond = clock.FrameCount / frameAccumulator;

            Info.Text = string.Format("Physics: {0} ms\n" +
                "Render: {1} ms\n" +
                "Interpolated: {2}/{3}\n" +
                "F1 - Help\n" +
                "{4}",
                clock.PhysicsAverage.ToString("0.000", culture),
                clock.RenderAverage.ToString("0.000", culture),
                _interpolatedSteps,
                clock.FrameCount,
                _demoText);
        }

        protected virtual void OnUpdate()
        {
            FrameDelta = clock.GetFrameDelta();
            frameAccumulator += FrameDelta;
            if (frameAccumulator >= 1.0f)
            {
                SetInfoText();

                frameAccumulator = 0.0f;
                _interpolatedSteps = 0;
                clock.Reset();
            }

            if (PhysicsContext.World != null)
            {
                clock.StartPhysics();
                int steps = PhysicsContext.World.StepSimulation(FrameDelta);
                clock.StopPhysics();
                if (steps == 0)
                {
                    _interpolatedSteps++;
                }
            }

            if (Freelook.Update(FrameDelta))
                UpdateView();

            Input.ClearKeyCache();
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
                if ((light.Position - Freelook.Eye).LengthSquared() >= (radius * radius) + bias)
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
                if ((light.Position - Freelook.Eye).LengthSquared() < (light.Radius * light.Radius) + bias)
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
            /*
            if (IsDebugDrawEnabled)
            {
                debugDrawPass.Apply(_immediateContext);
                (PhysicsContext.World.DebugDrawer as PhysicsDebugDraw).DrawDebugWorld(PhysicsContext.World);
            }
            */

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
            Info.Render();
            outputMerger.SetBlendState(alphaBlendState);
            diffuseBufferVar.SetResource(Info.OverlayBufferRes);
            gBufferOverlayPass.Apply(_immediateContext);
            _immediateContext.Draw(4, 0);

            _swapChain.Present(0, PresentFlags.None);
        }

        protected virtual void OnRender()
        {
            _meshFactory.RenderInstanced();
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                PhysicsContext.ExitPhysics();
            }
        }

        protected virtual void OnHandleInput()
        {
            if (Input.KeysPressed.Count != 0)
            {
                switch (Input.KeysPressed[0])
                {
                    case Keys.Escape:
                    case Keys.Q:
                        Form.Close();
                        return;
                    case Keys.F1:
                        MessageBox.Show(
                            "Move using mouse and WASD + shift\n" +
                            "Space - Shoot box\n" +
                            "Q - Quit\n\n" +
                            "G - Toggle shadows\n" +
                            "L - Toggle deferred lighting\n",
                            "Help");
                        return;
                    case Keys.F3:
                        //IsDebugDrawEnabled = !IsDebugDrawEnabled;
                        break;
                    case Keys.F11:
                        //ToggleFullScreen();
                        break;
                    case (Keys.Control | Keys.F):
                        const int maxSerializeBufferSize = 1024 * 1024 * 5;
                        using (var serializer = new DefaultSerializer(maxSerializeBufferSize))
                        {
                            PhysicsContext.World.Serialize(serializer);

                            byte[] dataBytes = new byte[serializer.CurrentBufferSize];
                            Marshal.Copy(serializer.BufferPointer, dataBytes, 0, dataBytes.Length);
                            using (var file = new System.IO.FileStream("world.bullet", System.IO.FileMode.Create))
                            {
                                file.Write(dataBytes, 0, dataBytes.Length);
                            }
                        }
                        break;
                    case Keys.G:
                        shadowsEnabled = !shadowsEnabled;
                        break;
                    case Keys.L:
                        deferredLightingEnabled = !deferredLightingEnabled;
                        break;
                    case Keys.Space:
                        PhysicsContext.ShootBox(Freelook.Eye, GetRayTo(Input.MousePoint, Freelook.Eye, Freelook.Target, FieldOfView));
                        break;
                }
            }

            if (Input.MousePressed != MouseButtons.None)
            {
                Vector3 rayTo = GetRayTo(Input.MousePoint, Freelook.Eye, Freelook.Target, FieldOfView);

                if (Input.MousePressed == MouseButtons.Right)
                {
                    if (PhysicsContext.World != null)
                    {
                        Vector3 rayFrom = Freelook.Eye;

                        var rayCallback = new ClosestRayResultCallback(ref rayFrom, ref rayTo);
                        PhysicsContext.World.RayTest(rayFrom, rayTo, rayCallback);
                        if (rayCallback.HasHit)
                        {
                            RigidBody body = rayCallback.CollisionObject as RigidBody;
                            if (body != null)
                            {
                                if (!(body.IsStaticObject || body.IsKinematicObject))
                                {
                                    pickedBody = body;
                                    pickedBody.ActivationState = ActivationState.DisableDeactivation;

                                    Vector3 pickPos = rayCallback.HitPointWorld;
                                    Vector3 localPivot = Vector3.TransformCoordinate(pickPos, Matrix.Invert(body.CenterOfMassTransform));

                                    if (Input.KeysDown.Contains(Keys.ShiftKey))
                                    {
                                        Generic6DofConstraint dof6 = new Generic6DofConstraint(body, Matrix.Translation(localPivot), false)
                                        {
                                            LinearLowerLimit = Vector3.Zero,
                                            LinearUpperLimit = Vector3.Zero,
                                            AngularLowerLimit = Vector3.Zero,
                                            AngularUpperLimit = Vector3.Zero
                                        };
                                        pickConstraint = dof6;

                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 0);
                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 1);
                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 2);
                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 3);
                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 4);
                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 5);

                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 0);
                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 1);
                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 2);
                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 3);
                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 4);
                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 5);
                                    }
                                    else
                                    {
                                        var p2p = new Point2PointConstraint(body, localPivot);
                                        pickConstraint = p2p;
                                        p2p.Setting.ImpulseClamp = 30;
                                        //very weak constraint for picking
                                        p2p.Setting.Tau = 0.001f;
                                        /*
                                        p2p.SetParam(ConstraintParams.Cfm, 0.8f, 0);
                                        p2p.SetParam(ConstraintParams.Cfm, 0.8f, 1);
                                        p2p.SetParam(ConstraintParams.Cfm, 0.8f, 2);
                                        p2p.SetParam(ConstraintParams.Erp, 0.1f, 0);
                                        p2p.SetParam(ConstraintParams.Erp, 0.1f, 1);
                                        p2p.SetParam(ConstraintParams.Erp, 0.1f, 2);
                                        */
                                    }
                                    PhysicsContext.World.AddConstraint(pickConstraint);

                                    oldPickingDist = (pickPos - rayFrom).Length();
                                }
                            }
                        }
                        rayCallback.Dispose();
                    }
                }
            }
            else if (Input.MouseReleased == MouseButtons.Right)
            {
                RemovePickingConstraint();
            }

            // Mouse movement
            if (Input.MouseDown == MouseButtons.Right)
            {
                if (pickConstraint != null)
                {
                    Vector3 newRayTo = GetRayTo(Input.MousePoint, Freelook.Eye, Freelook.Target, FieldOfView);

                    if (pickConstraint.ConstraintType == TypedConstraintType.D6)
                    {
                        Generic6DofConstraint pickCon = pickConstraint as Generic6DofConstraint;

                        //keep it at the same picking distance
                        Vector3 rayFrom = Freelook.Eye;
                        Vector3 dir = newRayTo - rayFrom;
                        dir.Normalize();
                        dir *= oldPickingDist;
                        Vector3 newPivotB = rayFrom + dir;

                        Matrix tempFrameOffsetA = pickCon.FrameOffsetA;
                        tempFrameOffsetA.M41 = newPivotB.X;
                        tempFrameOffsetA.M42 = newPivotB.Y;
                        tempFrameOffsetA.M43 = newPivotB.Z;
                        pickCon.SetFrames(tempFrameOffsetA, pickCon.FrameOffsetB);
                    }
                    else
                    {
                        Point2PointConstraint pickCon = pickConstraint as Point2PointConstraint;

                        //keep it at the same picking distance
                        Vector3 rayFrom = Freelook.Eye;
                        Vector3 dir = newRayTo - rayFrom;
                        dir.Normalize();
                        dir *= oldPickingDist;
                        pickCon.PivotInB = rayFrom + dir;
                    }
                }
            }
        }

        void RemovePickingConstraint()
        {
            if (pickConstraint == null) return;
            if (PhysicsContext.World == null) return;

            PhysicsContext.World.RemoveConstraint(pickConstraint);
            pickConstraint.Dispose();
            pickConstraint = null;
            pickedBody.ForceActivationState(ActivationState.ActiveTag);
            pickedBody.DeactivationTime = 0;
            pickedBody = null;
        }

        protected Vector3 GetRayTo(Point point, Vector3 eye, Vector3 target, float fov)
        {
            float aspect;

            Vector3 rayForward = target - eye;
            rayForward.Normalize();
            const float farPlane = 10000.0f;
            rayForward *= farPlane;

            Vector3 vertical = Freelook.Up;

            Vector3 hor = Vector3.Cross(rayForward, vertical);
            hor.Normalize();
            vertical = Vector3.Cross(hor, rayForward);
            vertical.Normalize();

            float tanFov = (float)Math.Tan(fov / 2);
            hor *= 2.0f * farPlane * tanFov;
            vertical *= 2.0f * farPlane * tanFov;

            Size clientSize = Form.ClientSize;
            if (clientSize.Width > clientSize.Height)
            {
                aspect = (float)clientSize.Width / (float)clientSize.Height;
                hor *= aspect;
            }
            else
            {
                aspect = (float)clientSize.Height / (float)clientSize.Width;
                vertical *= aspect;
            }

            Vector3 rayToCenter = eye + rayForward;
            Vector3 dHor = hor / (float)clientSize.Width;
            Vector3 dVert = vertical / (float)clientSize.Height;

            Vector3 rayTo = rayToCenter - 0.5f * hor + 0.5f * vertical;
            rayTo += (clientSize.Width - point.X) * dHor;
            rayTo -= point.Y * dVert;
            return rayTo;
        }
    }
}
