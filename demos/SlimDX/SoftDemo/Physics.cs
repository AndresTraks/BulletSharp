using BulletSharp;
using BulletSharp.SoftBody;
using DemoFramework;
using SlimDX;
using System;

namespace SoftDemo
{
    class Physics : PhysicsContext
    {
        //int numObjects = 1;
        public float Scaling = 1;
        //float waveHeight = 5;
        //float triangleHeight=8;
        //float CubeHalfExtents = 1.5f;
        //float extraHeight = -10.0f;

        SoftBodyWorldInfo softBodyWorldInfo;

        bool cutting;
        const int maxProxies = 32766;

        SoftRigidDynamicsWorld SoftWorld
        {
            get { return (SoftRigidDynamicsWorld)World; }
        }

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
            SoftWorld.AddSoftBody(psb);

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
            SoftWorld.AddSoftBody(psb);

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
            const int n = 15;
            for (int i = 0; i < n; i++)
	        {
                SoftBody psb = SoftBodyHelpers.CreateRope(softBodyWorldInfo,
                    new Vector3(-10, 0, i * 0.25f),
			        new Vector3(10, 0, i*0.25f), 16, 1+2);
                psb.Cfg.PIterations = 4;
		        psb.Materials[0].Lst = 0.1f + (i/(float)(n-1)) * 0.9f;
		        psb.TotalMass = 20;
                SoftWorld.AddSoftBody(psb);
	        }
        }

        SoftBody Create_Rope(Vector3 p)
        {
            SoftBody psb = SoftBodyHelpers.CreateRope(softBodyWorldInfo,p,p+new Vector3(10,0,0),8,1);
	        psb.TotalMass = 50;
            SoftWorld.AddSoftBody(psb);
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
            SoftWorld.AddSoftBody(psb);

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
                Material pm = psb.AppendMaterial();
                pm.Flags -=	FMaterial.DebugDraw;
                psb.GenerateBendingConstraints(2, pm);
                psb.Cfg.LF = 0.004f;
                psb.Cfg.DG = 0.0003f;
                psb.Cfg.AeroModel = AeroModel.VTwoSided;
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
                SoftWorld.AddSoftBody(psb);
	        }
        }

        void Init_TetraCube()
        {
            SoftBody psb = SoftBodyHelpers.CreateFromTetGenFile(softBodyWorldInfo,
			    "data\\cube.ele", null, "data\\cube.node", false,true,true);
            SoftWorld.AddSoftBody(psb);
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
            psb.Cfg.Collisions = FCollisions.ClSs | FCollisions.ClRs;
                // | SoftBody.FCollisions.ClSelf;
            psb.Materials[0].Lst = 0.8f;
	        cutting=true;
        }

        public Physics()
        {
            CollisionConfiguration collisionConf;

            // collision configuration contains default setup for memory, collision setup
            collisionConf = new SoftBodyRigidBodyCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(collisionConf);

            Broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000),
                new Vector3(1000, 1000, 1000), maxProxies);

            // the default constraint solver.
            Solver = new SequentialImpulseConstraintSolver();

            softBodyWorldInfo = new SoftBodyWorldInfo();
            softBodyWorldInfo.AirDensity = 1.2f;
            softBodyWorldInfo.WaterDensity = 0;
            softBodyWorldInfo.WaterOffset = 0;
            softBodyWorldInfo.WaterNormal = Vector3.Zero;
            softBodyWorldInfo.Gravity = new Vector3(0, -10, 0);
            softBodyWorldInfo.Dispatcher = Dispatcher;
            softBodyWorldInfo.Broadphase = Broadphase;
            softBodyWorldInfo.SparseSdf.Initialize();

            World = new SoftRigidDynamicsWorld(Dispatcher, Broadphase, Solver, collisionConf);
            World.Gravity = new Vector3(0, -10, 0);
            World.DispatchInfo.EnableSpu = true;

            CollisionShape groundShape = new BoxShape(50, 50, 50);
            CollisionShapes.PushBack(groundShape);
            RigidBody body = LocalCreateRigidBody(0, Matrix.Translation(0, -50, 0), groundShape);
            body.UserObject = "Ground";
            
            CollisionShape boxShape = new BoxShape(1, 1, 1);
            CollisionShapes.PushBack(boxShape);
            LocalCreateRigidBody(1.0f, Matrix.Translation(0, 1, 0), boxShape);
            
            softBodyWorldInfo.SparseSdf.Reset();
            //Init_Aero();
            Init_TetraCube();
            //Init_RbUpStack(5);
            //Init_LinearStair(8);
            //Init_ClothAttach();
            //Init_Ropes();
            Init_RopeAttach();
        }

        public static SlimDX.Direct3D9.Mesh GetMeshFromSoftBody(SlimDX.Direct3D9.Device device, CollisionObject obj)
        {
            SoftBody softBody = SoftBody.Upcast(obj);
            
            if (softBody == null)
                return null;

            if (softBody.Faces.Size == 0)
                return null;

            SlimDX.Direct3D9.Mesh mesh =
                new SlimDX.Direct3D9.Mesh(device, softBody.Faces.Size, softBody.Faces.Size * 3,
                SlimDX.Direct3D9.MeshFlags.SystemMemory | SlimDX.Direct3D9.MeshFlags.Use32Bit,
                SlimDX.Direct3D9.VertexFormat.Position);
            SlimDX.DataStream verts = mesh.LockVertexBuffer(SlimDX.Direct3D9.LockFlags.None);
            SlimDX.DataStream indices = mesh.LockIndexBuffer(SlimDX.Direct3D9.LockFlags.None);

            int j;
            for (j = 0; j < softBody.Faces.Size; j++)
            {
                BulletSharp.SoftBody.Face face = softBody.Faces[j];
                verts.Write(face.n[0].x);
                verts.Write(face.n[1].x);
                verts.Write(face.n[2].x);

                indices.Write(j * 3);
                indices.Write(j * 3 + 1);
                indices.Write(j * 3 + 2);
            }
            mesh.UnlockVertexBuffer();
            mesh.UnlockIndexBuffer();

            return mesh;
        }

        public override void Update(float elapsedTime)
        {
            base.Update(elapsedTime);
            softBodyWorldInfo.SparseSdf.GarbageCollect();
        }
    }
}
