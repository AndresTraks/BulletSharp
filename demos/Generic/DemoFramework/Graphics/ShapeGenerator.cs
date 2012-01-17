using System;
using BulletSharp;
using BulletSharp.SoftBody;

namespace DemoFramework
{
    // Creates platform-agnostic vertex buffers of physical shapes
    // (boxes, cones, cylinders, spheres) for drawing. Includes normals.
    public static class ShapeGenerator
    {
        public static Vector3[] CreateShape(CollisionShape shape, out ushort[] indices)
        {
            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.BoxShape:
                    indices = null;
                    return CreateBox(shape as BoxShape);
                case BroadphaseNativeType.CapsuleShape:
                    return CreateCapsule(shape as CapsuleShape, out indices);
                case BroadphaseNativeType.ConvexHullShape:
                    indices = null;
                    return CreateConvexHull(shape as ConvexHullShape);
                case BroadphaseNativeType.CylinderShape:
                    return CreateCylinder(shape as CylinderShape, out indices);
                case BroadphaseNativeType.SphereShape:
                    return CreateSphere(shape as SphereShape, out indices);
                default:
                    throw new NotImplementedException();
            }
        }

        public static Vector3[] CreateBox(BoxShape shape)
        {
            Vector3 size = shape.HalfExtentsWithMargin;
            float x = size.X;
            float y = size.Y;
            float z = size.Z;

            Vector3[] vertices = new Vector3[36 * 2];
            Vector3 normal;
            int v = 0;

            // Draw two sides (x and -x)
            for (int i = 1; i != -3; i -= 2)
            {
                normal = new Vector3(i, 0, 0);
                vertices[v++] = new Vector3(i * x, y, -z); // Position
                vertices[v++] = normal;
                vertices[v++] = new Vector3(i * x, -y, -z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(i * x, -y, z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(i * x, y, -z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(i * x, y, z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(i * x, -y, z);
                vertices[v++] = normal;
            }

            for (int i = 1; i != -3; i -= 2)
            {
                normal = new Vector3(0, 0, i);
                vertices[v++] = new Vector3(-x, y, i * z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(-x, -y, i * z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(x, -y, i * z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(-x, y, i * z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(x, y, i * z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(x, -y, i * z);
                vertices[v++] = normal;
            }

            for (int i = 1; i != -3; i -= 2)
            {
                normal = new Vector3(0, i, 0);
                vertices[v++] = new Vector3(-x, i * y, -z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(x, i * y, -z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(-x, i * y, z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(x, i * y, z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(-x, i * y, z);
                vertices[v++] = normal;
                vertices[v++] = new Vector3(x, i * y, -z);
                vertices[v++] = normal;
            }

            return vertices;
        }

        public static Vector3[] CreateCapsule(CapsuleShape shape, out ushort[] indices)
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

            int vertexCount = 2 + slices * (stacks - 1);
            int indexCount = 6 * slices * (stacks - 1);

            Vector3[] vertices = new Vector3[vertexCount * 2];
            indices = new ushort[indexCount];

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

            return vertices;
        }

        public static Vector3 GetVectorByAxis(Vector3 vector, int axis)
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

        public static Vector3[] CreateCone(ConeShape shape, out ushort[] indices)
        {
            int up = shape.ConeUpIndex;
            float radius = shape.Radius;
            float halfHeight = shape.Height / 2 + shape.Margin;

            int numSteps = 10;
            float angleStep = (2 * (float)Math.PI) / numSteps;

            int vertexCount = 2 + 6 * numSteps;
            int indexCount = (4 * numSteps + 2) * 3;

            Vector3[] vertices = new Vector3[vertexCount * 2];
            indices = new ushort[indexCount];

            int i = 0, v = 0;
            ushort index = 0;
            ushort baseIndex;
            Vector3 normal;

            // Draw the base
            normal = GetVectorByAxis(-Vector3.UnitY, up);

            baseIndex = index;
            vertices[v++] = GetVectorByAxis(new Vector3(0, -halfHeight, 0), up);
            vertices[v++] = normal;

            vertices[v++] = GetVectorByAxis(new Vector3(0, -halfHeight, radius), up);
            vertices[v++] = normal;
            index += 2;

            for (int j = 1; j < numSteps; j++)
            {
                float x = radius * (float)Math.Sin(j * angleStep);
                float z = radius * (float)Math.Cos(j * angleStep);

                vertices[v++] = GetVectorByAxis(new Vector3(x, -halfHeight, z), up);
                vertices[v++] = normal;

                indices[i++] = baseIndex;
                indices[i++] = (ushort)(index - 1);
                indices[i++] = index++;
            }
            indices[i++] = baseIndex;
            indices[i++] = (ushort)(index - 1);
            indices[i++] = (ushort)(baseIndex + 1);


            normal = GetVectorByAxis(new Vector3(0, 0, radius), up);
            normal.Normalize();

            baseIndex = index;
            vertices[v++] = GetVectorByAxis(new Vector3(0, halfHeight, 0), up);
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

                vertices[v++] = GetVectorByAxis(new Vector3(0, halfHeight, 0), up);
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

            return vertices;
        }

        public static Vector3[] CreateCylinder(CylinderShape shape, out ushort[] indices)
        {
            int up = shape.UpAxis;
            float radius = shape.Radius;
            float halfHeight = shape.HalfExtentsWithoutMargin[up] + shape.Margin;

            int numSteps = 10;
            float angleStep = (2 * (float)Math.PI) / numSteps;

            int vertexCount = 2 + 6 * numSteps;
            int indexCount = (4 * numSteps + 2) * 3;

            Vector3[] vertices = new Vector3[vertexCount * 2];
            indices = new ushort[indexCount];

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

            return vertices;
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
        public static Vector3[] CreateConvexHull(ConvexHullShape shape)
        {
            ConvexPolyhedron poly = shape.ConvexPolyhedron;
            if (poly != null)
            {
                throw new NotImplementedException();
            }

            ShapeHull hull = new ShapeHull(shape);
            hull.BuildHull(shape.Margin);

            int vertexCount = hull.NumIndices;
            UIntArray indices = hull.Indices;
            Vector3Array points = hull.Vertices;

            Vector3[] vertices = new Vector3[vertexCount * 2];

            int v = 0, i;
            for (i = 0; i < vertexCount; i += 3)
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

            return vertices;
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
        public static Vector3[] CreateSphere(SphereShape shape, out ushort[] indices)
        {
            float radius = shape.Radius;

            int slices = (int)(radius * 10.0f);
            int stacks = (int)(radius * 10.0f);
            slices = (slices > 16) ? 16 : (slices < 3) ? 3 : slices;
            stacks = (stacks > 16) ? 16 : (stacks < 2) ? 2 : stacks;

            float hAngleStep = (float)Math.PI * 2 / slices;
            float vAngleStep = (float)Math.PI / stacks;

            int vertexCount = 2 + slices * (stacks - 1);
            int indexCount = 6 * slices * (stacks - 1);

            Vector3[] vertices = new Vector3[vertexCount * 2];
            indices = new ushort[indexCount];

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

            return vertices;
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
        /*
        vertexCount CreateTriangleMeshShape(TriangleMeshShape shape)
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
        */
        /*
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
        */
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
        */
    }
}
