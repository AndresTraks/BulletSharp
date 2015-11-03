using BulletSharp;
using NUnit.Framework;

namespace BulletSharpTest
{
    [TestFixture]
    class TriangleMeshTest
    {
        DefaultCollisionConfiguration conf;
        CollisionDispatcher dispatcher;
        AxisSweep3 broadphase;
        DiscreteDynamicsWorld world;

        TriangleIndexVertexArray indexVertexArray;
        TriangleIndexVertexArray indexVertexArray2;
        GImpactMeshShape gImpactMeshShape;
        BvhTriangleMeshShape triangleMeshShape;
        RigidBody gImpactMesh, triangleMesh;

        private void TestTriangleArray(TriangleIndexVertexArray triangleArray)
        {
            Assert.AreSame(triangleArray.IndexedMeshArray, triangleArray.IndexedMeshArray); // check caching

            foreach (var indexedMesh in triangleArray.IndexedMeshArray)
            {
                Assert.NotNull(indexedMesh);
            }
            var initialMesh = triangleArray.IndexedMeshArray[0];
            Assert.AreEqual(PhyScalarType.Int32, initialMesh.IndexType);
            Assert.AreEqual(PhyScalarType.Single, initialMesh.VertexType);
            Assert.AreEqual(TorusMesh.Vertices.Length / 3, initialMesh.NumVertices);
            Assert.AreEqual(TorusMesh.Indices.Length / 3, initialMesh.NumTriangles);
            Assert.AreEqual(sizeof(float) * 3, initialMesh.VertexStride);
            Assert.AreEqual(sizeof(int) * 3, initialMesh.TriangleIndexStride);

            var triangleIndices = initialMesh.TriangleIndices;
            Assert.AreEqual(TorusMesh.Indices.Length, triangleIndices.Count);
            for (int i = 0; i < triangleIndices.Count; i++)
            {
                Assert.AreEqual(triangleIndices[i], TorusMesh.Indices[i]);
            }
        }

        [Test]
        public void TriangleMeshTest1()
        {
            TestTriangleArray(indexVertexArray);
            TestTriangleArray(indexVertexArray2);

            Vector3 aabbMin, aabbMax;
            gImpactMeshShape.GetAabb(Matrix.Identity, out aabbMin, out aabbMax);
            triangleMeshShape.GetAabb(Matrix.Identity, out aabbMin, out aabbMax);

            for (int i = 0; i < 600; i++)
            {
                world.StepSimulation(1.0f / 60.0f);
            }
        }

        [TestFixtureSetUp]
        public void SetUp()
        {
            conf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(conf);
            broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));
            world = new DiscreteDynamicsWorld(dispatcher, broadphase, null, conf);

            // Initialize TriangleIndexVertexArray with float array
            indexVertexArray = new TriangleIndexVertexArray(TorusMesh.Indices, TorusMesh.Vertices);
            gImpactMeshShape = new GImpactMeshShape(indexVertexArray);
            gImpactMeshShape.CalculateLocalInertia(1.0f);
            gImpactMesh = CreateBody(1.0f, gImpactMeshShape, Vector3.Zero);


            // Initialize TriangleIndexVertexArray with Vector3 array
            Vector3[] torusVertices = new Vector3[TorusMesh.Vertices.Length / 3];
            for (int i = 0; i < torusVertices.Length; i++)
            {
                torusVertices[i] = new Vector3(
                    TorusMesh.Vertices[i * 3],
                    TorusMesh.Vertices[i * 3 + 1],
                    TorusMesh.Vertices[i * 3 + 2]);
            }
            indexVertexArray2 = new TriangleIndexVertexArray(TorusMesh.Indices, torusVertices);
            triangleMeshShape = new BvhTriangleMeshShape(indexVertexArray2, true);
            // CalculateLocalInertia must fail for static shapes (shapes based on TriangleMeshShape)
            //triangleMeshShape.CalculateLocalInertia(1.0f);
            triangleMesh = CreateBody(0.0f, triangleMeshShape, Vector3.Zero);
        }

        [TestFixtureTearDown]
        public void TearDown()
        {
            world.RemoveRigidBody(gImpactMesh);
            world.RemoveRigidBody(triangleMesh);
            gImpactMesh.MotionState.Dispose();
            triangleMesh.MotionState.Dispose();
            gImpactMesh.Dispose();
            triangleMesh.Dispose();
            gImpactMeshShape.Dispose();
            triangleMeshShape.Dispose();
            indexVertexArray.Dispose();
            indexVertexArray2.Dispose();

            world.Dispose();
            dispatcher.Dispose();
            broadphase.Dispose();
            conf.Dispose();
        }

        RigidBody CreateBody(float mass, CollisionShape shape, Vector3 offset)
        {
            using (var info = new RigidBodyConstructionInfo(mass, new DefaultMotionState(), shape, Vector3.Zero))
            {
                if (mass != 0.0f)
                {
                    info.LocalInertia = info.CollisionShape.CalculateLocalInertia(mass);
                }
                var collisionObject = new RigidBody(info);
                collisionObject.Translate(offset);
                world.AddRigidBody(collisionObject);
                return collisionObject;
            }
        }
    }
}
