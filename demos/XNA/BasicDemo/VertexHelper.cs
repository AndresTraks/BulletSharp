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
            new VertexElement(0, 0, VertexElementFormat.Vector3,
                VertexElementMethod.Default, VertexElementUsage.Position, 0),

            new VertexElement(0, 12, VertexElementFormat.Vector3,
                VertexElementMethod.Default, VertexElementUsage.Normal, 0),
        };


        /// <summary>
        /// Size of this vertex type.
        /// </summary>
        public const int SizeInBytes = 24;
    }

    class VertexHelper
    {
        static public VertexBuffer CreateBox(GraphicsDevice device, Vector3 size)
        {
            VertexPositionNormal[] vertices = new VertexPositionNormal[36];

            Vector3 topLeftFront = new Vector3(-1.0f, 1.0f, -1.0f) * size;
            Vector3 bottomLeftFront = new Vector3(-1.0f, -1.0f, -1.0f) * size;
            Vector3 topRightFront =  new Vector3(1.0f, 1.0f, -1.0f) * size;
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
            vertices[0] = new VertexPositionNormal(topLeftFront, frontNormal);
            vertices[1] = new VertexPositionNormal(bottomLeftFront, frontNormal);
            vertices[2] = new VertexPositionNormal(topRightFront, frontNormal);
            vertices[3] = new VertexPositionNormal(bottomLeftFront, frontNormal);
            vertices[4] = new VertexPositionNormal(bottomRightFront, frontNormal);
            vertices[5] = new VertexPositionNormal(topRightFront, frontNormal);

            // Back face.
            vertices[6] = new VertexPositionNormal(topLeftBack, backNormal);
            vertices[7] = new VertexPositionNormal(topRightBack, backNormal);
            vertices[8] = new VertexPositionNormal(bottomLeftBack, backNormal);
            vertices[9] = new VertexPositionNormal(bottomLeftBack, backNormal);
            vertices[10] = new VertexPositionNormal(topRightBack, backNormal);
            vertices[11] = new VertexPositionNormal(bottomRightBack, backNormal);

            // Top face.
            vertices[12] = new VertexPositionNormal(topLeftFront, topNormal);
            vertices[13] = new VertexPositionNormal(topRightBack, topNormal);
            vertices[14] = new VertexPositionNormal(topLeftBack, topNormal);
            vertices[15] = new VertexPositionNormal(topLeftFront, topNormal);
            vertices[16] = new VertexPositionNormal(topRightFront, topNormal);
            vertices[17] = new VertexPositionNormal(topRightBack, topNormal);

            // Bottom face. 
            vertices[18] = new VertexPositionNormal(bottomLeftFront, bottomNormal);
            vertices[19] = new VertexPositionNormal(bottomLeftBack, bottomNormal);
            vertices[20] = new VertexPositionNormal(bottomRightBack, bottomNormal);
            vertices[21] = new VertexPositionNormal(bottomLeftFront, bottomNormal);
            vertices[22] = new VertexPositionNormal(bottomRightBack, bottomNormal);
            vertices[23] = new VertexPositionNormal(bottomRightFront, bottomNormal);

            // Left face.
            vertices[24] = new VertexPositionNormal(topLeftFront, leftNormal);
            vertices[25] = new VertexPositionNormal(bottomLeftBack, leftNormal);
            vertices[26] = new VertexPositionNormal(bottomLeftFront, leftNormal);
            vertices[27] = new VertexPositionNormal(topLeftBack, leftNormal);
            vertices[28] = new VertexPositionNormal(bottomLeftBack, leftNormal);
            vertices[29] = new VertexPositionNormal(topLeftFront, leftNormal);

            // Right face. 
            vertices[30] = new VertexPositionNormal(topRightFront, rightNormal);
            vertices[31] = new VertexPositionNormal(bottomRightFront, rightNormal);
            vertices[32] = new VertexPositionNormal(bottomRightBack, rightNormal);
            vertices[33] = new VertexPositionNormal(topRightBack, rightNormal);
            vertices[34] = new VertexPositionNormal(topRightFront, rightNormal);
            vertices[35] = new VertexPositionNormal(bottomRightBack, rightNormal);

            VertexBuffer buffer = new VertexBuffer(device,
                VertexPositionNormal.SizeInBytes * vertices.Length,
            BufferUsage.WriteOnly);
                buffer.SetData(vertices);

            return buffer;
        }

        static public void DrawBox(GraphicsDevice device, VertexBuffer buffer)
        {
            device.Vertices[0].SetSource(buffer, 0,
                VertexPositionNormal.SizeInBytes);
            device.VertexDeclaration = new VertexDeclaration(
                device, VertexPositionNormal.VertexElements);
            device.DrawPrimitives(PrimitiveType.TriangleList, 0, 12);
        }
    }
}
