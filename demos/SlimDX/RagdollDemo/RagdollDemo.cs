// Original RagdollDemo by written by Marten Svanfeldt
// Copyright (c) 2007 Starbreeze Studios

using System;
using System.Drawing;
using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace RagdollDemo
{
    public class RagdollDemo : Game
    {
        Vector3 eye = new Vector3(1, 1, 10);
        Vector3 target = new Vector3(0, 1, 0);

        Light _light = new Light
        {
            Type = LightType.Point,
            Range = 150,
            Position = new Vector3(10, 25, 10),
            Diffuse = Color.LemonChiffon,
            Attenuation0 = 0.9f
        };

        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - Ragdoll Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();

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

            RunGame();
        }

        static void RunGame()
        {
            using (RagdollDemo game = new RagdollDemo())
            {
                game.Run();
            }
        }
    }
}
