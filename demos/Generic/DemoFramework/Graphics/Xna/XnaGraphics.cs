using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using BulletSharp.SoftBody;
using Microsoft.Xna.Framework.Graphics;
using Color = Microsoft.Xna.Framework.Color;
using Matrix = Microsoft.Xna.Framework.Matrix;
using Vector3 = Microsoft.Xna.Framework.Vector3;

namespace DemoFramework.Xna
{
    public class XnaGraphics : DemoFramework.Graphics
    {
        public GraphicsDevice Device;

        MeshFactory meshFactory;
        protected MeshFactory GetMeshFactory()
        {
            return meshFactory;
        }

        protected int Width { get; set; }
        protected int Height { get; set; }
        protected int FullScreenWidth { get; set; }
        protected int FullScreenHeight { get; set; }
        protected float NearPlane { get; set; }
        protected float FarPlane { get; set; }

        protected InfoText Info { get; set; }

        protected int Ambient { get; set; }
        Vector3 activeColor = Color.Orange.ToVector3();
        Vector3 passiveColor = Color.DarkOrange.ToVector3();
        Vector3 groundColor = Color.Green.ToVector3();
        Vector3 softBodyColor = Color.White.ToVector3();
        //Light light;

        bool isFormClosed = false;
        bool formIsResizing = false;
        FormWindowState currentFormWindowState;

        public override IDebugDraw GetPhysicsDebugDrawer()
        {
            return new PhysicsDebugDraw(Device);
        }

        public XnaGraphics(Demo demo)
            : base(demo)
        {
            Form = new XnaForm(this);
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
                if (Form.IsDisposed == false)
                    Form.Dispose();
                Info.Dispose();
                meshFactory.Dispose();
            }
        }

        /// <summary>
        /// Performs object finalization.
        /// </summary>
        ~XnaGraphics()
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

            Width = 1024;
            Height = 768;
            FullScreenWidth = Screen.PrimaryScreen.Bounds.Width;
            FullScreenHeight = Screen.PrimaryScreen.Bounds.Height;
            NearPlane = 1.0f;
            FarPlane = 200f;
            //Ambient = Color.Gray.ToArgb();

            Info = new InfoText(Device);
        }

        public void InitializeDevice()
        {
            Form.ClientSize = new Size(Width, Height);

            /*
            light = new Light();
            light.Type = LightType.Point;
            light.Range = 70;
            light.Position = new Vector3(10, 25, 10);
            light.Diffuse = Color.LemonChiffon;
            light.Attenuation0 = 1.0f;
            */

            meshFactory = new MeshFactory(this);

            LibraryManager.LibraryStarted();
        }

        public void Render()
        {
            Device.Clear(ClearOptions.Target | ClearOptions.DepthBuffer, Microsoft.Xna.Framework.Color.LightGray, 1.0f, 0);

            meshFactory.InitInstancedRender(Demo.World.CollisionObjectArray);
            meshFactory.RenderInstanced();

            //if (Demo.IsDebugDrawEnabled)
            //    (Demo.World.DebugDrawer as PhysicsDebugDraw).DrawDebugWorld(Demo.World);
            //Info.OnRender(Demo.FramesPerSecond);
        }

        public override void UpdateView()
        {
            FreeLook freelook = Demo.Freelook;
            //Device.SetTransform(TransformState.View, Matrix.CreateLookAt(MathHelper.Convert(freelook.Eye), MathHelper.Convert(freelook.Target), MathHelper.Convert(freelook.Up)));
        }

        /// <summary>
        /// Runs the game.
        /// </summary>
        public override void Run()
        {
            Form.ShowDialog();
            /*
            while(true)
            {
                Demo.OnHandleInput();
                Demo.OnUpdate();

                if (isFormClosed)
                    break;

                if (!formIsResizing)
                    Render();
            }
            */
            //OnLostDevice();
        }

        protected virtual void OnResetDevice()
        {
            Info.OnResetDevice();

            Matrix projection = Matrix.CreatePerspectiveFieldOfView(FieldOfView, AspectRatio, NearPlane, FarPlane);
            //Device.SetTransform(TransformState.Projection, projection);
            UpdateView();

            //Device.SetRenderState(RenderState.Ambient, Ambient);

            //Device.SetLight(0, light);
            //Device.EnableLight(0, true);
        }

        protected virtual void OnLostDevice()
        {
            Info.OnLostDevice();
        }

        public override void SetInfoText(string text)
        {
            Info.Text = text;
        }
    }
}
