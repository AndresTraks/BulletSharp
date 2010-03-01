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
        public DynamicsWorld world;
        SoftBodyWorldInfo softBodyWorldInfo;

        bool cutting;

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

        static void	Init_TetraCube()
        {
            //SoftBody psb = SoftBodyHelpers.CreateFromTetGenData(softBodyWorldInfo,
			//    "cube.ele", null, "cube.node", false,true,true);
	        //softDynamicsWorld.AddSoftBody(psb);
	        //psb.Scale( new Vector3(4,4,4));
	        //psb.Translate(new Vector3(0,5,0));
	        //psb.VolumeMass = 300;
        	
	        ///fix one vertex
	        //psb->setMass(0,0);
	        //psb->setMass(10,0);
	        //psb->setMass(20,0);
	        //psb.Cfg.piterations=1;
	        //psb->generateClusters(128);
	        //psb.GenerateClusters(16);
	        //psb->getCollisionShape()->setMargin(0.5);

	        //psb.CollisionShape.Margin = 0.01f;
	        //psb->m_cfg.collisions = SoftBody.fCollision.CL_SS | SoftBody.fCollision.CL_RS
		        //+ SoftBody.fCollision.CL_SELF
		        ;
	        //psb->m_materials[0]->m_kLST=0.8;
	        //cutting=true;	
        }

        public Physics()
        {
            CollisionConfiguration collisionConf;

            // collision configuration contains default setup for memory, collision setup
            collisionConf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(collisionConf);

            broadphase = new DbvtBroadphase();

            // the default constraint solver.
            solver = new SequentialImpulseConstraintSolver();

            world = new DiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConf);
            world.Gravity = new Vector3(0, -10, 0);

            // create a few basic rigid bodies
            CollisionShape groundShape = new BoxShape(50, 50, 50);
            collisionShapes.PushBack(groundShape);
            LocalCreateRigidBody(0, Matrix.Translation(0, -50, 0), groundShape);

            // create a few dynamic rigidbodies
            float mass = 1.0f;


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
