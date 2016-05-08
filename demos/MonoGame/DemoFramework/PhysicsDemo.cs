using BulletSharp;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;
using System.Collections.Generic;

namespace DemoFramework
{
    /// <summary>
    /// This is the main type for your game.
    /// </summary>
    public class PhysicsDemo : DemoGame
    {
        private BasicEffect _debugEffect;
        private bool _isDebugDrawEnabled;
        private bool _f3KeyPressed;
        public PhysicsDebugDraw DebugDrawer { get; private set; }

        public CollisionConfiguration CollisionConf { get; set; }
        public CollisionDispatcher Dispatcher { get; set; }
        public BroadphaseInterface Broadphase { get; set; }
        public DynamicsWorld World { get; set; }

        public List<CollisionShape> CollisionShapes { get; } = new List<CollisionShape>();

        protected override void Initialize()
        {
            base.Initialize();
        }

        protected override void LoadContent()
        {
            base.LoadContent();

            DebugDrawer = new PhysicsDebugDraw(Device);
            _debugEffect = new BasicEffect(Device);
            _debugEffect.World = Matrix.Identity;
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            base.Draw(gameTime);

            GraphicsDevice.Clear(Color.CornflowerBlue);

            // Debug draw
            _debugEffect.LightingEnabled = false;
            _debugEffect.VertexColorEnabled = true;
            _debugEffect.CurrentTechnique.Passes[0].Apply();
            DebugDrawer.DrawDebugWorld(World);

            // Draw shapes
            foreach (RigidBody body in World.CollisionObjectArray)
            {
                DrawModel(body.CollisionShape, body.WorldTransform);
            }
        }

        protected override void Update(GameTime gameTime)
        {
            var ns = Keyboard.GetState();

            // Toggle debug
            if (ns.IsKeyDown(Keys.F3))
            {
                if (_f3KeyPressed == false)
                {
                    _f3KeyPressed = true;
                    if (_isDebugDrawEnabled == false)
                    {
                        DebugDrawer.DebugMode = DebugDrawModes.DrawAabb;
                        _isDebugDrawEnabled = true;
                    }
                    else
                    {
                        DebugDrawer.DebugMode = DebugDrawModes.None;
                        _isDebugDrawEnabled = false;
                    }
                }
            }
            if (_f3KeyPressed)
            {
                if (ns.IsKeyUp(Keys.F3))
                    _f3KeyPressed = false;
            }

            World.StepSimulation((float)gameTime.ElapsedGameTime.TotalSeconds);

            base.Update(gameTime);
        }

        protected override void UpdateView()
        {
            base.UpdateView();

            _debugEffect.View = View;
        }

        protected override void Window_ClientSizeChanged(object sender, EventArgs e)
        {
            base.Window_ClientSizeChanged(sender, e);

            _debugEffect.Projection = Projection;
        }

        protected override void EndRun()
        {
            ExitPhysics();
        }

        public void ExitPhysics()
        {
            // Remove/dispose constraints
            for (int i = World.NumConstraints - 1; i >= 0; i--)
            {
                var constraint = World.GetConstraint(i);
                World.RemoveConstraint(constraint);
                constraint.Dispose();
            }

            // Remove/dispose rigid bodies
            for (int i = World.NumCollisionObjects - 1; i >= 0; i--)
            {
                var obj = World.CollisionObjectArray[i];
                var body = obj as RigidBody;
                if (body != null && body.MotionState != null)
                {
                    body.MotionState.Dispose();
                }
                World.RemoveCollisionObject(obj);
                obj.Dispose();
            }

            //delete collision shapes
            foreach (var shape in CollisionShapes)
                shape.Dispose();
            CollisionShapes.Clear();

            World.Dispose();
            Broadphase.Dispose();
            if (Dispatcher != null)
            {
                Dispatcher.Dispose();
            }
            CollisionConf.Dispose();
        }

        public RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            using (var rbInfo = new RigidBodyConstructionInfo(mass, null, shape))
            {
                bool isDynamic = mass != 0.0f;
                if (isDynamic)
                {
                    rbInfo.LocalInertia = shape.CalculateLocalInertia(mass);
                    rbInfo.MotionState = new DefaultMotionState(startTransform);
                }

                var body = new RigidBody(rbInfo);
                World.AddRigidBody(body);
                return body;
            }
        }
    }
}
