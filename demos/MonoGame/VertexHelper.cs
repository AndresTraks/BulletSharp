// Adapted from http://www.switchonthecode.com/tutorials/creating-a-textured-box-in-xna

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace BasicDemo
{
    public struct VertexPositionNormal
    {
        public Vector3 Position;
        public Vector3 Normal;

        public VertexPositionNormal(Vector3 position, Vector3 normal)
        {
            Position = position;
            Normal = normal;
        }

        public static readonly VertexElement[] VertexElements =
        {
            new VertexElement(0, VertexElementFormat.Vector3, VertexElementUsage.Position, 0),
            new VertexElement(12, VertexElementFormat.Vector3, VertexElementUsage.Normal, 0),
        };


        /// <summary>
        /// Size of this vertex type.
        /// </summary>
        public const int SizeInBytes = 24;
    }

    class VertexHelper
    {
        public static VertexBuffer CreateBox(GraphicsDevice device, Vector3 size)
        {
            Vector3 topLeftFront = new Vector3(-1.0f, 1.0f, -1.0f) * size;
            Vector3 bottomLeftFront = new Vector3(-1.0f, -1.0f, -1.0f) * size;
            Vector3 topRightFront = new Vector3(1.0f, 1.0f, -1.0f) * size;
            Vector3 bottomRightFront = new Vector3(1.0f, -1.0f, -1.0f) * size;
            Vector3 topLeftBack = new Vector3(-1.0f, 1.0f, 1.0f) * size;
            Vector3 topRightBack = new Vector3(1.0f, 1.0f, 1.0f) * size;
            Vector3 bottomLeftBack = new Vector3(-1.0f, -1.0f, 1.0f) * size;
            Vector3 bottomRightBack = new Vector3(1.0f, -1.0f, 1.0f) * size;

            Vector3 frontNormal = new Vector3(0.0f, 0.0f, 1.0f) * size;
            Vector3 backNormal = new Vector3(0.0f, 0.0f, -1.0f) * size;
            Vector3 topNormal = new Vector3(0.0f, 1.0f, 0.0f) * size;
            Vector3 bottomNormal = new Vector3(0.0f, -1.0f, 0.0f) * size;
            Vector3 leftNormal = new Vector3(-1.0f, 0.0f, 0.0f) * size;
            Vector3 rightNormal = new Vector3(1.0f, 0.0f, 0.0f) * size;

            // Front face.
            var vertices = new[]
            {
                new VertexPositionNormal(topLeftFront, frontNormal),
                new VertexPositionNormal(bottomLeftFront, frontNormal),
                new VertexPositionNormal(topRightFront, frontNormal),
                new VertexPositionNormal(bottomLeftFront, frontNormal),
                new VertexPositionNormal(bottomRightFront, frontNormal),
                new VertexPositionNormal(topRightFront, frontNormal),

                // Back face.
                new VertexPositionNormal(topLeftBack, backNormal),
                new VertexPositionNormal(topRightBack, backNormal),
                new VertexPositionNormal(bottomLeftBack, backNormal),
                new VertexPositionNormal(bottomLeftBack, backNormal),
                new VertexPositionNormal(topRightBack, backNormal),
                new VertexPositionNormal(bottomRightBack, backNormal),

                // Top face.
                new VertexPositionNormal(topLeftFront, topNormal),
                new VertexPositionNormal(topRightBack, topNormal),
                new VertexPositionNormal(topLeftBack, topNormal),
                new VertexPositionNormal(topLeftFront, topNormal),
                new VertexPositionNormal(topRightFront, topNormal),
                new VertexPositionNormal(topRightBack, topNormal),

                // Bottom face. 
                new VertexPositionNormal(bottomLeftFront, bottomNormal),
                new VertexPositionNormal(bottomLeftBack, bottomNormal),
                new VertexPositionNormal(bottomRightBack, bottomNormal),
                new VertexPositionNormal(bottomLeftFront, bottomNormal),
                new VertexPositionNormal(bottomRightBack, bottomNormal),
                new VertexPositionNormal(bottomRightFront, bottomNormal),

                // Left face.
                new VertexPositionNormal(topLeftFront, leftNormal),
                new VertexPositionNormal(bottomLeftBack, leftNormal),
                new VertexPositionNormal(bottomLeftFront, leftNormal),
                new VertexPositionNormal(topLeftBack, leftNormal),
                new VertexPositionNormal(bottomLeftBack, leftNormal),
                new VertexPositionNormal(topLeftFront, leftNormal),

                // Right face. 
                new VertexPositionNormal(topRightFront, rightNormal),
                new VertexPositionNormal(bottomRightFront, rightNormal),
                new VertexPositionNormal(bottomRightBack, rightNormal),
                new VertexPositionNormal(topRightBack, rightNormal),
                new VertexPositionNormal(topRightFront, rightNormal),
                new VertexPositionNormal(bottomRightBack, rightNormal)
            };

            var buffer = new VertexBuffer(device, new VertexDeclaration(VertexPositionNormal.VertexElements),
                vertices.Length, BufferUsage.WriteOnly);
            buffer.SetData(vertices);

            return buffer;
        }

        public static void DrawBox(GraphicsDevice device, VertexBuffer buffer)
        {
            device.SetVertexBuffer(buffer);
            device.DrawPrimitives(PrimitiveType.TriangleList, 0, 12);
        }
    }
}
