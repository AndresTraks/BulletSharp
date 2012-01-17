using System;
using System.Collections.Generic;
using System.Drawing;
using Microsoft.Xna.Framework.Graphics;
using BulletSharp;

namespace DemoFramework.Xna
{
    public class PhysicsDebugDraw : BufferedDebugDraw
    {
        GraphicsDevice device;

        public PhysicsDebugDraw(GraphicsDevice device)
        {
            this.device = device;
        }

        public override void DrawDebugWorld(DynamicsWorld world)
        {
            world.DebugDrawWorld();
            if (lines.Count == 0)
                return;
            /*
            int lighting = device.GetRenderState(RenderState.Lighting);
            device.SetRenderState(RenderState.Lighting, false);
            device.SetTransform(TransformState.World, global::SlimDX.Matrix.Identity);
            device.VertexFormat = PositionColored.FVF;

            device.DrawUserPrimitives(PrimitiveType.LineList, lines.ToArray(), 0, lines.Count / 2);
            device.DrawUserPrimitives(PrimitiveType.LineList, lines.Count / 2, lines.ToArray());
            lines.Clear();

            device.BlendState.
            device.SetRenderState(RenderState.Lighting, lighting);
            */
        }
    };
};
