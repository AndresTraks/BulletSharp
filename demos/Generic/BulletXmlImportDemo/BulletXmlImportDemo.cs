using System;
using BulletSharp;
using BulletSharp.Serialize;
using DemoFramework;

namespace BulletXmlImportDemo
{
    class BulletXmlImportDemo : Demo
    {
        Vector3 eye = new Vector3(30, 20, 10);
        Vector3 target = new Vector3(0, 5, -4);

        BulletXmlWorldImporter importer;

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - XML Import Demo");
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new DbvtBroadphase();
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            importer = new BulletXmlWorldImporter(World);
            if (!importer.LoadFile("data\\bullet_basic.xml"))
            {
                //throw new FileNotFoundException();
            }
        }

        public override void ExitPhysics()
        {
            importer.DeleteAllData();
            importer.Dispose();

            base.ExitPhysics();
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new BulletXmlImportDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
