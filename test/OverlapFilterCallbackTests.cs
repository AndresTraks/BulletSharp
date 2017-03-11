using BulletSharp;
using NUnit.Framework;

namespace BulletSharpTest
{
    public class CustomOverlapFilterCallback : OverlapFilterCallback
    {
        private RigidBody _expectedBody0;
        private RigidBody _expectedBody1;

        public bool WasCalled { get; private set; }

        public CustomOverlapFilterCallback(RigidBody expectedBody0, RigidBody expectedBody1)
        {
            _expectedBody0 = expectedBody0;
            _expectedBody1 = expectedBody1;
        }

        public override bool NeedBroadphaseCollision(BroadphaseProxy proxy0, BroadphaseProxy proxy1)
        {
            Assert.IsTrue(
                (proxy0.ClientObject == _expectedBody0 && proxy1.ClientObject == _expectedBody1) ||
                (proxy0.ClientObject == _expectedBody1 && proxy1.ClientObject == _expectedBody0));

            WasCalled = true;
            return true;
        }
    }

    [TestFixture]
    [Category("Callbacks")]
    public class OverlapFilterCallbackTests
    {
        private DefaultCollisionConfiguration _conf;
        private CollisionDispatcher _dispatcher;
        private BroadphaseInterface _broadphase;
        private DiscreteDynamicsWorld _world;

        private CollisionShape _shape;
        private RigidBody _sphere1;
        private RigidBody _sphere2;

        private CustomOverlapFilterCallback _callback;

        [OneTimeSetUp]
        public void SetUp()
        {
            _conf = new DefaultCollisionConfiguration();
            _dispatcher = new CollisionDispatcher(_conf);
            //_broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));
            _broadphase = new DbvtBroadphase();
            _world = new DiscreteDynamicsWorld(_dispatcher, _broadphase, null, _conf);

            _shape = new BoxShape(2);
            _sphere1 = CreateBody(0, Matrix.Translation(0, 0, 0), _shape);
            _sphere2 = CreateBody(1, Matrix.Translation(0, 1, 0), _shape);

            _callback = new CustomOverlapFilterCallback(_sphere1, _sphere2);
        }

        [Test]
        public void OverlapFilterCallbackTest()
        {
            HashedOverlappingPairCache pairCache = (HashedOverlappingPairCache)_world.PairCache;
            Assert.IsNull(pairCache.OverlapFilterCallback);

            pairCache.OverlapFilterCallback = _callback;

            for (int i = 0; i < 10; i++)
            {
                _world.StepSimulation(1.0f / 60.0f);
            }

            Assert.IsTrue(_callback.WasCalled);
        }

        [OneTimeTearDown]
        public void TearDown()
        {
            _world.Dispose();
            _dispatcher.Dispose();
            _broadphase.Dispose();
            _conf.Dispose();

            _callback.Dispose();

            _shape.Dispose();
            _sphere1.Dispose();
            _sphere2.Dispose();
        }

        private RigidBody CreateBody(float mass, Matrix transform, CollisionShape shape)
        {
            using (var info = new RigidBodyConstructionInfo(mass, null, shape, Vector3.Zero))
            {
                if (mass != 0.0f)
                {
                    info.LocalInertia = info.CollisionShape.CalculateLocalInertia(mass);
                }
                info.StartWorldTransform = transform;

                var collisionObject = new RigidBody(info);
                _world.AddRigidBody(collisionObject);
                return collisionObject;
            }
        }
    }
}
