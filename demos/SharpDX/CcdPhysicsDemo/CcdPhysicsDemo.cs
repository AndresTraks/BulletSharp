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

        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - Basic Demo";
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
            CcdPhysicsDemo game = new CcdPhysicsDemo();

            if (game.TestLibraries() == false)
                return;

            game.Run();
            game.Dispose();
        }
    }
}
