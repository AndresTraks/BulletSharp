using BulletSharp;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DemoFramework.MonoGame
{
    public class PhysicsDebugDraw : BufferedDebugDraw
    {
        MonoGameGraphics graphics;
        BasicEffect effect;
        EffectPass pass;

        public PhysicsDebugDraw(MonoGameGraphics graphics)
        {
            this.graphics = graphics;
        }

        public void DrawDebugWorld(DynamicsWorld world)
        {
            world.DebugDrawWorld();

            if (lines.Count == 0)
                return;

            if (effect == null)
            {
                effect = new BasicEffect(graphics.Device);
                effect.World = Microsoft.Xna.Framework.Matrix.Identity;
                effect.VertexColorEnabled = true;
            }

            effect.Projection = graphics.GetEffect().Projection;
            effect.View = graphics.GetEffect().View;

            pass = effect.CurrentTechnique.Passes[0];
            pass.Apply();

            int pointCount = lines.Count;
            int linesCount = pointCount / 2;
            VertexPositionColor[] linesArray = new VertexPositionColor[pointCount];
            for (int i = 0; i < pointCount; i++)
            {
                int color = lines[i].Color;
                linesArray[i].Color = new Color(color & 0xff, (color & 0xff00) >> 8, (color & 0xff0000) >> 16, 1);
                linesArray[i].Position = MathHelper.Convert(lines[i].Position);
            }
            graphics.Device.DrawUserPrimitives(PrimitiveType.LineList, linesArray, 0, linesCount);
            lines.Clear();
        }
    };
};
