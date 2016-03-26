using System;
using BulletSharp;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace BasicDemo
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class BasicDemo : Game
    {
        Vector3 _activeColor = Color.Orange.ToVector3();
        Vector3 _passiveColor = Color.DarkOrange.ToVector3();
        Vector3 _groundColor = Color.Green.ToVector3();

        Vector3 eye = new Vector3(30, 20, 10);
        Vector3 target = new Vector3(0, 5, 0);

        GraphicsDeviceManager graphics;
        GraphicsDevice device;
        BasicEffect basicEffect;
        Physics physics;
        Physics.PhysicsDebugDraw DebugDrawer;
        bool IsDebugDrawEnabled;
        bool f3KeyPressed;

        Matrix viewMatrix;
        VertexBuffer groundBox, box;

        public BasicDemo()
        {
            graphics = new GraphicsDeviceManager(this);

            Window.Title = "BulletSharp - MonoGame Basic Demo";
            Window.AllowUserResizing = true;
            Window.ClientSizeChanged += Window_ClientSizeChanged;
        }

        void Window_ClientSizeChanged(object sender, EventArgs e)
        {
            basicEffect.Projection = Matrix.CreatePerspectiveFieldOfView(
                MathHelper.PiOver4, device.Viewport.AspectRatio, 1.0f, 200.0f);
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            physics = new Physics();

            DebugDrawer = new Physics.PhysicsDebugDraw(graphics.GraphicsDevice);
            physics.World.DebugDrawer = DebugDrawer;

            IsMouseVisible = true;
            base.Initialize();
        }

        protected override void EndRun()
        {
            physics.ExitPhysics();
            base.EndRun();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            device = graphics.GraphicsDevice;
            basicEffect = new BasicEffect(device);

            basicEffect.Projection = Matrix.CreatePerspectiveFieldOfView(
                MathHelper.PiOver4, device.Viewport.AspectRatio, 1.0f, 200.0f);

            // Set light
            basicEffect.AmbientLightColor = Color.Gray.ToVector3();
            basicEffect.DirectionalLight0.Enabled = true;
            basicEffect.DirectionalLight0.DiffuseColor = Color.LemonChiffon.ToVector3();

            box = VertexHelper.CreateBox(device, new Vector3(1, 1, 1));
            groundBox = VertexHelper.CreateBox(device, new Vector3(50, 1, 50));
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// game-specific content.
        /// </summary>
        protected override void UnloadContent()
        {
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            KeyboardState ns = Keyboard.GetState();
            if (ns.IsKeyDown(Keys.Escape) || ns.IsKeyDown(Keys.Q))
            {
                Exit();
            }

            // Toggle debug
            if (ns.IsKeyDown(Keys.F3))
            {
                if (f3KeyPressed == false)
                {
                    f3KeyPressed = true;
                    if (IsDebugDrawEnabled == false)
                    {
                        DebugDrawer.DebugMode = DebugDrawModes.DrawAabb;
                        IsDebugDrawEnabled = true;
                    }
                    else
                    {
                        DebugDrawer.DebugMode = DebugDrawModes.None;
                        IsDebugDrawEnabled = false;
                    }
                }
            }
            if (f3KeyPressed)
            {
                if (ns.IsKeyUp(Keys.F3))
                    f3KeyPressed = false;
            }

            viewMatrix = Matrix.CreateLookAt(eye, target, Vector3.UnitY);

            physics.Update((float)gameTime.ElapsedGameTime.TotalSeconds);

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            basicEffect.View = viewMatrix;


            // Debug draw
            basicEffect.VertexColorEnabled = true;
            basicEffect.LightingEnabled = false;

            basicEffect.World = Matrix.Identity;
            basicEffect.CurrentTechnique.Passes[0].Apply();
            DebugDrawer.DrawDebugWorld(physics.World);


            // Draw shapes
            basicEffect.VertexColorEnabled = false;
            basicEffect.LightingEnabled = true;

            foreach (var colObj in physics.World.CollisionObjectArray)
            {
                var body = colObj as RigidBody;
                basicEffect.World = body.WorldTransform;

                if ("Ground".Equals(colObj.UserObject))
                {
                    basicEffect.DiffuseColor = _groundColor;
                    basicEffect.CurrentTechnique.Passes[0].Apply();
                    VertexHelper.DrawBox(device, groundBox);
                    continue;
                }

                if (colObj.ActivationState == ActivationState.ActiveTag)
                    basicEffect.DiffuseColor = _activeColor;
                else
                    basicEffect.DiffuseColor = _passiveColor;

                basicEffect.CurrentTechnique.Passes[0].Apply();
                VertexHelper.DrawBox(device, box);
            }

            base.Draw(gameTime);
        }
    }
}
