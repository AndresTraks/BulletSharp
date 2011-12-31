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

        Input input;
        MouseController mouseController;

        public FreeLook(Input input)
        {
            Target = Vector3.UnitX;
            Up = Vector3.UnitY;
            this.input = input;
            mouseController = new MouseController(input);
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
            if (mouseController.Update() == false && input.KeysDown.Count == 0)
                return false;

            Vector3 direction = Vector3.Normalize(-mouseController.Vector);

            if (input.KeysDown.Count != 0)
            {
                Vector3 relDirection = frameDelta * direction;
                float flySpeed = input.KeysDown.Contains(Keys.ShiftKey) ? 15 : 5;

                if (input.KeysDown.Contains(Keys.W))
                {
                    Eye += flySpeed * relDirection;
                }
                if (input.KeysDown.Contains(Keys.S))
                {
                    Eye -= flySpeed * relDirection;
                }

                if (input.KeysDown.Contains(Keys.A))
                {
                    Eye += Vector3.Cross(relDirection, Up);
                }
                if (input.KeysDown.Contains(Keys.D))
                {
                    Eye -= Vector3.Cross(relDirection, Up);
                }
            }
            Target = Eye + direction;

            Recalculate();

            return true;
        }

        void Recalculate()
        {
            View = Matrix.LookAtLH(Eye, Target, Up);
        }
    }
}
