using System;
using System.Collections.Generic;
using BulletSharp;

namespace BulletSharpTest
{
    class Program
    {
        static DiscreteDynamicsWorld world;

        static void TestGCCollection()
        {
            var conf = new DefaultCollisionConfiguration();
            var dispatcher = new CollisionDispatcher(conf);
            var broadphase = new DbvtBroadphase();
            world = new DiscreteDynamicsWorld(dispatcher, broadphase, null, conf);
            world.Gravity = new Vector3(0, -10, 0);
            dispatcher.NearCallback = DispatcherNearCallback;

            var groundShape = new BoxShape(50, 1, 50);
            var constInfo = new RigidBodyConstructionInfo(0.0f, new DefaultMotionState(), groundShape, Vector3.Zero);
            var groundObject = new RigidBody(constInfo);
            world.AddRigidBody(groundObject);

            constInfo.Mass = 1.0f;
            constInfo.CollisionShape = new SphereShape(1.0f);
            constInfo.LocalInertia = constInfo.CollisionShape.CalculateLocalInertia(constInfo.Mass);
            constInfo.MotionState = new DefaultMotionState();
            var dynamicObject = new RigidBody(constInfo);
            dynamicObject.Translate(new Vector3(0, 2, 0));
            world.AddRigidBody(dynamicObject);

            AddToDisposeQueue(conf);
            AddToDisposeQueue(dispatcher);
            AddToDisposeQueue(broadphase);
            AddToDisposeQueue(world);
            AddToDisposeQueue(groundShape);
            AddToDisposeQueue(constInfo);
            AddToDisposeQueue(groundObject);
            AddToDisposeQueue(constInfo.CollisionShape);
            AddToDisposeQueue(dynamicObject);

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
            world.SetInternalTickCallback(WorldPreTickCallback);
            for (int i = 0; i < 60; i++)
            {
                world.StepSimulation(1.0f / 60.0f);
            }
            //world.SetInternalTickCallback(null);
            //world.Dispose();
            world = null;

            groundShape = null;
            constInfo = null;
            groundObject = null;
            dynamicObject = null;

            GC.Collect(GC.MaxGeneration, GCCollectionMode.Forced);
            GC.WaitForPendingFinalizers();

            TestWeakRefs();
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
                Console.WriteLine(name + " GC collection OK");
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
            //Console.WriteLine("WorldPreTickCallback");
            if (!object.ReferenceEquals(world, world2))
            {
                Console.WriteLine("WorldPreTickCallback: World reference lost!");
            }
        }

        static void DispatcherNearCallback(BroadphasePair collisionPair, CollisionDispatcher dispatcher,
			DispatcherInfo dispatchInfo)
        {
            //Console.WriteLine("DispatcherNearCallback");
        }

        static void Main(string[] args)
        {
            TestGCCollection();

            Console.ReadKey();
        }
    }
}