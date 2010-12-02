using System;
using System.Drawing;
using System.Windows.Forms;
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

        Light light;

        Physics Physics
        {
            get { return (Physics)PhysicsContext; }
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

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 70;
            light.Position = new Vector3(10, 25, 10);
            light.Diffuse = Color.LemonChiffon;
            light.Attenuation0 = 0.5f;

            Freelook.SetEyeTarget(eye, target);

            base.OnInitialize();
        }

        protected override void OnResourceLoad()
        {
            base.OnResourceLoad();

            Device.SetLight(0, light);
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

                if ((string)body.UserObject == "Ground")
                    Device.Material = GroundMaterial;
                else if (body.ActivationState == ActivationState.ActiveTag)
                    Device.Material = ActiveMaterial;
                else
                    Device.Material = PassiveMaterial;

                MeshFactory.Render(body.CollisionShape);

                if (Physics.HasDistanceResult)
                {
                    Device.Material = ActiveMaterial;
                    Device.SetTransform(TransformState.World, Matrix.Identity);
                    PositionColored[] vertices = new PositionColored[2];
                    vertices[0] = new PositionColored(Physics.distanceFrom, -1);
                    vertices[1] = new PositionColored(Physics.distanceTo, -1);
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
            DistanceDemo game = new DistanceDemo();

            if (game.TestLibraries() == false)
                return;

            game.Run();
            game.Dispose();
        }
    }
}
