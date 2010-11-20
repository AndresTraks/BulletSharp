using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace SoftDemo
{
    class SoftDemo : Game
    {
        Vector3 eye = new Vector3(20, 20, 80);
        Vector3 target = new Vector3(0, 0, 10);

        Light light;
        Material softBodyMaterial;

        Physics Physics
        {
            get { return (Physics)PhysicsContext; }
            set { PhysicsContext = value; }
        }

        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - SoftBody Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            Physics = new Physics();

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 75;
            light.Position = new Vector3(10, 25, 0);
            light.Diffuse = Color.LemonChiffon;
            light.Attenuation0 = 1.0f;

            softBodyMaterial = new Material();
            softBodyMaterial.Diffuse = Color.White;
            softBodyMaterial.Ambient = new Color4(Ambient);

            Fps.Text = "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen\n" +
                "Space - Shoot box\n\n" +
                "B - Previous Demo\n" +
                "N - Next Demo";

            Freelook.SetEyeTarget(eye, target);

            base.OnInitialize();
        }

        protected override void OnResourceLoad()
        {
            base.OnResourceLoad();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);

            Device.SetRenderState(RenderState.CullMode, Cull.None);
        }

        protected override void OnUpdate()
        {
            base.OnUpdate();

            if (Input.KeysPressed.Contains(Keys.B))
            {
                Physics.PreviousDemo();
            }
            else if (Input.KeysPressed.Contains(Keys.N))
            {
                Physics.NextDemo();
            }

            Physics.HandleKeys(Input, FrameDelta);
        }

        protected override void OnRender()
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
            Device.BeginScene();

            Device.SetTransform(TransformState.View, Freelook.View);

            foreach (CollisionObject colObj in Physics.World.CollisionObjectArray)
            {
                if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.SoftBodyShape)
                {
                    if (IsDebugDrawEnabled)
                        continue;

                    Device.Material = softBodyMaterial;
                    Device.SetTransform(TransformState.World, Matrix.Identity);
                    MeshFactory.Render(colObj);
                }
                else
                {
                    RigidBody body = RigidBody.Upcast(colObj);
                    Device.SetTransform(TransformState.World, body.MotionState.WorldTransform);

                    if ((string)body.UserObject == "Ground")
                        Device.Material = GroundMaterial;
                    else if (colObj.ActivationState == ActivationState.ActiveTag)
                        Device.Material = ActiveMaterial;
                    else
                        Device.Material = PassiveMaterial;

                    MeshFactory.Render(colObj.CollisionShape);
                }
            }

            DebugDrawWorld();

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
            SoftDemo game = new SoftDemo();

            if (game.TestLibraries() == false)
                return;

            game.Run();
            game.Dispose();
        }
    }
}
