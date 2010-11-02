using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using BulletSharp;
using BulletSharp.SoftBody;
using SlimDX;
using SlimDX.Direct3D9;

namespace DemoFramework
{
    // This class creates graphical objects (boxes, cones, cylinders, spheres) on the fly.
    public class GraphicObjectFactory : System.IDisposable
    {
        Device device;

        Dictionary<BoxShape, Mesh> boxes = new Dictionary<BoxShape, Mesh>();
        Dictionary<CapsuleShape, Mesh> capsules = new Dictionary<CapsuleShape, Mesh>();
        Dictionary<ConeShape, Mesh> cones = new Dictionary<ConeShape, Mesh>();
        Dictionary<CylinderShape, Mesh> cylinders = new Dictionary<CylinderShape, Mesh>();
        Dictionary<ConvexHullShape, Mesh> hullShapes = new Dictionary<ConvexHullShape, Mesh>();
        Dictionary<StaticPlaneShape, Mesh> planes = new Dictionary<StaticPlaneShape, Mesh>();
        Dictionary<GImpactMeshShape, Mesh> gImpactMeshShapes = new Dictionary<GImpactMeshShape, Mesh>();
        Dictionary<SphereShape, Mesh> spheres = new Dictionary<SphereShape, Mesh>();
        Dictionary<MultiSphereShape, Mesh> multiSpheres = new Dictionary<MultiSphereShape, Mesh>();

        Effect planeShader;

        public GraphicObjectFactory(Device device)
        {
            this.device = device;
        }

        public void Dispose()
        {
            foreach (Mesh mesh in boxes.Values)
            {
                mesh.Dispose();
            }
            boxes.Clear();

            foreach (Mesh mesh in capsules.Values)
            {
                mesh.Dispose();
            }
            capsules.Clear();

            foreach (Mesh mesh in cones.Values)
            {
                mesh.Dispose();
            }
            cones.Clear();

            foreach (Mesh mesh in cylinders.Values)
            {
                mesh.Dispose();
            }
            cylinders.Clear();

            foreach (Mesh mesh in gImpactMeshShapes.Values)
            {
                mesh.Dispose();
            }
            gImpactMeshShapes.Clear();

            foreach (Mesh mesh in hullShapes.Values)
            {
                mesh.Dispose();
            }
            hullShapes.Clear();

            foreach (Mesh mesh in planes.Values)
            {
                mesh.Dispose();
            }
            planes.Clear();

            foreach (Mesh mesh in spheres.Values)
            {
                mesh.Dispose();
            }
            spheres.Clear();

            foreach (Mesh mesh in multiSpheres.Values)
            {
                mesh.Dispose();
            }
            multiSpheres.Clear();

            if (planeShader != null)
                planeShader.Dispose();
        }

        // Local transforms are needed for CompoundShapes.
        void DoLocalTransform(Matrix localTransform)
        {
            Matrix tempTr = device.GetTransform(TransformState.World);
            device.SetTransform(TransformState.World, localTransform * tempTr);
        }

        public void Render(CollisionObject body)
        {
            if (body.CollisionShape.ShapeType == BroadphaseNativeType.SoftBodyShape)
            {
                RenderSoftBody(SoftBody.Upcast(body));
            }
            else
            {
                Render(body.CollisionShape, Matrix.Identity);
            }
        }

        public void Render(CollisionShape shape, Matrix localTransform)
        {
            shape = shape.UpcastDetect();

            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.BoxShape:
                    RenderBox((BoxShape)shape, localTransform);
                    return;
                case BroadphaseNativeType.ConeShape:
                    RenderCone((ConeShape)shape, localTransform);
                    return;
                case BroadphaseNativeType.Convex2DShape:
                    RenderConvex2dShape((Convex2DShape)shape, localTransform);
                    return;
                case BroadphaseNativeType.ConvexHullShape:
                    RenderConvexHullShape((ConvexHullShape)shape, localTransform);
                    return;
                case BroadphaseNativeType.CylinderShape:
                    RenderCylinder((CylinderShape)shape, localTransform);
                    return;
                case BroadphaseNativeType.SphereShape:
                    RenderSphere((SphereShape)shape, localTransform);
                    return;
                case BroadphaseNativeType.CompoundShape:
                    RenderCompoundShape((CompoundShape)shape, localTransform);
                    return;
                case BroadphaseNativeType.CapsuleShape:
                    RenderCapsuleShape((CapsuleShape)shape, localTransform);
                    return;
                case BroadphaseNativeType.MultiSphereShape:
                    RenderMultiSphereShape((MultiSphereShape)shape, localTransform);
                    return;
                case BroadphaseNativeType.StaticPlane:
                    RenderStaticPlaneShape((StaticPlaneShape)shape, localTransform);
                    return;
                case BroadphaseNativeType.GImpactShape:
                    RenderGImpactMeshShape((GImpactMeshShape)shape, localTransform);
                    return;
            }

            //throw new NotImplementedException();
        }

        public void RenderBox(BoxShape shape, Matrix localTransform)
        {
            if (localTransform.IsIdentity == false)
                DoLocalTransform(localTransform);

            Mesh boxMesh;

            if (boxes.TryGetValue(shape, out boxMesh) == false)
            {
                Vector3 size = shape.HalfExtentsWithMargin;
                boxMesh = Mesh.CreateBox(device, size.X * 2, size.Y * 2, size.Z * 2);
                boxes.Add(shape, boxMesh);
            }

            boxMesh.DrawSubset(0);
        }

        public void RenderCapsuleShape(CapsuleShape shape, Matrix localTransform)
        {
            if (localTransform.IsIdentity == false)
                DoLocalTransform(localTransform);

            Mesh compoundMesh;

            if (capsules.TryGetValue(shape, out compoundMesh) == false)
            {
                // Combine a cylinder and two spheres.
                Vector3 size = shape.ImplicitShapeDimensions;
                Mesh cylinder = Mesh.CreateCylinder(device, size.X, size.X, size.Y * 2, 8, 1);
                Mesh sphere = Mesh.CreateSphere(device, size.Z, 8, 4);
                Mesh[] meshes = new Mesh[] { sphere, cylinder, sphere };
                Matrix[] transforms = new Matrix[] {
                    Matrix.Translation(0, -size.Y, 0),
                    Matrix.RotationX((float)Math.PI / 2),
                    Matrix.Translation(0, size.Y, 0)};
                compoundMesh = Mesh.Concatenate(device, meshes, MeshFlags.Managed, transforms, null);
                cylinder.Dispose();
                sphere.Dispose();

                capsules.Add(shape, compoundMesh);
            }

            compoundMesh.DrawSubset(0);
            compoundMesh.DrawSubset(1);
            compoundMesh.DrawSubset(2);
        }

        public void RenderCone(ConeShape shape, Matrix localTransform)
        {
            if (localTransform.IsIdentity == false)
                DoLocalTransform(localTransform);

            Mesh coneMesh;

            if (cones.TryGetValue(shape, out coneMesh) == false)
            {
                coneMesh = Mesh.CreateCylinder(device, 0, shape.Radius, shape.Height, 16, 1);
                cones.Add(shape, coneMesh);
            }

            coneMesh.DrawSubset(0);
        }

        public void RenderCylinder(CylinderShape shape, Matrix localTransform)
        {
            if (localTransform.IsIdentity == false)
                DoLocalTransform(localTransform);

            Mesh mesh;

            if (cylinders.TryGetValue(shape, out mesh) == false)
            {
                int upAxis = shape.UpAxis;
                float radius = shape.Radius;
                float halfHeight = shape.HalfExtentsWithoutMargin[upAxis] + shape.Margin;
                
                mesh = Mesh.CreateCylinder(device, radius, radius, halfHeight * 2, 16, 1);
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
                cylinders.Add(shape, mesh);
            }

            mesh.DrawSubset(0);
        }

        public void RenderSphere(SphereShape shape, Matrix localTransform)
        {
            if (localTransform.IsIdentity == false)
                DoLocalTransform(localTransform);

            Mesh sphereMesh;

            if (spheres.TryGetValue(shape, out sphereMesh) == false)
            {
                sphereMesh = Mesh.CreateSphere(device, shape.Radius, 16, 16);
                spheres.Add(shape, sphereMesh);
            }

            sphereMesh.DrawSubset(0);
        }

        public void RenderConvex2dShape(Convex2DShape shape, Matrix localTransform)
        {
            if (localTransform.IsIdentity == false)
                DoLocalTransform(localTransform);

            Render(shape.ChildShape, Matrix.Identity);
        }

        public void RenderConvexHullShape(ConvexHullShape shape, Matrix localTransform)
        {
            if (localTransform.IsIdentity == false)
                DoLocalTransform(localTransform);
            
            Mesh hullMesh;
            if (hullShapes.TryGetValue(shape, out hullMesh) == false)
            {
                int vertexCount = shape.NumPoints;
                int faceCount = vertexCount / 3;
                vertexCount = faceCount * 3; // must be 3 verts for every face

                bool index32 = vertexCount > 65536;

                hullMesh = new Mesh(device, faceCount, vertexCount,
                    MeshFlags.SystemMemory | (index32 ? MeshFlags.Use32Bit : 0), VertexFormat.Position | VertexFormat.Normal);


                SlimDX.DataStream indices = hullMesh.LockIndexBuffer(LockFlags.Discard);
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
                hullMesh.UnlockIndexBuffer();

                SlimDX.DataStream verts = hullMesh.LockVertexBuffer(LockFlags.Discard);
                Vector3Array points = shape.UnscaledPoints;
                Vector3 scale = Vector3.Multiply(shape.LocalScaling, 1.0f + shape.Margin);
                for (i = 0; i < vertexCount; )
                {
                    verts.Write(Vector3.Modulate(points[i++], scale));
                    verts.Position += 12;
                    verts.Write(Vector3.Modulate(points[i++], scale));
                    verts.Position += 12;
                    verts.Write(Vector3.Modulate(points[i++], scale));
                    verts.Position += 12;
                }
                hullMesh.UnlockVertexBuffer();

                hullMesh.ComputeNormals();
                hullShapes.Add(shape, hullMesh);
            }

            hullMesh.DrawSubset(0);
        }

        public void RenderCompoundShape(CompoundShape shape, Matrix localTransform)
        {
            if (localTransform.IsIdentity == false)
                DoLocalTransform(localTransform);

            if (shape.NumChildShapes > 0)
            {
                foreach (CompoundShapeChild child in shape.ChildList)
                {
                    Render(child.ChildShape, child.Transform);
                }
            }
        }

        public void RenderGImpactMeshShape(GImpactMeshShape shape, Matrix localTransform)
        {
            if (localTransform.IsIdentity == false)
                DoLocalTransform(localTransform);

            Mesh gImpactMesh;

            if (gImpactMeshShapes.TryGetValue(shape, out gImpactMesh) == false)
            {
                BulletSharp.DataStream verts, indices;
                int numVerts, numFaces;
                PhyScalarType vertsType, indicesType;
                int vertexStride, indexStride;
                shape.MeshInterface.GetLockedReadOnlyVertexIndexData(out verts, out numVerts, out vertsType, out vertexStride,
                    out indices, out indexStride, out numFaces, out indicesType);

                bool index32 = numVerts > 65536;

                gImpactMesh = new Mesh(device, numFaces, numVerts,
                    MeshFlags.SystemMemory | (index32 ? MeshFlags.Use32Bit : 0), VertexFormat.Position | VertexFormat.Normal);

                SlimDX.DataStream vertexBuffer = gImpactMesh.LockVertexBuffer(LockFlags.Discard);
                while (vertexBuffer.Position < vertexBuffer.Length)
                {
                    vertexBuffer.Write(verts.Read<Vector3>());
                    vertexBuffer.Position += 12;
                }
                gImpactMesh.UnlockVertexBuffer();

                SlimDX.DataStream indexBuffer = gImpactMesh.LockIndexBuffer(LockFlags.Discard);
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
                gImpactMesh.UnlockIndexBuffer();

                gImpactMesh.ComputeNormals();
            }

            gImpactMesh.DrawSubset(0);
        }

        public void RenderMultiSphereShape(MultiSphereShape shape, Matrix localTransform)
        {
            if (localTransform.IsIdentity == false)
                DoLocalTransform(localTransform);

            Mesh multiSphereMesh;
            
            if (multiSpheres.TryGetValue(shape, out multiSphereMesh) == false)
            {
                int i;
                for (i = 0; i < shape.SphereCount; i++)
                {
                    Vector3 position = shape.GetSpherePosition(i);

                    Mesh sphereMesh = Mesh.CreateSphere(device, shape.GetSphereRadius(i), 12, 12);
                    if (i == 0)
                    {
                        Matrix[] transform = new Matrix[] { Matrix.Translation(position) };
                        multiSphereMesh = Mesh.Concatenate(device, new Mesh[] { sphereMesh }, MeshFlags.Managed, transform, null);
                    }
                    else
                    {
                        Mesh multiSphereMeshNew;
                        Matrix[] transform = new Matrix[] { Matrix.Identity, Matrix.Translation(position) };
                        multiSphereMeshNew = Mesh.Concatenate(device, new Mesh[] { multiSphereMesh, sphereMesh }, MeshFlags.Managed, transform, null);
                        multiSphereMesh.Dispose();
                        multiSphereMesh = multiSphereMeshNew;
                    }
                    sphereMesh.Dispose();
                }
                multiSpheres.Add(shape, multiSphereMesh);
            }
            
            for (int i=0; i<shape.SphereCount; i++)
                multiSphereMesh.DrawSubset(i);
        }

        public void RenderStaticPlaneShape(StaticPlaneShape shape, Matrix localTransform)
        {
            if (localTransform.IsIdentity == false)
                DoLocalTransform(localTransform);

            Mesh planeMesh;

            if (planes.TryGetValue(shape, out planeMesh) == false)
            {
                // Load shader
                if (planes.Count == 0)
                {
                    Assembly assembly = Assembly.GetExecutingAssembly();
                    Stream shaderStream = assembly.GetManifestResourceStream("DemoFramework.checker_shader.fx");

                    planeShader = Effect.FromStream(device, shaderStream, ShaderFlags.None);
                }


                Vector3[] vertices = new Vector3[4 * 2];

                planeMesh = new Mesh(device, 2, 4, MeshFlags.SystemMemory, VertexFormat.Position | VertexFormat.Normal);

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
                
                SlimDX.DataStream vertexBuffer = planeMesh.LockVertexBuffer(LockFlags.Discard);
                vertexBuffer.Write(verts[0]);
                vertexBuffer.Position += 12;
                vertexBuffer.Write(verts[1]);
                vertexBuffer.Position += 12;
                vertexBuffer.Write(verts[2]);
                vertexBuffer.Position += 12;
                vertexBuffer.Write(verts[3]);
                vertexBuffer.Position += 12;
                planeMesh.UnlockVertexBuffer();

                SlimDX.DataStream indexBuffer = planeMesh.LockIndexBuffer(LockFlags.Discard);
                indexBuffer.Write((short)1);
                indexBuffer.Write((short)2);
                indexBuffer.Write((short)0);
                indexBuffer.Write((short)1);
                indexBuffer.Write((short)3);
                indexBuffer.Write((short)0);
                planeMesh.UnlockIndexBuffer();
                
                planeMesh.ComputeNormals();

                planes.Add(shape, planeMesh);
            }

            Cull cullMode = device.GetRenderState<Cull>(RenderState.CullMode);
            device.SetRenderState(RenderState.CullMode, Cull.None);
            planeShader.Begin();
            Matrix matrix = device.GetTransform(TransformState.World);
            planeShader.SetValue("World", matrix);
            matrix = device.GetTransform(TransformState.View) * device.GetTransform(TransformState.Projection);
            planeShader.SetValue("ViewProjection", matrix);
            planeShader.BeginPass(0);
            planeMesh.DrawSubset(0);
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
                int vertexCount = faceCount * 3;
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
                foreach (Face face in faces)
                {
                    NodePtrArray nodes = face.N;
                    verts.Write(nodes[0].X);
                    verts.Position += 12;
                    verts.Write(nodes[1].X);
                    verts.Position += 12;
                    verts.Write(nodes[2].X);
                    verts.Position += 12;
                }
                mesh.UnlockVertexBuffer();

                mesh.ComputeNormals();
                mesh.DrawSubset(0);
                mesh.Dispose();
            }
            else
            {
                AlignedTetraArray tetras = softBody.Tetras;
                int tetraCount = tetras.Count;

                if (tetraCount > 0)
                {
                    int vertexCount = tetraCount * 12;
                    bool index32 = vertexCount > 65536;

                    Mesh mesh = new Mesh(device, tetraCount * 4, vertexCount,
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
                    foreach (Tetra t in tetras)
                    {
                        NodePtrArray nodes = t.Nodes;

                        verts.Write(nodes[2].X);
                        verts.Position += 12;
                        verts.Write(nodes[1].X);
                        verts.Position += 12;
                        verts.Write(nodes[0].X);
                        verts.Position += 12;

                        verts.Write(nodes[0].X);
                        verts.Position += 12;
                        verts.Write(nodes[1].X);
                        verts.Position += 12;
                        verts.Write(nodes[3].X);
                        verts.Position += 12;

                        verts.Write(nodes[2].X);
                        verts.Position += 12;
                        verts.Write(nodes[3].X);
                        verts.Position += 12;
                        verts.Write(nodes[1].X);
                        verts.Position += 12;

                        verts.Write(nodes[2].X);
                        verts.Position += 12;
                        verts.Write(nodes[0].X);
                        verts.Position += 12;
                        verts.Write(nodes[3].X);
                        verts.Position += 12;
                    }
                    mesh.UnlockVertexBuffer();

                    mesh.ComputeNormals();
                    mesh.DrawSubset(0);
                    mesh.Dispose();
                }
                else if (softBody.Links.Count > 0)
                {
                    AlignedLinkArray links = softBody.Links;
                    int linkCount = links.Count;
                    int linkColor = System.Drawing.Color.Black.ToArgb();

                    device.SetRenderState(RenderState.Lighting, false);
                    device.SetTransform(TransformState.World, Matrix.Identity);
                    device.VertexFormat = PositionColored.FVF;

                    PositionColored[] linkArray = new PositionColored[linkCount * 2];

                    for (int i=0; i<linkCount; i++)
                    {
                        Link link = links[i];
                        linkArray[i * 2] = new PositionColored(link.Nodes[0].X, linkColor);
                        linkArray[i * 2 + 1] = new PositionColored(link.Nodes[1].X, linkColor);
                    }
                    device.DrawUserPrimitives(PrimitiveType.LineList, links.Count, linkArray);

                    device.SetRenderState(RenderState.Lighting, true);
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

            int vertexCount = (vertexBuffer.Count / 8) ;

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
