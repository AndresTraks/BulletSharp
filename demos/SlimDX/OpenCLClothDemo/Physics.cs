using System;
using BulletSharp;
using BulletSharp.MultiThreaded;
using BulletSharp.SoftBody;
using BulletSharp.VectorMath.Aos;
using DemoFramework;
using SlimDX;

namespace OpenCLClothDemo
{
    class Physics : PhysicsContext
    {
        const int numFlags = 5;
        const int clothWidth = 40;
        const int clothHeight = 60;
        const float flagSpacing = 30;

        AlignedSoftBodyArray flags;

        SoftRigidDynamicsWorld SoftWorld
        {
            get { return (SoftRigidDynamicsWorld)World; }
        }

        public Physics()
        {
            CpuSoftBodySolver gSolver = new CpuSoftBodySolver();

            // collision configuration contains default setup for memory, collision setup
            CollisionConfiguration collisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(collisionConf);

            Broadphase = new DbvtBroadphase();
            Solver = new SequentialImpulseConstraintSolver();

            World = new SoftRigidDynamicsWorld(Dispatcher, Broadphase, Solver, collisionConf, gSolver);
            World.Gravity = new Vector3(0, -10, 0);

            // create the ground
            CollisionShape groundShape = new BoxShape(50, 50, 50);
            CollisionShapes.Add(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Translation(0, -50, 0), groundShape);
            ground.UserObject = "Ground";

            SoftWorld.WorldInfo.AirDensity = 1.2f;
            SoftWorld.WorldInfo.WaterDensity = 0;
            SoftWorld.WorldInfo.WaterOffset = 0;
            SoftWorld.WorldInfo.WaterNormal = Vector3.Zero;
            SoftWorld.WorldInfo.Gravity = new Vector3(0, -10, 0);

            CreateFlag(gSolver, clothWidth, clothHeight, out flags);

            gSolver.Optimize(SoftWorld.SoftBodyArray);
        }

        // Create a sequence of flag objects and add them to the world.
        void CreateFlag(SoftBodySolver solver, int width, int height, out AlignedSoftBodyArray flags)
        {
            flags = new AlignedSoftBodyArray();

	        // First create a triangle mesh to represent a flag

	        // Allocate a simple mesh consisting of a vertex array and a triangle index array
	        IndexedMesh mesh = new IndexedMesh();
	        mesh.NumVertices = width * height;
	        mesh.NumTriangles = 2*(width-1)*(height-1);

	        Vector3Array vertexArray = new Vector3Array(mesh.NumVertices);

	        mesh.VertexBase = vertexArray;
	        int[] triangleVertexIndexArray = new int[3*mesh.NumTriangles];
            /*
	        mesh.m_triangleIndexBase = reinterpret_cast<const unsigned char*>(triangleVertexIndexArray);
	        mesh.m_triangleIndexStride = sizeof(int)*3;
	        mesh.vertexStride = sizeof(Aos.Vector3);
            */
	        // Generate normalised object space vertex coordinates for a rectangular flag
	        float zCoordinate = 0.0f;

	        Matrix3 defaultScale = new Matrix3(new VMVector3(5, 0, 0), new VMVector3(0, 20, 0), new VMVector3(0, 0, 1));
	        for( int y = 0; y < height; ++y )
	        {
		        float yCoordinate = y*2.0f/(float)height - 1.0f;
		        for( int x = 0; x < width; ++x )
		        {			
			        float xCoordinate = x*2.0f/(float)width - 1.0f;

                    VMVector3 vertex = new VMVector3(xCoordinate, yCoordinate, zCoordinate);
                    VMVector3 transformedVertex = defaultScale * vertex;

			        vertexArray[y*width + x] = new Vector3(transformedVertex.X, transformedVertex.Y, transformedVertex.Z);

		        }
	        }

	        // Generate vertex indices for triangles
	        for( int y = 0; y < (height-1); ++y )
	        {
		        for( int x = 0; x < (width-1); ++x )
		        {	
			        // Triangle 0
			        // Top left of square on mesh
			        {
				        int vertex0 = y*width + x;
				        int vertex1 = vertex0 + 1;
				        int vertex2 = vertex0 + width;
				        int triangleIndex = 2*y*(width-1) + 2*x;
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex) / sizeof(int)] = vertex0;
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex + 1) / sizeof(int) + 1] = vertex1;
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex + 2) / sizeof(int) + 2] = vertex2;
			        }

			        // Triangle 1
			        // Bottom right of square on mesh
			        {
				        int vertex0 = y*width + x + 1;
				        int vertex1 = vertex0 + width;
				        int vertex2 = vertex1 - 1;
				        int triangleIndex = 2*y*(width-1) + 2*x + 1;
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex) / sizeof(int)] = vertex0;
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex) / sizeof(int) + 1] = vertex1;
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex) / sizeof(int) + 2] = vertex2;
			        }
		        }
	        }

        	
	        float rotateAngleRoundZ = 0.5f;
	        float rotateAngleRoundX = 0.5f;
	        Matrix defaultRotate = new Matrix();
	        defaultRotate.set_Rows(0, new Vector4((float)Math.Cos(rotateAngleRoundZ), (float)Math.Sin(rotateAngleRoundZ), 0, 0)); 
	        defaultRotate.set_Rows(1, new Vector4(-(float)Math.Sin(rotateAngleRoundZ), (float)Math.Cos(rotateAngleRoundZ), 0, 0));
	        defaultRotate.set_Rows(2, new Vector4(0, 0, 1, 0));
            Matrix defaultRotateX = new Matrix(); ;
	        defaultRotateX.set_Rows(0, new Vector4(1, 0, 0, 0));
	        defaultRotateX.set_Rows(1, new Vector4(0, (float)Math.Cos(rotateAngleRoundX), (float)Math.Sin(rotateAngleRoundX),0));
	        defaultRotateX.set_Rows(2, new Vector4(0, -(float)Math.Sin(rotateAngleRoundX), (float)Math.Cos(rotateAngleRoundX), 0));

	        Matrix defaultRotateAndScale = defaultRotateX * defaultRotate;


	        // Construct the sequence flags applying a slightly different translation to each one to arrange them
	        // appropriately in the scene.
	        for( int i = 0; i < numFlags; ++i )
	        {
		        float zTranslate = flagSpacing * (i-numFlags/2);

		        Vector3 defaultTranslate = new Vector3(0, 20, zTranslate);

		        Matrix transform = defaultRotateAndScale * Matrix.Translation(defaultTranslate);


		        SoftBody softBody = CreateFromIndexedMesh(vertexArray, mesh.NumVertices, triangleVertexIndexArray, mesh.NumTriangles, true);


		        for(int j = 0; j < mesh.NumVertices; ++j)
		        {
			        softBody.SetMass(j, 10.0f/mesh.NumVertices);
		        }
		        softBody.SetMass((height-i)*(width), 0);
		        softBody.SetMass((height-i)*(width) + width - 1, 0);
		        softBody.SetMass((height-i)*width + width/2, 0);
		        softBody.Cfg.Collisions = FCollisions.CLSS | FCollisions.CLRS;


		        flags.Add(softBody);

		        softBody.Transform(transform);
        		
		        SoftWorld.AddSoftBody( softBody );
	        }

	        //delete [] vertexArray;
	        //delete [] triangleVertexIndexArray;
        }

        SoftBody CreateFromIndexedMesh(Vector3Array vertexArray, int numVertices, int[] triangleVertexIndexArray, int numTriangles, bool createBendLinks)
        {
	        SoftBody softBody = new SoftBody(SoftWorld.WorldInfo, vertexArray, new float[]{});
	        Material structuralMaterial = softBody.AppendMaterial();
	        Material bendMaterial;
	        if( createBendLinks )
	        {
		        bendMaterial = softBody.AppendMaterial();
		        bendMaterial.Lst = 0.7f;
	        } else
            {
		        bendMaterial = null;
	        }
	        structuralMaterial.Lst = 1.0f;
        	

	        // List of values for each link saying which triangle is associated with that link
	        // -1 to start. Once a value is entered we know the "other" triangle
	        // and can add a link across the link
	        AlignedIntArray triangleForLinks = new AlignedIntArray();
	        triangleForLinks.Resize(numVertices * numVertices);
	        int numLinks = 0;
	        for(int triangle = 0; triangle < numTriangles; ++triangle)
	        {
		        int[] index = new int[]{triangleVertexIndexArray[triangle * 3], triangleVertexIndexArray[triangle * 3 + 1], triangleVertexIndexArray[triangle * 3 + 2]};
		        softBody.AppendFace(index[0], index[1], index[2]);
        		
		        // Generate the structural links directly from the triangles
		        //TestAndAddLink( triangleForLinks, softBody, triangle, triangleVertexIndexArray, numVertices, index[0], index[1], index[2], structuralMaterial, createBendLinks, bendMaterial );
		        //TestAndAddLink( triangleForLinks, softBody, triangle, triangleVertexIndexArray, numVertices, index[1], index[2], index[0], structuralMaterial, createBendLinks, bendMaterial );
		        //TestAndAddLink( triangleForLinks, softBody, triangle, triangleVertexIndexArray, numVertices, index[2], index[0], index[1], structuralMaterial, createBendLinks, bendMaterial);
	        }

	        return softBody;
        }

    }
}
