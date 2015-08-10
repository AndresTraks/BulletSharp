using BulletSharp;
using System;

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
            if (!(createFunc is BoxBoxCollisionAlgorithm.CreateFunc))
            {
                Console.WriteLine("BoxBoxCollisionAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.SphereShape, BroadphaseNativeType.SphereShape);
            if (!(createFunc is SphereSphereCollisionAlgorithm.CreateFunc))
            {
                Console.WriteLine("SphereSphereCollisionAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.SphereShape, BroadphaseNativeType.TriangleShape);
            if (!(createFunc is SphereTriangleCollisionAlgorithm.CreateFunc))
            {
                Console.WriteLine("SphereTriangleCollisionAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.TriangleShape, BroadphaseNativeType.SphereShape);
            if (!(createFunc is SphereTriangleCollisionAlgorithm.CreateFunc))
            {
                Console.WriteLine("SphereTriangleCollisionAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.BoxShape, BroadphaseNativeType.StaticPlaneShape);
            if (!(createFunc is ConvexPlaneCollisionAlgorithm.CreateFunc))
            {
                Console.WriteLine("ConvexPlaneCollisionAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.StaticPlaneShape, BroadphaseNativeType.BoxShape);
            if (!(createFunc is ConvexPlaneCollisionAlgorithm.CreateFunc))
            {
                Console.WriteLine("ConvexPlaneCollisionAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CylinderShape, BroadphaseNativeType.CylinderShape);
            if (!(createFunc is ConvexConvexAlgorithm.CreateFunc))
            {
                Console.WriteLine("ConvexConvexAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CylinderShape, BroadphaseNativeType.TerrainShape);
            if (!(createFunc is ConvexConcaveCollisionAlgorithm.CreateFunc))
            {
                Console.WriteLine("ConvexConcaveCollisionAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.TerrainShape, BroadphaseNativeType.CylinderShape);
            if (!(createFunc is ConvexConcaveCollisionAlgorithm.SwappedCreateFunc))
            {
                Console.WriteLine("ConvexConcaveCollisionAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CompoundShape, BroadphaseNativeType.CompoundShape);
            if (!(createFunc is CompoundCompoundCollisionAlgorithm.CreateFunc))
            {
                Console.WriteLine("CompoundCompoundCollisionAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.CompoundShape, BroadphaseNativeType.BoxShape);
            if (!(createFunc is CompoundCompoundCollisionAlgorithm.CreateFunc))
            {
                Console.WriteLine("CompoundCompoundCollisionAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = conf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.BoxShape, BroadphaseNativeType.CompoundShape);
            if (!(createFunc is CompoundCompoundCollisionAlgorithm.SwappedCreateFunc))
            {
                Console.WriteLine("CompoundCompoundCollisionAlgorithm ERROR!");
            }
            AddToDisposeQueue(createFunc);
            createFunc = null;
            conf = null;

            ForceGC();
            TestWeakRefs();
            ClearRefs();
        }
    }
}
