using System;
using BulletSharp;
using DemoFramework;

namespace CollisionInterfaceDemo
{
    class DrawingResult : ContactResultCallback
    {
        DynamicsWorld world;
        public DrawingResult(DynamicsWorld world)
        {
            this.world = world;
        }

        public override float AddSingleResult(ManifoldPoint cp,
            CollisionObjectWrapper colObj0Wrap, int partId0, int index0,
            CollisionObjectWrapper colObj1Wrap, int partId1, int index1)
        {
            Vector3 ptA = cp.PositionWorldOnA;
            Vector3 ptB = cp.PositionWorldOnB;
            world.DebugDrawer.DrawLine(ref ptA, ref ptB, System.Drawing.Color.Blue);
            return 0;
        }
    };

    class CollisionInterfaceDemo : Demo
    {
        Vector3 eye = new Vector3(6, 4, 1);
        Vector3 target = new Vector3(0, 3, 0);

        CollisionObject[] objects = new CollisionObject[2];
        DrawingResult renderCallback;

        Vector3 boxMin = new Vector3(-1, -1, -1);
        Vector3 boxMax = new Vector3(1, 1, 1);

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - Collision Interface Demo");

            IsDebugDrawEnabled = true;
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            renderCallback = new DrawingResult(World);


            BoxShape boxA = new BoxShape(new Vector3(1, 1, 1));
            boxA.Margin = 0;

            BoxShape boxB = new BoxShape(new Vector3(0.5f, 0.5f, 0.5f));
            boxB.Margin = 0;

            CollisionShapes.Add(boxA);
            CollisionShapes.Add(boxB);

            objects[0] = new CollisionObject();
            objects[1] = new CollisionObject();

            objects[0].CollisionShape = boxA;
            objects[1].CollisionShape = boxB;

            //World.AddCollisionObject(objects[0]);
            World.AddCollisionObject(objects[1]);

            Quaternion rotA = new Quaternion(0.739f, -0.204f, 0.587f, 0.257f);
            rotA.Normalize();

            objects[0].WorldTransform = Matrix.RotationQuaternion(rotA) * Matrix.Translation(0, 3, 0);
            objects[1].WorldTransform = Matrix.Translation(0, 4.248f, 0);
        }

        public override void OnUpdate()
        {
            base.OnUpdate();

            Matrix t = objects[0].WorldTransform;
            Vector3 pos = t.Origin;
            t.Origin = Vector3.Zero;
            t *= Matrix.RotationYawPitchRoll(0.1f * FrameDelta, 0.05f * FrameDelta, 0);
            t.Origin = pos;
            objects[0].WorldTransform = t;

            if (IsDebugDrawEnabled)
            {
                World.DebugDrawer.DrawBox(ref boxMin, ref boxMax, ref t, System.Drawing.Color.White);
                World.ContactTest(objects[0], renderCallback);
            }
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new CollisionInterfaceDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
