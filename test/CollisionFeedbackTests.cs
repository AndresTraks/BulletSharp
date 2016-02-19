using BulletSharp;
using NUnit.Framework;

namespace BulletSharpTest
{
    [TestFixture]
    class CollisionFeedbackTests
    {
        DefaultCollisionConfiguration conf;
        CollisionDispatcher dispatcher;
        AxisSweep3 broadphase;
        DiscreteDynamicsWorld world;

        BoxShape groundShape;
        BoxShape boxShape, boxShape2, boxShape3;
        CompoundShape compoundShape, compoundShape2;
        RigidBody ground;
        RigidBody compound;

        [TestFixtureSetUp]
        public void SetUp()
        {
            conf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(conf);
            broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));
            world = new DiscreteDynamicsWorld(dispatcher, broadphase, null, conf);

            groundShape = new BoxShape(30, 1, 30);
            ground = CreateBody(0, Matrix.Translation(0, -5, 0), groundShape);
            ground.CollisionFlags |= CollisionFlags.CustomMaterialCallback;

            compoundShape = new CompoundShape();
            boxShape = new BoxShape(1, 1, 1);
            compoundShape.AddChildShape(Matrix.Identity, boxShape);
            boxShape2 = new BoxShape(1, 1, 1);
            compoundShape.AddChildShape(Matrix.Translation(0, -1, 0), boxShape2);
            boxShape3 = new BoxShape(1, 1, 1);
            compoundShape.AddChildShape(Matrix.Translation(0, -2, 0), boxShape3);

            compoundShape2 = new CompoundShape();
            compoundShape2.AddChildShape(Matrix.Identity, compoundShape);

            compound = CreateBody(1, Matrix.Translation(0, 0, 0), compoundShape2);

            ManifoldPoint.ContactAdded += ContactAdded;
        }

        private void ContactAdded(ManifoldPoint cp, CollisionObjectWrapper colObj0Wrap, int partId0, int index0, CollisionObjectWrapper colObj1Wrap, int partId1, int index1)
        {
            Assert.AreEqual(2, index0);
            Assert.AreEqual(2, cp.Index0);

            Assert.AreSame(compound, colObj0Wrap.CollisionObject);
            Assert.AreSame(ground, colObj1Wrap.CollisionObject);
            Assert.AreSame(boxShape3, colObj0Wrap.CollisionShape);
            Assert.AreSame(groundShape, colObj1Wrap.CollisionShape);
        }

        [Test]
        public void CollisionFeedbackTest()
        {
            for (int i = 0; i < 100; i++)
            {
                world.StepSimulation(1.0f / 60.0f);
            }
        }

        [TestFixtureTearDown]
        public void TearDown()
        {
            world.RemoveRigidBody(compound);
            compound.MotionState.Dispose();
            ground.Dispose();
            groundShape.Dispose();
            compound.Dispose();
            boxShape.Dispose();
            boxShape2.Dispose();
            boxShape3.Dispose();
            compoundShape.Dispose();
            compoundShape2.Dispose();

            world.Dispose();
            dispatcher.Dispose();
            broadphase.Dispose();
            conf.Dispose();
        }

        RigidBody CreateBody(float mass, Matrix transform, CollisionShape shape)
        {
            using (var info = new RigidBodyConstructionInfo(mass, new DefaultMotionState(transform), shape, Vector3.Zero))
            {
                if (mass != 0.0f)
                {
                    info.LocalInertia = info.CollisionShape.CalculateLocalInertia(mass);
                }
                var collisionObject = new RigidBody(info);
                world.AddRigidBody(collisionObject);
                return collisionObject;
            }
        }
    }
}
