using BulletSharp;
using BulletSharp.SoftBody;
using SharpDX;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DXGI;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Buffer = SharpDX.Direct3D11.Buffer;
using Color = System.Drawing.Color;
using DataStream = SharpDX.DataStream;
using Device = SharpDX.Direct3D11.Device;

namespace DemoFramework
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
        public List<InstanceData> Instances;
        public InstanceData[] InstanceArray;

        public PrimitiveTopology PrimitiveTopology;
        public VertexBufferBinding[] BufferBindings;

        public Vector3[] SoftBodyData;

        public ShapeData()
        {
            Instances = new List<InstanceData>();
            InstanceArray = new InstanceData[0];
            PrimitiveTopology = PrimitiveTopology.TriangleList;
            BufferBindings = new VertexBufferBinding[2];
        }

        public void SetVertexBuffer(Device device, Vector3[] vectors)
        {
            BufferDescription vertexBufferDesc = new BufferDescription()
            {
                SizeInBytes = Vector3.SizeInBytes * vectors.Length,
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.VertexBuffer
            };

            using (var data = new DataStream(vertexBufferDesc.SizeInBytes, false, true))
            {
                data.WriteRange(vectors);
                data.Position = 0;
                VertexBuffer = new Buffer(device, data, vertexBufferDesc);
            }

            BufferBindings[0] = new VertexBufferBinding(VertexBuffer, 24, 0);
        }

        // Used with soft bodies
        public void SetDynamicVertexBuffer(Device device, Vector3[] vectors)
        {
            if (VertexBuffer != null && VertexCount * 2 == vectors.Length)
            {
                DataBox db = device.ImmediateContext.MapSubresource(VertexBuffer, 0, MapMode.WriteDiscard, SharpDX.Direct3D11.MapFlags.None);
                SharpDX.Utilities.Write(db.DataPointer, vectors, 0, vectors.Length);
                device.ImmediateContext.UnmapSubresource(VertexBuffer, 0);
            }
            else
            {
                // Create new buffer
                if (VertexBuffer != null)
                    VertexBuffer.Dispose();

                BufferDescription vertexBufferDesc = new BufferDescription()
                {
                    SizeInBytes = Vector3.SizeInBytes * vectors.Length,
                    Usage = ResourceUsage.Dynamic,
                    BindFlags = BindFlags.VertexBuffer,
                    CpuAccessFlags = CpuAccessFlags.Write
                };

                using (var data = new DataStream(vertexBufferDesc.SizeInBytes, false, true))
                {
                    data.WriteRange(vectors);
                    data.Position = 0;
                    VertexBuffer = new Buffer(device, data, vertexBufferDesc);
                }

                VertexCount = vectors.Length / 2;
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
                data.Position = 0;
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
                data.Position = 0;
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

        BufferDescription instanceDataDesc;
        InputLayout inputLayout;
        static uint groundColor = ColorToUint(Color.Green);
        static uint activeColor = ColorToUint(Color.Orange);
        static uint passiveColor = ColorToUint(Color.OrangeRed);
        static uint softBodyColor = ColorToUint(Color.LightBlue);
        static int linkColor = Color.Black.ToArgb();

        static uint ColorToUint(Color c)
        {
            return (uint)c.R + ((uint)c.G << 8) + ((uint)c.B << 16) + ((uint)c.A << 24);
        }

        public MeshFactory(Demo demo)
        {
            this.demo = demo;
            this.device = demo.Device;
            this.inputAssembler = device.ImmediateContext.InputAssembler;

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
            inputLayout = new InputLayout(device, demo.GetEffectPass().Description.Signature, elements);
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
        }

        public static Vector3 GetVectorByAxis(float x, float y, float z, int axis)
        {
            switch (axis)
            {
                case 0:
                    return new Vector3(y, z, x);
                case 1:
                    return new Vector3(x, y, z);
                default:
                    return new Vector3(z, x, y);
            }
        }

        ShapeData CreateBoxShape(BoxShape shape)
        {
            Vector3 size = shape.HalfExtentsWithMargin;
            float x = size.X;
            float y = size.Y;
            float z = size.Z;

            ShapeData shapeData = new ShapeData();
            shapeData.VertexCount = 36;

            Vector3[] vertices = new Vector3[shapeData.VertexCount * 2];
            Vector3 normal;
            int v = 0;

            for (int j = 0; j < 3; j++)
            {
                for (int i = 1; i != -3; i -= 2)
                {
                    normal = GetVectorByAxis(0, i, 0, j);
                    vertices[v++] = GetVectorByAxis(i, i, i, j) * size;
                    vertices[v++] = normal;
                    vertices[v++] = GetVectorByAxis(1, i, -1, j) * size;
                    vertices[v++] = normal;
                    vertices[v++] = GetVectorByAxis(-1, i, 1, j) * size;
                    vertices[v++] = normal;
                    vertices[v++] = GetVectorByAxis(-i, i, -i, j) * size;
                    vertices[v++] = normal;
                    vertices[v++] = GetVectorByAxis(-1, i, 1, j) * size;
                    vertices[v++] = normal;
                    vertices[v++] = GetVectorByAxis(1, i, -1, j) * size;
                    vertices[v++] = normal;
                }
            }

            shapeData.SetVertexBuffer(device, vertices);

            return shapeData;
        }

        public ShapeData CreateCapsule(CapsuleShape shape)
        {
            int up = shape.UpAxis;
            float radius = shape.Radius;
            float cylinderHalfHeight = shape.HalfHeight;

            int slices = (int)(radius * 10.0f);
            int stacks = (int)(radius * 10.0f);
            slices = (slices > 16) ? 16 : (slices < 3) ? 3 : slices;
            stacks = (stacks > 16) ? 16 : (stacks < 3) ? 3 : stacks;

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
            vertices[v++] = GetVectorByAxis(0, -cylinderHalfHeight - radius, 0, up);
            vertices[v++] = GetVectorByAxis(-Vector3.UnitY, up);
            vertices[v++] = GetVectorByAxis(0, cylinderHalfHeight + radius, 0, up);
            vertices[v++] = GetVectorByAxis(Vector3.UnitY, up);

            // Stacks
            int j, k;
            float angle = 0;
            float vAngle = -(float)Math.PI / 2;
            Vector3 vTemp;
            Vector3 cylinderOffset = GetVectorByAxis(0, -cylinderHalfHeight, 0, up);
            for (j = 0; j < stacks - 1; j++)
            {
                float prevAngle = vAngle;
                vAngle += vAngleStep;

                if (vAngle > 0 && prevAngle < 0)
                {
                    cylinderOffset = GetVectorByAxis(0, cylinderHalfHeight, 0, up);
                }

                for (k = 0; k < slices; k++)
                {
                    angle += hAngleStep;

                    vTemp = GetVectorByAxis((float)Math.Cos(vAngle) * (float)Math.Sin(angle),
                        (float)Math.Sin(vAngle),
                        (float)Math.Cos(vAngle) * (float)Math.Cos(angle), up);
                    vertices[v++] = vTemp * radius + cylinderOffset;
                    vertices[v++] = Vector3.Normalize(vTemp);
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
                    if (side == 1)
                    {
                        indices[i++] = (ushort)(index - 1);
                        indices[i++] = index++;
                    }
                    else
                    {
                        indices[i++] = index;
                        indices[i++] = (ushort)(index - 1);
                        index++;
                    }
                }
                indices[i++] = baseIndex;
                if (side == 1)
                {
                    indices[i++] = (ushort)(index - 1);
                    indices[i++] = (ushort)(baseIndex + 1);
                }
                else
                {
                    indices[i++] = (ushort)(baseIndex + 1);
                    indices[i++] = (ushort)(index - 1);
                }
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
            indices[i] = (ushort)(baseIndex + 1);

            shapeData.SetVertexBuffer(device, vertices);
            shapeData.SetIndexBuffer(device, indices);

            return shapeData;
        }

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

        ShapeData CreateTriangleMeshShape(StridingMeshInterface meshInterface)
        {
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
                    indices[i++] = (ushort)indexStream.Read<int>();
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
                        shapeData = new ShapeData();
                        break;
                    case BroadphaseNativeType.BoxShape:
                        shapeData = CreateBoxShape(shape as BoxShape);
                        break;
                    case BroadphaseNativeType.CapsuleShape:
                        shapeData = CreateCapsule(shape as CapsuleShape);
                        break;
                    case BroadphaseNativeType.CylinderShape:
                        shapeData = CreateCylinderShape(shape as CylinderShape);
                        break;
                    case BroadphaseNativeType.ConvexHullShape:
                        shapeData = CreateConvexHullShape(shape as ConvexHullShape);
                        break;
                    case BroadphaseNativeType.GImpactShape:
                        shapeData = CreateTriangleMeshShape((shape as GImpactMeshShape).MeshInterface);
                        break;
                    case BroadphaseNativeType.SphereShape:
                        shapeData = CreateSphereShape(shape as SphereShape);
                        break;
                    case BroadphaseNativeType.TriangleMeshShape:
                        shapeData = CreateTriangleMeshShape((shape as TriangleMeshShape).MeshInterface);
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

        void InitRigidBodyInstance(CollisionObject colObj, CollisionShape shape, ref Matrix transform)
        {
            if (shape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                foreach (var child in (shape as CompoundShape).ChildList)
                {
                    Matrix childTransform = child.Transform * transform;
                    InitRigidBodyInstance(colObj, child.ChildShape, ref childTransform);
                }
            }
            else
            {
                var shapeData = InitShapeData(shape);
                shapeData.Instances.Add(new InstanceData()
                {
                    WorldTransform = transform,
                    Color = "Ground".Equals(colObj.UserObject) ? groundColor :
                        colObj.ActivationState == ActivationState.ActiveTag ? activeColor : passiveColor
                });
            }
        }

        void InitSoftBodyInstance(SoftBody softBody, CollisionShape shape)
        {
            var shapeData = InitShapeData(shape);
            shapeData.Instances.Add(new InstanceData()
            {
                WorldTransform = Matrix.Identity,
                Color = softBodyColor
            });

            UpdateSoftBody(softBody, shapeData);
        }

        public void InitInstancedRender()
        {
            // Clear instance data
            foreach (ShapeData s in shapes.Values)
                s.Instances.Clear();

            // Gather instance data
            AlignedCollisionObjectArray objects = demo.PhysicsContext.World.CollisionObjectArray;
            int i = objects.Count - 1;
            for (; i >= 0; i--)
            {
                var colObj = objects[i];
                var shape = colObj.CollisionShape;

                if (shape.ShapeType == BroadphaseNativeType.SoftBodyShape)
                {
                    //if (demo.IsDebugDrawEnabled)
                    //    continue;
                    InitSoftBodyInstance(colObj as SoftBody, shape);
                }
                else
                {
                    Matrix transform;
                    colObj.GetWorldTransform(out transform);
                    InitRigidBodyInstance(colObj, shape, ref transform);
                }
            }

            foreach (KeyValuePair<CollisionShape, ShapeData> sh in shapes)
            {
                ShapeData s = sh.Value;
                int instanceCount = s.Instances.Count;
                var instanceArray = s.InstanceArray;

                // Is the instance buffer the right size?
                if (instanceArray.Length != instanceCount)
                {
                    // No, recreate it
                    s.InstanceDataBuffer.Dispose();

                    // Remember shapes that have no instances,
                    // shape is removed after iteration over shapes
                    if (instanceCount == 0)
                    {
                        if (s.IndexBuffer != null)
                            s.IndexBuffer.Dispose();
                        s.VertexBuffer.Dispose();
                        removeList.Add(sh.Key);
                        continue;
                    }

                    instanceDataDesc.SizeInBytes = instanceCount * InstanceData.SizeInBytes;
                    s.InstanceDataBuffer = new Buffer(device, instanceDataDesc);
                    s.BufferBindings[1] = new VertexBufferBinding(s.InstanceDataBuffer, InstanceData.SizeInBytes, 0);

                    instanceArray = new InstanceData[instanceCount];
                    s.InstanceArray = instanceArray;
                }

                // Copy the instance list over to the instance array
                s.Instances.CopyTo(instanceArray);

                DataBox db = device.ImmediateContext.MapSubresource(s.InstanceDataBuffer, 0, MapMode.WriteDiscard, SharpDX.Direct3D11.MapFlags.None);
                SharpDX.Utilities.Write(db.DataPointer, instanceArray, 0, instanceArray.Length);
                device.ImmediateContext.UnmapSubresource(s.InstanceDataBuffer, 0);
            }

            // Remove shapes that had no instances
            if (removeList.Count != 0)
            {
                foreach (var shape in removeList)
                {
                    shapes.Remove(shape);
                }
                removeList.Clear();
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
                    device.ImmediateContext.DrawIndexedInstanced(s.IndexCount, s.Instances.Count, 0, 0, 0);
                }
                else
                {
                    device.ImmediateContext.DrawInstanced(s.VertexCount, s.Instances.Count, 0, 0);
                }
            }
        }

        public void UpdateSoftBody(SoftBody softBody, ShapeData shapeData)
        {
            // Could just allocate a Vector3 array here at each frame, but reusing shapeData.SoftBodyData is faster.
            // Probably uses more memory though.
            softBody.GetVertexNormalData(out shapeData.SoftBodyData);
            shapeData.SetDynamicVertexBuffer(device, shapeData.SoftBodyData);

            if (softBody.Faces.Count == 0 && softBody.Tetras.Count == 0)
            {
                shapeData.PrimitiveTopology = PrimitiveTopology.LineList;
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
    }
}
