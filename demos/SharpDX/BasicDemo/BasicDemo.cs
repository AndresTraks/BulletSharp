using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;
using SharpDX;
using SharpDX.Direct3D10;
using SharpDX.DXGI;

namespace BasicDemo
{
    class BasicDemo : Demo
    {
        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - Basic Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();

            Eye = new Vector3(30, 20, 10);
            Target = new Vector3(0, 5, -4);
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

            Device.InputAssembler.SetInputLayout(new InputLayout(Device, Pass.Description.Signature, new[] { 
                    new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0)
                }));

            for (int i = 0; i < Technique.Description.PassCount; ++i)
            {
                Technique.GetPassByIndex(i).Apply();

                foreach (RigidBody body in PhysicsContext.World.CollisionObjectArray)
                {
                    Color color;
                    if ((string)body.UserObject == "Ground")
                    {
                        color = Color.Green;
                    }
                    else
                    {
                        color = body.ActivationState == ActivationState.ActiveTag ? Color.Orange : Color.Red;
                    }
                    SetBuffer(body.MotionState.WorldTransform, color);
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
