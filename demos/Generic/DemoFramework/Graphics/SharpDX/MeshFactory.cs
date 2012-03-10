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

        ShapeData CreateShape(CollisionShape shape)
        {
            ShapeData shapeData = new ShapeData();
            uint[] indices;
            Vector3[] vertices = ShapeGenerator.CreateShape(shape, out indices);
            shapeData.VertexCount = vertices.Length / 2;
            shapeData.SetVertexBuffer(device, vertices);

            if (indices != null)
            {
                shapeData.IndexCount = indices.Length;
                ushort[] indices_s = ShapeGenerator.CompactIndexBuffer(indices);
                if (indices_s != null)
                {
                    shapeData.SetIndexBuffer(device, indices_s);
                }
                else
                {
                    shapeData.SetIndexBuffer(device, indices);
                }
            }

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
                    case BroadphaseNativeType.Convex2DShape:
                        return InitShapeData((shape as Convex2DShape).ChildShape);
                    default:
                        shapeData = CreateShape(shape);
                        break;
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
