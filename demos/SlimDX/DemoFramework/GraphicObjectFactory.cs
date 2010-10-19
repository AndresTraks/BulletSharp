using BulletSharp;
using BulletSharp.SoftBody;
using System;
using System.Collections.Generic;
using SlimDX;
using SlimDX.Direct3D9;

namespace DemoFramework
{
    // This class creates graphical objects (boxes, cones, cylinders, spheres) on the fly.
    public class GraphicObjectFactory : System.IDisposable
    {
        Device device;

        Dictionary<Vector3, Mesh> boxes = new Dictionary<Vector3, Mesh>();
        Dictionary<Vector3, Mesh> capsules = new Dictionary<Vector3, Mesh>();
        Dictionary<Vector2, Mesh> cones = new Dictionary<Vector2, Mesh>();
        Dictionary<Vector3, Mesh> cylinders = new Dictionary<Vector3, Mesh>();
        Dictionary<float, Mesh> spheres = new Dictionary<float, Mesh>();

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

            foreach (Mesh mesh in cylinders.Values)
            {
                mesh.Dispose();
            }
            cylinders.Clear();

            foreach (Mesh mesh in spheres.Values)
            {
                mesh.Dispose();
            }
            spheres.Clear();

            foreach (Mesh mesh in cones.Values)
            {
                mesh.Dispose();
            }
            cones.Clear();
        }

        public void Render(CollisionObject body)
        {
            if (body.CollisionShape.ShapeType == BroadphaseNativeType.SoftBodyShape)
            {
                RenderSoftBody(SoftBody.Upcast(body));
            }
            Render(body.CollisionShape);
        }

        public void Render(CollisionShape shape)
        {
            shape = shape.UpcastDetect();

            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.BoxShape:
                    RenderBox((BoxShape)shape);
                    return;
                case BroadphaseNativeType.ConeShape:
                    RenderCone((ConeShape)shape);
                    return;
                case BroadphaseNativeType.Convex2DShape:
                    RenderConvex2dShape((Convex2DShape)shape);
                    return;
                case BroadphaseNativeType.CylinderShape:
                    RenderCylinder((CylinderShape)shape);
                    return;
                case BroadphaseNativeType.SphereShape:
                    RenderSphere((SphereShape)shape);
                    return;
                case BroadphaseNativeType.CompoundShape:
                    RenderCompoundShape((CompoundShape)shape);
                    return;
                case BroadphaseNativeType.CapsuleShape:
                    RenderCapsuleShape((CapsuleShape)shape);
                    return;
            }

            //throw new NotImplementedException();
        }

        public void RenderBox(BoxShape shape)
        {
            Mesh boxMesh;
            Vector3 size = shape.HalfExtentsWithMargin * 2;

            if (boxes.TryGetValue(size, out boxMesh) == false)
            {
                boxMesh = Mesh.CreateBox(device, size.X, size.Y, size.Z);
                boxes.Add(size, boxMesh);
            }

            boxMesh.DrawSubset(0);
        }

        public void RenderCapsuleShape(CapsuleShape shape)
        {
            Mesh compoundMesh;
            Vector3 size = shape.ImplicitShapeDimensions;

            if (capsules.TryGetValue(size, out compoundMesh) == false)
            {
                // Combine a cylinder and two spheres.
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

                capsules.Add(size, compoundMesh);
            }

            compoundMesh.DrawSubset(0);
            compoundMesh.DrawSubset(1);
            compoundMesh.DrawSubset(2);
        }

        public void RenderCone(ConeShape shape)
        {
            Mesh coneMesh;
            float radius = shape.Radius;
            float height = shape.Height;
            Vector2 dimensions = new Vector2(radius, height);

            if (cones.TryGetValue(dimensions, out coneMesh) == false)
            {
                coneMesh = Mesh.CreateCylinder(device, 0, radius, height, 16, 1);
                cones.Add(dimensions, coneMesh);
            }

            coneMesh.DrawSubset(0);
        }

        public void RenderCylinder(CylinderShape shape)
        {
            Mesh cylinderMesh;
            Vector3 size = shape.HalfExtentsWithMargin * 2;

            if (cylinders.TryGetValue(size, out cylinderMesh) == false)
            {
                cylinderMesh = Mesh.CreateCylinder(device, size.X / 2, size.X / 2, size.Z, 32, 1);
                cylinders.Add(size, cylinderMesh);
            }

            cylinderMesh.DrawSubset(0);
        }

        public void RenderSphere(SphereShape shape)
        {
            Mesh sphereMesh;
            float radius = shape.Radius;

            if (spheres.TryGetValue(radius, out sphereMesh) == false)
            {
                sphereMesh = Mesh.CreateSphere(device, radius, 16, 16);
                spheres.Add(radius, sphereMesh);
            }

            sphereMesh.DrawSubset(0);
        }

        public bool RenderConvex2dShape(Convex2DShape shape)
        {
            CollisionShape childShape = shape.ChildShape.UpcastDetect();

            switch (childShape.ShapeType)
            {
                case BroadphaseNativeType.BoxShape:
                    RenderBox((BoxShape)childShape);
                    return true;
                case BroadphaseNativeType.CylinderShape:
                    RenderCylinder((CylinderShape)childShape);
                    return true;
            }

            return false;
        }

        public void RenderCompoundShape(CompoundShape shape)
        {
            if (shape.NumChildShapes > 0)
            {
                foreach (CompoundShapeChild child in shape.ChildList)
                {
                    Render(child.ChildShape);
                }
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
            }
        }
    }
}