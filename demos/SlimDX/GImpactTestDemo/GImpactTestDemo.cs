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

        Light light;

        Physics Physics
        {
            get { return (Physics)PhysicsContext; }
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

            light = new Light();
            light.Type = LightType.Directional;
            light.Range = 500;
            light.Position = new Vector3(50, 50, 0);
            light.Direction = new Vector3(0, -1, 0);
            light.Diffuse = Color.LemonChiffon;
            light.Attenuation0 = 0.5f;

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

            Device.SetLight(0, light);
            Device.EnableLight(0, true);
        }

        protected override void OnUpdate()
        {
            base.OnUpdate();

            if (Input.KeysPressed.Contains(Keys.OemPeriod))
            {
                Physics.ShootTrimesh(Freelook.Eye, Freelook.Eye - Freelook.Target);
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

                if ((string)body.UserObject == "Ground")
                    Device.Material = GroundMaterial;
                else if (body.ActivationState == ActivationState.ActiveTag)
                    Device.Material = ActiveMaterial;
                else
                    Device.Material = PassiveMaterial;

                MeshFactory.Render(body.CollisionShape);
            }

            DebugDrawWorld();

            Fps.OnRender(FramesPerSecond);

            Device.EndScene();
            Device.Present();
        }

        public Device Device
        {
            get { return Device9; }
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            GImpactTestDemo game = new GImpactTestDemo();

            if (game.TestLibraries() == false)
                return;

            game.Run();
            game.Dispose();
        }
    }
}
