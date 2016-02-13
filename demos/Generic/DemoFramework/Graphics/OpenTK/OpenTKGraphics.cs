using System;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace DemoFramework.OpenTK
{
    public class OpenTKGraphics : Graphics
    {
        GLControl glControl;
        Matrix4 lookat, perspective;
        bool viewChanged;

        MeshFactory _meshFactory;
        InfoText info;

        int shaderProgram;
        int viewMatrixLocation;
        int projectionMatrixLocation;
        int lightPositionVectorLocation;
        int eyePositionVectorLocation;

        public override float AspectRatio
        {
            get { return glControl.AspectRatio; }
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

        public override bool CullingEnabled
        {
            get
            {
                return base.CullingEnabled;
            }
            set
            {
                viewChanged = true;
                base.CullingEnabled = value;
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

        public void InitializeDevice()
        {
            Version ver = new Version(GL.GetString(StringName.Version).Split(' ')[0]);
            Version req = new Version(2, 1);

            if (ver < req)
                MessageBox.Show(string.Format("Need OpenGL {0} or newer to run. Have {1}.", req, ver));

            GL.ClearColor(Color.Gray);
            GL.FrontFace(FrontFaceDirection.Cw);

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

            viewMatrixLocation = GL.GetUniformLocation(shaderProgram, "view_matrix");
            projectionMatrixLocation = GL.GetUniformLocation(shaderProgram, "projection_matrix");
            lightPositionVectorLocation = GL.GetUniformLocation(shaderProgram, "light_position");
            eyePositionVectorLocation = GL.GetUniformLocation(shaderProgram, "eye_position");
            _meshFactory.SetShaderLocations(
                GL.GetUniformLocation(shaderProgram, "world_matrix"),
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
            GraphicsLibraryManager.LibraryStarted();
            Form.ShowDialog();
        }

        public void Paint()
        {
            Demo.OnHandleInput();
            Demo.OnUpdate();

            Demo.Clock.StartRender();
            Render();
            Demo.Clock.StopRender();
        }

        public void Render()
        {
            GL.UseProgram(shaderProgram);
            GL.Enable(EnableCap.DepthTest);
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            
            if (viewChanged)
            {
                GL.Viewport(0, 0, glControl.Width, glControl.Height);

                FreeLook freelook = Demo.Freelook;
                lookat = Matrix4.LookAt(MathHelper.Convert(freelook.Eye), MathHelper.Convert(freelook.Target), MathHelper.Convert(freelook.Up));
                GL.UniformMatrix4(viewMatrixLocation, false, ref lookat);

                Matrix4.CreatePerspectiveFieldOfView(FieldOfView, AspectRatio, 0.1f, FarPlane, out perspective);
                perspective *= Matrix4.CreateScale(-1.0f, 1.0f, 1.0f);
                GL.UniformMatrix4(projectionMatrixLocation, false, ref perspective);

                Vector3 lightPosition = new Vector3(30, 20, 10);
                GL.Uniform3(lightPositionVectorLocation, lightPosition);
                GL.Uniform3(eyePositionVectorLocation, MathHelper.Convert(freelook.Eye));

                if (CullingEnabled)
                {
                    GL.Enable(EnableCap.CullFace);
                }
                else
                {
                    GL.Disable(EnableCap.CullFace);
                }

                viewChanged = false;
            }

            if (Demo.World != null)
            {
                _meshFactory.InitInstancedRender();
                _meshFactory.RenderInstanced();
            }

            GL.UseProgram(0);
            if (Demo.IsDebugDrawEnabled)
            {
                GL.MatrixMode(MatrixMode.Modelview);
                GL.LoadMatrix(ref lookat);
                GL.MatrixMode(MatrixMode.Projection);
                GL.LoadMatrix(ref perspective);
                (Demo.World.DebugDrawer as PhysicsDebugDraw).DrawDebugWorld(Demo.World);
            }

            info.OnRender();

            glControl.SwapBuffers();
        }

        public override void UpdateView()
        {
            // Can't update program variables here,
            // wait until Render().
            viewChanged = true;
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
