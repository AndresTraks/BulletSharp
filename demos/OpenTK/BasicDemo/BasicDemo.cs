using System.Drawing;
using BulletSharp;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace BasicDemo
{
    class BasicDemo : GameWindow
    {
        Physics physics;
        float angle = 0.0f;

        public BasicDemo()
            : base(800, 600,
            new GraphicsMode(), "BulletSharp OpenTK Demo")
        {
            physics = new Physics();
        }

        protected override void OnLoad(System.EventArgs e)
        {
            GL.Enable(EnableCap.DepthTest);
            GL.ClearColor(Color.MidnightBlue);

            GL.Enable(EnableCap.ColorMaterial);
            //GL.Enable(EnableCap.Light0);
            //GL.Enable(EnableCap.Lighting);
        }

        protected override void OnUpdateFrame(FrameEventArgs e)
        {
            physics.Update((float)e.Time);

            if (Keyboard[OpenTK.Input.Key.Escape])
                Exit();
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            GL.Viewport(0, 0, Width, Height);

            float aspect_ratio = Width / (float)Height;
            Matrix4 perpective = Matrix4.CreatePerspectiveFieldOfView(MathHelper.PiOver4, aspect_ratio, 0.1f, 100);
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadMatrix(ref perpective);

            Matrix4 lookat = Matrix4.LookAt(new Vector3(10, 20, 30), Vector3.Zero, Vector3.UnitY);
            GL.MatrixMode(MatrixMode.Modelview);

            GL.Rotate(angle, 0.0f, 1.0f, 0.0f);
            angle += (float)e.Time*100;

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            foreach (RigidBody body in physics.World.CollisionObjectArray)
            {
                Matrix4 modelLookAt;

                if ((string)body.UserObject == "Ground")
                {
                    modelLookAt = body.MotionState.WorldTransform * lookat;
                    GL.LoadMatrix(ref modelLookAt);
                    DrawCube(Color.Green, 50.0f);
                    continue;
                }

                modelLookAt = body.MotionState.WorldTransform * lookat;
                GL.LoadMatrix(ref modelLookAt);

                if (body.ActivationState == ActivationState.ActiveTag)
                    DrawCube(Color.Orange);
                else
                    DrawCube(Color.Red);
            }

            SwapBuffers();
        }

        private void DrawCube(Color color)
        {
            DrawCube(color, 1.0f);
        }

        private void DrawCube(Color color, float size)
        {
            GL.Begin(BeginMode.Quads);

            GL.Color3(color);
            GL.Vertex3(-size, -size, -size);
            GL.Vertex3(-size, size, -size);
            GL.Vertex3(size, size, -size);
            GL.Vertex3(size, -size, -size);

            GL.Vertex3(-size, -size, -size);
            GL.Vertex3(size, -size, -size);
            GL.Vertex3(size, -size, size);
            GL.Vertex3(-size, -size, size);

            GL.Vertex3(-size, -size, -size);
            GL.Vertex3(-size, -size, size);
            GL.Vertex3(-size, size, size);
            GL.Vertex3(-size, size, -size);
            
            GL.Vertex3(-size, -size, size);
            GL.Vertex3(size, -size, size);
            GL.Vertex3(size, size, size);
            GL.Vertex3(-size, size, size);

            GL.Vertex3(-size, size, -size);
            GL.Vertex3(-size, size, size);
            GL.Vertex3(size, size, size);
            GL.Vertex3(size, size, -size);

            GL.Vertex3(size, -size, -size);
            GL.Vertex3(size, size, -size);
            GL.Vertex3(size, size, size);
            GL.Vertex3(size, -size, size);

            GL.End();
        }
    }
}
