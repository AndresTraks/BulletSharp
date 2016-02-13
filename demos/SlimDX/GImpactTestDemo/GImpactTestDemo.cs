using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace GImpactTestDemo
{
    public class GImpactTestDemo : Game
    {
        Vector3 eye = new Vector3(0, 10, 50);
        Vector3 target = new Vector3(0, 10, -4);
        DebugDrawModes debugMode = DebugDrawModes.DrawAabb | DebugDrawModes.DrawWireframe;

        Light _light = new Light
        {
            Type = LightType.Directional,
            Range = 500,
            Position = new Vector3(50, 50, 0),
            Direction = new Vector3(0, -1, 0),
            Diffuse = Color.LemonChiffon,
            Attenuation0 = 0.5f
        };

        Physics Physics
        {
            get { return PhysicsContext as Physics; }
            set { PhysicsContext = value; }
        }

        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - GImpact Test Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            Physics = new Physics();
            DebugDrawMode = debugMode;

            FarPlane = 800f;
            Freelook.SetEyeTarget(eye, target);

            Fps.Text = "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen\n" +
                "Space - Shoot box\n" +
                ". - Shoot Bunny";

            base.OnInitialize();
        }

        protected override void OnResetDevice()
        {
            base.OnResetDevice();

            Device.SetLight(0, _light);
            Device.EnableLight(0, true);
        }

        protected override void OnUpdate()
        {
            base.OnUpdate();

            if (Input.KeysPressed.Contains(Keys.OemPeriod))
            {
                Physics.ShootTrimesh(Freelook.Eye, Freelook.Target);
            }
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

            using (GImpactTestDemo game = new GImpactTestDemo())
            {
                game.Run();
            }
        }
    }
}
