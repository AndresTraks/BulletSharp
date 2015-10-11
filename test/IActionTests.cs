using BulletSharp;
using NUnit.Framework;
using System;

namespace BulletSharpTest
{
    class Action : IAction
    {
        public bool Updated { get; set; }

        public void DebugDraw(IDebugDraw debugDrawer)
        {
            throw new NotImplementedException();
        }

        public void UpdateAction(CollisionWorld collisionWorld, float deltaTimeStep)
        {
            Updated = true;
        }

        public void UpdateAction(CollisionWorld collisionWorld, double deltaTimeStep)
        {
            Updated = true;
        }
    }

    [TestFixture]
    class IActionTests
    {
        DefaultCollisionConfiguration conf;
        CollisionDispatcher dispatcher;
        AxisSweep3 broadphase;
        DiscreteDynamicsWorld world;

        Action action;

        [Test]
        public void IActionTest()
        {
            for (int i = 0; i < 60; i++)
            {
                world.StepSimulation(1.0f / 60.0f);
            }
            Assert.True(action.Updated);
        }

        [TestFixtureSetUp]
        public void SetUp()
        {
            conf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(conf);
            broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));
            world = new DiscreteDynamicsWorld(dispatcher, broadphase, null, conf);

            action = new Action();
            world.AddAction(action);
            world.AddAction(action);
            world.RemoveAction(action);
            world.RemoveAction(action);
            world.AddAction(action);
        }

        [TestFixtureTearDown]
        public void TearDown()
        {
            world.Dispose();
            dispatcher.Dispose();
            broadphase.Dispose();
            conf.Dispose();
        }
    }
}
