using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using BulletSharp;
using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using SharpDX.Windows;
using Buffer = SharpDX.Direct3D10.Buffer;
using Device = SharpDX.Direct3D10.Device;
using DriverType = SharpDX.Direct3D10.DriverType;

namespace DemoFramework
{
    public class Demo : System.IDisposable
    {
        public RenderForm Form
        {
            get;
            private set;
        }

        Device _device;
        public Device Device
        {
            get { return _device; }
        }
        Device.OutputMergerStage outputMerger;
        Device.InputAssemblerStage inputAssembler;

        SwapChain _swapChain;
        public SwapChain SwapChain
        {
            get { return _swapChain; }
        }

        public float AspectRatio
        {
            get { return (float)Width / (float)Height; }
        }

        Texture2D gBufferLight;
        Texture2D gBufferNormal;
        Texture2D gBufferDiffuse;
        Texture2D depthTexture;
        Texture2D lightDepthTexture;

        public RenderTargetView RenderView { get; private set; }
        public DepthStencilView DepthView { get; private set; }
        public DepthStencilView LightDepthView { get; private set; }
        public RenderTargetView GBufferNormalView { get; private set; }
        public RenderTargetView GBufferDiffuseView { get; private set; }
        public RenderTargetView GBufferLightView { get; private set; }
        RenderTargetView[] gBufferViews;
        DepthStencilState depthStencilState;
        DepthStencilState lightDepthStencilState;
        bool shadowsEnabled = false;
        public RenderTargetView[] renderViews = new RenderTargetView[1];
        
        VertexBufferBinding quadBinding;
        InputLayout quadBufferLayout;

        public Effect Effect { get; private set; }
        public Effect Effect2 { get; private set; }
        public EffectPass ShadowGenPass { get; private set; }
        public EffectPass GBufferGenPass { get; private set; }
        public EffectPass GBufferRenderPass { get; private set; }
        
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
        protected float FieldOfView { get; set; }

        ShaderSceneConstants sceneConstants = new ShaderSceneConstants();
        Buffer sceneConstantsBuffer;

        protected InfoText Info { get; set; }

        protected Color4 Ambient { get; set; }
        protected MeshFactory MeshFactory { get; private set; }

        protected Input Input { get; private set; }
        protected FreeLook Freelook { get; set; }

        Clock clock = new Clock();
        float frameAccumulator;
        int frameCount;

        public float FrameDelta { get; private set; }
        public float FramesPerSecond { get; private set; }

        public PhysicsContext PhysicsContext { get; set; }

        RigidBody pickedBody;
        bool use6Dof = false;
        protected TypedConstraint pickConstraint;
        float oldPickingDist;

        [StructLayout(LayoutKind.Sequential)]
        struct ShaderSceneConstants
        {
            public Matrix View;
            public Matrix Projection;
            public Matrix ViewInverse;
            public Matrix LightViewProjection;
            public Vector4 LightPosition;
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

        protected virtual void OnInitializeDevice()
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
            outputMerger = Device.OutputMerger;
            inputAssembler = Device.InputAssembler;

            Factory factory = SwapChain.GetParent<Factory>();
            factory.MakeWindowAssociation(Form.Handle, WindowAssociationFlags.None);
        }

        void DisposeBuffers()
        {
            if (RenderView != null)
                RenderView.Release();

            if (GBufferLightView != null)
                GBufferLightView.Release();

            if (GBufferNormalView != null)
                GBufferNormalView.Release();

            if (GBufferDiffuseView != null)
                GBufferDiffuseView.Release();

            if (gBufferLight != null)
                gBufferLight.Release();
            
            if (gBufferNormal != null)
                gBufferNormal.Release();
            
            if (gBufferDiffuse != null)
                gBufferDiffuse.Release();

            if (depthTexture != null)
                depthTexture.Release();

            if (lightDepthTexture != null)
                lightDepthTexture.Release();

            if (lightBufferRes != null)
                lightBufferRes.Release();

            if (normalBufferRes != null)
                normalBufferRes.Release();

            if (diffuseBufferRes != null)
                diffuseBufferRes.Release();

            if (depthRes != null)
                depthRes.Release();

            if (lightDepthRes != null)
                lightDepthRes.Release();
        }

        void CreateBuffers()
        {
            DisposeBuffers();

            // New RenderTargetView from the backbuffer
            using (var bb = Texture2D.FromSwapChain<Texture2D>(_swapChain, 0))
            {
                RenderView = new RenderTargetView(Device, bb);
                renderViews[0] = RenderView;
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

            gBufferLight = new Texture2D(Device, gBufferDesc);
            GBufferLightView = new RenderTargetView(Device, gBufferLight);

            gBufferNormal = new Texture2D(Device, gBufferDesc);
            GBufferNormalView = new RenderTargetView(Device, gBufferNormal);

            gBufferDiffuse = new Texture2D(Device, gBufferDesc);
            GBufferDiffuseView = new RenderTargetView(Device, gBufferDiffuse);

            gBufferViews = new RenderTargetView[] { GBufferLightView, GBufferNormalView, GBufferDiffuseView };

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
            lightBufferRes = new ShaderResourceView(Device, gBufferLight, gBufferResourceDesc);
            normalBufferRes = new ShaderResourceView(Device, gBufferNormal, gBufferResourceDesc);
            diffuseBufferRes = new ShaderResourceView(Device, gBufferDiffuse, gBufferResourceDesc);


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

            depthTexture = new Texture2D(Device, depthDesc);
            DepthView = new DepthStencilView(Device, depthTexture, depthViewDesc);
            depthRes = new ShaderResourceView(Device, depthTexture, resourceDesc);

            lightDepthTexture = new Texture2D(Device, depthDesc);
            LightDepthView = new DepthStencilView(Device, lightDepthTexture, depthViewDesc);
            lightDepthRes = new ShaderResourceView(Device, lightDepthTexture, resourceDesc);

            Effect2.GetVariableByName("lightBuffer").AsShaderResource().SetResource(lightBufferRes);
            Effect2.GetVariableByName("normalBuffer").AsShaderResource().SetResource(normalBufferRes);
            Effect2.GetVariableByName("diffuseBuffer").AsShaderResource().SetResource(diffuseBufferRes);
            Effect2.GetVariableByName("depthMap").AsShaderResource().SetResource(depthRes);
            Effect2.GetVariableByName("lightDepthMap").AsShaderResource().SetResource(lightDepthRes);

            Device.Rasterizer.SetViewports(new Viewport(0, 0, Width, Height));
        }

        void Initialize()
        {
            // shader.fx

            ShaderFlags shaderFlags = ShaderFlags.None;
            //ShaderFlags shaderFlags = ShaderFlags.Debug | ShaderFlags.SkipOptimization;
            ShaderBytecode shaderByteCode = ShaderBytecode.CompileFromFile(Application.StartupPath + "\\shader.fx", "fx_4_0", shaderFlags, EffectFlags.None);

            Effect = new Effect(Device, shaderByteCode);
            EffectTechnique technique = Effect.GetTechniqueByIndex(0);
            ShadowGenPass = technique.GetPassByIndex(0);
            GBufferGenPass = technique.GetPassByIndex(1);

            BufferDescription sceneConstantsDesc = new BufferDescription()
            {
                SizeInBytes = Marshal.SizeOf(typeof(ShaderSceneConstants)),
                Usage = ResourceUsage.Dynamic,
                BindFlags = BindFlags.ConstantBuffer,
                CpuAccessFlags = CpuAccessFlags.Write,
                OptionFlags = ResourceOptionFlags.None
            };

            sceneConstantsBuffer = new Buffer(Device, sceneConstantsDesc);
            EffectConstantBuffer effectConstantBuffer = Effect.GetConstantBufferByName("scene");
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
            Device.Rasterizer.State = new RasterizerState(Device, desc);

            DepthStencilStateDescription depthDesc = new DepthStencilStateDescription()
            {
                IsDepthEnabled = true,
                IsStencilEnabled = false,
                DepthWriteMask = DepthWriteMask.All,
                DepthComparison = Comparison.Less
            };
            depthStencilState = new DepthStencilState(Device, depthDesc);

            DepthStencilStateDescription lightDepthStateDesc = new DepthStencilStateDescription()
            {
                IsDepthEnabled = true,
                IsStencilEnabled = false,
                DepthWriteMask = DepthWriteMask.All,
                DepthComparison = Comparison.Less
            };
            lightDepthStencilState = new DepthStencilState(Device, lightDepthStateDesc);


            // grender.fx

            shaderByteCode = ShaderBytecode.CompileFromFile(Application.StartupPath + "\\grender.fx", "fx_4_0", shaderFlags, EffectFlags.None);

            Effect2 = new Effect(Device, shaderByteCode);
            technique = Effect2.GetTechniqueByIndex(0);
            GBufferRenderPass = technique.GetPassByIndex(0);

            Buffer quad = MeshFactory.CreateScreenQuad(Device);
            quadBinding = new VertexBufferBinding(quad, 20, 0);
            Matrix quadProjection = Matrix.OrthoLH(1, 1, 0.1f, 1.0f);
            Effect2.GetVariableByName("ViewProjection").AsMatrix().SetMatrix(quadProjection);

            InputElement[] elements = new InputElement[]
            {
                new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0, InputClassification.PerVertexData, 0),
                new InputElement("TEXCOORD", 0, Format.R32G32_Float, 12, 0, InputClassification.PerVertexData, 0),
            };
            quadBufferLayout = new InputLayout(Device, GBufferRenderPass.Description.Signature, elements);


            Info = new InfoText(Device);
            MeshFactory = new MeshFactory(this);

            OnInitialize();
            CreateBuffers();
            SetSceneConstants();
        }

        protected void SetSceneConstants()
        {
            sceneConstants.View = Freelook.View;
            sceneConstants.Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, NearPlane, FarPlane);
            sceneConstants.ViewInverse = Matrix.Invert(Freelook.View);

            Vector3 light = new Vector3(20, 30, 10);
            sceneConstants.LightPosition = new Vector4(light, 1);
            Texture2DDescription depthBuffer = lightDepthTexture.Description;
            Matrix lightView = Matrix.LookAtLH(light, Vector3.Zero, Freelook.Up);
            Matrix lightProjection = Matrix.OrthoLH(depthBuffer.Width / 8, depthBuffer.Height / 8, NearPlane, FarPlane);
            sceneConstants.LightViewProjection = lightView * lightProjection;

            using (var data = sceneConstantsBuffer.Map(MapMode.WriteDiscard))
            {
                Marshal.StructureToPtr(sceneConstants, data.DataPointer, false);
                sceneConstantsBuffer.Unmap();
            }

            Effect2.GetVariableByName("InverseProjection").AsMatrix().SetMatrix(Matrix.Invert(sceneConstants.View * sceneConstants.Projection));
            Effect2.GetVariableByName("InverseView").AsMatrix().SetMatrix(sceneConstants.ViewInverse);
            Effect2.GetVariableByName("LightInverseViewProjection").AsMatrix().SetMatrix(Matrix.Invert(sceneConstants.LightViewProjection));
            Effect2.GetVariableByName("LightPosition").AsVector().Set(sceneConstants.LightPosition);
        }

        void Render()
        {
            frameAccumulator += FrameDelta;
            ++frameCount;
            if (frameAccumulator >= 1.0f)
            {
                FramesPerSecond = frameCount / frameAccumulator;

                frameAccumulator = 0.0f;
                frameCount = 0;
            }

            // Clear targets
            Device.ClearDepthStencilView(DepthView, DepthStencilClearFlags.Depth, 1.0f, 0);
            Device.ClearRenderTargetView(RenderView, Ambient);
            Device.ClearRenderTargetView(GBufferLightView, Ambient);
            Device.ClearRenderTargetView(GBufferNormalView, Ambient);
            Device.ClearRenderTargetView(GBufferDiffuseView, Ambient);

            MeshFactory.InitInstancedRender(PhysicsContext.World.CollisionObjectArray);

            // Depth map pass
            if (shadowsEnabled)
            {
                Device.ClearDepthStencilView(LightDepthView, DepthStencilClearFlags.Depth, 1.0f, 0);
                outputMerger.SetDepthStencilState(lightDepthStencilState, 0);
                outputMerger.SetRenderTargets(0, null, LightDepthView);
                ShadowGenPass.Apply();
                OnRender();
                Effect.GetVariableByName("lightDepthMap").AsShaderResource().SetResource(lightDepthRes);
            }

            // Render pass
            outputMerger.SetDepthStencilState(depthStencilState, 0);
            outputMerger.SetRenderTargets(3, gBufferViews, DepthView);
            GBufferGenPass.Apply();
            OnRender();

            
            // G-buffer render pass
            outputMerger.SetDepthStencilState(null, 0);
            outputMerger.SetRenderTargets(1, renderViews, null);
            GBufferRenderPass.Apply();

            inputAssembler.SetVertexBuffers(0, quadBinding);
            inputAssembler.SetPrimitiveTopology(PrimitiveTopology.TriangleStrip);
            inputAssembler.SetInputLayout(quadBufferLayout);
            Device.Draw(4, 0);

            Info.OnRender(FramesPerSecond);

            SwapChain.Present(0, PresentFlags.None);
        }

        /// <summary>
        /// Updates sample state.
        /// </summary>
        private void Update()
        {
            FrameDelta = clock.Update();
            OnUpdate();
        }

        /// <summary>
        /// Runs the demo.
        /// </summary>
        public void Run()
        {
            bool isFormClosed = false;
            bool formIsResizing = false;

            Form = new RenderForm();
            /*
            currentFormWindowState = Form.WindowState;
            Form.Resize += (o, args) =>
            {
                if (Form.WindowState != currentFormWindowState)
                {
                    if (togglingFullScreen == false)
                        HandleResize(o, args);
                }

                currentFormWindowState = Form.WindowState;
            };
            */
            Form.ResizeBegin += (o, args) => { formIsResizing = true; };
            Form.ResizeEnd += (o, args) =>
            {
                Width = Form.ClientSize.Width;
                Height = Form.ClientSize.Height;

                RenderView.Dispose();
                DepthView.Dispose();
                _swapChain.ResizeBuffers(_swapChain.Description.BufferCount, Width, Height, _swapChain.Description.ModeDescription.Format, (int)_swapChain.Description.Flags);

                CreateBuffers();

                SetSceneConstants();
                formIsResizing = false;
            };

            //Form.Closed += (o, args) => { isFormClosed = true; };

            Input = new Input(Form);

            Width = 1024;
            Height = 768;
            FullScreenWidth = Screen.PrimaryScreen.Bounds.Width;
            FullScreenHeight = Screen.PrimaryScreen.Bounds.Height;
            NearPlane = 1.0f;
            FarPlane = 200.0f;

            FieldOfView = (float)Math.PI / 4;
            Freelook = new FreeLook(Input);
            Ambient = (Color4)Color.Gray;

            try
            {
                OnInitializeDevice();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "Could not create DirectX 10 device.");
                return;
            }

            Initialize();

            clock.Start();
            RenderLoop.Run(Form, () =>
            {
                OnHandleInput();
                Update();
                Render();
                Input.ClearKeyCache();
            });
        }

        protected virtual void OnInitialize() { }

        protected virtual void OnRender()
        {
            MeshFactory.RenderInstanced();
        }

        protected virtual void OnUpdate()
        {
            if (Freelook.Update(FrameDelta))
                SetSceneConstants();
            PhysicsContext.Update(FrameDelta);
        }

        protected virtual void OnHandleInput()
        {
            if (Input.KeysPressed.Count != 0)
            {
                Keys key = Input.KeysPressed[0];
                switch (key)
                {
                    case Keys.Escape:
                    case Keys.Q:
                        Form.Close();
                        return;
                    case Keys.F3:
                        //IsDebugDrawEnabled = !IsDebugDrawEnabled;
                        break;
                    case Keys.F11:
                        //ToggleFullScreen();
                        break;
                    case Keys.G:
                        shadowsEnabled = !shadowsEnabled;
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

                        CollisionWorld.ClosestRayResultCallback rayCallback = new CollisionWorld.ClosestRayResultCallback(rayFrom, rayTo);
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

                                    if (use6Dof)
                                    {
                                        Generic6DofConstraint dof6 = new Generic6DofConstraint(body, Matrix.Translation(localPivot), false);
                                        dof6.LinearLowerLimit = Vector3.Zero;
                                        dof6.LinearUpperLimit = Vector3.Zero;
                                        dof6.AngularLowerLimit = Vector3.Zero;
                                        dof6.AngularUpperLimit = Vector3.Zero;

                                        PhysicsContext.World.AddConstraint(dof6);
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
                                        Point2PointConstraint p2p = new Point2PointConstraint(body, localPivot);
                                        PhysicsContext.World.AddConstraint(p2p);
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
                                    use6Dof = !use6Dof;

                                    oldPickingDist = (pickPos - rayFrom).Length();
                                }
                            }
                        }
                    }
                }
            }
            else if (Input.MouseReleased == MouseButtons.Right)
            {
                if (pickConstraint != null && PhysicsContext.World != null)
                {
                    PhysicsContext.World.RemoveConstraint(pickConstraint);
                    pickConstraint.Dispose();
                    pickConstraint = null;
                    pickedBody.ForceActivationState(ActivationState.ActiveTag);
                    pickedBody.DeactivationTime = 0;
                    pickedBody = null;
                }
            }

            // Mouse movement
            if (Input.MouseDown == MouseButtons.Right)
            {
                if (pickConstraint != null)
                {
                    Vector3 newRayTo = GetRayTo(Input.MousePoint, Freelook.Eye, Freelook.Target, FieldOfView);

                    if (pickConstraint.ConstraintType == TypedConstraintType.D6)
                    {
                        Generic6DofConstraint pickCon = (Generic6DofConstraint)pickConstraint;

                        //keep it at the same picking distance
                        Vector3 rayFrom = Freelook.Eye;
                        Vector3 scale;
                        Quaternion rotation;
                        Vector3 oldPivotInB;
                        pickCon.FrameOffsetA.Decompose(out scale, out rotation, out oldPivotInB);

                        Vector3 dir = newRayTo - rayFrom;
                        dir.Normalize();
                        dir *= oldPickingDist;
                        Vector3 newPivotB = rayFrom + dir;

                        Matrix tempFrameOffsetA = pickCon.FrameOffsetA;
                        Vector4 transRow = tempFrameOffsetA.Row4;
                        transRow.X = newPivotB.X;
                        transRow.Y = newPivotB.Y;
                        transRow.Z = newPivotB.Z;
                        tempFrameOffsetA.Row4 = transRow;
                        pickCon.FrameOffsetA = tempFrameOffsetA;
                    }
                    else
                    {
                        Point2PointConstraint pickCon = (Point2PointConstraint)pickConstraint;

                        //keep it at the same picking distance
                        Vector3 rayFrom = Freelook.Eye;
                        Vector3 oldPivotInB = pickCon.PivotInB;

                        Vector3 dir = newRayTo - rayFrom;
                        dir.Normalize();
                        dir *= oldPickingDist;
                        Vector3 newPivotB = rayFrom + dir;

                        pickCon.PivotInB = newPivotB;
                    }
                }
            }
        }

        protected Vector3 GetRayTo(Point point, Vector3 eye, Vector3 target, float fov)
        {
            float aspect;

            Vector3 rayFrom = eye;
            Vector3 rayForward = target - eye;
            rayForward.Normalize();
            float farPlane = 10000.0f;
            rayForward *= farPlane;

            Vector3 vertical = Vector3.UnitY;

            Vector3 hor = Vector3.Cross(rayForward, vertical);
            hor.Normalize();
            vertical = Vector3.Cross(hor, rayForward);
            vertical.Normalize();

            float tanFov = (float)Math.Tan(fov / 2);
            hor *= 2.0f * farPlane * tanFov;
            vertical *= 2.0f * farPlane * tanFov;

            if (Form.ClientSize.Width > Form.ClientSize.Height)
            {
                aspect = (float)Form.ClientSize.Width / (float)Form.ClientSize.Height;
                hor *= aspect;
            }
            else
            {
                aspect = (float)Form.ClientSize.Height / (float)Form.ClientSize.Width;
                vertical *= aspect;
            }

            Vector3 rayToCenter = rayFrom + rayForward;
            Vector3 dHor = hor / (float)Form.ClientSize.Width;
            Vector3 dVert = vertical / (float)Form.ClientSize.Height;

            Vector3 rayTo = rayToCenter - 0.5f * hor + 0.5f * vertical;
            rayTo += (Form.ClientSize.Width - point.X) * dHor;
            rayTo -= point.Y * dVert;
            return rayTo;
        }
    }
}
