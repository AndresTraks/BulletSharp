using System;
using System.Drawing;
using System.Timers;
using BulletSharp;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.Windows;

namespace SimplestDemo
{
    class SimplestDemo
    {
        int Width = 1024, Height = 768;
        Color ambient = Color.Gray;
        Vector3 eye = new Vector3(20, 15, 10);
        Vector3 target = new Vector3(0, 5, 0);

        Mesh box, groundBox;
        Light light;
        Material boxMaterial, groundMaterial;

        Physics physics;
        RenderForm Form;
        Device Device;
        Direct3D direct3D;

        bool isFormClosed = false;

        public SimplestDemo()
        {
            Form = new RenderForm();
            Form.Text = "BulletSharp - Simplest Demo";
            Form.ClientSize = new Size(Width, Height);
            Form.Closed += (o, args) => { isFormClosed = true; };

            Initialize();

            OnResourceLoad();

            Timer timer = new Timer(1.0f / 60.0f);
            timer.Elapsed += (o, args) => { physics.Update(1.0f / 60.0f); };
            timer.Enabled = true;

            MessagePump.Run(Form, () =>
            {
                if (isFormClosed)
                    return;

                Render();
            });
        }

        public void Dispose()
        {
            box.Dispose();
            groundBox.Dispose();
            Device.Dispose();
            direct3D.Dispose();
        }

        void InitializeDevice()
        {
            PresentParameters pp = new PresentParameters()
            {
                BackBufferWidth = Form.ClientSize.Width,
                BackBufferHeight = Form.ClientSize.Height,
                DeviceWindowHandle = Form.Handle
            };

            direct3D = new Direct3D();
            try
            {
                Device = new Device(direct3D, 0, DeviceType.Hardware, Form.Handle, CreateFlags.HardwareVertexProcessing, pp);
            }
            catch
            {
                Device = new Device(direct3D, 0, DeviceType.Hardware, Form.Handle, CreateFlags.SoftwareVertexProcessing, pp);
            }
        }

        void Initialize()
        {
            InitializeDevice();

            physics = new Physics();

            // Create meshes to draw
            box = Mesh.CreateBox(Device, 2, 2, 2);
            groundBox = Mesh.CreateBox(Device, 100, 2, 100);

            light = new Light
            {
                Type = LightType.Point,
                Range = 70,
                Position = new Vector3(10, 25, 10),
                Diffuse = Color.LemonChiffon,
                Attenuation0 = 1.0f
            };

            boxMaterial = new Material();
            boxMaterial.Diffuse = Color.Orange;
            boxMaterial.Ambient = ambient;

            groundMaterial = new Material();
            groundMaterial.Diffuse = Color.Green;
            groundMaterial.Ambient = ambient;
        }

        void OnResourceLoad()
        {
            Device.SetLight(0, light);
            Device.EnableLight(0, true);
            Device.SetRenderState(RenderState.Ambient, ambient.ToArgb());
        }

        void Render()
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
            Device.BeginScene();

            Matrix projection = Matrix.PerspectiveFovLH((float)Math.PI / 2, (float)Form.ClientSize.Width / (float)Form.ClientSize.Height, 0.1f, 150.0f);
            Device.SetTransform(TransformState.Projection, projection);

            Matrix view = Matrix.LookAtLH(eye, target, Vector3.UnitY);
            Device.SetTransform(TransformState.View, view);

            foreach (RigidBody body in physics.World.CollisionObjectArray)
            {
                Device.SetTransform(TransformState.World, body.WorldTransform);

                if ((string)body.UserObject == "Ground")
                {
                    Device.Material = groundMaterial;
                    groundBox.DrawSubset(0);
                    continue;
                }

                Device.Material = boxMaterial;
                box.DrawSubset(0);
            }

            Device.EndScene();
            Device.Present();
        }
    }
}
