using System;
using System.IO;
using BulletSharp;
using BulletSharp.Serialize;
using DemoFramework;
using System.Collections.Generic;

namespace SerializeDemo
{
    class CustomBulletWorldImporter : BulletWorldImporter
    {
        public CustomBulletWorldImporter(DynamicsWorld world)
            : base(world)
        {
        }

        public override RigidBody CreateRigidBody(bool isDynamic, float mass, Matrix startTransform, CollisionShape shape, string bodyName)
        {
            RigidBody body = base.CreateRigidBody(isDynamic, mass, startTransform, shape, bodyName);

            if (bodyName != null && bodyName.Equals("GroundName"))
                body.UserObject = "Ground";

            if (shape.ShapeType == BroadphaseNativeType.StaticPlaneShape)
                body.UserObject = "Ground";

            return body;
        }
    }

    sealed class SerializeDemo : Demo
    {
        ///create 125 (5x5x5) dynamic objects
        private const int ArraySizeX = 5, ArraySizeY = 5, ArraySizeZ = 5;

        ///scaling of the objects (0.1 = 20 centimeter boxes )
        private float StartPosX = -5;
        private float StartPosY = -5;
        private float StartPosZ = -3;

        private BulletWorldImporter _fileLoader;

        private List<CollisionShape> _collisionShapes = new List<CollisionShape>();

        protected override void OnInitialize()
        {
            Freelook.Eye = new Vector3(30, 20, 10);
            Freelook.Target = new Vector3(0, 5, 0);

            Graphics.SetFormText("BulletSharp - Serialize Demo");
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new DbvtBroadphase();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            GImpactCollisionAlgorithm.RegisterAlgorithm(Dispatcher);

            string bulletFile;
            string[] args = Environment.GetCommandLineArgs();
            if (args.Length == 1)
            {
                bulletFile = "testFile.bullet";
            }
            else
            {
                bulletFile = args[1];
            }

            _fileLoader = new CustomBulletWorldImporter(World);
            if (!_fileLoader.LoadFile(bulletFile))
            {
                CollisionShape groundShape = new BoxShape(50);
                _collisionShapes.Add(groundShape);
                RigidBody ground = LocalCreateRigidBody(0, Matrix.Translation(0, -50, 0), groundShape);
                ground.UserObject = "Ground";

                // create a few dynamic rigidbodies
                float mass = 1.0f;

                Vector3[] positions = new Vector3[2] { new Vector3(0.1f, 0.2f, 0.3f), new Vector3(0.4f, 0.5f, 0.6f) };
                float[] radi = new float[2] { 0.3f, 0.4f };

                CollisionShape colShape = new MultiSphereShape(positions, radi);

                //CollisionShape colShape = new CapsuleShapeZ(1, 1);
                //CollisionShape colShape = new CylinderShapeZ(1, 1, 1);
                //CollisionShape colShape = new BoxShape(1);
                //CollisionShape colShape = new SphereShape(1);
                _collisionShapes.Add(colShape);

                Vector3 localInertia = colShape.CalculateLocalInertia(mass);

                float start_x = StartPosX - ArraySizeX / 2;
                float start_y = StartPosY;
                float start_z = StartPosZ - ArraySizeZ / 2;

                for (int k = 0; k < ArraySizeY; k++)
                {
                    for (int i = 0; i < ArraySizeX; i++)
                    {
                        for (int j = 0; j < ArraySizeZ; j++)
                        {
                            Matrix startTransform = Matrix.Translation(
                                2 * i + start_x,
                                2 * k + start_y,
                                2 * j + start_z
                            );

                            // using motionstate is recommended, it provides interpolation capabilities
                            // and only synchronizes 'active' objects
                            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);
                            RigidBodyConstructionInfo rbInfo =
                                new RigidBodyConstructionInfo(mass, myMotionState, colShape, localInertia);
                            RigidBody body = new RigidBody(rbInfo);
                            rbInfo.Dispose();

                            // make it drop from a height
                            body.Translate(new Vector3(0, 20, 0));

                            World.AddRigidBody(body);
                        }
                    }
                }

                DefaultSerializer serializer = new DefaultSerializer();

                serializer.RegisterNameForObject(ground, "GroundName");

                for (int i = 0; i < _collisionShapes.Count; i++)
                    serializer.RegisterNameForObject(_collisionShapes[i], $"name{i}");

                Point2PointConstraint p2p = new Point2PointConstraint((RigidBody)World.CollisionObjectArray[2], new Vector3(0, 1, 0));
                World.AddConstraint(p2p);

                serializer.RegisterNameForObject(p2p, "constraintje");

                World.Serialize(serializer);

                DataStream data = serializer.LockBuffer();
                byte[] dataBytes = new byte[data.Length];
                data.Read(dataBytes, 0, dataBytes.Length);

                FileStream file = new FileStream("testFile.bullet", FileMode.Create);
                file.Write(dataBytes, 0, dataBytes.Length);
                file.Close();
            }
        }

        public override void ExitPhysics()
        {
            _fileLoader.DeleteAllData();
            _fileLoader.Dispose();
            base.ExitPhysics();
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new SerializeDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
