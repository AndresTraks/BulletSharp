using BulletSharp;
using BulletSharp.Serialize;
using DemoFramework;
using SlimDX;
using System.IO;

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

    class Physics : PhysicsContext
    {
        ///create 125 (5x5x5) dynamic objects
        const int ArraySizeX = 5, ArraySizeY = 5, ArraySizeZ = 5;

        ///scaling of the objects (0.1 = 20 centimeter boxes )
        const float StartPosX = -5;
        const float StartPosY = -5;
        const float StartPosZ = -3;

        public Physics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new DbvtBroadphase();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            GImpactCollisionAlgorithm.RegisterAlgorithm(Dispatcher);


            BulletWorldImporter fileLoader = new CustomBulletWorldImporter(World);
            if (!fileLoader.LoadFile("testFile.bullet"))
            {
                CollisionShape groundShape = new BoxShape(50);
                CollisionShapes.Add(groundShape);
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
                CollisionShapes.Add(colShape);

                Vector3 localInertia = colShape.CalculateLocalInertia(mass);

                var rbInfo = new RigidBodyConstructionInfo(mass, null, colShape, localInertia);

                const float startX = StartPosX - ArraySizeX / 2;
                const float startY = StartPosY;
                const float startZ = StartPosZ - ArraySizeZ / 2;

                for (int k = 0; k < ArraySizeY; k++)
                {
                    for (int i = 0; i < ArraySizeX; i++)
                    {
                        for (int j = 0; j < ArraySizeZ; j++)
                        {
                            Matrix startTransform = Matrix.Translation(
                                2 * i + startX,
                                2 * k + startY,
                                2 * j + startZ
                            );

                            // using motionstate is recommended, it provides interpolation capabilities
                            // and only synchronizes 'active' objects
                            rbInfo.MotionState = new DefaultMotionState(startTransform);
                            RigidBody body = new RigidBody(rbInfo);

                            // make it drop from a height
                            body.Translate(new Vector3(0, 20, 0));

                            World.AddRigidBody(body);
                        }
                    }
                }

                DefaultSerializer serializer = new DefaultSerializer();

                serializer.RegisterNameForObject(ground, "GroundName");

                for (int i = 0; i < CollisionShapes.Count; i++)
                    serializer.RegisterNameForObject(CollisionShapes[i], "name" + i.ToString());

                Point2PointConstraint p2p = new Point2PointConstraint((RigidBody)World.CollisionObjectArray[2], new Vector3(0, 1, 0));
                World.AddConstraint(p2p);

                serializer.RegisterNameForObject(p2p, "constraintje");

                World.Serialize(serializer);

                BulletSharp.DataStream data = serializer.LockBuffer();
                byte[] dataBytes = new byte[data.Length];
                data.Read(dataBytes, 0, dataBytes.Length);

                FileStream file = new FileStream("testFile.bullet", FileMode.Create);
                file.Write(dataBytes, 0, dataBytes.Length);
                file.Close();
            }
        }
    }
}
