using BulletSharp;
using NUnit.Framework;

namespace BulletSharpTest
{
    [TestFixture]
    class CollisionAlgorithmTests
    {
        DefaultCollisionConfiguration conf;

        [Test]
        public void CollisionAlgorithmTest()
        {
            Assert.NotNull(conf.CollisionAlgorithmPool);
            Assert.NotNull(conf.PersistentManifoldPool);
            Assert.NotNull(conf.SimplexSolver);

            // Test that the correct collision algorithms are returned in GetCollisionAlgorithmCreateFunc
            var createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.BoxShape, BroadphaseNativeType.BoxShape);
            Assert.IsInstanceOf(typeof(BoxBoxCollisionAlgorithm.CreateFunc), createFunc);

            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.SphereShape, BroadphaseNativeType.SphereShape);
            Assert.IsInstanceOf(typeof(SphereSphereCollisionAlgorithm.CreateFunc), createFunc);

            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.SphereShape, BroadphaseNativeType.TriangleShape);
            Assert.IsInstanceOf(typeof(SphereTriangleCollisionAlgorithm.CreateFunc), createFunc);

            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.TriangleShape, BroadphaseNativeType.SphereShape);
            Assert.IsInstanceOf(typeof(SphereTriangleCollisionAlgorithm.CreateFunc), createFunc);

            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.BoxShape, BroadphaseNativeType.StaticPlaneShape);
            Assert.IsInstanceOf(typeof(ConvexPlaneCollisionAlgorithm.CreateFunc), createFunc);

            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.StaticPlaneShape, BroadphaseNativeType.BoxShape);
            Assert.IsInstanceOf(typeof(ConvexPlaneCollisionAlgorithm.CreateFunc), createFunc);

            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CylinderShape, BroadphaseNativeType.CylinderShape);
            Assert.IsInstanceOf(typeof(ConvexConvexAlgorithm.CreateFunc), createFunc);

            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CylinderShape, BroadphaseNativeType.TerrainShape);
            Assert.IsInstanceOf(typeof(ConvexConcaveCollisionAlgorithm.CreateFunc), createFunc);

            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.TerrainShape, BroadphaseNativeType.CylinderShape);
            Assert.IsInstanceOf(typeof(ConvexConcaveCollisionAlgorithm.SwappedCreateFunc), createFunc);

            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CompoundShape, BroadphaseNativeType.CompoundShape);
            Assert.IsInstanceOf(typeof(CompoundCompoundCollisionAlgorithm.CreateFunc), createFunc);

            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CompoundShape, BroadphaseNativeType.BoxShape);
            Assert.IsInstanceOf(typeof(CompoundCompoundCollisionAlgorithm.CreateFunc), createFunc);

            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.BoxShape, BroadphaseNativeType.CompoundShape);
            Assert.IsInstanceOf(typeof(CompoundCompoundCollisionAlgorithm.SwappedCreateFunc), createFunc);
        }

        [TestFixtureSetUp]
        public void SetUp()
        {
            conf = new DefaultCollisionConfiguration();
        }

        [TestFixtureTearDown]
        public void TearDown()
        {
            conf.Dispose();
        }
    }
}
