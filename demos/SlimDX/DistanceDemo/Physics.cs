using BulletSharp;
using DemoFramework;
using SlimDX;

namespace DistanceDemo
{
    class Physics : PhysicsContext
    {
        public bool HasDistanceResult;
        public Vector3 distanceFrom, distanceTo;
        public float distance;

        Matrix rotBodyPosition = Matrix.Translation(0, 10, 0);
        Matrix body2Position = Matrix.Translation(0, 5, 0);
        RigidBody rotBody, body2;
        ConvexShape colShape0, colShape1;

        VoronoiSimplexSolver sGjkSimplexSolver = new VoronoiSimplexSolver();

        float rotation = 0;

        public Physics()
        {
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new DbvtBroadphase();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            // ground
            CollisionShape groundShape = new BoxShape(50, 1, 50);
            CollisionShapes.Add(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Identity, groundShape);
            ground.UserObject = "Ground";

            // Objects
            //colShape = new BoxShape(1);
            Vector3[] points0 = {
                new Vector3(1, 0, 0), new Vector3(0, 1, 0), new Vector3(0, 0, 1)
            };
            Vector3[] points1 = {
                new Vector3(1, 0, 0), new Vector3(0, 1, 0), new Vector3(0, 0, 1), new Vector3(0,0,-1), new Vector3(-1,-1,0)
            };
            colShape0 = new ConvexHullShape(points0);
            colShape1 = new ConvexHullShape(points1);
            CollisionShapes.Add(colShape0);
            CollisionShapes.Add(colShape1);

            body2 = LocalCreateRigidBody(0, body2Position, colShape1);

            rotBody = LocalCreateRigidBody(0, rotBodyPosition, colShape0);
            rotBody.CollisionFlags |= CollisionFlags.KinematicObject;
            rotBody.ActivationState = ActivationState.DisableDeactivation;
        }

        public override int Update(float elapsedTime)
        {
            int subSteps = base.Update(elapsedTime);

            rotation += elapsedTime;
            rotBody.CenterOfMassTransform = Matrix.RotationX(rotation) * rotBodyPosition;

            var input = new DiscreteCollisionDetectorInterface.ClosestPointInput
            {
                TransformA = rotBody.CenterOfMassTransform,
                TransformB = body2Position
            };

            var result = new PointCollector();

            using (var detector = new GjkPairDetector(colShape0, colShape1, sGjkSimplexSolver, null))
            {
                detector.CachedSeparatingAxis = new Vector3(0.00000000f, 0.059727669f, 0.29259586f);
                detector.GetClosestPoints(input, result, null);
            }

            if (result.HasResult)
            {
                HasDistanceResult = true;
                distanceFrom = result.PointInWorld;
                distanceTo = result.PointInWorld + result.NormalOnBInWorld * result.Distance;
                distance = result.Distance;
            }
            else
            {
                HasDistanceResult = false;
            }
            result.Dispose();

            return subSteps;
        }
    }
}
