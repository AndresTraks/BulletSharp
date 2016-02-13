using System;
using BulletSharp;
using DemoFramework;
using SlimDX;

namespace MultiMaterialDemo
{
    class Physics : PhysicsContext
    {
        const int NumVertsX = 20;
        const int NumVertsY = 50;
        const float TriangleSize = 1.0f;
        static float waveheight = 0.0f;

        Vector3[] gVertices;

        BvhTriangleMeshShape trimeshShape;

        // User can override this material combiner by implementing gContactAddedCallback
        // and setting body.CollisionFlags |= CollisionObject.CustomMaterialCallback.
        static float CalculateCombinedFriction(float friction0, float friction1)
        {
            float friction = friction0 * friction1;

            const float MAX_FRICTION = 10;
            if (friction < -MAX_FRICTION)
                friction = -MAX_FRICTION;
            if (friction > MAX_FRICTION)
                friction = MAX_FRICTION;
            return friction;

        }

        float CalculateCombinedRestitution(float restitution0, float restitution1)
        {
            return restitution0 * restitution1;
        }

        static void CustomMaterialCombinerCallback(ManifoldPoint cp,
            CollisionObjectWrapper colObj0Wrap, int partId0, int index0,
            CollisionObjectWrapper colObj1Wrap, int partId1, int index1)
        {
            // Apply material properties
            if (colObj0Wrap.CollisionShape.ShapeType == BroadphaseNativeType.TriangleShape)
            {
                CollisionShape parent0 = colObj0Wrap.CollisionObject.CollisionShape;
                if (parent0 != null && parent0.ShapeType == BroadphaseNativeType.MultiMaterialTriangleMesh)
                {
                    MultimaterialTriangleMeshShape shape = parent0 as MultimaterialTriangleMeshShape;
                    BulletMaterial props = shape.GetMaterialProperties(partId0, index0);
                    cp.CombinedFriction = CalculateCombinedFriction(props.Friction, colObj1Wrap.CollisionObject.Friction);
                    cp.CombinedRestitution = props.Restitution * colObj1Wrap.CollisionObject.Restitution;
                }
            }
            else if (colObj1Wrap.CollisionShape.ShapeType == BroadphaseNativeType.TriangleShape)
            {
                CollisionShape parent1 = colObj1Wrap.CollisionObject.CollisionShape;
                if (parent1 != null && parent1.ShapeType == BroadphaseNativeType.MultiMaterialTriangleMesh)
                {
                    MultimaterialTriangleMeshShape shape = parent1 as MultimaterialTriangleMeshShape;
                    BulletMaterial props = shape.GetMaterialProperties(partId1, index1);
                    cp.CombinedFriction = CalculateCombinedFriction(props.Friction, colObj0Wrap.CollisionObject.Friction);
                    cp.CombinedRestitution = props.Restitution * colObj0Wrap.CollisionObject.Restitution;
                }
            }
        }

        void SetVertexPositions(float waveHeight, float offset)
        {
            for (int y = 0; y < NumVertsY; y++)
            {
                for (int x = 0; x < NumVertsX; x++)
                {
                    gVertices[y * NumVertsX + x] = new Vector3(
                        x * TriangleSize,
                        waveHeight * (float)Math.Sin((float)x + offset) * (float)Math.Cos((float)y + offset),
                        y * TriangleSize);
                }
            }
        }

        public Physics()
        {
            ManifoldPoint.ContactAdded += CustomMaterialCombinerCallback;

            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new AxisSweep3(new Vector3(-10000, -10000, -10000), new Vector3(10000, 10000, 10000));
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);


            const int totalVerts = NumVertsX * NumVertsY;
            const int totalTriangles = 2 * (NumVertsX - 1) * (NumVertsY - 1);

            // Set up the vertex data
            gVertices = new Vector3[totalVerts];
            SetVertexPositions(waveheight, 0.0f);

            // Set up the face data
            int index = 0;
            int[] gIndices = new int[totalTriangles * 3];
            for (int y = 0; y < NumVertsY - 1; y++)
            {
                for (int x = 0; x < NumVertsX - 1; x++)
                {
                    gIndices[index++] = y * NumVertsX + x;
                    gIndices[index++] = y * NumVertsX + x + 1;
                    gIndices[index++] = (y + 1) * NumVertsX + x;

                    gIndices[index++] = y * NumVertsX + x + 1;
                    gIndices[index++] = (y + 1) * NumVertsX + x + 1;
                    gIndices[index++] = (y + 1) * NumVertsX + x;
                }
            }

            // Explicitly set up the materials.  It's a small array so let's do it bit by bit.
            BulletMaterial[] gMaterials = new BulletMaterial[2];
            gMaterials[0].Friction = 0;
            gMaterials[0].Restitution = 0.9f;
            gMaterials[1].Friction = 0.9f;
            gMaterials[1].Restitution = 0.1f;

            // Set up the face->material index data
            int[] gFaceMaterialIndices = new int[totalTriangles];
            for (int a = 0; a < totalTriangles; a++)
            {
                // This will give the first half of the faces low friction and high restitution
                // and the second half of the faces high friction and low restitution
                if (a > totalTriangles / 2)
                    gFaceMaterialIndices[a] = 0;
                else
                    gFaceMaterialIndices[a] = 1;
            }

            // Create the array structure
            TriangleIndexVertexMaterialArray indexVertexArrays = new TriangleIndexVertexMaterialArray(
                gIndices, gVertices, gMaterials, gFaceMaterialIndices);

            // Create the multimaterial mesh shape
            trimeshShape = new MultimaterialTriangleMeshShape(indexVertexArrays, true);
            CollisionShapes.Add(trimeshShape);

            // create the ground
            //CollisionShape groundShape = new BoxShape(50, 1, 50);
            //CollisionShapes.PushBack(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Translation(-15, 0, -30), trimeshShape);
            ground.UserObject = "Ground";
            ground.CollisionFlags |= CollisionFlags.CustomMaterialCallback;


            CollisionShape colShape = new BoxShape(0.5f);
            CollisionShapes.Add(colShape);

            for (int i = 0; i < 12; i++)
            {
                RigidBody body = LocalCreateRigidBody(1, Matrix.Translation(10 - i, 10, -20 + i * 3), colShape);
                body.CollisionFlags |= CollisionFlags.CustomMaterialCallback;
                body.Friction = 0.9f;
                body.Gravity = new Vector3(0, -20, 0);
                body.ApplyCentralImpulse(new Vector3(-7.7f, 0, 0));
            }
        }
    }
}
