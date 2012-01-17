using System.Windows.Forms;

namespace DemoFramework.Xna
{
    public partial class XnaForm : Form
    {
        public GraphicsDeviceControl GraphicsDeviceControl
        {
            get { return graphicsDeviceControl1; }
        }

        public XnaForm(XnaGraphics graphics)
        {
            InitializeComponent();
            
            graphicsDeviceControl1.SetGraphics(graphics);
        }
    }
}
