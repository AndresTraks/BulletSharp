using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;
using SharpDX.Direct3D10;
using SharpDX.DXGI;

namespace BasicDemo
{
    class BasicDemo : Demo
    {
        //Vector3 eye = new Vector3(30, 20, 10);
        //Vector3 target = new Vector3(0, 5, -4);

        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - Basic Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();

            //Freelook.SetEyeTarget(eye, target);

            Info.Text = "Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                "F11 - Toggle fullscreen\n" +
                "Space - Shoot box";

            base.OnInitialize();
        }

        protected override void OnRender()
        {
            Device.ClearRenderTargetView(RenderView, Ambient);
            Device.ClearDepthStencilView(DepthStencilView, DepthStencilClearFlags.Depth, 1.0f, 0);

            for (int i = 0; i < Technique.Description.PassCount; ++i)
            {
                Technique.GetPassByIndex(i).Apply();

                Device.InputAssembler.SetInputLayout(new InputLayout(Device, Pass.Description.Signature, new[] { 
                    new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0)
                }));

                foreach (CollisionObject colObj in PhysicsContext.World.CollisionObjectArray)
                {
                    RigidBody body = RigidBody.Upcast(colObj);
                    SetBuffer(body.MotionState.WorldTransform, Color.Green);
                    MeshFactory.Render(body.CollisionShape);
                }
            }

            Info.OnRender(FramesPerSecond);
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            BasicDemo game = new BasicDemo();

            if (game.TestLibraries() == false)
                return;

            game.Run();
            game.Dispose();
        }
    }
}
