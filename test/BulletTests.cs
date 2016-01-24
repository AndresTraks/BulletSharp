using BulletSharp;
using System;

namespace BulletSharpTest
{
    class BulletTests : TestContext
    {
        DiscreteDynamicsWorld world;

        public override void Run()
        {
            TestGCCollection();
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

            collisionObject.OnDisposing += onDisposing;
            collisionObject.OnDisposed += onDisposed;

            return collisionObject;
        }

        void TestContactTest(RigidBody testBody, RigidBody testBody2)
        {
            object context = "your context";
            ContactSensorCallback contactCallback = new ContactSensorCallback(testBody, context);
            world.ContactTest(testBody, contactCallback);

            testBody.CollisionFlags |= CollisionFlags.CustomMaterialCallback;
            testBody2.CollisionFlags |= CollisionFlags.CustomMaterialCallback;
            world.ContactPairTest(testBody, testBody2, contactCallback);
            testBody.CollisionFlags &= ~CollisionFlags.CustomMaterialCallback;
            testBody2.CollisionFlags &= ~CollisionFlags.CustomMaterialCallback;

            AddToDisposeQueue(contactCallback);
        }

        void TestGCCollection()
        {
            var conf = new DefaultCollisionConfiguration();

            var dispatcher = new CollisionDispatcher(conf);
            var broadphase = new DbvtBroadphase();
            //var broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));
            world = new DiscreteDynamicsWorld(dispatcher, broadphase, null, conf);
            world.Gravity = new Vector3(0, -10, 0);
            dispatcher.NearCallback = DispatcherNearCallback;

            CreateBody(0.0f, new BoxShape(50, 1, 50), Vector3.Zero);
            var dynamicObject = CreateBody(10.0f, new SphereShape(1.0f), new Vector3(2, 2, 0));
            var dynamicObject2 = CreateBody(1.0f, new SphereShape(1.0f), new Vector3(0, 2, 0));

            var ghostPairCallback = new GhostPairCallback();
            broadphase.OverlappingPairCache.SetInternalGhostPairCallback(ghostPairCallback);
            AddToDisposeQueue(ghostPairCallback);
            ghostPairCallback = null;
            var ghostObject = new PairCachingGhostObject();
            ghostObject.CollisionShape = new BoxShape(2);
            ghostObject.WorldTransform = Matrix.Translation(2, 2, 0);
            world.AddCollisionObject(ghostObject);

            var trimesh = new TriangleMesh();
            Vector3 v0 = new Vector3(0, 0, 0);
            Vector3 v1 = new Vector3(1, 0, 0);
            Vector3 v2 = new Vector3(0, 1, 0);
            Vector3 v3 = new Vector3(1, 1, 0);
            trimesh.AddTriangle(v0, v1, v2);
            trimesh.AddTriangle(v1, v3, v2);
            var triangleMeshShape = new BvhTriangleMeshShape(trimesh, false);
            var triMeshObject = CreateBody(0, triangleMeshShape, new Vector3(20, 0, 20));
            AddToDisposeQueue(triangleMeshShape);
            AddToDisposeQueue(trimesh);
            AddToDisposeQueue(triMeshObject);
            triangleMeshShape = null;
            trimesh = null;

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
            world.DebugDrawer = new DebugDrawTest();
            AddToDisposeQueue(world.DebugDrawer);
            world.SetInternalTickCallback(WorldPreTickCallback);
            for (int i = 0; i < 600; i++)
            {
                world.StepSimulation(1.0f / 60.0f);
            }

            world.DispatchInfo.DebugDraw = new DebugDrawTest2();
            AddToDisposeQueue(world.DispatchInfo.DebugDraw);
            world.DispatchInfo.DebugDraw = world.DispatchInfo.DebugDraw;
            AddToDisposeQueue(world.DispatchInfo.DebugDraw);
            world.DispatchInfo.DebugDraw = null;
            world.DebugDrawer = null;
            world.DebugDrawer = new DebugDrawTest2();
            world.StepSimulation(1.0f / 60.0f);
            world.DebugDrawWorld();
            AddToDisposeQueue(world.DispatchInfo.DebugDraw);

            world.DebugDrawer = new DebugDrawTest();
            world.DebugDrawWorld();
            AddToDisposeQueue(world.DebugDrawer);
            world.DebugDrawer = null;

            TestContactTest(dynamicObject, dynamicObject2);
            TestGhostObjectPairs(ghostObject);
            TestRayCast(dynamicObject);
            TestTriangleMeshRayCast(triMeshObject);
            dynamicObject = null;
            dynamicObject2 = null;
            triMeshObject = null;

            //world.SetInternalTickCallback(null);
            world.Dispose();
            world = null;

            ForceGC();
            TestWeakRefs();
            ClearRefs();
        }

        void TestGhostObjectPairs(PairCachingGhostObject ghostObject)
        {
            AlignedManifoldArray manifoldArray = new AlignedManifoldArray();
            AlignedBroadphasePairArray pairArray = ghostObject.OverlappingPairCache.OverlappingPairArray;
            int numPairs = pairArray.Count;

            for (int i = 0; i < numPairs; i++)
            {
                manifoldArray.Clear();

                BroadphasePair pair = pairArray[i];

                //unless we manually perform collision detection on this pair, the contacts are in the dynamics world paircache:
                BroadphasePair collisionPair = world.PairCache.FindPair(pair.Proxy0, pair.Proxy1);
                if (collisionPair == null)
                    continue;

                if (collisionPair.Algorithm != null)
                    collisionPair.Algorithm.GetAllContactManifolds(manifoldArray);

                for (int j = 0; j < manifoldArray.Count; j++)
                {
                    PersistentManifold manifold = manifoldArray[j];
                    float directionSign = manifold.Body0 == ghostObject ? -1.0f : 1.0f;
                    for (int p = 0; p < manifold.NumContacts; p++)
                    {
                        ManifoldPoint pt = manifold.GetContactPoint(p);
                        if (pt.Distance < 0.0f)
                        {
                            Vector3 ptA = pt.PositionWorldOnA;
                            Vector3 ptB = pt.PositionWorldOnB;
                            Vector3 normalOnB = pt.NormalWorldOnB;
                            /// work here
                        }
                    }
                }
            }
        }

        void TestManifoldPoints()
        {
            int numManifolds = world.Dispatcher.NumManifolds;
            for (int i = 0; i < numManifolds; i++)
            {
                PersistentManifold contactManifold = world.Dispatcher.GetManifoldByIndexInternal(i);
                CollisionObject obA = contactManifold.Body0 as CollisionObject;
                CollisionObject obB = contactManifold.Body1 as CollisionObject;

                int numContacts = contactManifold.NumContacts;
                for (int j = 0; j < numContacts; j++)
                {
                    ManifoldPoint pt = contactManifold.GetContactPoint(j);
                    if (pt.Distance < 0.0f)
                    {
                        Vector3 ptA = pt.PositionWorldOnA;
                        Vector3 ptB = pt.PositionWorldOnB;
                        Vector3 normalOnB = pt.NormalWorldOnB;
                    }
                }
            }
        }

        void TestRayCast(CollisionObject testObject)
        {
            Vector3 rayFromWorld = testObject.WorldTransform.Origin + new Vector3(0, 0, -2);
            Vector3 rayToWorld = testObject.WorldTransform.Origin + new Vector3(0, 0, 2);
            var rayCallback = new CustomRayCallback(ref rayFromWorld, ref rayToWorld);
            world.RayTest(ref rayFromWorld, ref rayToWorld, rayCallback);
            if (rayCallback.CollisionObject != testObject)
            {
                Console.WriteLine("Raycast FAILED!");
            }

            AddToDisposeQueue(rayCallback);
        }

        void TestTriangleMeshRayCast(RigidBody triMeshObject)
        {
            Vector3 rayFromWorld = triMeshObject.WorldTransform.Origin + new Vector3(0, 0, -2);
            Vector3 rayToWorld = triMeshObject.WorldTransform.Origin + new Vector3(0, 0, 2);
            var cb = new TriangleMeshRayCastCallback(ref rayFromWorld, ref rayToWorld);
            world.RayTest(ref rayFromWorld, ref rayToWorld, cb);
            if (!cb.Success)
            {
                Console.WriteLine("Triangle mesh raycast fail!");
            }
        }

        void onDisposed(object sender, EventArgs e)
        {
            //Console.WriteLine("OnDisposed: " + sender.ToString());
        }

        void onDisposing(object sender, EventArgs e)
        {
            //Console.WriteLine("OnDisposing: " + sender.ToString());
        }

#if BT_USE_DOUBLE_PRECISION
        void WorldPreTickCallback(DynamicsWorld world2, double timeStep)
#else
        void WorldPreTickCallback(DynamicsWorld world2, float timeStep)
#endif
        {
            TestManifoldPoints();

            //Console.WriteLine("WorldPreTickCallback");
            if (!object.ReferenceEquals(world, world2))
            {
                Console.WriteLine("WorldPreTickCallback: World reference lost!");
            }
        }

        void DispatcherNearCallback(BroadphasePair collisionPair, CollisionDispatcher dispatcher,
            DispatcherInfo dispatchInfo)
        {
            //AddToDisposeQueue(dispatchInfo.DebugDraw);
            TestManifoldPoints();
            //Console.WriteLine("DispatcherNearCallback");
        }
    }

    class CustomRayCallback : ClosestRayResultCallback
    {
        public CustomRayCallback(ref Vector3 rayFrom, ref Vector3 rayTo)
            : base(ref rayFrom, ref rayTo)
        {
        }

#if BT_USE_DOUBLE_PRECISION
        public override double AddSingleResult(LocalRayResult rayResult, bool normalInWorldSpace)
#else
        public override float AddSingleResult(LocalRayResult rayResult, bool normalInWorldSpace)
#endif
        {
            return base.AddSingleResult(rayResult, normalInWorldSpace);
        }
    }

    public class TriangleMeshRayCastCallback : ClosestRayResultCallback
    {
        public int TriangleIndex { get; private set; }
        public bool Success { get; private set; }

        public TriangleMeshRayCastCallback(ref Vector3 from, ref Vector3 to)
            : base(ref from, ref to)
        {
        }

#if BT_USE_DOUBLE_PRECISION
        public override double AddSingleResult(LocalRayResult rayResult, bool normalInWorldSpace)
#else
        public override float AddSingleResult(LocalRayResult rayResult, bool normalInWorldSpace)
#endif
        {
            if (rayResult.LocalShapeInfo != null)
            {
                Success = true;
                TriangleIndex = rayResult.LocalShapeInfo.TriangleIndex;
            }
            return base.AddSingleResult(rayResult, normalInWorldSpace);
        }
    }
}
