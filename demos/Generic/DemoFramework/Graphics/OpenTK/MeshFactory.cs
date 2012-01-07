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
        public BeginMode BeginMode = BeginMode.Triangles;

        public List<InstanceData> InstanceDataList = new List<InstanceData>();

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

            // Bind current context to Array Buffer ID
            GL.BindBuffer(BufferTarget.ArrayBuffer, bufferId);

            // Send data to buffer
            GL.BufferData(BufferTarget.ArrayBuffer, (IntPtr)(vertices.Length * Vector3.SizeInBytes), vertices, usage);

            // Validate that the buffer is the correct size
            GL.GetBufferParameter(BufferTarget.ArrayBuffer, BufferParameterName.BufferSize, out bufferSize);
            if (vertices.Length * Vector3.SizeInBytes != bufferSize)
                throw new ApplicationException("Buffer data not uploaded correctly");

            // Clear the buffer Binding
            GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
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

    class MeshFactory
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
            shapeData.ElementCount = 6 * slices * (stacks - 1);

            Vector3[] vertices = new Vector3[shapeData.VertexCount];
            Vector3[] normals = new Vector3[shapeData.VertexCount];
            byte[] indices = new byte[shapeData.ElementCount];

            int i = 0, v = 0;


            // Vertices
            // Top and bottom
            normals[v] = GetVectorByAxis(-Vector3.UnitY, up);
            vertices[v++] = GetVectorByAxis(new Vector3(0, -cylinderHalfHeight - radius, 0), up);
            normals[v] = GetVectorByAxis(Vector3.UnitY, up);
            vertices[v++] = GetVectorByAxis(new Vector3(0, cylinderHalfHeight + radius, 0), up);

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
                    normals[v] = Vector3.Normalize(vTemp);
                    vertices[v++] = vTemp * radius + cylinderOffset;
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

            shapeData.SetVertexBuffer(vertices);
            shapeData.SetNormalBuffer(normals);
            shapeData.SetIndexBuffer(indices);

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

            Vector3[] vertices = new Vector3[indexCount];
            Vector3[] normals = new Vector3[indexCount];

            int v = 0, i;
            for (i = 0; i < indexCount; i += 3)
            {
                Vector3 v0 = MathHelper.Convert(points[(int)indices[i]]);
                Vector3 v1 = MathHelper.Convert(points[(int)indices[i + 1]]);
                Vector3 v2 = MathHelper.Convert(points[(int)indices[i + 2]]);

                Vector3 v01 = v0 - v1;
                Vector3 v02 = v0 - v2;
                Vector3 normal = Vector3.Cross(v01, v02);
                normal.Normalize();

                normals[v] = normal;
                vertices[v++] = v0;
                normals[v] = normal;
                vertices[v++] = v1;
                normals[v] = normal;
                vertices[v++] = v2;
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
            shapeData.ElementCount = (4 * numSteps + 2) * 3;

            Vector3[] vertices = new Vector3[shapeData.VertexCount];
            Vector3[] normals = new Vector3[shapeData.VertexCount];
            byte[] indices = new byte[shapeData.ElementCount];

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

            shapeData.SetVertexBuffer(vertices);
            shapeData.SetNormalBuffer(normals);
            shapeData.SetIndexBuffer(indices);

            return shapeData;
        }

        public ShapeData CreateSoftBody()
        {
            // Soft body geometry is recreated each frame. Nothing to do here.
            return new ShapeData();
        }

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
            shapeData.ElementCount = 6 * slices * (stacks - 1);

            Vector3[] vertices = new Vector3[shapeData.VertexCount];
            Vector3[] normals = new Vector3[shapeData.VertexCount];
            byte[] indices = new byte[shapeData.ElementCount];

            int i = 0, v = 0;


            // Vertices
            // Top and bottom
            normals[v] = -Vector3.UnitY;
            vertices[v++] = new Vector3(0, -radius, 0);
            normals[v] = Vector3.UnitY;
            vertices[v++] = new Vector3(0, radius, 0);

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
                    normals[v] = Vector3.Normalize(vTemp);
                    vertices[v++] = vTemp * radius;
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

            shapeData.SetVertexBuffer(vertices);
            shapeData.SetNormalBuffer(normals);
            shapeData.SetIndexBuffer(indices);

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
                        Color = ground.Equals(colObj.UserObject) ? groundColor :
                            colObj.ActivationState == ActivationState.ActiveTag ? activeColor : passiveColor
                    });
                    break;
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
                    if (demo.IsDebugDrawEnabled)
                        continue;
                    transform = BulletSharp.Matrix.Identity;
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
                        GL.DrawElements(s.BeginMode, s.ElementCount, s.ElementsType, IntPtr.Zero);
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
                        GL.DrawArrays(s.BeginMode, 0, s.VertexCount);
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
            AlignedFaceArray faces = softBody.Faces;

            if (faces.Count != 0)
            {
                shapeData.VertexCount = faces.Count * 3;

                BulletSharp.Vector3[] vectors = new BulletSharp.Vector3[shapeData.VertexCount];
                BulletSharp.Vector3[] normals = new BulletSharp.Vector3[shapeData.VertexCount];
                int v = 0;

                int i;
                for (i = 0; i < faces.Count; i++)
                {
                    NodePtrArray nodes = faces[i].N;
                    Node n0 = nodes[0];
                    Node n1 = nodes[1];
                    Node n2 = nodes[2];
                    n0.GetX(out vectors[v]);
                    n0.GetNormal(out normals[v++]);
                    n1.GetX(out vectors[v]);
                    n1.GetNormal(out normals[v++]);
                    n2.GetX(out vectors[v]);
                    n2.GetNormal(out normals[v++]);
                }

                shapeData.SetDynamicVertexBuffer(vectors);
                shapeData.SetDynamicNormalBuffer(normals);
            }
            else
            {
                AlignedTetraArray tetras = softBody.Tetras;
                int tetraCount = tetras.Count;

                if (tetraCount != 0)
                {
                    shapeData.VertexCount = tetraCount * 12;

                    BulletSharp.Vector3[] vectors = new BulletSharp.Vector3[tetraCount * 12];
                    BulletSharp.Vector3[] normals = new BulletSharp.Vector3[tetraCount * 12];
                    int v = 0;

                    for (int i = 0; i < tetraCount; i++)
                    {
                        NodePtrArray nodes = tetras[i].Nodes;
                        BulletSharp.Vector3 v0 = nodes[0].X;
                        BulletSharp.Vector3 v1 = nodes[1].X;
                        BulletSharp.Vector3 v2 = nodes[2].X;
                        BulletSharp.Vector3 v3 = nodes[3].X;
                        BulletSharp.Vector3 v10 = v1 - v0;
                        BulletSharp.Vector3 v02 = v0 - v2;

                        BulletSharp.Vector3 normal = BulletSharp.Vector3.Cross(v10, v02);
                        vectors[v] = v0;
                        normals[v++] = normal;
                        vectors[v] = v1;
                        normals[v++] = normal;
                        vectors[v] = v2;
                        normals[v++] = normal;

                        normal = BulletSharp.Vector3.Cross(v10, v3 - v0);
                        vectors[v] = v0;
                        normals[v++] = normal;
                        vectors[v] = v1;
                        normals[v++] = normal;
                        vectors[v] = v3;
                        normals[v++] = normal;

                        normal = BulletSharp.Vector3.Cross(v2 - v1, v3 - v1);
                        vectors[v] = v1;
                        normals[v++] = normal;
                        vectors[v] = v2;
                        normals[v++] = normal;
                        vectors[v] = v3;
                        normals[v++] = normal;

                        normal = BulletSharp.Vector3.Cross(v02, v3 - v2);
                        vectors[v] = v2;
                        normals[v++] = normal;
                        vectors[v] = v0;
                        normals[v++] = normal;
                        vectors[v] = v3;
                        normals[v++] = normal;
                    }

                    shapeData.SetDynamicVertexBuffer(vectors);
                    shapeData.SetDynamicNormalBuffer(normals);
                }
                else if (softBody.Links.Count != 0)
                {
                    AlignedLinkArray links = softBody.Links;
                    int linkCount = links.Count;
                    shapeData.VertexCount = linkCount * 2;

                    BulletSharp.Vector3[] vectors = new BulletSharp.Vector3[shapeData.VertexCount];

                    for (int i = 0; i < linkCount; i++)
                    {
                        NodePtrArray nodes = links[i].Nodes;
                        nodes[0].GetX(out vectors[i * 2]);
                        nodes[1].GetX(out vectors[i * 2 + 1]);
                    }

                    shapeData.BeginMode = BeginMode.Lines;
                    shapeData.SetDynamicVertexBuffer(vectors);
                }
                else
                {
                    throw new NotImplementedException();
                }
            }
        }
    }
}
