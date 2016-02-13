using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using BulletSharp;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.Multimedia;
using SlimDX.RawInput;
using SlimDX.Windows;
using Device = SlimDX.Direct3D9.Device;

namespace DemoFramework
{
    public class Game : IDisposable
    {
        public RenderForm Form
        {
            get;
            private set;
        }

        public Device Device
        {
            get { return Context9.Device; }
        }

        /// <summary>
        /// Represents a Direct3D9 Context, only valid after calling InitializeDevice(DeviceSettings9)
        /// </summary>
        public DeviceContext9 Context9 { get; private set; }

        protected Input Input { get; private set; }
        protected GraphicObjectFactory MeshFactory { get; private set; }

        /// <summary>
        /// Gets the number of seconds passed since the last frame.
        /// </summary>
        public float FrameDelta { get; private set; }
        public float FramesPerSecond { get; private set; }


        protected int Width { get; set; }
        protected int Height { get; set; }
        protected int FullScreenWidth { get; set; }
        protected int FullScreenHeight { get; set; }

        protected float AspectRatio
        {
            get { return (float)Context9.PresentParameters.BackBufferWidth / (float)Context9.PresentParameters.BackBufferHeight; }
        }

        protected float NearPlane { get; set; }
        protected float FarPlane { get; set; }
        protected float FieldOfView { get; set; }
        protected FreeLook Freelook { get; set; }
        protected FpsDisplay Fps { get; set; }

        protected int Ambient { get; set; }
        protected Material ActiveMaterial;
        protected Material PassiveMaterial;
        protected Material GroundMaterial;

        readonly Clock clock = new Clock();
        bool deviceLost = false;
        float frameAccumulator;
        int frameCount;
        System.IDisposable apiContext;
        FormWindowState currentFormWindowState;
        FormWindowState windowedFormWindowState;
        FormBorderStyle windowedFormBorderStyle;
        bool togglingFullScreen = false;

        RigidBody pickedBody;
        bool use6Dof = false;
        protected TypedConstraint pickConstraint;
        float oldPickingDist;

        public PhysicsContext PhysicsContext { get; set; }

        DebugDrawModes debugDrawMode = DebugDrawModes.DrawWireframe;
        public DebugDrawModes DebugDrawMode
        {
            get
            {
                if (DebugDrawer == null) return debugDrawMode;

                return DebugDrawer.DebugMode;
            }
            set
            {
                if (DebugDrawer == null)
                    debugDrawMode = value;
                else
                    DebugDrawer.DebugMode = value;
            }
        }

        bool isDebugDrawEnabled = false;
        public bool IsDebugDrawEnabled
        {
            get
            {
                return isDebugDrawEnabled;
            }
            set
            {
                if (DebugDrawer == null)
                {
                    DebugDrawer = new PhysicsDebugDrawLineGathering(Device);
                    DebugDrawer.DebugMode = debugDrawMode;
                }
                isDebugDrawEnabled = value;
            }
        }

        public PhysicsDebugDraw DebugDrawer
        {
            get { return (PhysicsDebugDraw)PhysicsContext.World.DebugDrawer; }
            set { PhysicsContext.World.DebugDrawer = value; }
        }

        public void DebugDrawWorld()
        {
            if (IsDebugDrawEnabled)
                DebugDrawer.DrawDebugWorld(PhysicsContext.World);
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
                apiContext.Dispose();
                if (Form.IsDisposed == false)
                    Form.Dispose();
                Fps.Dispose();
                MeshFactory.Dispose();
                PhysicsContext.Dispose();
            }
        }

        /// <summary>
        /// Performs object finalization.
        /// </summary>
        ~Game()
        {
            Dispose(false);
        }

        /// <summary>
        /// Quits the sample.
        /// </summary>
        protected void Quit()
        {
            Form.Close();
        }

        /// <summary>
        /// Updates sample state.
        /// </summary>
        private void Update()
        {
            FrameDelta = clock.Update();
            OnUpdate();
        }

        protected Vector3 GetRayTo(Point point, Vector3 eye, Vector3 target, float fov)
        {
            float aspect;

            Vector3 rayFrom = eye;
            Vector3 rayForward = target - eye;
            rayForward.Normalize();
            float farPlane = 10000.0f;
            rayForward *= farPlane;

            Vector3 vertical = Freelook.Up;

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

        /// <summary>
        /// Renders the game.
        /// </summary>
        private void Render()
        {
            if (deviceLost)
            {
                // This should only become true if we're using D3D9, so we can assume the
                // D3D9 context is valid at this point.
                if (Device.TestCooperativeLevel() == SlimDX.Direct3D9.ResultCode.DeviceNotReset)
                {
                    Device.Reset(Context9.PresentParameters);
                    deviceLost = false;
                    OnResetDevice();
                }
                else
                {
                    Thread.Sleep(100);
                    return;
                }
            }

            frameAccumulator += FrameDelta;
            ++frameCount;
            if (frameAccumulator >= 1.0f)
            {
                FramesPerSecond = frameCount / frameAccumulator;

                frameAccumulator = 0.0f;
                frameCount = 0;
            }

            try
            {
                OnRender();
            }
            catch (SlimDX.Direct3D9.Direct3D9Exception e)
            {
                if (e.ResultCode == SlimDX.Direct3D9.ResultCode.DeviceLost)
                {
                    OnLostDevice();
                    deviceLost = true;
                }
                else
                {
                    throw;
                }
            }
        }

        /// <summary>
        /// Runs the game.
        /// </summary>
        public void Run()
        {
            bool isFormClosed = false;
            bool formIsResizing = false;

            Form = new RenderForm();

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

            Form.ResizeBegin += (o, args) => { formIsResizing = true; };
            Form.ResizeEnd += (o, args) =>
            {
                formIsResizing = false;
                HandleResize(o, args);
            };

            Form.Closed += (o, args) => { isFormClosed = true; };


            // initialize input
            SlimDX.RawInput.Device.RegisterDevice(UsagePage.Generic, UsageId.Keyboard, DeviceFlags.None);
            SlimDX.RawInput.Device.RegisterDevice(UsagePage.Generic, UsageId.Mouse, DeviceFlags.None);

            Input = new Input(Form);

            SlimDX.RawInput.Device.KeyboardInput += Input.Device_KeyboardInput;
            SlimDX.RawInput.Device.MouseInput += Input.Device_MouseInput;


            Width = 1024;
            Height = 768;
            FullScreenWidth = Screen.PrimaryScreen.Bounds.Width;
            FullScreenHeight = Screen.PrimaryScreen.Bounds.Height;
            NearPlane = 0.1f;
            FarPlane = 200f;
            FieldOfView = (float)Math.PI / 4;
            Freelook = new FreeLook(Input);
            Ambient = Color.Gray.ToArgb();

            OnInitializeDevice();

            Fps = new FpsDisplay(Device);
            MeshFactory = new GraphicObjectFactory(Device);

            OnInitialize();
            OnResetDevice();

            clock.Start();
            MessagePump.Run(Form, () =>
            {
                OnHandleInput();
                Update();
                Input.ClearKeyCache();

                if (isFormClosed)
                    return;

                if (!formIsResizing)
                    Render();
            });

            SlimDX.RawInput.Device.KeyboardInput -= Input.Device_KeyboardInput;
            SlimDX.RawInput.Device.MouseInput -= Input.Device_MouseInput;

            OnLostDevice();
        }

        protected virtual void OnInitializeDevice()
        {
            Form.ClientSize = new Size(Width, Height);

            DeviceSettings9 settings = new DeviceSettings9();
            settings.CreationFlags = CreateFlags.HardwareVertexProcessing;
            settings.Windowed = true;
            settings.MultisampleType = MultisampleType.FourSamples;
            try
            {
                InitializeDevice(settings);
            }
            catch
            {
                // Disable 4xAA if not supported
                settings.MultisampleType = MultisampleType.None;
                try
                {
                    InitializeDevice(settings);
                }
                catch
                {
                    settings.CreationFlags = CreateFlags.SoftwareVertexProcessing;
                    try
                    {
                        InitializeDevice(settings);
                    }
                    catch
                    {
                        MessageBox.Show("Could not initialize DirectX device!");
                    }
                }
            }
        }

        protected virtual void OnInitialize()
        {
            ActiveMaterial = new Material();
            ActiveMaterial.Diffuse = Color.Orange;
            ActiveMaterial.Ambient = new Color4(Ambient);

            PassiveMaterial = new Material();
            PassiveMaterial.Diffuse = Color.Red;
            PassiveMaterial.Ambient = new Color4(Ambient);

            GroundMaterial = new Material();
            GroundMaterial.Diffuse = Color.Green;
            GroundMaterial.Ambient = new Color4(Ambient);
        }

        protected virtual void OnResetDevice()
        {
            Fps.OnResetDevice();

            Matrix projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, NearPlane, FarPlane);
            Device.SetTransform(TransformState.Projection, projection);
            Device.SetTransform(TransformState.View, Freelook.View);

            Device.SetRenderState(RenderState.Ambient, Ambient);

            MeshFactory.OnResetDevice();
        }

        protected virtual void OnLostDevice()
        {
            Fps.OnLostDevice();
            MeshFactory.OnLostDevice();
        }

        /// <summary>
        /// Implements logic to update any relevant sample state.
        /// </summary>
        protected virtual void OnUpdate()
        {
            if (Freelook.Update(FrameDelta))
                Device.SetTransform(TransformState.View, Freelook.View);
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
                        Quit();
                        return;
                    case Keys.F3:
                        IsDebugDrawEnabled = !IsDebugDrawEnabled;
                        break;
                    case Keys.F11:
                        ToggleFullScreen();
                        break;
                    case Keys.Space:
                        PhysicsContext.ShootBox(Freelook.Eye, GetRayTo(Input.MousePoint, Freelook.Eye, Freelook.Target, FieldOfView));
                        break;
                }
            }

            if (Input.MousePressed != MouseButtonFlags.None)
            {
                Vector3 rayTo = GetRayTo(Input.MousePoint, Freelook.Eye, Freelook.Target, FieldOfView);

                if (Input.MousePressed == MouseButtonFlags.RightDown)
                {
                    if (PhysicsContext.World != null)
                    {
                        Vector3 rayFrom = Freelook.Eye;

                        ClosestRayResultCallback rayCallback = new ClosestRayResultCallback(ref rayFrom, ref rayTo);
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
                else if (Input.MousePressed == MouseButtonFlags.RightUp)
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
            }

            // Mouse movement
            if (Input.MouseDown == MouseButtonFlags.RightDown)
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
                        pickCon.FrameOffsetA = tempFrameOffsetA;
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

        /// <summary>
        /// In a derived class, implements logic to render the sample.
        /// </summary>
        protected virtual void OnRender() { }

        /// <summary>
        /// Initializes a <see cref="DeviceContext9">Direct3D9 device context</see> according to the specified settings.
        /// The base class retains ownership of the context and will dispose of it when appropriate.
        /// </summary>
        /// <param name="settings">The settings.</param>
        /// <returns>The initialized device context.</returns>
        protected void InitializeDevice(DeviceSettings9 settings)
        {
            var result = new DeviceContext9(Form, settings);
            apiContext = result;
            Context9 = result;
        }

        private void HandleResize(object sender, EventArgs e)
        {
            if (Form.WindowState == FormWindowState.Minimized)
                return;

            OnLostDevice();

            if (Context9 != null)
            {
                Context9.PresentParameters.BackBufferWidth = Form.ClientSize.Width;
                Context9.PresentParameters.BackBufferHeight = Form.ClientSize.Height;

                Device.Reset(Context9.PresentParameters);

            }
            //else if( Context10 != null )
            //{
            //    Context10.SwapChain.ResizeBuffers( 1, WindowWidth, WindowHeight, Context10.SwapChain.Description.ModeDescription.Format, Context10.SwapChain.Description.Flags );
            //}

            OnResetDevice();
        }

        public void ToggleFullScreen()
        {
            if (Context9 == null)
                return;

            togglingFullScreen = true;

            OnLostDevice();

            if (Context9.PresentParameters.Windowed)
            {
                windowedFormWindowState = Form.WindowState;
                windowedFormBorderStyle = Form.FormBorderStyle;

                Width = Form.ClientSize.Width;
                Height = Form.ClientSize.Height;

                // Only normal window can be used in full screen.
                if (Form.WindowState != FormWindowState.Normal)
                    Form.WindowState = FormWindowState.Normal;

                Context9.PresentParameters.BackBufferWidth = FullScreenWidth;
                Context9.PresentParameters.BackBufferHeight = FullScreenHeight;
                Form.FormBorderStyle = FormBorderStyle.None;

                Context9.PresentParameters.Windowed = false;
            }
            else
            {
                Context9.PresentParameters.BackBufferWidth = Width;
                Context9.PresentParameters.BackBufferHeight = Height;
                Form.FormBorderStyle = windowedFormBorderStyle;
                Form.WindowState = windowedFormWindowState;
                if (Form.WindowState == FormWindowState.Normal)
                    Form.ClientSize = new System.Drawing.Size(Width, Height);

                Context9.PresentParameters.Windowed = true;
            }

            Device.Reset(Context9.PresentParameters);
            OnResetDevice();

            togglingFullScreen = false;
        }

        protected void RenderWithMaterial(CollisionObject body)
        {
            if ("Ground".Equals(body.UserObject))
                Device.Material = GroundMaterial;
            else if (body.ActivationState == ActivationState.ActiveTag)
                Device.Material = ActiveMaterial;
            else
                Device.Material = PassiveMaterial;

            MeshFactory.Render(body.CollisionShape);
        }
    }
}
