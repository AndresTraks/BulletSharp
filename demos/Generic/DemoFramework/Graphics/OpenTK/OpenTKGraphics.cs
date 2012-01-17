using System;
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

        int shaderProgram;
        int projectionMatrixLocation;
        int lightDirectionVectorLocation;

        public override float AspectRatio
        {
            get
            {
                return (float)glControl.Width / (float)glControl.Height;
            }
        }

        public override BulletSharp.IDebugDraw GetPhysicsDebugDrawer()
        {
            return new PhysicsDebugDraw(this);
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
            Version req = new Version(3, 1, 0, 0);

            if (ver < req)
                MessageBox.Show(string.Format("Need OpenGL {0:0.0} or newer to run.", req.ToString()));

            GL.ClearColor(Color.Gray);

            int vertexShaderHandle = CreateShader(ShaderType.VertexShader, "vp.cg");
            int fragmentShaderHandle = CreateShader(ShaderType.FragmentShader, "fp.cg");

            if (vertexShaderHandle == 0 || fragmentShaderHandle == 0)
            {
                MessageBox.Show("Could not create shaders!");
                return;
            }

            shaderProgram = GL.CreateProgram();
            if (GL.GetError() != ErrorCode.NoError)
                return;

            GL.AttachShader(shaderProgram, vertexShaderHandle);
            if (GL.GetError() != ErrorCode.NoError)
                return;
            
            GL.AttachShader(shaderProgram, fragmentShaderHandle);
            if (GL.GetError() != ErrorCode.NoError)
                return;
            
            GL.LinkProgram(shaderProgram);
            if (GL.GetError() != ErrorCode.NoError)
                return;

            string programInfoLog;
            GL.GetProgramInfoLog(shaderProgram, out programInfoLog);
            programInfoLog.ToString();

            GL.UseProgram(shaderProgram);
            if (GL.GetError() != ErrorCode.NoError)
                return;

            projectionMatrixLocation = GL.GetUniformLocation(shaderProgram, "projection_matrix");
            lightDirectionVectorLocation = GL.GetUniformLocation(shaderProgram, "light_direction");
            meshFactory.SetShaderLocations(GL.GetUniformLocation(shaderProgram, "modelview_matrix"),
                GL.GetAttribLocation(shaderProgram, "position"),
                GL.GetAttribLocation(shaderProgram, "normal"),
                GL.GetUniformLocation(shaderProgram, "color")
            );

            UpdateView();
        }

        public override void Initialize()
        {
            meshFactory = new MeshFactory(Demo);
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

            GL.UseProgram(shaderProgram);
            GL.Enable(EnableCap.DepthTest);
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            meshFactory.InitInstancedRender(Demo.World.CollisionObjectArray);
            meshFactory.RenderInstanced(ref lookat);

            GL.UseProgram(0);
            if (Demo.IsDebugDrawEnabled)
            {
                GL.MatrixMode(MatrixMode.Modelview);
                GL.LoadMatrix(ref lookat);
                GL.MatrixMode(MatrixMode.Projection);
                GL.LoadMatrix(ref perspective);
                (Demo.World.DebugDrawer as PhysicsDebugDraw).DrawDebugWorld(Demo.World);
            }

            info.OnRender(Demo.FramesPerSecond);

            glControl.SwapBuffers();
        }

        public override void UpdateView()
        {
            if (shaderProgram != 0)
            {
                GL.Viewport(0, 0, glControl.Width, glControl.Height);
                
                perspective = Matrix4.CreatePerspectiveFieldOfView(FieldOfView, AspectRatio, 0.1f, 400);
                perspective *= Matrix4.Scale(-1.0f, 1.0f, 1.0f);
                GL.UniformMatrix4(projectionMatrixLocation, false, ref perspective);

                Vector3 lightDirection = Vector3.Normalize(new Vector3(1.0f, 1.0f, 1.0f));
                GL.Uniform3(lightDirectionVectorLocation, lightDirection);
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
