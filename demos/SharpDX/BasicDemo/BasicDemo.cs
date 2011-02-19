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
        Vector3 eye = new Vector3(30, 20, 10);
        Vector3 target = new Vector3(0, 5, -4);

        protected override void OnInitializeDevice()
        {
            Form.Text = "BulletSharp - Basic Demo";
            base.OnInitializeDevice();
        }

        protected override void OnInitialize()
        {
            PhysicsContext = new Physics();

            Freelook.SetEyeTarget(eye, target);

            Info.Text = "Move using mouse and WASD+shift\n" +
                //"F3 - Toggle debug\n" +
                //"F11 - Toggle fullscreen\n" +
                "Space - Shoot box";

            base.OnInitialize();
        }

        string ground = "Ground";
        protected override void OnRender()
        {
            Device.ClearRenderTargetView(RenderView, Ambient);
            Device.ClearDepthStencilView(DepthStencilView, DepthStencilClearFlags.Depth, 1.0f, 0);

            for (int i = 0; i < Technique.Description.PassCount; ++i)
            {
                Technique.GetPassByIndex(i).Apply();

                foreach (RigidBody body in PhysicsContext.World.CollisionObjectArray)
                {
                    Color color;
                    if (ground.Equals(body.UserObject))
                    {
                        color = Color.Green;
                    }
                    else
                    {
                        color = body.ActivationState == ActivationState.ActiveTag ? Color.Orange : Color.OrangeRed;
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
