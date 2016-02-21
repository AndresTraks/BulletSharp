using System;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;

namespace ConcaveRaycastDemo
{
    // Scrolls back and forth over terrain
    class RaycastBar
    {
        const int NumRays = 100;

        Vector3[] _source = new Vector3[NumRays];
        Vector3[] _destination = new Vector3[NumRays];
        Vector3[] _direction = new Vector3[NumRays];
        Vector3[] _hitCenterOfMass = new Vector3[NumRays];
        Vector3[] _hitPoint = new Vector3[NumRays];
        float[] _hitFraction = new float[NumRays];
        Vector3[] _normal = new Vector3[NumRays];

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
            const float dalpha = 4 * (float)Math.PI / NumRays;
            for (int i = 0; i < NumRays; i++)
            {
                float alpha = dalpha * i;
                // rotate around by alpha degrees y
                Matrix transform = Matrix.RotationY(alpha);
                _direction[i] = new Vector3(1.0f, 0.0f, 0.0f);
                _direction[i] = Vector3.TransformCoordinate(_direction[i], transform);
                _source[i] = new Vector3(_minX, maxY, z);
                _destination[i] = _source[i] + _direction[i] * rayLength;
                _destination[i].Y = minY;
                _normal[i] = new Vector3(1.0f, 0.0f, 0.0f);
            }
        }

        public void Move(float frameDelta)
        {
            if (frameDelta > 1.0f / 60.0f)
                frameDelta = 1.0f / 60.0f;

            float move = _sign * _dx * frameDelta;
            for (int i = 0; i < NumRays; i++)
            {
                _source[i].X += move;
                _destination[i].X += move;
            }

            if (_source[0].X < _minX)
                _sign = 1.0f;
            else if (_source[0].X > _maxX)
                _sign = -1.0f;
        }

        public void Cast(CollisionWorld cw, float frameDelta)
        {
#if BATCH_RAYCASTER
		    if (!gBatchRaycaster)
			    return;

		    gBatchRaycaster->clearRays ();
		    for (int i = 0; i < NumRays; i++)
		    {
			    gBatchRaycaster->addRay (source[i], dest[i]);
		    }
		    gBatchRaycaster->performBatchRaycast ();
		    for (int i = 0; i < gBatchRaycaster->getNumRays(); i++)
		    {
				    const SpuRaycastTaskWorkUnitOut& out = (*gBatchRaycaster)[i];
				    _hitPoint[i].setInterpolate3(_source[i], _destination[i], out.HitFraction);
				    _normal[i] = out.hitNormal;
				    _normal[i].Normalize();
		    }
#else
            for (int i = 0; i < NumRays; i++)
            {
                using (var cb = new ClosestRayResultCallback(ref _source[i], ref _destination[i]))
                {
                    cw.RayTest(ref _source[i], ref _destination[i], cb);
                    if (cb.HasHit)
                    {
                        _hitPoint[i] = cb.HitPointWorld;
                        _normal[i] = cb.HitNormalWorld;
                        _normal[i].Normalize();
                    }
                    else
                    {
                        _hitPoint[i] = _destination[i];
                        _normal[i] = new Vector3(1.0f, 0.0f, 0.0f);
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
                Console.WriteLine("{0} rays in {1} s, min {2}, max {3}, mean {4}",
                    NumRays * _frameCount,
                    _time.ToString("0.000", CultureInfo.InvariantCulture),
                    _timeMin.ToString("0.000", CultureInfo.InvariantCulture),
                    _timeMax.ToString("0.000", CultureInfo.InvariantCulture),
                    timeMean.ToString("0.000", CultureInfo.InvariantCulture));
                _time = 0;
                _frameCount = 0;
            }
#endif
        }

        public void Draw(IDebugDraw drawer)
        {
            int i;
            for (i = 0; i < NumRays; i++)
            {
                drawer.DrawLine(ref _source[i], ref _hitPoint[i], Color.Lime);
            }
            for (i = 0; i < NumRays; i++)
            {
                Vector3 to = _hitPoint[i] + _normal[i];
                drawer.DrawLine(ref _hitPoint[i], ref to, Color.White);
            }
        }
    }

    class ConcaveRaycastDemo : Demo
    {
        Vector3 eye = new Vector3(0, 15, 60);
        Vector3 target = new Vector3(-5, 5, 0);

        const DebugDrawModes debugMode = DebugDrawModes.None;

        const float TriangleSize = 8.0f;
        const int NumVertsX = 30;
        const int NumVertsY = 30;
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

            IsDebugDrawEnabled = true;
            DebugDrawMode = debugMode;
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


            const int totalVerts = NumVertsX * NumVertsY;
            const int totalTriangles = 2 * (NumVertsX - 1) * (NumVertsY - 1);
            indexVertexArrays = new TriangleIndexVertexArray();

            IndexedMesh mesh = new IndexedMesh();
            mesh.Allocate(totalTriangles, totalVerts, 3 * sizeof(int), Vector3.SizeInBytes, PhyScalarType.Int32, PhyScalarType.Single);
            //mesh.NumTriangles = totalTriangles;
            //mesh.NumVertices = totalVerts;
            //mesh.TriangleIndexStride = 3 * sizeof(int);
            //mesh.VertexStride = Vector3.SizeInBytes;
            //mesh.TriangleIndexBase = Marshal.AllocHGlobal(mesh.TriangleIndexStride * totalTriangles);
            //mesh.VertexBase = Marshal.AllocHGlobal(mesh.VertexStride * totalVerts);
            using (var indicesStream = mesh.LockIndices())
            {
                using (var indices = new BinaryWriter(indicesStream))
                {
                    for (int i = 0; i < NumVertsX - 1; i++)
                    {
                        for (int j = 0; j < NumVertsY - 1; j++)
                        {
                            indices.Write(j * NumVertsX + i);
                            indices.Write(j * NumVertsX + i + 1);
                            indices.Write((j + 1) * NumVertsX + i + 1);

                            indices.Write(j * NumVertsX + i);
                            indices.Write((j + 1) * NumVertsX + i + 1);
                            indices.Write((j + 1) * NumVertsX + i);
                        }
                    }
                }
            }

            indexVertexArrays.AddIndexedMesh(mesh);

            raycastBar = new RaycastBar(4000, 0, -1000, 10);
            //raycastBar = new RaycastBar(true, 40.0f, -50.0f, 50.0f);


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
