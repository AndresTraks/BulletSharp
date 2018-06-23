using BulletSharp;
using DemoFramework;
using System;

namespace Box2DDemo
{
    sealed class Box2DDemo : Demo
    {
        ///create 25 (5x5) dynamic objects
        const int ArraySizeX = 5, ArraySizeY = 5;
        public float Depth = 0.04f;

        private VoronoiSimplexSolver _simplexSolver;
        private ConvexPenetrationDepthSolver _penetrationDepthSolver;
        private Convex2DConvex2DAlgorithm.CreateFunc _convexAlgorithm2D;
        private Box2DBox2DCollisionAlgorithm.CreateFunc _boxAlgorithm2D;

        protected override void OnInitialize()
        {
            Freelook.Eye = new Vector3(0, 15, 20);
            Freelook.Target = new Vector3(10, 10, 0);

            Graphics.SetFormText("BulletSharp - Box 2D Demo");
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();

            // Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher.
            Dispatcher = new CollisionDispatcher(CollisionConf);
            RegisterCollisionAlgorithms();

            Broadphase = new DbvtBroadphase();

            // the default constraint solver.
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            CreateGround();
            Create2dBodies();
        }

        public override void ExitPhysics()
        {
            _simplexSolver.Dispose();
            _penetrationDepthSolver.Dispose();
            _convexAlgorithm2D.Dispose();
            _boxAlgorithm2D.Dispose();

            base.ExitPhysics();
        }

        private void RegisterCollisionAlgorithms()
        {
            _simplexSolver = new VoronoiSimplexSolver();
            _penetrationDepthSolver = new MinkowskiPenetrationDepthSolver();

            _convexAlgorithm2D = new Convex2DConvex2DAlgorithm.CreateFunc(_simplexSolver, _penetrationDepthSolver);
            _boxAlgorithm2D = new Box2DBox2DCollisionAlgorithm.CreateFunc();

            Dispatcher.RegisterCollisionCreateFunc(BroadphaseNativeType.Convex2DShape, BroadphaseNativeType.Convex2DShape, _convexAlgorithm2D);
            Dispatcher.RegisterCollisionCreateFunc(BroadphaseNativeType.Box2DShape, BroadphaseNativeType.Convex2DShape, _convexAlgorithm2D);
            Dispatcher.RegisterCollisionCreateFunc(BroadphaseNativeType.Convex2DShape, BroadphaseNativeType.Box2DShape, _convexAlgorithm2D);
            Dispatcher.RegisterCollisionCreateFunc(BroadphaseNativeType.Box2DShape, BroadphaseNativeType.Box2DShape, _boxAlgorithm2D);
        }

        private void CreateGround()
        {
            var groundShape = new BoxShape(150, 7, 150);
            var ground = LocalCreateRigidBody(0, Matrix.Identity, groundShape);
            ground.UserObject = "Ground";
        }

        private void Create2dBodies()
        {
            // Re-using the same collision is better for memory usage and performance
            float u = 0.96f;
            Vector3[] points = { new Vector3(0, u, 0), new Vector3(-u, -u, 0), new Vector3(u, -u, 0) };
            var childShape0 = new BoxShape(1, 1, Depth);
            var colShape = new Convex2DShape(childShape0);
            var childShape1 = new ConvexHullShape(points);
            var colShape2 = new Convex2DShape(childShape1);
            var childShape2 = new CylinderShapeZ(1, 1, Depth);
            var colShape3 = new Convex2DShape(childShape2);

            colShape.Margin = 0.03f;

            float mass = 1.0f;
            Vector3 localInertia = colShape.CalculateLocalInertia(mass);

            var rbInfo = new RigidBodyConstructionInfo(mass, null, null, localInertia);

            Vector3 x = new Vector3(-ArraySizeX, 8, -20);
            Vector3 y;
            Vector3 deltaX = new Vector3(1, 2, 0);
            Vector3 deltaY = new Vector3(2, 0, 0);

            for (int i = 0; i < ArraySizeY; i++)
            {
                y = x;
                for (int j = 0; j < ArraySizeX; j++)
                {
                    Matrix startTransform = Matrix.Translation(y - new Vector3(-10, 0, 0));

                    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
                    rbInfo.MotionState = new DefaultMotionState(startTransform);

                    switch (j % 3)
                    {
                        case 0:
                            rbInfo.CollisionShape = colShape;
                            break;
                        case 1:
                            rbInfo.CollisionShape = colShape3;
                            break;
                        default:
                            rbInfo.CollisionShape = colShape2;
                            break;
                    }
                    var body = new RigidBody(rbInfo)
                    {
                        //ActivationState = ActivationState.IslandSleeping,
                        LinearFactor = new Vector3(1, 1, 0),
                        AngularFactor = new Vector3(0, 0, 1)
                    };

                    World.AddRigidBody(body);

                    y += deltaY;
                }
                x += deltaX;
            }

            rbInfo.Dispose();
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new Box2DDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
