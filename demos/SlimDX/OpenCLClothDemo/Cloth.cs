using BulletSharp;
using BulletSharp.SoftBody;
using System;

namespace OpenCLClothDemo
{
    class Cloth
    {
        FloatArray cpuBuffer;
        IntArray indices;
        VertexBufferDescriptor vertexBufferDescriptor;

        int width;
        int height;

        public VertexBufferDescriptor VertexBufferDescriptor
        {
            get { return vertexBufferDescriptor; }
            set { vertexBufferDescriptor = value; }
        }

        public IntArray Indices
        {
            get { return indices; }
        }

        public FloatArray CpuBuffer
        {
            get { return cpuBuffer; }
        }

        public void CreateBuffers(int width_, int height_)
        {
            width = width_;
            height = height_;

            cpuBuffer = new FloatArray(width * height * 8);

            // Initial test data for rendering
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    double coord = Math.Sin(x / 5.0) * 0.01;
                    //coord = sin(y/);

                    int index = (y * width + x) * 8;
                    // Position
                    cpuBuffer[index] = x / ((float)(width - 1));
                    cpuBuffer[index + 1] = (float)coord;
                    cpuBuffer[index + 2] = y / ((float)(height - 1));
                    // Normal
                    cpuBuffer[index + 3] = 1;
                    cpuBuffer[index + 4] = 0;
                    cpuBuffer[index + 5] = 0;
                    // TexCoords
                    cpuBuffer[index + 6] = y / ((float)(height - 1));
                    cpuBuffer[index + 7] = -x / ((float)(width - 1));
                }
            }


            // Generate and fill index array for rendering
            //indices = new IntArray(width * 3 * 2 + 2 + height * width * 3 * 2); // FIXME: what is this?
            indices = new IntArray(3 * 2 * (width - 1) * (height - 1));

            for (int y = 0; y < height - 1; y++)
            {
                for (int x = 0; x < width - 1; x++)
                {
                    // *3 indices/triangle, *2 triangles/quad
                    int baseIndex = (x + y * (width - 1)) * 3 * 2;

                    indices[baseIndex] = x + y * width;
                    indices[baseIndex + 1] = x + 1 + y * width;
                    indices[baseIndex + 2] = x + width + y * width;

                    indices[baseIndex + 3] = indices[baseIndex + 1];
                    indices[baseIndex + 4] = indices[baseIndex] + (width + 1);
                    indices[baseIndex + 5] = indices[baseIndex + 2];
                }
            }
        }
    }
}
