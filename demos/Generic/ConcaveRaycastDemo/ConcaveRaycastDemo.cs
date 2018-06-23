using BulletSharp;
using DemoFramework;
using System;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Windows.Forms;

namespace ConcaveRaycastDemo
{
    class ConcaveRaycastDemo : Demo
    {
        const DebugDrawModes debugMode = DebugDrawModes.None;

        const float TriangleSize = 8.0f;
        const int NumVertsX = 30;
        const int NumVertsY = 30;
        const float waveHeight = 5.0f;
        static float groundOffset = 0.0f;
        bool animatedMesh = false;

        Vector3 worldMin = new Vector3(-1000, -1000, -1000);
        Vector3 worldMax = new Vector3(1000, 1000, 1000);

        TriangleIndexVertexArray indexVertexArrays;
        BvhTriangleMeshShape groundShape;
        RaycastBar raycastBar;
        RigidBody staticBody;

        protected override void OnInitialize()
        {
            Freelook.Eye = new Vector3(0, 15, 60);
            Freelook.Target = new Vector3(-5, 5, 0);

            Graphics.SetFormText("BulletSharp - Concave Raycast Demo");
            Graphics.SetInfoText("Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                //"F11 - Toggle fullscreen\n" +
                "Space - Shoot box");

            IsDebugDrawEnabled = true;
            DebugDrawMode = debugMode;
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new AxisSweep3(worldMin, worldMax);
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.SolverInfo.SplitImpulse = 1;
            World.Gravity = new Vector3(0, -10, 0);

            raycastBar = new RaycastBar(4000.0f, 0.0f, -1000.0f, 10);
            //raycastBar = new RaycastBar(true, 40.0f, -50.0f, 50.0f);

            CreateBoxes();
            CreateGround();
        }

        private void CreateGround()
        {
            const int totalVerts = NumVertsX * NumVertsY;
            const int totalTriangles = 2 * (NumVertsX - 1) * (NumVertsY - 1);
            const int triangleIndexStride = 3 * sizeof(int);

            var mesh = new IndexedMesh();
            mesh.Allocate(totalTriangles, totalVerts, triangleIndexStride, Vector3.SizeInBytes, PhyScalarType.Int32, PhyScalarType.Single);

            DataStream indices = mesh.LockIndices();
            for (int x = 0; x < NumVertsX - 1; x++)
            {
                for (int y = 0; y < NumVertsY - 1; y++)
                {
                    int row1Index = x * NumVertsX + y;
                    int row2Index = row1Index + NumVertsX;
                    indices.Write(row1Index);
                    indices.Write(row1Index + 1);
                    indices.Write(row2Index + 1);

                    indices.Write(row1Index);
                    indices.Write(row2Index + 1);
                    indices.Write(row2Index);
                }
            }

            indexVertexArrays = new TriangleIndexVertexArray();
            indexVertexArrays.AddIndexedMesh(mesh);

            SetVertexPositions(waveHeight, 0.0f);

            const bool useQuantizedAabbCompression = true;
            groundShape = new BvhTriangleMeshShape(indexVertexArrays, useQuantizedAabbCompression);

            staticBody = LocalCreateRigidBody(0.0f, Matrix.Identity, groundShape);
            staticBody.CollisionFlags |= CollisionFlags.StaticObject;
            staticBody.UserObject = "Ground";
        }

        private void CreateBoxes()
        {
            var colShape = new BoxShape(1);

            for (int i = 0; i < 10; i++)
            {
                //CollisionShape colShape = new CapsuleShape(0.5f,2.0f);//boxShape = new SphereShape(1.0f);
                Matrix startTransform = Matrix.Translation(2 * i, 10, 1);
                LocalCreateRigidBody(1.0f, startTransform, colShape);
            }
        }

        public override void OnUpdate()
        {
            if (animatedMesh)
            {
                groundOffset += FrameDelta;
                SetVertexPositions(waveHeight, groundOffset);
                Graphics.MeshFactory.RemoveShape(groundShape);

                groundShape.RefitTree(ref worldMin, ref worldMax);

                //clear all contact points involving mesh proxy. Note: this is a slow/unoptimized operation.
                Broadphase.OverlappingPairCache.CleanProxyFromPairs(staticBody.BroadphaseHandle, Dispatcher);
            }

            raycastBar.Move(FrameDelta);
            raycastBar.Cast(World, FrameDelta);
            if (IsDebugDrawEnabled)
            {
                raycastBar.Draw(World.DebugDrawer);
            }

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

        void SetVertexPositions(float waveheight, float offset)
        {
            BulletSharp.DataStream vertexBuffer, indexBuffer;
            int numVerts, numFaces;
            PhyScalarType vertsType, indicesType;
            int vertexStride, indexStride;
            indexVertexArrays.GetLockedVertexIndexData(out vertexBuffer, out numVerts, out vertsType, out vertexStride,
                out indexBuffer, out indexStride, out numFaces, out indicesType);

            using (var vertexWriter = new BinaryWriter(vertexBuffer))
            {
                for (int i = 0; i < NumVertsX; i++)
                {
                    for (int j = 0; j < NumVertsY; j++)
                    {
                        vertexWriter.Write((i - NumVertsX * 0.5f) * TriangleSize);
                        vertexWriter.Write(waveheight * (float)Math.Sin((float)i + offset) * (float)Math.Cos((float)j + offset));
                        vertexWriter.Write((j - NumVertsY * 0.5f) * TriangleSize);
                    }
                }
            }

            vertexBuffer.Dispose();
            indexBuffer.Dispose();
        }
    }

    // Scrolls back and forth over terrain
    class RaycastBar
    {
        const int NumRays = 100;
        Ray[] _rays = new Ray[NumRays];

        int _frameCount;
        float _time;
        float _timeMin = float.MaxValue;
        float _timeMax;
        float _timeTotal;
        int _sampleCount;

        float _dx = 10;
        float _minX = -40;
        float _maxX = 20;
        float _sign = 1;

        public RaycastBar(float rayLength, float z, float minY, float maxY)
        {
            const float alpha = 4 * (float)Math.PI / NumRays;
            for (int i = 0; i < NumRays; i++)
            {
                Matrix transform = Matrix.RotationY(alpha * i);
                var direction = Vector3.TransformCoordinate(Vector3.UnitX, transform);

                _rays[i] = new Ray
                {
                    Source = new Vector3(_minX, maxY, z),
                    Destination = new Vector3(
                        _minX + direction.X * rayLength,
                        minY,
                        z + direction.Z * rayLength),
                    Normal = new Vector3(1, 0, 0)
                };
            }
        }

        public void Move(float frameDelta)
        {
            if (frameDelta > 1.0f / 60.0f)
                frameDelta = 1.0f / 60.0f;

            float move = _sign * _dx * frameDelta;
            foreach (var ray in _rays)
            {
                ray.MoveX(move);
            }

            if (_rays[0].Source.X < _minX)
                _sign = 1.0f;
            else if (_rays[0].Source.X > _maxX)
                _sign = -1.0f;
        }

        public void Cast(CollisionWorld cw, float frameDelta)
        {
#if BATCH_RAYCASTER
            if (!batchRaycaster)
                return;

            batchRaycaster.ClearRays();
            foreach (var ray in _rays)
            {
                batchRaycaster.AddRay(ray.Source, ray.Destination);
            }
            batchRaycaster.PerformBatchRaycast();
            for (int i = 0; i < batchRaycaster.NumRays; i++)
            {
                const SpuRaycastTaskWorkUnitOut& out = (*batchRaycaster)[i];
                _rays[i].HitPoint.SetInterpolate3(_source[i], _destination[i], out.HitFraction);
                _rays[i].Normal = out.hitNormal;
                _rays[i].Normal.Normalize();
		    }
#else
            foreach (var ray in _rays)
            {
                using (var cb = new ClosestRayResultCallback(ref ray.Source, ref ray.Destination))
                {
                    cw.RayTestRef(ref ray.Source, ref ray.Destination, cb);
                    if (cb.HasHit)
                    {
                        ray.HitPoint = cb.HitPointWorld;
                        ray.Normal = cb.HitNormalWorld;
                        ray.Normal.Normalize();
                    }
                    else
                    {
                        ray.HitPoint = ray.Destination;
                        ray.Normal = new Vector3(1.0f, 0.0f, 0.0f);
                    }
                }
            }

            _time += frameDelta;
            _frameCount++;
            if (_frameCount > 50)
            {
                if (_time < _timeMin) _timeMin = _time;
                if (_time > _timeMax) _timeMax = _time;
                _timeTotal += _time;
                _sampleCount++;
                float timeMean = _timeTotal / _sampleCount;
                PrintStats();
                _time = 0;
                _frameCount = 0;
            }
#endif
        }

        private void PrintStats()
        {
            float timeMean = _timeTotal / _sampleCount;
            Console.WriteLine("{0} rays in {1} s, min {2}, max {3}, mean {4}",
                    NumRays * _frameCount,
                    _time.ToString("0.000", CultureInfo.InvariantCulture),
                    _timeMin.ToString("0.000", CultureInfo.InvariantCulture),
                    _timeMax.ToString("0.000", CultureInfo.InvariantCulture),
                    timeMean.ToString("0.000", CultureInfo.InvariantCulture));
        }

        static Vector3 green = new Vector3(0.0f, 1.0f, 0.0f);
        static Vector3 white = new Vector3(1.0f, 1.0f, 1.0f);

        public void Draw(IDebugDraw drawer)
        {
            foreach (var ray in _rays)
            {
                drawer.DrawLine(ref ray.Source, ref ray.HitPoint, Color.Green);

                Vector3 to = ray.HitPoint + ray.Normal;
                drawer.DrawLine(ref ray.HitPoint, ref to, Color.White);
            }
        }
    }

    class Ray
    {
        public Vector3 Source;
        public Vector3 Destination;
        public Vector3 HitPoint;
        public Vector3 Normal;

        public void MoveX(float move)
        {
            Source.X += move;
            Destination.X += move;
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new ConcaveRaycastDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
