using System;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace DemoFramework.OpenTK
{
    public class OpenTKGraphics : DemoFramework.Graphics
    {
        GLControl glControl;
        Matrix4 lookat, perspective;

        MeshFactory _meshFactory;
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

        public override float FarPlane
        {
            set
            {
                base.FarPlane = value;
                if (Demo.Freelook != null)
                {
                    UpdateView();
                }
            }
        }

        public override BulletSharp.IDebugDraw GetPhysicsDebugDrawer()
        {
            return new PhysicsDebugDraw();
        }

        public OpenTKGraphics(Demo demo)
            : base(demo)
        {
            Form = new GLForm(this);
            glControl = (Form as GLForm).GLControl;
        }

        int CreateShaderFromResource(ShaderType type, string resourceName)
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            string shaderSource;
            StreamReader reader;
            try
            {
                reader = new StreamReader(assembly.GetManifestResourceStream("DemoFramework.OpenTK." + resourceName));
                shaderSource = reader.ReadToEnd();
                reader.Close();
            }
            catch
            {
                return 0;
            }

            return CreateShaderFromString(type, shaderSource);
        }

        int CreateShaderFromString(ShaderType type, string shaderSource)
        {
            int shaderHandle = GL.CreateShader(type);
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

        int CreateShaderFromFile(ShaderType type, string filename)
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

            return CreateShaderFromString(type, shaderSource);
        }

        public void InitializeDevice()
        {
            Version ver = new Version(GL.GetString(StringName.Version).Split(' ')[0]);
            Version req = new Version(3, 1, 0, 0);

            if (ver < req)
                MessageBox.Show(string.Format("Need OpenGL {0:0.0} or newer to run.", req.ToString()));

            GL.ClearColor(Color.Gray);

            int vertexShaderHandle = CreateShaderFromResource(ShaderType.VertexShader, "vp.cg");
            int fragmentShaderHandle = CreateShaderFromResource(ShaderType.FragmentShader, "fp.cg");

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

            //string programInfoLog;
            //GL.GetProgramInfoLog(shaderProgram, out programInfoLog);

            GL.UseProgram(shaderProgram);
            if (GL.GetError() != ErrorCode.NoError)
                return;

            projectionMatrixLocation = GL.GetUniformLocation(shaderProgram, "projection_matrix");
            lightDirectionVectorLocation = GL.GetUniformLocation(shaderProgram, "light_direction");
            _meshFactory.SetShaderLocations(GL.GetUniformLocation(shaderProgram, "modelview_matrix"),
                GL.GetAttribLocation(shaderProgram, "position"),
                GL.GetAttribLocation(shaderProgram, "normal"),
                GL.GetUniformLocation(shaderProgram, "color")
            );

            UpdateView();
        }

        public override void Initialize()
        {
            _meshFactory = new MeshFactory(Demo);
            MeshFactory = _meshFactory;
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

            _meshFactory.InitInstancedRender(Demo.World.CollisionObjectArray);
            _meshFactory.RenderInstanced(ref lookat);

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
                
                perspective = Matrix4.CreatePerspectiveFieldOfView(FieldOfView, AspectRatio, 0.1f, FarPlane);
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
