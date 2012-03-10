using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using BulletSharp;
using BulletSharp.SoftBody;
using Microsoft.Xna.Framework.Graphics;
using Color = Microsoft.Xna.Framework.Color;

namespace DemoFramework.Xna
{
    public struct InstanceData
    {
        public Microsoft.Xna.Framework.Matrix WorldTransform;
        public Microsoft.Xna.Framework.Vector3 Color;

        public static readonly int SizeInBytes = Marshal.SizeOf(typeof(InstanceData));
    }

    // Contains the geometry buffers and information of all instances of a particular shape.
    public class ShapeData : System.IDisposable
    {
        public VertexBuffer VertexBuffer;
        public int VertexCount;

        public IndexBuffer IndexBuffer;
        public int IndexCount;

        //public Buffer InstanceDataBuffer;
        public List<InstanceData> InstanceDataList;

        public PrimitiveType PrimitiveType;
        //public VertexBufferBinding[] BufferBindings;

        public ShapeData()
        {
            InstanceDataList = new List<InstanceData>();
            PrimitiveType = PrimitiveType.TriangleList;
            //BufferBindings = new VertexBufferBinding[2];
        }

        static readonly VertexDeclaration vertexDecl = new VertexDeclaration(new VertexElement[] {
            new VertexElement(0, VertexElementFormat.Vector3, VertexElementUsage.Position, 0),
            new VertexElement(12, VertexElementFormat.Vector3, VertexElementUsage.Normal, 0)
        });

        public void SetVertexBuffer(GraphicsDevice device, Vector3[] vectors)
        {
            VertexCount = vectors.Length;
            VertexBuffer = new VertexBuffer(device, vertexDecl, VertexCount, BufferUsage.None);
            VertexBuffer.SetData(vectors);
            //BufferBindings[0] = new VertexBufferBinding(VertexBuffer, 0, 0);
        }

        public void SetVertexNormalBuffer(GraphicsDevice device, Vector3[] vectors)
        {
            VertexCount = vectors.Length / 2;
            VertexBuffer = new VertexBuffer(device, vertexDecl, VertexCount, BufferUsage.None);
            VertexBuffer.SetData(vectors);
            //BufferBindings[0] = new VertexBufferBinding(VertexBuffer, 0, 0);
        }

        // Used with soft bodies
        public void SetDynamicVertexBuffer(GraphicsDevice device, Vector3[] vectors)
        {
            if (VertexBuffer != null && VertexCount == vectors.Length)
            {
                // Update existing buffer
                VertexBuffer.SetData(vectors);
            }
            else
            {
                // Create new buffer
                if (VertexBuffer != null)
                    VertexBuffer.Dispose();

                SetVertexBuffer(device, vectors);
            }
        }

        // Used with soft bodies
        public void SetDynamicVertexNormalBuffer(GraphicsDevice device, Vector3[] vectors)
        {
            if (VertexBuffer != null && VertexCount * 2 == vectors.Length)
            {
                // Update existing buffer
                VertexBuffer.SetData(vectors);
            }
            else
            {
                // Create new buffer
                if (VertexBuffer != null)
                    VertexBuffer.Dispose();

                SetVertexNormalBuffer(device, vectors);
            }
        }

        public void SetIndexBuffer(GraphicsDevice device, ushort[] indices)
        {
            IndexBuffer = new IndexBuffer(device, typeof(ushort), indices.Length, BufferUsage.None);
            IndexBuffer.SetData(indices);
        }

        public void SetIndexBuffer(GraphicsDevice device, uint[] indices)
        {
            IndexBuffer = new IndexBuffer(device, typeof(uint), indices.Length, BufferUsage.None);
            IndexBuffer.SetData(indices);
        }

        public void Dispose()
        {
            if (VertexBuffer != null)
            {
                VertexBuffer.Dispose();
                VertexBuffer = null;
            }
            if (IndexBuffer != null)
            {
                IndexBuffer.Dispose();
                IndexBuffer = null;
            }
            /*
            if (InstanceDataBuffer != null)
            {
                InstanceDataBuffer.Dispose();
                InstanceDataBuffer = null;
            }
            */
        }
    }

    // This class creates graphical objects (boxes, cones, cylinders, spheres) on the fly.
    public class MeshFactory : System.IDisposable
    {
        Demo demo;
        GraphicsDevice device;
        Dictionary<CollisionShape, ShapeData> shapes = new Dictionary<CollisionShape, ShapeData>();
        List<CollisionShape> removeList = new List<CollisionShape>();
        Effect planeShader;

        Microsoft.Xna.Framework.Vector3 groundColor = Color.Green.ToVector3();
        Microsoft.Xna.Framework.Vector3 activeColor = Color.Orange.ToVector3();
        Microsoft.Xna.Framework.Vector3 passiveColor = Color.Red.ToVector3();
        Microsoft.Xna.Framework.Vector3 softBodyColor = Color.LightBlue.ToVector3();
        Microsoft.Xna.Framework.Vector3 linkColor = Color.Black.ToVector3();

        public MeshFactory(XnaGraphics graphics)
        {
            this.demo = graphics.Demo;
            this.device = graphics.Device;
        }

        public void Dispose()
        {
            shapes.Clear();

            if (planeShader != null)
                planeShader.Dispose();
        }

        ShapeData CreateShape(CollisionShape shape)
        {
            ShapeData shapeData = new ShapeData();
            uint[] indices;
            Vector3[] vertices = ShapeGenerator.CreateShape(shape, out indices);
            shapeData.SetVertexNormalBuffer(device, vertices);

            if (indices != null)
            {
                shapeData.IndexCount = indices.Length;
                ushort[] indices_s = ShapeGenerator.CompactIndexBuffer(indices);
                if (indices_s != null)
                {
                    shapeData.SetIndexBuffer(device, indices_s);
                }
                else
                {
                    shapeData.SetIndexBuffer(device, indices);
                }
            }

            return shapeData;
        }

        public ShapeData CreateSoftBody()
        {
            // Soft body geometry is recreated each frame. Nothing to do here.
            return new ShapeData();
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
                //instanceDataDesc.SizeInBytes = InstanceData.SizeInBytes;
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
                        WorldTransform = MathHelper.Convert(transform),
                        Color = softBodyColor
                    });
                    break;
                default:
                    InitShapeData(shape).InstanceDataList.Add(new InstanceData()
                    {
                        WorldTransform = MathHelper.Convert(transform),
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

        public void RenderInstanced(BasicEffect effect)
        {
            EffectPass pass = effect.CurrentTechnique.Passes[0];

            foreach (ShapeData s in shapes.Values)
            {
                device.SetVertexBuffer(s.VertexBuffer);
                foreach (InstanceData instance in s.InstanceDataList)
                {
                    effect.DiffuseColor = instance.Color;
                    effect.World = instance.WorldTransform;
                    pass.Apply();

                    if (s.IndexBuffer != null)
                    {
                        device.Indices = s.IndexBuffer;
                        device.DrawIndexedPrimitives(s.PrimitiveType, 0, 0,
                            s.VertexCount, 0, s.IndexCount / 3);
                    }
                    else
                    {
                        device.DrawPrimitives(s.PrimitiveType, 0, s.VertexCount / 3);
                    }
                }
            }
            device.SetVertexBuffer(null);
        }

        public void UpdateSoftBody(SoftBody softBody, ShapeData shapeData)
        {
            AlignedFaceArray faces = softBody.Faces;

            if (faces.Count != 0)
            {
                Vector3[] vectors = new Vector3[3 * faces.Count * 2];
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

                shapeData.SetDynamicVertexNormalBuffer(device, vectors);
            }
            else
            {
                AlignedTetraArray tetras = softBody.Tetras;
                int tetraCount = tetras.Count;

                if (tetraCount != 0)
                {
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

                    shapeData.SetDynamicVertexNormalBuffer(device, vectors);
                }
                else if (softBody.Links.Count != 0)
                {
                    AlignedLinkArray links = softBody.Links;
                    int linkCount = links.Count;

                    Vector3[] vectors = new Vector3[linkCount * 4];

                    for (int i = 0; i < linkCount; i++)
                    {
                        NodePtrArray nodes = links[i].Nodes;
                        nodes[0].GetX(out vectors[i * 4]);
                        nodes[1].GetX(out vectors[i * 4 + 2]);
                    }

                    shapeData.PrimitiveType = PrimitiveType.LineList;
                    shapeData.SetDynamicVertexBuffer(device, vectors);
                }
                else
                {
                    throw new NotImplementedException();
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
        */
    }
}
