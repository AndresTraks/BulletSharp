using BulletSharp;
using OpenTK;
//using OpenTK.Graphics;

namespace BasicDemo
{
    class Physics
    {
        ///create 125 (5x5x5) dynamic objects
        int ArraySizeX = 5, ArraySizeY = 5, ArraySizeZ = 5;

        ///scaling of the objects (0.1 = 20 centimeter boxes )
        float StartPosX = -5;
        float StartPosY = -5;
        float StartPosZ = -3;

        public DiscreteDynamicsWorld World { get; set; }
        CollisionDispatcher dispatcher;
        CollisionShapeArray collisionShapes = new CollisionShapeArray();

        public Physics()
        {
            CollisionConfiguration collisionConf;

            // collision configuration contains default setup for memory, collision setup
            collisionConf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(collisionConf);

            World = new DiscreteDynamicsWorld(dispatcher, new DbvtBroadphase(), null, collisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            // create the ground
            CollisionShape groundShape = new BoxShape(50, 50, 50);
            collisionShapes.PushBack(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix4.CreateTranslation(0, -50, 0), groundShape);
            ground.UserObject = "Ground";

            // create a few dynamic rigidbodies
            float mass = 1.0f;

            CollisionShape colShape = new BoxShape(1);
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
                        Matrix4 startTransform = Matrix4.CreateTranslation(
                            new Vector3(
                                2*i + start_x,
                                2*k + start_y,
                                2*j + start_z
                                )
                            );

                        // using motionstate is recommended, it provides interpolation capabilities
                        // and only synchronizes 'active' objects
                        DefaultMotionState myMotionState = new DefaultMotionState(startTransform);
                        RigidBody.RigidBodyConstructionInfo rbInfo =
                            new RigidBody.RigidBodyConstructionInfo(mass, myMotionState, colShape, localInertia);
                        RigidBody body = new RigidBody(rbInfo);
                        
                        // make it drop from a height
                        body.Translate(new Vector3(0, 20, 0));

                        World.AddRigidBody(body);
                    }
                }
            }
        }

        public virtual void Update(float elapsedTime)
        {
            World.StepSimulation(elapsedTime);
        }

        public RigidBody LocalCreateRigidBody(float mass, Matrix4 startTransform, CollisionShape shape)
        {
            bool isDynamic = (mass != 0.0f);

            Vector3 localInertia = Vector3.Zero;
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);

            RigidBody.RigidBodyConstructionInfo rbInfo = new RigidBody.RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia);
            RigidBody body = new RigidBody(rbInfo);

            World.AddRigidBody(body);

            return body;
        }
    }
}
