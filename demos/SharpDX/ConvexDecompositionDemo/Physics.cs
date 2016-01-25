using BulletSharp;
using DemoFramework;
using SharpDX;
using System.Collections.Generic;
using System.Globalization;
using System.IO;

namespace ConvexDecompositionDemo
{
    class MyConvexDecomposition : IConvexDecomposition
    {
        StreamWriter output;
        Physics demo;
        CultureInfo floatFormat = new CultureInfo("en-US");

        public List<CollisionShape> convexShapes = new List<CollisionShape>();
        public AlignedVector3Array convexCentroids = new AlignedVector3Array();

        int mHullCount = 0;
        int mBaseCount = 0;

        public MyConvexDecomposition(StreamWriter output, Physics demo)
        {
            this.output = output;
            this.demo = demo;
        }

        public override void ConvexDecompResult(ConvexResult result)
        {
            TriangleMesh trimesh = new TriangleMesh();
            demo.trimeshes.Add(trimesh);

            Vector3 localScaling = new Vector3(6.0f, 6.0f, 6.0f);

            if (output == null)
                return;

            output.WriteLine(string.Format("## Hull Piece {0} with {1} vertices and {2} triangles.", mHullCount, result.mHullVertices.Length, result.mHullIndices.Length / 3));

            output.WriteLine(string.Format("usemtl Material{0}", mBaseCount));
            output.WriteLine(string.Format("o Object{0}", mBaseCount));

            foreach (Vector3 p in result.mHullVertices)
            {
                output.WriteLine(string.Format(floatFormat, "v {0:F9} {1:F9} {2:F9}", p.X, p.Y, p.Z));
            }

            //calc centroid, to shift vertices around center of mass
            demo.centroid = Vector3.Zero;

            AlignedVector3Array vertices = new AlignedVector3Array();
            if (true)
            {
                foreach (Vector3 vertex in result.mHullVertices)
                {
                    demo.centroid += Vector3.Multiply(vertex, localScaling);
                }
            }

            demo.centroid /= (float)result.mHullVertices.Length;

            if (true)
            {
                foreach (Vector3 vertex in result.mHullVertices)
                {
                    vertices.Add(Vector3.Multiply(vertex, localScaling) - demo.centroid);
                }
            }

            if (true)
            {
                int[] src = result.mHullIndices;
                for (int i = 0; i < src.Length; i += 3)
                {
                    int index0 = src[i];
                    int index1 = src[i + 1];
                    int index2 = src[i + 2];


                    Vector3 vertex0 = Vector3.Multiply(result.mHullVertices[index0], localScaling) - demo.centroid;
                    Vector3 vertex1 = Vector3.Multiply(result.mHullVertices[index1], localScaling) - demo.centroid;
                    Vector3 vertex2 = Vector3.Multiply(result.mHullVertices[index2], localScaling) - demo.centroid;

                    trimesh.AddTriangle(vertex0, vertex1, vertex2);

                    index0 += mBaseCount;
                    index1 += mBaseCount;
                    index2 += mBaseCount;

                    output.WriteLine(string.Format("f {0} {1} {2}", index0 + 1, index1 + 1, index2 + 1));
                }
            }

            //this is a tools issue: due to collision margin, convex objects overlap, compensate for it here:
            //#define SHRINK_OBJECT_INWARDS 1
#if SHRINK_OBJECT_INWARDS

			float collisionMargin = 0.01f;
					
			btAlignedObjectArray<btVector3> planeEquations;
			btGeometryUtil::getPlaneEquationsFromVertices(vertices,planeEquations);

			btAlignedObjectArray<btVector3> shiftedPlaneEquations;
			for (int p=0;p<planeEquations.size();p++)
			{
				btVector3 plane = planeEquations[p];
				plane[3] += collisionMargin;
				shiftedPlaneEquations.push_back(plane);
			}
			btAlignedObjectArray<btVector3> shiftedVertices;
			btGeometryUtil::getVerticesFromPlaneEquations(shiftedPlaneEquations,shiftedVertices);

					
			btConvexHullShape* convexShape = new btConvexHullShape(&(shiftedVertices[0].getX()),shiftedVertices.size());
					
#else //SHRINK_OBJECT_INWARDS

            ConvexHullShape convexShape = new ConvexHullShape(vertices);
#endif

            convexShape.Margin = 0.01f;
            convexShapes.Add(convexShape);
            convexCentroids.Add(demo.centroid);
            demo.CollisionShapes.Add(convexShape);
            mBaseCount += result.mHullVertices.Length; // advance the 'base index' counter.
        }
    }

    class Physics : PhysicsContext
    {
        public Vector3 centroid;
        Vector3 convexDecompositionObjectOffset;
        public List<TriangleMesh> trimeshes = new List<TriangleMesh>();

        // MyContactCallback is just an example to show how to get access to the child shape that collided
        bool MyContactCallback(ManifoldPoint cp, CollisionObject colObj0, int partId0, int index0, CollisionObject colObj1, int partId1, int index1)
        {
            if (colObj0.CollisionShape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                CompoundShape compound = colObj0.CollisionShape as CompoundShape;
                CollisionShape childShape = compound.GetChildShape(index0);
            }

            if (colObj1.CollisionShape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                CompoundShape compound = colObj1.CollisionShape as CompoundShape;
                CollisionShape childShape = compound.GetChildShape(index1);
            }

            return true;
        }

        public void SetupEmptyDynamicsWorld()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            convexDecompositionObjectOffset = new Vector3(10, 0, 0);

            Broadphase = new AxisSweep3(new Vector3(-10000, -10000, -10000), new Vector3(10000, 10000, 10000));
            //Broadphase = new SimpleBroadphase();

            Solver = new SequentialImpulseConstraintSolver();
            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);

            // create the ground
            CollisionShape groundShape = new BoxShape(30, 2, 30);
            CollisionShapes.Add(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Translation(0, -4.5f, 0), groundShape);
            ground.UserObject = "Ground";

            // create a few dynamic rigidbodies
            float mass = 1.0f;

            CollisionShape colShape = new BoxShape(1);
            CollisionShapes.Add(colShape);
            Vector3 localInertia = colShape.CalculateLocalInertia(mass);
        }

        public override void InitPhysics()
        {
            SetupEmptyDynamicsWorld();

            WavefrontObj wo = new WavefrontObj();
            int tcount = wo.LoadObj("file.obj");
            if (tcount > 0)
            {
                TriangleMesh trimesh = new TriangleMesh();
                trimeshes.Add(trimesh);

                Vector3 localScaling = new Vector3(6, 6, 6);
                List<int> indices = wo.Indices;
                List<Vector3> vertices = wo.Vertices;

                int i;
                for (i = 0; i < tcount; i++)
                {
                    int index0 = indices[i * 3];
                    int index1 = indices[i * 3 + 1];
                    int index2 = indices[i * 3 + 2];

                    Vector3 vertex0 = Vector3.Multiply(vertices[index0], localScaling);
                    Vector3 vertex1 = Vector3.Multiply(vertices[index1], localScaling);
                    Vector3 vertex2 = Vector3.Multiply(vertices[index2], localScaling);

                    trimesh.AddTriangle(vertex0, vertex1, vertex2);
                }

                ConvexShape tmpConvexShape = new ConvexTriangleMeshShape(trimesh);

                //create a hull approximation
                ShapeHull hull = new ShapeHull(tmpConvexShape);
                float margin = tmpConvexShape.Margin;
                hull.BuildHull(margin);
                tmpConvexShape.UserObject = hull;

                ConvexHullShape convexShape = new ConvexHullShape();
                foreach (Vector3 v in hull.Vertices)
                {
                    convexShape.AddPoint(v);
                }

                tmpConvexShape.Dispose();
                //hull.Dispose();


                CollisionShapes.Add(convexShape);

                float mass = 1.0f;

                LocalCreateRigidBody(mass, Matrix.Translation(0, 2, 14), convexShape);

                bool useQuantization = true;
                CollisionShape concaveShape = new BvhTriangleMeshShape(trimesh, useQuantization);
                LocalCreateRigidBody(0, Matrix.Translation(convexDecompositionObjectOffset), concaveShape);

                CollisionShapes.Add(concaveShape);


                // Bullet Convex Decomposition

                FileStream outputFile = new FileStream("file_convex.obj", FileMode.Create, FileAccess.Write);
                StreamWriter writer = new StreamWriter(outputFile);

                DecompDesc desc = new DecompDesc();
                desc.mVertices = wo.Vertices.ToArray();
                desc.mTcount = tcount;
                desc.mIndices = wo.Indices.ToArray();
                desc.mDepth = 5;
                desc.mCpercent = 5;
                desc.mPpercent = 15;
                desc.mMaxVertices = 16;
                desc.mSkinWidth = 0.0f;

                MyConvexDecomposition convexDecomposition = new MyConvexDecomposition(writer, this);
                desc.mCallback = convexDecomposition;


                // HACD

                Hacd myHACD = new Hacd();
                myHACD.SetPoints(wo.Vertices);
                myHACD.SetTriangles(wo.Indices);
                myHACD.CompacityWeight = 0.1;
                myHACD.VolumeWeight = 0.0;

                // HACD parameters
                // Recommended parameters: 2 100 0 0 0 0
                int nClusters = 2;
                double concavity = 100;
                //bool invert = false;
                bool addExtraDistPoints = false;
                bool addNeighboursDistPoints = false;
                bool addFacesPoints = false;

                myHACD.NClusters = nClusters;                     // minimum number of clusters
                myHACD.NumVerticesPerConvexHull = 100;               // max of 100 vertices per convex-hull
                myHACD.Concavity = concavity;                     // maximum concavity
                myHACD.AddExtraDistPoints = addExtraDistPoints;
                myHACD.AddNeighboursDistPoints = addNeighboursDistPoints;
                myHACD.AddFacesPoints = addFacesPoints;

                myHACD.Compute();
                nClusters = myHACD.NClusters;

                myHACD.Save("output.wrl", false);


                if (true)
                {
                    CompoundShape compound = new CompoundShape();
                    CollisionShapes.Add(compound);

                    Matrix trans = Matrix.Identity;

                    for (int c = 0; c < nClusters; c++)
                    {
                        //generate convex result
                        Vector3[] points;
                        int[] triangles;
                        myHACD.GetCH(c, out points, out triangles);

                        ConvexResult r = new ConvexResult(points, triangles);
                        convexDecomposition.ConvexDecompResult(r);
                    }

                    for (i = 0; i < convexDecomposition.convexShapes.Count; i++)
                    {
                        Vector3 centroid = convexDecomposition.convexCentroids[i];
                        trans = Matrix.Translation(centroid);
                        ConvexHullShape convexShape2 = convexDecomposition.convexShapes[i] as ConvexHullShape;
                        compound.AddChildShape(trans, convexShape2);

                        RigidBody body = LocalCreateRigidBody(1.0f, trans, convexShape2);
                    }

#if true
                    mass = 10.0f;
                    trans = Matrix.Translation(-convexDecompositionObjectOffset);
                    RigidBody body2 = LocalCreateRigidBody(mass, trans, compound);
                    body2.CollisionFlags |= CollisionFlags.CustomMaterialCallback;

                    convexDecompositionObjectOffset.Z = 6;
                    trans = Matrix.Translation(-convexDecompositionObjectOffset);
                    body2 = LocalCreateRigidBody(mass, trans, compound);
                    body2.CollisionFlags |= CollisionFlags.CustomMaterialCallback;

                    convexDecompositionObjectOffset.Z = -6;
                    trans = Matrix.Translation(-convexDecompositionObjectOffset);
                    body2 = LocalCreateRigidBody(mass, trans, compound);
                    body2.CollisionFlags |= CollisionFlags.CustomMaterialCallback;
#endif
                }

                if (outputFile != null)
                {
                    if (writer != null)
                    {
                        writer.Dispose();
                    }
                    outputFile.Dispose();
                }
            }
        }
    }
}
