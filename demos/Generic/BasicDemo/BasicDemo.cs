using System;
using BulletSharp;
using DemoFramework;

namespace BasicDemo
{
    sealed class BasicDemo : Demo
    {
        // create 125 (5x5x5) dynamic objects
        private const int ArraySizeX = 5, ArraySizeY = 5, ArraySizeZ = 5;
        private Vector3 startPosition = new Vector3(0, 2, 0);

        protected override void OnInitialize()
        {
            Freelook.Eye = new Vector3(30, 20, 15);
            Freelook.Target = new Vector3(0, 3, 0);

            Graphics.SetFormText("BulletSharp - Basic Demo");
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new DbvtBroadphase();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            CreateGround();
            CreateBoxes();
        }

        private void CreateGround()
        {
            var groundShape = new BoxShape(50, 1, 50);
            //groundShape.InitializePolyhedralFeatures();
            //var groundShape = new StaticPlaneShape(Vector3.UnitY, 1);

            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Identity, groundShape);
            ground.UserObject = "Ground";
        }

        private void CreateBoxes()
        {
            const float mass = 1.0f;
            var colShape = new BoxShape(1);
            Vector3 localInertia = colShape.CalculateLocalInertia(mass);

            var rbInfo = new RigidBodyConstructionInfo(mass, null, colShape, localInertia);

            for (int y = 0; y < ArraySizeY; y++)
            {
                for (int x = 0; x < ArraySizeX; x++)
                {
                    for (int z = 0; z < ArraySizeZ; z++)
                    {
                        Vector3 position = startPosition + 2 * new Vector3(x, y, z);

                        // make it drop from a height
                        position += new Vector3(0, 10, 0);

                        // using MotionState is recommended, it provides interpolation capabilities
                        // and only synchronizes 'active' objects
                        rbInfo.MotionState = new DefaultMotionState(Matrix.Translation(position));
                        var body = new RigidBody(rbInfo);

                        World.AddRigidBody(body);
                    }
                }
            }

            rbInfo.Dispose();
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new BasicDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
