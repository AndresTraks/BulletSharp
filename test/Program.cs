using BulletSharp;
using System;

namespace BulletSharpTest
{
    class Program
    {
        static public void TestWeakRef(string name, WeakReference wr)
        {
            if (wr.IsAlive)
            {
                Console.WriteLine(name + " GC collection failed!");
                Console.WriteLine("Generation: " + GC.GetGeneration(wr.Target));
            }
            else
            {
                Console.WriteLine(name + " OK");
            }
        }

        static public void TestGCCollection()
        {
            var conf = new DefaultCollisionConfiguration();
            var dispatcher = new CollisionDispatcher(conf);
            var broadphase = new DbvtBroadphase();
            var world = new DiscreteDynamicsWorld(dispatcher, broadphase, null, conf);
            world.Gravity = new Vector3(0, -10, 0);

            var conf_wr = new WeakReference(conf);
            var dispatcher_wr = new WeakReference(dispatcher);
            var broadphase_wr = new WeakReference(broadphase);
            var world_wr = new WeakReference(broadphase);

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
            world.StepSimulation(1.0f/60.0f);
            //world.SetInternalTickCallback(null);
            //world.Dispose();
            world = null;

            GC.Collect();
            GC.WaitForPendingFinalizers();
            TestWeakRef("CollisionConfiguration", conf_wr);
            TestWeakRef("CollisionDispatcher", dispatcher_wr);
            TestWeakRef("DbvtBroadphase", broadphase_wr);
            TestWeakRef("DiscreteDynamicsWorld", world_wr);
        }

        static void onDisposed(object sender, EventArgs e)
        {
            Console.WriteLine("OnDisposed: " + sender.ToString());
        }

        static void onDisposing(object sender, EventArgs e)
        {
            Console.WriteLine("OnDisposing: " + sender.ToString());
        }

        static void WorldPreTickCallback(DynamicsWorld world, float timeStep)
        {
            Console.WriteLine("WorldPreTickCallback");
        }

        static void Main(string[] args)
        {
            TestGCCollection();

            Console.ReadKey();
        }
    }
}
