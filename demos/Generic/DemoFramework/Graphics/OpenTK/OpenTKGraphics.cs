using System.Drawing;
using System.IO;
using System.Windows.Forms;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace DemoFramework.OpenTK
{
    public class OpenTKGraphics : DemoFramework.Graphics
    {
        GLControl glControl;
        Matrix4 lookat, perspective;

        MeshFactory meshFactory;
        InfoText info;

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

        int CreateShader(ShaderType type, string filename)
        {
            string shaderSource;
            StreamReader reader;
            try
            {
                reader = new StreamReader(filename);
                shaderSource = reader.ReadToEnd();
                reader.Close();
            }
            catch
            {
                return 0;
            }

            int shaderHandle = GL.CreateShader(type);
            GL.ShaderSource(shaderHandle, shaderSource);
            GL.CompileShader(shaderHandle);

            return shaderHandle;
        }

        public void InitializeDevice()
        {
            GL.ClearColor(Color.Gray);

            GL.Enable(EnableCap.ColorMaterial);
            GL.Enable(EnableCap.Light0);
            GL.Enable(EnableCap.Lighting);

            GL.Material(MaterialFace.Front, MaterialParameter.Specular, 0xffffffff);
            GL.Material(MaterialFace.Front, MaterialParameter.Shininess, 50.0f);
            GL.Light(LightName.Light0, LightParameter.Position, new global::OpenTK.Vector4(-10, 10, 10, 0.0f));
            GL.Light(LightName.Light0, LightParameter.ConstantAttenuation, 0.6f);
            GL.Light(LightName.Light0, LightParameter.Diffuse, new global::OpenTK.Vector4(1.0f, 0.98f, 0.8f, 1.0f));

            int vertexShaderHandle = CreateShader(ShaderType.VertexShader, "vp.cg");
            int fragmentShaderHandle = CreateShader(ShaderType.VertexShader, "fp.cg");
        }

        public override void Initialize()
        {
            meshFactory = new MeshFactory();
            info = new InfoText(glControl);
        }

        public override void Run()
        {
            LibraryManager.LibraryStarted();
            Form.ShowDialog();
        }

        static float fps;
        public void Render()
        {
            Demo.OnHandleInput();
            Demo.OnUpdate();

            if (fps != Demo.FramesPerSecond)
            {
                fps = Demo.FramesPerSecond;
                Form.Text = "FPS: " + Demo.FramesPerSecond.ToString();
            }

            GL.Viewport(0, 0, glControl.Width, glControl.Height);

            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadMatrix(ref perspective);
            GL.Scale(-1.0f, 1.0f, 1.0f);

            GL.Enable(EnableCap.DepthTest);
            GL.Enable(EnableCap.Lighting);
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            meshFactory.InitInstancedRender(Demo.World.CollisionObjectArray);
            meshFactory.RenderInstanced(ref lookat);

            info.OnRender(Demo.FramesPerSecond);

            glControl.SwapBuffers();
        }

        public override void UpdateView()
        {
            perspective = Matrix4.CreatePerspectiveFieldOfView((float)System.Math.PI / 4.0f, AspectRatio, 0.1f, 400);

            FreeLook freelook = Demo.Freelook;
            lookat = Matrix4.LookAt(MathHelper.Convert(freelook.Eye), MathHelper.Convert(freelook.Target), MathHelper.Convert(freelook.Up));
        }

        public override void SetInfoText(string text)
        {
            info.Text = text;
        }
    }
}
