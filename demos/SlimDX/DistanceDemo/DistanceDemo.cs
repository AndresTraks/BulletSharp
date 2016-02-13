using System;
using System.Drawing;
using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace DistanceDemo
{
    public class DistanceDemo : Game
    {
        Vector3 eye = new Vector3(10, 10, 5);
        Vector3 target = new Vector3(0, 8, 0);

        Light _light = new Light
        {
            Type = LightType.Point,
            Range = 70,
            Position = new Vector3(10, 25, 10),
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
            Form.Text = "BulletSharp - Convex Hull Distance Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            Physics = new Physics();
            IsDebugDrawEnabled = true;

            Freelook.SetEyeTarget(eye, target);

            base.OnInitialize();
        }

        protected override void OnResetDevice()
        {
            base.OnResetDevice();

            Device.SetLight(0, _light);
            Device.EnableLight(0, true);

            //Device.SetRenderState(RenderState.CullMode, Cull.None);
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

                if (Physics.HasDistanceResult)
                {
                    Device.Material = ActiveMaterial;
                    Device.SetTransform(TransformState.World, Matrix.Identity);
                    var vertices = new[]
                    {
                        new PositionColored(Physics.distanceFrom, -1),
                        new PositionColored(Physics.distanceTo, -1)
                    };
                    Device.DrawUserPrimitives(PrimitiveType.LineList, 1, vertices);
                }
            }

            DebugDrawWorld();

            Fps.Text = string.Format(
                "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen\n" +
                "Distance: {0}", Physics.distance.ToString("0.00"));
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

            using (DistanceDemo game = new DistanceDemo())
            {
                game.Run();
            }
        }
    }
}
