using System;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;
using BulletSharp;
using DemoFramework;

namespace ConcaveConvexCastDemo
{
    // Scrolls back and forth over terrain
    class ConvexcastBatch
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

        Vector3 _boxBoundMin;
        Vector3  _boxBoundMax;
        BoxShape _boxShape;

        const float NormalScale = 10.0f; // easier to see if this is big

        Matrix _fromRotation = Matrix.Identity; //Matrix.RotationX(0.7f);
        Matrix _toRotation = Matrix.RotationX(0.7f);

        public ConvexcastBatch(float rayLength, float z, float minY, float maxY)
        {
            _boxBoundMax = new Vector3(1.0f, 1.0f, 1.0f);
            _boxBoundMin = -_boxBoundMax;
            _boxShape = new BoxShape(_boxBoundMax);

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
            var cb = new ClosestConvexResultCallback();
            for (int i = 0; i < NumRays; i++)
            {
                cb.ClosestHitFraction = 1.0f;
                cb.ConvexFromWorld = _source[i];
                cb.ConvexToWorld = _destination[i];

                Matrix from = _fromRotation * Matrix.Translation(_source[i]);
                Matrix to = _toRotation * Matrix.Translation(_destination[i]);
                cw.ConvexSweepTest(_boxShape, from, to, cb);
                if (cb.HasHit)
                {
                    _hitPoint[i] = cb.HitPointWorld;
                    Vector3.Lerp(ref _source[i], ref _destination[i], cb.ClosestHitFraction, out _hitCenterOfMass[i]);
                    _hitFraction[i] = cb.ClosestHitFraction;
                    _normal[i] = cb.HitNormalWorld;
                    _normal[i].Normalize();
                }
                else
                {
                    _hitCenterOfMass[i] = _destination[i];
                    _hitPoint[i] = _destination[i];
                    _hitFraction[i] = 1.0f;
                    _normal[i] = new Vector3(1.0f, 0.0f, 0.0f);
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
        }

        public void Draw(IDebugDraw drawer)
        {
            for (int i = 0; i < NumRays; i++)
            {
                drawer.DrawLine(ref _source[i], ref _hitCenterOfMass[i], Color.Lime);

                Vector3 to = _hitPoint[i] + NormalScale * _normal[i];
                drawer.DrawLine(ref _hitPoint[i], ref to, Color.White);

                Matrix fromTransform = _fromRotation * Matrix.Translation(_source[i]);
                Matrix toTransform = _toRotation * Matrix.Translation(_destination[i]);
                Vector3 linVel, angVel;
                TransformUtil.CalculateVelocity(fromTransform, toTransform, 1.0f, out linVel, out angVel);
                Matrix transform;
                TransformUtil.IntegrateTransform(fromTransform, linVel, angVel, _hitFraction[i], out transform);
                drawer.DrawBox(ref _boxBoundMin, ref _boxBoundMax, ref transform, Color.Aqua);
            }
        }
    }

    class ConcaveConvexCastDemo : Demo
    {
        Vector3 eye = new Vector3(0, 15, 60);
        Vector3 target = new Vector3(-5, 5, 0);

        const DebugDrawModes debugMode = DebugDrawModes.None;

        const float TriangleSize = 8.0f;
        const int NumVertsX = 30;
        const int NumVertsY = 30;
        const float WaveHeight = 5.0f;
        static float offset = 0.0f;
        bool animatedMesh = true;
        const int NumDynamicBoxesX = 30;
        const int NumDynamicBoxesY = 30;

        TriangleIndexVertexArray indexVertexArrays;
        BvhTriangleMeshShape groundShape;
        static ConvexcastBatch convexcastBatch;
        RigidBody staticBody;

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - Concave Convexcast Demo");

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

            for (int i = 0; i < NumVertsX; i++)
            {
                for (int j = 0; j < NumVertsY; j++)
                {
                    vertexBuffer.Write((i - NumVertsX * 0.5f) * TriangleSize);
                    vertexBuffer.Write(waveheight * (float)Math.Sin((float)i + offset) * (float)Math.Cos((float)j + offset));
                    vertexBuffer.Write((j - NumVertsY * 0.5f) * TriangleSize);
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
            DataStream indices = mesh.LockIndices();
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
            indices.Dispose();

            indexVertexArrays.AddIndexedMesh(mesh);

            convexcastBatch = new ConvexcastBatch(40.0f, 0.0f, -10.0f, 80.0f);
            //convexcastBatch = new ConvexcastBatch(true, 40.0f, -50.0f, 50.0f);


            CollisionShape colShape = new BoxShape(1);
            CollisionShapes.Add(colShape);

            for (int j = 0; j < NumDynamicBoxesX; j++)
            {
                for (int i = 0; i < NumDynamicBoxesY; i++)
                {
                    //CollisionShape colShape = new CapsuleShape(0.5f,2.0f);//boxShape = new SphereShape(1.0f);
                    Matrix startTransform = Matrix.Translation(5 * (i - NumDynamicBoxesX / 2), 10, 5 * (j - NumDynamicBoxesY / 2));
                    LocalCreateRigidBody(1.0f, startTransform, colShape);
                }
            }

            SetVertexPositions(WaveHeight, 0.0f);

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
                SetVertexPositions(WaveHeight, offset);
                Graphics.MeshFactory.RemoveShape(groundShape);

                Vector3 worldMin = new Vector3(-1000, -1000, -1000);
                Vector3 worldMax = new Vector3(1000, 1000, 1000);

                groundShape.RefitTree(ref worldMin, ref worldMax);

                //clear all contact points involving mesh proxy. Note: this is a slow/unoptimized operation.
                Broadphase.OverlappingPairCache.CleanProxyFromPairs(staticBody.BroadphaseHandle, Dispatcher);
            }

            convexcastBatch.Move(FrameDelta);
            convexcastBatch.Cast(World, FrameDelta);
            if (IsDebugDrawEnabled)
            {
                convexcastBatch.Draw(World.DebugDrawer);
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
            using (Demo demo = new ConcaveConvexCastDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
