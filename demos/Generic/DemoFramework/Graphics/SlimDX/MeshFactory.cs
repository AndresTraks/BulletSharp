using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using BulletSharp;
using BulletSharp.SoftBody;
using SlimDX.Direct3D9;
using DataStream = SlimDX.DataStream;
using Matrix = SlimDX.Matrix;

namespace DemoFramework.SlimDX
{
    // This class creates graphical objects (boxes, cones, cylinders, spheres) on the fly.
    public class MeshFactory : DemoFramework.MeshFactory
    {
        Device device;
        Dictionary<CollisionShape, Mesh> shapes = new Dictionary<CollisionShape, Mesh>();
        Dictionary<CollisionShape, Mesh> planeShapes = new Dictionary<CollisionShape, Mesh>(); // these are rendered differently
        Effect planeShader;

        public MeshFactory(SlimDXGraphics graphics)
        {
            this.device = graphics.Device;
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

            foreach (Mesh mesh in planeShapes.Values)
            {
                mesh.Dispose();
            }
            planeShapes.Clear();

            if (planeShader != null)
                planeShader.Dispose();
        }

        public override void RemoveShape(CollisionShape shape)
        {
            if (shapes.ContainsKey(shape))
            {
                shapes[shape].Dispose();
                shapes.Remove(shape);
            }
        }

        Mesh CreateShape(CollisionShape shape)
        {
            uint[] indices;
            BulletSharp.Vector3[] vertices = CreateShape(shape, out indices);

            int vertexCount = vertices.Length / 2;
            int indexCount = (indices != null) ? indices.Length : vertexCount;
            bool index32 = indexCount > 65536;

            Mesh mesh = new Mesh(device, indexCount / 3, vertexCount,
                MeshFlags.SystemMemory | (index32 ? MeshFlags.Use32Bit : 0), VertexFormat.Position | VertexFormat.Normal);

            DataStream vertexBuffer = mesh.LockVertexBuffer(LockFlags.Discard);
            vertexBuffer.WriteRange(vertices);
            mesh.UnlockVertexBuffer();

            DataStream indexBuffer = mesh.LockIndexBuffer(LockFlags.Discard);
            if (index32)
            {
                if (indices == null)
                {
                    indices = new uint[indexCount];
                    uint i = 0;
                    while (i < indexCount)
                    {
                        indices[i] = i;
                        i++;
                    }
                }
                indexBuffer.WriteRange(indices);
            }
            else
            {
                ushort[] indices_s;
                if (indices == null)
                {
                    indices_s = new ushort[indexCount];
                    ushort i = 0;
                    while (i < indexCount)
                    {
                        indices_s[i] = i;
                        i++;
                    }
                }
                else
                {
                    indices_s = CompactIndexBuffer(indices);
                }
                indexBuffer.WriteRange(indices_s);
            }
            mesh.UnlockIndexBuffer();

            shapes.Add(shape, mesh);
            return mesh;
        }

        Mesh CreateConeShape(ConeShape shape)
        {
            Mesh mesh = Mesh.CreateCylinder(device, 0, shape.Radius, shape.Height, 16, 1);
            shapes.Add(shape, mesh);
            return mesh;
        }

        Mesh CreateStaticPlaneShape(StaticPlaneShape shape)
        {
            // Load shader
            if (planeShader == null)
            {
                Assembly assembly = Assembly.GetExecutingAssembly();
                Stream shaderStream = assembly.GetManifestResourceStream("DemoFramework.SlimDX.checker_shader.fx");

                planeShader = Effect.FromStream(device, shaderStream, ShaderFlags.None);
            }

            Mesh mesh = CreateShape(shape);
            shapes.Remove(shape);
            planeShapes.Add(shape, mesh);

            return mesh;
        }

        public void Render(CollisionObject body)
        {
            switch (body.CollisionShape.ShapeType)
            {
                case BroadphaseNativeType.SoftBodyShape:
                    device.SetTransform(TransformState.World, Matrix.Identity);
                    RenderSoftBody(body as SoftBody);
                    break;
                case BroadphaseNativeType.CompoundShape:
                    CompoundShape compoundShape = body.CollisionShape as CompoundShape;
                    //if (compoundShape.NumChildShapes == 0)
                    //    return;
                    foreach (CompoundShapeChild child in compoundShape.ChildList)
                    {
                        device.SetTransform(TransformState.World,
                            MathHelper.Convert(child.Transform) * MathHelper.Convert(body.WorldTransform));
                        Render(child.ChildShape);
                    }
                    break;
                default:
                    device.SetTransform(TransformState.World, MathHelper.Convert(body.WorldTransform));
                    Render(body.CollisionShape);
                    break;
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

            if (planeShapes.TryGetValue(shape, out mesh))
            {
                RenderStaticPlaneShape(mesh);
                return;
            }

            // Create the graphics mesh or go to child shapes.
            switch (shape.ShapeType)
            {
                case BroadphaseNativeType.ConeShape:
                    mesh = CreateConeShape(shape as ConeShape);
                    break;
                case BroadphaseNativeType.StaticPlaneShape:
                    mesh = CreateStaticPlaneShape(shape as StaticPlaneShape);
                    RenderStaticPlaneShape(mesh);
                    return;
                default:
                    mesh = CreateShape(shape);
                    break;
            }

            mesh.DrawSubset(0);
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

        void PlaneSpace1(BulletSharp.Vector3 n, out BulletSharp.Vector3 p, out BulletSharp.Vector3 q)
        {
            if (Math.Abs(n[2]) > (Math.Sqrt(2) / 2))
            {
                // choose p in y-z plane
                float a = n[1] * n[1] + n[2] * n[2];
                float k = 1.0f / (float)Math.Sqrt(a);
                p = new BulletSharp.Vector3(0, -n[2] * k, n[1] * k);
                // set q = n x p
                q = BulletSharp.Vector3.Cross(n, p);
            }
            else
            {
                // choose p in x-y plane
                float a = n[0] * n[0] + n[1] * n[1];
                float k = 1.0f / (float)Math.Sqrt(a);
                p = new BulletSharp.Vector3(-n[1] * k, n[0] * k, 0);
                // set q = n x p
                q = BulletSharp.Vector3.Cross(n, p);
            }
        }

        public void RenderSoftBody(SoftBody softBody)
        {
            Cull cullMode = device.GetRenderState<Cull>(RenderState.CullMode);
            device.SetRenderState(RenderState.CullMode, Cull.None);

            AlignedFaceArray faces = softBody.Faces;
            int faceCount = faces.Count;

            if (faceCount > 0)
            {
                PositionedNormal[] vectors = new PositionedNormal[faceCount * 6];
                int v = 0;

                int i;
                for (i = 0; i < faceCount; i++)
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

                device.VertexFormat = VertexFormat.PositionNormal;
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
                        BulletSharp.Vector3 v0 = nodes[0].X;
                        BulletSharp.Vector3 v1 = nodes[1].X;
                        BulletSharp.Vector3 v2 = nodes[2].X;
                        BulletSharp.Vector3 v3 = nodes[3].X;
                        BulletSharp.Vector3 v10 = v1 - v0;
                        BulletSharp.Vector3 v02 = v0 - v2;

                        BulletSharp.Vector3 normal = BulletSharp.Vector3.Cross(v10, v02);
                        normal.Normalize();
                        vectors[v].Position = v0;
                        vectors[v].Normal = normal;
                        vectors[v + 1].Position = v1;
                        vectors[v + 1].Normal = normal;
                        vectors[v + 2].Position = v2;
                        vectors[v + 2].Normal = normal;

                        normal = BulletSharp.Vector3.Cross(v10, v3 - v0);
                        normal.Normalize();
                        vectors[v + 3].Position = v0;
                        vectors[v + 3].Normal = normal;
                        vectors[v + 4].Position = v1;
                        vectors[v + 4].Normal = normal;
                        vectors[v + 5].Position = v3;
                        vectors[v + 5].Normal = normal;

                        normal = BulletSharp.Vector3.Cross(v2 - v1, v3 - v1);
                        normal.Normalize();
                        vectors[v + 6].Position = v1;
                        vectors[v + 6].Normal = normal;
                        vectors[v + 7].Position = v2;
                        vectors[v + 7].Normal = normal;
                        vectors[v + 8].Position = v3;
                        vectors[v + 8].Normal = normal;

                        normal = BulletSharp.Vector3.Cross(v02, v3 - v2);
                        normal.Normalize();
                        vectors[v + 9].Position = v2;
                        vectors[v + 9].Normal = normal;
                        vectors[v + 10].Position = v0;
                        vectors[v + 10].Normal = normal;
                        vectors[v + 11].Position = v3;
                        vectors[v + 11].Normal = normal;
                        v += 12;
                    }
                    device.VertexFormat = VertexFormat.PositionNormal;
                    device.DrawUserPrimitives(PrimitiveType.TriangleList, tetraCount * 4, vectors);
                }
                else if (softBody.Links.Count > 0)
                {
                    AlignedLinkArray links = softBody.Links;
                    int linkCount = links.Count;
                    int linkColor = System.Drawing.Color.Black.ToArgb();

                    device.VertexFormat = VertexFormat.Position | VertexFormat.Diffuse;

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

            device.SetRenderState(RenderState.CullMode, cullMode);
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

                DataStream indices = mesh.LockIndexBuffer(LockFlags.Discard);
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

                DataStream verts = mesh.LockVertexBuffer(LockFlags.Discard);
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
