using System;
using BulletSharp;
using DemoFramework;
using System.Windows.Forms;

namespace ConcaveRaycastDemo
{
    class ConcaveRaycastDemo : Demo
    {
        Vector3 eye = new Vector3(0, 15, 60);
        Vector3 target = new Vector3(-5, 5, 0);

        DebugDrawModes debugMode = DebugDrawModes.DrawWireframe;

        const float TRIANGLE_SIZE = 8.0f;
        const int NUM_VERTS_X = 30;
        const int NUM_VERTS_Y = 30;
        const float waveHeight = 5.0f;
        static float offset = 0.0f;
        bool animatedMesh = false;

        TriangleIndexVertexArray indexVertexArrays;
        BvhTriangleMeshShape groundShape;

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - Concave Raycast Demo");
            Graphics.SetInfoText("Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                //"F11 - Toggle fullscreen\n" +
                "Space - Shoot box");

            DebugDrawMode = debugMode;

            const int totalVerts = NUM_VERTS_X * NUM_VERTS_Y;
            const int totalTriangles = 2 * (NUM_VERTS_X - 1) * (NUM_VERTS_Y - 1);
            indexVertexArrays = new TriangleIndexVertexArray();

            IndexedMesh mesh = new IndexedMesh();
            mesh.Allocate(totalVerts, Vector3.SizeInBytes, totalTriangles * 3, 3 * sizeof(int));
            DataStream indices = mesh.LockIndices();
            for (int i = 0; i < NUM_VERTS_X - 1; i++)
            {
                for (int j = 0; j < NUM_VERTS_Y - 1; j++)
                {
                    indices.Write(j * NUM_VERTS_X + i);
                    indices.Write(j * NUM_VERTS_X + i + 1);
                    indices.Write((j + 1) * NUM_VERTS_X + i + 1);

                    indices.Write(j * NUM_VERTS_X + i);
                    indices.Write((j + 1) * NUM_VERTS_X + i + 1);
                    indices.Write((j + 1) * NUM_VERTS_X + i);
                }
            }
            indices.Dispose();

            indexVertexArrays.AddIndexedMesh(mesh);
        }

        void SetVertexPositions(float waveheight, float offset)
        {
            BulletSharp.DataStream vertexBuffer, indexBuffer;
            int numVerts, numFaces;
            PhyScalarType vertsType, indicesType;
            int vertexStride, indexStride;
            indexVertexArrays.GetLockedVertexIndexData(out vertexBuffer, out numVerts, out vertsType, out vertexStride,
                out indexBuffer, out indexStride, out numFaces, out indicesType);

            for (int i = 0; i < NUM_VERTS_X; i++)
            {
                for (int j = 0; j < NUM_VERTS_Y; j++)
                {
                    vertexBuffer.Write((i - NUM_VERTS_X * 0.5f) * TRIANGLE_SIZE);
                    vertexBuffer.Write(waveheight * (float)Math.Sin((float)i + offset) * (float)Math.Cos((float)j + offset));
                    vertexBuffer.Write((j - NUM_VERTS_Y * 0.5f) * TRIANGLE_SIZE);
                }
            }

            vertexBuffer.Dispose();
            indexBuffer.Dispose();
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Vector3 worldMin = new Vector3(-1000,-1000,-1000);
	        Vector3 worldMax = new Vector3(1000,1000,1000);
	        Broadphase = new AxisSweep3(worldMin,worldMax);
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.SolverInfo.SplitImpulse = 1;
            World.Gravity = new Vector3(0, -10, 0);
            IsDebugDrawEnabled = true;


            CollisionShape colShape = new BoxShape(1);
            CollisionShapes.Add(colShape);

            for (int i = 0; i < 10; i++)
            {
                //CollisionShape colShape = new CapsuleShape(0.5f,2.0f);//boxShape = new SphereShape(1.0f);
                Matrix startTransform = Matrix.Translation(2 * i, 10, 1);
                LocalCreateRigidBody(1.0f, startTransform, colShape);
            }


            SetVertexPositions(waveHeight, 0.0f);

            bool useQuantizedAabbCompression = true;
            groundShape = new BvhTriangleMeshShape(indexVertexArrays, useQuantizedAabbCompression);
            CollisionShapes.Add(groundShape);

            RigidBody staticBody = LocalCreateRigidBody(0.0f, Matrix.Identity, groundShape);
            staticBody.CollisionFlags |= CollisionFlags.StaticObject;
        }

        public override void OnUpdate()
        {
            if (animatedMesh)
            {
                offset += FrameDelta;
                SetVertexPositions(waveHeight, offset);
                Graphics.MeshFactory.RemoveShape(groundShape);
            }
            base.OnUpdate();
        }

        public override void OnHandleInput()
        {
            if (Input.KeysPressed.Contains(Keys.G))
            {
                animatedMesh = !animatedMesh;
            }
            base.OnHandleInput();
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new ConcaveRaycastDemo())
            {
                LibraryManager.Initialize(demo);
            }
        }
    }
}
