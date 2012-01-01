using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using BulletSharp;
using BulletSharp.SoftBody;
using SharpDX;
using SharpDX.Direct3D;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using Buffer = SharpDX.Direct3D10.Buffer;
using DataStream = SharpDX.DataStream;
using Device = SharpDX.Direct3D10.Device;
using Matrix = BulletSharp.Matrix;
using Mesh = SharpDX.Direct3D10.Mesh;
using Vector3 = BulletSharp.Vector3;

namespace DemoFramework.SharpDX
{
    public struct InstanceData
    {
        public Matrix WorldTransform;
        public uint Color;

        public static readonly int SizeInBytes = Marshal.SizeOf(typeof(InstanceData));
    }

    // Contains the geometry buffers and information of all instances of a particular shape.
    public class ShapeData : System.IDisposable
    {
        public Buffer VertexBuffer;
        public int VertexCount;

        public Buffer IndexBuffer;
        public int IndexCount;
        public Format IndexFormat;

        public Buffer InstanceDataBuffer;
        public List<InstanceData> InstanceDataList;

        public PrimitiveTopology PrimitiveTopology;
        public VertexBufferBinding[] BufferBindings;

        public ShapeData()
        {
            InstanceDataList = new List<InstanceData>();
            PrimitiveTopology = PrimitiveTopology.TriangleList;
            BufferBindings = new VertexBufferBinding[2];
        }

        public void SetVertexBuffer(Device device, Vector3[] vectors)
        {
            BufferDescription vertexBufferDesc = new BufferDescription()
            {
                SizeInBytes = Marshal.SizeOf(typeof(Vector3)) * vectors.Length,
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.VertexBuffer
            };

            using (var data = new DataStream(vertexBufferDesc.SizeInBytes, false, true))
            {
                data.WriteRange(vectors);
                VertexBuffer = new Buffer(device, data, vertexBufferDesc);
            }

            BufferBindings[0] = new VertexBufferBinding(VertexBuffer, 24, 0);
        }

        // Used with soft bodies
        public void SetDynamicVertexBuffer(Device device, Vector3[] vectors)
        {
            if (VertexBuffer != null && VertexCount * 2 == vectors.Length)
            {
                // Update existing buffer
                using (var data = VertexBuffer.Map(MapMode.WriteDiscard))
                {
                    data.WriteRange(vectors, 0, vectors.Length);
                    VertexBuffer.Unmap();
                }
            }
            else
            {
                // Create new buffer
                if (VertexBuffer != null)
                    VertexBuffer.Dispose();

                BufferDescription vertexBufferDesc = new BufferDescription()
                {
                    SizeInBytes = Marshal.SizeOf(typeof(Vector3)) * vectors.Length,
                    Usage = ResourceUsage.Dynamic,
                    BindFlags = BindFlags.VertexBuffer,
                    CpuAccessFlags = CpuAccessFlags.Write
                };

                using (var data = new DataStream(vertexBufferDesc.SizeInBytes, false, true))
                {
                    data.WriteRange(vectors);
                    VertexBuffer = new Buffer(device, data, vertexBufferDesc);
                }

                BufferBindings[0] = new VertexBufferBinding(VertexBuffer, 24, 0);
            }
        }

        public void SetIndexBuffer(Device device, ushort[] indices)
        {
            IndexFormat = Format.R16_UInt;

            BufferDescription indexBufferDesc = new BufferDescription()
            {
                SizeInBytes = sizeof(ushort) * indices.Length,
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.IndexBuffer
            };

            using (var data = new DataStream(indexBufferDesc.SizeInBytes, false, true))
            {
                data.WriteRange(indices);
                IndexBuffer = new Buffer(device, data, indexBufferDesc);
            }
        }

        public void SetIndexBuffer(Device device, uint[] indices)
        {
            IndexFormat = Format.R32_UInt;

            BufferDescription indexBufferDesc = new BufferDescription()
            {
                SizeInBytes = sizeof(uint) * indices.Length,
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.IndexBuffer
            };

            using (var data = new DataStream(indexBufferDesc.SizeInBytes, false, true))
            {
                data.WriteRange(indices);
                IndexBuffer = new Buffer(device, data, indexBufferDesc);
            }
        }

        public void Dispose()
        {
            if (VertexBuffer != null)
            {
                VertexBuffer.Dispose();
                VertexBuffer = null;
            }
            if (IndexBuffer != null)
            {
                IndexBuffer.Dispose();
                IndexBuffer = null;
            }
            if (InstanceDataBuffer != null)
            {
                InstanceDataBuffer.Dispose();
                InstanceDataBuffer = null;
            }
        }
    }

    // This class creates graphical objects (boxes, cones, cylinders, spheres) on the fly.
    public class MeshFactory : System.IDisposable
    {
        Demo demo;
        Device device;
        InputAssemblerStage inputAssembler;
        Dictionary<CollisionShape, ShapeData> shapes = new Dictionary<CollisionShape, ShapeData>();
        List<CollisionShape> removeList = new List<CollisionShape>();
        Effect planeShader = null;

        BufferDescription instanceDataDesc;
        InputLayout inputLayout;
        uint groundColor;
        uint activeColor;
        uint passiveColor;
        uint softBodyColor;
        int linkColor = System.Drawing.Color.Black.ToArgb();

        public MeshFactory(SharpDXGraphics graphics)
        {
            this.device = graphics.Device;
            this.inputAssembler = device.InputAssembler;
            this.demo = graphics.Demo;

            instanceDataDesc = new BufferDescription()
            {
                Usage = ResourceUsage.Dynamic,
                BindFlags = BindFlags.VertexBuffer,
                CpuAccessFlags = CpuAccessFlags.Write,
                OptionFlags = ResourceOptionFlags.None,
            };

            InputElement[] elements = new InputElement[]
            {
                new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0, InputClassification.PerVertexData, 0),
                new InputElement("NORMAL", 0, Format.R32G32B32_Float, 12, 0, InputClassification.PerVertexData, 0),
                new InputElement("WORLD", 0, Format.R32G32B32A32_Float, 0, 1, InputClassification.PerInstanceData, 1),
                new InputElement("WORLD", 1, Format.R32G32B32A32_Float, 16, 1, InputClassification.PerInstanceData, 1),
                new InputElement("WORLD", 2, Format.R32G32B32A32_Float, 32, 1, InputClassification.PerInstanceData, 1),
                new InputElement("WORLD", 3, Format.R32G32B32A32_Float, 48, 1, InputClassification.PerInstanceData, 1),
                new InputElement("COLOR", 0, Format.R8G8B8A8_UNorm, 64, 1, InputClassification.PerInstanceData, 1)
            };
            inputLayout = new InputLayout(device, graphics.GetEffectPass().Description.Signature, elements);

            Color c = Color.Green;
            groundColor = (uint)c.R + ((uint)c.G << 8) + ((uint)c.B << 16) + ((uint)c.A << 24);
            c = Color.Orange;
            activeColor = (uint)c.R + ((uint)c.G << 8) + ((uint)c.B << 16) + ((uint)c.A << 24);
            c = Color.OrangeRed;
            passiveColor = (uint)c.R + ((uint)c.G << 8) + ((uint)c.B << 16) + ((uint)c.A << 24);
            c = Color.LightBlue;
            softBodyColor = (uint)c.R + ((uint)c.G << 8) + ((uint)c.B << 16) + ((uint)c.A << 24);
        }

        public void Clear()
        {
            foreach (ShapeData shapeData in shapes.Values)
            {
                shapeData.Dispose();
            }
            shapes.Clear();
        }

        public void Dispose()
        {
            Clear();

            if (planeShader != null)
                planeShader.Dispose();
        }

        ShapeData CreateBoxShape(BoxShape shape)
        {
            Vector3 size = shape.HalfExtentsWithMargin;
            float x = size.X;
            float y = size.Y;
            float z = size.Z;

            ShapeData shapeData = new ShapeData();
            shapeData.VertexCount = 36;

            Vector3[] vectors = new Vector3[shapeData.VertexCount * 2];
            Vector3 normal;
            int v = 0;

            // Draw two sides
            for (int i = 1; i != -3; i -= 2)
            {
                normal = new Vector3(i, 0, 0);
                vectors[v++] = new Vector3(i * x, y, -z); // Position
                vectors[v++] = normal;
                vectors[v++] = new Vector3(i * x, -y, -z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(i * x, -y, z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(i * x, y, -z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(i * x, y, z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(i * x, -y, z);
                vectors[v++] = normal;
            }

            for (int i = 1; i != -3; i -= 2)
            {
                normal = new Vector3(0, 0, i);
                vectors[v++] = new Vector3(-x, y, i * z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(-x, -y, i * z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(x, -y, i * z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(-x, y, i * z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(x, y, i * z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(x, -y, i * z);
                vectors[v++] = normal;
            }

            for (int i = 1; i != -3; i -= 2)
            {
                normal = new Vector3(0, i, 0);
                vectors[v++] = new Vector3(-x, i * y, -z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(x, i * y, -z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(-x, i * y, z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(x, i * y, z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(-x, i * y, z);
                vectors[v++] = normal;
                vectors[v++] = new Vector3(x, i * y, -z);
                vectors[v++] = normal;
            }

            shapeData.SetVertexBuffer(device, vectors);

            return shapeData;
        }

        ShapeData CreateCapsuleShape(CapsuleShape shape)
        {
            int up = shape.UpAxis;
            float radius = shape.Radius;
            float cylinderHalfHeight = shape.HalfHeight;

            int slices = (int)(radius * 10.0f);
            int stacks = (int)(radius * 10.0f);
            slices = (slices > 16) ? 16 : (slices < 3) ? 3 : slices;
            stacks = (stacks > 16) ? 16 : (stacks < 2) ? 2 : stacks;

            float hAngleStep = (float)Math.PI * 2 / slices;
            float vAngleStep = (float)Math.PI / stacks;

            ShapeData shapeData = new ShapeData();

            shapeData.VertexCount = 2 + slices * (stacks - 1);
            shapeData.IndexCount = 6 * slices * (stacks - 1);

            Vector3[] vertices = new Vector3[shapeData.VertexCount * 2];
            ushort[] indices = new ushort[shapeData.IndexCount];

            int i = 0, v = 0;


            // Vertices
            // Top and bottom
            vertices[v++] = GetVectorByAxis(new Vector3(0, -cylinderHalfHeight - radius, 0), up);
            vertices[v++] = GetVectorByAxis(-Vector3.UnitY, up);
            vertices[v++] = GetVectorByAxis(new Vector3(0, cylinderHalfHeight + radius, 0), up);
            vertices[v++] = GetVectorByAxis(Vector3.UnitY, up);

            // Stacks
            int j, k;
            float angle = 0;
            float vAngle = -(float)Math.PI / 2;
            Vector3 vTemp;
            Vector3 cylinderOffset = GetVectorByAxis(new Vector3(0, -cylinderHalfHeight, 0), up);
            for (j = 0; j < stacks - 1; j++)
            {
                float prevAngle = vAngle;
                vAngle += vAngleStep;

                if (vAngle > 0 && prevAngle < 0)
                {
                    cylinderOffset = GetVectorByAxis(new Vector3(0, cylinderHalfHeight, 0), up);
                }

                for (k = 0; k < slices; k++)
                {
                    angle += hAngleStep;

                    vTemp = GetVectorByAxis(new Vector3((float)Math.Cos(vAngle) * (float)Math.Sin(angle),
                        (float)Math.Sin(vAngle),
                        (float)Math.Cos(vAngle) * (float)Math.Cos(angle)), up);
                    vertices[v++] = vTemp * radius + cylinderOffset;
                    vertices[v++] = Vector3.Normalize(vTemp);
                }
            }


            // Indices
            // Top cap
            byte index = 2;
            for (k = 0; k < slices; k++)
            {
                indices[i++] = 0;
                indices[i++] = index;
                index++;
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
                    indices[i++] = indices[i - sliceDiff];
                    indices[i++] = indices[i - sliceDiff];
                    indices[i++] = index;
                    index++;
                }

                for (k = 0; k < slices; k++)
                {
                    indices[i++] = indices[i - sliceDiff];
                    indices[i++] = indices[i - sliceDiff];
                    indices[i++] = indices[i - sliceDiff + 2];
                }
                indices[i - 1] = indices[i - sliceDiff + 1];
            }

            // Bottom cap
            index--;
            for (k = 0; k < slices; k++)
            {
                indices[i++] = 1;
                indices[i++] = index;
                index--;
                indices[i++] = index;
            }
            indices[i - 1] = indices[i - sliceDiff + 1];

            shapeData.SetVertexBuffer(device, vertices);
            shapeData.SetIndexBuffer(device, indices);

            return shapeData;
        }
        /*
        Mesh CreateConeShape(ConeShape shape)
        {
            Mesh mesh = Mesh.CreateCylinder(device, 0, shape.Radius, shape.Height, 16, 1);
            shapes.Add(shape, mesh);
            return mesh;
        }
        */

        Vector3 GetVectorByAxis(Vector3 vector, int axis)
        {
            switch (axis)
            {
                case 0:
                    return new Vector3(vector.Y, vector.Z, vector.X);
                case 1:
                    return vector;
                default:
                    return new Vector3(vector.Z, vector.X, vector.Y);
            }
        }

        ShapeData CreateCylinderShape(CylinderShape shape)
        {
            int up = shape.UpAxis;
            float radius = shape.Radius;
            float halfHeight = shape.HalfExtentsWithoutMargin[up] + shape.Margin;

            int numSteps = 10;
            float angleStep = (2 * (float)Math.PI) / numSteps;

            ShapeData shapeData = new ShapeData();
            shapeData.VertexCount = 2 + 6 * numSteps;
            shapeData.IndexCount = (4 * numSteps + 2) * 3;

            Vector3[] vertices = new Vector3[shapeData.VertexCount * 2];
            ushort[] indices = new ushort[shapeData.IndexCount];

            int i = 0, v = 0;
            ushort index = 0;
            ushort baseIndex;
            Vector3 normal;

            // Draw two sides
            for (int side = 1; side != -3; side -= 2)
            {
                normal = GetVectorByAxis(side * Vector3.UnitY, up);

                baseIndex = index;
                vertices[v++] = GetVectorByAxis(new Vector3(0, side * halfHeight, 0), up);
                vertices[v++] = normal;

                vertices[v++] = GetVectorByAxis(new Vector3(0, side * halfHeight, radius), up);
                vertices[v++] = normal;
                index += 2;

                for (int j = 1; j < numSteps; j++)
                {
                    float x = radius * (float)Math.Sin(j * angleStep);
                    float z = radius * (float)Math.Cos(j * angleStep);

                    vertices[v++] = GetVectorByAxis(new Vector3(x, side * halfHeight, z), up);
                    vertices[v++] = normal;

                    indices[i++] = baseIndex;
                    indices[i++] = (ushort)(index - 1);
                    indices[i++] = index++;
                }
                indices[i++] = baseIndex;
                indices[i++] = (ushort)(index - 1);
                indices[i++] = (ushort)(baseIndex + 1);
            }


            normal = GetVectorByAxis(new Vector3(0, 0, radius), up);
            normal.Normalize();

            baseIndex = index;
            vertices[v++] = GetVectorByAxis(new Vector3(0, halfHeight, radius), up);
            vertices[v++] = normal;

            vertices[v++] = GetVectorByAxis(new Vector3(0, -halfHeight, radius), up);
            vertices[v++] = normal;
            index += 2;

            for (int j = 1; j < numSteps + 1; j++)
            {
                float x = radius * (float)Math.Sin(j * angleStep);
                float z = radius * (float)Math.Cos(j * angleStep);

                normal = GetVectorByAxis(new Vector3(x, 0, z), up);
                normal.Normalize();

                vertices[v++] = GetVectorByAxis(new Vector3(x, halfHeight, z), up);
                vertices[v++] = normal;

                vertices[v++] = GetVectorByAxis(new Vector3(x, -halfHeight, z), up);
                vertices[v++] = normal;

                indices[i++] = (ushort)(index - 2);
                indices[i++] = (ushort)(index - 1);
                indices[i++] = index;
                indices[i++] = index;
                indices[i++] = (ushort)(index - 1);
                indices[i++] = (ushort)(index + 1);
                index += 2;
            }
            indices[i++] = (ushort)(index - 2);
            indices[i++] = (ushort)(index - 1);
            indices[i++] = baseIndex;
            indices[i++] = baseIndex;
            indices[i++] = (ushort)(index - 1);
            indices[i++] = (ushort)(baseIndex + 1);

            shapeData.SetVertexBuffer(device, vertices);
            shapeData.SetIndexBuffer(device, indices);

            return shapeData;
        }
        /*
        Mesh CreateGImpactMeshShape(GImpactMeshShape shape)
        {
            BulletSharp.DataStream verts, indices;
            int numVerts, numFaces;
            PhyScalarType vertsType, indicesType;
            int vertexStride, indexStride;
            shape.MeshInterface.GetLockedReadOnlyVertexIndexData(out verts, out numVerts, out vertsType, out vertexStride,
                out indices, out indexStride, out numFaces, out indicesType);

            bool index32 = numVerts > 65536;

            Mesh mesh = new Mesh(device, numFaces, numVerts,
                MeshFlags.SystemMemory | (index32 ? MeshFlags.Use32Bit : 0), VertexFormat.Position | VertexFormat.Normal);

            SlimDX.DataStream vertexBuffer = mesh.LockVertexBuffer(LockFlags.Discard);
            while (vertexBuffer.Position < vertexBuffer.Length)
            {
                vertexBuffer.Write(verts.Read<Vector3>());
                vertexBuffer.Position += 12;
            }
            mesh.UnlockVertexBuffer();

            SlimDX.DataStream indexBuffer = mesh.LockIndexBuffer(LockFlags.Discard);
            if (index32)
            {
                while (indexBuffer.Position < indexBuffer.Length)
                    indexBuffer.Write(indices.Read<int>());
            }
            else
            {
                while (indexBuffer.Position < indexBuffer.Length)
                    indexBuffer.Write((ushort)indices.Read<int>());
            }
            mesh.UnlockIndexBuffer();

            mesh.ComputeNormals();
            return mesh;
        }
        */
        ShapeData CreateConvexHullShape(ConvexHullShape shape)
        {
            ConvexPolyhedron poly = shape.ConvexPolyhedron;
            if (poly != null)
            {
                throw new NotImplementedException();
            }

            ShapeHull hull = new ShapeHull(shape);
            hull.BuildHull(shape.Margin);

            int indexCount = hull.NumIndices;
            UIntArray indices = hull.Indices;
            Vector3Array points = hull.Vertices;

            ShapeData shapeData = new ShapeData();
            shapeData.VertexCount = indexCount;

            Vector3[] vertices = new Vector3[indexCount * 2];

            int v = 0, i;
            for (i = 0; i < indexCount; i += 3)
            {
                Vector3 v0 = points[(int)indices[i]];
                Vector3 v1 = points[(int)indices[i + 1]];
                Vector3 v2 = points[(int)indices[i + 2]];

                Vector3 v01 = v0 - v1;
                Vector3 v02 = v0 - v2;
                Vector3 normal = Vector3.Cross(v01, v02);
                normal.Normalize();

                vertices[v++] = v0;
                vertices[v++] = normal;
                vertices[v++] = v1;
                vertices[v++] = normal;
                vertices[v++] = v2;
                vertices[v++] = normal;
            }

            shapeData.SetVertexBuffer(device, vertices);

            return shapeData;
        }
        /*
        Mesh CreateMultiSphereShape(MultiSphereShape shape)
        {
            Mesh mesh = null;

            int i;
            for (i = 0; i < shape.SphereCount; i++)
            {
                Vector3 position = shape.GetSpherePosition(i);

                Mesh sphereMesh = Mesh.CreateSphere(device, shape.GetSphereRadius(i), 12, 12);
                if (i == 0)
                {
                    Matrix[] transform = new Matrix[] { Matrix.Translation(position) };
                    mesh = Mesh.Concatenate(device, new Mesh[] { sphereMesh }, MeshFlags.Managed, transform, null);
                }
                else
                {
                    Mesh multiSphereMeshNew;
                    Matrix[] transform = new Matrix[] { Matrix.Identity, Matrix.Translation(position) };
                    multiSphereMeshNew = Mesh.Concatenate(device, new Mesh[] { mesh, sphereMesh }, MeshFlags.Managed, transform, null);
                    mesh.Dispose();
                    mesh = multiSphereMeshNew;
                }
                sphereMesh.Dispose();
            }
            
            complexShapes.Add(shape, mesh);
            return mesh;
        }
        */
        ShapeData CreateSphereShape(SphereShape shape)
        {
            float radius = shape.Radius;

            int slices = (int)(radius * 10.0f);
            int stacks = (int)(radius * 10.0f);
            slices = (slices > 16) ? 16 : (slices < 3) ? 3 : slices;
            stacks = (stacks > 16) ? 16 : (stacks < 2) ? 2 : stacks;

            float hAngleStep = (float)Math.PI * 2 / slices;
            float vAngleStep = (float)Math.PI / stacks;

            ShapeData shapeData = new ShapeData();

            shapeData.VertexCount = 2 + slices * (stacks - 1);
            shapeData.IndexCount = 6 * slices * (stacks - 1);

            Vector3[] vertices = new Vector3[shapeData.VertexCount * 2];
            ushort[] indices = new ushort[shapeData.IndexCount];

            int i = 0, v = 0;


            // Vertices
            // Top and bottom
            vertices[v++] = new Vector3(0, -radius, 0);
            vertices[v++] = -Vector3.UnitY;
            vertices[v++] = new Vector3(0, radius, 0);
            vertices[v++] = Vector3.UnitY;

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
                    vertices[v++] = Vector3.Normalize(vTemp);
                }
            }


            // Indices
            // Top cap
            byte index = 2;
            for (k = 0; k < slices; k++)
            {
                indices[i++] = 0;
                indices[i++] = index;
                index++;
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
                    indices[i++] = indices[i - sliceDiff];
                    indices[i++] = indices[i - sliceDiff];
                    indices[i++] = index;
                    index++;
                }

                for (k = 0; k < slices; k++)
                {
                    indices[i++] = indices[i - sliceDiff];
                    indices[i++] = indices[i - sliceDiff];
                    indices[i++] = indices[i - sliceDiff + 2];
                }
                indices[i - 1] = indices[i - sliceDiff + 1];
            }

            // Bottom cap
            index--;
            for (k = 0; k < slices; k++)
            {
                indices[i++] = 1;
                indices[i++] = index;
                index--;
                indices[i++] = index;
            }
            indices[i - 1] = indices[i - sliceDiff + 1];

            shapeData.SetVertexBuffer(device, vertices);
            shapeData.SetIndexBuffer(device, indices);

            return shapeData;
        }
        /*
        Mesh CreateStaticPlaneShape(StaticPlaneShape shape)
        {
            // Load shader
            if (planeShader == null)
            {
                Assembly assembly = Assembly.GetExecutingAssembly();
                Stream shaderStream = assembly.GetManifestResourceStream("DemoFramework.checker_shader.fx");

                planeShader = Effect.FromStream(device, shaderStream, ShaderFlags.None);
            }


            Vector3[] vertices = new Vector3[4 * 2];

            Mesh mesh = new Mesh(device, 2, 4, MeshFlags.SystemMemory, VertexFormat.Position | VertexFormat.Normal);

            Vector3 planeOrigin = shape.PlaneNormal * shape.PlaneConstant;
            Vector3 vec0, vec1;
            PlaneSpace1(shape.PlaneNormal, out vec0, out vec1);
            float size = 1000;

            Vector3[] verts = new Vector3[4]
                {
                    planeOrigin + vec0*size,
                    planeOrigin - vec0*size,
                    planeOrigin + vec1*size,
                    planeOrigin - vec1*size
                };

            SlimDX.DataStream vertexBuffer = mesh.LockVertexBuffer(LockFlags.Discard);
            vertexBuffer.Write(verts[0]);
            vertexBuffer.Position += 12;
            vertexBuffer.Write(verts[1]);
            vertexBuffer.Position += 12;
            vertexBuffer.Write(verts[2]);
            vertexBuffer.Position += 12;
            vertexBuffer.Write(verts[3]);
            vertexBuffer.Position += 12;
            mesh.UnlockVertexBuffer();

            SlimDX.DataStream indexBuffer = mesh.LockIndexBuffer(LockFlags.Discard);
            indexBuffer.Write((short)1);
            indexBuffer.Write((short)2);
            indexBuffer.Write((short)0);
            indexBuffer.Write((short)1);
            indexBuffer.Write((short)3);
            indexBuffer.Write((short)0);
            mesh.UnlockIndexBuffer();

            mesh.ComputeNormals();

            complexShapes.Add(shape, mesh);

            return mesh;
        }
        */

        ShapeData CreateTriangleMeshShape(TriangleMeshShape shape)
        {
            StridingMeshInterface meshInterface = shape.MeshInterface.UpcastDetect();

            BulletSharp.DataStream vertexStream, indexStream;
            int numVerts, numFaces;
            PhyScalarType vertsType, indicesType;
            int vertexStride, indexStride;
            meshInterface.GetLockedReadOnlyVertexIndexData(out vertexStream, out numVerts, out vertsType, out vertexStride,
                out indexStream, out indexStride, out numFaces, out indicesType);

            ShapeData shapeData = new ShapeData();
            shapeData.VertexCount = numVerts;
            shapeData.IndexCount = numFaces * 3;

            Vector3[] vertices = new Vector3[shapeData.VertexCount * 2];
            int v = 0;
            int vStrideExtra = vertexStride - Marshal.SizeOf(typeof(Vector3));
            while (vertexStream.Position < vertexStream.Length)
            {
                Vector3 v0 = vertexStream.Read<Vector3>();
                vertexStream.Position += vStrideExtra;
                Vector3 v1 = vertexStream.Read<Vector3>();
                vertexStream.Position += vStrideExtra;
                Vector3 v2 = vertexStream.Read<Vector3>();
                vertexStream.Position += vStrideExtra;

                Vector3 v01 = v0 - v1;
                Vector3 v02 = v0 - v2;
                Vector3 normal = Vector3.Cross(v01, v02);

                vertices[v++] = v0;
                vertices[v++] = normal;
                vertices[v++] = v1;
                vertices[v++] = normal;
                vertices[v++] = v2;
                vertices[v++] = normal;
            }

            int i = 0;
            if (numVerts > 65536)
            {
                uint[] indices = new uint[shapeData.IndexCount];
                while (indexStream.Position < indexStream.Length)
                    indices[i++] = indexStream.Read<uint>();
                shapeData.SetIndexBuffer(device, indices);
            }
            else
            {
                ushort[] indices = new ushort[shapeData.IndexCount];
                while (indexStream.Position < indexStream.Length)
                    indices[i++] = (ushort)indexStream.Read<uint>();
                shapeData.SetIndexBuffer(device, indices);
            }

            shapeData.SetVertexBuffer(device, vertices);

            return shapeData;
        }

        ShapeData InitShapeData(CollisionShape shape)
        {
            ShapeData shapeData;

            if (shapes.TryGetValue(shape, out shapeData) == false)
            {
                switch (shape.ShapeType)
                {
                    case BroadphaseNativeType.SoftBodyShape:
                        shapeData = CreateSoftBody();
                        break;
                    case BroadphaseNativeType.BoxShape:
                        shapeData = CreateBoxShape(shape as BoxShape);
                        break;
                    case BroadphaseNativeType.CapsuleShape:
                        shapeData = CreateCapsuleShape(shape as CapsuleShape);
                        break;
                    case BroadphaseNativeType.CylinderShape:
                        shapeData = CreateCylinderShape(shape as CylinderShape);
                        break;
                    case BroadphaseNativeType.Convex2DShape:
                        return InitShapeData((shape as Convex2DShape).ChildShape);
                    case BroadphaseNativeType.ConvexHullShape:
                        shapeData = CreateConvexHullShape(shape as ConvexHullShape);
                        break;
                    case BroadphaseNativeType.SphereShape:
                        shapeData = CreateSphereShape(shape as SphereShape);
                        break;
                    case BroadphaseNativeType.TriangleMeshShape:
                        shapeData = CreateTriangleMeshShape(shape as TriangleMeshShape);
                        break;
                    default:
                        throw new NotImplementedException();
                }

                // Create an initial instance data buffer for a single instance
                instanceDataDesc.SizeInBytes = InstanceData.SizeInBytes;
                shapeData.InstanceDataBuffer = new Buffer(device, instanceDataDesc);
                shapeData.BufferBindings[1] = new VertexBufferBinding(shapeData.InstanceDataBuffer, instanceDataDesc.SizeInBytes, 0);

                shapes.Add(shape, shapeData);
            }

            return shapeData;
        }

        void InitInstanceData(CollisionObject colObj, CollisionShape shape, ref Matrix transform)
        {
            if (shape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                foreach (CompoundShapeChild child in (shape as CompoundShape).ChildList)
                {
                    Matrix childTransform = child.Transform * transform;
                    InitInstanceData(colObj, child.ChildShape, ref childTransform);
                }
            }
            else if (shape.ShapeType == BroadphaseNativeType.SoftBodyShape)
            {
                ShapeData shapeData = InitShapeData(shape);
                UpdateSoftBody(colObj as SoftBody, shapeData);

                shapeData.InstanceDataList.Add(new InstanceData()
                {
                    WorldTransform = transform,
                    Color = softBodyColor
                });
            }
            else
            {
                InitShapeData(shape).InstanceDataList.Add(new InstanceData()
                {
                    WorldTransform = transform,
                    Color = ground.Equals(colObj.UserObject) ? groundColor :
                        colObj.ActivationState == ActivationState.ActiveTag ? activeColor : passiveColor
                });
            }
        }

        string ground = "Ground";

        public void InitInstancedRender(AlignedCollisionObjectArray objects)
        {
            // Clear instance data
            foreach (ShapeData s in shapes.Values)
                s.InstanceDataList.Clear();
            removeList.Clear();

            int i = objects.Count - 1;
            for (; i >= 0; i--)
            {
                CollisionObject colObj = objects[i];

                Matrix transform;
                if (colObj is SoftBody)
                {
                    if (demo.IsDebugDrawEnabled)
                        continue;
                    transform = Matrix.Identity;
                }
                else
                {
                    (colObj as RigidBody).GetWorldTransform(out transform);
                }
                InitInstanceData(colObj, colObj.CollisionShape, ref transform);
            }

            foreach (KeyValuePair<CollisionShape, ShapeData> sh in shapes)
            {
                ShapeData s = sh.Value;
                // Is the instance buffer the right size?
                if (s.InstanceDataBuffer.Description.SizeInBytes != s.InstanceDataList.Count * InstanceData.SizeInBytes)
                {
                    // No, recreate it
                    s.InstanceDataBuffer.Dispose();

                    if (s.InstanceDataList.Count == 0)
                    {
                        if (s.IndexBuffer != null)
                            s.IndexBuffer.Dispose();
                        s.VertexBuffer.Dispose();
                        removeList.Add(sh.Key);
                        continue;
                    }

                    instanceDataDesc.SizeInBytes = s.InstanceDataList.Count * InstanceData.SizeInBytes;
                    s.InstanceDataBuffer = new Buffer(device, instanceDataDesc);
                    s.BufferBindings[1] = new VertexBufferBinding(s.InstanceDataBuffer, InstanceData.SizeInBytes, 0);
                }

                // Copy the instance data over to the instance buffer
                using (var data = s.InstanceDataBuffer.Map(MapMode.WriteDiscard))
                {
                    data.WriteRange(s.InstanceDataList.ToArray());
                    s.InstanceDataBuffer.Unmap();
                }
            }

            if (removeList.Count != 0)
            {
                for (i = removeList.Count - 1; i >= 0; i--)
                {
                    shapes.Remove(removeList[i]);
                }
            }
        }

        public void RenderInstanced()
        {
            inputAssembler.InputLayout = inputLayout;

            foreach (ShapeData s in shapes.Values)
            {
                inputAssembler.SetVertexBuffers(0, s.BufferBindings);
                inputAssembler.PrimitiveTopology = s.PrimitiveTopology;
                if (s.IndexBuffer != null)
                {
                    inputAssembler.SetIndexBuffer(s.IndexBuffer, s.IndexFormat, 0);
                    device.DrawIndexedInstanced(s.IndexCount, s.InstanceDataList.Count, 0, 0, 0);
                }
                else
                {
                    device.DrawInstanced(s.VertexCount, s.InstanceDataList.Count, 0, 0);
                }
            }
        }

        public void RenderComplexShape(CollisionShape shape, Mesh mesh)
        {
            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.StaticPlane:
                    //RenderStaticPlaneShape(mesh);
                    break;
                case BroadphaseNativeType.CapsuleShape:
                    //RenderCapsuleShape(mesh);
                    break;
                case BroadphaseNativeType.MultiSphereShape:
                    //RenderMultiSphereShape((MultiSphereShape)shape, mesh);
                    break;
            }
        }
        /*
        public void RenderCapsuleShape(Mesh mesh)
        {
            mesh.DrawSubset(0);
            mesh.DrawSubset(1);
            mesh.DrawSubset(2);
        }

        public void RenderMultiSphereShape(MultiSphereShape shape, Mesh mesh)
        {
            int count = shape.SphereCount;
            for (int i = 0; i < count; i++)
                mesh.DrawSubset(i);
        }

        void RenderStaticPlaneShape(Mesh mesh)
        {
            Cull cullMode = device.GetRenderState<Cull>(RenderState.CullMode);
            device.SetRenderState(RenderState.CullMode, Cull.None);
            planeShader.Begin();
            Matrix matrix = device.GetTransform(TransformState.World);
            planeShader.SetValue("World", matrix);
            matrix = device.GetTransform(TransformState.View) * device.GetTransform(TransformState.Projection);
            planeShader.SetValue("ViewProjection", matrix);
            planeShader.BeginPass(0);
            mesh.DrawSubset(0);
            planeShader.EndPass();
            planeShader.End();
            device.SetRenderState(RenderState.CullMode, cullMode);
        }

        void PlaneSpace1(Vector3 n, out Vector3 p, out Vector3 q)
        {
            if (Math.Abs(n[2]) > (Math.Sqrt(2) / 2))
            {
                // choose p in y-z plane
                float a = n[1] * n[1] + n[2] * n[2];
                float k = 1.0f / (float)Math.Sqrt(a);
                p = new Vector3(0, -n[2] * k, n[1] * k);
                // set q = n x p
                q = Vector3.Cross(n, p);
            }
            else
            {
                // choose p in x-y plane
                float a = n[0] * n[0] + n[1] * n[1];
                float k = 1.0f / (float)Math.Sqrt(a);
                p = new Vector3(-n[1] * k, n[0] * k, 0);
                // set q = n x p
                q = Vector3.Cross(n, p);
            }
        }
        */

        public ShapeData CreateSoftBody()
        {
            // Soft body geometry is recreated each frame. Nothing to do here.
            return new ShapeData();
        }

        public void UpdateSoftBody(SoftBody softBody, ShapeData shapeData)
        {
            AlignedFaceArray faces = softBody.Faces;

            if (faces.Count != 0)
            {
                shapeData.VertexCount = faces.Count * 3;

                Vector3[] vectors = new Vector3[shapeData.VertexCount * 2];
                int v = 0;

                int i;
                for (i = 0; i < faces.Count; i++)
                {
                    NodePtrArray nodes = faces[i].N;
                    Node n0 = nodes[0];
                    Node n1 = nodes[1];
                    Node n2 = nodes[2];
                    n0.GetX(out vectors[v]);
                    n0.GetNormal(out vectors[v + 1]);
                    n1.GetX(out vectors[v + 2]);
                    n1.GetNormal(out vectors[v + 3]);
                    n2.GetX(out vectors[v + 4]);
                    n2.GetNormal(out vectors[v + 5]);
                    v += 6;
                }

                shapeData.SetDynamicVertexBuffer(device, vectors);
            }
            else
            {
                AlignedTetraArray tetras = softBody.Tetras;
                int tetraCount = tetras.Count;

                if (tetraCount != 0)
                {
                    shapeData.VertexCount = tetraCount * 12;

                    Vector3[] vectors = new Vector3[tetraCount * 24];
                    int v = 0;

                    for (int i = 0; i < tetraCount; i++)
                    {
                        NodePtrArray nodes = tetras[i].Nodes;
                        Vector3 v0 = nodes[0].X;
                        Vector3 v1 = nodes[1].X;
                        Vector3 v2 = nodes[2].X;
                        Vector3 v3 = nodes[3].X;
                        Vector3 v10 = v1 - v0;
                        Vector3 v02 = v0 - v2;

                        Vector3 normal = Vector3.Cross(v10, v02);
                        vectors[v] = v0;
                        vectors[v + 1] = normal;
                        vectors[v + 2] = v1;
                        vectors[v + 3] = normal;
                        vectors[v + 4] = v2;
                        vectors[v + 5] = normal;

                        normal = Vector3.Cross(v10, v3 - v0);
                        vectors[v + 6] = v0;
                        vectors[v + 7] = normal;
                        vectors[v + 8] = v1;
                        vectors[v + 9] = normal;
                        vectors[v + 10] = v3;
                        vectors[v + 11] = normal;

                        normal = Vector3.Cross(v2 - v1, v3 - v1);
                        vectors[v + 12] = v1;
                        vectors[v + 13] = normal;
                        vectors[v + 14] = v2;
                        vectors[v + 15] = normal;
                        vectors[v + 16] = v3;
                        vectors[v + 17] = normal;

                        normal = Vector3.Cross(v02, v3 - v2);
                        vectors[v + 18] = v2;
                        vectors[v + 19] = normal;
                        vectors[v + 20] = v0;
                        vectors[v + 21] = normal;
                        vectors[v + 22] = v3;
                        vectors[v + 23] = normal;
                        v += 24;
                    }

                    shapeData.SetDynamicVertexBuffer(device, vectors);
                }
                else if (softBody.Links.Count != 0)
                {
                    AlignedLinkArray links = softBody.Links;
                    int linkCount = links.Count;
                    shapeData.VertexCount = linkCount * 2;

                    Vector3[] vectors = new Vector3[linkCount * 4];

                    for (int i = 0; i < linkCount; i++)
                    {
                        NodePtrArray nodes = links[i].Nodes;
                        nodes[0].GetX(out vectors[i * 4]);
                        nodes[1].GetX(out vectors[i * 4 + 2]);
                    }

                    shapeData.PrimitiveTopology = PrimitiveTopology.LineList;
                    shapeData.SetDynamicVertexBuffer(device, vectors);
                }
                else
                {
                    throw new NotImplementedException();
                }
            }
        }

        /*
        public void RenderSoftBodyTextured(SoftBody softBody)
        {
            if (!(softBody.UserObject is Array))
                return;

            object[] userObjArr = softBody.UserObject as object[];
            FloatArray vertexBuffer = userObjArr[0] as FloatArray;
            IntArray indexBuffer = userObjArr[1] as IntArray;

            int vertexCount = (vertexBuffer.Count / 8);

            if (vertexCount > 0)
            {
                int faceCount = indexBuffer.Count / 2;

                bool index32 = vertexCount > 65536;

                Mesh mesh = new Mesh(device, faceCount, vertexCount,
                    MeshFlags.SystemMemory | (index32 ? MeshFlags.Use32Bit : 0),
                    VertexFormat.Position | VertexFormat.Normal | VertexFormat.Texture1);

                SlimDX.DataStream indices = mesh.LockIndexBuffer(LockFlags.Discard);
                if (index32)
                {
                    foreach (int i in indexBuffer)
                        indices.Write(i);
                }
                else
                {
                    foreach (int i in indexBuffer)
                        indices.Write((ushort)i);
                }
                mesh.UnlockIndexBuffer();

                SlimDX.DataStream verts = mesh.LockVertexBuffer(LockFlags.Discard);
                foreach (float f in vertexBuffer)
                    verts.Write(f);
                mesh.UnlockVertexBuffer();

                mesh.ComputeNormals();
                mesh.DrawSubset(0);
                mesh.Dispose();
            }
        }
         * */

        public static Buffer CreateScreenQuad(Device device)
        {
            Buffer vertexBuffer;

            BufferDescription vertexBufferDesc = new BufferDescription()
            {
                SizeInBytes = sizeof(float) * 5 * 4,
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.VertexBuffer,
            };

            using (var data = new DataStream(vertexBufferDesc.SizeInBytes, false, true))
            {
                data.Write(new Vector3(0.5f, 0.5f, 0));
                data.Write(new Vector2(1, 0));
                data.Write(new Vector3(0.5f, -0.5f, 0));
                data.Write(new Vector2(1, 1));
                data.Write(new Vector3(-0.5f, 0.5f, 0));
                data.Write(new Vector2(0, 0));
                data.Write(new Vector3(-0.5f, -0.5f, 0));
                data.Write(new Vector2(0, 1));
                vertexBuffer = new Buffer(device, data, vertexBufferDesc);
                vertexBuffer.Unmap();
            }

            return vertexBuffer;
        }
    }
}
