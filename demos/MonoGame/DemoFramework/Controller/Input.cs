using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace DemoFramework
{
    public class Input
    {
        private MouseState _oldState;

        public bool LeftPressed { get { return _oldState.LeftButton == ButtonState.Pressed; } }
        public bool MiddlePressed { get { return _oldState.MiddleButton == ButtonState.Pressed; } }
        public bool RightPressed { get { return _oldState.RightButton == ButtonState.Pressed; } }

        public bool LeftClick { get; private set; }
        public bool MiddleClick { get; private set; }
        public bool RightClick { get; private set; }

        public Point MousePoint { get { return _oldState.Position; } }
        public int MouseWheelDelta { get; private set; }

        public void Update()
        {
            var newState = Mouse.GetState();
            LeftClick =
                newState.LeftButton == ButtonState.Pressed &&
                _oldState.LeftButton == ButtonState.Released;
            MiddleClick =
                newState.MiddleButton == ButtonState.Pressed &&
                _oldState.MiddleButton == ButtonState.Released;
            RightClick =
                newState.RightButton == ButtonState.Pressed &&
                _oldState.RightButton == ButtonState.Released;
            MouseWheelDelta = _oldState.ScrollWheelValue - newState.ScrollWheelValue;

            _oldState = newState;
        }
    }
}
