using System.Collections.Generic;
using BulletSharp;
using SlimDX;

namespace SimplestDemo
{
    class Physics
    {
        public DiscreteDynamicsWorld World { get; private set; }
        List<CollisionShape> collisionShapes = new List<CollisionShape>();

        public Physics()
        {
            CollisionConfiguration collisionConf = new DefaultCollisionConfiguration();
            CollisionDispatcher dispatcher = new CollisionDispatcher(collisionConf);

            World = new DiscreteDynamicsWorld(dispatcher, new DbvtBroadphase(), null, collisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            // create the ground
            CollisionShape groundShape = new BoxShape(50, 1, 50);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Identity, groundShape);
            ground.UserObject = "Ground";

            // create a box
            CollisionShape boxShape = new BoxShape(1);
            LocalCreateRigidBody(1.0f, Matrix.Translation(0, 20, 0), boxShape);
        }

        public virtual void Update(float elapsedTime)
        {
            World.StepSimulation(elapsedTime);
        }

        public RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            collisionShapes.Add(shape);

            bool isDynamic = (mass != 0.0f);

            Vector3 localInertia = Vector3.Zero;
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);

            RigidBody body;
            using (var rbInfo = new RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia))
            {
                body = new RigidBody(rbInfo);
            }

            World.AddRigidBody(body);

            return body;
        }
    }
}
