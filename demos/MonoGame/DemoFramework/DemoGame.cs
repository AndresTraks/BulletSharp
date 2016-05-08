using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;
using System.Collections.Generic;

namespace DemoFramework
{
    public class DemoGame : Game
    {
        private GraphicsDeviceManager _graphics;
        public GraphicsDevice Device { get { return _graphics.GraphicsDevice; } }

        protected Input Input { get; set; }
        public Matrix View { get; set; }
        public Matrix Projection { get; set; }
        public FreeLook FreeLook { get; private set; }

        private Dictionary<object, Model> _models = new Dictionary<object, Model>();

        public DemoGame()
        {
            _graphics = new GraphicsDeviceManager(this);

            Content.RootDirectory = "Content";

            Window.AllowUserResizing = true;
            Window.ClientSizeChanged += Window_ClientSizeChanged;
        }

        protected virtual void Window_ClientSizeChanged(object sender, EventArgs e)
        {
            Projection = Matrix.CreatePerspectiveFieldOfView(
                MathHelper.PiOver4, Device.Viewport.AspectRatio, 1.0f, 200.0f);
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            base.Initialize();

            Input = new Input();
            FreeLook = new FreeLook(Input);
            IsMouseVisible = true;
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            Projection = Matrix.CreatePerspectiveFieldOfView(
                MathHelper.PiOver4, Device.Viewport.AspectRatio, 1.0f, 200.0f);

            base.LoadContent();
        }

        protected void LoadModel(string modelName, object key)
        {
            var model = Content.Load<Model>(modelName);
            _models[key] = model;

            foreach (var mesh in model.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.EnableDefaultLighting();
                    effect.PreferPerPixelLighting = true;
                }
            }
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// game-specific content.
        /// </summary>
        protected override void UnloadContent()
        {
        }

        protected void UpdateModel(Model model)
        {
            foreach (var mesh in model.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.AmbientLightColor = Color.Gray.ToVector3();
                    effect.DirectionalLight0.Enabled = true;
                    effect.DirectionalLight0.DiffuseColor = Color.LemonChiffon.ToVector3();

                    effect.View = View;
                    effect.Projection = Projection;
                }
            }
        }

        protected virtual void UpdateView()
        {
            View = Matrix.CreateLookAt(FreeLook.Eye, FreeLook.Target, Vector3.UnitY);

            foreach (var model in _models.Values)
            {
                UpdateModel(model);
            }
        }

        protected void DrawModel(object key, Matrix worldTransform)
        {
            foreach (var mesh in _models[key].Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.World = worldTransform;
                }

                mesh.Draw();
            }
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            var ns = Keyboard.GetState();
            if (ns.IsKeyDown(Keys.Escape) || ns.IsKeyDown(Keys.Q))
            {
                Exit();
            }

            Input.Update();

            float deltaTime = (float)gameTime.ElapsedGameTime.TotalSeconds;
            if (FreeLook.Update(deltaTime))
            {
                UpdateView();
            }

            base.Update(gameTime);
        }
    }
}
