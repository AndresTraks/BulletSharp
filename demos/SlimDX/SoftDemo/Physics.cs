using BulletSharp;
using DemoFramework;
using System;
using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;

namespace BasicDemo
{
    class Physics
    {
        int numObjects = 1;
        public float Scaling = 1;
        float waveHeight = 5;
        float triangleHeight=8;
        float CubeHalfExtents = 1.5f;
        float extraHeight = -10.0f;

        CollisionDispatcher dispatcher;
        BroadphaseInterface broadphase;
        ConstraintSolver solver;
        CollisionShapeArray collisionShapes = new CollisionShapeArray();
        public SoftRigidDynamicsWorld world;
        SoftBodyWorldInfo softBodyWorldInfo;

        bool cutting;
        const int maxProxies = 32766;

        void CreateStack(CollisionShape boxShape, float halfCubeSize, int size, float zPos)
        {
            Matrix trans;
            float mass = 1;
            for (int i = 0; i < size; i++)
            {
                // This constructs a row, from left to right
                int rowSize = size - i;
                for (int j = 0; j < rowSize; j++)
                {
                    trans = Matrix.Translation(
                        -rowSize * halfCubeSize + halfCubeSize + j * 2.0f * halfCubeSize,
                        halfCubeSize + i * halfCubeSize * 2.0f, zPos);

                    RigidBody body = LocalCreateRigidBody(mass, trans, boxShape);
                }
            }
        }

        void Init_TetraCube()
        {
            SoftBody psb = SoftBodyHelpers.CreateFromTetGenFile(softBodyWorldInfo,
			    "data\\cube.ele", null, "data\\cube.node", false,true,true);
	        world.AddSoftBody(psb);
	        psb.Scale(new Vector3(4,4,4));
	        psb.Translate(0,5,0);
	        psb.SetVolumeMass(300);
        	
	        ///fix one vertex
	        //psb->setMass(0,0);
	        //psb->setMass(10,0);
	        //psb->setMass(20,0);
	        psb.Cfg.PIterations=1;
	        //psb.GenerateClusters(128);
	        psb.GenerateClusters(16);
            //psb.CollisionShape.Margin = 0.5f;

	        psb.CollisionShape.Margin = 0.01f;
            psb.Cfg.Collisions = SoftBody.FCollisions.ClSs | SoftBody.FCollisions.ClRs |
                SoftBody.FCollisions.ClSelf;
	        //psb->m_materials[0]->m_kLST=0.8;
	        cutting=true;	
        }

        public Physics()
        {
            CollisionConfiguration collisionConf;

            // collision configuration contains default setup for memory, collision setup
            collisionConf = new SoftBodyRigidBodyCollisionConfiguration();
            dispatcher = new CollisionDispatcher(collisionConf);

            broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000),
                new Vector3(1000, 1000, 1000), maxProxies);

            // the default constraint solver.
            solver = new SequentialImpulseConstraintSolver();

            softBodyWorldInfo = new SoftBodyWorldInfo();
            softBodyWorldInfo.AirDensity = 1.2f;
            softBodyWorldInfo.WaterDensity = 0;
            softBodyWorldInfo.WaterOffset = 0;
            softBodyWorldInfo.WaterNormal = Vector3.Zero;
            softBodyWorldInfo.Gravity = new Vector3(0, -10, 0);
            softBodyWorldInfo.Dispatcher = dispatcher;
            softBodyWorldInfo.Broadphase = broadphase;

            world = new SoftRigidDynamicsWorld(dispatcher, broadphase, solver, collisionConf);
            world.Gravity = new Vector3(0, -10, 0);

            // create a few basic rigid bodies
            CollisionShape groundShape = new BoxShape(50, 50, 50);
            collisionShapes.PushBack(groundShape);
            LocalCreateRigidBody(0, Matrix.Translation(0, -50, 0), groundShape);

            Init_TetraCube();

            world.Broadphase.ResetPool(dispatcher);
            solver.Reset();
        }

        public void Update(float elapsedTime)
        {
            world.StepSimulation(elapsedTime);
        }

        public RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            bool isDynamic = (mass != 0.0f);

            Vector3 localInertia = new Vector3(0, 0, 0);
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);

            RigidBody.RigidBodyConstructionInfo rbInfo = new RigidBody.RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia);
            RigidBody body = new RigidBody(rbInfo);

            world.AddRigidBody(body);

            return body;
        }
    }
}
