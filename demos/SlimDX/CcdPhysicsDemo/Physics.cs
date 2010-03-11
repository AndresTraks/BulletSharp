using BulletSharp;
using DemoFramework;
using System;
using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;

namespace CcdPhysicsDemo
{
    class Physics
    {
        // Enable just one, DoBenchmarkPyramids or DoWall
        public bool DoBenchmarkPyramids = false;
        bool DoWall = true;

        // Note: some of those settings need 'DoWall' demo
        bool UseKinematicGround = false;
        bool UseCustomNearCallback = false;
        bool CenterOfMassShift = false;
        bool useCompound;

        public float Scaling = 1;
        float CubeHalfExtents = 0.5f;
        float numObjects = 120;
        Vector3 comOffsetVec = new Vector3(0,2,0);
        float collisionMargin = 0.05f;
        float ExtraHeight = -10;

        const int maxNumObjects = 32760;
        int[] shapeIndex = new int[maxNumObjects];

        CollisionDispatcher dispatcher;
        BroadphaseInterface broadphase;
        ConstraintSolver solver;
        CollisionShapeArray collisionShapes = new CollisionShapeArray();
        public DynamicsWorld world;

        void CreateStack(CollisionShape boxShape, float halfCubeSize, int size, float zPos)
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
				        -rowSize * halfCubeSize + halfCubeSize + j * 2.0f * halfCubeSize,
				        halfCubeSize + i * halfCubeSize * 2.0f,
				        zPos);

			        RigidBody body = LocalCreateRigidBody(mass,trans,boxShape);
		        }
	        }
        }

        //by default, Bullet will use its own nearcallback, but you can override it using dispatcher->setNearCallback()
        void CustomNearCallback(BroadphasePair collisionPair, CollisionDispatcher dispatcher, DispatcherInfo dispatchInfo)
        {
	        CollisionObject colObj0 = new CollisionObject(collisionPair.Proxy0.ClientObject);
            CollisionObject colObj1 = new CollisionObject(collisionPair.Proxy1.ClientObject);

	        if (dispatcher.NeedsCollision(colObj0, colObj1))
	        {
		        //dispatcher will keep algorithms persistent in the collision pair
		        if (collisionPair.Algorithm == null)
		        {
			        collisionPair.Algorithm = dispatcher.FindAlgorithm(colObj0, colObj1);
		        }

		        if (collisionPair.Algorithm != null)
		        {
			        ManifoldResult contactPointResult = new ManifoldResult(colObj0, colObj1);

			        if (dispatchInfo.DispatchFunction == DispatcherInfo.DispatchFunc.Discrete)
			        {
				        //discrete collision detection query
				        collisionPair.Algorithm.ProcessCollision(colObj0, colObj1, dispatchInfo, contactPointResult);
			        }
                    else
			        {
				        //continuous collision detection query, time of impact (toi)
				        float toi = collisionPair.Algorithm.CalculateTimeOfImpact(colObj0, colObj1, dispatchInfo, contactPointResult);
				        if (dispatchInfo.TimeOfImpact > toi)
					        dispatchInfo.TimeOfImpact = toi;

			        }
		        }
	        }
        }

        public Physics()
        {
            int i;

            useCompound = CenterOfMassShift;

            collisionShapes.PushBack(new BoxShape(200, CubeHalfExtents, 200));

            if (DoBenchmarkPyramids)
            {
                collisionShapes.PushBack(new BoxShape(CubeHalfExtents, CubeHalfExtents, CubeHalfExtents));
            }
            else
            {
                //collisionShapes.PushBack(new BoxShape(CubeHalfExtents, CubeHalfExtents, CubeHalfExtents));
                collisionShapes.PushBack(new CylinderShape(CubeHalfExtents, CubeHalfExtents, CubeHalfExtents));
            }

            CollisionConfiguration collisionConf;

            // collision configuration contains default setup for memory, collision setup
            collisionConf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(collisionConf);

            if (UseCustomNearCallback)
                dispatcher.NearCallback = new NearCallback(CustomNearCallback);

            broadphase = new DbvtBroadphase();


            // the default constraint solver.
            solver = new SequentialImpulseConstraintSolver();

            world = new DiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConf);
            world.Gravity = new Vector3(0, -10, 0);

            // RandomizeOrder makes cylinder stacking a bit more stable
            world.SolverInfo.SolverMode |= SolverModes.RandomizeOrder;

            if (DoBenchmarkPyramids)
                world.SolverInfo.NumIterations = 4;

            world.DispatchInfo.EnableSpu = true;

            shapeIndex[0] = 0;
            for (i = 1; i < numObjects; i++)
                    shapeIndex[i] = 1;//sphere

            if (useCompound)
	        {
		        CompoundShape compoundShape = new CompoundShape();
		        CollisionShape oldShape = collisionShapes[1];
		        collisionShapes[1] = compoundShape;
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
                    CollisionShape shape = collisionShapes[shapeIndex[i]];
                    shape.Margin = collisionMargin;

                    RigidBody body;
                    Matrix trans;
                    if (i > 0)
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
                            row * 2 * CubeHalfExtents + CubeHalfExtents + ExtraHeight, 0);
                        
                        body = LocalCreateRigidBody(1, trans, shape);
                    }
                    else
                    {
                        trans = Matrix.Translation(0, ExtraHeight - CubeHalfExtents, 0);
                        body = LocalCreateRigidBody(0, trans, shape);
                        body.UserObject = "Ground";

                        if (UseKinematicGround)
                        {
                            body.CollisionFlags = body.CollisionFlags | CollisionFlags.KinematicObject;
                            body.ActivationState = ActivationState.DisableDeactivation;
                        }
                    }

                    // Only do CCD if  motion in one timestep (1.f/60.f) exceeds CubeHalfExtents
                    body.CcdMotionThreshold = CubeHalfExtents;

                    //Experimental: better estimation of CCD Time of Impact:
                    body.CcdSweptSphereRadius = 0.2f * CubeHalfExtents;
                }
            }

            if (DoBenchmarkPyramids)
            {
    	        LocalCreateRigidBody(0,Matrix.Translation(0,-CubeHalfExtents,0), collisionShapes[shapeIndex[0]]);

	            int numWalls = 15;
	            int wallHeight = 15;
	            float wallDistance = 3;


	            for (i=0;i<numWalls;i++)
	            {
		            float zPos = (i-numWalls/2) * wallDistance;
		            CreateStack(collisionShapes[shapeIndex[1]],CubeHalfExtents,wallHeight,zPos);
	            }
                // CreateStack(collisionShapes[shapeIndex[1]],halfExtends,20,10);

                // CreateStack(collisionShapes[shapeIndex[1]],halfExtends,20,20);


                // Destroyer ball
	            SphereShape ball = new SphereShape(2);
	            collisionShapes.PushBack(ball);
	            RigidBody ballBody = LocalCreateRigidBody(10000,Matrix.Translation(0,2,40),ball);
	            ballBody.LinearVelocity = new Vector3(0,0,-10);
            }
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
