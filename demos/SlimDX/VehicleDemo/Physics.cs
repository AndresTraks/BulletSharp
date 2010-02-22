using BulletSharp;
using DemoFramework;
using System;
using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.DirectInput;

namespace VehicleDemo
{
    class Physics
    {
        int rightIndex = 0;
        int upIndex = 1;
        int forwardIndex = 2;
        Vector3 wheelDirectionCS0 = new Vector3(0, -1, 0);
        Vector3 wheelAxleCS = new Vector3(-1, 0, 0);

        const int maxProxies = 32766;
        const int maxOverlap = 65535;

        // btRaycastVehicle is the interface for the constraint that implements the raycast vehicle
        // notice that for higher-quality slow-moving vehicles, another approach might be better
        // implementing explicit hinged-wheel constraints with cylinder collision, rather then raycasts
        float gEngineForce = 0.0f;
        float gBreakingForce = 0.0f;

        float maxEngineForce = 1500.0f;//this should be engine/velocity dependent
        float maxBreakingForce = 100.0f;

        float gVehicleSteering = 0.0f;
        float steeringIncrement = 0.005f;
        float steeringClamp = 0.3f;
        public float wheelRadius = 0.7f;
        public float wheelWidth = 0.4f;
        float wheelFriction = 1000;//BT_LARGE_FLOAT;
        float suspensionStiffness = 20.0f;
        float suspensionDamping = 2.3f;
        float suspensionCompression = 4.4f;
        float rollInfluence = 0.1f;//1.0f;

        float suspensionRestLength = 0.6f;
        float CUBE_HALF_EXTENTS = 1;

        float timeCounter = 0.0f;


        CollisionDispatcher dispatcher;
        BroadphaseInterface broadphase;
        ConstraintSolver solver;
        AlignedObjectArray<CollisionShape> collisionShapes = new AlignedObjectArray<CollisionShape>();
        public DynamicsWorld world;
        public RaycastVehicle vehicle;

        public Physics(VehicleDemo game)
        {
            CollisionConfiguration collisionConf;

            CollisionShape groundShape = new BoxShape(50, 3, 50);
            collisionShapes.PushBack(groundShape);

            collisionConf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(collisionConf);
            solver = new SequentialImpulseConstraintSolver();

            Vector3 worldMin = new Vector3(-10000, -10000, -10000);
            Vector3 worldMax = new Vector3(10000, 10000, 10000);
            broadphase = new AxisSweep3(worldMin, worldMax);
            //broadphase = new DbvtBroadphase();

            world = new DiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConf);


            int i;
            const float TRIANGLE_SIZE = 20.0f;

            //create a triangle-mesh ground
            int vertStride = Vector3.SizeInBytes;
            int indexStride = 3 * sizeof(int);

            const int NUM_VERTS_X = 20;
            const int NUM_VERTS_Y = 20;
            const int totalVerts = NUM_VERTS_X * NUM_VERTS_Y;

            const int totalTriangles = 2 * (NUM_VERTS_X - 1) * (NUM_VERTS_Y - 1);

            TriangleIndexVertexArray vertexArray = new TriangleIndexVertexArray();
            IndexedMesh mesh = new IndexedMesh();
            mesh.Allocate(totalVerts, vertStride, totalTriangles, indexStride);

            game.ground = new Mesh(game.Device, totalTriangles, totalVerts, MeshFlags.SystemMemory | MeshFlags.Use32Bit, VertexFormat.Position | VertexFormat.Normal);
            SlimDX.DataStream data2 = game.ground.LockVertexBuffer(LockFlags.None);
            BulletSharp.DataStream data = mesh.LockVerts();
            for (i = 0; i < NUM_VERTS_X; i++)
            {
                for (int j = 0; j < NUM_VERTS_Y; j++)
                {
                    float wl = .2f;
                    //height set to zero, but can also use curved landscape, just uncomment out the code
                    float height = 20.0f * (float)(Math.Sin(i * wl) * Math.Cos(j * wl));

                    data.Write((i - NUM_VERTS_X * 0.5f) * TRIANGLE_SIZE);
                    data.Write(height);
                    data.Write((j - NUM_VERTS_Y * 0.5f) * TRIANGLE_SIZE);

                    data2.Write((i - NUM_VERTS_X * 0.5f) * TRIANGLE_SIZE);
                    data2.Write(height);
                    data2.Write((j - NUM_VERTS_Y * 0.5f) * TRIANGLE_SIZE);

                    // Normals will be calculated later
                    data2.Write(0.0f);
                    data2.Write(0.0f);
                    data2.Write(0.0f);
                }
            }
            game.ground.UnlockVertexBuffer();

            data = mesh.LockIndices();
            data2 = game.ground.LockIndexBuffer(LockFlags.None);
            for (i = 0; i < NUM_VERTS_X - 1; i++)
            {
                for (int j = 0; j < NUM_VERTS_Y - 1; j++)
                {
                    data.Write(j * NUM_VERTS_X + i);
                    data.Write(j * NUM_VERTS_X + i + 1);
                    data.Write((j + 1) * NUM_VERTS_X + i + 1);

                    data.Write(j * NUM_VERTS_X + i);
                    data.Write((j + 1) * NUM_VERTS_X + i + 1);
                    data.Write((j + 1) * NUM_VERTS_X + i);

                    data2.Write(j * NUM_VERTS_X + i);
                    data2.Write(j * NUM_VERTS_X + i + 1);
                    data2.Write((j + 1) * NUM_VERTS_X + i + 1);

                    data2.Write(j * NUM_VERTS_X + i);
                    data2.Write((j + 1) * NUM_VERTS_X + i + 1);
                    data2.Write((j + 1) * NUM_VERTS_X + i);
                }
            }
            game.ground.UnlockIndexBuffer();

            vertexArray.AddIndexedMesh(mesh);
            groundShape = new BvhTriangleMeshShape(vertexArray, true);
            collisionShapes.PushBack(groundShape);

            //create ground object
            LocalCreateRigidBody(0, Matrix.Translation(0, -4.5f, 0), groundShape);


            CollisionShape chassisShape = new BoxShape(1.0f, 0.5f, 2.0f);
            collisionShapes.PushBack(chassisShape);

            CompoundShape compound = new CompoundShape();
            collisionShapes.PushBack(compound);

            compound.AddChildShape(Matrix.Translation(Vector3.UnitY), chassisShape);
            RigidBody carChassis = LocalCreateRigidBody(800, Matrix.Identity, compound);
            //carChassis.SetDamping(0.2f, 0.2f);

            CylinderShapeX wheelShape = new CylinderShapeX(wheelWidth, wheelRadius, wheelRadius);


            // clientResetScene();

	        // create vehicle
            RaycastVehicle.VehicleTuning tuning = new RaycastVehicle.VehicleTuning();
		    VehicleRaycaster vehicleRayCaster = new DefaultVehicleRaycaster(world);
            vehicle = new RaycastVehicle(tuning, carChassis, vehicleRayCaster);

            carChassis.ActivationState = ActivationState.DisableDeactivation;
            world.AddAction(vehicle);


            float connectionHeight = 1.2f;
            bool isFrontWheel = true;

            // choose coordinate system
            vehicle.SetCoordinateSystem(rightIndex, upIndex, forwardIndex);

            Vector3 connectionPointCS0 = new Vector3(CUBE_HALF_EXTENTS-(0.3f*wheelWidth),connectionHeight,2*CUBE_HALF_EXTENTS-wheelRadius);
            WheelInfo a = vehicle.AddWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, isFrontWheel);

            connectionPointCS0 = new Vector3(-CUBE_HALF_EXTENTS + (0.3f * wheelWidth), connectionHeight, 2 * CUBE_HALF_EXTENTS - wheelRadius);
            vehicle.AddWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, isFrontWheel);

            isFrontWheel = false;
            connectionPointCS0 = new Vector3(-CUBE_HALF_EXTENTS + (0.3f * wheelWidth), connectionHeight, -2 * CUBE_HALF_EXTENTS + wheelRadius);
            vehicle.AddWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, isFrontWheel);

            connectionPointCS0 = new Vector3(CUBE_HALF_EXTENTS - (0.3f * wheelWidth), connectionHeight, -2 * CUBE_HALF_EXTENTS + wheelRadius);
            vehicle.AddWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, isFrontWheel);


            for (i = 0; i < vehicle.NumWheels; i++)
            {
                WheelInfo wheel = vehicle.GetWheelInfo(i);
                wheel.SuspensionStiffness = suspensionStiffness;
                wheel.DampingRelaxation = suspensionDamping;
                wheel.DampingCompression = suspensionCompression;
                wheel.FrictionSlip = wheelFriction;
                wheel.RollInfluence = rollInfluence;
            }
        }

        public void Update(float elapsedTime)
        {
            // Use 1/60 update step like StepSimulation does
            timeCounter += elapsedTime;
            if (timeCounter >= 1 / 60)
            {
                vehicle.ApplyEngineForce(gEngineForce, 2);
                vehicle.SetBrake(gBreakingForce, 2);
                vehicle.ApplyEngineForce(gEngineForce, 3);
                vehicle.SetBrake(gBreakingForce, 3);

                vehicle.SetSteeringValue(gVehicleSteering, 0);
                vehicle.SetSteeringValue(gVehicleSteering, 1);

                gEngineForce *= 0.99f;
                gVehicleSteering *= 0.99f;

                timeCounter = 0.0f;
            }

            world.StepSimulation(elapsedTime);
        }

        public void HandleKeys(Input input, float ElapsedTime)
        {
            if (input.KeyboardState.IsPressed(Key.RightArrow))
            {
                gVehicleSteering += steeringIncrement;
                if (gVehicleSteering > steeringClamp)
                    gVehicleSteering = steeringClamp;
            }

            if (input.KeyboardState.IsPressed(Key.LeftArrow))
            {
                gVehicleSteering -= steeringIncrement;
                if (gVehicleSteering < -steeringClamp)
                    gVehicleSteering = -steeringClamp;
            }

            if (input.KeyboardState.IsPressed(Key.UpArrow))
            {
                gEngineForce = maxEngineForce;
                gBreakingForce = 0.0f;
            }

            if (input.KeyboardState.IsPressed(Key.DownArrow))
            {
                gEngineForce = 0.0f;
                gBreakingForce = maxBreakingForce;
            }
        }

        public RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            bool isDynamic = (mass != 0.0f);

            Vector3 localInertia = new Vector3(0, 0, 0);
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);

            RigidBodyConstructionInfo rbInfo = new RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia);
            RigidBody body = new RigidBody(rbInfo);

            world.AddRigidBody(body);

            return body;
        }
    }
}
