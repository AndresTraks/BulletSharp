using BulletSharp;

namespace BulletSharpTest
{
    class CollisionAlgorithmTests : TestContext
    {
        public override void Run()
        {
            var conf = new DefaultCollisionConfiguration();

            // Test CollisionConfiguration methods
            var pool = conf.CollisionAlgorithmPool;
            AddToDisposeQueue(pool);
            pool = conf.PersistentManifoldPool;
            AddToDisposeQueue(pool);
            pool = null;
            var simplexSolver = conf.SimplexSolver;
            //var simplexResult = simplexSolver.CachedBC;
            //AddToDisposeQueue(simplexResult);
            //simplexResult = null;
            AddToDisposeQueue(simplexSolver);
            simplexSolver = null;
            var createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.BoxShape, BroadphaseNativeType.BoxShape);
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.SphereShape, BroadphaseNativeType.SphereShape);
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.SphereShape, BroadphaseNativeType.TriangleShape);
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.TriangleShape, BroadphaseNativeType.SphereShape);
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.BoxShape, BroadphaseNativeType.StaticPlaneShape);
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.StaticPlaneShape, BroadphaseNativeType.BoxShape);
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CylinderShape, BroadphaseNativeType.CylinderShape);
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CylinderShape, BroadphaseNativeType.TerrainShape);
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.TerrainShape, BroadphaseNativeType.CylinderShape);
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CompoundShape, BroadphaseNativeType.CompoundShape);
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CompoundShape, BroadphaseNativeType.BoxShape);
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.BoxShape, BroadphaseNativeType.CompoundShape);
            AddToDisposeQueue(createFunc);
            createFunc = null;
            conf = null;

            ForceGC();
            TestWeakRefs();
            ClearRefs();
        }
    }
}
