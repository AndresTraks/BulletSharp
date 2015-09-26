using System.Collections.Generic;
using System.Runtime.InteropServices;
using BulletSharp;
using BulletSharp.SoftBody;
using SharpDX;
using SharpDX.Direct3D;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using Buffer = SharpDX.Direct3D10.Buffer;
using Color = System.Drawing.Color;
using DataStream = SharpDX.DataStream;
using Device = SharpDX.Direct3D10.Device;
using Matrix = BulletSharp.Matrix;
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
    public class MeshFactory : DemoFramework.MeshFactory
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
        }

        public override void RemoveShape(CollisionShape shape)
        {
            if (shapes.ContainsKey(shape))
            {
                shapes[shape].Dispose();
                shapes.Remove(shape);
            }
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

        ShapeData CreateShape(CollisionShape shape)
        {
            ShapeData shapeData = new ShapeData();
            uint[] indices;
            Vector3[] vertices = CreateShape(shape, out indices);
            shapeData.VertexCount = vertices.Length / 2;
            shapeData.SetVertexBuffer(device, vertices);

            if (indices != null)
            {
                shapeData.IndexCount = indices.Length;
                ushort[] indices_s = CompactIndexBuffer(indices);
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
                if (shape.ShapeType == BroadphaseNativeType.SoftBodyShape)
                {
                    shapeData = new ShapeData();
                }
                else
                {
                    shapeData = CreateShape(shape);
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

        public void InitInstancedRender(AlignedCollisionObjectArray objects)
        {
            // Clear instance data
            foreach (ShapeData s in shapes.Values)
                s.Instances.Clear();

            // Gather instance data
            int i = objects.Count - 1;
            for (; i >= 0; i--)
            {
                var colObj = objects[i];
                var shape = colObj.CollisionShape;

                if (shape.ShapeType == BroadphaseNativeType.SoftBodyShape)
                {
                    if (demo.IsDebugDrawEnabled)
                        continue;
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

                // Is the instance buffer the right size?
                if (s.InstanceDataBuffer.Description.SizeInBytes != instanceCount * InstanceData.SizeInBytes)
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
                }

                // Copy the instance list over to the instance array
                InstanceData[] instanceArray = s.InstanceArray;
                if (instanceArray.Length != instanceCount)
                {
                    instanceArray = new InstanceData[instanceCount];
                    s.InstanceArray = instanceArray;
                }
                s.Instances.CopyTo(instanceArray);

                using (var data = s.InstanceDataBuffer.Map(MapMode.WriteDiscard, global::SharpDX.Direct3D10.MapFlags.None))
                {
                    data.WriteRange(instanceArray);
                    s.InstanceDataBuffer.Unmap();
                }
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
                    device.DrawIndexedInstanced(s.IndexCount, s.Instances.Count, 0, 0, 0);
                }
                else
                {
                    device.DrawInstanced(s.VertexCount, s.Instances.Count, 0, 0);
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
