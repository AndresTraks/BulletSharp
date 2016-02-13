using SharpDX;
using System;
using System.Runtime.InteropServices;

namespace DemoFramework.SharpDX11
{
    [StructLayout(LayoutKind.Sequential)]
    class Light
    {
        public Matrix World { get; }
        public Vector3 Position { get; }
        public float Radius { get; }
        public Vector4 Color { get; }

        public Light(Vector3 position, float radius, Vector4 color)
        {
            Position = position;
            Radius = radius;
            Color = color;

            World = Matrix.Scaling(Radius) * Matrix.Translation(Position);
        }

        public static Vector3[] CreatePointLightVolume(out uint[] indices)
        {
            float radius = 1.0f;

            int slices = (int)(radius * 10.0f);
            int stacks = (int)(radius * 10.0f);
            slices = (slices > 16) ? 16 : (slices < 3) ? 3 : slices;
            stacks = (stacks > 16) ? 16 : (stacks < 2) ? 2 : stacks;

            float hAngleStep = (float)Math.PI * 2 / slices;
            float vAngleStep = (float)Math.PI / stacks;

            int vertexCount = 2 + slices * (stacks - 1);
            int indexCount = 6 * slices * (stacks - 1);

            Vector3[] vertices = new Vector3[vertexCount];
            indices = new uint[indexCount];

            int i = 0, v = 0;


            // Vertices
            // Top and bottom
            vertices[v++] = new Vector3(0, -radius, 0);
            vertices[v++] = new Vector3(0, radius, 0);

            // Stacks
            int j, k;
            float angle = 0;
            float vAngle = -(float)Math.PI / 2;
            Vector3 vTemp;
            for (j = 0; j < stacks - 1; j++)
            {
                vAngle += vAngleStep;

                for (k = 0; k < slices; k++)
                {
                    angle += hAngleStep;

                    vTemp = new Vector3((float)Math.Cos(vAngle) * (float)Math.Sin(angle), (float)Math.Sin(vAngle), (float)Math.Cos(vAngle) * (float)Math.Cos(angle));
                    vertices[v++] = vTemp * radius;
                }
            }


            // Indices
            // Top cap
            ushort index = 2;
            for (k = 0; k < slices; k++)
            {
                indices[i++] = index++;
                indices[i++] = 0;
                indices[i++] = index;
            }
            indices[i - 1] = 2;

            // Stacks
            //for (j = 0; j < 1; j++)
            int sliceDiff = slices * 3;
            for (j = 0; j < stacks - 2; j++)
            {
                for (k = 0; k < slices; k++)
                {
                    indices[i] = indices[i - sliceDiff + 2];
                    indices[i + 1] = index++;
                    indices[i + 2] = indices[i - sliceDiff];
                    i += 3;
                }

                for (k = 0; k < slices; k++)
                {
                    indices[i] = indices[i - sliceDiff + 1];
                    indices[i + 1] = indices[i - sliceDiff];
                    indices[i + 2] = indices[i - sliceDiff + 4];
                    i += 3;
                }
                indices[i - 1] = indices[i - sliceDiff];
            }

            // Bottom cap
            index--;
            for (k = 0; k < slices; k++)
            {
                indices[i++] = index--;
                indices[i++] = 1;
                indices[i++] = index;
            }
            indices[i - 1] = indices[i - sliceDiff];

            return vertices;
        }
    }
}
