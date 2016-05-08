using BulletSharp;
using DemoFramework;
using Microsoft.Xna.Framework;

namespace BasicDemo
{
    public class BasicDemo : PhysicsDemo
    {
        ///create 125 (5x5x5) dynamic objects
        private const int ArraySizeX = 5, ArraySizeY = 5, ArraySizeZ = 5;

        private Vector3 _start = new Vector3(
            -5 - ArraySizeX / 2,
            -5,
            -3 - ArraySizeZ / 2);

        private Vector3 _eye = new Vector3(30, 20, 10);
        private Vector3 _target = new Vector3(0, 5, 0);

        private CollisionShape _boxShape, _groundShape;

        public BasicDemo()
        {
            Window.Title = "BulletSharp - MonoGame Basic Demo";
        }

        protected override void Initialize()
        {
            base.Initialize();

            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new DbvtBroadphase();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);
            World.DebugDrawer = DebugDrawer;

            // create the ground
            _groundShape = new BoxShape(50, 1, 50);
            LoadModel("ground", _groundShape);
            CollisionShapes.Add(_groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Identity, _groundShape);

            // create a few dynamic rigidbodies
            const float mass = 1.0f;

            _boxShape = new BoxShape(1);
            LoadModel("cube", _boxShape);
            CollisionShapes.Add(_boxShape);

            var rbInfo = new RigidBodyConstructionInfo(mass, null, _boxShape);
            rbInfo.LocalInertia = _boxShape.CalculateLocalInertia(mass);

            for (int k = 0; k < ArraySizeY; k++)
            {
                for (int i = 0; i < ArraySizeX; i++)
                {
                    for (int j = 0; j < ArraySizeZ; j++)
                    {
                        Matrix startTransform = Matrix.CreateTranslation(
                            _start + new Vector3(2 * i, 2 * k, 2 * j));

                        // using motionstate is recommended, it provides interpolation capabilities
                        // and only synchronizes 'active' objects
                        rbInfo.MotionState = new DefaultMotionState(startTransform);

                        var body = new RigidBody(rbInfo);

                        // make it drop from a height
                        body.Translate(new Vector3(0, 20, 0));

                        World.AddRigidBody(body);
                    }
                }
            }

            rbInfo.Dispose();

            FreeLook.SetEyeTarget(ref _eye, ref _target);
        }
    }
}
