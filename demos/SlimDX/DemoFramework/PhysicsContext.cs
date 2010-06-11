using BulletSharp;
using SlimDX;
using SlimDX.Direct3D9;
using System;

namespace DemoFramework
{
    public class PhysicsContext
    {
        public DynamicsWorld World;
        public bool IsDebugDrawEnabled { get; private set; }

        protected CollisionDispatcher Dispatcher;
        protected BroadphaseInterface Broadphase;
        protected ConstraintSolver Solver;
        protected CollisionShapeArray CollisionShapes;

        public PhysicsDebugDraw DebugDrawer
        {
            get { return (PhysicsDebugDraw)World.DebugDrawer; }
            private set { World.DebugDrawer = value; }
        }
        BoxShape shootBoxShape;

        public PhysicsContext()
        {
            CollisionShapes = new CollisionShapeArray();
        }

        public void SetDebugDrawMode(Device device, DebugDrawModes modes)
        {
            if (World == null)
                throw new System.Exception("Physics world not initialized.");

            if (modes == 0)
            {
                if (DebugDrawer != null)
                    DebugDrawer.DebugMode = DebugDrawModes.None;
                IsDebugDrawEnabled = false;
            }
            else
            {
                if (DebugDrawer == null)
                {
                    DebugDrawer = new PhysicsDebugDraw(device);
                    World.DebugDrawer = DebugDrawer;
                }
                DebugDrawer.DebugMode = modes;
                IsDebugDrawEnabled = true;
            }
        }

        public void SetDebugDrawer(PhysicsDebugDraw debugDraw)
        {
            if (World == null)
                throw new System.Exception("Physics world not initialized.");

            DebugDrawer = debugDraw;
            IsDebugDrawEnabled = (debugDraw != null);
        }

        public void SetDebugDraw(PhysicsDebugDraw debugDraw, DebugDrawModes modes)
        {
            debugDraw.DebugMode = modes;
            SetDebugDrawer(debugDraw);
        }

        public void DebugDrawWorld()
        {
            if (IsDebugDrawEnabled)
                DebugDrawer.DrawDebugWorld(World);
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

            RigidBody.RigidBodyConstructionInfo rbInfo = new RigidBody.RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia);
            RigidBody body = new RigidBody(rbInfo);

            World.AddRigidBody(body);

            return body;
        }

        public void ShootBox(Vector3 camPos, Vector3 destination)
        {
	        if (World == null)
                return;
	        
            float mass = 1.0f;
            float speed = 10;

            if (shootBoxShape == null)
                shootBoxShape = new BoxShape(0.5f);

	        RigidBody body = LocalCreateRigidBody(mass, Matrix.Translation(camPos), shootBoxShape);
            body.LinearFactor = new Vector3(1,1,1);
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
