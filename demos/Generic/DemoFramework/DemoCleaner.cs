using BulletSharp;
using System;
using System.Collections.Generic;

namespace DemoFramework
{
    public static class DemoCleaner
    {
        public static void StandardCleanup(this Demo demo)
        {
            CleanupConstraints(demo.World);
            CleanupBodiesAndShapes(demo.World);

            var multiBodyWorld = demo.World as MultiBodyDynamicsWorld;
            if (multiBodyWorld != null)
            {
                CleanupMultiBodyWorld(multiBodyWorld);
            }

            demo.World.Dispose();
            demo.Broadphase.Dispose();
            demo.Dispatcher.Dispose();
            demo.CollisionConf.Dispose();

            if (demo.Solver != null)
            {
                demo.Solver.Dispose();
            }

            AssertAllocatedMemoryFreed();
        }

        private static void CleanupConstraints(DynamicsWorld world)
        {
            for (int i = world.NumConstraints - 1; i >= 0; i--)
            {
                TypedConstraint constraint = world.GetConstraint(i);
                world.RemoveConstraint(constraint);
                constraint.Dispose();
            }
        }

        private static void CleanupBodiesAndShapes(DynamicsWorld world)
        {
            var shapes = new HashSet<CollisionShape>();

            for (int i = world.NumCollisionObjects - 1; i >= 0; i--)
            {
                CollisionObject obj = world.CollisionObjectArray[i];
                var body = obj as RigidBody;
                if (body != null && body.MotionState != null)
                {
                    body.MotionState.Dispose();
                }
                world.RemoveCollisionObject(obj);
                GetShapeWithChildShapes(obj.CollisionShape, shapes);

                obj.Dispose();
            }

            foreach (var shape in shapes)
            {
                shape.Dispose();
            }
        }

        private static void CleanupMultiBodyWorld(MultiBodyDynamicsWorld world)
        {
            for (int i = world.NumMultiBodyConstraints - 1; i >= 0; i--)
            {
                MultiBodyConstraint multiBodyConstraint = world.GetMultiBodyConstraint(i);
                world.RemoveMultiBodyConstraint(multiBodyConstraint);
                multiBodyConstraint.Dispose();
            }

            for (int i = world.NumMultibodies - 1; i >= 0; i--)
            {
                MultiBody multiBody = world.GetMultiBody(i);
                world.RemoveMultiBody(multiBody);
                multiBody.Dispose();
            }
        }

        private static void GetShapeWithChildShapes(CollisionShape shape, HashSet<CollisionShape> shapes)
        {
            shapes.Add(shape);

            var convex2DShape = shape as Convex2DShape;
            if (convex2DShape != null)
            {
                GetShapeWithChildShapes(convex2DShape.ChildShape, shapes);
                return;
            }

            var compoundShape = shape as CompoundShape;
            if (compoundShape != null)
            {
                foreach (var childShape in compoundShape.ChildList)
                {
                    GetShapeWithChildShapes(childShape.ChildShape, shapes);
                }
                return;
            }

            var scaledTriangleMeshShape = shape as ScaledBvhTriangleMeshShape;
            if (scaledTriangleMeshShape != null)
            {
                GetShapeWithChildShapes(scaledTriangleMeshShape.ChildShape, shapes);
                return;
            }

            var uniformScalingShape = shape as UniformScalingShape;
            if (uniformScalingShape != null)
            {
                GetShapeWithChildShapes(uniformScalingShape.ChildShape, shapes);
                return;
            }
        }

        private static void AssertAllocatedMemoryFreed()
        {
            int numAllocs;
            int numFrees;

            try
            {
                numAllocs = AlignedAllocator.NumAlignedAllocs;
                numFrees = AlignedAllocator.NumAlignedFrees;
            }
            catch (NotSupportedException)
            {
                return;
            }

            if (numAllocs != numFrees)
            {
                Console.WriteLine(
                    numAllocs.ToString() + " aligned objects allocated,\n" +
                    numFrees.ToString() + " aligned objects freed.");
            }
        }
    }
}
