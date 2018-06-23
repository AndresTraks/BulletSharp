using System;
using System.Drawing;
using BulletSharp;
using DemoFramework;

namespace DistanceDemo
{
    sealed class DistanceDemo : Demo
    {
        private readonly Matrix _rotBodyPosition = Matrix.Translation(0, 10, 0);
        private Matrix _staticBodyPosition = Matrix.Translation(0, 5, 0);
        private RigidBody _rotatingBody, _staticBody;
        private ConvexShape _rotatingShape, _staticShape;

        private VoronoiSimplexSolver _gjkSimplexSolver = new VoronoiSimplexSolver();

        private float _rotation = 0;

        protected override void OnInitialize()
        {
            Freelook.Eye = new Vector3(30, 20, 10);
            Freelook.Target = new Vector3(0, 5, -4);

            Graphics.SetFormText("BulletSharp - Distance Demo");

            IsDebugDrawEnabled = true;
        }

        protected override void OnInitializePhysics()
        {
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new DbvtBroadphase();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            CreateGround();

            Vector3[] rotatingPoints = {
                new Vector3(1, 0, 0), new Vector3(0, 1, 0), new Vector3(0, 0, 1)
            };
            _rotatingShape = new ConvexHullShape(rotatingPoints);
            _rotatingBody = LocalCreateRigidBody(0, _rotBodyPosition, _rotatingShape);
            _rotatingBody.CollisionFlags |= CollisionFlags.KinematicObject;
            _rotatingBody.ActivationState = ActivationState.DisableDeactivation;

            Vector3[] staticPoints = {
                new Vector3(1, 0, 0), new Vector3(0, 1, 0), new Vector3(0, 0, 1), new Vector3(0,0,-1), new Vector3(-1,-1,0)
            };
            _staticShape = new ConvexHullShape(staticPoints);

            _staticBody = LocalCreateRigidBody(0, _staticBodyPosition, _staticShape);
        }

        public override void OnUpdate()
        {
            base.OnUpdate();

            _rotation += FrameDelta;
            SetRotation(_rotation);

            if (IsDebugDrawEnabled)
            {
                DrawDistance();
            }
        }

        private void CreateGround()
        {
            var groundShape = new BoxShape(50, 1, 50);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Identity, groundShape);
            ground.UserObject = "Ground";
        }

        private void SetRotation(float rotation)
        {
            _rotatingBody.CenterOfMassTransform = Matrix.RotationX(rotation) * _rotBodyPosition;
            _rotatingBody.WorldTransform = _rotatingBody.CenterOfMassTransform;
        }

        private void DrawDistance()
        {
            var input = new DiscreteCollisionDetectorInterface.ClosestPointInput
            {
                TransformA = _rotatingBody.CenterOfMassTransform,
                TransformB = _staticBody.CenterOfMassTransform
            };

            using (var result = new PointCollector())
            {
                using (var detector = new GjkPairDetector(_rotatingShape, _staticShape, _gjkSimplexSolver, null))
                {
                    detector.CachedSeparatingAxis = new Vector3(0.00000000f, 0.059727669f, 0.29259586f);
                    detector.GetClosestPoints(input, result, null);
                }

                if (result.HasResult)
                {
                    Vector3 distanceFrom = result.PointInWorld;
                    Vector3 distanceTo = result.PointInWorld + result.NormalOnBInWorld * result.Distance;
                    World.DebugDrawer.DrawLine(ref distanceFrom, ref distanceTo, Color.White);
                }
            }

            input.Dispose();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                _gjkSimplexSolver.Dispose();
            }

            base.Dispose(disposing);
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new DistanceDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
