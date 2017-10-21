using BulletSharp;
using BulletSharp.SoftBody;
using SharpDX;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DXGI;
using System;
using System.Collections.Generic;
using Buffer = SharpDX.Direct3D11.Buffer;
using Color = System.Drawing.Color;
using DataStream = SharpDX.DataStream;
using Device = SharpDX.Direct3D11.Device;
using Matrix = BulletSharp.Matrix;
using Vector3 = BulletSharp.Vector3;

namespace DemoFramework.SharpDX11
{
    // Contains the geometry buffers and information of all instances of a particular shape.
    public class ShapeData : IDisposable
    {
        public Buffer VertexBuffer;
        public int VertexCount;

        public Buffer IndexBuffer;
        public int IndexCount;
        public Format IndexFormat;

        public Buffer InstanceDataBuffer;
        public int InstanceDataBufferCount;
        public InstanceDataList Instances = new InstanceDataList();

        public PrimitiveTopology PrimitiveTopology = PrimitiveTopology.TriangleList;
        public VertexBufferBinding[] BufferBindings = new VertexBufferBinding[2];

        public Vector3[] SoftBodyData;

        public void SetVertexBuffer(Device device, Vector3[] vectors)
        {
            var vertexBufferDesc = new BufferDescription
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

                var vertexBufferDesc = new BufferDescription
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

            var indexBufferDesc = new BufferDescription
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

        public MeshFactory(SharpDX11Graphics graphics)
        {
            this.device = graphics.Device;
            this.inputAssembler = device.ImmediateContext.InputAssembler;
            this.demo = graphics.Demo;

            instanceDataDesc = new BufferDescription()
            {
                Usage = ResourceUsage.Dynamic,
                BindFlags = BindFlags.VertexBuffer,
                CpuAccessFlags = CpuAccessFlags.Write,
                OptionFlags = ResourceOptionFlags.None,
            };

            var elements = new InputElement[]
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
            uint[] indices;
            Vector3[] vertices = CreateShape(shape, out indices);

            var shapeData = new ShapeData();
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
                shapeData.InstanceDataBufferCount = 1;
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
                uint color = "Ground".Equals(colObj.UserObject) ? groundColor :
                        colObj.ActivationState == ActivationState.ActiveTag ? activeColor : passiveColor;
                shapeData.Instances.Add(ref transform, color);
            }
        }

        void InitSoftBodyInstance(SoftBody softBody, CollisionShape shape)
        {
            var shapeData = InitShapeData(shape);
            shapeData.Instances.Add(softBodyColor);

            UpdateSoftBody(softBody, shapeData);
        }

        public void InitInstancedRender()
        {
            // Clear instance data
            foreach (ShapeData shapeData in shapes.Values)
            {
                shapeData.Instances.Clear();
            }

            // Gather instance data
            foreach (var colObj in demo.World.CollisionObjectArray)
            {
                var shape = colObj.CollisionShape;

                if (shape.ShapeType == BroadphaseNativeType.SoftBodyShape)
                {
                    if (!demo.IsDebugDrawEnabled)
                    {
                        InitSoftBodyInstance(colObj as SoftBody, shape);
                    }
                }
                else
                {
                    Matrix transform;
                    colObj.GetWorldTransform(out transform);
                    InitRigidBodyInstance(colObj, shape, ref transform);
                }
            }

            foreach (KeyValuePair<CollisionShape, ShapeData> shape in shapes)
            {
                ShapeData shapeData = shape.Value;
                int instanceCount = shapeData.Instances.Count;

                // Is the instance buffer the right size?
                if (shapeData.InstanceDataBufferCount != instanceCount)
                {
                    // No, recreate it
                    shapeData.InstanceDataBuffer.Dispose();

                    // Remember shapes that have no instances,
                    // shape is removed after iteration over shapes
                    if (instanceCount == 0)
                    {
                        if (shapeData.IndexBuffer != null)
                            shapeData.IndexBuffer.Dispose();
                        shapeData.VertexBuffer.Dispose();
                        removeList.Add(shape.Key);
                        continue;
                    }

                    instanceDataDesc.SizeInBytes = instanceCount * InstanceData.SizeInBytes;
                    shapeData.InstanceDataBufferCount = instanceCount;
                    shapeData.InstanceDataBuffer = new Buffer(device, instanceDataDesc);
                    shapeData.BufferBindings[1] = new VertexBufferBinding(shapeData.InstanceDataBuffer, InstanceData.SizeInBytes, 0);
                }

                DataBox db = device.ImmediateContext.MapSubresource(shapeData.InstanceDataBuffer, 0, MapMode.WriteDiscard, SharpDX.Direct3D11.MapFlags.None);
                Utilities.Write(db.DataPointer, shapeData.Instances.Array, 0, instanceCount);
                device.ImmediateContext.UnmapSubresource(shapeData.InstanceDataBuffer, 0);
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

            foreach (ShapeData shapeData in shapes.Values)
            {
                inputAssembler.SetVertexBuffers(0, shapeData.BufferBindings);
                inputAssembler.PrimitiveTopology = shapeData.PrimitiveTopology;
                if (shapeData.IndexBuffer != null)
                {
                    inputAssembler.SetIndexBuffer(shapeData.IndexBuffer, shapeData.IndexFormat, 0);
                    device.ImmediateContext.DrawIndexedInstanced(shapeData.IndexCount, shapeData.Instances.Count, 0, 0, 0);
                }
                else
                {
                    device.ImmediateContext.DrawInstanced(shapeData.VertexCount, shapeData.Instances.Count, 0, 0);
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
    }
}
