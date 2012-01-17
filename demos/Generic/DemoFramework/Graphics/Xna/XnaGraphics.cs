﻿using System;
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

        public override float AspectRatio
        {
            get { return Device.Viewport.AspectRatio; }
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

        BasicEffect effect;

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
            Demo.Input.Control = (Form as XnaForm).GraphicsDeviceControl;
        }

        public void InitializeDevice()
        {
            Form.ClientSize = new Size(Width, Height);

            meshFactory = new MeshFactory(this);

            effect = new BasicEffect(Device);

            // Set light
            //effect.LightingEnabled = true;
            //effect.AmbientLightColor = Color.Gray.ToVector3();
            //effect.DirectionalLight0.Enabled = true;
            //effect.DirectionalLight0.DiffuseColor = Color.LemonChiffon.ToVector3();
            effect.EnableDefaultLighting();

            Device.RasterizerState = RasterizerState.CullNone;

            UpdateView();
            LibraryManager.LibraryStarted();
        }

        public void Render()
        {
            Device.Clear(ClearOptions.Target | ClearOptions.DepthBuffer, Microsoft.Xna.Framework.Color.LightGray, 1.0f, 0);

            meshFactory.InitInstancedRender(Demo.World.CollisionObjectArray);
            meshFactory.RenderInstanced(effect);

            //if (Demo.IsDebugDrawEnabled)
            //    (Demo.World.DebugDrawer as PhysicsDebugDraw).DrawDebugWorld(Demo.World);
            //Info.OnRender(Demo.FramesPerSecond);
        }

        public override void UpdateView()
        {
            if (effect != null)
            {
                FreeLook freelook = Demo.Freelook;
                effect.View = Matrix.CreateLookAt(MathHelper.Convert(freelook.Eye), MathHelper.Convert(freelook.Target), MathHelper.Convert(freelook.Up));
                effect.View *= Matrix.CreateScale(-1, 1, 1);
            }
        }

        /// <summary>
        /// Runs the game.
        /// </summary>
        public override void Run()
        {
            Form.ShowDialog();
        }

        public virtual void OnResetDevice()
        {
            Info.OnResetDevice();

            effect.Projection = Matrix.CreatePerspectiveFieldOfView(FieldOfView, AspectRatio, NearPlane, FarPlane);
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
