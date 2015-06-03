using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using BulletSharp;
using BulletSharp.SoftBody;
using SlimDX;
using SlimDX.Direct3D9;
using Face = BulletSharp.SoftBody.Face;

namespace DemoFramework
{
    // This class creates graphical objects (boxes, cones, cylinders, spheres) on the fly.
    public class GraphicObjectFactory : System.IDisposable
    {
        Device device;
        Dictionary<CollisionShape, Mesh> shapes = new Dictionary<CollisionShape, Mesh>();
        Dictionary<CollisionShape, Mesh> complexShapes = new Dictionary<CollisionShape, Mesh>(); // these have more than 1 subset
        Effect planeShader;

        public GraphicObjectFactory(Device device)
        {
            this.device = device;
        }

        public void OnLostDevice()
        {
            if (planeShader != null)
                planeShader.OnLostDevice();
        }

        public void OnResetDevice()
        {
            if (planeShader != null)
                planeShader.OnResetDevice();
        }

        public void Dispose()
        {
            foreach (Mesh mesh in shapes.Values)
            {
                mesh.Dispose();
            }
            shapes.Clear();

            foreach (Mesh mesh in complexShapes.Values)
            {
                mesh.Dispose();
            }
            complexShapes.Clear();

            if (planeShader != null)
                planeShader.Dispose();
        }

        Mesh CreateBoxShape(BoxShape shape)
        {
            Vector3 size = shape.HalfExtentsWithMargin;
            Mesh mesh = Mesh.CreateBox(device, size.X * 2, size.Y * 2, size.Z * 2);
            shapes.Add(shape, mesh);
            return mesh;
        }

        Mesh CreateCapsuleShape(CapsuleShape shape)
        {
            int upAxis = shape.UpAxis;
            Vector3 size = shape.ImplicitShapeDimensions;
            float halfHeight = size[upAxis];
            float radius = (upAxis == 0) ? size.Y : size.X;

            // Combine a cylinder and two spheres.
            Mesh cylinder = Mesh.CreateCylinder(device, radius, radius, halfHeight * 2, 8, 1);
            Mesh sphere = Mesh.CreateSphere(device, radius, 8, 4);
            Matrix[] transforms;
            if (upAxis == 0)
            {
                transforms = new Matrix[] {
                    Matrix.Translation(halfHeight, 0, 0),
                    Matrix.RotationY((float)Math.PI / 2),
                    Matrix.Translation(-halfHeight, 0, 0)};
            }
            else if (upAxis == 1)
            {
                transforms = new Matrix[] {
                    Matrix.Translation(0, halfHeight, 0),
                    Matrix.RotationX((float)Math.PI / 2),
                    Matrix.Translation(0, -halfHeight, 0)};
            }
            else
            {
                transforms = new Matrix[] {
                    Matrix.Translation(0, 0, halfHeight),
                    Matrix.Identity,
                    Matrix.Translation(0, 0, -halfHeight)};
            }

            Mesh[] meshes = new Mesh[] { sphere, cylinder, sphere };
            Mesh mesh = Mesh.Concatenate(device, meshes, MeshFlags.Managed, transforms, null);
            cylinder.Dispose();
            sphere.Dispose();

            complexShapes.Add(shape, mesh);
            return mesh;
        }

        Mesh CreateConeShape(ConeShape shape)
        {
            Mesh mesh = Mesh.CreateCylinder(device, 0, shape.Radius, shape.Height, 16, 1);
            shapes.Add(shape, mesh);
            return mesh;
        }

        Mesh CreateCylinderShape(CylinderShape shape)
        {
            int upAxis = shape.UpAxis;
            float radius = shape.Radius;
            float halfHeight = shape.HalfExtentsWithoutMargin[upAxis] + shape.Margin;

            Mesh mesh = Mesh.CreateCylinder(device, radius, radius, halfHeight * 2, 16, 1);
            if (upAxis == 0)
            {
                Matrix[] transform = new Matrix[] { Matrix.RotationY((float)Math.PI / 2) };
                Mesh meshRotated = Mesh.Concatenate(device, new Mesh[] { mesh }, MeshFlags.Managed, transform, null);
                mesh.Dispose();
                mesh = meshRotated;
            }
            else if (upAxis == 1)
            {
                Matrix[] transform = new Matrix[] { Matrix.RotationX((float)Math.PI / 2) };
                Mesh cylinderMeshRot = Mesh.Concatenate(device, new Mesh[] { mesh }, MeshFlags.Managed, transform, null);
                mesh.Dispose();
                mesh = cylinderMeshRot;
            }
            shapes.Add(shape, mesh);

            return mesh;
        }

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
                    indexBuffer.Write((short)indices.Read<int>());
            }
            mesh.UnlockIndexBuffer();

            mesh.ComputeNormals();
            shapes.Add(shape, mesh);

            return mesh;
        }

        Mesh CreateConvexHullShape(ConvexHullShape shape)
        {
            ShapeHull hull = new ShapeHull(shape);
            hull.BuildHull(shape.Margin);

            UIntArray hullIndices = hull.Indices;
            Vector3Array points = hull.Vertices;


            int vertexCount = hull.NumIndices;
            int faceCount = hull.NumTriangles;

            bool index32 = vertexCount > 65536;

            Mesh mesh = new Mesh(device, faceCount, vertexCount,
                MeshFlags.SystemMemory | (index32 ? MeshFlags.Use32Bit : 0), VertexFormat.Position | VertexFormat.Normal);


            SlimDX.DataStream indices = mesh.LockIndexBuffer(LockFlags.Discard);
            int i;
            if (index32)
            {
                for (i = 0; i < vertexCount; i++)
                    indices.Write(i);
            }
            else
            {
                for (i = 0; i < vertexCount; i++)
                    indices.Write((short)i);
            }
            mesh.UnlockIndexBuffer();

            SlimDX.DataStream verts = mesh.LockVertexBuffer(LockFlags.Discard);
            Vector3 scale = Vector3.Multiply(shape.LocalScaling, 1.0f + shape.Margin);
            for (i = 0; i < vertexCount; i += 3)
            {
                verts.Write(Vector3.Modulate(points[(int)hullIndices[i]], scale));
                verts.Position += 12;
                verts.Write(Vector3.Modulate(points[(int)hullIndices[i+1]], scale));
                verts.Position += 12;
                verts.Write(Vector3.Modulate(points[(int)hullIndices[i+2]], scale));
                verts.Position += 12;
            }
            mesh.UnlockVertexBuffer();

            mesh.ComputeNormals();
            shapes.Add(shape, mesh);

            return mesh;
        }

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

        Mesh CreateSphere(SphereShape shape)
        {
            Mesh mesh = Mesh.CreateSphere(device, shape.Radius, 16, 16);
            shapes.Add(shape, mesh);
            return mesh;
        }

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

        Mesh CreateTriangleMeshShape(TriangleMeshShape shape)
        {
            StridingMeshInterface meshInterface = shape.MeshInterface;

            BulletSharp.DataStream verts, indices;
            int numVerts, numFaces;
            PhyScalarType vertsType, indicesType;
            int vertexStride, indexStride;
            meshInterface.GetLockedReadOnlyVertexIndexData(out verts, out numVerts, out vertsType, out vertexStride,
                out indices, out indexStride, out numFaces, out indicesType);

            bool index32 = numVerts > 65536;

            Mesh mesh = new Mesh(device, numFaces, numVerts,
                 MeshFlags.SystemMemory | (index32 ? MeshFlags.Use32Bit : 0), VertexFormat.Position | VertexFormat.Normal);

            SlimDX.DataStream data = mesh.LockVertexBuffer(LockFlags.None);
            while (verts.Position < verts.Length)
            {
                Vector3 v = verts.Read<Vector3>();
                data.Write(v);

                verts.Position += vertexStride - 12;

                // Normals will be calculated later
                data.Position += 12;
            }
            mesh.UnlockVertexBuffer();

            data = mesh.LockIndexBuffer(LockFlags.None);
            while (indices.Position < indices.Length)
            {
                int index = indices.Read<int>();
                if (index32)
                    data.Write(index);
                else
                    data.Write((short)index);
            }
            mesh.UnlockVertexBuffer();

            mesh.ComputeNormals();

            shapes.Add(shape, mesh);
            return mesh;
        }

        public void Render(CollisionObject body)
        {
            if (body.CollisionShape.ShapeType == BroadphaseNativeType.SoftBodyShape)
            {
                RenderSoftBody(body as SoftBody);
            }
            else
            {
                Render(body.CollisionShape);
            }
        }

        public void Render(CollisionShape shape)
        {
            Mesh mesh;

            if (shapes.TryGetValue(shape, out mesh))
            {
                mesh.DrawSubset(0);
                return;
            }

            if (complexShapes.TryGetValue(shape, out mesh))
            {
                RenderComplexShape(shape, mesh);
                return;
            }

            // Create the graphics mesh or go to child shapes.
            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.BoxShape:
                    mesh = CreateBoxShape(shape as BoxShape);
                    break;
                case BroadphaseNativeType.CylinderShape:
                    mesh = CreateCylinderShape(shape as CylinderShape);
                    break;
                case BroadphaseNativeType.ConeShape:
                    mesh = CreateConeShape(shape as ConeShape);
                    break;
                case BroadphaseNativeType.ConvexHullShape:
                    mesh = CreateConvexHullShape(shape as ConvexHullShape);
                    break;
                case BroadphaseNativeType.GImpactShape:
                    mesh = CreateGImpactMeshShape(shape as GImpactMeshShape);
                    break;
                case BroadphaseNativeType.Convex2DShape:
                    Render((shape as Convex2DShape).ChildShape);
                    return;
                case BroadphaseNativeType.CompoundShape:
                    CompoundShape compoundShape = shape as CompoundShape;
                    //if (compoundShape.NumChildShapes == 0)
                    //    return;
                    foreach (CompoundShapeChild child in compoundShape.ChildList)
                    {
                        // do a pre-transform
                        Matrix tempTr = device.GetTransform(TransformState.World);
                        device.SetTransform(TransformState.World, child.Transform * tempTr);

                        Render(child.ChildShape);
                    }
                    return;
                case BroadphaseNativeType.SphereShape:
                    mesh = CreateSphere(shape as SphereShape);
                    break;
                case BroadphaseNativeType.TriangleMeshShape:
                    mesh = CreateTriangleMeshShape(shape as TriangleMeshShape);
                    break;
            }

            // If the shape has one subset, render it.
            if (mesh != null)
            {
                mesh.DrawSubset(0);
                return;
            }

            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.CapsuleShape:
                    mesh = CreateCapsuleShape(shape as CapsuleShape);
                    break;
                case BroadphaseNativeType.MultiSphereShape:
                    mesh = CreateMultiSphereShape(shape as MultiSphereShape);
                    break;
                case BroadphaseNativeType.StaticPlaneShape:
                    mesh = CreateStaticPlaneShape(shape as StaticPlaneShape);
                    break;
            }

            RenderComplexShape(shape, mesh);
        }

        public void RenderComplexShape(CollisionShape shape, Mesh mesh)
        {
            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.StaticPlaneShape:
                    RenderStaticPlaneShape(mesh);
                    break;
                case BroadphaseNativeType.CapsuleShape:
                    RenderCapsuleShape(mesh);
                    break;
                case BroadphaseNativeType.MultiSphereShape:
                    RenderMultiSphereShape(shape as MultiSphereShape, mesh);
                    break;
            }
        }

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

        public void RenderSoftBody(SoftBody softBody)
        {
            AlignedFaceArray faces = softBody.Faces;
            int faceCount = faces.Count;

            if (faceCount > 0)
            {
                PositionedNormal[] vectors = new PositionedNormal[faceCount * 6];
                int v = 0;

                int i;
                for (i = 0; i < faces.Count; i++)
                {
                    NodePtrArray nodes = faces[i].N;
                    Node n0 = nodes[0];
                    Node n1 = nodes[1];
                    Node n2 = nodes[2];
                    n0.GetX(out vectors[v].Position);
                    n0.GetNormal(out vectors[v].Normal);
                    n1.GetX(out vectors[v + 1].Position);
                    n1.GetNormal(out vectors[v + 1].Normal);
                    n2.GetX(out vectors[v + 2].Position);
                    n2.GetNormal(out vectors[v + 2].Normal);
                    v += 3;
                }

                device.VertexFormat = PositionedNormal.FVF;
                device.DrawUserPrimitives(PrimitiveType.TriangleList, faces.Count, vectors);
            }
            else
            {
                AlignedTetraArray tetras = softBody.Tetras;
                int tetraCount = tetras.Count;

                if (tetraCount > 0)
                {
                    PositionedNormal[] vectors = new PositionedNormal[tetraCount * 12];
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
                        normal.Normalize();
                        vectors[v].Position = v0;
                        vectors[v].Normal = normal;
                        vectors[v + 1].Position = v1;
                        vectors[v + 1].Normal = normal;
                        vectors[v + 2].Position = v2;
                        vectors[v + 2].Normal = normal;

                        normal = Vector3.Cross(v10, v3 - v0);
                        normal.Normalize();
                        vectors[v + 3].Position = v0;
                        vectors[v + 3].Normal = normal;
                        vectors[v + 4].Position = v1;
                        vectors[v + 4].Normal = normal;
                        vectors[v + 5].Position = v3;
                        vectors[v + 5].Normal = normal;

                        normal = Vector3.Cross(v2 - v1, v3 - v1);
                        normal.Normalize();
                        vectors[v + 6].Position = v1;
                        vectors[v + 6].Normal = normal;
                        vectors[v + 7].Position = v2;
                        vectors[v + 7].Normal = normal;
                        vectors[v + 8].Position = v3;
                        vectors[v + 8].Normal = normal;

                        normal = Vector3.Cross(v02, v3 - v2);
                        normal.Normalize();
                        vectors[v + 9].Position = v2;
                        vectors[v + 9].Normal = normal;
                        vectors[v + 10].Position = v0;
                        vectors[v + 10].Normal = normal;
                        vectors[v + 11].Position = v3;
                        vectors[v + 11].Normal = normal;
                        v += 12;
                    }
                    device.VertexFormat = PositionedNormal.FVF;
                    device.DrawUserPrimitives(PrimitiveType.TriangleList, tetraCount * 4, vectors);
                }
                else if (softBody.Links.Count > 0)
                {
                    AlignedLinkArray links = softBody.Links;
                    int linkCount = links.Count;
                    int linkColor = System.Drawing.Color.Black.ToArgb();

                    device.VertexFormat = PositionColored.FVF;

                    PositionColored[] linkArray = new PositionColored[linkCount * 2];

                    for (int i = 0; i < linkCount; i++)
                    {
                        Link link = links[i];
                        linkArray[i * 2].Position = link.Nodes[0].X;
                        linkArray[i * 2].Color = linkColor;
                        linkArray[i * 2 + 1].Position = link.Nodes[1].X;
                        linkArray[i * 2 + 1].Color = linkColor;
                    }
                    device.DrawUserPrimitives(PrimitiveType.LineList, links.Count, linkArray);
                }
            }
        }

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
                        indices.Write((short)i);
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
    }
}
