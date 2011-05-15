using System.Drawing;
using System.Runtime.InteropServices;
using SlimDX;
using SlimDX.Direct3D9;

namespace DemoFramework
{
    // Vertex element definitions

    [StructLayout(LayoutKind.Sequential)]
    public struct Positioned
    {
        public static readonly VertexFormat FVF = VertexFormat.Position;
        public static readonly int Stride = Vector3.SizeInBytes;

        public Vector3 Position;

        public Positioned(Vector3 pos)
        {
            Position = pos;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct PositionedNormal
    {
        public static readonly VertexFormat FVF = VertexFormat.PositionNormal;
        public static readonly int Stride = 2 * Vector3.SizeInBytes;

        public Vector3 Position;
        public Vector3 Normal;

        public PositionedNormal(Vector3 pos, Vector3 normal)
        {
            Position = pos;
            Normal = normal;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct PositionColored
    {
        public static readonly VertexFormat FVF = VertexFormat.Position | VertexFormat.Diffuse;
        public static readonly int Stride = Vector3.SizeInBytes + sizeof(int);

        public Vector3 Position;
        public int Color;

        public PositionColored(Vector3 pos, int col)
        {
            Position = pos;
            Color = col;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct PositionTextured
    {
        public static readonly VertexFormat FVF = VertexFormat.Position | VertexFormat.Texture1;
        public static readonly int Stride = Vector3.SizeInBytes + 2 * sizeof(float);

        public Vector3 Position;
        public float u, v;

        public PositionTextured(Vector3 pos, float u, float v)
        {
            Position = pos;
            this.u = u;
            this.v = v;
        }
    }

    
    public static class VertexHelper
    {
        // Returns a quad as a vertex element array

        public static Positioned[] Billboard()
        {
            return Billboard(1.0f);
        }

        public static Positioned[] Billboard(float size)
        {
            Positioned[] b = new Positioned[4];

            b[0].Position.X = -size;
            b[0].Position.Y = size;
            b[1].Position.X = size;
            b[1].Position.Y = size;
            b[2].Position.X = size;
            b[2].Position.Y = -size;
            b[3].Position.X = -size;
            b[3].Position.Y = -size;
            b[0].Position.Z = b[1].Position.Z = b[2].Position.Z = b[3].Position.Z = 0.0f;

            return b;
        }

        // Returns a quad as a vertex buffer

        public static VertexBuffer BillboardVertexBuffer(Device device)
        {
            return BillboardVertexBuffer(device, 1.0f);
        }

        public static VertexBuffer BillboardVertexBuffer(Device device, float size)
        {
            VertexBuffer vb = new VertexBuffer(device, 4 * Positioned.Stride, Usage.None,
                Positioned.FVF, Pool.SystemMemory);
            DataStream ds = vb.Lock(0, 4 * Positioned.Stride, LockFlags.None);
            Positioned[] vertexArray = Billboard(size);
            ds.WriteRange(vertexArray);

            return vb;
        }


        // Returns a colored quad as a vertex element array

        public static PositionColored[] BillboardColored()
        {
            return BillboardColored(1.0f);
        }

        public static PositionColored[] BillboardColored(float size)
        {
            PositionColored[] b = new PositionColored[4];

            b[0].Position.X = -size;
            b[0].Position.Y = size;
            b[1].Position.X = size;
            b[1].Position.Y = size;
            b[2].Position.X = size;
            b[2].Position.Y = -size;
            b[3].Position.X = -size;
            b[3].Position.Y = -size;
            b[0].Position.Z = b[1].Position.Z = b[2].Position.Z = b[3].Position.Z = 0.0f;
            b[0].Color = b[1].Color = b[2].Color = b[3].Color = Color.Black.ToArgb();

            return b;
        }

        // Returns a colored quad as a vertex buffer

        public static VertexBuffer BillboardColoredVertexBuffer(Device device)
        {
            return BillboardColoredVertexBuffer(device, 1.0f);
        }

        public static VertexBuffer BillboardColoredVertexBuffer(Device device, float size)
        {
            VertexBuffer vb = new VertexBuffer(device, 4 * PositionColored.Stride, Usage.None,
                PositionColored.FVF, Pool.SystemMemory);
            DataStream ds = vb.Lock(0, 4 * PositionColored.Stride, LockFlags.None);
            PositionColored[] vertexArray = BillboardColored(size);
            ds.WriteRange(vertexArray);

            return vb;
        }


        // Returns a textured quad as a vertex element array

        public static PositionTextured[] BillboardTextured()
        {
            return BillboardTextured(1.0f);
        }

        public static PositionTextured[] BillboardTextured(float size)
        {
            PositionTextured[] b = new PositionTextured[4];

            b[0].Position.X = -size;
            b[0].Position.Y = size;
            b[1].Position.X = size;
            b[1].Position.Y = size;
            b[2].Position.X = size;
            b[2].Position.Y = -size;
            b[3].Position.X = -size;
            b[3].Position.Y = -size;
            b[0].Position.Z = b[1].Position.Z = b[2].Position.Z = b[3].Position.Z = 0.0f;

            b[0].u = 0.0f;
            b[0].v = 0.0f;
            b[1].u = 1.0f;
            b[1].v = 0.0f;
            b[2].u = 1.0f;
            b[2].v = 1.0f;
            b[3].u = 0.0f;
            b[3].v = 1.0f;

            return b;
        }

        // Returns a textured quad as a vertex buffer

        public static VertexBuffer BillboardTexturedVertexBuffer(Device device)
        {
            return BillboardTexturedVertexBuffer(device, 1.0f);
        }

        public static VertexBuffer BillboardTexturedVertexBuffer(Device device, float size)
        {
            VertexBuffer vb = new VertexBuffer(device, 4 * PositionTextured.Stride, Usage.None,
                PositionTextured.FVF, Pool.SystemMemory);
            DataStream ds = vb.Lock(0, 4 * PositionTextured.Stride, LockFlags.None);
            PositionTextured[] vertexArray = BillboardTextured(size);
            ds.WriteRange(vertexArray);

            return vb;
        }


        // Render primitives

        public static void Draw(VertexBuffer buffer)
        {
            buffer.Device.SetStreamSource(0, buffer, 0, Positioned.Stride);
            buffer.Device.VertexFormat = Positioned.FVF;
            buffer.Device.DrawPrimitives(PrimitiveType.TriangleFan, 0, 2);
        }

        public static void DrawColored(VertexBuffer buffer)
        {
            buffer.Device.SetStreamSource(0, buffer, 0, PositionColored.Stride);
            buffer.Device.VertexFormat = PositionColored.FVF;
            buffer.Device.DrawPrimitives(PrimitiveType.TriangleFan, 0, 2);
        }

        public static void DrawTextured(VertexBuffer buffer)
        {
            buffer.Device.SetStreamSource(0, buffer, 0, PositionTextured.Stride);
            buffer.Device.VertexFormat = PositionTextured.FVF;
            buffer.Device.DrawPrimitives(PrimitiveType.TriangleFan, 0, 2);
        }


        // Optimizations

        public static void OptimizeMeshFile(Device device, string file)
        {
            OptimizeMeshFile(device, file, file);
        }

        public static void OptimizeMeshFile(Device device, string inFile, string outFile)
        {
            Mesh mesh = Mesh.FromFile(device, inFile, MeshFlags.SystemMemory);
            mesh.OptimizeInPlace(MeshOptimizeFlags.StripReorder);
            Mesh.ToXFile(mesh, outFile, XFileFormat.Compressed);
            mesh.Dispose();
        }
    }
}
