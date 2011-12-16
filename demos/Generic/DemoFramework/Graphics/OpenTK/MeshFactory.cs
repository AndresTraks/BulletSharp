using System;
using System.Collections.Generic;
using System.Drawing;
using BulletSharp;
using BulletSharp.SoftBody;
using OpenTK.Graphics.OpenGL;
using OpenTK;
using Vector3 = OpenTK.Vector3;

namespace DemoFramework.OpenTK
{
    public struct InstanceData
    {
        public Matrix4 worldTransform;
        public Color color;
    }

    public class ShapeData : System.IDisposable
    {
        public int VertexCount { get; set; }
        public int IndexCount { get; set; }

        public int VertexBufferID;
        public int TexCoordBufferID;
        public int NormalBufferID;

        public int ElementBufferID;
        //public int NumElements;

        public List<InstanceData> InstanceDataList { get; set; }

        public ShapeData()
        {
            InstanceDataList = new List<InstanceData>();
        }

        public void SetVertexBuffer(Vector3[] vectors)
        {
            SetBuffer(vectors, out VertexBufferID);
        }

        public void SetNormalBuffer(Vector3[] normals)
        {
            SetBuffer(normals, out NormalBufferID);
        }

        static void SetBuffer(Vector3[] vertices, out int bufferId)
        {
            int bufferSize;

            // Generate Array Buffer Id
            GL.GenBuffers(1, out bufferId);

            // Bind current context to Array Buffer ID
            GL.BindBuffer(BufferTarget.ArrayBuffer, bufferId);

            // Send data to buffer
            GL.BufferData(BufferTarget.ArrayBuffer, (IntPtr)(vertices.Length * Vector3.SizeInBytes), vertices, BufferUsageHint.StaticDraw);

            // Validate that the buffer is the correct size
            GL.GetBufferParameter(BufferTarget.ArrayBuffer, BufferParameterName.BufferSize, out bufferSize);
            if (vertices.Length * Vector3.SizeInBytes != bufferSize)
                throw new ApplicationException("Buffer data not uploaded correctly");

            // Clear the buffer Binding
            GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
        }

        public void SetIndexBuffer(int[] indices)
        {
            int bufferSize;

            // Generate Array Buffer Id
            GL.GenBuffers(1, out ElementBufferID);

            // Bind current context to Array Buffer ID
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, ElementBufferID);

            // Send data to buffer
            GL.BufferData(BufferTarget.ElementArrayBuffer, (IntPtr)(indices.Length * sizeof(int)), indices, BufferUsageHint.StaticDraw);

            // Validate that the buffer is the correct size
            GL.GetBufferParameter(BufferTarget.ElementArrayBuffer, BufferParameterName.BufferSize, out bufferSize);
            if (indices.Length * sizeof(int) != bufferSize)
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

    class MeshFactory
    {
        Dictionary<CollisionShape, ShapeData> shapes = new Dictionary<CollisionShape, ShapeData>();
        List<CollisionShape> removeList = new List<CollisionShape>();

        Color groundColor = Color.Green;
        Color activeColor = Color.Orange;
        Color passiveColor = Color.Red;
        Color softBodyColor = Color.LightBlue;
        Color linkColor = Color.Black;

        ShapeData CreateBoxShape(BoxShape shape)
        {
            BulletSharp.Vector3 size = shape.HalfExtentsWithMargin;
            float x = size.X;
            float y = size.Y;
            float z = size.Z;

            ShapeData shapeData = new ShapeData();
            shapeData.VertexCount = 36;

            Vector3[] vertices = new Vector3[shapeData.VertexCount];
            Vector3[] normals = new Vector3[shapeData.VertexCount];
            Vector3 normal;
            int v = 0;

            // Draw opposite sides
            for (int i = 1; i != -3; i -= 2)
            {
                normal = new Vector3(i, 0, 0);
                float ix = i * x;
                normals[v] = normal;
                vertices[v++] = new Vector3(ix, y, -z); // Position
                normals[v] = normal;
                vertices[v++] = new Vector3(ix, -y, -z);
                normals[v] = normal;
                vertices[v++] = new Vector3(ix, -y, z);
                normals[v] = normal;
                vertices[v++] = new Vector3(ix, y, -z);
                normals[v] = normal;
                vertices[v++] = new Vector3(ix, y, z);
                normals[v] = normal;
                vertices[v++] = new Vector3(ix, -y, z);
            }

            for (int i = 1; i != -3; i -= 2)
            {
                normal = new Vector3(0, 0, i);
                float iz = i * z;
                normals[v] = normal;
                vertices[v++] = new Vector3(-x, y, iz);
                normals[v] = normal;
                vertices[v++] = new Vector3(-x, -y, iz);
                normals[v] = normal;
                vertices[v++] = new Vector3(x, -y, iz);
                normals[v] = normal;
                vertices[v++] = new Vector3(-x, y, iz);
                normals[v] = normal;
                vertices[v++] = new Vector3(x, y, iz);
                normals[v] = normal;
                vertices[v++] = new Vector3(x, -y, iz);
            }

            for (int i = 1; i != -3; i -= 2)
            {
                normal = new Vector3(0, i, 0);
                float iy = i * y;
                normals[v] = normal;
                vertices[v++] = new Vector3(-x, iy, -z);
                normals[v] = normal;
                vertices[v++] = new Vector3(x, iy, -z);
                normals[v] = normal;
                vertices[v++] = new Vector3(-x, iy, z);
                normals[v] = normal;
                vertices[v++] = new Vector3(x, iy, z);
                normals[v] = normal;
                vertices[v++] = new Vector3(-x, iy, z);
                normals[v] = normal;
                vertices[v++] = new Vector3(x, i * y, -z);
            }

            shapeData.SetVertexBuffer(vertices);
            shapeData.SetNormalBuffer(normals);

            return shapeData;
        }

        Vector3 GetVectorByAxis(Vector3 vector, int axis)
        {
            switch (axis)
            {
                case 0:
                    return new Vector3(vector.Y, vector.Z, vector.X);
                case 1:
                    return new Vector3(vector.Z, vector.Y, vector.X);
                default:
                    return vector;
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

            Vector3[] vertices = new Vector3[shapeData.VertexCount];
            Vector3[] normals = new Vector3[shapeData.VertexCount];
            byte[] indices = new byte[shapeData.IndexCount];

            int i = 0, v = 0;
            byte index = 0;
            byte baseIndex;
            Vector3 normal;

            // Draw two sides
            for (int side = 1; side != -3; side -= 2)
            {
                normal = GetVectorByAxis(side * Vector3.UnitY, up);

                baseIndex = index;
                normals[v] = normal;
                vertices[v++] = GetVectorByAxis(new Vector3(0, side * halfHeight, 0), up);

                normals[v] = normal;
                vertices[v++] = GetVectorByAxis(new Vector3(0, side * halfHeight, radius), up);
                index += 2;

                for (int j = 1; j < numSteps; j++)
                {
                    float x = radius * (float)Math.Sin(j * angleStep);
                    float z = radius * (float)Math.Cos(j * angleStep);

                    normals[v] = normal;
                    vertices[v++] = GetVectorByAxis(new Vector3(x, side * halfHeight, z), up);

                    indices[i++] = baseIndex;
                    indices[i++] = (byte)(index - 1);
                    indices[i++] = index++;
                }
                indices[i++] = baseIndex;
                indices[i++] = (byte)(index - 1);
                indices[i++] = (byte)(baseIndex + 1);
            }


            normal = GetVectorByAxis(new Vector3(0, 0, radius), up);
            normal.Normalize();

            baseIndex = index;
            normals[v] = normal;
            vertices[v++] = GetVectorByAxis(new Vector3(0, halfHeight, radius), up);

            normals[v] = normal;
            vertices[v++] = GetVectorByAxis(new Vector3(0, -halfHeight, radius), up);
            index += 2;

            for (int j = 1; j < numSteps + 1; j++)
            {
                float x = radius * (float)Math.Sin(j * angleStep);
                float z = radius * (float)Math.Cos(j * angleStep);

                normal = GetVectorByAxis(new Vector3(x, 0, z), up);
                normal.Normalize();

                normals[v] = normal;
                vertices[v++] = GetVectorByAxis(new Vector3(x, halfHeight, z), up);

                normals[v] = normal;
                vertices[v++] = GetVectorByAxis(new Vector3(x, -halfHeight, z), up);

                indices[i++] = (byte)(index - 2);
                indices[i++] = (byte)(index - 1);
                indices[i++] = (byte)index;
                indices[i++] = (byte)index;
                indices[i++] = (byte)(index - 1);
                indices[i++] = (byte)(index + 1);
                index += 2;
            }
            indices[i++] = (byte)(index - 2);
            indices[i++] = (byte)(index - 1);
            indices[i++] = (byte)(baseIndex);
            indices[i++] = (byte)(baseIndex);
            indices[i++] = (byte)(index - 1);
            indices[i++] = (byte)(baseIndex + 1);

            int[] indices2 = new int[indices.Length];
            for (i = 0; i < indices.Length; i++)
            {
                indices2[i] = indices[i];
            }

            shapeData.SetVertexBuffer(vertices);
            shapeData.SetNormalBuffer(vertices);
            shapeData.SetIndexBuffer(indices2);

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
                        //shapeData = CreateSoftBody();
                        break;
                    case BroadphaseNativeType.BoxShape:
                        shapeData = CreateBoxShape(shape as BoxShape);
                        break;
                    case BroadphaseNativeType.CylinderShape:
                        shapeData = CreateCylinderShape(shape as CylinderShape);
                        break;
                    case BroadphaseNativeType.ConvexHullShape:
                        //shapeData = CreateConvexHullShape(shape as ConvexHullShape);
                        break;
                    case BroadphaseNativeType.SphereShape:
                        //shapeData = CreateSphereShape(shape as SphereShape);
                        break;
                    case BroadphaseNativeType.TriangleMeshShape:
                        //shapeData = CreateTriangleMeshShape(shape as TriangleMeshShape);
                        break;
                    default:
                        throw new NotImplementedException();
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
            if (shape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                foreach (CompoundShapeChild child in (shape as CompoundShape).ChildList)
                {
                    BulletSharp.Matrix childTransform = child.Transform * transform;
                    CollisionShape childShape = child.ChildShape;
                    InitInstanceData(colObj, childShape, ref childTransform);
                }
            }
            else if (shape.ShapeType == BroadphaseNativeType.SoftBodyShape)
            {
                /*
                ShapeData shapeData = InitShapeData(shape);
                UpdateSoftBody(colObj as SoftBody, shapeData);

                shapeData.InstanceDataList.Add(new InstanceData()
                {
                    WorldTransform = transform,
                    Color = softBodyColor
                });
                */
            }
            else
            {
                InitShapeData(shape).InstanceDataList.Add(new InstanceData()
                {
                    worldTransform = MathHelper.Convert(ref transform),
                    color = ground.Equals(colObj.UserObject) ? groundColor :
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

                BulletSharp.Matrix transform;
                if (colObj is SoftBody)
                {
                    transform = BulletSharp.Matrix.Identity;
                }
                else
                {
                    ((colObj as RigidBody).MotionState as DefaultMotionState).GetWorldTransform(out transform);
                }
                InitInstanceData(colObj, colObj.CollisionShape, ref transform);
            }
            /*
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
            */
            if (removeList.Count != 0)
            {
                for (i = removeList.Count - 1; i >= 0; i--)
                {
                    shapes.Remove(removeList[i]);
                }
            }
        }

        public void RenderInstanced(ref Matrix4 lookat)
        {
            foreach (ShapeData s in shapes.Values)
            {
                // Bormal buffer
                GL.BindBuffer(BufferTarget.ArrayBuffer, s.NormalBufferID);
                GL.NormalPointer(NormalPointerType.Float, Vector3.SizeInBytes, IntPtr.Zero);
                GL.EnableClientState(ArrayCap.NormalArray);

                // Vertex buffer
                GL.BindBuffer(BufferTarget.ArrayBuffer, s.VertexBufferID);
                GL.VertexPointer(3, VertexPointerType.Float, Vector3.SizeInBytes, IntPtr.Zero);
                GL.EnableClientState(ArrayCap.VertexArray);

                // index buffer
                if (s.IndexCount != 0)
                {
                    GL.BindBuffer(BufferTarget.ElementArrayBuffer, s.ElementBufferID);

                    foreach (InstanceData instance in s.InstanceDataList)
                    {
                        Matrix4 modelLookAt = instance.worldTransform * lookat;
                        GL.LoadMatrix(ref modelLookAt);
                        GL.Color3(instance.color);
                        GL.DrawElements(BeginMode.Triangles, s.IndexCount, DrawElementsType.UnsignedInt, IntPtr.Zero);
                    }
                }
                else
                {
                    foreach (InstanceData instance in s.InstanceDataList)
                    {
                        Matrix4 modelLookAt = instance.worldTransform * lookat;
                        GL.LoadMatrix(ref modelLookAt);
                        GL.Color3(instance.color);
                        GL.DrawArrays(BeginMode.Triangles, 0, s.VertexCount);
                    }
                }

                GL.DisableClientState(ArrayCap.VertexArray);
                GL.DisableClientState(ArrayCap.NormalArray);
            }
        }
    }
}
