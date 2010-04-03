using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.DirectInput;
using System;
using System.Drawing;

namespace CcdPhysicsDemo
{
    class CcdPhysicsDemo : Game
    {
        int Width = 1024, Height = 768;
        Color ambient = Color.Gray;
        Vector3 eye = new Vector3(0, 10, 40);
        Vector3 target = Vector3.Zero;

        Mesh box, cylinder, sphere, groundBox;
        Light light;
        Material activeMaterial, passiveMaterial, groundMaterial;
        
        Physics physics;

        public SlimDX.Direct3D9.Device Device
        {
            get { return Device9; }
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (disposing)
            {
                box.Dispose();
                cylinder.Dispose();
                groundBox.Dispose();
            }
        }

        protected override void OnInitializeDevice()
        {
            Form.ClientSize = new Size(Width, Height);
            Form.Text = "BulletSharp - Continuous Collision Detection Demo";

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

            float size = physics.CubeHalfExtents;
            box = Mesh.CreateBox(Device, size * 2, size * 2, size * 2);
            cylinder = Mesh.CreateCylinder(Device, size, size, size * 2, 16, 1);
            sphere = Mesh.CreateSphere(Device, 1.8f, 16, 16);
            groundBox = Mesh.CreateBox(Device, 400, 2, 400);

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 400;
            light.Position = new Vector3(10, 25, 10);
            light.Diffuse = Color.LemonChiffon;

            activeMaterial = new Material();
            activeMaterial.Diffuse = Color.Orange;
            activeMaterial.Ambient = ambient;

            passiveMaterial = new Material();
            passiveMaterial.Diffuse = Color.Red;
            passiveMaterial.Ambient = ambient;

            groundMaterial = new Material();
            groundMaterial.Diffuse = Color.Green;
            groundMaterial.Ambient = ambient;

            Fps.Text = "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen";

            if (physics.DoBenchmarkPyramids)
                Freelook.SetEyeTarget(new Vector3(40, 40, 40), Vector3.Zero);
            else
                Freelook.SetEyeTarget(eye, Vector3.Zero);
        }

        protected override void OnResourceLoad()
        {
            base.OnResourceLoad();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);
            Device.SetRenderState(RenderState.Ambient, ambient.ToArgb());

            Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, 0.1f, 150.0f);

            Device.SetTransform(TransformState.Projection, Projection);
        }

        protected override void OnUpdate()
        {
            base.OnUpdate();

            if (Input.KeyboardDown.Contains(Key.F3))
            {
                if (physics.IsDebugDrawEnabled == false)
                    physics.SetDebugDraw(Device, DebugDrawModes.DrawWireframe);
                else
                    physics.SetDebugDraw(Device, DebugDrawModes.None);
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
                if ((string)body.UserObject == "Ground")
                {
                    Device.SetTransform(TransformState.World, body.MotionState.WorldTransform);
                    Device.Material = groundMaterial;
                    groundBox.DrawSubset(0);
                    continue;
                }

                Matrix trans = Matrix.RotationX((float)Math.PI / 2);
                trans *= body.MotionState.WorldTransform;
                Device.SetTransform(TransformState.World, trans);

                if (colObj.ActivationState == ActivationState.ActiveTag)
                    Device.Material = activeMaterial;
                else
                    Device.Material = passiveMaterial;

                switch (colObj.CollisionShape.ShapeType)
                {
                    case BroadphaseNativeType.CylinderShape:
                        cylinder.DrawSubset(0);
                        break;
                    case BroadphaseNativeType.BoxShape:
                        box.DrawSubset(0);
                        break;
                    case BroadphaseNativeType.SphereShape:
                        sphere.DrawSubset(0);
                        break;
                }
            }

            physics.DebugDrawWorld();

            Fps.OnRender(FramesPerSecond);

            Device.EndScene();
            Device.Present();
        }
    }
}
