using System;
using System.Windows.Forms;
using SharpDX;

namespace DemoFramework
{
    public class FreeLook
    {
        public Vector3 Eye { get; private set; }
        public Vector3 Target { get; private set; }
        public Matrix View { get; private set; }
        public Vector3 Up { get; set; }
        public Input Input { get; private set; }

        MouseController mouseController;

        public FreeLook(Input input)
        {
            Target = Vector3.UnitX;
            Up = Vector3.UnitY;
            Input = input;
            mouseController = new MouseController(Input);
            Recalculate();
        }

        public void SetEyeTarget(Vector3 eye, Vector3 target)
        {
            Eye = eye;
            this.Target = target;
            mouseController.Vector = eye - target;
            Recalculate();
        }

        public bool Update(float frameDelta)
        {
            if (mouseController.Update() == false && Input.KeysDown.Count == 0)
                return false;

            Vector3 direction = Vector3.Normalize(-mouseController.Vector);

            if (Input.KeysDown.Count != 0)
            {
                Vector3 relDirection = frameDelta * direction;
                Vector3 translation = Vector3.Zero;

                float flySpeed = Input.KeysDown.Contains(Keys.ShiftKey) ? 15 : 5;

                if (Input.KeysDown.Contains(Keys.W))
                {
                    translation = flySpeed * relDirection;
                }
                if (Input.KeysDown.Contains(Keys.S))
                {
                    translation -= flySpeed * relDirection;
                }

                if (Input.KeysDown.Contains(Keys.A))
                {
                    translation += GetSizewaysTranslation(relDirection, -Math.PI / 2);
                }
                if (Input.KeysDown.Contains(Keys.D))
                {
                    translation += GetSizewaysTranslation(relDirection, Math.PI / 2);
                }

                Eye += translation;
            }
            Target = Eye + direction;

            Recalculate();

            return true;
        }

        Vector3 GetSizewaysTranslation(Vector3 direction, double angle)
        {
            Vector3 sideways = Vector3.TransformCoordinate(direction, Matrix.RotationAxis(Up, (float)angle));
            sideways.Y = 0;
            return sideways;
        }

        void Recalculate()
        {
            View = Matrix.LookAtLH(Eye, Target, Up);
        }
    }
}
