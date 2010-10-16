using BulletSharp;
using BulletSharp.MultiThreaded;
using DemoFramework;
using SlimDX;

namespace CcdPhysicsDemo
{
    class Physics : PhysicsContext
    {
        // Enable just one, DoBenchmarkPyramids or DoWall
        public bool DoBenchmarkPyramids = false;
        bool DoWall = true;

        // Note: some of those settings need 'DoWall' demo
        bool UseKinematicGround = false;
        bool CenterOfMassShift = false;
        bool useCompound;

        bool UseThreading = false;
        Win32ThreadSupport threadSupportCollision;

        float CubeHalfExtents = 0.5f;
        float numObjects = 120;
        Vector3 comOffsetVec = new Vector3(0,2,0);
        float collisionMargin = 0.05f;
        float ExtraHeight = -10.0f;

        const int maxNumObjects = 32760;
        int[] shapeIndex = new int[maxNumObjects];

        void CreateStack(CollisionShape boxShape, int size, float zPos)
        {
	        Matrix trans;
            float mass = 1.0f;

	        for(int i=0; i<size; i++)
	        {
		        // This constructs a row, from left to right
		        int rowSize = size - i;
		        for(int j=0; j< rowSize; j++)
		        {
			        trans = Matrix.Translation(
                        -rowSize * CubeHalfExtents + CubeHalfExtents + j * 2.0f * CubeHalfExtents,
                        CubeHalfExtents + i * CubeHalfExtents * 2.0f,
				        zPos);

			        RigidBody body = LocalCreateRigidBody(mass,trans,boxShape);
                    body.ActivationState = ActivationState.IslandSleeping;
		        }
	        }
        }

        public Physics()
        {
            int i;

            useCompound = CenterOfMassShift;

            CollisionShapes.Add(new BoxShape(200, CubeHalfExtents, 200));

            if (DoBenchmarkPyramids)
            {
                CollisionShapes.Add(new BoxShape(CubeHalfExtents, CubeHalfExtents, CubeHalfExtents));
            }
            else
            {
                //CollisionShapes.PushBack(new BoxShape(CubeHalfExtents, CubeHalfExtents, CubeHalfExtents));
                CollisionShapes.Add(new CylinderShape(CubeHalfExtents, CubeHalfExtents, CubeHalfExtents));
            }

            // collision configuration contains default setup for memory, collision setup
            CollisionConfiguration collisionConf = new DefaultCollisionConfiguration();

            if (UseThreading)
            {
                int maxNumOutstandingTasks = 4;

                Win32ThreadConstructionInfo info = new Win32ThreadConstructionInfo("collision",
                    Win32ThreadFunc.ProcessCollisionTask, Win32LSMemorySetupFunc.CreateCollisionLocalStoreMemory,
                    maxNumOutstandingTasks);
                
                threadSupportCollision = new Win32ThreadSupport(info);
                Dispatcher = new SpuGatheringCollisionDispatcher(threadSupportCollision, maxNumOutstandingTasks, collisionConf);
            }
            else
            {
                Dispatcher = new CollisionDispatcher(collisionConf);
            }

            Broadphase = new DbvtBroadphase();


            // the default constraint solver.
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, collisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            // RandomizeOrder makes cylinder stacking a bit more stable
            World.SolverInfo.SolverMode |= SolverModes.RandomizeOrder;

            if (DoBenchmarkPyramids)
                World.SolverInfo.NumIterations = 4;

            World.DispatchInfo.EnableSpu = true;

            shapeIndex[0] = 0;
            for (i = 1; i < numObjects; i++)
                    shapeIndex[i] = 1;//sphere

            if (useCompound)
	        {
		        CompoundShape compoundShape = new CompoundShape();
		        CollisionShape oldShape = CollisionShapes[1];
		        CollisionShapes[1] = compoundShape;
		        Vector3 sphereOffset = new Vector3(0,0,2);

                if (CenterOfMassShift)
                {
                    compoundShape.AddChildShape(Matrix.Translation(comOffsetVec), oldShape);
                }
                else
                {
	                compoundShape.AddChildShape(Matrix.Identity, oldShape);
                    compoundShape.AddChildShape(Matrix.Translation(sphereOffset), new SphereShape(0.9f));
                }
	        }

            if (DoWall)
            {
                for (i = 0; i < numObjects; i++)
                {
                    CollisionShape shape = CollisionShapes[shapeIndex[i]];
                    shape.Margin = collisionMargin;

                    RigidBody body;
                    Matrix trans;

                    if (i == 0)
                    {
                        body = LocalCreateRigidBody(0, Matrix.Translation(0, ExtraHeight, 0), shape);
                        body.UserObject = "Ground";

                        if (UseKinematicGround)
                        {
                            body.CollisionFlags = body.CollisionFlags | CollisionFlags.KinematicObject;
                            body.ActivationState = ActivationState.DisableDeactivation;
                        }
                    }
                    else
                    {
                        //stack them
                        int colsize = 10;
                        int row = (int)((i * CubeHalfExtents * 2) / (colsize * 2 * CubeHalfExtents));
                        int row2 = row;
                        int col = (i) % (colsize) - colsize / 2;

                        if (col > 3)
                        {
                            col = 11;
                            row2 |= 1;
                        }

                        trans = Matrix.Translation(col * 2 * CubeHalfExtents + (row2 % 2) * CubeHalfExtents,
                            (row + 1) * 2 * CubeHalfExtents + ExtraHeight, 0);
                        
                        body = LocalCreateRigidBody(1, trans, shape);
                    }

                    // Only do CCD if  motion in one timestep (1.f/60.f) exceeds CubeHalfExtents
                    body.CcdMotionThreshold = CubeHalfExtents;

                    //Experimental: better estimation of CCD Time of Impact:
                    body.CcdSweptSphereRadius = 0.2f * CubeHalfExtents;
                }
            }

            if (DoBenchmarkPyramids)
            {
                RigidBody ground = LocalCreateRigidBody(0, Matrix.Translation(new Vector3(0, -CubeHalfExtents, 0)),
                    CollisionShapes[shapeIndex[0]]);
                ground.UserObject = "Ground";

	            int numWalls = 15;
	            int wallHeight = 15;
	            float wallDistance = 3;

	            for (i=0;i<numWalls;i++)
	            {
		            float zPos = (i-numWalls/2) * wallDistance;
		            CreateStack(CollisionShapes[shapeIndex[1]], wallHeight, zPos);
                }

                // Destroyer ball
	            SphereShape ballShape = new SphereShape(2);
	            CollisionShapes.Add(ballShape);
	            RigidBody ballBody = LocalCreateRigidBody(10000, Matrix.Translation(0,2,40), ballShape);
	            ballBody.LinearVelocity = new Vector3(0,0,-10);
            }
        }
    }
}
