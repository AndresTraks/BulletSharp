using SlimDX;
using SlimDX.DirectInput;
using System;

namespace DemoFramework
{
    public class FreeLook
    {
        public Vector3 Eye
        {
            get;
            private set;
        }

        public Vector3 Target
        {
            get;
            private set;
        }

        public Matrix View
        {
            get;
            private set;
        }

        public Vector3 UpVector
        {
            get;
            private set;
        }

        Vector3 upVector = Vector3.UnitY;
        MouseController mouseController;

        public FreeLook()
        {
            Target = Vector3.UnitX;
            UpVector = Vector3.UnitY;
            mouseController = new MouseController();
            mouseController.Sensitivity = 0.005f;
            Recalculate();
        }

        public void SetEyeTarget(Vector3 eye, Vector3 target)
        {
            Eye = eye;
            this.Target = target;
            mouseController.Vector = eye - target;
            Recalculate();
        }

        public void Update(float frameDelta, Input input)
        {
            bool changed = mouseController.Update(input);

            if (changed == false && (input.KeyboardState == null ||
                input.KeyboardState.PressedKeys.Count == 0))
                return;

            Vector3 direction = Vector3.Normalize(-mouseController.Vector);

            if (input.KeyboardState.PressedKeys.Count != 0)
            {
                Vector3 relDirection = frameDelta * direction;

                Vector3 translation = Vector3.Zero;
                Vector3 sideways = Vector3.Zero;
                bool hasForward = false;
                bool hasSideways = false;

                float flySpeed = (input.KeyboardState.IsPressed(Key.LeftShift)) ? 15 : 5;

                if (input.KeyboardState.IsPressed(Key.W))
                {
                    translation = flySpeed * relDirection;
                    hasForward = true;
                }
                if (input.KeyboardState.IsPressed(Key.S))
                {
                    translation -= flySpeed * relDirection;
                    hasForward = true;
                }

                if (input.KeyboardState.IsPressed(Key.A))
                {
                    sideways = Vector3.TransformCoordinate(relDirection, Matrix.RotationY((float)-Math.PI / 2));
                    hasSideways = true;
                }
                if (input.KeyboardState.IsPressed(Key.D))
                {
                    sideways += Vector3.TransformCoordinate(relDirection, Matrix.RotationY((float)Math.PI / 2));
                    hasSideways = true;
                }

                if (hasForward || hasSideways)
                {
                    if (hasSideways)
                    {
                        // Sideways movement should not affect up-down movement(y=0)
                        sideways.Y = 0;
                        translation += sideways;
                    }
                    Eye += translation;
                }
            }
            Target = Eye + direction;

            Recalculate();
        }

        void Recalculate()
        {
            View = Matrix.LookAtLH(Eye, Target, UpVector);
        }
    }
}
