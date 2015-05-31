using System.Windows.Forms;

namespace DemoFramework.MonoGame
{
    public partial class XnaForm : Form
    {
        public GraphicsDeviceControl GraphicsDeviceControl
        {
            get { return graphicsDeviceControl1; }
        }

        public XnaForm(MonoGameGraphics graphics)
        {
            InitializeComponent();
            
            graphicsDeviceControl1.SetGraphics(graphics);
        }
    }
}
