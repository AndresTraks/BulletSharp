using System;
using System.Drawing;
using System.Reflection;
using System.Threading;
using System.Windows.Forms;
using BulletSharp;
using SlimDX;
using SlimDX.Multimedia;
using SlimDX.RawInput;
using SlimDX.Windows;

namespace DemoFramework
{
    public class Game : System.IDisposable
    {
        public RenderForm Form
        {
            get;
            private set;
        }

        public SlimDX.Direct3D9.Device Device9
        {
            get { return Context9.Device; }
        }

        /// <summary>
        /// Represents a Direct3D9 Context, only valid after calling InitializeDevice(DeviceSettings9)
        /// </summary>
        public DeviceContext9 Context9 { get; private set; }

        public Input Input { get; private set; }

        /// <summary>
        /// Gets the number of seconds passed since the last frame.
        /// </summary>
        public float FrameDelta { get; private set; }
        public float FramesPerSecond { get; private set; }

        public float AspectRatio
        {
            get { return (float)Form.ClientSize.Width / (float)Form.ClientSize.Height; }
        }

        protected float FieldOfView;
        protected Matrix Projection;
        protected FreeLook Freelook;
        protected FpsDisplay Fps;


        readonly Clock clock = new Clock();
        bool deviceLost = false;
        float frameAccumulator;
        int frameCount;
        System.IDisposable apiContext;
        FormWindowState currentFormWindowState;
        int tempWindowWidth, tempWindowHeight;

        RigidBody pickedBody;
        bool use6Dof = false;
        TypedConstraint pickConstraint;
        float oldPickingDist;


        public bool TestLibraries()
        {
            try
            {
                Assembly.Load("SlimDX, Version=2.0.10.43, Culture=neutral, PublicKeyToken=b1b0c32fd1ffe4f9");
            }
            catch
            {
                MessageBox.Show("SlimDX(v2.0.10.43) not installed." +
                    "Please download it from http://slimdx.org.", "Error!");
                return false;
            }

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
                Form.Dispose();
                Fps.Dispose();
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

        protected void InputUpdate(Vector3 eye, Vector3 target, PhysicsContext physics)
        {
            if (Input.KeysPressed.Contains(Keys.Escape))
            {
                Quit();
                return;
            }

            if (Input.KeysPressed.Contains(Keys.F11))
                ToggleFullScreen();

            if (Input.KeysPressed.Contains(Keys.Space))
                physics.ShootBox(Freelook.Eye, GetRayTo(Input.MousePoint, Freelook.Eye, Freelook.Target, FieldOfView));


            if (Input.MousePressed != MouseButtonFlags.None)
            {
                Vector3 rayTo = GetRayTo(Input.MousePoint, eye, target, FieldOfView);

                if (Input.MousePressed == MouseButtonFlags.RightDown)
                {
                    if (physics.World != null)
                    {
                        Vector3 rayFrom = eye;

                        CollisionWorld.ClosestRayResultCallback rayCallback = new CollisionWorld.ClosestRayResultCallback(rayFrom, rayTo);
                        physics.World.RayTest(rayFrom, rayTo, rayCallback);
                        if (rayCallback.HasHit)
                        {
                            RigidBody body = RigidBody.Upcast(rayCallback.CollisionObject);
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
                                        dof6.SetLinearLowerLimit(Vector3.Zero);
                                        dof6.SetLinearUpperLimit(Vector3.Zero);
                                        dof6.SetAngularLowerLimit(Vector3.Zero);
                                        dof6.SetAngularUpperLimit(Vector3.Zero);

                                        physics.World.AddConstraint(dof6);
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
                                        physics.World.AddConstraint(p2p);
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
                    if (pickConstraint != null && physics.World != null)
                    {
                        physics.World.RemoveConstraint(pickConstraint);
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
                    Vector3 newRayTo = GetRayTo(Input.MousePoint, eye, target, FieldOfView);

                    if (pickConstraint.ConstraintType == TypedConstraintType.D6)
                    {
                        Generic6DofConstraint pickCon = (Generic6DofConstraint)pickConstraint;

                        //keep it at the same picking distance
                        Vector3 rayFrom = eye;
                        Vector3 scale;
                        Quaternion rotation;
                        Vector3 oldPivotInB;
                        pickCon.FrameOffsetA.Decompose(out scale, out rotation, out oldPivotInB);

                        Vector3 dir = newRayTo - rayFrom;
                        dir.Normalize();
                        dir *= oldPickingDist;
                        Vector3 newPivotB = rayFrom + dir;

                        Matrix tempFrameOffsetA = pickCon.FrameOffsetA;
                        Vector4 transRow = tempFrameOffsetA.get_Rows(3);
                        transRow.X = newPivotB.X;
                        transRow.Y = newPivotB.Y;
                        transRow.Z = newPivotB.Z;
                        tempFrameOffsetA.set_Rows(3, transRow);
                        pickCon.FrameOffsetA = tempFrameOffsetA;
                    }
                    else
                    {
                        Point2PointConstraint pickCon = (Point2PointConstraint)pickConstraint;

                        //keep it at the same picking distance
                        Vector3 rayFrom = eye;
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

        Vector3 GetRayTo(Point point, Vector3 eye, Vector3 target, float fov)
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

        /// <summary>
        /// Renders the game.
        /// </summary>
        private void Render()
        {
            if (deviceLost)
            {
                // This should only become true if we're using D3D9, so we can assume the
                // D3D9 context is valid at this point.
                if (Device9.TestCooperativeLevel() == SlimDX.Direct3D9.ResultCode.DeviceNotReset)
                {
                    Device9.Reset(Context9.PresentParameters);
                    deviceLost = false;
                    OnResourceLoad();
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
                    OnResourceUnload();
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

            SlimDX.RawInput.Device.RegisterDevice(UsagePage.Generic, UsageId.Keyboard, DeviceFlags.None);
            SlimDX.RawInput.Device.RegisterDevice(UsagePage.Generic, UsageId.Mouse, DeviceFlags.None);

            Input = new Input(Form);

            SlimDX.RawInput.Device.KeyboardInput += Device_KeyboardInput;
            SlimDX.RawInput.Device.MouseInput += Device_MouseInput;

            OnInitializeDevice();

            FieldOfView = (float)Math.PI / 4;
            Freelook = new FreeLook();
            Fps = new FpsDisplay(Device9);

            OnInitialize();
            OnResourceLoad();

            clock.Start();
            MessagePump.Run(Form, () =>
            {
                Update();
                Input.ClearKeyCache();

                if (isFormClosed)
                    return;

                if (!formIsResizing)
                    Render();
            });

            OnResourceUnload();
        }

        private void Device_MouseInput(object sender, MouseInputEventArgs e)
        {
            Input.Device_MouseInput(e);
        }

        private void Device_KeyboardInput(object sender, KeyboardInputEventArgs e)
        {
            Input.Device_KeyboardInput(e);
        }

        protected virtual void OnInitializeDevice() { }

        protected virtual void OnInitialize() { }

        protected virtual void OnResourceLoad()
        {
            Fps.OnResourceLoad();
        }

        protected virtual void OnResourceUnload()
        {
            Fps.OnResourceUnload();
        }

        /// <summary>
        /// Implements logic to update any relevant sample state.
        /// </summary>
        protected virtual void OnUpdate()
        {
            Freelook.Update(FrameDelta, Input);
            Fps.OnResourceUnload();
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

            OnResourceUnload();

            if (Context9 != null)
            {
                Context9.PresentParameters.BackBufferWidth = Form.ClientSize.Width;
                Context9.PresentParameters.BackBufferHeight = Form.ClientSize.Height;

                Device9.Reset(Context9.PresentParameters);

            }
            //else if( Context10 != null )
            //{
            //    Context10.SwapChain.ResizeBuffers( 1, WindowWidth, WindowHeight, Context10.SwapChain.Description.ModeDescription.Format, Context10.SwapChain.Description.Flags );
            //}

            OnResourceLoad();
        }

        public void ToggleFullScreen()
        {
            if (Context9 == null)
                return;

            OnResourceUnload();

            if (Context9.PresentParameters.Windowed)
            {
                tempWindowWidth = Form.ClientSize.Width;
                tempWindowHeight = Form.ClientSize.Height;
                Context9.PresentParameters.BackBufferWidth = System.Windows.Forms.SystemInformation.PrimaryMonitorSize.Width;
                Context9.PresentParameters.BackBufferHeight = System.Windows.Forms.SystemInformation.PrimaryMonitorSize.Height;
                Form.ClientSize = new System.Drawing.Size(
                    Context9.PresentParameters.BackBufferWidth,
                    Context9.PresentParameters.BackBufferHeight
                    );
            }
            else
            {
                if (tempWindowWidth > 0 && tempWindowHeight > 0)
                {
                    Context9.PresentParameters.BackBufferWidth = tempWindowWidth;
                    Context9.PresentParameters.BackBufferHeight = tempWindowHeight;
                    Form.ClientSize = new System.Drawing.Size(
                        tempWindowWidth, tempWindowHeight);
                }
            }
            Context9.PresentParameters.Windowed = !Context9.PresentParameters.Windowed;
            Device9.Reset(Context9.PresentParameters);
            OnResourceLoad();
        }
    }
}
