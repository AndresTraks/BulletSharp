using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;

namespace ConcaveRaycastDemo
{
    // Scrolls back and forth over terrain
    class RaycastBar
    {
        const int NUMRAYS_IN_BAR = 100;

        Vector3[] source = new Vector3[NUMRAYS_IN_BAR];
        Vector3[] dest = new Vector3[NUMRAYS_IN_BAR];
        Vector3[] direction = new Vector3[NUMRAYS_IN_BAR];
        Vector3[] hit = new Vector3[NUMRAYS_IN_BAR];
        Vector3[] normal = new Vector3[NUMRAYS_IN_BAR];

        int frame_counter;
        int ms;
        int sum_ms;
        int sum_ms_samples;
        int min_ms;
        int max_ms;

        float dx;
        float min_x;
        float max_x;
        float min_y;
        float max_y;
        float sign;

        public RaycastBar()
        {
            ms = 0;
            max_ms = 0;
            min_ms = 9999;
            sum_ms_samples = 0;
            sum_ms = 0;
        }

        public RaycastBar(bool unused, float ray_length, float min_z, float max_z, float min_y = -10, float max_y = 10)
        {
            frame_counter = 0;
            ms = 0;
            max_ms = 0;
            min_ms = 9999;
            sum_ms_samples = 0;
            sum_ms = 0;
            dx = 10.0f;
            min_x = -40;
            max_x = 20;
            this.min_y = min_y;
            this.max_y = max_y;
            sign = 1.0f;
            //float dalpha = 4 * (float)Math.PI / NUMRAYS_IN_BAR;
            for (int i = 0; i < NUMRAYS_IN_BAR; i++)
            {
                float z = (max_z - min_z) / NUMRAYS_IN_BAR * (float)i + min_z;
                source[i] = new Vector3(min_x, max_y, z);
                dest[i] = new Vector3(min_x + ray_length, min_y, z);
                normal[i] = new Vector3(1.0f, 0.0f, 0.0f);
            }
        }

        public RaycastBar(float ray_length, float z, float min_y = -1000, float max_y = 10)
        {
            frame_counter = 0;
            ms = 0;
            max_ms = 0;
            min_ms = 9999;
            sum_ms_samples = 0;
            sum_ms = 0;
            dx = 10.0f;
            min_x = -40;
            max_x = 20;
            this.min_y = min_y;
            this.max_y = max_y;
            sign = 1.0f;
            float dalpha = 4 * (float)Math.PI / NUMRAYS_IN_BAR;
            for (int i = 0; i < NUMRAYS_IN_BAR; i++)
            {
                float alpha = dalpha * i;
                // rotate around by alpha degrees y
                Matrix tr = Matrix.RotationQuaternion(Quaternion.RotationAxis(new Vector3(0.0f, 1.0f, 0.0f), alpha));
                direction[i] = new Vector3(1.0f, 0.0f, 0.0f);
                direction[i] = Vector3.TransformCoordinate(direction[i], tr);
                direction[i] = direction[i] * ray_length;
                source[i] = new Vector3(min_x, max_y, z);
                dest[i] = source[i] + direction[i];
                dest[i][1] = min_y;
                normal[i] = new Vector3(1.0f, 0.0f, 0.0f);
            }
        }

        public void Move(float dt)
        {
            if (dt > (1.0f / 60.0f))
                dt = 1.0f / 60.0f;
            for (int i = 0; i < NUMRAYS_IN_BAR; i++)
            {
                source[i][0] += dx * dt * sign;
                dest[i][0] += dx * dt * sign;
            }
            if (source[0][0] < min_x)
                sign = 1.0f;
            else if (source[0][0] > max_x)
                sign = -1.0f;
        }

        public void Cast(CollisionWorld cw)
        {
#if BATCH_RAYCASTER
		    if (!gBatchRaycaster)
			    return;

		    gBatchRaycaster->clearRays ();
		    for (int i = 0; i < NUMRAYS_IN_BAR; i++)
		    {
			    gBatchRaycaster->addRay (source[i], dest[i]);
		    }
		    gBatchRaycaster->performBatchRaycast ();
		    for (int i = 0; i < gBatchRaycaster->getNumRays (); i++)
		    {
				    const SpuRaycastTaskWorkUnitOut& out = (*gBatchRaycaster)[i];
				    hit[i].setInterpolate3(source[i],dest[i],out.HitFraction);
				    normal[i] = out.hitNormal;
				    normal[i].Normalize();
		    }
#else
            for (int i = 0; i < NUMRAYS_IN_BAR; i++)
            {
                using (var cb = new ClosestRayResultCallback(ref source[i], ref dest[i]))
                {
                    cw.RayTest(ref source[i], ref dest[i], cb);
                    if (cb.HasHit)
                    {
                        hit[i] = cb.HitPointWorld;
                        normal[i] = cb.HitNormalWorld;
                        normal[i].Normalize();
                    }
                    else
                    {
                        hit[i] = dest[i];
                        normal[i] = new Vector3(1.0f, 0.0f, 0.0f);
                    }
                }
            }

            frame_counter++;
            if (frame_counter > 50)
            {
                min_ms = ms < min_ms ? ms : min_ms;
                max_ms = ms > max_ms ? ms : max_ms;
                sum_ms += ms;
                sum_ms_samples++;
                float mean_ms = (float)sum_ms / (float)sum_ms_samples;
                Console.WriteLine("{0} rays in {1} ms {2} {3} {4}", NUMRAYS_IN_BAR * frame_counter, ms, min_ms, max_ms, mean_ms);
                ms = 0;
                frame_counter = 0;
            }
#endif
        }

        public void Draw(IDebugDraw drawer)
        {
            int i;
            for (i = 0; i < NUMRAYS_IN_BAR; i++)
            {
                drawer.DrawLine(ref source[i], ref hit[i], Color.Lime);
            }
            for (i = 0; i < NUMRAYS_IN_BAR; i++)
            {
                Vector3 to = hit[i] + normal[i];
                drawer.DrawLine(ref hit[i], ref to, Color.White);
            }
        }
    }

    class ConcaveRaycastDemo : Demo
    {
        Vector3 eye = new Vector3(0, 15, 60);
        Vector3 target = new Vector3(-5, 5, 0);

        const DebugDrawModes debugMode = DebugDrawModes.None;

        const float TRIANGLE_SIZE = 8.0f;
        const int NUM_VERTS_X = 30;
        const int NUM_VERTS_Y = 30;
        const float waveHeight = 5.0f;
        static float offset = 0.0f;
        bool animatedMesh = false;

        TriangleIndexVertexArray indexVertexArrays;
        BvhTriangleMeshShape groundShape;
        static RaycastBar raycastBar;
        RigidBody staticBody;

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - Concave Raycast Demo");
            Graphics.SetInfoText("Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                //"F11 - Toggle fullscreen\n" +
                "Space - Shoot box");

            DebugDrawMode = debugMode;

            const int totalVerts = NUM_VERTS_X * NUM_VERTS_Y;
            const int totalTriangles = 2 * (NUM_VERTS_X - 1) * (NUM_VERTS_Y - 1);
            indexVertexArrays = new TriangleIndexVertexArray();

            IndexedMesh mesh = new IndexedMesh();
            mesh.Allocate(totalVerts, Vector3.SizeInBytes, totalTriangles, 3 * sizeof(int));
            DataStream indices = mesh.LockIndices();
            for (int i = 0; i < NUM_VERTS_X - 1; i++)
            {
                for (int j = 0; j < NUM_VERTS_Y - 1; j++)
                {
                    indices.Write(j * NUM_VERTS_X + i);
                    indices.Write(j * NUM_VERTS_X + i + 1);
                    indices.Write((j + 1) * NUM_VERTS_X + i + 1);

                    indices.Write(j * NUM_VERTS_X + i);
                    indices.Write((j + 1) * NUM_VERTS_X + i + 1);
                    indices.Write((j + 1) * NUM_VERTS_X + i);
                }
            }
            indices.Dispose();

            indexVertexArrays.AddIndexedMesh(mesh);

            raycastBar = new RaycastBar(4000.0f, 0.0f);
            //raycastBar = new RaycastBar(true, 40.0f, -50.0f, 50.0f);
        }

        void SetVertexPositions(float waveheight, float offset)
        {
            BulletSharp.DataStream vertexBuffer, indexBuffer;
            int numVerts, numFaces;
            PhyScalarType vertsType, indicesType;
            int vertexStride, indexStride;
            indexVertexArrays.GetLockedVertexIndexData(out vertexBuffer, out numVerts, out vertsType, out vertexStride,
                out indexBuffer, out indexStride, out numFaces, out indicesType);

            for (int i = 0; i < NUM_VERTS_X; i++)
            {
                for (int j = 0; j < NUM_VERTS_Y; j++)
                {
                    vertexBuffer.Write((i - NUM_VERTS_X * 0.5f) * TRIANGLE_SIZE);
                    vertexBuffer.Write(waveheight * (float)Math.Sin((float)i + offset) * (float)Math.Cos((float)j + offset));
                    vertexBuffer.Write((j - NUM_VERTS_Y * 0.5f) * TRIANGLE_SIZE);
                }
            }

            vertexBuffer.Dispose();
            indexBuffer.Dispose();
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Vector3 worldMin = new Vector3(-1000, -1000, -1000);
            Vector3 worldMax = new Vector3(1000, 1000, 1000);
            Broadphase = new AxisSweep3(worldMin, worldMax);
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.SolverInfo.SplitImpulse = 1;
            World.Gravity = new Vector3(0, -10, 0);
            IsDebugDrawEnabled = true;


            CollisionShape colShape = new BoxShape(1);
            CollisionShapes.Add(colShape);

            for (int i = 0; i < 10; i++)
            {
                //CollisionShape colShape = new CapsuleShape(0.5f,2.0f);//boxShape = new SphereShape(1.0f);
                Matrix startTransform = Matrix.Translation(2 * i, 10, 1);
                LocalCreateRigidBody(1.0f, startTransform, colShape);
            }


            SetVertexPositions(waveHeight, 0.0f);

            const bool useQuantizedAabbCompression = true;
            groundShape = new BvhTriangleMeshShape(indexVertexArrays, useQuantizedAabbCompression);
            CollisionShapes.Add(groundShape);

            staticBody = LocalCreateRigidBody(0.0f, Matrix.Identity, groundShape);
            staticBody.CollisionFlags |= CollisionFlags.StaticObject;
            staticBody.UserObject = "Ground";
        }

        public override void OnUpdate()
        {
            if (animatedMesh)
            {
                offset += FrameDelta;
                SetVertexPositions(waveHeight, offset);
                Graphics.MeshFactory.RemoveShape(groundShape);

                Vector3 worldMin = new Vector3(-1000, -1000, -1000);
                Vector3 worldMax = new Vector3(1000, 1000, 1000);

                groundShape.RefitTree(worldMin, worldMax);

                //clear all contact points involving mesh proxy. Note: this is a slow/unoptimized operation.
                Broadphase.OverlappingPairCache.CleanProxyFromPairs(staticBody.BroadphaseHandle, Dispatcher);
            }

            raycastBar.Move(FrameDelta);
            raycastBar.Cast(World);
            raycastBar.Draw(World.DebugDrawer);

            base.OnUpdate();
        }

        public override void OnHandleInput()
        {
            if (Input.KeysPressed.Contains(Keys.G))
            {
                animatedMesh = !animatedMesh;
                if (animatedMesh)
                {
                    staticBody.CollisionFlags |= CollisionFlags.KinematicObject;
                    staticBody.ActivationState = ActivationState.DisableDeactivation;
                }
                else
                {
                    staticBody.CollisionFlags &= ~CollisionFlags.KinematicObject;
                    staticBody.ActivationState = ActivationState.ActiveTag;
                }
            }
            base.OnHandleInput();
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new ConcaveRaycastDemo())
            {
                LibraryManager.Initialize(demo);
            }
        }
    }
}
