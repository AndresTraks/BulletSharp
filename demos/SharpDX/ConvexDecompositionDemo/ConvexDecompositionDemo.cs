using System;
using System.Windows.Forms;
using DemoFramework;
using SharpDX;

namespace ConvexDecompositionDemo
{
    class ConvexDecompositionDemo : Demo
    {
        Vector3 eye = new Vector3(30, 15, 20);
        Vector3 target = new Vector3(0, 0, -4);

        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - Convex Decomposition Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();

            Freelook.SetEyeTarget(eye, target);

            Info.Text = "Move using mouse and WASD+shift\n" +
                //"F3 - Toggle debug\n" +
                //"F11 - Toggle fullscreen\n" +
                "Space - Shoot box";

            base.OnInitialize();
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
            using (Demo demo = new ConvexDecompositionDemo())
            {
                demo.Run();
            }
        }
    }
}
