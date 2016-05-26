using BulletSharp;
using NUnit.Framework;
using System;
using System.Collections.Generic;

namespace BulletSharpTest
{
    [TestFixture]
    [Category("Collections")]
    class CollisionObjectArrayTests
    {
        DefaultCollisionConfiguration conf;
        CollisionDispatcher dispatcher;
        AxisSweep3 broadphase;
        DiscreteDynamicsWorld world;

        BoxShape boxShape;
        
        [TestFixtureSetUp]
        public void SetUp()
        {
            conf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(conf);
            broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));
            world = new DiscreteDynamicsWorld(dispatcher, broadphase, null, conf);

            broadphase.OverlappingPairUserCallback = new AxisSweepUserCallback();

            boxShape = new BoxShape(1);
        }



        [Test]
        public void AlignedObjectArray_CollisionObjectTest()
        {
            // Allocate bodies
            var bodies = new List<RigidBody>();
            for (int i = 0; i < 100; i++)
            {
                bodies.Add(CreateBody(10.0f, boxShape, new Vector3(i * 2, 2, 0)));
            }

            var objects = world.CollisionObjectArray;
            for (int i = 0; i < bodies.Count; i++)
            {
                Assert.AreEqual(objects[i], bodies[i]);
            }

            // Dispose all bodies
            foreach (var body in bodies)
            {
                world.RemoveRigidBody(body);
                body.MotionState.Dispose();
                body.Dispose();
            }
            Assert.AreEqual(0, objects.Count);
            Assert.AreEqual(0, world.NumCollisionObjects);

            // Allocate second set of bodies
            // that may have the same address
            var bodies2 = new List<RigidBody>();
            for (int i = 0; i < 100; i++)
            {
                bodies2.Add(CreateBody(10.0f, boxShape, new Vector3(i * 2, 2, 0)));
            }

            foreach (var body in bodies)
            {
                foreach (var body2 in bodies2)
                {
                    // Bodies with the same address should not be the same
                    Assert.AreNotEqual(body, body2);
                }
            }

            bodies.Clear();
        }
        
        [TestFixtureTearDown]
        public void TearDown()
        {
            boxShape.Dispose();

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
