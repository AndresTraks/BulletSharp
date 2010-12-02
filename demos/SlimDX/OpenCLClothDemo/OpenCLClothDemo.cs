using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace OpenCLClothDemo
{
    public class OpenCLClothDemo : Game
    {
        Vector3 eye = new Vector3(50, 20, 100);
        Vector3 target = new Vector3(0, 20, 40);
        DebugDrawModes debugMode = DebugDrawModes.DrawAabb;

        Light light;
        Material softBodyMaterial;
        Texture amdFlag;
        Texture atiFlag;

        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - OpenCL Cloth Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();
            DebugDrawMode = debugMode;

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 140;
            light.Position = new Vector3(10, 30, 50);
            light.Diffuse = Color.LemonChiffon;
            light.Attenuation0 = 1.0f;

            softBodyMaterial = new Material();
            softBodyMaterial.Diffuse = Color.White;
            softBodyMaterial.Ambient = new Color4(Ambient);

            amdFlag = Texture.FromFile(Device, "amdFlag.png");
            atiFlag = Texture.FromFile(Device, "atiFlag.png");

            FarPlane = 200f;
            Freelook.SetEyeTarget(eye, target);

            Fps.Text = "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen\n" +
                "Space - Shoot box";

            base.OnInitialize();
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (disposing)
            {
                amdFlag.Dispose();
                atiFlag.Dispose();
            }
        }

        protected override void OnResourceLoad()
        {
            base.OnResourceLoad();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);

            Device.SetRenderState(RenderState.CullMode, Cull.None);
            Device.SetSamplerState(0, SamplerState.MagFilter, TextureFilter.Linear);
        }

        protected override void OnRender()
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
            Device.BeginScene();

            Device.SetTransform(TransformState.View, Freelook.View);

            foreach (CollisionObject colObj in PhysicsContext.World.CollisionObjectArray)
            {
                if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.SoftBodyShape)
                {
                    Device.SetTexture(0, atiFlag);
                    Device.Material = softBodyMaterial;
                    Device.SetTransform(TransformState.World, Matrix.Identity);
                    MeshFactory.RenderSoftBodyTextured(BulletSharp.SoftBody.SoftBody.Upcast(colObj));
                    Device.SetTexture(0, null);
                    continue;
                }

                Device.SetTransform(TransformState.World, ((RigidBody)colObj).MotionState.WorldTransform);

                if ((string)colObj.UserObject == "Ground")
                    Device.Material = GroundMaterial;
                else if (colObj.ActivationState == ActivationState.ActiveTag)
                    Device.Material = ActiveMaterial;
                else
                    Device.Material = PassiveMaterial;

                MeshFactory.Render(((RigidBody)colObj).CollisionShape);
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
            OpenCLClothDemo game = new OpenCLClothDemo();

            if (game.TestLibraries() == false)
                return;

            game.Run();
            game.Dispose();
        }
    }
}
