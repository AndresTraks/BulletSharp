using BulletSharp;

namespace BulletSharpTest
{
    class TriangleMeshTest : TestContext
    {
        DiscreteDynamicsWorld world;

        public override void Run()
        {
            var conf = new DefaultCollisionConfiguration();
            var dispatcher = new CollisionDispatcher(conf);
            var broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));
            world = new DiscreteDynamicsWorld(dispatcher, broadphase, null, conf);

            var indexVertexArray = new TriangleIndexVertexArray(TorusMesh.Indices, TorusMesh.Vertices);
            foreach (var indexedMesh in indexVertexArray.IndexedMeshArray)
            {
                indexedMesh.ToString();
            }
            AddToDisposeQueue(indexVertexArray);

            var gImpactMesh = new GImpactMeshShape(indexVertexArray);
            Vector3 aabbMin, aabbMax;
            gImpactMesh.GetAabb(Matrix.Identity, out aabbMin, out aabbMax);
            CreateBody(1.0f, gImpactMesh, Vector3.Zero);
            AddToDisposeQueue(gImpactMesh);
            gImpactMesh = null;

            var triangleMesh = new BvhTriangleMeshShape(indexVertexArray, true);
            triangleMesh.CalculateLocalInertia(1.0f);
            triangleMesh.GetAabb(Matrix.Identity, out aabbMin, out aabbMax);
            CreateBody(1.0f, triangleMesh, Vector3.Zero);
            AddToDisposeQueue(triangleMesh);
            triangleMesh = null;

            indexVertexArray = null;


            AddToDisposeQueue(conf);
            AddToDisposeQueue(dispatcher);
            AddToDisposeQueue(broadphase);
            AddToDisposeQueue(world);

            //conf.Dispose();
            conf = null;
            //dispatcher.Dispose();
            dispatcher = null;
            //broadphase.Dispose();
            broadphase = null;
            for (int i = 0; i < 600; i++)
            {
                world.StepSimulation(1.0f / 60.0f);
            }
            world.Dispose();
            world = null;

            ForceGC();
            TestWeakRefs();
            ClearRefs();
        }

        RigidBody CreateBody(float mass, CollisionShape shape, Vector3 offset)
        {
            var constInfo = new RigidBodyConstructionInfo(mass, new DefaultMotionState(), shape, Vector3.Zero);
            if (mass != 0.0f)
            {
                constInfo.LocalInertia = constInfo.CollisionShape.CalculateLocalInertia(mass);
            }
            var collisionObject = new RigidBody(constInfo);
            collisionObject.Translate(offset);
            world.AddRigidBody(collisionObject);

            AddToDisposeQueue(constInfo);
            AddToDisposeQueue(constInfo.MotionState);
            AddToDisposeQueue(collisionObject);
            AddToDisposeQueue(shape);

            //collisionObject.OnDisposing += onDisposing;
            //collisionObject.OnDisposed += onDisposed;

            return collisionObject;
        }
    }
}
