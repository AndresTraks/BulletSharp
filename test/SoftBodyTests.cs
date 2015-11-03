using BulletSharp;
using BulletSharp.SoftBody;
using NUnit.Framework;

namespace BulletSharpTest
{
    [TestFixture]
    class SoftBodyTests
    {
        SoftBodyRigidBodyCollisionConfiguration conf;
        SoftBodyWorldInfo softBodyWorldInfo;
        CollisionDispatcher dispatcher;
        AxisSweep3 broadphase;
        DefaultSoftBodySolver solver;
        SoftRigidDynamicsWorld world;
        SoftBody softBody;

        [Test]
        public void SoftBodyTest()
        {
            Assert.AreSame(softBody.SoftBodySolver, solver, "body and world SoftBodySolvers don't match");

            //Assert.AreSame(dispatcher, softBodyWorldInfo.Dispatcher);
            //Assert.AreSame(broadphase, softBodyWorldInfo.Broadphase);

            Assert.AreEqual(1, world.SoftBodyArray.Count);
        }

        [TestFixtureSetUp]
        public void SetUp()
        {
            conf = new SoftBodyRigidBodyCollisionConfiguration();
            dispatcher = new CollisionDispatcher(conf);
            broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000),
                new Vector3(1000, 1000, 1000));
            solver = new DefaultSoftBodySolver();
            world = new SoftRigidDynamicsWorld(dispatcher, broadphase, null, conf, solver);

            softBodyWorldInfo = new SoftBodyWorldInfo();
            softBody = new SoftBody(softBodyWorldInfo);
            world.AddSoftBody(softBody);
        }

        [TestFixtureTearDown]
        public void TearDown()
        {
            world.RemoveSoftBody(softBody);
            softBody.Dispose();
            softBodyWorldInfo.Dispose();

            world.Dispose();
            solver.Dispose();
            broadphase.Dispose();
            dispatcher.Dispose();
            conf.Dispose();
        }
    }
}
