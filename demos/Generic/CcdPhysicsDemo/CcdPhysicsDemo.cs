﻿using System;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;

namespace CcdPhysicsDemo
{
    class CcdPhysicsDemo : Demo
    {
        bool ccdMode = true;

        Vector3 eye = new Vector3(0, 10, 40);
        Vector3 target = Vector3.Zero;

        const float CubeHalfExtents = 0.5f;
        const float ExtraHeight = 1.0f;

        string infoText = "Move using mouse and WASD+shift\n" +
            "F3 - Toggle debug\n" +
            //"F11 - Toggle fullscreen\n" +
            "Space - Shoot box";

        void ToggleCcdMode()
        {
            ccdMode = !ccdMode;

            if (ccdMode)
            {
                Graphics.SetInfoText(infoText + "\nCCD enabled (P to disable)");
            }
            else
            {
                Graphics.SetInfoText(infoText + "\nCCD disabled (P to enable)");
            }

            ClientResetScene();
        }

        void CreateStack(CollisionShape boxShape, int size, float zPos)
        {
            Matrix trans;
            const float mass = 1.0f;

            for (int i = 0; i < size; i++)
            {
                // This constructs a row, from left to right
                int rowSize = size - i;
                for (int j = 0; j < rowSize; j++)
                {
                    trans = Matrix.Translation(
                        -rowSize * CubeHalfExtents + CubeHalfExtents + j * 2.0f * CubeHalfExtents,
                        CubeHalfExtents + i * CubeHalfExtents * 2.0f,
                        zPos);

                    RigidBody body = LocalCreateRigidBody(mass, trans, boxShape);
                    body.ActivationState = ActivationState.IslandSleeping;
                }
            }
        }

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - CCD Demo");
            Graphics.SetInfoText(infoText + "\nCCD enabled (P to disable)");
        }

        public override void OnHandleInput()
        {
            if (Input.KeysPressed.Contains(Keys.P))
            {
                ToggleCcdMode();
            }

            base.OnHandleInput();
        }

        protected override void OnInitializePhysics()
        {
            int i;

            shootBoxInitialSpeed = 4000;

            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();

            Dispatcher = new CollisionDispatcher(CollisionConf);
            Dispatcher.RegisterCollisionCreateFunc(BroadphaseNativeType.BoxShape, BroadphaseNativeType.BoxShape,
                CollisionConf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.ConvexShape, BroadphaseNativeType.ConvexShape));

            Broadphase = new DbvtBroadphase();


            // the default constraint solver.
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.SolverInfo.SplitImpulse = 1;
            World.SolverInfo.NumIterations = 20;

            World.DispatchInfo.UseContinuous = ccdMode;

            World.Gravity = new Vector3(0, -10, 0);

            BoxShape ground = new BoxShape(200, 1, 200);
            ground.InitializePolyhedralFeatures();
            CollisionShapes.Add(ground);
            RigidBody body = LocalCreateRigidBody(0, Matrix.Identity, ground);
            body.UserObject = "Ground";

            CollisionShape shape = new CylinderShape(CubeHalfExtents, CubeHalfExtents, CubeHalfExtents);
            CollisionShapes.Add(shape);

            const int numObjects = 120;
            for (i = 0; i < numObjects; i++)
            {
                //stack them
                const int colsize = 10;
                int row = (int)((i * CubeHalfExtents * 2) / (colsize * 2 * CubeHalfExtents));
                int row2 = row;
                int col = (i) % (colsize) - colsize / 2;

                if (col > 3)
                {
                    col = 11;
                    row2 |= 1;
                }

                Matrix trans = Matrix.Translation(col * 2 * CubeHalfExtents + (row2 % 2) * CubeHalfExtents,
                    row * 2 * CubeHalfExtents + CubeHalfExtents + ExtraHeight, 0);

                body = LocalCreateRigidBody(1, trans, shape);
                body.SetAnisotropicFriction(shape.AnisotropicRollingFrictionDirection, AnisotropicFrictionFlags.AnisotropicRollingFriction);
                body.RollingFriction = 0.3f;

                if (ccdMode)
                {
                    body.CcdMotionThreshold = 1e-7f;
                    body.CcdSweptSphereRadius = 0.9f * CubeHalfExtents;
                }
            }
        }

        public override void ShootBox(Vector3 camPos, Vector3 destination)
        {
            if (World != null)
            {
                const float mass = 1.0f;

                if (shootBoxShape == null)
                {
                    shootBoxShape = new BoxShape(1.0f);
                    shootBoxShape.InitializePolyhedralFeatures();
                }

                RigidBody body = LocalCreateRigidBody(mass, Matrix.Translation(camPos), shootBoxShape);
                body.LinearFactor = new Vector3(1, 1, 1);
                //body->setRestitution(1);

                Vector3 linVel = destination - camPos;
                linVel.Normalize();
                body.LinearVelocity = linVel * shootBoxInitialSpeed;
                body.AngularVelocity = Vector3.Zero;
                body.ContactProcessingThreshold = 1e30f;

                // when using m_ccdMode, disable regular CCD
                if (ccdMode)
                {
                    body.CcdMotionThreshold = 0.0001f;
                    body.CcdSweptSphereRadius = 0.4f;
                }
            }
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new CcdPhysicsDemo())
            {
                LibraryManager.Initialize(demo);
            }
        }
    }
}
