using System.Drawing;
using BulletSharp;
using SlimDX.Direct3D9;

namespace DemoFramework.SlimDX
{
    public class PhysicsDebugDraw : BufferedDebugDraw
    {
        Device device;

        public PhysicsDebugDraw(Device device)
        {
            this.device = device;
        }

        protected override int ColorToInt(ref Color c)
        {
            return c.ToArgb();
        }

        public void DrawDebugWorld(DynamicsWorld world)
        {
            world.DebugDrawWorld();
            if (lines.Count == 0)
                return;

            int lighting = device.GetRenderState(RenderState.Lighting);
            device.SetRenderState(RenderState.Lighting, false);
            device.SetTransform(TransformState.World, global::SlimDX.Matrix.Identity);
            device.VertexFormat = VertexFormat.Position | VertexFormat.Diffuse;

            device.DrawUserPrimitives(PrimitiveType.LineList, lines.Count / 2, lines.ToArray());
            lines.Clear();

            device.SetRenderState(RenderState.Lighting, lighting);
        }
    };
};
