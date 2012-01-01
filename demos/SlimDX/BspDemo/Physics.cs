using BulletSharp;
using DemoFramework;
using SlimDX;

namespace BspDemo
{
    public class BspToBulletConverter : BspConverter
    {
        PhysicsContext context;

        public BspToBulletConverter(PhysicsContext context)
        {
            this.context = context;
        }

        public override void AddConvexVerticesCollider(AlignedVector3Array vertices, bool isEntity, Vector3 entityTargetLocation)
        {
            // perhaps we can do something special with entities (isEntity)
            // like adding a collision Triggering (as example)

            if (vertices.Count == 0)
                return;

            float mass = 0.0f;
            //can use a shift
            Matrix startTransform = Matrix.Translation(0, 0, -10.0f);
            CollisionShape shape = new ConvexHullShape(vertices);
            context.CollisionShapes.Add(shape);

            context.LocalCreateRigidBody(mass, startTransform, shape);
        }
    }

    class Physics : PhysicsContext
    {
        public Physics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new DbvtBroadphase();
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.Gravity = new Vector3(0, 0, -10);

            BspLoader bspLoader = new BspLoader();
            bspLoader.LoadBspFile("BspDemo.bsp");
            BspConverter bsp2Bullet = new BspToBulletConverter(this);
            bsp2Bullet.ConvertBsp(bspLoader, 0.1f);
        }
    }
}
