using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using BulletSharp;
using DemoFramework;

namespace ConvexDecompositionDemo
{
    class MyConvexDecomposition : IConvexDecomposition
    {
        StreamWriter output;
        ConvexDecompositionDemo demo;
        CultureInfo floatFormat = new CultureInfo("en-US");

        public AlignedCollisionShapeArray convexShapes = new AlignedCollisionShapeArray();
        public AlignedVector3Array convexCentroids = new AlignedVector3Array();

        int mHullCount = 0;
        int mBaseCount = 0;

        public MyConvexDecomposition(StreamWriter output, ConvexDecompositionDemo demo)
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

            output.WriteLine("## Hull Piece {0} with {1} vertices and {2} triangles.", mHullCount, result.mHullVertices.Length, result.mHullIndices.Length / 3);

            output.WriteLine("usemtl Material{0}", mBaseCount);
            output.WriteLine("o Object{0}", mBaseCount);

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
                    demo.centroid += vertex * localScaling;
                }
            }

            demo.centroid /= (float)result.mHullVertices.Length;

            if (true)
            {
                foreach (Vector3 vertex in result.mHullVertices)
                {
                    vertices.Add(vertex * localScaling - demo.centroid);
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


                    Vector3 vertex0 = result.mHullVertices[index0] * localScaling - demo.centroid;
                    Vector3 vertex1 = result.mHullVertices[index1] * localScaling - demo.centroid;
                    Vector3 vertex2 = result.mHullVertices[index2] * localScaling - demo.centroid;

                    trimesh.AddTriangle(vertex0, vertex1, vertex2);

                    index0 += mBaseCount;
                    index1 += mBaseCount;
                    index2 += mBaseCount;

                    output.WriteLine("f {0} {1} {2}", index0 + 1, index1 + 1, index2 + 1);
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

    class ConvexDecompositionDemo : Demo
    {
        Vector3 eye = new Vector3(35, 10, 35);
        Vector3 target = new Vector3(0, 5, 0);

        public Vector3 centroid;
        Vector3 convexDecompositionObjectOffset;
        public AlignedTriangleMeshArray trimeshes = new AlignedTriangleMeshArray();

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - Convex Decomposition Demo");
            Graphics.SetInfoText("Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                //"F11 - Toggle fullscreen\n" +
                "Space - Shoot box");
        }

        // MyContactCallback is just an example to show how to get access to the child shape that collided
        void MyContactCallback(ManifoldPoint cp, CollisionObjectWrapper colObj0Wrap, int partId0, int index0, CollisionObjectWrapper colObj1Wrap, int partId1, int index1)
        {
            if (colObj0Wrap.CollisionObject.CollisionShape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                CompoundShape compound = colObj0Wrap.CollisionObject.CollisionShape as CompoundShape;
                CollisionShape childShape = compound.GetChildShape(index0);
            }

            if (colObj1Wrap.CollisionObject.CollisionShape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                CompoundShape compound = colObj1Wrap.CollisionObject.CollisionShape as CompoundShape;
                CollisionShape childShape = compound.GetChildShape(index1);
            }
        }

        /*
        void MyContactCallback(object sender, ContactAddedEventArgs e)
        {
            if (e.CollisionObject0Wrapper.CollisionObject.CollisionShape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                CompoundShape compound = e.CollisionObject0Wrapper.CollisionObject.CollisionShape as CompoundShape;
                CollisionShape childShape = compound.GetChildShape(e.Index0);
            }

            if (e.CollisionObject1Wrapper.CollisionObject.CollisionShape.ShapeType == BroadphaseNativeType.CompoundShape)
            {
                CompoundShape compound = e.CollisionObject1Wrapper.CollisionObject.CollisionShape as CompoundShape;
                CollisionShape childShape = compound.GetChildShape(e.Index1);
            }

            e.IsContactModified = true;
        }
        */

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

        protected override void OnInitializePhysics()
        {
            ManifoldPoint.ContactAdded += MyContactCallback;

            SetupEmptyDynamicsWorld();

            WavefrontObj wo = new WavefrontObj();
            int tcount = wo.LoadObj("data/file.obj");
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

                    Vector3 vertex0 = vertices[index0] * localScaling;
                    Vector3 vertex1 = vertices[index1] * localScaling;
                    Vector3 vertex2 = vertices[index2] * localScaling;

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

                const bool useQuantization = true;
                CollisionShape concaveShape = new BvhTriangleMeshShape(trimesh, useQuantization);
                LocalCreateRigidBody(0, Matrix.Translation(convexDecompositionObjectOffset), concaveShape);

                CollisionShapes.Add(concaveShape);


                // Bullet Convex Decomposition

                FileStream outputFile = new FileStream("file_convex.obj", FileMode.Create, FileAccess.Write);
                StreamWriter writer = new StreamWriter(outputFile);

                DecompDesc desc = new DecompDesc
                {
                    mVertices = wo.Vertices.ToArray(),
                    mTcount = tcount,
                    mIndices = wo.Indices.ToArray(),
                    mDepth = 5,
                    mCpercent = 5,
                    mPpercent = 15,
                    mMaxVertices = 16,
                    mSkinWidth = 0.0f
                };

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
                const double concavity = 100;
                //bool invert = false;
                const bool addExtraDistPoints = false;
                const bool addNeighboursDistPoints = false;
                const bool addFacesPoints = false;

                myHACD.NClusters = nClusters;                     // minimum number of clusters
                myHACD.VerticesPerConvexHull = 100;               // max of 100 vertices per convex-hull
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

                writer.Dispose();
                outputFile.Dispose();
            }
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new ConvexDecompositionDemo())
            {
                LibraryManager.Initialize(demo);
            }
        }
    }
}
