using BulletSharp;
using BulletSharp.SoftBody;
using System;

namespace OpenCLClothDemo
{
    class Cloth
    {
        bool created;

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

        public FloatArray CpuBuffer
        {
            get { return cpuBuffer; }
        }

        public void CreateBuffers(int width_, int height_)
	    {	    
		    width = width_;
		    height = height_;
    		
		    created = true;

            cpuBuffer = new FloatArray(width * height * 8);

		    // Initial test data for rendering
		    for(int y = 0; y < height; y++)
		    {
			    for(int x = 0; x < width; x++)
			    {
				    double coord = Math.Sin(x/5.0)*0.01;
				    //coord = sin(y/);

                    int index = (y * width + x) * 8;
                    // Position
                    cpuBuffer[index] = (x / ((float)(width - 1))) * 1;
                    cpuBuffer[index + 1] = (float)coord;
                    cpuBuffer[index + 2] = (y / ((float)(height - 1))) * 1;
                    // Normal
                    cpuBuffer[index + 3] = 1;
                    cpuBuffer[index + 4] = 0;
                    cpuBuffer[index + 5] = 0;
                    // TexCoords
                    cpuBuffer[index + 6] = x / ((float)(width - 1));
                    cpuBuffer[index + 7] = y / ((float)(height - 1));
			    }
		    }


		    // Generate and fill index array for rendering
            indices = new IntArray(3 * 2 * ((height + 1) * width + 2));

		    for(int y = 0; y < height-1; y++)
		    {
			    for(int x = 0; x < width-1; x++)
			    {
				    // *3 indices/triangle, *2 triangles/quad
				    int baseIndex = (x + y*(width-1))*3*2;

                    indices[baseIndex] = x + y*width;
				    indices[baseIndex+1] = x+1 + y*width;
				    indices[baseIndex+2] = x+width + y*width;

				    indices[baseIndex+3] = x + 1 +  y*width;
				    indices[baseIndex+4] = x+(width+1) + y*width;
				    indices[baseIndex+5] = x+width + y*width;
			    }
		    }
	    }
    }
}
