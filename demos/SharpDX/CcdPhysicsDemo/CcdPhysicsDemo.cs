using DemoFramework;
using SharpDX;
using System;
using System.Windows.Forms;

namespace CcdPhysicsDemo
{
    class CcdPhysicsDemo : Demo
    {
        Vector3 eye = new Vector3(0, 10, 40);
        Vector3 target = Vector3.Zero;

        Physics Physics
        {
            get { return (Physics)PhysicsContext; }
        }

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();

            Freelook.SetEyeTarget(eye, target);
            DemoText = "CCD enabled (P to disable)";
            Form.Text = "BulletSharp - CCD Demo";

            base.OnInitialize();
        }

        protected override void OnHandleInput()
        {
            if (Input.KeysPressed.Contains(Keys.P))
            {
                Physics.ToggleCcdMode();

                if (Physics.CcdMode)
                {
                    DemoText = "CCD enabled (P to disable)";
                }
                else
                {
                    DemoText = "CCD disabled (P to enable)";
                }
            }

            base.OnHandleInput();
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            if (LibraryTest.Test() == false)
                return;

            using (Demo demo = new CcdPhysicsDemo())
            {
                demo.Run();
            }
        }
    }
}
