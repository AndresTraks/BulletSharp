using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace VehicleDemo
{
    class VehicleDemo : Game
    {
        int Width = 1024, Height = 768;
        Vector3 eye = new Vector3(5, 15, 5);
        Vector3 target = Vector3.Zero;
        Color ambient = Color.Black;
        DebugDrawModes debug = DebugDrawModes.DrawWireframe;
        int ViewMode = 1;

        Light light;
        Material activeMaterial, passiveMaterial, groundMaterial, bodyMaterial, wheelMaterial;
        GraphicObjectFactory mesh;
        Mesh wheel;
        public Mesh ground;
        Physics physics;

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
            physics.DebugDrawer = new PhysicsDebugDrawLineGathering(Device);

            wheel = Mesh.CreateCylinder(Device, physics.wheelRadius, physics.wheelRadius, physics.wheelWidth, 10, 10);
            ground.ComputeNormals();

            mesh = new GraphicObjectFactory(Device);

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 500;
            light.Position = new Vector3(0, 100, 0);
            light.Direction = -Vector3.UnitY;
            light.Diffuse = Color.White;
            light.Attenuation0 = 0.75f;

            activeMaterial = new Material();
            activeMaterial.Diffuse = Color.Orange;
            activeMaterial.Ambient = ambient;

            passiveMaterial = new Material();
            passiveMaterial.Diffuse = Color.Red;
            passiveMaterial.Ambient = ambient;

            groundMaterial = new Material();
            groundMaterial.Diffuse = Color.Green;
            groundMaterial.Ambient = ambient;

            bodyMaterial = new Material();
            bodyMaterial.Diffuse = Color.Blue;
            bodyMaterial.Ambient = ambient;

            wheelMaterial = new Material();
            wheelMaterial.Diffuse = Color.Red;
            wheelMaterial.Ambient = ambient;

            Fps.Text = "F2 - Toggle view mode: Tracking\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen";

            Freelook.SetEyeTarget(new Vector3(30, 10, 0), target);
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (disposing)
            {
                wheel.Dispose();
                ground.Dispose();
                mesh.Dispose();
            }
        }

        protected override void OnResourceLoad()
        {
            base.OnResourceLoad();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);
            Device.SetRenderState(RenderState.Ambient, ambient.ToArgb());

            Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, 1.0f, 600.0f);
            Device.SetTransform(TransformState.Projection, Projection);

            Device.SetRenderState(RenderState.CullMode, Cull.None);

            Device.SetRenderState(RenderState.FogEnable, true);
            Device.SetRenderState(RenderState.FogStart, 125f);
            Device.SetRenderState(RenderState.FogEnd, 400f);
            Device.SetRenderState(RenderState.FogColor, Color.LightGray.ToArgb());
            Device.SetRenderState(RenderState.FogTableMode, FogMode.Linear);
        }

        protected override void OnUpdate()
        {
            base.OnUpdate();

            // Can only shoot boxes in FreeLook mode
            if (Input.KeysPressed.Contains(Keys.Space))
            {
                if (ViewMode != 3)
                {
                    Input.KeysPressed.Remove(Keys.Space);
                }
            }

            InputUpdate(Freelook.Eye, Freelook.Target, physics);

            if (Input.KeysPressed.Contains(Keys.F2))
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

            if (Input.KeysPressed.Contains(Keys.F3))
            {
                if (physics.IsDebugDrawEnabled)
                    physics.SetDebugDrawMode(Device, 0);
                else
                    physics.SetDebugDrawMode(Device, debug);
            }

            physics.HandleKeys(Input, FrameDelta);
            physics.Update(FrameDelta);
        }

        protected override void OnRender()
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
            Device.BeginScene();

            Matrix trans = physics.vehicle.ChassisWorldTransform;
            Vector4 pos = trans.get_Rows(3);
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

            if (physics.IsDebugDrawEnabled == false)
            {
                // Draw wireframe
                Device.SetRenderState(RenderState.Lighting, false);
                Device.SetRenderState(RenderState.FillMode, FillMode.Wireframe);
                Device.SetTransform(TransformState.World, Matrix.Identity);
                ground.DrawSubset(0);
                Device.SetRenderState(RenderState.Lighting, true);
                Device.SetRenderState(RenderState.FillMode, FillMode.Solid);
            }

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

            foreach (CollisionObject colObj in physics.World.CollisionObjectArray)
            {
                RigidBody body = RigidBody.Upcast(colObj);
                if ((string)body.UserObject == "Ground")
                {
                    Device.SetTransform(TransformState.World, Matrix.Identity);
                    Device.Material = groundMaterial;
                    ground.DrawSubset(0);
                    continue;
                }
                else if ((string)body.UserObject == "Chassis")
                    Device.Material = bodyMaterial;
                else if (colObj.ActivationState == ActivationState.ActiveTag)
                    Device.Material = activeMaterial;
                else
                    Device.Material = passiveMaterial;
                Device.SetTransform(TransformState.World, body.MotionState.WorldTransform);
                mesh.Render(colObj);
            }

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
            VehicleDemo game = new VehicleDemo();

            if (game.TestLibraries() == false)
                return;

            game.Run();
            game.Dispose();
        }
    }
}
