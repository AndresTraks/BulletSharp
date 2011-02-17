using System;
using System.Windows.Forms;
using SlimDX;

namespace DemoFramework
{
    public class FreeLook
    {
        public Vector3 Eye { get; private set; }
        public Vector3 Target { get; private set; }
        public Matrix View { get; private set; }
        public Vector3 UpVector { get; private set; }
        public Input Input { get; set; }

        MouseController mouseController;

        public FreeLook(Input input)
        {
            Target = Vector3.UnitX;
            UpVector = Vector3.UnitY;
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
                    Vector3 sideways = Vector3.TransformCoordinate(relDirection, Matrix.RotationY((float)-Math.PI / 2));
                    translation += new Vector3(sideways.X, 0, sideways.Z);
                }
                if (Input.KeysDown.Contains(Keys.D))
                {
                    Vector3 sideways = Vector3.TransformCoordinate(relDirection, Matrix.RotationY((float)Math.PI / 2));
                    translation += new Vector3(sideways.X, 0, sideways.Z);
                }

                Eye += translation;
            }
            Target = Eye + direction;

            Recalculate();

            return true;
        }

        void Recalculate()
        {
            View = Matrix.LookAtLH(Eye, Target, UpVector);
        }
    }
}
