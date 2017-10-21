using BulletSharp;
using DemoFramework;
using DemoFramework.FileLoaders;
using System;
using System.Collections.Generic;
using System.IO;

namespace BspDemo
{
    class BspDemo : Demo
    {
        protected override void OnInitialize()
        {
            Freelook.Up = Vector3.UnitZ;
            Freelook.Eye = new Vector3(10, 10, 10);
            Freelook.Target = new Vector3(0, 0, 0);

            Graphics.SetFormText("BulletSharp - Quake BSP Physics Viewer");
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new DbvtBroadphase();
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.Gravity = Freelook.Up * -10.0f;

            var bspLoader = new BspLoader();
            string[] args = Environment.GetCommandLineArgs();
            if (args.Length == 1)
            {
                bspLoader.LoadBspFile(Path.Combine("data", "BspDemo.bsp"));
            }
            else
            {
                bspLoader.LoadBspFile(args[1]);
            }
            BspConverter bsp2Bullet = new BspToBulletConverter(this);
            bsp2Bullet.ConvertBsp(bspLoader, 0.1f);
        }
    }

    public class BspToBulletConverter : BspConverter
    {
        private Demo _demo;

        public BspToBulletConverter(Demo demo)
        {
            _demo = demo;
        }
        
        public override void AddConvexVerticesCollider(List<Vector3> vertices, bool isEntity, Vector3 entityTargetLocation)
        {
            if (vertices.Count == 0) return;

            // perhaps we can do something special with entities (isEntity)
            // like adding a collision triggering (as example)

            const float mass = 0.0f;
            //can use a shift
            Matrix startTransform = Matrix.Translation(0, 0, -10.0f);
            var shape = new ConvexHullShape(vertices);
            _demo.CollisionShapes.Add(shape);

            _demo.LocalCreateRigidBody(mass, startTransform, shape);
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new BspDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
