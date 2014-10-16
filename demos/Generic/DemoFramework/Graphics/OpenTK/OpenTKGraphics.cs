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

        public static bool CheckGLError(string caller)
        {
            ErrorCode err = GL.GetError();
            if (err != ErrorCode.NoError)
            {
                //MessageBox.Show(string.Format("GL error {0} at {1}", err, caller));
                Console.WriteLine("GL error {0} at {1}", err, caller);
                return true;
            }
            return false;
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
            if (!GL.GetBoolean(GetPName.ShaderCompiler))
            {
                Console.WriteLine("OpenGL shader compiler not available");
                return 0;
            }

            int shaderHandle = GL.CreateShader(type);
            if (CheckGLError("CreateShader"))
                return 0;

            GL.ShaderSource(shaderHandle, shaderSource);
            if (CheckGLError("ShaderSource"))
                return 0;

            GL.CompileShader(shaderHandle);
            if (CheckGLError("CompileShader"))
                return 0;

            int success;
            GL.GetShader(shaderHandle, ShaderParameter.CompileStatus, out success);
            if (success == 0)
            {
                string programInfoLog = GL.GetShaderInfoLog(shaderHandle);
                GL.GetShaderInfoLog(shaderHandle, out programInfoLog);
                if (CheckGLError("GetShaderInfoLog"))
                    return 0;

                Console.WriteLine(programInfoLog);
                return 0;
            }

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
            Version req = new Version(2, 1);

            if (ver < req)
                MessageBox.Show(string.Format("Need OpenGL {0} or newer to run. Have {1}.", req, ver));

            GL.ClearColor(Color.Gray);

            int vertexShaderHandle = CreateShaderFromResource(ShaderType.VertexShader, "vp.cg");
            int fragmentShaderHandle = CreateShaderFromResource(ShaderType.FragmentShader, "fp.cg");

            if (vertexShaderHandle == 0 || fragmentShaderHandle == 0)
            {
                MessageBox.Show("Could not create shaders!");
                return;
            }

            shaderProgram = GL.CreateProgram();
            if (CheckGLError("CreateProgram"))
                return;

            GL.AttachShader(shaderProgram, vertexShaderHandle);
            if (CheckGLError("AttachShader"))
                return;
            
            GL.AttachShader(shaderProgram, fragmentShaderHandle);
            if (CheckGLError("AttachShader"))
                return;
            
            GL.LinkProgram(shaderProgram);
            if (CheckGLError("LinkProgram"))
                return;

            GL.UseProgram(shaderProgram);
            if (CheckGLError("UseProgram"))
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
                perspective *= Matrix4.CreateScale(-1.0f, 1.0f, 1.0f);
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

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                info.Dispose();
            }
            base.Dispose(disposing);
        }
    }
}
