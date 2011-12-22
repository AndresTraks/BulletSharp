using System.Drawing;
using System.IO;
using System.Windows.Forms;
using OpenTK;
using OpenTK.Graphics.OpenGL;
using System;

namespace DemoFramework.OpenTK
{
    public class OpenTKGraphics : DemoFramework.Graphics
    {
        GLControl glControl;
        Matrix4 lookat, perspective;

        MeshFactory meshFactory;
        InfoText info;

        int shaderProgramHandle;
        int projectionMatrixLocation;
        int modelviewMatrixLocation;
        int lightPositionVectorLocation;

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
            ErrorCode e = GL.GetError();
            e.ToString();
            if (GL.GetError() != ErrorCode.NoError)
                return 0;

            GL.ShaderSource(shaderHandle, shaderSource);
            if (GL.GetError() != ErrorCode.NoError)
                return 0;

            GL.CompileShader(shaderHandle);
            if (GL.GetError() != ErrorCode.NoError)
                return 0;

            return shaderHandle;
        }

        public void InitializeDevice()
        {
            Version ver = new Version(GL.GetString(StringName.Version));
            Version req = new Version(1, 4, 0, 0);

            if (ver < req)
                MessageBox.Show(string.Format("Need OpenGL {0:0.0} or newer to run.", req.ToString()));

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
            int fragmentShaderHandle = CreateShader(ShaderType.FragmentShader, "fp.cg");

            if (vertexShaderHandle == 0 || fragmentShaderHandle == 0)
            {
                MessageBox.Show("Could not create shaders!");
                return;
            }

            shaderProgramHandle = GL.CreateProgram();
            if (GL.GetError() != ErrorCode.NoError)
                return;

            GL.AttachShader(shaderProgramHandle, vertexShaderHandle);
            if (GL.GetError() != ErrorCode.NoError)
                return;
            
            GL.AttachShader(shaderProgramHandle, fragmentShaderHandle);
            if (GL.GetError() != ErrorCode.NoError)
                return;
            
            GL.LinkProgram(shaderProgramHandle);
            if (GL.GetError() != ErrorCode.NoError)
                return;

            string programInfoLog;
            GL.GetProgramInfoLog(shaderProgramHandle, out programInfoLog);
            programInfoLog.ToString();

            GL.UseProgram(shaderProgramHandle);
            if (GL.GetError() != ErrorCode.NoError)
                return;

            projectionMatrixLocation = GL.GetUniformLocation(shaderProgramHandle, "projection_matrix");
            modelviewMatrixLocation = GL.GetUniformLocation(shaderProgramHandle, "modelview_matrix");
            lightPositionVectorLocation = GL.GetUniformLocation(shaderProgramHandle, "light_position");
            meshFactory.SetModelViewMatrixLocation(modelviewMatrixLocation);
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

        public void Render()
        {
            Demo.OnHandleInput();
            Demo.OnUpdate();

            GL.Viewport(0, 0, glControl.Width, glControl.Height);

            GL.UseProgram(shaderProgramHandle);
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadMatrix(ref perspective);
            GL.UniformMatrix4(projectionMatrixLocation, false, ref perspective);

            GL.Enable(EnableCap.DepthTest);
            GL.Enable(EnableCap.Lighting);
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            meshFactory.InitInstancedRender(Demo.World.CollisionObjectArray);
            meshFactory.RenderInstanced(ref lookat);

            GL.UseProgram(0);
            info.OnRender(Demo.FramesPerSecond);

            glControl.SwapBuffers();
        }

        public override void UpdateView()
        {
            perspective = Matrix4.CreatePerspectiveFieldOfView(FieldOfView, AspectRatio, 0.1f, 400);
            perspective *= Matrix4.Scale(-1.0f, 1.0f, 1.0f);
            if (projectionMatrixLocation != 0)
            {
                GL.UniformMatrix4(projectionMatrixLocation, false, ref perspective);
            }

            FreeLook freelook = Demo.Freelook;
            lookat = Matrix4.LookAt(MathHelper.Convert(freelook.Eye), MathHelper.Convert(freelook.Target), MathHelper.Convert(freelook.Up));
        }

        public override void SetInfoText(string text)
        {
            info.Text = text;
        }
    }
}
