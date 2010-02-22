using SlimDX.Direct3D9;
using SlimDX.Windows;
using System;
using System.Threading;
using System.Windows.Forms;

namespace DemoFramework
{
    public class Game : IDisposable
    {
        public RenderForm Form
        {
            get;
            private set;
        }

        public Device Device9
        {
            get { return Context9.Device; }
        }

        /// <summary>
        /// Represents a Direct3D9 Context, only valid after calling InitializeDevice(DeviceSettings9)
        /// </summary>
        public DeviceContext9 Context9 { get; private set; }

        /// <summary>
        /// Gets the number of seconds passed since the last frame.
        /// </summary>
        public float FrameDelta { get; private set; }

        public float FramesPerSecond { get; private set; }

        private readonly Clock clock = new Clock();
        private bool deviceLost = false;
        private float frameAccumulator;
        private int frameCount;
        private FormWindowState currentFormWindowState;
        private IDisposable apiContext;
        private int tempWindowWidth, tempWindowHeight;

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
            }
        }

                /// <summary>
        /// Performs object finalization.
        /// </summary>
        ~Game() {
            Dispose( false );
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
        private void Update() {
            FrameDelta = clock.Update();
            OnUpdate();
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

            OnInitialize();
            OnResourceLoad();

            clock.Start();
            MessagePump.Run(Form, () =>
            {
                Update();

                if (isFormClosed)
                    return;
                
                if (!formIsResizing)
                    Render();
            });

            OnResourceUnload();
        }

        /// <summary>
        /// In a derived class, implements logic to initialize the sample.
        /// </summary>
        protected virtual void OnInitialize() { }

        protected virtual void OnResourceLoad() { }

        protected virtual void OnResourceUnload() { }

        /// <summary>
        /// In a derived class, implements logic to update any relevant sample state.
        /// </summary>
        protected virtual void OnUpdate() { }

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
            if (Context9 != null)
            {
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
}
