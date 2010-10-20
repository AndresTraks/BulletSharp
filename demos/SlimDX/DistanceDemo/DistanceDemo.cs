using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace DistanceDemo
{
    class DistanceDemo : Game
    {
        int Width = 1024, Height = 768;
        Vector3 eye = new Vector3(10, 10, 5);
        Vector3 target = new Vector3(0, 8, 0);
        Color ambient = Color.Gray;
        DebugDrawModes debugMode = DebugDrawModes.DrawWireframe;

        Light light;
        Material activeMaterial, passiveMaterial, groundMaterial;
        GraphicObjectFactory mesh;
        Physics physics;

        protected override void OnInitializeDevice()
        {
            Form.ClientSize = new Size(Width, Height);
            Form.Text = "BulletSharp - Convex Hull Distance Demo";

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
            mesh = new GraphicObjectFactory(Device);

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 70;
            light.Position = new Vector3(10, 25, 10);
            light.Diffuse = Color.LemonChiffon;
            light.Attenuation0 = 0.5f;

            activeMaterial = new Material();
            activeMaterial.Diffuse = Color.Orange;
            activeMaterial.Ambient = ambient;

            passiveMaterial = new Material();
            passiveMaterial.Diffuse = Color.Red;
            passiveMaterial.Ambient = ambient;

            groundMaterial = new Material();
            groundMaterial.Diffuse = Color.Green;
            groundMaterial.Ambient = ambient;

            Freelook.SetEyeTarget(eye, target);

            physics = new Physics();
            physics.SetDebugDrawMode(Device, debugMode);
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (disposing)
            {
                mesh.Dispose();
            }
        }

        protected override void OnResourceLoad()
        {
            base.OnResourceLoad();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);
            Device.SetRenderState(RenderState.Ambient, ambient.ToArgb());

            Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, 0.1f, 150.0f);
            Device.SetTransform(TransformState.Projection, Projection);

            //Device.SetRenderState(RenderState.CullMode, Cull.None);
        }

        protected override void OnUpdate()
        {
            base.OnUpdate();

            if (Input.KeysPressed.Contains(Keys.F3))
            {
                if (physics.IsDebugDrawEnabled == false)
                    physics.SetDebugDrawMode(Device, DebugDrawModes.DrawWireframe);
                else
                    physics.SetDebugDrawMode(Device, DebugDrawModes.None);
            }

            InputUpdate(Freelook.Eye, Freelook.Target, physics);
            physics.Update(FrameDelta);
        }

        protected override void OnRender()
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
            Device.BeginScene();

            Device.SetTransform(TransformState.View, Freelook.View);

            foreach (CollisionObject colObj in physics.World.CollisionObjectArray)
            {
                RigidBody body = RigidBody.Upcast(colObj);
                Device.SetTransform(TransformState.World, body.WorldTransform);

                if ((string)colObj.UserObject == "Ground")
                    Device.Material = groundMaterial;
                else if (colObj.ActivationState == ActivationState.ActiveTag)
                    Device.Material = activeMaterial;
                else
                    Device.Material = passiveMaterial;

                mesh.Render(body.CollisionShape, Matrix.Identity);

                if (physics.HasDistanceResult)
                {
                    Device.Material = activeMaterial;
                    Device.SetTransform(TransformState.World, Matrix.Identity);
                    PositionColored[] vertices = new PositionColored[2];
                    vertices[0] = new PositionColored(physics.distanceFrom, -1);
                    vertices[1] = new PositionColored(physics.distanceTo, -1);
                    Device.DrawUserPrimitives(PrimitiveType.LineList, 1, vertices);
                }
            }

            physics.DebugDrawWorld();

            Fps.Text = "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen\n";
            Fps.Text += "Distance: " + physics.distance.ToString("0.00");
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
