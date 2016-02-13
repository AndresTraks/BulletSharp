using DemoFramework;
using SharpDX;
using System;

namespace BasicDemo
{
    class BasicDemo : Demo
    {
        Vector3 eye = new Vector3(30, 20, 10);
        Vector3 target = new Vector3(0, 5, -4);

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();

            Freelook.SetEyeTarget(eye, target);
            Form.Text = "BulletSharp - Basic Demo";

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

            using (Demo demo = new BasicDemo())
            {
                demo.Run();
            }
        }
    }
}
