using BulletSharp;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;

namespace DemoFramework
{
    public class PhysicsDebugDraw : DebugDraw
    {
        GraphicsDevice _device;

        public override DebugDrawModes DebugMode { get; set; }

        public PhysicsDebugDraw(GraphicsDevice device)
        {
            _device = device;
        }

        public override void Draw3dText(ref Vector3 location, string textString)
        {
            throw new NotImplementedException();
        }

        public override void DrawContactPoint(ref Vector3 pointOnB, ref Vector3 normalOnB, float distance, int lifeTime, Color color)
        {
            var vertices = new[]
            {
                new VertexPositionColor(pointOnB, color),
                new VertexPositionColor(pointOnB + normalOnB, color)
            };
            _device.DrawUserPrimitives(PrimitiveType.LineList, vertices, 0, 1);
        }

        public override void DrawLine(ref Vector3 from, ref Vector3 to, Color color)
        {
            var vertices = new[]
            {
                new VertexPositionColor(from, color),
                new VertexPositionColor(to, color)
            };
            _device.DrawUserPrimitives(PrimitiveType.LineList, vertices, 0, 1);
        }

        public void DrawDebugWorld(DynamicsWorld world)
        {
            world.DebugDrawWorld();
        }

        public override void ReportErrorWarning(string warningString)
        {
            throw new NotImplementedException();
        }
    }
}
