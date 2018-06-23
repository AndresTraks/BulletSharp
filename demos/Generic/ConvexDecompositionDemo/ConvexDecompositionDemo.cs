using BulletSharp;
using DemoFramework;
using DemoFramework.FileLoaders;
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace ConvexDecompositionDemo
{
    sealed class ConvexDecompositionDemo : Demo
    {
        private bool _enableSat = false;

        protected override void OnInitialize()
        {
            Freelook.Eye = new Vector3(35, 10, 35);
            Freelook.Target = new Vector3(0, 5, 0);

            Graphics.SetFormText("BulletSharp - Convex Decomposition Demo");
        }

        private bool MyCompoundChildShapeCallback(CollisionShape shape0, CollisionShape shape1)
        {
            return true;
        }

        private void SetupEmptyDynamicsWorld()
        {
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);
            Broadphase = new AxisSweep3(new Vector3(-10000, -10000, -10000), new Vector3(10000, 10000, 10000));
            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, CollisionConf);

            CreateGround();
        }

        protected override void OnInitializePhysics()
        {
            ManifoldPoint.ContactAdded += MyContactCallback;

            SetupEmptyDynamicsWorld();

            //CompoundCollisionAlgorithm.CompoundChildShapePairCallback = MyCompoundChildShapeCallback;

            string path = Path.Combine("data", "file.obj");
            var wavefrontModel = WavefrontObj.Load(path);
            if (wavefrontModel.Indices.Count == 0)
            {
                return;
            }

            var localScaling = new Vector3(6, 6, 6);
            _triangleMesh = CreateTriangleMesh(wavefrontModel.Indices, wavefrontModel.Vertices, localScaling);

            // Convex hull approximation
            ConvexHullShape convexShape = CreateHullApproximation(_triangleMesh);
            float mass = 1.0f;
            LocalCreateRigidBody(mass, Matrix.Translation(0, 2, 14), convexShape);

            // Non-moving body
            var objectOffset = new Vector3(10, 0, 0);
            const bool useQuantization = true;
            var concaveShape = new BvhTriangleMeshShape(_triangleMesh, useQuantization);
            LocalCreateRigidBody(0, Matrix.Translation(objectOffset), concaveShape);


            Hacd hacd = ComputeHacd(wavefrontModel);
            hacd.Save("output.wrl", false);

            var compoundShape = CreateCompoundShape(hacd, localScaling);

            mass = 10.0f;
            objectOffset = new Vector3(-10, 0, -6);
            var body2 = LocalCreateRigidBody(mass, Matrix.Translation(objectOffset), compoundShape);
            body2.CollisionFlags |= CollisionFlags.CustomMaterialCallback;

            objectOffset.Z += 6;
            body2 = LocalCreateRigidBody(mass, Matrix.Translation(objectOffset), compoundShape);
            body2.CollisionFlags |= CollisionFlags.CustomMaterialCallback;

            objectOffset.Z += 6;
            body2 = LocalCreateRigidBody(mass, Matrix.Translation(objectOffset), compoundShape);
            body2.CollisionFlags |= CollisionFlags.CustomMaterialCallback;
        }

        public override void OnHandleInput()
        {
            base.OnHandleInput();

            if (Input.KeysPressed.Contains(Keys.T))
            {
                _enableSat = !_enableSat;
                ClientResetScene();
            }
        }

        private TriangleMesh _triangleMesh;

        public void Dispose()
        {
            _triangleMesh.Dispose();
        }

        // MyContactCallback is just an example to show how to get access to the child shape that collided
        private void MyContactCallback(ManifoldPoint cp, CollisionObjectWrapper colObj0Wrap, int partId0, int index0, CollisionObjectWrapper colObj1Wrap, int partId1, int index1)
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

        private void CreateGround()
        {
            var groundShape = new BoxShape(30, 2, 30);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Translation(0, -4.5f, 0), groundShape);
            ground.UserObject = "Ground";
        }

        private static TriangleMesh CreateTriangleMesh(List<int> indices, List<Vector3> vertices, Vector3 localScaling)
        {
            var triangleMesh = new TriangleMesh();

            int triangleCount = indices.Count / 3;
            for (int i = 0; i < triangleCount; i++)
            {
                int index0 = indices[i * 3];
                int index1 = indices[i * 3 + 1];
                int index2 = indices[i * 3 + 2];

                Vector3 vertex0 = vertices[index0] * localScaling;
                Vector3 vertex1 = vertices[index1] * localScaling;
                Vector3 vertex2 = vertices[index2] * localScaling;

                triangleMesh.AddTriangleRef(ref vertex0, ref vertex1, ref vertex2);
            }

            return triangleMesh;
        }

        private ConvexHullShape CreateHullApproximation(TriangleMesh triangleMesh)
        {
            using (var tmpConvexShape = new ConvexTriangleMeshShape(triangleMesh))
            {
                using (var hull = new ShapeHull(tmpConvexShape))
                {
                    hull.BuildHull(tmpConvexShape.Margin);
                    var convexShape = new ConvexHullShape(hull.Vertices);
                    if (_enableSat)
                    {
                        convexShape.InitializePolyhedralFeatures();
                    }
                    return convexShape;
                }
            }
        }

        private Hacd ComputeHacd(WavefrontObj model)
        {
            var hacd = new Hacd()
            {
                NumVerticesPerConvexHull = 100,
                CompacityWeight = 0.1,
                VolumeWeight = 0,

                // Recommended HACD parameters
                NClusters = 2,
                Concavity = 100,
                AddExtraDistPoints = false,
                AddFacesPoints = false,
                AddNeighboursDistPoints = false
            };
            hacd.SetPoints(model.Vertices);
            hacd.SetTriangles(model.Indices);

            hacd.Compute();
            return hacd;
        }

        private CompoundShape CreateCompoundShape(Hacd hacd, Vector3 localScaling)
        {
            var wavefrontWriter = new WavefrontWriter("file_convex.obj");
            var convexDecomposition = new ConvexDecomposition(wavefrontWriter)
            {
                LocalScaling = localScaling
            };

            for (int c = 0; c < hacd.NClusters; c++)
            {
                int trianglesLen = hacd.GetNTrianglesCH(c) * 3;
                if (trianglesLen == 0)
                {
                    continue;
                }

                Vector3[] points;
                int[] triangles;
                hacd.GetCH(c, out points, out triangles);

                convexDecomposition.Result(points, triangles);
            }

            wavefrontWriter.Dispose();

            // Combine convex shapes into a compound shape
            var compoundShape = new CompoundShape();
            for (int i = 0; i < convexDecomposition.ConvexShapes.Count; i++)
            {
                Vector3 centroid = convexDecomposition.ConvexCentroids[i];
                var convexShape = convexDecomposition.ConvexShapes[i];
                Matrix trans = Matrix.Translation(centroid);
                if (_enableSat)
                {
                    convexShape.InitializePolyhedralFeatures();
                }
                compoundShape.AddChildShape(trans, convexShape);

                LocalCreateRigidBody(1.0f, trans, convexShape);
            }

            return compoundShape;
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
