using BulletSharp;
using BulletSharp.Serialize;
using DemoFramework;
using System;
using System.IO;

namespace BulletXmlImportDemo
{
    class BulletXmlImportDemo : Demo
    {
        BulletXmlWorldImporter importer;

        protected override void OnInitialize()
        {
            Freelook.Eye = new Vector3(30, 20, 10);
            Freelook.Target = new Vector3(0, 5, -4);

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
            if (!importer.LoadFile(Path.Combine("data", "bullet_basic.xml")))
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
