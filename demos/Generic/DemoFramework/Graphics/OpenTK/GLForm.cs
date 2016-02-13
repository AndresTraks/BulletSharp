using System;
using System.Windows.Forms;
using OpenTK;
using OpenTK.Graphics;

namespace DemoFramework.OpenTK
{
    public partial class GLForm : Form
    {
        GLControl glControl;
        public GLControl GLControl
        {
            get { return glControl; }
            set { glControl = value; }
        }
        OpenTKGraphics graphics;

        public GLForm(OpenTKGraphics graphics)
        {
            this.graphics = graphics;

            InitializeComponent();

            glControl = new GLControl(new GraphicsMode(new ColorFormat(24), 24, 0, 4));
            glControl.BackColor = System.Drawing.Color.Black;
            glControl.Dock = DockStyle.Fill;
            glControl.TabIndex = 0;
            glControl.VSync = false;

            Controls.Add(glControl);

            glControl.Paint += new PaintEventHandler(glControl_Paint);
            glControl.Disposed += new EventHandler(glControl_Disposed);

            glControl.KeyDown += new KeyEventHandler(glControl_KeyDown);
            glControl.KeyUp += new KeyEventHandler(glControl_KeyUp);
            glControl.MouseDown += new MouseEventHandler(glControl_MouseDown);
            glControl.MouseUp += new MouseEventHandler(glControl_MouseUp);
            glControl.MouseMove += new MouseEventHandler(glControl_MouseMove);
            glControl.MouseWheel += new MouseEventHandler(glControl_MouseWheel);
            glControl.PreviewKeyDown += new PreviewKeyDownEventHandler(glControl_PreviewKeyDown);

            Resize += new EventHandler(GLForm_Resize);
        }

        void glControl_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if (e.KeyCode == Keys.Left || e.KeyCode == Keys.Right || e.KeyCode == Keys.Up || e.KeyCode == Keys.Down)
            {
                e.IsInputKey = true;
            }
        }

        void GLForm_Resize(object sender, EventArgs e)
        {
            graphics.UpdateView();
        }

        void glControl_Disposed(object sender, EventArgs e)
        {
            Application.Idle -= Application_Idle;
        }

        void glControl_Paint(object sender, PaintEventArgs e)
        {
            graphics.Paint();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            // GLControl loaded, start demo
            graphics.InitializeDevice();

            Application.Idle += new EventHandler(Application_Idle);
            Focus();
        }

        void Application_Idle(object sender, EventArgs e)
        {
            glControl.Invalidate();
        }

        void glControl_KeyDown(object sender, KeyEventArgs e)
        {
            OnKeyDown(e);
        }

        void glControl_KeyUp(object sender, KeyEventArgs e)
        {
            OnKeyUp(e);
        }

        void glControl_MouseDown(object sender, MouseEventArgs e)
        {
            OnMouseDown(e);
        }

        void glControl_MouseUp(object sender, MouseEventArgs e)
        {
            OnMouseUp(e);
        }

        void glControl_MouseMove(object sender, MouseEventArgs e)
        {
            OnMouseMove(e);
        }

        void glControl_MouseWheel(object sender, MouseEventArgs e)
        {
            OnMouseWheel(e);
        }
    }
}
