using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using System;

namespace DemoFramework
{
    public class FreeLook
    {
        private Input _input;
        private MouseController _mouseController;
        private bool _doUpdate;

        public Vector3 Eye { get; private set; }
        public Vector3 Target { get; private set; }
        public Vector3 Up { get; set; }

        public FreeLook(Input input)
        {
            Target = Vector3.UnitX;
            Up = Vector3.UnitY;
            _input = input;
            _mouseController = new MouseController(input);
        }

        public void SetEyeTarget(ref Vector3 eye, ref Vector3 target)
        {
            Eye = eye;
            Target = target;

            // Convert direction vector to Y-up for MouseController
            Matrix swapAxis = Matrix.CreateFromAxisAngle(Vector3.Cross(Up, Vector3.UnitY), Angle(Up, Vector3.UnitY));
            _mouseController.Vector = Vector3.Transform(Vector3.Normalize(eye - target), swapAxis);

            _doUpdate = true;
        }

        public bool Update(float frameDelta)
        {
            var ks = Keyboard.GetState();
            var pressedKeys = ks.GetPressedKeys();

            if (_mouseController.Update() == false && pressedKeys.Length == 0)
            {
                if (!_doUpdate)
                    return false;
                _doUpdate = false;
            }

            // MouseController is Y-up, convert to Up-up
            Matrix swapAxis = Matrix.CreateFromAxisAngle(Vector3.Cross(Vector3.UnitY, Up), Angle(Vector3.UnitY, Up));
            Vector3 direction = Vector3.Transform(-_mouseController.Vector, swapAxis);

            if (pressedKeys.Length != 0)
            {
                Vector3 relDirection = frameDelta * direction;
                float flySpeed = ks.IsKeyDown(Keys.LeftShift) ? 15 : 5;

                if (ks.IsKeyDown(Keys.W))
                {
                    Eye += flySpeed * relDirection;
                }
                if (ks.IsKeyDown(Keys.S))
                {
                    Eye -= flySpeed * relDirection;
                }

                if (ks.IsKeyDown(Keys.A))
                {
                    Eye -= Vector3.Cross(relDirection, Up);
                }
                if (ks.IsKeyDown(Keys.D))
                {
                    Eye += Vector3.Cross(relDirection, Up);
                }
            }
            Target = Eye + (Eye - Target).Length() * direction;

            return true;
        }

        // vertices must be normalized
        float Angle(Vector3 v1, Vector3 v2)
        {
            return (float)Math.Acos(Vector3.Dot(v1, v2));
        }
    }
}
