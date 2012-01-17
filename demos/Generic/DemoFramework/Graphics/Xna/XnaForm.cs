using System.Windows.Forms;

namespace DemoFramework.Xna
{
    public partial class XnaForm : Form
    {
        public XnaForm(XnaGraphics graphics)
        {
            InitializeComponent();
            
            graphicsDeviceControl1.SetGraphics(graphics);
        }
    }
}
