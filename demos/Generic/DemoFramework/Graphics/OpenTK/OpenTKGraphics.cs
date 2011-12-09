using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace DemoFramework.OpenTK
{
    public class OpenTKGraphics : DemoFramework.Graphics
    {
        GLControl glControl;
        Matrix4 lookat, perspective;

        public override float AspectRatio
        {
            get
            {
                return (float)glControl.Width / (float)glControl.Height;
            }
        }

        public OpenTKGraphics(Demo demo)
            : base(demo)
        {
            Form = new GLForm(this);
            glControl = (Form as GLForm).GLControl;
        }

        public void InitializeDevice()
        {
            GL.Enable(EnableCap.DepthTest);
            GL.ClearColor(Color.MidnightBlue);

            GL.Enable(EnableCap.ColorMaterial);
            GL.Enable(EnableCap.Light0);
            GL.Enable(EnableCap.Lighting);
        }

        public override void Run()
        {
            Application.Run(Form);
        }

        public void Render()
        {
            Demo.OnHandleInput();
            Demo.OnUpdate();

            GL.Viewport(0, 0, Form.Width, Form.Height);

            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadMatrix(ref perspective);
            GL.Scale(-1.0f, 1.0f, 1.0f);

            GL.MatrixMode(MatrixMode.Modelview);

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            InitCube();

            foreach (RigidBody body in Demo.World.CollisionObjectArray)
            {
                Matrix4 modelLookAt;

                if ((string)body.UserObject == "Ground")
                {
                    modelLookAt = MathHelper.Convert(body.MotionState.WorldTransform) * lookat;
                    GL.LoadMatrix(ref modelLookAt);
                    DrawCube(Color.Green, (body.CollisionShape as BoxShape).HalfExtentsWithMargin);
                    continue;
                }

                modelLookAt = MathHelper.Convert(body.MotionState.WorldTransform) * lookat;
                GL.LoadMatrix(ref modelLookAt);

                if (body.ActivationState == ActivationState.ActiveTag)
                    DrawCube2(Color.Orange, 1);
                else
                    DrawCube2(Color.Red, 1);
            }

            UninitCube();

            glControl.SwapBuffers();
        }

        public override void UpdateView()
        {
            perspective = Matrix4.CreatePerspectiveFieldOfView((float)System.Math.PI / 4.0f, AspectRatio, 0.1f, 100);

            FreeLook freelook = Demo.Freelook;
            lookat = Matrix4.LookAt(MathHelper.Convert(freelook.Eye), MathHelper.Convert(freelook.Target), MathHelper.Convert(freelook.Up));
        }

        private void DrawCube(Color color, BulletSharp.Vector3 size)
        {
            float x = size.X;
            float y = size.Y;
            float z = size.Z;

            GL.Begin(BeginMode.Quads);

            GL.Color3(color);
            GL.Vertex3(-x, -y, -z);
            GL.Vertex3(-x, y, -z);
            GL.Vertex3(x, y, -z);
            GL.Vertex3(x, -y, -z);

            GL.Vertex3(-x, -y, -z);
            GL.Vertex3(x, -y, -z);
            GL.Vertex3(x, -y, z);
            GL.Vertex3(-x, -y, z);

            GL.Vertex3(-x, -y, -z);
            GL.Vertex3(-x, -y, z);
            GL.Vertex3(-x, y, z);
            GL.Vertex3(-x, y, -z);

            GL.Vertex3(-x, -y, z);
            GL.Vertex3(x, -y, z);
            GL.Vertex3(x, y, z);
            GL.Vertex3(-x, y, z);

            GL.Vertex3(-x, y, -z);
            GL.Vertex3(-x, y, z);
            GL.Vertex3(x, y, z);
            GL.Vertex3(x, y, -z);

            GL.Vertex3(x, -y, -z);
            GL.Vertex3(x, y, -z);
            GL.Vertex3(x, y, z);
            GL.Vertex3(x, -y, z);

            GL.End();
        }

        float[] vertices = new float[] {1,1,1,  -1,1,1,  -1,-1,1,  1,-1,1,
            1,1,1,  1,-1,1,  1,-1,-1,  1,1,-1,
            1,1,1,  1,1,-1,  -1,1,-1,  -1,1,1,
            -1,1,1,  -1,1,-1,  -1,-1,-1,  -1,-1,1,
            -1,-1,-1,  1,-1,-1,  1,-1,1,  -1,-1,1,
            1,-1,-1,  -1,-1,-1,  -1,1,-1,  1,1,-1};

        float[] normals = new float[] {0,0,1,  0,0,1,  0,0,1,  0,0,1,
            1,0,0,  1,0,0,  1,0,0, 1,0,0,
            0,1,0,  0,1,0,  0,1,0, 0,1,0,
            -1,0,0,  -1,0,0, -1,0,0,  -1,0,0,
            0,-1,0,  0,-1,0,  0,-1,0,  0,-1,0,
            0,0,-1,  0,0,-1,  0,0,-1,  0,0,-1};

        byte[] indices = {0,1,2,3,
            4,5,6,7,
            8,9,10,11,
            12,13,14,15,
            16,17,18,19,
            20,21,22,23};

        void InitCube()
        {
            GL.EnableClientState(ArrayCap.NormalArray);
            GL.EnableClientState(ArrayCap.VertexArray);
            GL.NormalPointer(NormalPointerType.Float, 0, normals);
            GL.VertexPointer(3, VertexPointerType.Float, 0, vertices);
        }

        void UninitCube()
        {
            GL.DisableClientState(ArrayCap.VertexArray);
            GL.DisableClientState(ArrayCap.NormalArray);
        }

        void DrawCube2(Color color, float size)
        {
            GL.Color3(color);
            GL.DrawElements(BeginMode.Quads, 24, DrawElementsType.UnsignedByte, indices);
        }
    }
}
