using SlimDX;
using SlimDX.DirectInput;
using System;

namespace GameFramework
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

        Vector3 upVector = Vector3.UnitY;
        MouseController mouseController;

        public FreeLook()
        {
            Target = Vector3.UnitX;
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
            mouseController.Update(input);

            if (input.KeyboardState == null ||
                input.KeyboardState.PressedKeys.Count == 0)
            {
                Target = Eye - mouseController.Vector;
                Recalculate();
                return;
            }

            Vector3 translation = Vector3.Zero;
            Vector3 sideways = Vector3.Zero;
            bool hasSideways = false;
            Vector3 direction = Vector3.Normalize(-mouseController.Vector);
            direction *= frameDelta;

            float flySpeed = (input.KeyboardState.IsPressed(Key.LeftShift)) ? 10 : 2;

            if (input.KeyboardState.IsPressed(Key.W))
                translation = flySpeed * direction;
            if (input.KeyboardState.IsPressed(Key.S))
                translation -= flySpeed * direction;

            if (input.KeyboardState.IsPressed(Key.A))
            {
                sideways = Vector3.TransformCoordinate(direction, Matrix.RotationY((float)-Math.PI / 2));
                hasSideways = true;
            }
            if (input.KeyboardState.IsPressed(Key.D))
            {
                sideways += Vector3.TransformCoordinate(direction, Matrix.RotationY((float)Math.PI / 2));
                hasSideways = true;
            }
            
            // Sideways movement should not affect up-down movement(y=0)
            if (hasSideways)
            {
                sideways.Y = 0;
                translation += sideways;
            }

            Eye += translation;
            Target = Eye + direction;

            Recalculate();
        }

        void Recalculate()
        {
            View = Matrix.LookAtLH(Eye, Target, upVector);
        }
    }
}
