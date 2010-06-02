using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.DirectInput;
using System;
using System.Drawing;

namespace SoftDemo
{
    class SoftDemo : Game
    {
        int Width = 1024, Height = 768;
        Color ambient = Color.Gray;
        Vector3 eye = new Vector3(60, 20, 30);
        Vector3 target = new Vector3(0, 0, 10);

        Mesh box, largeBox, groundBox, cylinder, sphere;
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
                largeBox.Dispose();
                cylinder.Dispose();
                sphere.Dispose();
                groundBox.Dispose();
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

            float size = physics.Scaling * 2;
            box = Mesh.CreateBox(Device, size, size, size);
            largeBox = Mesh.CreateBox(Device, 4 * size, size, 3 * size);
            groundBox = Mesh.CreateBox(Device, 100, 100, 100);
            cylinder = Mesh.CreateCylinder(Device, 1, 1, 4, 8, 1);
            sphere = Mesh.CreateSphere(Device, 1.5f, 12, 12);

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 75;
            light.Position = new Vector3(10, 25, 0);
            light.Falloff = 1.0f;
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

            Freelook.SetEyeTarget(eye, target);
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
                    physics.SetDebugDrawMode(Device, DebugDrawModes.DrawWireframe);
                else
                    physics.SetDebugDrawMode(Device, 0);
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
                if (colObj.ActivationState == ActivationState.ActiveTag)
                    Device.Material = activeMaterial;
                else
                    Device.Material = passiveMaterial;

                if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.SoftBodyShape)
                {
                    Mesh mesh = Physics.GetMeshFromSoftBody(Device, colObj);

                    if (mesh == null)
                        continue;

                    Device.SetTransform(TransformState.World, Matrix.Identity);
                    Device.SetRenderState(RenderState.CullMode, Cull.None);

                    mesh.DrawSubset(0);
                    mesh.Dispose();
                }
                else if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.BoxShape)
                {
                    RigidBody body = RigidBody.Upcast(colObj);
                    Device.SetTransform(TransformState.World, body.MotionState.WorldTransform);

                    if ((string)body.UserObject == "Ground")
                    {
                        Device.Material = groundMaterial;
                        groundBox.DrawSubset(0);
                    }
                    else
                    {
                        if ((string)body.UserObject == "LargeBox")
                            largeBox.DrawSubset(0);
                        else
                            box.DrawSubset(0);
                    }
                }
                else if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.SphereShape)
                {
                    RigidBody body = RigidBody.Upcast(colObj);
                    Device.SetTransform(TransformState.World, body.MotionState.WorldTransform);
                    sphere.DrawSubset(0);
                }
                else if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.CompoundShape)
                {
                    RigidBody body = RigidBody.Upcast(colObj);
                    Device.SetTransform(TransformState.World, body.MotionState.WorldTransform);
                    cylinder.DrawSubset(0);
                }
            }

            physics.DebugDrawWorld();

            Fps.OnRender(FramesPerSecond);

            Device.EndScene();
            Device.Present();
        }
    }
}
