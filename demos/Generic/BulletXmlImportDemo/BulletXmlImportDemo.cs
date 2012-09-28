using System;
using System.IO;
using BulletSharp;
using BulletSharp.Serialize;
using DemoFramework;

namespace BulletXmlImportDemo
{
    class BulletXmlImportDemo : Demo
    {
        Vector3 eye = new Vector3(30, 20, 10);
        Vector3 target = new Vector3(0, 5, -4);

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - XML Import Demo");
            Graphics.SetInfoText("Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                //"F11 - Toggle fullscreen\n" +
                "Space - Shoot box");
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

            BulletXmlWorldImporter importer = new BulletXmlWorldImporter(World);
            if (!importer.LoadFile("data\\bullet_basic.xml"))
            {
                //throw new FileNotFoundException();
            }
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new BulletXmlImportDemo())
            {
                LibraryManager.Initialize(demo);
            }
        }
    }
}
