using BulletSharp;
using DemoFramework;
using SlimDX;

namespace DistanceDemo
{
    class Physics : PhysicsContext
    {
        public bool HasDistanceResult;
        public Vector3 distanceFrom, distanceTo;

        Matrix rotBodyPosition = Matrix.Translation(0, 10, 0);
        Matrix body2Position = Matrix.Translation(0, 5, 0);
        RigidBody rotBody, body2;
        BoxShape colShape;

        //VoronoiSimplexSolver sGjkSimplexSolver;

        float rotation = 0;

        public Physics()
        {
            CollisionConfiguration collisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(collisionConf);

            Broadphase = new DbvtBroadphase();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, collisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            // ground
            CollisionShape groundShape = new BoxShape(50, 1, 50);
            CollisionShapes.PushBack(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Identity, groundShape);
            ground.UserObject = "Ground";

            // Objects
            colShape = new BoxShape(1);
            CollisionShapes.PushBack(colShape);

            body2 = LocalCreateRigidBody(0, body2Position, colShape);

            rotBody = LocalCreateRigidBody(0, rotBodyPosition, colShape);
            rotBody.CollisionFlags |= CollisionFlags.KinematicObject;
            rotBody.ActivationState = ActivationState.DisableDeactivation;
        }

        public override void Update(float elapsedTime)
        {
            base.Update(elapsedTime);
            rotation += elapsedTime;
            rotBody.CenterOfMassTransform = Matrix.RotationX(rotation) * rotBodyPosition;

            BoxBoxDetector detector = new BoxBoxDetector(colShape, colShape);

            DiscreteCollisionDetectorInterface.ClosestPointInput input = new DiscreteCollisionDetectorInterface.ClosestPointInput();
            input.TransformA = rotBody.CenterOfMassTransform;
            input.TransformB = body2Position;

            PointCollector result = new PointCollector();
            detector.GetClosestPoints(input, result, null);

            if (result.HasResult)
            {
                HasDistanceResult = true;
                distanceFrom = result.PointInWorld;
                distanceTo = result.PointInWorld + result.NormalOnBInWorld * result.Distance;
            }
            else
            {
                HasDistanceResult = false;
            }
        }
    }
}
