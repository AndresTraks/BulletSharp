using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.DirectInput;
using System;
using System.Drawing;

namespace VehicleDemo
{
    class VehicleDemo : Game
    {
        int Width = 1024, Height = 768;
        Color ambient = Color.Gray;
        Vector3 eye = new Vector3(5, 15, 5);
        Vector3 target = Vector3.Zero;
        int ViewMode = 1;

        Mesh wheel, chassis;
        Light light;
        Material wheelMaterial, bodyMaterial, groundMaterial;
        public Mesh ground;

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
                wheel.Dispose();
                chassis.Dispose();
                ground.Dispose();
            }
        }

        protected override void OnInitializeDevice()
        {
            Form.ClientSize = new Size(Width, Height);
            Form.Text = "BulletSharp - Vehicle Demo";

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
            physics = new Physics(this);

            wheel = Mesh.CreateCylinder(Device, physics.wheelRadius, physics.wheelRadius, physics.wheelWidth, 10, 10);
            chassis = Mesh.CreateBox(Device, 2.0f, 1.0f, 4.0f);
            ground.ComputeNormals();

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 200;
            light.Position = new Vector3(10, 25, 10);
            light.Diffuse = Color.LemonChiffon;
            light.Attenuation1 = 0.03f;

            //light.Type = LightType.Directional;
            //light.Direction = new Vector3(-1, -1, -1);

            wheelMaterial = new Material();
            wheelMaterial.Diffuse = Color.Black;
            wheelMaterial.Ambient = ambient;

            bodyMaterial = new Material();
            bodyMaterial.Diffuse = Color.Orange;
            bodyMaterial.Ambient = ambient;

            groundMaterial = new Material();
            groundMaterial.Diffuse = Color.Green;
            groundMaterial.Ambient = ambient;
            groundMaterial.Emissive = Color.Green;

            Fps.Text = "F2 - Toggle view mode: Tracking\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen";

            Freelook.SetEyeTarget(new Vector3(30, 10, 0), target);
        }

        protected override void OnResourceLoad()
        {
            base.OnResourceLoad();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);
            Device.SetRenderState(RenderState.Ambient, ambient.ToArgb());

            Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, 0.1f, 400.0f);

            Device.SetTransform(TransformState.Projection, Projection);
        }

        protected override void OnUpdate()
        {
            base.OnUpdate();

            InputUpdate(Freelook.Eye, Freelook.Target, physics);

            if (Input.KeyboardDown.Contains(Key.F2))
            {
                ViewMode++;
                if (ViewMode > 3) ViewMode = 1;

                string viewMode = "";
                switch (ViewMode)
                {
                    case 1:
                        viewMode = "Tracking";
                        break;
                    case 2:
                        viewMode = "Following";
                        break;
                    case 3:
                        viewMode = "Freelook (WASD + mouse)";
                        break;
                }
                Fps.Text = "F2 - Toggle view mode: " + viewMode + "\n" +
                    "F3 - Toggle debug\n" +
                    "F11 - Toggle fullscreen";
            }

            if (Input.KeyboardDown.Contains(Key.F3))
            {
                if (physics.IsDebugDrawEnabled == false)
                    physics.SetDebugDraw(Device, DebugDrawModes.DrawWireframe);
                else
                    physics.SetDebugDraw(Device, 0);
            }

            physics.HandleKeys(Input, FrameDelta);

            physics.Update(FrameDelta);
        }

        protected override void OnRender()
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
            Device.BeginScene();

            Matrix trans = Matrix.Translation(new Vector3(0, 1, 0)) * physics.vehicle.ChassisWorldTransform;
            Vector4 pos = physics.vehicle.ChassisWorldTransform.get_Rows(3);
            Vector3 pos2 = new Vector3(pos.X, pos.Y, pos.Z);
            
            // Set View matrix based on view mode
            if (ViewMode == 1)
            {
                Matrix view = Matrix.LookAtLH(new Vector3(30, 20, 30), pos2, Vector3.UnitY);
                Device.SetTransform(TransformState.View, view);
            }
            else if (ViewMode == 2)
            {
                Freelook.SetEyeTarget(pos2 + new Vector3(30, 10, 0), pos2);
                Device.SetTransform(TransformState.View, Freelook.View);
            }
            else if (ViewMode == 3)
            {
                Device.SetTransform(TransformState.View, Freelook.View);
            }

            Device.Material = groundMaterial;
            Device.SetTransform(TransformState.World, Matrix.Translation(0, -4.5f, 0));
            ground.DrawSubset(0);

            Device.Material = bodyMaterial;
            Device.SetTransform(TransformState.World, trans);
            chassis.DrawSubset(0);

            Device.Material = wheelMaterial;
            int i;
            for (i = 0; i < physics.vehicle.NumWheels; i++)
            {
                //synchronize the wheels with the (interpolated) chassis worldtransform
                physics.vehicle.UpdateWheelTransform(i, true);
                //draw wheels (cylinders)
                trans = Matrix.RotationY((float)Math.PI / 2);
                trans *= physics.vehicle.GetWheelInfo(i).WorldTransform;
                Device.SetTransform(TransformState.World, trans);
                wheel.DrawSubset(0);
            }
            
            physics.DebugDrawWorld();

            Fps.OnRender(FramesPerSecond);

            Device.EndScene();
            Device.Present();
        }
    }
}
