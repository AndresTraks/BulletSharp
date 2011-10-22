using BulletSharp;
using DemoFramework;
using SharpDX;
using System.Collections.Generic;

namespace ConvexDecompositionDemo
{
    class Physics : PhysicsContext
    {
        Vector3 convexDecompositionObjectOffset;
        AlignedTriangleMeshArray trimeshes = new AlignedTriangleMeshArray();

        // MyContactCallback is just an example to show how to get access to the child shape that collided
        bool MyContactCallback(ManifoldPoint cp, CollisionObject colObj0, int partId0, int index0, CollisionObject colObj1, int partId1, int index1)
        {
            if (colObj0.RootCollisionShape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                CompoundShape compound = colObj0.RootCollisionShape as CompoundShape;
                CollisionShape childShape = compound.GetChildShape(index0);
            }

            if (colObj1.RootCollisionShape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                CompoundShape compound = colObj1.RootCollisionShape as CompoundShape;
                CollisionShape childShape = compound.GetChildShape(index1);
            }

            return true;
        }

        public void SetupEmptyDynamicsWorld()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            convexDecompositionObjectOffset = new Vector3(10, 0, 0);

            Broadphase = new AxisSweep3(new Vector3(-10000, -10000, -10000), new Vector3(10000, 10000, 10000));
            //Broadphase = new SimpleBroadphase();

            Solver = new SequentialImpulseConstraintSolver();
            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);

            // create the ground
            CollisionShape groundShape = new BoxShape(30, 2, 30);
            CollisionShapes.Add(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Translation(0, -4.5f, 0), groundShape);
            ground.UserObject = "Ground";

            // create a few dynamic rigidbodies
            float mass = 1.0f;

            CollisionShape colShape = new BoxShape(1);
            CollisionShapes.Add(colShape);
            Vector3 localInertia = colShape.CalculateLocalInertia(mass);
        }

        public override void InitPhysics()
        {
            SetupEmptyDynamicsWorld();

            WavefrontObj wo = new WavefrontObj();
            int tcount = wo.LoadObj("file.obj");
            if (tcount > 0)
            {
                TriangleMesh trimesh = new TriangleMesh();
                trimeshes.Add(trimesh);

                Vector3 localScaling = new Vector3(6, 6, 6);
                List<int> indices = wo.Indices;
                List<Vector3> vertices = wo.Vertices;

                int i;
                for (i = 0; i < tcount; i++)
                {
                    int index0 = indices[i * 3];
                    int index1 = indices[i * 3 + 1];
                    int index2 = indices[i * 3 + 2];

                    Vector3 vertex0 = Vector3.Modulate(vertices[index0], localScaling);
                    Vector3 vertex1 = Vector3.Modulate(vertices[index1], localScaling);
                    Vector3 vertex2 = Vector3.Modulate(vertices[index2], localScaling);

                    trimesh.AddTriangle(vertex0, vertex1, vertex2);
                }

                ConvexShape tmpConvexShape = new ConvexTriangleMeshShape(trimesh);

                //create a hull approximation
                ShapeHull hull = new ShapeHull(tmpConvexShape);
                float margin = tmpConvexShape.Margin;
                hull.BuildHull(margin);
                tmpConvexShape.UserObject = hull;

                ConvexHullShape convexShape = new ConvexHullShape();
                BulletSharp.DataStream ds = hull.GetVertexStream();
                while (ds.Position < ds.Length)
                {
                    Vector3 a = ds.Read<Vector3>();
                    ds.Read<int>(); // btVector3 padding
                    convexShape.AddPoint(a);
                }
                ds.Dispose();

                tmpConvexShape.Dispose();
                //hull.Dispose();


                CollisionShapes.Add(convexShape);

                float mass = 1.0f;

                LocalCreateRigidBody(mass, Matrix.Translation(0, 2, 14), convexShape);

                bool useQuantization = true;
                CollisionShape concaveShape = new BvhTriangleMeshShape(trimesh, useQuantization);
                LocalCreateRigidBody(0, Matrix.Translation(convexDecompositionObjectOffset), concaveShape);

                CollisionShapes.Add(concaveShape);
            }
        }
    }
}
