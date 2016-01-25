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

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();

            Freelook.SetEyeTarget(eye, target);
            Form.Text = "BulletSharp - Convex Decomposition Demo";

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

            using (Demo demo = new ConvexDecompositionDemo())
            {
                demo.Run();
            }
        }
    }
}
