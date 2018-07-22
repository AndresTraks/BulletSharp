using System;
using System.Collections.Generic;
using System.Drawing;
using BulletSharp;
using BulletSharp.SoftBody;
using OpenTK;
using OpenTK.Graphics.OpenGL;
//using Vector3 = OpenTK.Vector3;
using Vector3 = BulletSharp.Vector3;

namespace DemoFramework.OpenTK
{
    public struct InstanceData
    {
        public Matrix4 WorldTransform;
        public Color Color;
    }

    public class ShapeData : System.IDisposable
    {
        public int VertexCount;
        public int ElementCount;

        public int VertexBufferID;
        public int TexCoordBufferID;
        public int NormalBufferID;
        public int ElementBufferID;
        public DrawElementsType ElementsType;
        public PrimitiveType PrimitiveType = PrimitiveType.Triangles;

        public List<InstanceData> Instances = new List<InstanceData>();
        public Vector3[] SoftBodyVertices;
        public Vector3[] SoftBodyNormals;

        public void SetVertexBuffer<T>(T[] vertices) where T : struct
        {
            SetBuffer(vertices, out VertexBufferID);
        }

        public void SetNormalBuffer<T>(T[] normals) where T : struct
        {
            SetBuffer(normals, out NormalBufferID);
        }

        public void SetDynamicVertexBuffer<T>(T[] vertices) where T : struct
        {
            VertexCount = vertices.Length;
            if (VertexBufferID == 0)
            {
                SetBuffer(vertices, out VertexBufferID, BufferUsageHint.DynamicDraw);
            }
            else
            {
                UpdateBuffer(vertices, VertexBufferID);
            }
        }

        public void SetDynamicNormalBuffer<T>(T[] vertices) where T : struct
        {
            if (NormalBufferID == 0)
            {
                SetBuffer(vertices, out NormalBufferID, BufferUsageHint.DynamicDraw);
            }
            else
            {
                UpdateBuffer(vertices, NormalBufferID);
            }
        }

        static void SetBuffer<T>(T[] vertices, out int bufferId, BufferUsageHint usage = BufferUsageHint.StaticDraw) where T : struct
        {
            int bufferSize;

            // Generate Array Buffer Id
            GL.GenBuffers(1, out bufferId);
            OpenTKGraphics.CheckGLError("GenBuffers");

            // Bind current context to Array Buffer ID
            GL.BindBuffer(BufferTarget.ArrayBuffer, bufferId);
            OpenTKGraphics.CheckGLError("BindBuffer");

            // Send data to buffer
            GL.BufferData(BufferTarget.ArrayBuffer, (IntPtr)(vertices.Length * Vector3.SizeInBytes), vertices, usage);
            OpenTKGraphics.CheckGLError("BufferData");

            // Validate that the buffer is the correct size
            GL.GetBufferParameter(BufferTarget.ArrayBuffer, BufferParameterName.BufferSize, out bufferSize);
            OpenTKGraphics.CheckGLError("GetBufferParameter");
            if (vertices.Length * Vector3.SizeInBytes != bufferSize)
                throw new ApplicationException("Buffer data not uploaded correctly");

            // Clear the buffer Binding
            GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
            OpenTKGraphics.CheckGLError("BindBuffer");
        }

        static void UpdateBuffer<T>(T[] vertices, int bufferId) where T : struct
        {
            // Bind current context to Array Buffer ID
            GL.BindBuffer(BufferTarget.ArrayBuffer, bufferId);

            // Send data to buffer
            GL.BufferData(BufferTarget.ArrayBuffer, (IntPtr)(vertices.Length * Vector3.SizeInBytes), vertices, BufferUsageHint.DynamicDraw);

            // Clear the buffer Binding
            GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
        }

        public void SetIndexBuffer(uint[] indices)
        {
            int bufferSize;

            ElementsType = DrawElementsType.UnsignedInt;

            // Generate Array Buffer Id
            GL.GenBuffers(1, out ElementBufferID);

            // Bind current context to Array Buffer ID
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, ElementBufferID);

            // Send data to buffer
            GL.BufferData(BufferTarget.ElementArrayBuffer, (IntPtr)(indices.Length * sizeof(uint)), indices, BufferUsageHint.StaticDraw);

            // Validate that the buffer is the correct size
            GL.GetBufferParameter(BufferTarget.ElementArrayBuffer, BufferParameterName.BufferSize, out bufferSize);
            if (indices.Length * sizeof(uint) != bufferSize)
                throw new ApplicationException("Element array not uploaded correctly");

            // Clear the buffer Binding
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
        }

        public void SetIndexBuffer(ushort[] indices)
        {
            int bufferSize;

            ElementsType = DrawElementsType.UnsignedShort;

            // Generate Array Buffer Id
            GL.GenBuffers(1, out ElementBufferID);

            // Bind current context to Array Buffer ID
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, ElementBufferID);

            // Send data to buffer
            GL.BufferData(BufferTarget.ElementArrayBuffer, (IntPtr)(indices.Length * sizeof(ushort)), indices, BufferUsageHint.StaticDraw);

            // Validate that the buffer is the correct size
            GL.GetBufferParameter(BufferTarget.ElementArrayBuffer, BufferParameterName.BufferSize, out bufferSize);
            if (indices.Length * sizeof(ushort) != bufferSize)
                throw new ApplicationException("Element array not uploaded correctly");

            // Clear the buffer Binding
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
        }

        public void SetIndexBuffer(byte[] indices)
        {
            int bufferSize;

            ElementsType = DrawElementsType.UnsignedByte;

            // Generate Array Buffer Id
            GL.GenBuffers(1, out ElementBufferID);

            // Bind current context to Array Buffer ID
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, ElementBufferID);

            // Send data to buffer
            GL.BufferData(BufferTarget.ElementArrayBuffer, (IntPtr)indices.Length, indices, BufferUsageHint.StaticDraw);

            // Validate that the buffer is the correct size
            GL.GetBufferParameter(BufferTarget.ElementArrayBuffer, BufferParameterName.BufferSize, out bufferSize);
            if (indices.Length != bufferSize)
                throw new ApplicationException("Element array not uploaded correctly");

            // Clear the buffer Binding
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
        }

        public void Dispose()
        {
            if (VertexBufferID != 0)
            {
                GL.DeleteBuffers(1, ref VertexBufferID);
            }
            if (NormalBufferID != 0)
            {
                GL.DeleteBuffers(1, ref NormalBufferID);
            }
        }
    }

    class MeshFactory : DemoFramework.MeshFactory
    {
        Demo _demo;

        Dictionary<CollisionShape, ShapeData> shapes = new Dictionary<CollisionShape, ShapeData>();
        List<CollisionShape> removeList = new List<CollisionShape>();

        static Color groundColor = Color.Green;
        static Color activeColor = Color.Orange;
        static Color passiveColor = Color.Red;
        static Color softBodyColor = Color.LightBlue;
        static Color linkColor = Color.Black;

        int worldMatrixLocation;
        int vertexPositionLocation;
        int vertexNormalLocation;
        int vertexColorLocation;

        public MeshFactory(Demo demo)
        {
            _demo = demo;
        }

        public void SetShaderLocations(int worldMatrix, int position, int normal, int color)
        {
            worldMatrixLocation = worldMatrix;
            vertexPositionLocation = position;
            vertexNormalLocation = normal;
            vertexColorLocation = color;
        }

        ShapeData CreateShape(CollisionShape shape)
        {
            ShapeData shapeData = new ShapeData();
            uint[] indices;
            BulletSharp.Vector3[] vertexBuffer = CreateShape(shape, out indices);

            if (vertexBuffer != null)
            {
                shapeData.VertexCount = vertexBuffer.Length / 2;

                Vector3[] vertices = new Vector3[shapeData.VertexCount];
                Vector3[] normals = new Vector3[shapeData.VertexCount];

                int i;
                for (i = 0; i < shapeData.VertexCount; i++)
                {
                    vertices[i] = vertexBuffer[i * 2];
                    normals[i] = vertexBuffer[i * 2 + 1];
                }

                shapeData.SetVertexBuffer(vertices);
                shapeData.SetNormalBuffer(normals);
            }

            if (indices != null)
            {
                ushort[] indices_s = CompactIndexBuffer(indices);
                if (indices_s != null)
                {
                    shapeData.SetIndexBuffer(indices_s);
                }
                else
                {
                    shapeData.SetIndexBuffer(indices);
                }
                shapeData.ElementCount = indices.Length;
            }

            return shapeData;
        }

        public override void RemoveShape(CollisionShape shape)
        {
            if (shapes.ContainsKey(shape))
            {
                shapes[shape].Dispose();
                shapes.Remove(shape);
            }
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
                //instanceDataDesc.SizeInBytes = Marshal.SizeOf(typeof(InstanceData));
                //shapeData.InstanceDataBuffer = new Buffer(device, instanceDataDesc);
                //shapeData.BufferBindings[1] = new VertexBufferBinding(shapeData.InstanceDataBuffer, instanceDataDesc.SizeInBytes, 0);

                shapes.Add(shape, shapeData);
            }

            return shapeData;
        }

        void InitRigidBodyInstance(CollisionObject colObj, CollisionShape shape, ref BulletSharp.Matrix transform)
        {
            if (shape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                foreach (CompoundShapeChild child in (shape as CompoundShape).ChildList)
                {
                    BulletSharp.Matrix childTransform = child.Transform * transform;
                    InitRigidBodyInstance(colObj, child.ChildShape, ref childTransform);
                }
            }
            else
            {
                InitShapeData(shape).Instances.Add(new InstanceData()
                {
                    WorldTransform = MathHelper.Convert(ref transform),
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
                WorldTransform = Matrix4.Identity,
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
            foreach (var colObj in _demo.World.CollisionObjectArray)
            {
                var shape = colObj.CollisionShape;

                if (colObj is SoftBody)
                {
                    if (_demo.IsDebugDrawEnabled)
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

                if (s.Instances.Count == 0)
                {
                    removeList.Add(sh.Key);
                }

                /*
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
                */
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
            GL.EnableVertexAttribArray(vertexPositionLocation);

            foreach (ShapeData s in shapes.Values)
            {
                // Normal buffer
                if (s.NormalBufferID != 0)
                {
                    GL.EnableVertexAttribArray(vertexNormalLocation);
                    GL.BindBuffer(BufferTarget.ArrayBuffer, s.NormalBufferID);
                    GL.VertexAttribPointer(vertexNormalLocation, 3, VertexAttribPointerType.Float, false, Vector3.SizeInBytes, IntPtr.Zero);
                }

                // Vertex buffer
                GL.BindBuffer(BufferTarget.ArrayBuffer, s.VertexBufferID);
                GL.VertexAttribPointer(vertexPositionLocation, 3, VertexAttribPointerType.Float, false, Vector3.SizeInBytes, IntPtr.Zero);

                Matrix4 worldMatrix;

                // Index (element) buffer
                if (s.ElementCount != 0)
                {
                    GL.BindBuffer(BufferTarget.ElementArrayBuffer, s.ElementBufferID);

                    foreach (InstanceData instance in s.Instances)
                    {
                        worldMatrix = instance.WorldTransform;
                        GL.UniformMatrix4(worldMatrixLocation, false, ref worldMatrix);
                        GL.Uniform4(vertexColorLocation, instance.Color);
                        GL.DrawElements(s.PrimitiveType, s.ElementCount, s.ElementsType, IntPtr.Zero);
                    }

                    GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
                }
                else
                {
                    foreach (InstanceData instance in s.Instances)
                    {
                        worldMatrix = instance.WorldTransform;
                        GL.UniformMatrix4(worldMatrixLocation, false, ref worldMatrix);
                        GL.Uniform4(vertexColorLocation, instance.Color);
                        GL.DrawArrays(s.PrimitiveType, 0, s.VertexCount);
                    }
                }

                if (s.NormalBufferID != 0)
                {
                    GL.DisableVertexAttribArray(vertexNormalLocation);
                }
            }

            GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
            GL.DisableVertexAttribArray(vertexPositionLocation);
        }

        public void UpdateSoftBody(SoftBody softBody, ShapeData shapeData)
        {
            softBody.GetVertexNormalData(out shapeData.SoftBodyVertices, out shapeData.SoftBodyNormals);
            shapeData.SetDynamicVertexBuffer(shapeData.SoftBodyVertices);

            if (shapeData.SoftBodyNormals != null)
            {
                shapeData.SetDynamicNormalBuffer(shapeData.SoftBodyNormals);
            }
            else
            {
                shapeData.SetDynamicNormalBuffer(new Vector3[shapeData.VertexCount]); // hack, should use a different shader that doesn't process normals
                shapeData.PrimitiveType = PrimitiveType.Lines;
            }
        }
    }
}
