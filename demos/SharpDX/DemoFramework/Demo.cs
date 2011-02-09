using System;
using System.Drawing;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using BulletSharp;
using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using SharpDX.Windows;
using Buffer = SharpDX.Direct3D10.Buffer;
using Device = SharpDX.Direct3D10.Device;

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

        SwapChain _swapChain;
        public SwapChain SwapChain
        {
            get { return _swapChain; }
        }

        public float AspectRatio
        {
            get { return (float)Width / (float)Height; }
        }

        public RenderTargetView RenderView { get; private set; }
        public DepthStencilView DepthStencilView { get; private set; }
        DepthStencilState depthStencilState;

        public Effect Effect { get; private set; }
        public EffectTechnique Technique { get; private set; }
        public EffectPass Pass { get; private set; }

        protected int Width { get; set; }
        protected int Height { get; set; }
        protected int FullScreenWidth { get; set; }
        protected int FullScreenHeight { get; set; }
        protected float NearPlane { get; set; }
        protected float FarPlane { get; set; }
        protected float FieldOfView { get; set; }

        ShaderObjectConstants objectConstants = new ShaderObjectConstants();
        ShaderSceneConstants sceneConstants = new ShaderSceneConstants();
        Buffer objectConstantsBuffer;
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
        struct ShaderObjectConstants
        {
            public Matrix World;
            public Matrix WorldInverseTranspose;
            public Color4 Color;
        }

        [StructLayout(LayoutKind.Sequential)]
        struct ShaderSceneConstants
        {
            public Matrix View;
            public Matrix Projection;
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
                //apiContext.Dispose();
                Form.Dispose();
            }
        }

        public bool TestLibraries()
        {
            /*
            try
            {
                Assembly.Load("SharpDX, Version=2.0.10.43, Culture=neutral, PublicKeyToken=b1b0c32fd1ffe4f9");
            }
            catch
            {
                MessageBox.Show("SharpDX(v2.0.10.43) not installed." +
                    "Please download it from http://code.google.com/p/sharpdx.", "Error!");
                return false;
            }
            */

            try
            {
                Assembly.Load("BulletSharp");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "BulletSharp Error!");
                return false;
            }

            return true;
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

            // Ignore all windows events
            Factory factory = SwapChain.GetParent<Factory>();
            factory.MakeWindowAssociation(Form.Handle, WindowAssociationFlags.None);

            CreateBuffers();
        }

        void CreateBuffers()
        {
            // New RenderTargetView from the backbuffer
            using (var bb = Texture2D.FromSwapChain<Texture2D>(_swapChain, 0))
                RenderView = new RenderTargetView(Device, bb);

            Texture2DDescription depthDesc = new Texture2DDescription()
            {
                ArraySize = 1,
                BindFlags = BindFlags.DepthStencil,
                CpuAccessFlags = CpuAccessFlags.None,
                Format = Format.D32_Float,
                Height = Height,
                Width = Width,
                MipLevels = 1,
                OptionFlags = ResourceOptionFlags.None,
                SampleDescription = new SampleDescription(1, 0),
                Usage = ResourceUsage.Default
            };
            Texture2D depthBuffer = new Texture2D(Device, depthDesc);
            DepthStencilView = new DepthStencilView(Device, depthBuffer);

            Device.OutputMerger.SetTargets(DepthStencilView, RenderView);
            Device.Rasterizer.SetViewports(new Viewport(0, 0, Width, Height));
        }

        void Initialize()
        {
            ShaderFlags shaderFlags = ShaderFlags.None;
            //ShaderFlags shaderFlags = ShaderFlags.Debug | ShaderFlags.SkipOptimization;
            ShaderBytecode shaderByteCode = ShaderBytecode.CompileFromFile("shader.fx", "fx_4_0", shaderFlags, EffectFlags.None);

            Effect = new Effect(Device, shaderByteCode);
            Technique = Effect.GetTechniqueByIndex(0);
            Pass = Technique.GetPassByIndex(0);

            BufferDescription objectConstantsDesc = new BufferDescription()
            {
                SizeInBytes = Marshal.SizeOf(typeof(ShaderObjectConstants)),
                Usage = ResourceUsage.Dynamic,
                BindFlags = BindFlags.ConstantBuffer,
                CpuAccessFlags = CpuAccessFlags.Write,
                OptionFlags = ResourceOptionFlags.None
            };

            objectConstantsBuffer = new Buffer(Device, objectConstantsDesc);
            EffectConstantBuffer effectConstantBuffer = Effect.GetConstantBufferByIndex(0);
            effectConstantBuffer.SetConstantBuffer(objectConstantsBuffer);

            BufferDescription sceneConstantsDesc = new BufferDescription()
            {
                SizeInBytes = Marshal.SizeOf(typeof(ShaderSceneConstants)),
                Usage = ResourceUsage.Dynamic,
                BindFlags = BindFlags.ConstantBuffer,
                CpuAccessFlags = CpuAccessFlags.Write,
                OptionFlags = ResourceOptionFlags.None
            };

            sceneConstantsBuffer = new Buffer(Device, sceneConstantsDesc);
            effectConstantBuffer = Effect.GetConstantBufferByIndex(1);
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

            OnInitialize();
            SetSceneBuffer();
        }

        protected void SetBuffer(Matrix world, Color color)
        {
            objectConstants.World = world;
            objectConstants.WorldInverseTranspose = Matrix.Transpose(Matrix.Invert(world));
            objectConstants.Color = (Color4)color;

            SharpDX.DataStream c = objectConstantsBuffer.Map(MapMode.WriteDiscard);
            Marshal.StructureToPtr(objectConstants, c.DataPointer, false);
            objectConstantsBuffer.Unmap();
        }

        protected void SetSceneBuffer()
        {
            sceneConstants.View = Freelook.View;
            sceneConstants.Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, NearPlane, FarPlane);

            SharpDX.DataStream c = sceneConstantsBuffer.Map(MapMode.WriteDiscard);
            Marshal.StructureToPtr(sceneConstants, c.DataPointer, false);
            sceneConstantsBuffer.Unmap();
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

            Device.OutputMerger.SetDepthStencilState(depthStencilState, 0);

            OnRender();

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
                DepthStencilView.Dispose();
                _swapChain.ResizeBuffers(_swapChain.Description.BufferCount, Width, Height, _swapChain.Description.ModeDescription.Format, (int)_swapChain.Description.Flags);

                CreateBuffers();

                SetSceneBuffer();
                formIsResizing = false;
            };

            //Form.Closed += (o, args) => { isFormClosed = true; };

            Input = new Input(Form);

            Width = 1024;
            Height = 768;
            FullScreenWidth = Screen.PrimaryScreen.Bounds.Width;
            FullScreenHeight = Screen.PrimaryScreen.Bounds.Height;
            NearPlane = 0.1f;
            FarPlane = 200.0f;

            FieldOfView = (float)Math.PI / 4;
            Freelook = new FreeLook();
            Ambient = (Color4)Color.Gray;

            OnInitializeDevice();

            Info = new InfoText(Device);
            MeshFactory = new MeshFactory(Device);

            Initialize();

            clock.Start();
            MessagePump.Run(Form, () =>
            {
                OnHandleInput();
                Update();
                Render();
                Input.ClearKeyCache();
            });
        }

        protected virtual void OnInitialize() { }

        protected virtual void OnRender() { }

        protected virtual void OnUpdate()
        {
            if (Freelook.Update(FrameDelta, Input))
                SetSceneBuffer();
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
                        Form.Close();
                        return;
                    case Keys.F3:
                        //IsDebugDrawEnabled = !IsDebugDrawEnabled;
                        break;
                    case Keys.F11:
                        //ToggleFullScreen();
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
