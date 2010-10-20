﻿using BulletSharp;
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

            if (shape.ShapeType == BroadphaseNativeType.StaticPlane)
                body.UserObject = "Ground";

            return body;
        }
    }

    class Physics : PhysicsContext
    {
        ///create 125 (5x5x5) dynamic objects
        int ArraySizeX = 5, ArraySizeY = 5, ArraySizeZ = 5;

        ///scaling of the objects (0.1 = 20 centimeter boxes )
        float StartPosX = -5;
        float StartPosY = -5;
        float StartPosZ = -3;

        public Physics()
        {
            CollisionConfiguration collisionConf;

            // collision configuration contains default setup for memory, collision setup
            collisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(collisionConf);

            Broadphase = new DbvtBroadphase();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, collisionConf);
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

                float start_x = StartPosX - ArraySizeX / 2;
                float start_y = StartPosY;
                float start_z = StartPosZ - ArraySizeZ / 2;

                int k, i, j;
                for (k = 0; k < ArraySizeY; k++)
                {
                    for (i = 0; i < ArraySizeX; i++)
                    {
                        for (j = 0; j < ArraySizeZ; j++)
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

                            // make it drop from a height
                            body.Translate(new Vector3(0, 20, 0));

                            World.AddRigidBody(body);
                        }
                    }
                }

                int maxSerializeBufferSize = 1024 * 1024 * 5;
                DefaultSerializer serializer = new DefaultSerializer(maxSerializeBufferSize);

                serializer.RegisterNameForObject(ground, "GroundName");

                for (i = 0; i < CollisionShapes.Count; i++)
                    serializer.RegisterNameForObject(CollisionShapes[i], "name" + i.ToString());

                Point2PointConstraint p2p = new Point2PointConstraint(RigidBody.Upcast(World.CollisionObjectArray[2]), new Vector3(0, 1, 0));
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
