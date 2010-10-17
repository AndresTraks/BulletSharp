using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace SoftDemo
{
    class SoftDemo : Game
    {
        int Width = 1024, Height = 768;
        Color ambient = Color.Gray;
        Vector3 eye = new Vector3(20, 20, 80);
        Vector3 target = new Vector3(0, 0, 10);

        Light light;
        Material activeMaterial, passiveMaterial, groundMaterial, softBodyMaterial;
        GraphicObjectFactory mesh;

        Physics physics;

        public Device Device
        {
            get { return Device9; }
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (disposing)
            {
                mesh.Dispose();
            }
        }

        protected override void OnInitializeDevice()
        {
            Form.ClientSize = new Size(Width, Height);
            Form.Text = "BulletSharp - SoftBody Demo";

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
            physics = new Physics();
            physics.SetDebugDrawer(new PhysicsDebugDrawLineGathering(Device));
            //physics.SetDebugDrawMode(Device, DebugDrawModes.None);

            mesh = new GraphicObjectFactory(Device);

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 75;
            light.Position = new Vector3(10, 25, 0);
            light.Diffuse = Color.LemonChiffon;
            light.Attenuation0 = 1.0f;

            activeMaterial = new Material();
            activeMaterial.Diffuse = Color.Orange;
            activeMaterial.Ambient = ambient;

            passiveMaterial = new Material();
            passiveMaterial.Diffuse = Color.Red;
            passiveMaterial.Ambient = ambient;

            groundMaterial = new Material();
            groundMaterial.Diffuse = Color.Green;
            groundMaterial.Ambient = ambient;

            softBodyMaterial = new Material();
            softBodyMaterial.Diffuse = Color.White;
            softBodyMaterial.Ambient = ambient;

            Fps.Text = "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen\n" +
                "Space - Shoot box\n\n" +
                "B - Previous Demo\n" +
                "N - Next Demo";

            Freelook.SetEyeTarget(eye, target);
        }

        protected override void OnResourceLoad()
        {
            base.OnResourceLoad();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);
            Device.SetRenderState(RenderState.Ambient, ambient.ToArgb());

            Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, 0.1f, 150.0f);

            Device.SetRenderState(RenderState.CullMode, Cull.None);
            Device.SetTransform(TransformState.Projection, Projection);
        }

        protected override void OnUpdate()
        {
            base.OnUpdate();

            if (Input.KeysPressed.Contains(Keys.F3))
            {
                if (physics.IsDebugDrawEnabled == false)
                    physics.SetDebugDrawMode(Device, DebugDrawModes.DrawWireframe);
                else
                    physics.SetDebugDrawMode(Device, 0);
            }

            if (Input.KeysPressed.Contains(Keys.B))
            {
                physics.PreviousDemo();
            }

            if (Input.KeysPressed.Contains(Keys.N))
            {
                physics.NextDemo();
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
                if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.SoftBodyShape)
                {
                    if (physics.IsDebugDrawEnabled)
                        continue;

                    Device.Material = softBodyMaterial;
                    Device.SetTransform(TransformState.World, Matrix.Identity);
                }
                else
                {
                    RigidBody body = RigidBody.Upcast(colObj);

                    Device.SetTransform(TransformState.World, body.MotionState.WorldTransform);

                    if ((string)body.UserObject == "Ground")
                    {
                        Device.Material = groundMaterial;
                        mesh.Render(body);
                        continue;
                    }

                    if (colObj.ActivationState == ActivationState.ActiveTag)
                        Device.Material = activeMaterial;
                    else
                        Device.Material = passiveMaterial;
                }

                mesh.Render(colObj);
            }

            physics.DebugDrawWorld();

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
            SoftDemo game = new SoftDemo();

            if (game.TestLibraries() == false)
                return;

            game.Run();
            game.Dispose();
        }
    }
}
