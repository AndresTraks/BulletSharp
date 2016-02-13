using System;
using System.Drawing;
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

        Light _light = new Light
        {
            Type = LightType.Point,
            Range = 70,
            Position = new Vector3(10, 25, 10),
            Diffuse = Color.LemonChiffon,
            Attenuation0 = 1.0f
        };

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

            Freelook.SetEyeTarget(eye, target);

            Fps.Text = "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen\n" +
                "Space - Shoot box";

            base.OnInitialize();
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

            using (MultiMaterialDemo game = new MultiMaterialDemo())
            {
                game.Run();
            }
        }
    }
}
