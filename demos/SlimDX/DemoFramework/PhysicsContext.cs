using BulletSharp;
using SlimDX;

namespace DemoFramework
{
    public class PhysicsContext : System.IDisposable
    {
        public DynamicsWorld World { get; protected set; }

        protected CollisionConfiguration CollisionConf;
        protected CollisionDispatcher Dispatcher;
        protected BroadphaseInterface Broadphase;
        protected ConstraintSolver Solver;
        protected AlignedCollisionShapeArray CollisionShapes = new AlignedCollisionShapeArray();

        BoxShape shootBoxShape;

        public PhysicsContext()
        {
        }

        public virtual void Dispose()
        {
            //removed/dispose constraints
            int i;
            for (i = World.NumConstraints - 1; i >= 0; i--)
            {
                TypedConstraint constraint = World.GetConstraint(i);
                World.RemoveConstraint(constraint);
                constraint.Dispose(); ;
            }

            //remove the rigidbodies from the dynamics world and delete them
            for (i = World.NumCollisionObjects - 1; i >= 0; i--)
            {
                CollisionObject obj = World.CollisionObjectArray[i];
                RigidBody body = RigidBody.Upcast(obj);
                if (body != null && body.MotionState != null)
                {
                    body.MotionState.Dispose();
                }
                World.RemoveCollisionObject(obj);
                obj.Dispose();
            }

            //delete collision shapes
            for (int j = 0; j < CollisionShapes.Count; j++)
            {
                CollisionShape shape = CollisionShapes[j];
                CollisionShapes[j] = null;
                shape.Dispose();
            }

            World.Dispose();
            Broadphase.Dispose();
            Dispatcher.Dispose();
            CollisionConf.Dispose();
        }

        public virtual int Update(float elapsedTime)
        {
            return World.StepSimulation(elapsedTime);
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

        public void ShootBox(Vector3 camPos, Vector3 destination)
        {
            if (World == null)
                return;

            float mass = 1.0f;
            float speed = 40;

            if (shootBoxShape == null)
                shootBoxShape = new BoxShape(1.0f);

            RigidBody body = LocalCreateRigidBody(mass, Matrix.Translation(camPos), shootBoxShape);
            body.LinearFactor = new Vector3(1, 1, 1);
            //body.Restitution = 1;

            Vector3 linVel = destination - camPos;
            linVel.Normalize();

            body.LinearVelocity = linVel * speed;
            body.CcdMotionThreshold = 1;
            body.CcdSweptSphereRadius = 0.2f;

            Broadphase.ResetPool(Dispatcher);
        }
    };
};
