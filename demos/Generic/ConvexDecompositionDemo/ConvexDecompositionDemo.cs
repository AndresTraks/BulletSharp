﻿using BulletSharp;
using DemoFramework;
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace ConvexDecompositionDemo
{
    class ConvexDecompositionDemo : Demo
    {
        Vector3 eye = new Vector3(35, 10, 35);
        Vector3 target = new Vector3(0, 5, 0);

        Vector3 convexDecompositionObjectOffset;
        List<TriangleMesh> trimeshes = new List<TriangleMesh>();
        public bool sEnableSAT = false;

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - Convex Decomposition Demo");
        }

        bool MyCompoundChildShapeCallback(CollisionShape shape0, CollisionShape shape1)
        {
            return true;
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
            Broadphase = new AxisSweep3(new Vector3(-10000, -10000, -10000), new Vector3(10000, 10000, 10000));
            Solver = new SequentialImpulseConstraintSolver();
            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);

            // create the ground
            CollisionShape groundShape = new BoxShape(30, 2, 30);
            CollisionShapes.Add(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Translation(0, -4.5f, 0), groundShape);
            ground.UserObject = "Ground";
        }

        protected override void OnInitializePhysics()
        {
            ManifoldPoint.ContactAdded += MyContactCallback;

            SetupEmptyDynamicsWorld();

            CompoundCollisionAlgorithm.CompoundChildShapePairCallback = MyCompoundChildShapeCallback;
            convexDecompositionObjectOffset = new Vector3(10, 0, 0);


            // Load wavefront file
            var wo = new WavefrontObj();
            int tcount = wo.LoadObj("data/file.obj");
            if (tcount == 0)
            {
                return;
            }

            // Convert file data to TriangleMesh
            var trimesh = new TriangleMesh();
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

                trimesh.AddTriangleRef(ref vertex0, ref vertex1, ref vertex2);
            }

            // Create a hull approximation
            ConvexHullShape convexShape;
            using (var tmpConvexShape = new ConvexTriangleMeshShape(trimesh))
            {
                using (var hull = new ShapeHull(tmpConvexShape))
                {
                    hull.BuildHull(tmpConvexShape.Margin);
                    convexShape = new ConvexHullShape(hull.Vertices);
                }
            }
            if (sEnableSAT)
            {
                convexShape.InitializePolyhedralFeatures();
            }
            CollisionShapes.Add(convexShape);


            // Add non-moving body to world
            float mass = 1.0f;
            LocalCreateRigidBody(mass, Matrix.Translation(0, 2, 14), convexShape);

            const bool useQuantization = true;
            var concaveShape = new BvhTriangleMeshShape(trimesh, useQuantization);
            LocalCreateRigidBody(0, Matrix.Translation(convexDecompositionObjectOffset), concaveShape);

            CollisionShapes.Add(concaveShape);


            // HACD
            var hacd = new Hacd();
            hacd.SetPoints(wo.Vertices);
            hacd.SetTriangles(wo.Indices);
            hacd.CompacityWeight = 0.1;
            hacd.VolumeWeight = 0.0;

            // Recommended HACD parameters: 2 100 false false false
            hacd.NClusters = 2;                      // minimum number of clusters
            hacd.Concavity = 100;                    // maximum concavity
            hacd.AddExtraDistPoints = false;
            hacd.AddNeighboursDistPoints = false;
            hacd.AddFacesPoints = false;
            hacd.NumVerticesPerConvexHull = 100;     // max of 100 vertices per convex-hull

            hacd.Compute();
            hacd.Save("output.wrl", false);


            // Generate convex result
            var outputFile = new FileStream("file_convex.obj", FileMode.Create, FileAccess.Write);
            var writer = new StreamWriter(outputFile);

            var convexDecomposition = new ConvexDecomposition(writer, this);
            convexDecomposition.LocalScaling = localScaling;

            for (int c = 0; c < hacd.NClusters; c++)
            {
                Vector3[] points;
                int[] triangles;
                hacd.GetCH(c, out points, out triangles);

                convexDecomposition.ConvexDecompResult(points, triangles);
            }


            // Combine convex shapes into a compound shape
            var compound = new CompoundShape();
            for (i = 0; i < convexDecomposition.convexShapes.Count; i++)
            {
                Vector3 centroid = convexDecomposition.convexCentroids[i];
                var convexShape2 = convexDecomposition.convexShapes[i];
                Matrix trans = Matrix.Translation(centroid);
                if (sEnableSAT)
                {
                    convexShape2.InitializePolyhedralFeatures();
                }
                CollisionShapes.Add(convexShape2);
                compound.AddChildShape(trans, convexShape2);

                LocalCreateRigidBody(1.0f, trans, convexShape2);
            }
            CollisionShapes.Add(compound);

            writer.Dispose();
            outputFile.Dispose();

#if true
            mass = 10.0f;
            var body2 = LocalCreateRigidBody(mass, Matrix.Translation(-convexDecompositionObjectOffset), compound);
            body2.CollisionFlags |= CollisionFlags.CustomMaterialCallback;

            convexDecompositionObjectOffset.Z = 6;
            body2 = LocalCreateRigidBody(mass, Matrix.Translation(-convexDecompositionObjectOffset), compound);
            body2.CollisionFlags |= CollisionFlags.CustomMaterialCallback;

            convexDecompositionObjectOffset.Z = -6;
            body2 = LocalCreateRigidBody(mass, Matrix.Translation(-convexDecompositionObjectOffset), compound);
            body2.CollisionFlags |= CollisionFlags.CustomMaterialCallback;
#endif
        }

        public override void OnHandleInput()
        {
            base.OnHandleInput();

            if (Input.KeysPressed.Contains(Keys.T))
            {
                sEnableSAT = !sEnableSAT;
                if (sEnableSAT)
                {
                    Console.WriteLine("SAT enabled after the next restart of the demo");
                }
                else
                {
                    Console.WriteLine("SAT disabled after the next restart of the demo");
                }
            }
        }

        public override void ExitPhysics()
        {
            base.ExitPhysics();

            foreach (var trimesh in trimeshes)
            {
                trimesh.Dispose();
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
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
