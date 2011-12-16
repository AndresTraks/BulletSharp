using System;
using System.Windows.Forms;
using DemoFramework;
using SharpDX;

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

        string infoText = "Move using mouse and WASD+shift\n" +
            //"F3 - Toggle debug\n" +
            //"F11 - Toggle fullscreen\n" +
            "Space - Shoot box";

        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - CCD Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();

            Freelook.SetEyeTarget(eye, target);

            Info.Text = infoText + "\nCCD enabled (P to disable)";

            base.OnInitialize();
        }

        protected override void OnHandleInput()
        {
            if (Input.KeysPressed.Contains(Keys.P))
            {
                Physics.ToggleCcdMode();
                GetMeshFactory().Clear();

                if (Physics.CcdMode)
                {
                    Info.Text = infoText + "\nCCD enabled (P to disable)";
                }
                else
                {
                    Info.Text = infoText + "\nCCD disabled (P to enable)";
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

            RunDemo();
        }

        static void RunDemo()
        {
            using (Demo demo = new CcdPhysicsDemo())
            {
                demo.Run();
            }
        }
    }
}
