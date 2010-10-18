using BulletSharp;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace BasicDemo
{
    class Physics
    {
        public DynamicsWorld World;

        CollisionDispatcher Dispatcher;
        BroadphaseInterface Broadphase;
        //ConstraintSolver Solver;
        AlignedCollisionShapeArray CollisionShapes;

        ///create 125 (5x5x5) dynamic objects
        int ArraySizeX = 5, ArraySizeY = 5, ArraySizeZ = 5;

        ///scaling of the objects (0.1 = 20 centimeter boxes )
        float StartPosX = -5;
        float StartPosY = -5;
        float StartPosZ = -3;

        public Physics()
        {
            CollisionConfiguration collisionConf;

            // collision configuration contains default setup for memory, collision setup
            collisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(collisionConf);

            Broadphase = new DbvtBroadphase();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, collisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            CollisionShapes = new AlignedCollisionShapeArray();

            // create the ground
            CollisionShape groundShape = new BoxShape(50, 1, 50);
            CollisionShapes.Add(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Identity, groundShape);
            ground.UserObject = "Ground";

            // create a few dynamic rigidbodies
            float mass = 1.0f;

            CollisionShape colShape = new BoxShape(1);
            CollisionShapes.Add(colShape);
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
                        Matrix startTransform = Matrix.CreateTranslation(
                            new Vector3(
                                2*i + start_x,
                                2*k + start_y,
                                2*j + start_z
                                )
                            );

                        // using motionstate is recommended, it provides interpolation capabilities
                        // and only synchronizes 'active' objects
                        DefaultMotionState myMotionState = new DefaultMotionState(startTransform);
                        RigidBodyConstructionInfo rbInfo =
                            new RigidBodyConstructionInfo(mass, myMotionState, colShape, localInertia);
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

        public RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            bool isDynamic = (mass != 0.0f);

            Vector3 localInertia = Vector3.Zero;
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);

            RigidBodyConstructionInfo rbInfo = new RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia);
            RigidBody body = new RigidBody(rbInfo);

            World.AddRigidBody(body);

            return body;
        }

        public class PhysicsDebugDraw : DebugDraw
        {
            GraphicsDevice device;

            public PhysicsDebugDraw(GraphicsDevice device, BasicEffect effect)
            {
                this.device = device;
            }

            public override void DrawLine(Vector3 from, Vector3 to, Color color)
            {
                VertexPositionColor[] vertices = new VertexPositionColor[2];
                vertices[0] = new VertexPositionColor(from, color);
                vertices[1] = new VertexPositionColor(to, color);
                device.DrawUserPrimitives<VertexPositionColor>(PrimitiveType.LineList, vertices, 0, 1);
            }

            public void DrawDebugWorld(DynamicsWorld world)
            {
                world.DebugDrawWorld();
            }
        }
    }
}
