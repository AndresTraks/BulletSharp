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

        public bool Render(CollisionObject body)
        {
            if (body.CollisionShape.ShapeType == BroadphaseNativeType.SoftBodyShape)
            {
                RenderSoftBody(SoftBody.Upcast(body));
                return true;
            }
            return Render(body.CollisionShape);
        }

        public bool Render(CollisionShape shape)
        {
            shape = shape.UpcastDetect();

            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.BoxShape:
                    RenderBox((BoxShape)shape);
                    return true;
                case BroadphaseNativeType.ConeShape:
                    RenderCone((ConeShape)shape);
                    return true;
                case BroadphaseNativeType.Convex2dShape:
                    return RenderConvex2dShape((Convex2dShape)shape);
                case BroadphaseNativeType.CylinderShape:
                    RenderCylinder((CylinderShape)shape);
                    return true;
                case BroadphaseNativeType.SphereShape:
                    RenderSphere((SphereShape)shape);
                    return true;
                case BroadphaseNativeType.CompoundShape:
                    RenderCompoundShape((CompoundShape)shape);
                    return true;
            }

            return false;
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

        public bool RenderConvex2dShape(Convex2dShape shape)
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
            CompoundShapeChildArray childShapes = shape.ChildList;
            if (childShapes != null)
            {
                foreach (CompoundShapeChild child in childShapes)
                {
                    Render(child.ChildShape);
                }
            }
        }

        public void RenderSoftBody(SoftBody softBody)
        {
            if (softBody.Faces.Size == 0)
                return;

            Mesh mesh = new Mesh(device, softBody.Faces.Size, softBody.Faces.Size * 3,
                MeshFlags.SystemMemory | MeshFlags.Use32Bit, VertexFormat.Position);

            SlimDX.DataStream verts = mesh.LockVertexBuffer(LockFlags.None);
            SlimDX.DataStream indices = mesh.LockIndexBuffer(LockFlags.None);

            int j;
            for (j = 0; j < softBody.Faces.Size; j++)
            {
                BulletSharp.SoftBody.Face face = softBody.Faces[j];
                verts.Write(face.n[0].x);
                verts.Write(face.n[1].x);
                verts.Write(face.n[2].x);

                indices.Write(j * 3);
                indices.Write(j * 3 + 1);
                indices.Write(j * 3 + 2);
            }

            mesh.UnlockVertexBuffer();
            mesh.UnlockIndexBuffer();

            mesh.DrawSubset(0);
            mesh.Dispose();
        }
    }
}