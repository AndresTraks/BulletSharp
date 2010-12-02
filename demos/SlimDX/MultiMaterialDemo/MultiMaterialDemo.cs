using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace MultiMaterialDemo
{
    public class MultiMaterialDemo : Game
    {
        Vector3 eye = new Vector3(30, 20, 10);
        Vector3 target = new Vector3(0, 5, 0);
        DebugDrawModes debugMode = DebugDrawModes.DrawAabb | DebugDrawModes.DrawWireframe;

        Light light;

        protected override void OnInitializeDevice()
        {
            Form.ClientSize = new Size(Width, Height);
            Form.Text = "BulletSharp - Multimaterial Mesh Demo";

            DeviceSettings9 settings = new DeviceSettings9();
            settings.CreationFlags = CreateFlags.HardwareVertexProcessing;
            settings.Windowed = true;
            settings.MultisampleType = MultisampleType.FourSamples;
            try
            {
                InitializeDevice(settings);
            }
            catch
            {
                // Disable 4xAA if not supported
                settings.MultisampleType = MultisampleType.None;
                InitializeDevice(settings);
            }
        }

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();
            DebugDrawMode = debugMode;
            IsDebugDrawEnabled = true;

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 70;
            light.Position = new Vector3(10, 25, 10);
            light.Diffuse = Color.LemonChiffon;
            light.Attenuation0 = 1.0f;

            Freelook.SetEyeTarget(eye, target);

            Fps.Text = "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen\n" +
                "Space - Shoot box";

            base.OnInitialize();
        }

        protected override void OnResourceLoad()
        {
            base.OnResourceLoad();

            Device.SetLight(0, light);
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

                if ((string)body.UserObject == "Ground")
                    Device.Material = GroundMaterial;
                if (body.ActivationState == ActivationState.ActiveTag)
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
            MultiMaterialDemo game = new MultiMaterialDemo();
            game.Run();
            game.Dispose();
        }
    }
}
