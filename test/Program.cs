using System;
using System.Collections.Generic;
using BulletSharp;

namespace BulletSharpTest
{
    class Program
    {
        static DiscreteDynamicsWorld world;

        static RigidBody CreateBody(float mass, CollisionShape shape, Vector3 offset)
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

        static void TestGCCollection()
        {
            var conf = new DefaultCollisionConfiguration();
            var dispatcher = new CollisionDispatcher(conf);
            var broadphase = new DbvtBroadphase();
            world = new DiscreteDynamicsWorld(dispatcher, broadphase, null, conf);
            world.Gravity = new Vector3(0, -10, 0);
            dispatcher.NearCallback = DispatcherNearCallback;

            CreateBody(0.0f, new BoxShape(50, 1, 50), Vector3.Zero);
            CreateBody(10.0f, new SphereShape(1.0f), new Vector3(2, 2, 0));
            var dynamicObject = CreateBody(1.0f, new SphereShape(1.0f), new Vector3(0, 2, 0));

            AddToDisposeQueue(conf);
            AddToDisposeQueue(dispatcher);
            AddToDisposeQueue(broadphase);
            AddToDisposeQueue(world);

            //conf.Dispose();
            conf = null;
            dispatcher.OnDisposing += onDisposing;
            dispatcher.OnDisposed += onDisposed;
            //dispatcher.Dispose();
            dispatcher = null;
            broadphase.OnDisposing += onDisposing;
            broadphase.OnDisposed += onDisposed;
            //broadphase.Dispose();
            broadphase = null;
            world.OnDisposing += onDisposing;
            world.OnDisposed += onDisposed;
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

            TestRayCast(dynamicObject);
            TestManifoldPoints();

            //world.SetInternalTickCallback(null);
            //world.Dispose();
            world = null;

            dynamicObject = null;

            GC.Collect(GC.MaxGeneration, GCCollectionMode.Forced);
            GC.WaitForPendingFinalizers();

            TestWeakRefs();
        }

        static void TestManifoldPoints()
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

        static void TestRayCast(CollisionObject testObject)
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

        static void TestWeakRefs()
        {
            foreach (var r in disposeQueue)
            {
                TestWeakRef(r.Key, r.Value);
            }
        }

        static void TestWeakRef(string name, WeakReference wr)
        {
            if (wr.IsAlive)
            {
                Console.Write(name + " GC collection FAILED! ");
                Console.WriteLine("Gen: " + GC.GetGeneration(wr.Target));
            }
            else
            {
                //Console.WriteLine(name + " GC collection OK");
            }
        }

        static Dictionary<string, WeakReference> disposeQueue = new Dictionary<string, WeakReference>();
        static void AddToDisposeQueue(object obj)
        {
            var r = new WeakReference(obj);
            string name = obj.GetType().Name;
            if (disposeQueue.ContainsKey(name))
            {
                int i = 2;
                var name2 = name + i.ToString();
                while (disposeQueue.ContainsKey(name2))
                {
                    i++;
                    name2 = name + i.ToString();
                }
                name = name2;
            }
            disposeQueue.Add(name, r);
        }

        static void onDisposed(object sender, EventArgs e)
        {
            Console.WriteLine("OnDisposed: " + sender.ToString());
        }

        static void onDisposing(object sender, EventArgs e)
        {
            Console.WriteLine("OnDisposing: " + sender.ToString());
        }

        static void WorldPreTickCallback(DynamicsWorld world2, float timeStep)
        {
            TestManifoldPoints();

            //Console.WriteLine("WorldPreTickCallback");
            if (!object.ReferenceEquals(world, world2))
            {
                Console.WriteLine("WorldPreTickCallback: World reference lost!");
            }
        }

        static void DispatcherNearCallback(BroadphasePair collisionPair, CollisionDispatcher dispatcher,
			DispatcherInfo dispatchInfo)
        {
            //AddToDisposeQueue(dispatchInfo.DebugDraw);
            TestManifoldPoints();
            //Console.WriteLine("DispatcherNearCallback");
        }

        static void Main(string[] args)
        {
            TestGCCollection();

            Console.WriteLine("Finished");
            Console.ReadKey();
        }
    }

    class CustomRayCallback : ClosestRayResultCallback
    {
        public CustomRayCallback(ref Vector3 rayFrom, ref Vector3 rayTo)
            : base(rayFrom, rayTo)
        {
        }

        public override float AddSingleResult(LocalRayResult rayResult, bool normalInWorldSpace)
        {
            return base.AddSingleResult(rayResult, normalInWorldSpace);
        }
    }
}