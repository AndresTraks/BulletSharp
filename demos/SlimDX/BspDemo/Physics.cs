using BulletSharp;
using DemoFramework;
using SlimDX;

namespace BspDemo
{
    public class BspToBulletConverter : BspConverter
    {
    }

    class Physics : PhysicsContext
    {
        public Physics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new DbvtBroadphase();
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            BspLoader bspLoader = new BspLoader();
            bspLoader.LoadBspFile("BspDemo.bsp");
            BspConverter bsp2Bullet = new BspToBulletConverter();
            bsp2Bullet.ConvertBsp(bspLoader, 0.1f);
        }
    }
}
