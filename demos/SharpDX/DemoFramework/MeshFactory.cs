using System;
using System.Collections.Generic;
using System.Drawing;
using BulletSharp;
using BulletSharp.SoftBody;
using SharpDX;
using SharpDX.Direct3D10;
using SharpDX.DXGI;
using Device = SharpDX.Direct3D10.Device;
using Mesh = SharpDX.Direct3D10.Mesh;

namespace DemoFramework
{
    // This class creates graphical objects (boxes, cones, cylinders, spheres) on the fly.
    public class MeshFactory : System.IDisposable
    {
        Device device;
        Demo demo;
        Dictionary<CollisionShape, Mesh> shapes = new Dictionary<CollisionShape, Mesh>();
        Dictionary<CollisionShape, Mesh> complexShapes = new Dictionary<CollisionShape, Mesh>(); // these have more than 1 subset
        Effect planeShader;

        public MeshFactory(Demo demo)
        {
            this.demo = demo;
            this.device = demo.Device;
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
                planeShader.Release();
        }

        Mesh CreateBoxShape(BoxShape shape)
        {
            Vector3 size = shape.HalfExtentsWithMargin;
            float x = size.X;
            float y = size.Y;
            float z = size.Z;

            InputElement[] elements = new InputElement[] {
                new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0, InputClassification.PerVertexData, 0),
                new InputElement("NORMAL", 0, Format.R32G32B32_Float, 12, 0, InputClassification.PerVertexData, 0)
            };
            Mesh mesh = new Mesh(device, elements, "POSITION", 36, 12, MeshFlags.None);

            MeshBuffer vertexBuffer = mesh.GetVertexBuffer(0);
            SharpDX.DataStream vStream = vertexBuffer.Map();

            // Draw two sides
            for (int i = 1; i != -3; i -= 2)
            {
                vStream.Write(new Vector3(i * x, y, -z));
                vStream.Write(new Vector3(i, 0, 0));
                vStream.Write(new Vector3(i * x, -y, -z));
                vStream.Write(new Vector3(i, 0, 0));
                vStream.Write(new Vector3(i * x, -y, z));
                vStream.Write(new Vector3(i, 0, 0));
                vStream.Write(new Vector3(i * x, y, -z));
                vStream.Write(new Vector3(i, 0, 0));
                vStream.Write(new Vector3(i * x, y, z));
                vStream.Write(new Vector3(i, 0, 0));
                vStream.Write(new Vector3(i * x, -y, z));
                vStream.Write(new Vector3(i, 0, 0));
            }

            for (int i = 1; i != -3; i -= 2)
            {
                vStream.Write(new Vector3(-x, y, i * z));
                vStream.Write(new Vector3(0, 0, i));
                vStream.Write(new Vector3(-x, -y, i * z));
                vStream.Write(new Vector3(0, 0, i));
                vStream.Write(new Vector3(x, -y, i * z));
                vStream.Write(new Vector3(0, 0, i));
                vStream.Write(new Vector3(-x, y, i * z));
                vStream.Write(new Vector3(0, 0, i));
                vStream.Write(new Vector3(x, y, i * z));
                vStream.Write(new Vector3(0, 0, i));
                vStream.Write(new Vector3(x, -y, i * z));
                vStream.Write(new Vector3(0, 0, i));
            }

            for (int i = 1; i != -3; i -= 2)
            {
                vStream.Write(new Vector3(-x, i * y, -z));
                vStream.Write(new Vector3(0, i, 0));
                vStream.Write(new Vector3(x, i * y, -z));
                vStream.Write(new Vector3(0, i, 0));
                vStream.Write(new Vector3(-x, i * y, z));
                vStream.Write(new Vector3(0, i, 0));
                vStream.Write(new Vector3(x, i * y, z));
                vStream.Write(new Vector3(0, i, 0));
                vStream.Write(new Vector3(-x, i * y, z));
                vStream.Write(new Vector3(0, i, 0));
                vStream.Write(new Vector3(x, i * y, -z));
                vStream.Write(new Vector3(0, i, 0));
            }

            vertexBuffer.Unmap();

            MeshBuffer indexBuffer = mesh.GetIndexBuffer();
            SharpDX.DataStream iStream = indexBuffer.Map();
            for (short ii = 0; ii < mesh.VertexCount; ii++)
                iStream.Write(ii);
            indexBuffer.Unmap();

            mesh.Commit();

            shapes.Add(shape, mesh);
            return mesh;
        }
        /*
        Mesh CreateCapsuleShape(CapsuleShape shape)
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
        */

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

        Mesh CreateCylinderShape(CylinderShape shape)
        {
            int up = shape.UpAxis;
            float radius = shape.Radius;
            float halfHeight = shape.HalfExtentsWithoutMargin[up] + shape.Margin;

            int numSteps = 10;
            float angleStep = (2 * (float)Math.PI) / numSteps;

            InputElement[] elements = new InputElement[] {
                new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0, InputClassification.PerVertexData, 0),
                new InputElement("NORMAL", 0, Format.R32G32B32_Float, 12, 0, InputClassification.PerVertexData, 0)
            };
            Mesh mesh = new Mesh(device, elements, "POSITION", 2 + 6 * numSteps, 4 * numSteps, MeshFlags.None);

            MeshBuffer vertexBuffer = mesh.GetVertexBuffer(0);
            SharpDX.DataStream vStream = vertexBuffer.Map();

            MeshBuffer indexBuffer = mesh.GetIndexBuffer();
            SharpDX.DataStream iStream = indexBuffer.Map();
            int index = 0;

            Vector3 normal = GetVectorByAxis(Vector3.UnitY, up);
            normal.Normalize();

            int baseIndex = index;
            vStream.Write(GetVectorByAxis(new Vector3(0, halfHeight, 0), up));
            vStream.Write(normal);

            vStream.Write(GetVectorByAxis(new Vector3(0, halfHeight, radius), up));
            vStream.Write(normal);
            index += 2;

            for (int i = 1; i < numSteps; i++)
            {
                float x = radius * (float)Math.Sin(i * angleStep);
                float z = radius * (float)Math.Cos(i * angleStep);

                vStream.Write(GetVectorByAxis(new Vector3(x, halfHeight, z), up));
                vStream.Write(normal);

                iStream.Write((short)baseIndex);
                iStream.Write((short)(index - 1));
                iStream.Write((short)(index++));
            }
            iStream.Write((short)baseIndex);
            iStream.Write((short)(index - 1));
            iStream.Write((short)(baseIndex + 1));


            normal = GetVectorByAxis(-Vector3.UnitY, up);

            baseIndex = index;
            vStream.Write(GetVectorByAxis(new Vector3(0, -halfHeight, 0), up));
            vStream.Write(normal);

            vStream.Write(GetVectorByAxis(new Vector3(0, -halfHeight, radius), up));
            vStream.Write(normal);
            index += 2;

            for (int i = 1; i < numSteps; i++)
            {
                float x = radius * (float)Math.Sin(i * angleStep);
                float z = radius * (float)Math.Cos(i * angleStep);

                vStream.Write(GetVectorByAxis(new Vector3(x, -halfHeight, z), up));
                vStream.Write(normal);

                iStream.Write((short)baseIndex);
                iStream.Write((short)(index - 1));
                iStream.Write((short)(index++));
            }
            iStream.Write((short)baseIndex);
            iStream.Write((short)(index - 1));
            iStream.Write((short)(baseIndex + 1));


            normal = GetVectorByAxis(new Vector3(0, 0, radius), up);
            normal.Normalize();

            baseIndex = index;
            vStream.Write(GetVectorByAxis(new Vector3(0, halfHeight, radius), up));
            vStream.Write(normal);

            vStream.Write(GetVectorByAxis(new Vector3(0, -halfHeight, radius), up));
            vStream.Write(normal);
            index += 2;

            for (int i = 1; i < numSteps + 1; i++)
            {
                float x = radius * (float)Math.Sin(i * angleStep);
                float z = radius * (float)Math.Cos(i * angleStep);

                normal = GetVectorByAxis(new Vector3(x, 0, z), up);
                normal.Normalize();

                vStream.Write(GetVectorByAxis(new Vector3(x, halfHeight, z), up));
                vStream.Write(normal);

                vStream.Write(GetVectorByAxis(new Vector3(x, -halfHeight, z), up));
                vStream.Write(normal);

                iStream.Write((short)(index - 2));
                iStream.Write((short)(index - 1));
                iStream.Write((short)(index));
                iStream.Write((short)(index));
                iStream.Write((short)(index - 1));
                iStream.Write((short)(++index));
                index++;
            }
            iStream.Write((short)(index - 2));
            iStream.Write((short)(index - 1));
            iStream.Write((short)(baseIndex));
            iStream.Write((short)(baseIndex));
            iStream.Write((short)(index - 1));
            iStream.Write((short)(baseIndex + 1));

            vertexBuffer.Unmap();
            indexBuffer.Unmap();

            mesh.Commit();

            shapes.Add(shape, mesh);
            return mesh;
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
                    indexBuffer.Write((short)indices.Read<int>());
            }
            mesh.UnlockIndexBuffer();

            mesh.ComputeNormals();
            return mesh;
        }

        Mesh CreateConvexHullShape(ConvexHullShape shape)
        {
            int vertexCount = shape.NumPoints;
            int faceCount = vertexCount / 3;
            vertexCount = faceCount * 3; // must be 3 verts for every face

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
        */
        Mesh CreateSphere(SphereShape shape)
        {
            float radius = shape.Radius;
            int slices = (int)(radius * 10);
            int stacks = (int)(radius * 10);
            float hAngleStep = (float)Math.PI * 2 / slices;
            float vAngleStep = (float)Math.PI / stacks;

            InputElement[] elements = new InputElement[] {
                new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0, InputClassification.PerVertexData, 0),
                new InputElement("NORMAL", 0, Format.R32G32B32_Float, 12, 0, InputClassification.PerVertexData, 0)
            };
            Mesh mesh = new Mesh(device, elements, "POSITION", (6 * slices) * (stacks - 2), 2 * slices * stacks - 2 * slices, MeshFlags.None);

            MeshBuffer vertexBuffer = mesh.GetVertexBuffer(0);
            SharpDX.DataStream vStream = vertexBuffer.Map();

            MeshBuffer indexBuffer = mesh.GetIndexBuffer();
            SharpDX.DataStream iStream = indexBuffer.Map();
            int index = 0;


            // Bottom cap
            vStream.Write(new Vector3(0, -radius, 0));
            vStream.Write(-Vector3.UnitY);
            index++;

            float angle = 0;
            float vAngle = -(float)Math.PI / 2 + vAngleStep;

            Vector3 v = new Vector3((float)Math.Cos(vAngle) * (float)Math.Sin(angle), (float)Math.Sin(vAngle), (float)Math.Cos(vAngle) * (float)Math.Cos(angle));
            vStream.Write(v * radius);
            vStream.Write(Vector3.Normalize(v));
            index++;

            int i;
            for (i = 0; i < slices - 1; i++)
            {
                iStream.Write((short)0);
                iStream.Write((short)(index - 1));

                angle += hAngleStep;

                v = new Vector3((float)Math.Cos(vAngle) * (float)Math.Sin(angle), (float)Math.Sin(vAngle), (float)Math.Cos(vAngle) * (float)Math.Cos(angle));
                vStream.Write(v * radius);
                vStream.Write(Vector3.Normalize(v));
                iStream.Write((short)index);
                index++;
            }

            iStream.Write((short)0);
            iStream.Write((short)(index - 1));
            iStream.Write((short)1);

            
            // Stacks
            for (i = 0; i < stacks - 2; i++)
            {
                vAngle += vAngleStep;

                angle = 0;

                v = new Vector3((float)Math.Cos(vAngle) * (float)Math.Sin(angle), (float)Math.Sin(vAngle), (float)Math.Cos(vAngle) * (float)Math.Cos(angle));
                vStream.Write(v * radius);
                vStream.Write(Vector3.Normalize(v));
                index++;

                int j;
                for (j = 0; j < slices - 1; j++)
                {
                    iStream.Write((short)(index - slices - 1));
                    iStream.Write((short)(index - 1));
                    iStream.Write((short)(index - slices));

                    angle += hAngleStep;
                    iStream.Write((short)(index - 1));
                    iStream.Write((short)(index - slices));

                    v = new Vector3((float)Math.Cos(vAngle) * (float)Math.Sin(angle), (float)Math.Sin(vAngle), (float)Math.Cos(vAngle) * (float)Math.Cos(angle));
                    vStream.Write(v * radius);
                    vStream.Write(Vector3.Normalize(v));
                    iStream.Write((short)index);
                    index++;
                }

                iStream.Write((short)(index - 2 * slices));
                iStream.Write((short)(index - slices));
                iStream.Write((short)(index - slices - 1));

                iStream.Write((short)(index - slices - 1));
                iStream.Write((short)(index - slices));
                iStream.Write((short)(index - 1));
            }


            // Top cap
            vStream.Write(new Vector3(0, radius, 0));
            vStream.Write(Vector3.UnitY);

            for (i = 1; i < slices; i++)
            {
                iStream.Write((short)index);
                iStream.Write((short)(index - i));
                iStream.Write((short)(index - i - 1));
            }
            
            iStream.Write((short)index);
            iStream.Write((short)(index - i));
            iStream.Write((short)(index - 1));


            vertexBuffer.Unmap();
            indexBuffer.Unmap();

            mesh.Commit();

            shapes.Add(shape, mesh);
            return mesh;
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
        string ground = "Ground";
        public void Render(CollisionObject body)
        {
            if (body.CollisionShape.ShapeType == BroadphaseNativeType.SoftBodyShape)
            {
                demo.SetBuffer(Matrix.Identity, Color.LightBlue);
                RenderSoftBody(SoftBody.Upcast(body));
            }
            else
            {
                Color color;
                if (ground.Equals(body.UserObject))
                {
                    color = Color.Green;
                }
                else
                {
                    color = body.ActivationState == ActivationState.ActiveTag ? Color.Orange : Color.OrangeRed;
                }
                demo.SetBuffer((body as RigidBody).MotionState.WorldTransform, color);
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
                    mesh = CreateBoxShape((BoxShape)shape);
                    break;
                case BroadphaseNativeType.CylinderShape:
                    mesh = CreateCylinderShape((CylinderShape)shape);
                    break;
                /*
                case BroadphaseNativeType.ConeShape:
                    mesh = CreateConeShape((ConeShape)shape);
                    break;
                case BroadphaseNativeType.ConvexHullShape:
                    mesh = CreateConvexHullShape((ConvexHullShape)shape);
                    break;
                case BroadphaseNativeType.GImpactShape:
                    mesh = CreateGImpactMeshShape((GImpactMeshShape)shape);
                    break;
                */
                case BroadphaseNativeType.SphereShape:
                    mesh = CreateSphere((SphereShape)shape);
                    break;
                /*
                case BroadphaseNativeType.Convex2DShape:
                    Render(((Convex2DShape)shape).ChildShape);
                    return;
                */
                case BroadphaseNativeType.CompoundShape:
                    CompoundShape compoundShape = (CompoundShape)shape;
                    foreach (CompoundShapeChild child in compoundShape.ChildList)
                    {
                        // do a pre-transform
                        demo.BodyTransform = child.Transform * demo.BodyTransform;
                        
                        Render(child.ChildShape);
                    }
                    return;
            }

            // If the shape has one subset, render it.
            if (mesh != null)
            {
                mesh.DrawSubset(0);
                return;
            }
            /*
            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.CapsuleShape:
                    mesh = CreateCapsuleShape((CapsuleShape)shape);
                    break;
                case BroadphaseNativeType.MultiSphereShape:
                    mesh = CreateMultiSphereShape((MultiSphereShape)shape);
                    break;
                case BroadphaseNativeType.StaticPlane:
                    mesh = CreateStaticPlaneShape((StaticPlaneShape)shape);
                    break;
            }
            */
            RenderComplexShape(shape, mesh);
        }

        public void RenderComplexShape(CollisionShape shape, Mesh mesh)
        {
            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.StaticPlane:
                    //RenderStaticPlaneShape(mesh);
                    break;
                case BroadphaseNativeType.CapsuleShape:
                    //RenderCapsuleShape(mesh);
                    break;
                case BroadphaseNativeType.MultiSphereShape:
                    //RenderMultiSphereShape((MultiSphereShape)shape, mesh);
                    break;
            }
        }
        /*
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
        */

        public void RenderSoftBody(SoftBody softBody)
        {
            AlignedFaceArray faces = softBody.Faces;
            int faceCount = faces.Count;

            if (faceCount > 0)
            {
                int vertexCount = faceCount * 3;
                bool index32 = vertexCount > 65536;

                InputElement[] elements = new InputElement[] {
                    new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0, InputClassification.PerVertexData, 0),
                    new InputElement("NORMAL", 0, Format.R32G32B32_Float, 12, 0, InputClassification.PerVertexData, 0)
                };
                Mesh mesh = new Mesh(device, elements, "POSITION", vertexCount, faceCount, index32 ? MeshFlags.Has32BitIndices : 0);

                MeshBuffer indexBuffer = mesh.GetIndexBuffer();
                SharpDX.DataStream iStream = indexBuffer.Map();
                int i;
                if (index32)
                {
                    for (i = 0; i < vertexCount; i++)
                        iStream.Write(i);
                }
                else
                {
                    for (i = 0; i < vertexCount; i++)
                        iStream.Write((short)i);
                }
                indexBuffer.Unmap();

                MeshBuffer vertexBuffer = mesh.GetVertexBuffer(0);
                SharpDX.DataStream vStream = vertexBuffer.Map();
                foreach (Face face in faces)
                {
                    NodePtrArray nodes = face.N;
                    Node n0 = nodes[0];
                    Node n1 = nodes[1];
                    Node n2 = nodes[2];
                    vStream.Write(n0.X);
                    vStream.Write(n0.Normal);
                    vStream.Write(n1.X);
                    vStream.Write(n1.Normal);
                    vStream.Write(n2.X);
                    vStream.Write(n2.Normal);
                }
                vertexBuffer.Unmap();

                mesh.Commit();

                mesh.DrawSubset(0);
                mesh.Dispose();
                vertexBuffer.Dispose();
                indexBuffer.Dispose();
            }
            else
            {
                AlignedTetraArray tetras = softBody.Tetras;
                int tetraCount = tetras.Count;

                if (tetraCount > 0)
                {
                    int vertexCount = tetraCount * 12;
                    bool index32 = vertexCount > 65536;

                    InputElement[] elements = new InputElement[] {
                        new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0, InputClassification.PerVertexData, 0),
                        new InputElement("NORMAL", 0, Format.R32G32B32_Float, 12, 0, InputClassification.PerVertexData, 0)
                    };
                    Mesh mesh = new Mesh(device, elements, "POSITION", vertexCount, tetraCount * 4, index32 ? MeshFlags.Has32BitIndices : 0);

                    MeshBuffer indexBuffer = mesh.GetIndexBuffer();
                    SharpDX.DataStream iStream = indexBuffer.Map();
                    int i;
                    if (index32)
                    {
                        for (i = 0; i < vertexCount; i++)
                            iStream.Write(i);
                    }
                    else
                    {
                        for (i = 0; i < vertexCount; i++)
                            iStream.Write((short)i);
                    }
                    indexBuffer.Unmap();

                    MeshBuffer vertexBuffer = mesh.GetVertexBuffer(0);
                    SharpDX.DataStream verts = vertexBuffer.Map();
                    foreach (Tetra t in tetras)
                    {
                        NodePtrArray nodes = t.Nodes;
                        Vector3 v0 = nodes[0].X;
                        Vector3 v1 = nodes[1].X;
                        Vector3 v2 = nodes[2].X;
                        Vector3 v3 = nodes[3].X;

                        Vector3 normal0 = -Vector3.Cross(v1 - v0, v2 - v0);
                        Vector3 normal1 = Vector3.Cross(v1 - v0, v3 - v0);
                        Vector3 normal2 = Vector3.Cross(v2 - v1, v3 - v1);
                        Vector3 normal3 = Vector3.Cross(v0 - v2, v3 - v2);

                        verts.Write(v0);
                        verts.Write(normal0);
                        verts.Write(v1);
                        verts.Write(normal0);
                        verts.Write(v2);
                        verts.Write(normal0);

                        verts.Write(v0);
                        verts.Write(normal1);
                        verts.Write(v1);
                        verts.Write(normal1);
                        verts.Write(v3);
                        verts.Write(normal1);
                        
                        verts.Write(v1);
                        verts.Write(normal2);
                        verts.Write(v2);
                        verts.Write(normal2);
                        verts.Write(v3);
                        verts.Write(normal2);

                        verts.Write(v2);
                        verts.Write(normal3);
                        verts.Write(v0);
                        verts.Write(normal3);
                        verts.Write(v3);
                        verts.Write(normal3);
                    }
                    vertexBuffer.Unmap();

                    mesh.Commit();

                    mesh.DrawSubset(0);
                    mesh.Dispose();
                    vertexBuffer.Dispose();
                    indexBuffer.Dispose();
                }
                else if (softBody.Links.Count > 0)
                {
                    /*
                    AlignedLinkArray links = softBody.Links;
                    int linkCount = links.Count;
                    int linkColor = System.Drawing.Color.Black.ToArgb();

                    device.SetRenderState(RenderState.Lighting, false);
                    device.SetTransform(TransformState.World, Matrix.Identity);
                    device.VertexFormat = PositionColored.FVF;

                    PositionColored[] linkArray = new PositionColored[linkCount * 2];

                    for (int i = 0; i < linkCount; i++)
                    {
                        Link link = links[i];
                        linkArray[i * 2] = new PositionColored(link.Nodes[0].X, linkColor);
                        linkArray[i * 2 + 1] = new PositionColored(link.Nodes[1].X, linkColor);
                    }
                    device.DrawUserPrimitives(PrimitiveType.LineList, links.Count, linkArray);

                    device.SetRenderState(RenderState.Lighting, true);
                    */
                }
            }
        }
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
         * */
    }
}
