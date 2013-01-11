using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace DemoFramework
{
    public class Input
    {
        List<Keys> _keysPressed;
        List<Keys> _keysReleased;
        List<Keys> _keysDown;
        MouseButtons _mousePressed;
        MouseButtons _mouseReleased;
        MouseButtons _mouseDown;
        Point _mousePoint;
        int _mouseWheelDelta;

        public List<Keys> KeysPressed { get { return _keysPressed; } }
        public List<Keys> KeysReleased { get { return _keysReleased; } }
        public List<Keys> KeysDown { get { return _keysDown; } }
        public MouseButtons MousePressed { get { return _mousePressed; } }
        public MouseButtons MouseReleased { get { return _mouseReleased; } }
        public MouseButtons MouseDown { get { return _mouseDown; } }
        public Point MousePoint { get { return _mousePoint; } }
        public int MouseWheelDelta { get { return _mouseWheelDelta; } }

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

            _keysDown = new List<Keys>();
            _keysPressed = new List<Keys>();
            _keysReleased = new List<Keys>();
            _mousePoint = control.PointToClient(Cursor.Position);
            _mouseWheelDelta = 0;
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

            if (_keysDown.Contains(key) == false)
            {
                _keysPressed.Add(key);
                _keysDown.Add(key);
            }
        }

        void ControlOnKeyUp(object sender, KeyEventArgs e)
        {
            Keys key = e.KeyData & ~Keys.Shift;

            _keysReleased.Add(key);
            _keysDown.Remove(key);
        }

        public void ClearKeyCache()
        {
            _keysPressed.Clear();
            _keysReleased.Clear();
            _mousePressed = MouseButtons.None;
            _mouseReleased = MouseButtons.None;
            _mouseWheelDelta = 0;
        }

        void ControlOnMouseDown(object sender, MouseEventArgs e)
        {
            _mousePoint = e.Location;

            if (e.Button == MouseButtons.None)
                return;

            // Don't consider mouse clicks outside of the client area
            if (_control.ClientRectangle.Contains(_mousePoint) == false)
                return;

            //if (_control.Focused == false && _control.CanFocus)
            //    return;

            if (e.Button == MouseButtons.Left)
            {
                if ((_mouseDown & MouseButtons.Left) != MouseButtons.Left)
                {
                    _mouseDown |= MouseButtons.Left;
                    _mousePressed |= MouseButtons.Left;
                }
            }
            else if (e.Button == MouseButtons.Right)
            {
                if ((_mouseDown & MouseButtons.Right) != MouseButtons.Right)
                {
                    _mouseDown |= MouseButtons.Right;
                    _mousePressed |= MouseButtons.Right;
                }
            }
        }

        void ControlOnMouseMove(object sender, MouseEventArgs e)
        {
            _mousePoint = e.Location;
        }

        void ControlOnMouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                _mouseDown &= ~MouseButtons.Left;
                _mouseReleased |= MouseButtons.Left;
            }

            if (e.Button == MouseButtons.Right)
            {
                _mouseDown &= ~MouseButtons.Right;
                _mouseReleased |= MouseButtons.Right;
            }
        }

        void ControlOnMouseWheel(object sender, MouseEventArgs e)
        {
            _mouseWheelDelta = e.Delta;
        }
    }
}
