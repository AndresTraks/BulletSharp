using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace DemoFramework
{
    public class Input
    {
        public List<Keys> KeysPressed { get; private set; }
        public List<Keys> KeysReleased { get; private set; }
        public List<Keys> KeysDown { get; private set; }

        public MouseButtons MousePressed { get; private set; }
        public MouseButtons MouseReleased { get; private set; }
        public MouseButtons MouseDown { get; private set; }
        public Point MousePoint { get; private set; }
        public int MouseWheelDelta { get; private set; }

        Form form;

        public Input(Form form)
        {
            this.form = form;
            form.KeyDown += new KeyEventHandler(form_KeyDown);
            form.KeyUp += new KeyEventHandler(form_KeyUp);
            form.MouseDown += new MouseEventHandler(form_MouseDown);
            form.MouseMove += new MouseEventHandler(form_MouseMove);
            form.MouseUp += new MouseEventHandler(form_MouseUp);
            form.MouseWheel += new MouseEventHandler(form_MouseWheel);

            KeysDown = new List<Keys>();
            KeysPressed = new List<Keys>();
            KeysReleased = new List<Keys>();
            MousePoint = form.PointToClient(Cursor.Position);
            MouseWheelDelta = 0;
        }

        void form_KeyDown(object sender, KeyEventArgs e)
        {
            Keys key = e.KeyData & ~Keys.Shift;

            if (KeysDown.Contains(key) == false)
            {
                KeysPressed.Add(key);
                KeysDown.Add(key);
            }
        }

        void form_KeyUp(object sender, KeyEventArgs e)
        {
            Keys key = e.KeyData & ~Keys.Shift;

            KeysReleased.Add(key);
            KeysDown.Remove(key);
        }

        public void ClearKeyCache()
        {
            KeysPressed.Clear();
            KeysReleased.Clear();
            MousePressed = MouseButtons.None;
            MouseReleased = MouseButtons.None;
            MouseWheelDelta = 0;
        }

        void form_MouseDown(object sender, MouseEventArgs e)
        {
            MousePoint = e.Location;

            if (e.Button == MouseButtons.None)
                return;

            // Don't consider mouse clicks outside of the client area
            if (form.Focused == false || form.ClientRectangle.Contains(MousePoint) == false)
                return;

            if (e.Button == MouseButtons.Left)
            {
                if ((MouseDown & MouseButtons.Left) != MouseButtons.Left)
                {
                    MouseDown |= MouseButtons.Left;
                    MousePressed |= MouseButtons.Left;
                }
            }
            else if (e.Button == MouseButtons.Right)
            {
                if ((MouseDown & MouseButtons.Right) != MouseButtons.Right)
                {
                    MouseDown |= MouseButtons.Right;
                    MousePressed |= MouseButtons.Right;
                }
            }
        }

        void form_MouseMove(object sender, MouseEventArgs e)
        {
            MousePoint = e.Location;
        }

        void form_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                MouseDown &= ~MouseButtons.Left;
                MouseReleased |= MouseButtons.Left;
            }

            if (e.Button == MouseButtons.Right)
            {
                MouseDown &= ~MouseButtons.Right;
                MouseReleased |= MouseButtons.Right;
            }
        }

        void form_MouseWheel(object sender, MouseEventArgs e)
        {
            MouseWheelDelta = e.Delta;
        }
    }
}
