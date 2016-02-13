﻿using System;
using System.Drawing;
using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace SerializeDemo
{
    public class SerializeDemo : Game
    {
        Vector3 eye = new Vector3(30, 20, 10);
        Vector3 target = new Vector3(0, 5, 0);
        DebugDrawModes debugMode = DebugDrawModes.DrawWireframe |
            DebugDrawModes.DrawConstraints | DebugDrawModes.DrawConstraintLimits;

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
            Form.Text = "BulletSharp - Serialize Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();
            DebugDrawMode = debugMode;

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
                Device.SetTransform(TransformState.World, body.WorldTransform);
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

            using (SerializeDemo game = new SerializeDemo())
            {
                game.Run();
            }
        }
    }
}
