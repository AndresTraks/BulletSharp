using BulletSharp;
using DemoFramework;
using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace MultiThreadedDemo
{
    internal class MultiThreadedDemo : Demo
    {
        private const float Scale = 0.5f;
        private const int NumBoxesX = 7, NumBoxesY = 7, NumBoxesZ = 7;
        private const int NumStacksX = 5, NumStacksZ = 5;
        private const float StackSpacingX = 50 * Scale;
        private const float StackSpacingZ = 50 * Scale;
        private Vector3 _startPosition = new Vector3(0, 20, -40);
        private const int MaxThreadCount = 64;
        private ConstraintSolverPoolMultiThreaded _constraintSolver;
        private List<TaskScheduler> _schedulers = new List<TaskScheduler>();
        private int _currentScheduler = 0;

        private Vector3 eye = new Vector3(-100, 100, -100) * Scale;
        private Vector3 target = new Vector3(0, 50, -30) * Scale;

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - Multi-threaded Demo");
            SetDemoText();

            var scheduler = Threads.TaskScheduler;
        }

        public override void OnHandleInput()
        {
            base.OnHandleInput();


            if (Input.KeysPressed.Count != 0)
            {
                switch (Input.KeysPressed[0])
                {
                    case Keys.T:
                        NextTaskScheduler();
                        SetDemoText();
                        break;
                }
            }
        }

        private void SetDemoText()
        {
            var scheduler = Threads.TaskScheduler;
            DemoText = $"T - Scheduler: {scheduler.Name}\n{scheduler.NumThreads}/{scheduler.MaxNumThreads} threads";
        }

        protected override void OnInitializePhysics()
        {
            CreateSchedulers();
            NextTaskScheduler();

            using (var collisionConfigurationInfo = new DefaultCollisionConstructionInfo
            {
                DefaultMaxPersistentManifoldPoolSize = 80000,
                DefaultMaxCollisionAlgorithmPoolSize = 80000
            })
            {
                CollisionConf = new DefaultCollisionConfiguration(collisionConfigurationInfo);
            };
            Dispatcher = new CollisionDispatcherMultiThreaded(CollisionConf);
            Broadphase = new DbvtBroadphase();
            _constraintSolver = new ConstraintSolverPoolMultiThreaded(MaxThreadCount);
            World = new DiscreteDynamicsWorldMultiThreaded(Dispatcher, Broadphase, _constraintSolver, CollisionConf);
            World.SolverInfo.SolverMode = SolverModes.Simd | SolverModes.UseWarmStarting;

            CreateGround();
            CreateBoxes();
        }

        public void NextTaskScheduler()
        {
            _currentScheduler++;
            if (_currentScheduler >= _schedulers.Count)
            {
                _currentScheduler = 0;
            }
            TaskScheduler scheduler = _schedulers[_currentScheduler];
            scheduler.NumThreads = scheduler.MaxNumThreads;
            Threads.TaskScheduler = scheduler;
        }

        private void CreateSchedulers()
        {
            AddScheduler(Threads.GetSequentialTaskScheduler());
            AddScheduler(Threads.GetOpenMPTaskScheduler());
            AddScheduler(Threads.GetTbbTaskScheduler());
            AddScheduler(Threads.GetPplTaskScheduler());
        }

        private void AddScheduler(TaskScheduler scheduler)
        {
            if (scheduler != null)
            {
                _schedulers.Add(scheduler);
            }
        }

        private void CreateGround()
        {
            var groundShape = new BoxShape(Scale * new Vector3(400, 1, 400));
            //var groundShape = new StaticPlaneShape(Vector3.UnitY, Scale);

            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Identity, groundShape);
            ground.Friction = 1;
            ground.UserObject = "Ground";
        }

        private void CreateBoxes()
        {
            const float mass = 1.0f;
            var shape = new BoxShape(Scale);
            Vector3 localInertia = shape.CalculateLocalInertia(mass);

            using (var bodyInfo = new RigidBodyConstructionInfo(mass, null, shape, localInertia))
            {
                for (int x = 0; x < NumStacksX; x++)
                {
                    for (int z = 0; z < NumStacksZ; z++)
                    {
                        Vector3 offset = _startPosition + new Vector3(x * StackSpacingX, 0, z * StackSpacingZ);
                        CreateStack(offset, bodyInfo);
                    }
                }
            }
        }

        private void CreateStack(Vector3 offset, RigidBodyConstructionInfo bodyInfo)
        {
            for (int y = 0; y < NumBoxesY; y++)
            {
                for (int x = 0; x < NumBoxesX; x++)
                {
                    for (int z = 0; z < NumBoxesZ; z++)
                    {
                        Vector3 position = offset + Scale * 2 * new Vector3(x, y, z);

                        bodyInfo.MotionState = new DefaultMotionState(Matrix.Translation(position));
                        var body = new RigidBody(bodyInfo);

                        World.AddRigidBody(body);
                    }
                }
            }
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new MultiThreadedDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
