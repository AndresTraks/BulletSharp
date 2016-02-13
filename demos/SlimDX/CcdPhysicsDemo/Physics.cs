using BulletSharp;
using DemoFramework;
using SlimDX;

namespace CcdPhysicsDemo
{
    class Physics : PhysicsContext
    {
        bool ccdMode = true;
        public bool CcdMode => ccdMode;

        float CubeHalfExtents = 0.5f;
        //Vector3 comOffsetVec = new Vector3(0, 2, 0);
        float ExtraHeight = 1.0f;

        public void ToggleCcdMode()
        {
            ccdMode = !ccdMode;

            ClientResetScene();
        }

        public override void InitPhysics()
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
//            ground.InitializePolyhedralFeatures();
            CollisionShapes.Add(ground);
            RigidBody body = LocalCreateRigidBody(0, Matrix.Identity, ground);
            body.UserObject = "Ground";

            CollisionShape shape = new CylinderShape(CubeHalfExtents, CubeHalfExtents, CubeHalfExtents);
            CollisionShapes.Add(shape);

            int numObjects = 120;
            for (i = 0; i < numObjects; i++)
            {
                //stack them
                int colsize = 10;
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

                if (ccdMode)
                {
                    body.CcdMotionThreshold = CubeHalfExtents;
                    body.CcdSweptSphereRadius = 0.9f * CubeHalfExtents;
                }
            }
        }

        public override void ShootBox(Vector3 camPos, Vector3 destination)
        {
            if (World != null)
            {
                float mass = 1.0f;

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

                ///when using m_ccdMode, disable regular CCD
                if (ccdMode)
                {
                    body.CcdMotionThreshold = CubeHalfExtents;
                    body.CcdSweptSphereRadius = 0.4f;
                }
            }
        }
    }
}
