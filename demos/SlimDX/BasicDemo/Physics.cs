using BulletSharp;
using DemoFramework;
using System;
using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;

namespace BasicDemo
{
    class Physics
    {
        ///create 125 (5x5x5) dynamic objects
        int ArraySizeX = 5, ArraySizeY = 5, ArraySizeZ = 5;

        ///scaling of the objects (0.1 = 20 centimeter boxes )
        public float Scaling = 1;
        float StartPosX = -5;
        float StartPosY = -5;
        float StartPosZ = -3;

        CollisionDispatcher dispatcher;
        BroadphaseInterface broadphase;
        ConstraintSolver solver;
        AlignedObjectArray<CollisionShape> collisionShapes = new AlignedObjectArray<CollisionShape>();
        public DynamicsWorld world;

        public Physics()
        {
            CollisionConfiguration collisionConf;

            // collision configuration contains default setup for memory, collision setup
            collisionConf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(collisionConf);

            broadphase = new DbvtBroadphase();

            // the default constraint solver.
            solver = new SequentialImpulseConstraintSolver();

            world = new DiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConf);
            world.Gravity = new Vector3(0, -10, 0);

            // create a few basic rigid bodies
            CollisionShape groundShape = new BoxShape(50, 50, 50);
            collisionShapes.PushBack(groundShape);
            LocalCreateRigidBody(0, Matrix.Translation(0, -50, 0), groundShape);

            // create a few dynamic rigidbodies
            float mass = 1.0f;

            CollisionShape colShape = new BoxShape(Scaling, Scaling, Scaling);
            collisionShapes.PushBack(colShape);
            Vector3 localInertia = colShape.CalculateLocalInertia(mass);

            float start_x = StartPosX - ArraySizeX / 2;
            float start_y = StartPosY;
            float start_z = StartPosZ - ArraySizeZ / 2;

            int k, i, j;
            for (k = 0; k < ArraySizeY; k++)
            {
                for (i = 0; i < ArraySizeX; i++)
                {
                    for (j = 0; j < ArraySizeZ; j++)
                    {
                        Matrix startTransform = Matrix.Translation(
                            Scaling * new Vector3(
                                2 * i + start_x,
                                20 + 2 * k + start_y,
                                2 * j + start_z
                                )
                            );

                        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
                        DefaultMotionState myMotionState = new DefaultMotionState(startTransform);
                        RigidBodyConstructionInfo rbInfo = new RigidBodyConstructionInfo(mass, myMotionState, colShape, localInertia);
                        RigidBody body = new RigidBody(rbInfo);

                        world.AddRigidBody(body);
                    }
                }
            }

            world.Broadphase.ResetPool(dispatcher);
            solver.Reset();
        }

        public void Update(float elapsedTime)
        {
            world.StepSimulation(elapsedTime);
        }

        public RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            bool isDynamic = (mass != 0.0f);

            Vector3 localInertia = new Vector3(0, 0, 0);
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);

            RigidBodyConstructionInfo rbInfo = new RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia);
            RigidBody body = new RigidBody(rbInfo);

            world.AddRigidBody(body);

            return body;
        }
    }
}
