using BulletSharp;
using DemoFramework;
using System;
using System.Windows.Forms;

namespace CcdPhysicsDemo
{
    sealed class CcdPhysicsDemo : Demo
    {
        private bool _ccdMode = true;

        private const float CubeHalfExtents = 1.0f;
        private const float ExtraHeight = 1.0f;

        private const float ShootBoxInitialSpeed = 4000;

        private void ToggleCcdMode()
        {
            _ccdMode = !_ccdMode;

            if (_ccdMode)
            {
                DemoText = "CCD enabled (P to disable)";
            }
            else
            {
                DemoText = "CCD enabled (P to enable)";
            }

            ClientResetScene();
        }

        protected override void OnInitialize()
        {
            Freelook.Eye = new Vector3(0, 20, 80);
            Freelook.Target = Vector3.Zero;

            Graphics.SetFormText("BulletSharp - CCD Demo");
            DemoText = "CCD enabled (P to disable)";
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
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();

            Dispatcher = new CollisionDispatcher(CollisionConf);
            //Dispatcher.RegisterCollisionCreateFunc(BroadphaseNativeType.BoxShape, BroadphaseNativeType.BoxShape,
            //    CollisionConf.GetCollisionAlgorithmCreateFunc(BroadphaseNativeType.ConvexShape, BroadphaseNativeType.ConvexShape));

            Broadphase = new DbvtBroadphase();

            // the default constraint solver
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.SolverInfo.SolverMode |= SolverModes.Use2FrictionDirections | SolverModes.RandomizeOrder;
            //World.SolverInfo.SplitImpulse = 0;
            World.SolverInfo.NumIterations = 20;

            World.DispatchInfo.UseContinuous = _ccdMode;

            World.Gravity = new Vector3(0, -10, 0);

            CreateGround();
            CreateBoxStack();
        }

        private void CreateGround()
        {
            BoxShape ground = new BoxShape(200, 1, 200);
            ground.InitializePolyhedralFeatures();
            RigidBody body = LocalCreateRigidBody(0, Matrix.Identity, ground);
            body.Friction = 0.5f;
            //body.RollingFriction = 0.3f;
            body.UserObject = "Ground";
        }

        private void CreateBoxStack()
        {
            //var shape = new CylinderShape(CubeHalfExtents, CubeHalfExtents, CubeHalfExtents);
            var shape = new BoxShape(CubeHalfExtents);

            const int numObjects = 120;
            for (int i = 0; i < numObjects; i++)
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

                RigidBody body = LocalCreateRigidBody(1, trans, shape);
                body.SetAnisotropicFriction(shape.AnisotropicRollingFrictionDirection, AnisotropicFrictionFlags.AnisotropicRollingFriction);
                body.Friction = 0.5f;
                //body.RollingFriction = 0.3f;

                if (_ccdMode)
                {
                    body.CcdMotionThreshold = 1e-7f;
                    body.CcdSweptSphereRadius = 0.9f * CubeHalfExtents;
                }
            }
        }

        public override void ShootBox(Vector3 camPos, Vector3 destination)
        {
            const float mass = 1.0f;

            if (_shootBoxShape == null)
            {
                _shootBoxShape = new BoxShape(1.0f);
                _shootBoxShape.InitializePolyhedralFeatures();
            }

            RigidBody body = LocalCreateRigidBody(mass, Matrix.Translation(camPos), _shootBoxShape);
            body.LinearFactor = new Vector3(1, 1, 1);
            //body.Restitution = 1;

            Vector3 linVel = destination - camPos;
            linVel.Normalize();
            body.LinearVelocity = linVel * ShootBoxInitialSpeed;
            body.AngularVelocity = Vector3.Zero;
            body.ContactProcessingThreshold = 1e30f;

            // when using ccdMode, disable regular CCD
            if (_ccdMode)
            {
                body.CcdMotionThreshold = 0.0001f;
                body.CcdSweptSphereRadius = 0.4f;
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
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
