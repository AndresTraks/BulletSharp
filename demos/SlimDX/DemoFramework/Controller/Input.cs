using System;
using System.Drawing;
using System.Windows.Forms;
using SlimDX.DirectInput;
using System.Collections.Generic;

namespace DemoFramework
{
    public class Input : IDisposable
    {
        public KeyboardState KeyboardState
        {
            get;
            private set;
        }

        public MouseButtons MouseButtons
        {
            get;
            private set;
        }

        public Point MousePoint
        {
            get;
            private set;
        }

        // These are cleared every frame
        public MouseButtons MouseDown
        {
            get;
            private set;
        }

        public MouseButtons MouseUp
        {
            get;
            private set;
        }

        public List<Key> KeyboardDown
        {
            get;
            private set;
        }
        public List<Key> KeyboardUp
        {
            get;
            private set;
        }


        DirectInput dinput;
        Form form;

        Keyboard keyboard;
        Mouse mouse;

        public Input(Form form)
        {
            dinput = new DirectInput();
            this.form = form;

            MousePoint = Point.Empty;
            MouseButtons = MouseDown = MouseUp = MouseButtons.None;
            KeyboardDown = new List<Key>();

            try
            {
                keyboard = new Keyboard(dinput);
                keyboard.SetCooperativeLevel(form.Handle, CooperativeLevel.Foreground | CooperativeLevel.Nonexclusive);
                mouse = new Mouse(dinput);
                mouse.SetCooperativeLevel(form.Handle, CooperativeLevel.Foreground | CooperativeLevel.Nonexclusive);
            }
            catch (DirectInputException e)
            {
                MessageBox.Show(e.Message);
                return;
            }

            keyboard.Acquire();
            mouse.Properties.AxisMode = DeviceAxisMode.Absolute;
            mouse.Acquire();
            KeyboardUp = new List<Key>(keyboard.Capabilities.ButtonCount);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        void Dispose(bool isDisposing)
        {
            if (isDisposing == false)
                return;

            if (keyboard != null)
            {
                keyboard.Unacquire();
                keyboard.Dispose();
            }

            if (mouse != null)
            {
                mouse.Unacquire();
                mouse.Dispose();
            }

            if (dinput != null) dinput.Dispose();
        }

        public void OnResetDevice()
        {
            MousePoint = form.PointToClient(Cursor.Position);
        }

        public void GetCurrentKeyboardState()
        {
            if (keyboard.Acquire().IsFailure)
                return;

            KeyboardState keyboardStateNew = keyboard.GetCurrentState();
            if (keyboardStateNew == null)
                return;

            KeyboardDown.Clear();
            KeyboardUp.Clear();

            if (KeyboardState != null)
            {
                foreach (Key key in keyboardStateNew.PressedKeys)
                {
                    if (KeyboardState.IsPressed(key) == false)
                        KeyboardDown.Add(key);
                }
                foreach (Key key in KeyboardState.PressedKeys)
                {
                    if (keyboardStateNew.IsReleased(key) == true)
                        KeyboardUp.Add(key);
                }
            }

            KeyboardState = keyboardStateNew;
        }

        public void GetCurrentMouseState()
        {
            MousePoint = form.PointToClient(Cursor.Position);

            if (mouse.Acquire().IsFailure)
                return;

            if (mouse.Poll().IsFailure)
                return;

            MouseState ms = mouse.GetCurrentState();
            if (ms == null)
                return;

            MouseDown = MouseButtons.None;
            MouseUp = MouseButtons.None;

            if (ms.IsPressed(0))
            {
                if ((MouseButtons & MouseButtons.Left) != MouseButtons.Left)
                {
                    // Clicks outside the form don't matter to us
                    if (form.Bounds.Contains(Cursor.Position) == false)
                        return;

                    MouseDown |= MouseButtons.Left;
                    MouseButtons |= MouseButtons.Left;
                }
            }
            else
            {
                if ((MouseButtons & MouseButtons.Left) == MouseButtons.Left)
                {
                    MouseUp |= MouseButtons.Left;
                    MouseButtons ^= MouseButtons.Left;
                }
            }

            if (ms.IsPressed(1))
            {
                if ((MouseButtons & MouseButtons.Right) != MouseButtons.Right)
                {
                    MouseDown |= MouseButtons.Right;
                    MouseButtons |= MouseButtons.Right;
                }
            }
            else
            {
                if ((MouseButtons & MouseButtons.Right) == MouseButtons.Right)
                {
                    MouseUp |= MouseButtons.Right;
                    MouseButtons ^= MouseButtons.Right;
                }
            }
        }

        public void GetCurrentState()
        {
            GetCurrentKeyboardState();
            GetCurrentMouseState();
        }

        public static char KeyToChar(Key key, bool shift, out bool isChar)
        {
            isChar = true;
            switch (key)
            {
                case Key.A: return shift ? 'A' : 'a';
                case Key.B: return shift ? 'B' : 'b';
                case Key.C: return shift ? 'C' : 'c';
                case Key.D: return shift ? 'D' : 'd';
                case Key.E: return shift ? 'E' : 'e';
                case Key.F: return shift ? 'F' : 'f';
                case Key.G: return shift ? 'G' : 'g';
                case Key.H: return shift ? 'H' : 'h';
                case Key.I: return shift ? 'I' : 'i';
                case Key.J: return shift ? 'J' : 'j';
                case Key.K: return shift ? 'K' : 'k';
                case Key.L: return shift ? 'L' : 'l';
                case Key.M: return shift ? 'M' : 'm';
                case Key.N: return shift ? 'N' : 'n';
                case Key.O: return shift ? 'O' : 'o';
                case Key.P: return shift ? 'P' : 'p';
                case Key.Q: return shift ? 'Q' : 'q';
                case Key.R: return shift ? 'R' : 'r';
                case Key.S: return shift ? 'S' : 's';
                case Key.T: return shift ? 'T' : 't';
                case Key.U: return shift ? 'U' : 'u';
                case Key.V: return shift ? 'V' : 'v';
                case Key.W: return shift ? 'W' : 'w';
                case Key.X: return shift ? 'X' : 'x';
                case Key.Y: return shift ? 'Y' : 'y';
                case Key.Z: return shift ? 'Z' : 'z';
                case Key.D0: return shift ? '=' : '0';
                case Key.D1: return shift ? '!' : '1';
                case Key.D2: return shift ? '"' : '2';
                case Key.D3: return shift ? '#' : '3';
                case Key.D4: return shift ? '$' : '4';
                case Key.D5: return shift ? '%' : '5';
                case Key.D6: return shift ? '&' : '6';
                case Key.D7: return shift ? '/' : '7';
                case Key.D8: return shift ? '(' : '8';
                case Key.D9: return shift ? ')' : '9';
                case Key.NumberPad0: return '0';
                case Key.NumberPad1: return '1';
                case Key.NumberPad2: return '2';
                case Key.NumberPad3: return '3';
                case Key.NumberPad4: return '4';
                case Key.NumberPad5: return '5';
                case Key.NumberPad6: return '6';
                case Key.NumberPad7: return '7';
                case Key.NumberPad8: return '8';
                case Key.NumberPad9: return '9';
                case Key.Space: return ' ';
                case Key.Comma: return ',';
                case Key.Period: return '.';
                case Key.Apostrophe: return '\'';
            }
            isChar = false;
            switch (key)
            {
                case Key.Tab: return '\t';
                case Key.Return: return '\r';
                case Key.Backspace: return '\b';
                case Key.Escape: return '\x1B';  //VK_ESCAPE
                case Key.PageUp: return '\x21';  //VK_PRIOR
                case Key.PageDown: return '\x22';  //VK_NEXT
                case Key.End: return '\x23';  //VK_END
                case Key.Home: return '\x24';  //VK_HOME
                case Key.LeftArrow: return '\x25';  //VK_LEFT
                case Key.UpArrow: return '\x26';  //VK_UP
                case Key.RightArrow: return '\x27';  //VK_RIGHT
                case Key.DownArrow: return '\x28';  //VK_DOWN
                case Key.Insert: return '\x2D';  //VK_INSERT
                case Key.Delete: return '\x2E';  //VK_DELETE
            }
            return '\0';
        }
    }
}
