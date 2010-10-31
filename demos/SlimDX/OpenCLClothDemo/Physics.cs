using System;
using BulletSharp;
using BulletSharp.MultiThreaded;
using BulletSharp.SoftBody;
//using BulletSharp.VectorMath.Aos;
using DemoFramework;
using SlimDX;

namespace OpenCLClothDemo
{
    class Physics : PhysicsContext
    {
        bool UseGpuSolver = true;

        const int numFlags = 5;
        const int clothWidth = 20;//40;
        const int clothHeight = 30;//60;
        const float flagSpacing = 30;
        float _windAngle = 1.0f;//0.4f;
        float _windStrength = 15;

        AlignedSoftBodyArray flags;
        Cloth[] cloths;
        SoftBodySolver gSolver;
        BulletSharp.Clock clock = new BulletSharp.Clock();

        SoftRigidDynamicsWorld SoftWorld
        {
            get { return (SoftRigidDynamicsWorld)World; }
        }

        public Physics()
        {
            CLStuff.InitCL();

            cloths = new Cloth[numFlags];
            for (int flagIndex = 0; flagIndex < numFlags; ++flagIndex)
            {
                cloths[flagIndex] = new Cloth();
                cloths[flagIndex].CreateBuffers(clothWidth, clothHeight);
            }


            if (UseGpuSolver)
            {
                gSolver = new OpenCLSoftBodySolver(CLStuff.commandQueue, CLStuff.cxMainContext);
            }
            else
            {
                gSolver = new CpuSoftBodySolver();
            }

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
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Translation(0, -60, 0), groundShape);
            ground.UserObject = "Ground";


            SoftWorld.WorldInfo.AirDensity = 1.2f;
            SoftWorld.WorldInfo.WaterDensity = 0;
            SoftWorld.WorldInfo.WaterOffset = 0;
            SoftWorld.WorldInfo.WaterNormal = Vector3.Zero;
            SoftWorld.WorldInfo.Gravity = new Vector3(0, -10, 0);


            CreateFlag(clothWidth, clothHeight, out flags);

            // Create output buffer descriptions for ecah flag
            // These describe where the simulation should send output data to
            for (int flagIndex = 0; flagIndex < flags.Count; ++flagIndex)
            {
                // flags[flagIndex].WindVelocity = new Vector3(0, 0, 15.0f);

                // In this case we have a DX11 output buffer with a vertex at index 0, 8, 16 and so on as well as a normal at 3, 11, 19 etc.
                // Copies will be performed GPU-side directly into the output buffer

                CpuVertexBufferDescriptor vertexBufferDescriptor = new CpuVertexBufferDescriptor(cloths[flagIndex].CpuBuffer, 0, 8, 3, 8);
                cloths[flagIndex].VertexBufferDescriptor = vertexBufferDescriptor;
            }

            gSolver.Optimize(SoftWorld.SoftBodyArray);

            World.StepSimulation(1.0f / 60.0f, 0);
        }

        // Create a sequence of flag objects and add them to the world.
        void CreateFlag(int width, int height, out AlignedSoftBodyArray flags)
        {
            flags = new AlignedSoftBodyArray();

            // First create a triangle mesh to represent a flag

            // Allocate a simple mesh consisting of a vertex array and a triangle index array
            IndexedMesh mesh = new IndexedMesh();
            mesh.NumVertices = width * height;
            mesh.NumTriangles = 2 * (width - 1) * (height - 1);

            Vector3Array vertexArray = new Vector3Array(mesh.NumVertices);
            mesh.VertexBase = vertexArray;
            mesh.VertexStride = Vector3.SizeInBytes;

            IntArray triangleVertexIndexArray = new IntArray(3 * mesh.NumTriangles);
            mesh.TriangleIndexBase = triangleVertexIndexArray;
            mesh.TriangleIndexStride = sizeof(int) * 3;


            // Generate normalised object space vertex coordinates for a rectangular flag

            Matrix defaultScale = Matrix.Scaling(5, 20, 1);
            for (int y = 0; y < height; ++y)
            {
                float yCoordinate = y * 2.0f / (float)height - 1.0f;
                for (int x = 0; x < width; ++x)
                {
                    float xCoordinate = x * 2.0f / (float)width - 1.0f;

                    Vector3 vertex = new Vector3(xCoordinate, yCoordinate, 0.0f);
                    vertexArray[y * width + x] = Vector3.TransformCoordinate(vertex, defaultScale);
                }
            }

            // Generate vertex indices for triangles
            for (int y = 0; y < (height - 1); ++y)
            {
                for (int x = 0; x < (width - 1); ++x)
                {
                    // Triangle 0
                    // Top left of square on mesh
                    {
                        int vertex0 = y * width + x;
                        int vertex1 = vertex0 + 1;
                        int vertex2 = vertex0 + width;
                        int triangleIndex = 2 * (y * (width - 1) + x);
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex) / sizeof(int)] = vertex0;
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex + 1) / sizeof(int) + 1] = vertex1;
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex + 2) / sizeof(int) + 2] = vertex2;
                    }

                    // Triangle 1
                    // Bottom right of square on mesh
                    {
                        int vertex0 = y * width + x + 1;
                        int vertex1 = vertex0 + width;
                        int vertex2 = vertex1 - 1;
                        int triangleIndex = 2 * y * (width - 1) + 2 * x + 1;
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex) / sizeof(int)] = vertex0;
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex) / sizeof(int) + 1] = vertex1;
                        triangleVertexIndexArray[(mesh.TriangleIndexStride * triangleIndex) / sizeof(int) + 2] = vertex2;
                    }
                }
            }


            Matrix defaultRotateAndScale = Matrix.RotationX(0.5f) * Matrix.RotationZ(0.5f);

            // Construct the sequence flags applying a slightly different translation to each one to arrange them
            // appropriately in the scene.
            for (int i = 0; i < numFlags; ++i)
            {
                float zTranslate = flagSpacing * (i - numFlags / 2);

                Vector3 defaultTranslate = new Vector3(0, 20, zTranslate);
                Matrix transform = defaultRotateAndScale * Matrix.Translation(defaultTranslate);


                SoftBody softBody = CreateFromIndexedMesh(vertexArray, triangleVertexIndexArray, true);


                for (int j = 0; j < mesh.NumVertices; ++j)
                {
                    softBody.SetMass(j, 10.0f / mesh.NumVertices);
                }
                softBody.SetMass((height - 1) * width, 0);
                softBody.SetMass((height - 1) * width + width - 1, 0);
                softBody.SetMass((height - 1) * width + width / 2, 0);
                softBody.Cfg.Collisions = FCollisions.CLSS | FCollisions.CLRS;


                flags.Add(softBody);

                softBody.Transform(transform);

                SoftWorld.AddSoftBody(softBody);
            }

            //delete [] vertexArray;
            //delete [] triangleVertexIndexArray;
        }

        SoftBody CreateFromIndexedMesh(Vector3Array vertexArray, IntArray triangleVertexIndexArray, bool createBendLinks)
        {
            SoftBody softBody = new SoftBody(SoftWorld.WorldInfo, vertexArray, null);
            Material structuralMaterial = softBody.AppendMaterial();
            Material bendMaterial;
            if (createBendLinks)
            {
                bendMaterial = softBody.AppendMaterial();
                bendMaterial.Lst = 0.7f;
            }
            else
            {
                bendMaterial = null;
            }
            structuralMaterial.Lst = 1.0f;


            int numVertices = vertexArray.Count;
            int numTriangles = triangleVertexIndexArray.Count / 3;

            // List of values for each link saying which triangle is associated with that link
            // -1 to start. Once a value is entered we know the "other" triangle
            // and can add a link across the link
            AlignedIntArray triangleForLinks = new AlignedIntArray();
            triangleForLinks.Resize(numVertices * numVertices, -1);

            for (int triangle = 0; triangle < numTriangles; ++triangle)
            {
                int[] index = new int[] { triangleVertexIndexArray[triangle * 3], triangleVertexIndexArray[triangle * 3 + 1], triangleVertexIndexArray[triangle * 3 + 2] };
                softBody.AppendFace(index[0], index[1], index[2]);

                // Generate the structural links directly from the triangles
                TestAndAddLink(triangleForLinks, softBody, triangle, triangleVertexIndexArray, numVertices, index[0], index[1], index[2], structuralMaterial, createBendLinks, bendMaterial);
                TestAndAddLink(triangleForLinks, softBody, triangle, triangleVertexIndexArray, numVertices, index[1], index[2], index[0], structuralMaterial, createBendLinks, bendMaterial);
                TestAndAddLink(triangleForLinks, softBody, triangle, triangleVertexIndexArray, numVertices, index[2], index[0], index[1], structuralMaterial, createBendLinks, bendMaterial);
            }

            return softBody;
        }

        // Helper to test and add links correctly.
        // Records links that have already been generated
        static bool TestAndAddLink(AlignedIntArray trianglesForLinks, SoftBody softBody, int triangle, IntArray triangleVertexIndexArray, int numVertices, int vertex0, int vertex1, int nonLinkVertex, Material structuralMaterial, bool createBendLinks, Material bendMaterial)
        {
            if (trianglesForLinks[numVertices * vertex0 + vertex1] >= 0 && createBendLinks)
            {
                // Already have link so find other triangle and generate cross link

                int otherTriangle = trianglesForLinks[numVertices * vertex0 + vertex1];
                int[] otherIndices = new int[] { triangleVertexIndexArray[otherTriangle * 3], triangleVertexIndexArray[otherTriangle * 3 + 1], triangleVertexIndexArray[otherTriangle * 3 + 2] };

                int nodeA = 0;
                // Test all links of the other triangle against this link. The one that's not part of it is what we want.
                if (otherIndices[0] != vertex0 && otherIndices[0] != vertex1)
                    nodeA = otherIndices[0];
                if (otherIndices[1] != vertex0 && otherIndices[1] != vertex1)
                    nodeA = otherIndices[1];
                if (otherIndices[2] != vertex0 && otherIndices[2] != vertex1)
                    nodeA = otherIndices[2];

                softBody.AppendLink(nodeA, nonLinkVertex, bendMaterial);
            }
            else
            {
                // Don't yet have link so create it
                softBody.AppendLink(vertex0, vertex1, structuralMaterial);

                // If we added a new link, set the triangle array
                trianglesForLinks[numVertices * vertex0 + vertex1] = triangle;
                trianglesForLinks[numVertices * vertex1 + vertex0] = triangle;

            }

            return true;
        }

        static int counter = 0;
        static Random random = new Random();
        static int frameCount = 0;

        public override int Update(float elapsedTime)
        {
            float dt = clock.TimeMicroseconds;
            clock.Reset();

            int ret = World.StepSimulation(dt / 1000000.0f);
            frameCount++;
            if (frameCount == 100)
            {
                ret += World.StepSimulation(1.0f / 60.0f, 0);
            }

            //int ret = base.Update(elapsedTime);

            // Change wind velocity a bit based on a frame counter
            if ((counter % 400) == 0)
            {
                _windAngle = (_windAngle + 0.05f);
                if (_windAngle > (2 * 3.141))
                    _windAngle = 0;

                for (int flagIndex = 0; flagIndex < flags.Count; ++flagIndex)
                {
                    SoftBody cloth = flags[flagIndex];

                    float localWind = _windAngle + 0.5f * (((float)random.NextDouble()) - 0.1f);
                    float xCoordinate = (float)Math.Cos(localWind) * _windStrength;
                    float zCoordinate = (float)Math.Sin(localWind) * _windStrength;

                    cloth.WindVelocity = new Vector3(xCoordinate, 0, zCoordinate);
                }
            }

            //btVector3 origin( capCollider->getWorldTransform().getOrigin() );
            //origin.setX( origin.getX() + 0.05 );
            //capCollider->getWorldTransform().setOrigin( origin );

            counter++;

            for (int flagIndex = 0; flagIndex < flags.Count; ++flagIndex)
            {
                gSolver.CopySoftBodyToVertexBuffer(flags[flagIndex], cloths[flagIndex].VertexBufferDescriptor);
                flags[flagIndex].UserObject = new object[] { cloths[flagIndex].CpuBuffer, cloths[flagIndex].Indices };
            }


            return ret;
        }
    }
}
