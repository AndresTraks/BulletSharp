using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using SlimDX.RawInput;

namespace DemoFramework
{
    public class Input
    {
        public List<Keys> KeysPressed { get; private set; }
        public List<Keys> KeysReleased { get; private set; }
        public List<Keys> KeysDown { get; private set; }

        public MouseButtonFlags MousePressed { get; private set; }
        public MouseButtonFlags MouseDown { get; private set; }
        public Point MousePoint { get; private set; }
        public int MouseWheelDelta { get; private set; }

        Point _mouseDelta;
        public Point MouseDelta { get { return _mouseDelta; } }

        Form form;

        public Input(Form form)
        {
            this.form = form;

            KeysDown = new List<Keys>();
            KeysPressed = new List<Keys>();
            KeysReleased = new List<Keys>();
            MousePoint = form.PointToClient(Cursor.Position);
            MouseWheelDelta = 0;
        }

        public void ClearKeyCache()
        {
            KeysPressed.Clear();
            KeysReleased.Clear();
            MousePressed = MouseButtonFlags.None;
            MouseWheelDelta = 0;
            _mouseDelta.X = 0;
            _mouseDelta.Y = 0;
        }

        public void Device_KeyboardInput(object sender, KeyboardInputEventArgs e)
        {
            if (e.State == KeyState.Pressed)
            {
                if (KeysDown.Contains(e.Key) == false)
                {
                    KeysPressed.Add(e.Key);
                    KeysDown.Add(e.Key);
                }
            }
            else if (e.State == KeyState.Released)
            {
                KeysReleased.Add(e.Key);
                KeysDown.Remove(e.Key);
            }
        }

        public void Device_MouseInput(object sender, MouseInputEventArgs e)
        {
            MousePoint = form.PointToClient(Cursor.Position);
            _mouseDelta.X = e.X;
            _mouseDelta.Y = e.Y;
            MouseWheelDelta = e.WheelDelta;

            if (e.ButtonFlags == MouseButtonFlags.None)
                return;

            MouseButtonFlags mouseFlags = e.ButtonFlags;

            // Don't consider mouse clicks outside of the client area
            if (form.Focused == false || form.ClientRectangle.Contains(MousePoint) == false)
                mouseFlags &= ~(MouseButtonFlags.LeftDown | MouseButtonFlags.RightDown);

            // Find the pressed/unpressed keys
            if (mouseFlags == MouseButtonFlags.LeftDown)
            {
                if ((MouseDown & MouseButtonFlags.LeftDown) != MouseButtonFlags.LeftDown)
                {
                    MouseDown |= MouseButtonFlags.LeftDown;
                    MousePressed |= MouseButtonFlags.LeftDown;
                }
            }
            else if (mouseFlags == MouseButtonFlags.LeftUp)
            {
                MouseDown &= ~MouseButtonFlags.LeftDown;
                MousePressed |= MouseButtonFlags.LeftUp;
            }

            if (mouseFlags == MouseButtonFlags.RightDown)
            {
                if ((MouseDown & MouseButtonFlags.RightDown) != MouseButtonFlags.RightDown)
                {
                    MouseDown |= MouseButtonFlags.RightDown;
                    MousePressed |= MouseButtonFlags.RightDown;
                }
            }
            else if (mouseFlags == MouseButtonFlags.RightUp)
            {
                MouseDown &= ~MouseButtonFlags.RightDown;
                MousePressed |= MouseButtonFlags.RightUp;
            }
        }

        public static char KeyToChar(Keys key, bool shift, out bool isChar)
        {
            isChar = true;
            switch (key)
            {
                case Keys.A: return shift ? 'A' : 'a';
                case Keys.B: return shift ? 'B' : 'b';
                case Keys.C: return shift ? 'C' : 'c';
                case Keys.D: return shift ? 'D' : 'd';
                case Keys.E: return shift ? 'E' : 'e';
                case Keys.F: return shift ? 'F' : 'f';
                case Keys.G: return shift ? 'G' : 'g';
                case Keys.H: return shift ? 'H' : 'h';
                case Keys.I: return shift ? 'I' : 'i';
                case Keys.J: return shift ? 'J' : 'j';
                case Keys.K: return shift ? 'K' : 'k';
                case Keys.L: return shift ? 'L' : 'l';
                case Keys.M: return shift ? 'M' : 'm';
                case Keys.N: return shift ? 'N' : 'n';
                case Keys.O: return shift ? 'O' : 'o';
                case Keys.P: return shift ? 'P' : 'p';
                case Keys.Q: return shift ? 'Q' : 'q';
                case Keys.R: return shift ? 'R' : 'r';
                case Keys.S: return shift ? 'S' : 's';
                case Keys.T: return shift ? 'T' : 't';
                case Keys.U: return shift ? 'U' : 'u';
                case Keys.V: return shift ? 'V' : 'v';
                case Keys.W: return shift ? 'W' : 'w';
                case Keys.X: return shift ? 'X' : 'x';
                case Keys.Y: return shift ? 'Y' : 'y';
                case Keys.Z: return shift ? 'Z' : 'z';
                case Keys.D0: return shift ? '=' : '0';
                case Keys.D1: return shift ? '!' : '1';
                case Keys.D2: return shift ? '"' : '2';
                case Keys.D3: return shift ? '#' : '3';
                case Keys.D4: return shift ? '$' : '4';
                case Keys.D5: return shift ? '%' : '5';
                case Keys.D6: return shift ? '&' : '6';
                case Keys.D7: return shift ? '/' : '7';
                case Keys.D8: return shift ? '(' : '8';
                case Keys.D9: return shift ? ')' : '9';
                case Keys.NumPad0: return '0';
                case Keys.NumPad1: return '1';
                case Keys.NumPad2: return '2';
                case Keys.NumPad3: return '3';
                case Keys.NumPad4: return '4';
                case Keys.NumPad5: return '5';
                case Keys.NumPad6: return '6';
                case Keys.NumPad7: return '7';
                case Keys.NumPad8: return '8';
                case Keys.NumPad9: return '9';
                case Keys.Space: return ' ';
                case Keys.Oemcomma: return ',';
                case Keys.OemPeriod: return '.';
                case Keys.OemQuestion: return '?';
            }
            isChar = false;
            switch (key)
            {
                case Keys.Tab: return '\t';
                case Keys.Return: return '\r';
                case Keys.Back: return '\b';
                case Keys.Escape: return '\x1B';  //VK_ESCAPE
                case Keys.PageUp: return '\x21';  //VK_PRIOR
                case Keys.PageDown: return '\x22';  //VK_NEXT
                case Keys.End: return '\x23';  //VK_END
                case Keys.Home: return '\x24';  //VK_HOME
                case Keys.Left: return '\x25';  //VK_LEFT
                case Keys.Up: return '\x26';  //VK_UP
                case Keys.Right: return '\x27';  //VK_RIGHT
                case Keys.Down: return '\x28';  //VK_DOWN
                case Keys.Insert: return '\x2D';  //VK_INSERT
                case Keys.Delete: return '\x2E';  //VK_DELETE
            }
            return '\0';
        }
    }
}
