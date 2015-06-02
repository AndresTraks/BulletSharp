using System;
using BulletSharp;
using BulletSharp.SoftBody;

namespace BulletSharpTest
{
    class SoftBodyTests : TestContext
    {
        public override void Run()
        {
            var softBodyWorldInfo = new SoftBodyWorldInfo();
            var softBody = new SoftBody(softBodyWorldInfo);
            var softBodyCollisionConf = new SoftBodyRigidBodyCollisionConfiguration();
            var softBodySolver = new DefaultSoftBodySolver();
            var dispatcher = new CollisionDispatcher(softBodyCollisionConf);
            var broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000),
                new Vector3(1000, 1000, 1000));
            var softBodyWorld = new SoftRigidDynamicsWorld(dispatcher, broadphase, null, softBodyCollisionConf, softBodySolver);
            softBodyWorld.AddSoftBody(softBody);

            if (!object.ReferenceEquals(softBody.SoftBodySolver, softBodySolver))
            {
                Console.WriteLine("SoftBody: body and world SoftBodySolvers don't match!");
            }

            AddToDisposeQueue(softBodyWorldInfo);
            AddToDisposeQueue(softBody);
            AddToDisposeQueue(softBodyCollisionConf);
            AddToDisposeQueue(softBodySolver);
            AddToDisposeQueue(dispatcher);
            AddToDisposeQueue(broadphase);
            AddToDisposeQueue(softBodyWorld);

            softBodyWorldInfo = null;
            softBody = null;
            softBodyCollisionConf = null;
            softBodySolver = null;
            dispatcher = null;
            broadphase = null;
            softBodyWorld.Dispose();
            softBodyWorld = null;

            ForceGC();
            TestWeakRefs();
            ClearRefs();
        }
    }
}
