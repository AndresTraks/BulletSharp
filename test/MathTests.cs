using BulletSharp;
using NUnit.Framework;
using System;

namespace BulletSharpTest
{
    [TestFixture]
    [Category("Math")]
    class MathTests
    {
        DefaultCollisionConfiguration conf;
        CollisionDispatcher dispatcher;
        AxisSweep3 broadphase;
        DiscreteDynamicsWorld world;

        BoxShape boxShape;
        RigidBody body1, body2;

        GhostObject ghostObject;

        [TestFixtureSetUp]
        public void SetUp()
        {
            conf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(conf);
            broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));
            world = new DiscreteDynamicsWorld(dispatcher, broadphase, null, conf);

            broadphase.OverlappingPairUserCallback = new AxisSweepUserCallback();

            boxShape = new BoxShape(1);

            body1 = CreateBody(10.0f, new SphereShape(1.0f), new Vector3(2, 2, 0));
            body2 = CreateBody(1.0f, new SphereShape(1.0f), new Vector3(0, 2, 0));

            ghostObject = new PairCachingGhostObject();
            ghostObject.WorldTransform = Matrix.Translation(-1, 2, 0);
            ghostObject.CollisionShape = boxShape;
            broadphase.OverlappingPairCache.SetInternalGhostPairCallback(new GhostPairCallback());
        }

        [Test]
        public void AlignmentTest()
        {
            const float mass = 1.0f;

            for (int i = 0; i < 100; i++)
            {
                // RigidBodyConstructionInfo without the optional localInertia parameter will
                // cause the default value to be passed, which is not aligned to 16 bytes in C++/CLI.
                // If BulletSharp doesn't explicitly pass an aligned value and SSE is used,
                // an AccessViolationException occurs.
                var info = new RigidBodyConstructionInfo(mass, new DefaultMotionState(), boxShape); // , Vector3.Zero
                info.Dispose();
            }
        }

        [Test]
        public void AlignedObjectArray_World()
        {
            // World's object array has a backing list
            var objects = world.CollisionObjectArray;
            Assert.AreSame(objects[0], body1);
            Assert.AreSame(objects[1], body2);

            // Swap
            objects.Swap(0, 1);
            Assert.AreSame(objects[0], body2);
            Assert.AreSame(objects[1], body1);

            objects.Swap(0, 1);
            Assert.AreSame(objects[0], body1);
            Assert.AreSame(objects[1], body2);

            Assert.AreEqual(2, objects.Count);
            Assert.AreEqual(2, world.NumCollisionObjects);

            // Remove
            objects.Remove(body1);
            Assert.AreEqual(1, objects.Count);
            Assert.AreSame(body2, objects[0]);
            
            // List modifications should propagate to the related world
            Assert.AreEqual(1, world.NumCollisionObjects);
            Assert.IsNull(body1.BroadphaseHandle);

            // Add (body1 & body2 order flipped)
            objects.Add(body1);
            Assert.AreSame(body2, objects[0]);
            Assert.AreSame(body1, objects[1]);

            Assert.AreEqual(2, world.NumCollisionObjects);
            Assert.IsNotNull(body1.BroadphaseHandle);
            Assert.AreSame(body1, body1.BroadphaseHandle.ClientObject);

            // Contains
            Assert.True(objects.Contains(body1));
            Assert.True(objects.Contains(body2));

            // CopyTo
            CollisionObject[] objectsArray = new CollisionObject[2];
            objects.CopyTo(objectsArray, 0);
            Assert.AreSame(body2, objectsArray[0]);
            Assert.AreSame(body1, objectsArray[1]);

            // IndexOf
            Assert.AreEqual(0, objects.IndexOf(body2));
            Assert.AreEqual(1, objects.IndexOf(body1));
            Assert.AreEqual(-1, objects.IndexOf(null));

            // RemoveAt
            objects.RemoveAt(0);
            Assert.AreEqual(1, objects.Count);
            Assert.AreEqual(1, world.NumCollisionObjects);
            Assert.AreSame(body1, objects[0]);

            world.AddCollisionObject(body2);

            // PopBack
            objects.PopBack();
            Assert.AreEqual(1, objects.Count);
            Assert.AreEqual(1, world.NumCollisionObjects);
            Assert.AreSame(body1, objects[0]);

            world.AddCollisionObject(body2);

            // Clear
            objects.Clear();
            Assert.AreEqual(0, objects.Count);
            Assert.AreEqual(0, world.NumCollisionObjects);
            Assert.IsNull(body1.BroadphaseHandle);
            Assert.IsNull(body2.BroadphaseHandle);

            world.AddCollisionObject(body1, CollisionFilterGroups.DefaultFilter, CollisionFilterGroups.AllFilter);
            world.AddCollisionObject(body2, CollisionFilterGroups.DefaultFilter, CollisionFilterGroups.AllFilter);
        }

        [Test]
        public void AlignedObjectArray_GhostObject()
        {
            var pairs = ghostObject.OverlappingPairs;
            Assert.AreEqual(0, pairs.Count);

            // Ghost object's object array does not have a backing list
            world.AddCollisionObject(ghostObject);
            Assert.AreEqual(3, world.NumCollisionObjects);

            world.StepSimulation(1 / 60.0f);

            Assert.AreEqual(1, pairs.Count);
            Assert.AreSame(pairs[0].CollisionShape, body2.CollisionShape);

            world.RemoveCollisionObject(ghostObject);
            Assert.AreEqual(2, world.NumCollisionObjects);
        }

        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void AlignedObjectArray_ArgumentOutOfRange()
        {
            world.CollisionObjectArray[2] = null;
        }

        [TestFixtureTearDown]
        public void TearDown()
        {
            world.RemoveRigidBody(body1);
            world.RemoveRigidBody(body2);
            boxShape.Dispose();
            body1.MotionState.Dispose();
            body2.MotionState.Dispose();
            body1.Dispose();
            body2.Dispose();
            ghostObject.Dispose();

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
