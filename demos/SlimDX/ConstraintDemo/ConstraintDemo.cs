using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.DirectInput;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace ConstraintDemo
{
    class ConstraintDemo : Game
    {
        int Width = 1024, Height = 768;
        Color ambient = Color.Gray;
        Vector3 eye = new Vector3(35, 10, 35);
        Vector3 target = new Vector3(0, 5, 0);
        bool DrawDebugLines = true;
        float FieldOfView = (float)Math.PI / 4;

        Matrix Projection;
        Input input;
        FreeLook freelook;
        FpsDisplay fps;
        Mesh box, groundBox;
        Light light;
        Material activeMaterial, passiveMaterial, groundMaterial;
        
        Physics physics;
        PhysicsDebugDraw debugDraw;

        public SlimDX.Direct3D9.Device Device
        {
            get { return Device9; }
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (disposing)
            {
                input.Dispose();
                box.Dispose();
                groundBox.Dispose();
                fps.Dispose();
            }
        }

        protected override void OnInitialize()
        {
            Form.ClientSize = new Size(Width, Height);
            Form.Text = "BulletSharp - Constraints Demo";

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
            freelook.SetEyeTarget(eye, target);

            physics = new Physics();

            float size = physics.CubeHalfExtents * 2;
            box = Mesh.CreateBox(Device, size, size, size);
            groundBox = Mesh.CreateBox(Device, 100, 80, 100);

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 70;
            light.Position = new Vector3(10, 25, 10);
            light.Falloff = 1.0f;
            light.Diffuse = Color.LemonChiffon;

            //light.Type = LightType.Directional;
            //light.Direction = new Vector3(-1, -1, -1);

            activeMaterial = new Material();
            activeMaterial.Diffuse = Color.Orange;
            activeMaterial.Ambient = ambient;

            passiveMaterial = new Material();
            passiveMaterial.Diffuse = Color.Red;
            passiveMaterial.Ambient = ambient;

            groundMaterial = new Material();
            groundMaterial.Diffuse = Color.Green;
            groundMaterial.Ambient = ambient;

            fps = new FpsDisplay(Device);
            fps.Text = "Move using mouse and WASD\r\n" +
                "F11 - Toggle fullscreen";

            debugDraw = new PhysicsDebugDraw(Device);
            physics.world.DebugDrawer = debugDraw;
            debugDraw.SetDebugMode(DebugDrawModes.DrawConstraints | DebugDrawModes.DrawConstraintLimits);
        }

        protected override void OnResourceLoad()
        {
            input.OnResetDevice();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);
            Device.SetRenderState(RenderState.Ambient, new Color4(0.5f, 0.5f, 0.5f).ToArgb());

            Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, 0.1f, 150.0f);

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
                MouseUpdate(input, freelook.Eye, freelook.Target, FieldOfView, physics.world);
            }

            // Handle keyboard events
            if (input.KeyboardState != null)
            {
                // Exit
                if (input.KeyboardState.IsPressed(Key.Escape))
                    Quit();

                if (input.KeyboardDown.Contains(Key.F11))
                    ToggleFullScreen();
            }

            physics.Update(FrameDelta);
        }

        protected override void OnRender()
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
            Device.BeginScene();

            Device.SetTransform(TransformState.View, freelook.View);

            foreach (CollisionObject colObj in physics.world.CollisionObjectArray)
            {
                RigidBody body = RigidBody.Upcast(colObj);
                Device.SetTransform(TransformState.World, body.MotionState.WorldTransform);

                if ((string)body.UserObject == "Ground")
                {
                    Device.Material = groundMaterial;
                    groundBox.DrawSubset(0);
                }

                if (colObj.ActivationState == ActivationState.ActiveTag)
                    Device.Material = activeMaterial;
                else
                    Device.Material = passiveMaterial;

                box.DrawSubset(0);
            }

            if (DrawDebugLines)
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
    }
}
