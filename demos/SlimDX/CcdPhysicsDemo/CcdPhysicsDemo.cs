using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace CcdPhysicsDemo
{
    public class CcdPhysicsDemo : Game
    {
        Vector3 eye = new Vector3(0, 10, 40);
        Vector3 target = Vector3.Zero;

        Light _light = new Light
        {
            Type = LightType.Point,
            Range = 400,
            Position = new Vector3(10, 25, 10),
            Diffuse = Color.LemonChiffon,
            Attenuation0 = 1.0f
        };

        string fpsText = "Move using mouse and WASD+shift\n" +
            "F3 - Toggle debug\n" +
            "F11 - Toggle fullscreen\n" +
            "Space - Shoot box";

        Physics Physics
        {
            get { return PhysicsContext as Physics; }
            set { PhysicsContext = value; }
        }

        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - Continuous Collision Detection Demo";

            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            Physics = new Physics();

            Fps.Text = fpsText + "\nCCD enabled (P to disable)";

            Freelook.SetEyeTarget(eye, target);

            base.OnInitialize();
        }

        protected override void OnHandleInput()
        {
            if (Input.KeysPressed.Contains(Keys.P))
            {
                Physics.ToggleCcdMode();

                if (Physics.CcdMode)
                {
                    Fps.Text = fpsText + "\nCCD enabled (P to disable)";
                }
                else
                {
                    Fps.Text = fpsText + "\nCCD disabled (P to enable)";
                }
            }

            base.OnHandleInput();
        }

        protected override void OnResetDevice()
        {
            base.OnResetDevice();

            Device.SetLight(0, _light);
            Device.EnableLight(0, true);
        }

        protected override void OnRender()
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
            Device.BeginScene();

            Device.SetTransform(TransformState.View, Freelook.View);

            foreach (RigidBody body in PhysicsContext.World.CollisionObjectArray)
            {
                Device.SetTransform(TransformState.World, body.MotionState.WorldTransform);
                RenderWithMaterial(body);
            }

            DebugDrawWorld();

            Fps.OnRender(FramesPerSecond);

            Device.EndScene();
            Device.Present();
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            if (LibraryTest.Test() == false)
                return;

            using (CcdPhysicsDemo game = new CcdPhysicsDemo())
            {
                game.Run();
            }
        }
    }
}
