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

        static Vector3 GetRandomVector(Random random)
        {
            return new Vector3((float)random.NextDouble(),
                    (float)random.NextDouble(), (float)random.NextDouble());
        }

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

        SoftBody Create_SoftBox(Vector3 p, Vector3 s)
        {
	        Vector3	h = s * 0.5f;
	        Vector3[] c = new Vector3[]{
                Vector3.Modulate(h, new Vector3(-1,-1,-1)),
		        Vector3.Modulate(h, new Vector3(+1,-1,-1)),
		        Vector3.Modulate(h, new Vector3(-1,+1,-1)),
		        Vector3.Modulate(h, new Vector3(+1,+1,-1)),
		        Vector3.Modulate(h, new Vector3(-1,-1,+1)),
		        Vector3.Modulate(h, new Vector3(+1,-1,+1)),
		        Vector3.Modulate(h, new Vector3(-1,+1,+1)),
		        Vector3.Modulate(h, new Vector3(+1,+1,+1))};
	        SoftBody psb = SoftBodyHelpers.CreateFromConvexHull(softBodyWorldInfo,c);
	        psb.GenerateBendingConstraints(2);
            psb.Translate(p);
            world.AddSoftBody(psb);

	        return(psb);
        }

        SoftBody Create_SoftBoulder(Vector3 p, Vector3 s, int np)
        {
            Random random = new Random();
            Vector3[] pts = new Vector3[np];
	        for(int i=0; i<np; ++i)
		        pts[i] = Vector3.Modulate(GetRandomVector(random), s);

            SoftBody psb = SoftBodyHelpers.CreateFromConvexHull(softBodyWorldInfo, pts);
	        psb.GenerateBendingConstraints(2);
            psb.Translate(p);
	        world.AddSoftBody(psb);

	        return(psb);
        }

        void Init_RbUpStack(int count)
        {
	        float mass=10.0f;

	        CompoundShape cylinderCompound = new CompoundShape();
	        CollisionShape cylinderShape = new CylinderShapeX(4,1,1);
	        CollisionShape boxShape = new BoxShape(4,1,1);
            cylinderCompound.AddChildShape(Matrix.Identity, boxShape);
	        Quaternion orn = new Quaternion((float)Math.PI/2.0f, 0.0f, 0.0f, 1.0f);
            Matrix localTransform = Matrix.RotationQuaternion(orn);
            //localTransform *= Matrix.Translation(new Vector3(1,1,1));
	        cylinderCompound.AddChildShape(localTransform,cylinderShape);

            LocalCreateRigidBody(mass, Matrix.Translation(0, 2, 0), cylinderCompound);
            LocalCreateRigidBody(mass, Matrix.Translation(0, 8, 0), new BoxShape(1, 1, 1));
            LocalCreateRigidBody(mass, Matrix.Translation(0, 14, 0), new SphereShape(1.5f));
        }

        void Create_BigBall(Vector3 position)
        {
            LocalCreateRigidBody(10.0f, Matrix.Translation(position), new SphereShape(1.5f));
        }

        void Init_Ropes()
        {
	        for(int i=0; i<15; i++)
	        {
                SoftBody psb = SoftBodyHelpers.CreateRope(softBodyWorldInfo,
                    new Vector3(-10, 0, i * 0.25f),
			        new Vector3(10, 0, i*0.25f), 16, 1+2);
                psb.Cfg.PIterations = 4;
		        //psb->m_materials[0]->m_kLST	=	0.1+(i/(btScalar)(n-1))*0.9;
		        psb.TotalMass = 20;
                world.AddSoftBody(psb);
	        }
        }

        SoftBody Create_Rope(Vector3 p)
        {
            SoftBody psb = SoftBodyHelpers.CreateRope(softBodyWorldInfo,p,p+new Vector3(10,0,0),8,1);
	        psb.TotalMass = 50;
	        world.AddSoftBody(psb);
	        return(psb);
        }

        void Init_RopeAttach()
        {
	        softBodyWorldInfo.SparseSdf.RemoveReferences(null);
	        RigidBody body = LocalCreateRigidBody(50, Matrix.Translation(12,8,0),new BoxShape(2,6,2));
            SoftBody psb0 = Create_Rope(new Vector3(0, 8, -1));
            SoftBody psb1 = Create_Rope(new Vector3(0, 8, +1));
	        psb0.AppendAnchor(psb0.Nodes.Size-1,body);
	        psb1.AppendAnchor(psb1.Nodes.Size-1,body);
        }

        void Init_ClothAttach()
        {
	        float s=4;
	        float h=6;
	        int r=9;
	        SoftBody psb = SoftBodyHelpers.CreatePatch(softBodyWorldInfo, new Vector3(-s,h,-s),
		        new Vector3(+s,h,-s),
		        new Vector3(-s,h,+s),
		        new Vector3(+s,h,+s),r,r,4+8,true);
	        world.AddSoftBody(psb);

	        RigidBody body = LocalCreateRigidBody(20,Matrix.Translation(0,h,-(s+3.5f)),new BoxShape(s,1,3));
	        psb.AppendAnchor(0,body);
	        psb.AppendAnchor(r-1,body);
            body.UserObject = "LargeBox";
	        cutting=true;
        }

        void Init_LinearStair(int count)
        {
            Vector3 origin = new Vector3(2, 1, 0);

            BoxShape shape = new BoxShape(1,1,1);
            for(int i=0; i<count; i++)
            {
	            RigidBody body = LocalCreateRigidBody(0,
                    Matrix.Translation(origin + new Vector3(2 * i, 2 * i, 0)), shape);
                body.Friction = 1;
            }
        }

        // Aerodynamic forces, 50x1g flyers
        void Init_Aero()
        {
	        const float s=2;
	        const int segments=6;
	        const int count=50;
            Random random = new Random();
	        for(int i=0;i<count;++i)
	        {
		        SoftBody psb = SoftBodyHelpers.CreatePatch(softBodyWorldInfo,
                    new Vector3(-s,0,-s), new Vector3(+s,0,-s),
			        new Vector3(-s,0,+s), new Vector3(+s,0,+s),
			        segments,segments, 0,true);
                SoftBody.Material pm = psb.AppendMaterial();
                pm.Flags -=	SoftBody.FMaterial.DebugDraw;
                psb.GenerateBendingConstraints(2, pm);
                psb.Cfg.LF = 0.004f;
                psb.Cfg.DG = 0.0003f;
                psb.Cfg.AeroModel = SoftBody.AeroModel.VTwoSided;
                Matrix trans = Matrix.Identity;
                Vector3 ra = 0.1f * GetRandomVector(random);
                Vector3 rp = 75 * GetRandomVector(random) + new Vector3(-50, 15, 0);
                Quaternion rot = Quaternion.RotationYawPitchRoll(
                    (float)Math.PI/8+ra.X, (float)-Math.PI/7+ra.Y, ra.Z);
                trans *= Matrix.RotationQuaternion(rot);
                trans *= Matrix.Translation(rp);
                psb.Transform(trans);
                psb.TotalMass = 0.1f;
                psb.AddForce(new Vector3(0,(float)random.NextDouble(),0),0);
                world.AddSoftBody(psb);
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
	        //psb.SetMass(0,0);
	        //psb.SetMass(10,0);
	        //psb.SetMass(20,0);
	        psb.Cfg.PIterations=1;
	        //psb.GenerateClusters(128);
	        psb.GenerateClusters(16);
            //psb.CollisionShape.Margin = 0.5f;

	        psb.CollisionShape.Margin = 0.01f;
            psb.Cfg.Collisions = SoftBody.FCollisions.ClSs | SoftBody.FCollisions.ClRs;
                // | SoftBody.FCollisions.ClSelf;
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
            softBodyWorldInfo.SparseSdf.Initialize();

            world = new SoftRigidDynamicsWorld(dispatcher, broadphase, solver, collisionConf);
            world.Gravity = new Vector3(0, -10, 0);
            world.DispatchInfo.EnableSpu = true;

            CollisionShape groundShape = new BoxShape(50, 50, 50);
            collisionShapes.PushBack(groundShape);
            RigidBody body = LocalCreateRigidBody(0, Matrix.Translation(0, -50, 0), groundShape);
            body.UserObject = "Ground";

            CollisionShape boxShape = new BoxShape(1, 1, 1);
            collisionShapes.PushBack(boxShape);
            LocalCreateRigidBody(1.0f, Matrix.Translation(0, 1, 0), boxShape);

            softBodyWorldInfo.SparseSdf.Reset();
            //Init_Aero();
            //Init_TetraCube();
            //Init_RbUpStack(5);
            //Init_LinearStair(8);
            Init_ClothAttach();

            world.Broadphase.ResetPool(dispatcher);
            solver.Reset();
        }

        public void Update(float elapsedTime)
        {
            world.StepSimulation(elapsedTime);
            softBodyWorldInfo.SparseSdf.GarbageCollect();
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
