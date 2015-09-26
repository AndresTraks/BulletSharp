using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using BulletSharp;
using BulletSharp.SoftBody;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.Windows;
using Device = SlimDX.Direct3D9.Device;
using Material = SlimDX.Direct3D9.Material;
using Matrix = SlimDX.Matrix;
using Vector3 = SlimDX.Vector3;

namespace DemoFramework.SlimDX
{
    public class SlimDXGraphics : Graphics
    {
        public Device Device
        {
            get { return Context9.Device; }
        }

        /// <summary>
        /// Represents a Direct3D9 Context, only valid after calling InitializeDevice(DeviceSettings9)
        /// </summary>
        public DeviceContext9 Context9 { get; private set; }

        MeshFactory _meshFactory;
        protected MeshFactory GetMeshFactory()
        {
            return _meshFactory;
        }

        protected int Width { get; set; }
        protected int Height { get; set; }
        protected int FullScreenWidth { get; set; }
        protected int FullScreenHeight { get; set; }
        protected float NearPlane { get; set; }

        public override float AspectRatio
        {
            get
            {
                return (float)Context9.PresentParameters.BackBufferWidth / (float)Context9.PresentParameters.BackBufferHeight;
            }
        }

        public override float FarPlane
        {
            set
            {
                base.FarPlane = value;
                if (Context9 != null && Demo.Freelook != null)
                {
                    UpdateView();
                }
            }
        }

        protected InfoText Info { get; set; }

        protected int Ambient { get; set; }
        protected Material ActiveMaterial;
        protected Material PassiveMaterial;
        protected Material GroundMaterial;
        protected Material SoftBodyMaterial;
        Light light;

        bool isFormClosed = false;
        bool formIsResizing = false;
        bool deviceLost = false;
        System.IDisposable apiContext;
        FormWindowState currentFormWindowState;
        FormWindowState windowedFormWindowState;
        FormBorderStyle windowedFormBorderStyle;
        bool togglingFullScreen = false;

        public override IDebugDraw GetPhysicsDebugDrawer()
        {
            return new PhysicsDebugDraw(Device);
        }

        public override bool IsFullScreen
        {
            get
            {
                return !Context9.PresentParameters.Windowed;
            }
            set
            {
                if (Context9 == null)
                    return;

                if (value == !Context9.PresentParameters.Windowed)
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
        }

        public SlimDXGraphics(Demo demo)
            : base(demo)
        {
            Form = new RenderForm();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                apiContext.Dispose();
                if (Form.IsDisposed == false)
                    Form.Dispose();
                Info.Dispose();
                _meshFactory.Dispose();
            }
            base.Dispose(disposing);
        }

        /// <summary>
        /// Performs object finalization.
        /// </summary>
        ~SlimDXGraphics()
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

        public override void Initialize()
        {
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


            Width = 1024;
            Height = 768;
            FullScreenWidth = Screen.PrimaryScreen.Bounds.Width;
            FullScreenHeight = Screen.PrimaryScreen.Bounds.Height;
            NearPlane = 1.0f;
            FarPlane = 200f;
            Ambient = Color.Gray.ToArgb();

            OnInitializeDevice();

            ActiveMaterial = new Material();
            ActiveMaterial.Diffuse = Color.Orange;
            ActiveMaterial.Ambient = new Color4(Ambient);

            PassiveMaterial = new Material();
            PassiveMaterial.Diffuse = Color.Red;
            PassiveMaterial.Ambient = new Color4(Ambient);

            GroundMaterial = new Material();
            GroundMaterial.Diffuse = Color.Green;
            GroundMaterial.Ambient = new Color4(Ambient);

            SoftBodyMaterial = new Material();
            SoftBodyMaterial.Diffuse = Color.White;
            SoftBodyMaterial.Ambient = new Color4(Ambient);

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 70;
            light.Position = new Vector3(10, 25, 10);
            light.Diffuse = Color.LemonChiffon;
            light.Attenuation0 = 1.0f;

            Info = new InfoText(Device);
            _meshFactory = new MeshFactory(this);
            MeshFactory = _meshFactory;
        }

        private void Render()
        {
            if (deviceLost)
            {
                // This should only become true if we're using D3D9, so we can assume the
                // D3D9 context is valid at this point.
                if (Device.TestCooperativeLevel() == global::SlimDX.Direct3D9.ResultCode.DeviceNotReset)
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

            try
            {
                Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
                Device.BeginScene();

                foreach (CollisionObject colObj in Demo.World.CollisionObjectArray)
                {
                    if (colObj is SoftBody)
                    {
                        if (Demo.IsDebugDrawEnabled)
                            continue;

                        Device.Material = SoftBodyMaterial;
                        Device.SetTransform(TransformState.World, Matrix.Identity);
                        _meshFactory.RenderSoftBody(colObj as SoftBody);
                    }
                    else
                    {
                        if ("Ground".Equals(colObj.UserObject))
                            Device.Material = GroundMaterial;
                        else if (colObj.ActivationState == ActivationState.ActiveTag)
                            Device.Material = ActiveMaterial;
                        else
                            Device.Material = PassiveMaterial;
                        _meshFactory.Render(colObj);
                    }
                }

                if (Demo.IsDebugDrawEnabled)
                    (Demo.World.DebugDrawer as PhysicsDebugDraw).DrawDebugWorld(Demo.World);
                Info.OnRender(Demo.FramesPerSecond);

                Device.EndScene();
                Device.Present();
            }
            catch (global::SlimDX.Direct3D9.Direct3D9Exception e)
            {
                if (e.ResultCode == global::SlimDX.Direct3D9.ResultCode.DeviceLost)
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

        public override void UpdateView()
        {
            FreeLook freelook = Demo.Freelook;
            Device.SetTransform(TransformState.View, Matrix.LookAtLH(MathHelper.Convert(freelook.Eye), MathHelper.Convert(freelook.Target), MathHelper.Convert(freelook.Up)));
        }

        /// <summary>
        /// Runs the game.
        /// </summary>
        public override void Run()
        {
            OnResetDevice();

            MessagePump.Run(Form, () =>
            {
                Demo.OnHandleInput();
                Demo.OnUpdate();

                if (isFormClosed)
                    return;

                if (!formIsResizing)
                    Render();
            });

            OnLostDevice();
        }

        protected void OnInitializeDevice()
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
                        return;
                    }
                }
            }

            GraphicsLibraryManager.LibraryStarted();
        }

        protected virtual void OnResetDevice()
        {
            Info.OnResetDevice();

            Matrix projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, NearPlane, FarPlane);
            Device.SetTransform(TransformState.Projection, projection);
            UpdateView();

            Device.SetRenderState(RenderState.Ambient, Ambient);
            Device.SetRenderState(RenderState.CullMode, CullingEnabled ? Cull.Counterclockwise : Cull.None);

            Device.SetLight(0, light);
            Device.EnableLight(0, true);

            _meshFactory.OnResetDevice();
        }

        protected virtual void OnLostDevice()
        {
            Info.OnLostDevice();
            _meshFactory.OnLostDevice();
        }

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

        public override void SetInfoText(string text)
        {
            Info.Text = text;
        }
    }
}
