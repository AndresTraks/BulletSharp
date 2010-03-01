using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.DirectInput;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace VehicleDemo
{
    class VehicleDemo : Game
    {
        int Width = 1024, Height = 768;
        Color ambient = Color.Gray;
        Vector3 eye = new Vector3(5, 15, 5);
        bool DrawDebugLines = true;
        int ViewMode = 1, DrawMode = 1;
        float FieldOfView = (float)Math.PI / 4;

        Matrix Projection;
        Input input;
        FreeLook freelook;
        FpsDisplay fps;
        Mesh wheel, chassis;
        Light light;
        Material wheelMaterial, bodyMaterial, groundMaterial;
        PhysicsDebugDraw debugDraw;
        public Mesh ground;

        Physics physics;

        public SlimDX.Direct3D9.Device Device
        {
            get { return Device9; }
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            input.Dispose();
            wheel.Dispose();
            chassis.Dispose();
            ground.Dispose();
            fps.Dispose();
        }

        protected override void OnInitialize()
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

            input = new Input(Form);
            freelook = new FreeLook();
            freelook.SetEyeTarget(new Vector3(30, 10, 0), Vector3.Zero);

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

            fps = new FpsDisplay(Device);
            fps.Text = "F2 - Toggle view mode: Tracking\r\n" +
                "F3 - Toggle draw mode\r\n" +
                "F11 - Toggle fullscreen";

            debugDraw = new PhysicsDebugDraw(Device);
            physics.world.DebugDrawer = debugDraw;
            debugDraw.SetDebugMode(DebugDrawModes.DrawWireframe);
        }

        protected override void OnResourceLoad()
        {
            input.OnResetDevice();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);
            Device.SetRenderState(RenderState.Ambient, new Color4(0.5f, 0.5f, 0.5f).ToArgb());

            Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, 0.1f, 400.0f);

            Device.SetTransform(TransformState.Projection, Projection);

            fps.OnResourceLoad();
        }

        protected override void OnResourceUnload()
        {
            fps.OnResourceUnload();
        }

        protected override void OnUpdate()
        {
            input.GetCurrentState();

            // Handle mouse events
            if (input.MousePoint != Point.Empty)
            {
                freelook.Update(FrameDelta, input);
            }

            // Handle keyboard events
            if (input.KeyboardState != null)
            {
                // Exit
                if (input.KeyboardState.IsPressed(Key.Escape))
                    Quit();

                if (input.KeyboardDown.Contains(Key.F11))
                    ToggleFullScreen();

                if (input.KeyboardDown.Contains(Key.F2))
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
                    fps.Text = "F2 - Toggle view mode: " + viewMode + "\r\n" +
                    "F3 - Toggle draw mode\r\n" +
                    "F11 - Toggle fullscreen";
                }

                if (input.KeyboardDown.Contains(Key.F3))
                {
                    DrawMode++;
                    if (DrawDebugLines)
                    {
                        if (DrawMode > 3) DrawMode = 1;
                    }
                    else
                    {
                        if (DrawMode > 2) DrawMode = 1;
                    }
                }

                physics.HandleKeys(input, FrameDelta);
            }

            physics.Update(FrameDelta);
        }

        protected override void OnRender()
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
            Device.BeginScene();

            Matrix trans = Matrix.Translation(new Vector3(0, 1, 0)) * physics.vehicle.ChassisWorldTransform;
            Vector4 pos = physics.vehicle.ChassisWorldTransform.get_Rows(3);
            Vector3 pos2 = new Vector3(pos.X, pos.Y, pos.Z);
            if (ViewMode == 1)
            {
                Matrix view = Matrix.LookAtLH(new Vector3(30, 20, 30), pos2, Vector3.UnitY);
                Device.SetTransform(TransformState.View, view);
            }
            else if (ViewMode == 2)
            {
                freelook.SetEyeTarget(pos2 + new Vector3(30, 10, 0), pos2);
                Device.SetTransform(TransformState.View, freelook.View);
            }
            else if (ViewMode == 3)
            {
                Device.SetTransform(TransformState.View, freelook.View);
            }

            if (DrawMode == 1 || DrawMode == 2)
            {
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
            }
            if (DrawDebugLines && (DrawMode == 2 || DrawMode == 3))
            {
                Device.SetRenderState(RenderState.Lighting, false);
                Device.SetTransform(TransformState.World, Matrix.Identity);
                Device.VertexFormat = PositionColored.FVF;
                physics.world.DebugDrawWorld();
                Device.SetRenderState(RenderState.Lighting, true);
            }

            fps.OnRender(FramesPerSecond);

            Device.EndScene();
            Device.Present();
        }

        class PhysicsDebugDraw : DebugDraw
        {
            SlimDX.Direct3D9.Device device;

            public PhysicsDebugDraw(SlimDX.Direct3D9.Device device)
            {
                this.device = device;
            }

            public override void DrawLine(Vector3 from, Vector3 to, Color4 color)
            {
                PositionColored[] vertices = new PositionColored[2];
                vertices[0] = new PositionColored(from, color.ToArgb());
                vertices[1] = new PositionColored(to, color.ToArgb());
                device.DrawUserPrimitives(PrimitiveType.LineList, 1, vertices);
            }
        }
    }
}
