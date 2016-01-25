﻿using BulletSharp;
using SharpDX;
using System.Collections.Generic;

namespace DemoFramework
{
    public class PhysicsContext : System.IDisposable
    {
        DynamicsWorld _world;
        public DynamicsWorld World
        {
            get { return _world; }
            protected set { _world = value; }
        }

        protected CollisionConfiguration CollisionConf;
        protected CollisionDispatcher Dispatcher;
        protected BroadphaseInterface Broadphase;
        protected ConstraintSolver Solver;
        public List<CollisionShape> CollisionShapes { get; private set; }

        protected BoxShape shootBoxShape;
        protected float shootBoxInitialSpeed = 40;

        public PhysicsContext()
        {
            CollisionShapes = new List<CollisionShape>();

            InitPhysics();
        }

        public virtual void InitPhysics()
        {
        }

        public void ExitPhysics()
        {
            //removed/dispose constraints
            int i;
            for (i = _world.NumConstraints - 1; i >= 0; i--)
            {
                TypedConstraint constraint = _world.GetConstraint(i);
                _world.RemoveConstraint(constraint);
                constraint.Dispose(); ;
            }

            //remove the rigidbodies from the dynamics world and delete them
            for (i = _world.NumCollisionObjects - 1; i >= 0; i--)
            {
                CollisionObject obj = _world.CollisionObjectArray[i];
                RigidBody body = obj as RigidBody;
                if (body != null && body.MotionState != null)
                {
                    body.MotionState.Dispose();
                }
                _world.RemoveCollisionObject(obj);
                obj.Dispose();
            }

            //delete collision shapes
            foreach (CollisionShape shape in CollisionShapes)
                shape.Dispose();
            CollisionShapes.Clear();

            _world.Dispose();
            Broadphase.Dispose();
            Dispatcher.Dispose();
            CollisionConf.Dispose();
        }

        public void ClientResetScene()
        {
            ExitPhysics();
            InitPhysics();
        }

        public virtual void Dispose()
        {
            ExitPhysics();
        }

        public virtual int Update(float elapsedTime)
        {
            return _world.StepSimulation(elapsedTime);
        }

        public virtual RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            //rigidbody is dynamic if and only if mass is non zero, otherwise static
            bool isDynamic = (mass != 0.0f);

            Vector3 localInertia = Vector3.Zero;
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);

            RigidBody body;
            using (var rbInfo = new RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia))
            {
                body = new RigidBody(rbInfo);
            }

            _world.AddRigidBody(body);

            return body;
        }

        public virtual void ShootBox(Vector3 camPos, Vector3 destination)
        {
            if (_world == null)
                return;

            float mass = 1.0f;

            if (shootBoxShape == null)
            {
                shootBoxShape = new BoxShape(1.0f);
                shootBoxShape.InitializePolyhedralFeatures();
            }

            RigidBody body = LocalCreateRigidBody(mass, Matrix.Translation(camPos), shootBoxShape);
            body.LinearFactor = new Vector3(1, 1, 1);
            //body.Restitution = 1;

            Vector3 linVel = destination - camPos;
            linVel.Normalize();

            body.LinearVelocity = linVel * shootBoxInitialSpeed;
            body.CcdMotionThreshold = 0.5f;
            body.CcdSweptSphereRadius = 0.9f;
        }
    };
};
