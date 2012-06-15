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

        static bool CustomMaterialCombinerCallback(ManifoldPoint cp,
            CollisionObject colObj0, int partId0, int index0,
            CollisionObject colObj1, int partId1, int index1)
        {
            // Apply material properties
            if (colObj0.CollisionShape.ShapeType == BroadphaseNativeType.TriangleShape)
            {
                CollisionShape parent0 = colObj0.CollisionShape;
                if (parent0 != null && parent0.ShapeType == BroadphaseNativeType.MultiMaterialTriangleMesh)
                {
                    MultimaterialTriangleMeshShape shape = parent0 as MultimaterialTriangleMeshShape;
                    BulletMaterial props = shape.GetMaterialProperties(partId0, index0);
                    cp.CombinedFriction = CalculateCombinedFriction(props.Friction, colObj1.Friction);
                    cp.CombinedRestitution = props.Restitution * colObj1.Restitution;
                }
            }
            else if (colObj1.CollisionShape.ShapeType == BroadphaseNativeType.TriangleShape)
            {
                CollisionShape parent1 = colObj1.CollisionShape;
                if (parent1 != null && parent1.ShapeType == BroadphaseNativeType.MultiMaterialTriangleMesh)
                {
                    MultimaterialTriangleMeshShape shape = parent1 as MultimaterialTriangleMeshShape;
                    BulletMaterial props = shape.GetMaterialProperties(partId1, index1);
                    cp.CombinedFriction = CalculateCombinedFriction(props.Friction, colObj0.Friction);
                    cp.CombinedRestitution = props.Restitution * colObj0.Restitution;
                }
            }

            //this return value is currently ignored, but to be on the safe side: return false if you don't calculate friction
            return true;
        }

        void SetVertexPositions(float waveheight, float offset)
        {
            int i;
            int j;

            for (i = 0; i < NumVertsX; i++)
            {
                for (j = 0; j < NumVertsY; j++)
                {
                    gVertices[i + j * NumVertsX] = new Vector3((i - NumVertsX * 0.5f) * TriangleSize,
                        //0.f,
                        waveheight * (float)Math.Sin((float)i + offset) * (float)Math.Cos((float)j + offset),
                        (j - NumVertsY * 0.5f) * TriangleSize);
                }
            }
        }

        public Physics()
        {
            ManifoldPoint.ContactAddedCallback = CustomMaterialCombinerCallback;

            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new AxisSweep3(new Vector3(-10000, -10000, -10000), new Vector3(10000, 10000, 10000));
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);


            const int totalVerts = NumVertsX * NumVertsY;
            const int totalTriangles = 2 * (NumVertsX - 1) * (NumVertsY - 1);

            gVertices = new Vector3[totalVerts];
            int[] gIndices = new int[totalTriangles * 3];
            BulletMaterial[] gMaterials = new BulletMaterial[2];
            int[] gFaceMaterialIndices = new int[totalTriangles];

            // Explicitly set up the materials.  It's a small array so let's do it bit by bit.
            gMaterials[0].Friction = 0;
            gMaterials[0].Restitution = 0.9f;
            gMaterials[1].Friction = 0.9f;
            gMaterials[1].Restitution = 0.1f;

            int i;
            // Set up the vertex data
            SetVertexPositions(waveheight, 0.0f);
            int index = 0;
            // Set up the face data
            for (i = 0; i < NumVertsX - 1; i++)
            {
                for (int j = 0; j < NumVertsY - 1; j++)
                {
                    gIndices[index++] = j * NumVertsX + i;
                    gIndices[index++] = j * NumVertsX + i + 1;
                    gIndices[index++] = (j + 1) * NumVertsX + i + 1;

                    gIndices[index++] = j * NumVertsX + i;
                    gIndices[index++] = (j + 1) * NumVertsX + i + 1;
                    gIndices[index++] = (j + 1) * NumVertsX + i;
                }
            }

            // Set up the face->material index data
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
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Identity, trimeshShape);
            ground.UserObject = "Ground";
            ground.CollisionFlags |= CollisionFlags.StaticObject | CollisionFlags.CustomMaterialCallback;



            CollisionShape colShape = new BoxShape(0.5f);
            CollisionShapes.Add(colShape);

            for (i = 0; i < 12; i++)
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
