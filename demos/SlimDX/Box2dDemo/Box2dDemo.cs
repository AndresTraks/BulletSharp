using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace Box2dDemo
{
    class Box2dDemo : Game
    {
        int Width = 1024, Height = 768;
        Color ambient = Color.Gray;
        Vector3 eye = new Vector3(10, 20, 30);
        Vector3 target = new Vector3(7, 7, 0);

        Mesh triangle;
        Light light;
        Material activeMaterial, passiveMaterial, groundMaterial;
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
                triangle.Dispose();
            }
        }

        Mesh ConstructTriangleMesh()
        {
            float u = 1.02f;
            Vector3[] points = { new Vector3(0, u, 0), new Vector3(-u, -u, 0), new Vector3(u, -u, 0) };
            Vector3 depth = new Vector3(0, 0, physics.Depth);
            Mesh triangle = new Mesh(Device, 8, 6, MeshFlags.Managed, VertexFormat.Position | VertexFormat.Normal);

            SlimDX.DataStream ds = triangle.LockVertexBuffer(LockFlags.None);
            
            // Front
            ds.Write(points[0] + depth);
            ds.Write(Vector3.UnitZ);
            ds.Write(points[1] + depth);
            ds.Write(Vector3.UnitZ);
            ds.Write(points[2] + depth);
            ds.Write(Vector3.UnitZ);

            // Back
            ds.Write(points[0] - depth);
            ds.Write(-Vector3.UnitZ);
            ds.Write(points[1] - depth);
            ds.Write(-Vector3.UnitZ);
            ds.Write(points[2] - depth);
            ds.Write(-Vector3.UnitZ);

            triangle.UnlockVertexBuffer();

            short[] indices = new short[] {
                0, 1, 2, 3, 4, 5,
                0, 1, 3, 1, 3, 4,
                1, 2, 4, 2, 4, 5,
                2, 0, 5, 0, 5, 3
            };
            
            ds = triangle.LockIndexBuffer(LockFlags.None);
            foreach (short index in indices)
            {
                ds.Write(index);
            }
            triangle.UnlockIndexBuffer();

            return triangle;
        }

        protected override void OnInitializeDevice()
        {
            Form.ClientSize = new Size(Width, Height);
            Form.Text = "BulletSharp - Box2d Demo";

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

            mesh = new GraphicObjectFactory(Device);

            // Create the shapes to be drawn
            triangle = ConstructTriangleMesh();

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 100;
            light.Position = new Vector3(10, 25, 10);
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

            Freelook.SetEyeTarget(eye, target);

            Fps.Text = "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen\n" +
                "Space - Shoot box";
        }

        protected override void OnResourceLoad()
        {
            base.OnResourceLoad();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);
            Device.SetRenderState(RenderState.Ambient, new Color4(0.5f, 0.5f, 0.5f).ToArgb());

            Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, 0.1f, 150.0f);

            Device.SetTransform(TransformState.Projection, Projection);
            Device.SetRenderState(RenderState.CullMode, Cull.None);
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

                if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.BoxShape)
                {
                    mesh.Render(body);
                }
                else if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.Convex2DShape)
                {
                    Convex2DShape shape = Convex2DShape.Upcast2d(colObj.CollisionShape);
                    switch (shape.ChildShape.ShapeType)
                    {
                        case BroadphaseNativeType.ConvexHullShape:
                            triangle.DrawSubset(0);
                            break;
                        default:
                            mesh.Render(body);
                            break;
                    }
                }
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
            Box2dDemo game = new Box2dDemo();

            if (game.TestLibraries() == false)
                return;

            game.Run();
            game.Dispose();
        }
    }
}
