using BulletSharp;
using NUnit.Framework;
using System;

namespace BulletSharpTest
{
    class AxisSweepUserCallback : OverlappingPairCallback
    {
        public AxisSweepUserCallback()
        {
        }

        public override BroadphasePair AddOverlappingPair(BroadphaseProxy proxy0, BroadphaseProxy proxy1)
        {
            return null;
        }

        public override IntPtr RemoveOverlappingPair(BroadphaseProxy proxy0, BroadphaseProxy proxy1, Dispatcher dispatcher)
        {
            return IntPtr.Zero;
        }

        public override void RemoveOverlappingPairsContainingProxy(BroadphaseProxy proxy0, Dispatcher dispatcher)
        {
            throw new NotImplementedException();
        }
    }

    class CustomBroadphaseAabbCallback : BroadphaseAabbCallback
    {
        public bool Processed { get; set; }

        public override bool Process(BroadphaseProxy proxy)
        {
            Processed = true;
            return true;
        }
    }

    class CustomBroadphaseRayTestCallback : BroadphaseRayCallback
    {
        public bool HasHit { get; private set; }

        public CustomBroadphaseRayTestCallback(ref Vector3 rayFromWorld, ref Vector3 rayToWorld)
        {
            Vector3 rayDir = (rayToWorld - rayFromWorld);
            rayDir.Normalize();
            RayDirectionInverse = new Vector3(
                rayDir[0] == 0 ? float.MaxValue : 1 / rayDir[0],
                rayDir[1] == 0 ? float.MaxValue : 1 / rayDir[1],
                rayDir[2] == 0 ? float.MaxValue : 1 / rayDir[2]);
            Signs[0] = (RayDirectionInverse[0] < 0) ? 1U : 0U;
            Signs[1] = (RayDirectionInverse[1] < 0) ? 1U : 0U;
            Signs[2] = (RayDirectionInverse[2] < 0) ? 1U : 0U;

            LambdaMax = rayDir.Dot(rayToWorld - rayFromWorld);
        }

        public override bool Process(BroadphaseProxy proxy)
        {
            HasHit = true;
            return true;
        }
    }

    [TestFixture]
    class AxisSweepTests
    {
        DefaultCollisionConfiguration conf;
        CollisionDispatcher dispatcher;
        AxisSweep3 broadphase;
        DiscreteDynamicsWorld world;

        RigidBody body1, body2;

        [Test]
        public void AxisSweepAabbTest()
        {
            var rayFromWorld = new Vector3(-2, 2, 0);
            var rayToWorld = new Vector3(4, 2, 0);
            using (var aabbCallback = new CustomBroadphaseAabbCallback())
            {
                broadphase.AabbTest(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000), aabbCallback);
                Assert.True(aabbCallback.Processed, "Broadphase AABB callback failed");
            }
        }

        [Test]
        public void AxisSweepRayTest()
        {
            var rayFromWorld = new Vector3(-2, 2, 0);
            var rayToWorld = new Vector3(4, 2, 0);
            using (var rayCallback = new CustomBroadphaseRayTestCallback(ref rayFromWorld, ref rayToWorld))
            {
                broadphase.RayTest(rayFromWorld, rayToWorld, rayCallback, Vector3.Zero, Vector3.Zero);
                Assert.True(rayCallback.HasHit, "Broadphase ray test failed");
            }
        }
        
        [TestFixtureSetUp]
        public void SetUp()
        {
            conf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(conf);
            broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));
            world = new DiscreteDynamicsWorld(dispatcher, broadphase, null, conf);

            broadphase.OverlappingPairUserCallback = new AxisSweepUserCallback();

            body1 = CreateBody(10.0f, new SphereShape(1.0f), new Vector3(2, 2, 0));
            body2 = CreateBody(1.0f, new SphereShape(1.0f), new Vector3(0, 2, 0));
        }

        [TestFixtureTearDown]
        public void TearDown()
        {
            world.RemoveRigidBody(body1);
            world.RemoveRigidBody(body2);
            body1.CollisionShape.Dispose();
            body2.CollisionShape.Dispose();
            body1.MotionState.Dispose();
            body2.MotionState.Dispose();
            body1.Dispose();
            body2.Dispose();

            broadphase.OverlappingPairUserCallback.Dispose();
            broadphase.OverlappingPairUserCallback = null;

            world.Dispose();
            dispatcher.Dispose();
            broadphase.Dispose();
            conf.Dispose();
        }

        RigidBody CreateBody(float mass, CollisionShape shape, Vector3 offset)
        {
            using (var info = new RigidBodyConstructionInfo(mass, new DefaultMotionState(), shape, Vector3.Zero))
            {
                if (mass != 0.0f)
                {
                    info.LocalInertia = info.CollisionShape.CalculateLocalInertia(mass);
                }
                var collisionObject = new RigidBody(info);
                collisionObject.Translate(offset);
                world.AddRigidBody(collisionObject);
                return collisionObject;
            }
        }
    }
}
