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

        Control _control;
        public Control Control
        {
            get { return _control; }
            set
            {
                Release();
                _control = value;
                _control.KeyDown += ControlOnKeyDown;
                _control.KeyUp += ControlOnKeyUp;
                _control.MouseDown += ControlOnMouseDown;
                _control.MouseMove += ControlOnMouseMove;
                _control.MouseUp += ControlOnMouseUp;
                _control.MouseWheel += ControlOnMouseWheel;
            }
        }

        public Input(Control control)
        {
            Control = control;

            KeysDown = new List<Keys>();
            KeysPressed = new List<Keys>();
            KeysReleased = new List<Keys>();
            MousePoint = control.PointToClient(Cursor.Position);
            MouseWheelDelta = 0;
        }

        public void Release()
        {
            if (_control == null)
                return;

            _control.KeyDown -= ControlOnKeyDown;
            _control.KeyUp -= ControlOnKeyUp;
            _control.MouseDown -= ControlOnMouseDown;
            _control.MouseMove -= ControlOnMouseMove;
            _control.MouseUp -= ControlOnMouseUp;
            _control.MouseWheel -= ControlOnMouseWheel;

            _control = null;
        }

        void ControlOnKeyDown(object sender, KeyEventArgs e)
        {
            Keys key = e.KeyData & ~Keys.Shift;

            if (KeysDown.Contains(key) == false)
            {
                KeysPressed.Add(key);
                KeysDown.Add(key);
            }
        }

        void ControlOnKeyUp(object sender, KeyEventArgs e)
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

        void ControlOnMouseDown(object sender, MouseEventArgs e)
        {
            MousePoint = e.Location;

            if (e.Button == MouseButtons.None)
                return;

            // Don't consider mouse clicks outside of the client area
            if (_control.ClientRectangle.Contains(MousePoint) == false)
                return;

            //if (_control.Focused == false && _control.CanFocus)
            //    return;

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

        void ControlOnMouseMove(object sender, MouseEventArgs e)
        {
            MousePoint = e.Location;
        }

        void ControlOnMouseUp(object sender, MouseEventArgs e)
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

        void ControlOnMouseWheel(object sender, MouseEventArgs e)
        {
            MouseWheelDelta = e.Delta;
        }
    }
}
