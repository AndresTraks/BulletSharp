﻿using System;
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

        public List<InstanceData> InstanceDataList = new List<InstanceData>();
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
        Demo demo;

        Dictionary<CollisionShape, ShapeData> shapes = new Dictionary<CollisionShape, ShapeData>();
        List<CollisionShape> removeList = new List<CollisionShape>();

        Color groundColor = Color.Green;
        Color activeColor = Color.Orange;
        Color passiveColor = Color.Red;
        Color softBodyColor = Color.LightBlue;
        Color linkColor = Color.Black;

        int modelViewMatrixLocation;
        int vertexPositionLocation;
        int vertexNormalLocation;
        int vertexColorLocation;

        public MeshFactory(Demo demo)
        {
            this.demo = demo;
        }

        public void SetShaderLocations(int modelViewMatrix, int position, int normal, int color)
        {
            modelViewMatrixLocation = modelViewMatrix;
            vertexPositionLocation = position;
            vertexNormalLocation = normal;
            vertexColorLocation = color;
        }

        ShapeData CreateShape(CollisionShape shape)
        {
            ShapeData shapeData = new ShapeData();
            uint[] indices;
            BulletSharp.Vector3[] vertexBuffer = CreateShape(shape, out indices);
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

        public ShapeData CreateSoftBody()
        {
            // Soft body geometry is recreated each frame. Nothing to do here.
            return new ShapeData();
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
                //instanceDataDesc.SizeInBytes = Marshal.SizeOf(typeof(InstanceData));
                //shapeData.InstanceDataBuffer = new Buffer(device, instanceDataDesc);
                //shapeData.BufferBindings[1] = new VertexBufferBinding(shapeData.InstanceDataBuffer, instanceDataDesc.SizeInBytes, 0);

                shapes.Add(shape, shapeData);
            }

            return shapeData;
        }

        void InitInstanceData(CollisionObject colObj, CollisionShape shape, ref BulletSharp.Matrix transform)
        {
            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.CompoundShape:
                    foreach (CompoundShapeChild child in (shape as CompoundShape).ChildList)
                    {
                        BulletSharp.Matrix childTransform = child.Transform * transform;
                        InitInstanceData(colObj, child.ChildShape, ref childTransform);
                    }
                    break;
                case BroadphaseNativeType.SoftBodyShape:
                    ShapeData shapeData = InitShapeData(shape);
                    UpdateSoftBody(colObj as SoftBody, shapeData);

                    shapeData.InstanceDataList.Add(new InstanceData()
                    {
                        WorldTransform = MathHelper.Convert(ref transform),
                        Color = softBodyColor
                    });
                    break;
                default:
                    InitShapeData(shape).InstanceDataList.Add(new InstanceData()
                    {
                        WorldTransform = MathHelper.Convert(ref transform),
                        Color = "Ground".Equals(colObj.UserObject) ? groundColor :
                            colObj.ActivationState == ActivationState.ActiveTag ? activeColor : passiveColor
                    });
                    break;
            }
        }

        public void InitInstancedRender(AlignedCollisionObjectArray objects)
        {
            // Clear instance data
            foreach (ShapeData s in shapes.Values)
                s.InstanceDataList.Clear();

            int i = objects.Count - 1;
            for (; i >= 0; i--)
            {
                CollisionObject colObj = objects[i];

                BulletSharp.Matrix transform;
                if (colObj is SoftBody)
                {
                    if (demo.IsDebugDrawEnabled)
                        continue;
                    transform = BulletSharp.Matrix.Identity;
                }
                else
                {
                    colObj.GetWorldTransform(out transform);
                }
                InitInstanceData(colObj, colObj.CollisionShape, ref transform);
            }

            foreach (KeyValuePair<CollisionShape, ShapeData> sh in shapes)
            {
                ShapeData s = sh.Value;

                if (s.InstanceDataList.Count == 0)
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

            if (removeList.Count != 0)
            {
                for (i = removeList.Count - 1; i >= 0; i--)
                {
                    shapes.Remove(removeList[i]);
                }
                removeList.Clear();
            }
        }

        public void RenderInstanced(ref Matrix4 lookat)
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

                Matrix4 modelLookAt;

                // Index (element) buffer
                if (s.ElementCount != 0)
                {
                    GL.BindBuffer(BufferTarget.ElementArrayBuffer, s.ElementBufferID);

                    foreach (InstanceData instance in s.InstanceDataList)
                    {
                        modelLookAt = instance.WorldTransform * lookat;
                        GL.UniformMatrix4(modelViewMatrixLocation, false, ref modelLookAt);
                        GL.Uniform4(vertexColorLocation, instance.Color);
                        GL.DrawElements(s.PrimitiveType, s.ElementCount, s.ElementsType, IntPtr.Zero);
                    }

                    GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
                }
                else
                {
                    foreach (InstanceData instance in s.InstanceDataList)
                    {
                        modelLookAt = instance.WorldTransform * lookat;
                        GL.UniformMatrix4(modelViewMatrixLocation, false, ref modelLookAt);
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
