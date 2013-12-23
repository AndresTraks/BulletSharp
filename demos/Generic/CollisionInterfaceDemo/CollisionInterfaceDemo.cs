using System;
using BulletSharp;
using DemoFramework;

namespace CollisionInterfaceDemo
{
    class DrawingResult : CollisionWorld.ContactResultCallback
    {
        DynamicsWorld world;
        public DrawingResult(DynamicsWorld world)
        {
            this.world = world;
        }

        public override float AddSingleResult(ManifoldPoint cp, CollisionObjectWrapper colObj0Wrap, int partId0, int index0, CollisionObjectWrapper colObj1Wrap, int partId1, int index1)
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

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - Collision Interface Demo");
            Graphics.SetInfoText("Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                //"F11 - Toggle fullscreen\n" +
                "Space - Shoot box");
        }

        protected override void OnInitializePhysics()
        {
            BoxShape boxA = new BoxShape(new Vector3(1, 1, 1));
            boxA.Margin = 0;

            BoxShape boxB = new BoxShape(new Vector3(0.5f, 0.5f, 0.5f));
            boxB.Margin = 0;

            objects[0] = new CollisionObject();
            objects[1] = new CollisionObject();

            objects[0].CollisionShape = boxA;
            objects[1].CollisionShape = boxB;


            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);
            IsDebugDrawEnabled = true;

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

            DrawingResult renderCallback = new DrawingResult(World);
            World.ContactTest(objects[0], renderCallback);

            Matrix t = objects[0].WorldTransform;
            Vector4 pos = t.get_Rows(3);
            t.set_Rows(3, new Vector4(0, 0, 0, 1));
            t *= Matrix.RotationYawPitchRoll(0.1f * FrameDelta, 0.05f * FrameDelta, 0);
            t.set_Rows(3, pos);
            objects[0].WorldTransform = t;

            Vector3 min = new Vector3(-1, -1, -1);
            Vector3 max = new Vector3(1, 1, 1);
            World.DebugDrawer.DrawBox(ref min, ref max, ref t, System.Drawing.Color.White);
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new CollisionInterfaceDemo())
            {
                LibraryManager.Initialize(demo);
            }
        }
    }
}
