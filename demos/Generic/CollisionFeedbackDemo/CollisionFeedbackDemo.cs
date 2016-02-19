using System;
using BulletSharp;
using DemoFramework;

namespace CollisionFeedbackDemo
{
    class CollisionFeedbackDemo : Demo
    {
        Vector3 eye = new Vector3(0, 20, 50);
        Vector3 target = new Vector3(10, 0, 0);

        AudioEngine _audioEngine = new AudioEngine();

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - Collision Interface Demo");
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            var groundShape = new BoxShape(30, 1, 30);
            var ground = LocalCreateRigidBody(0, Matrix.Translation(0, -5, 0), groundShape);
            ground.UserObject = "metal.wav";
            ground = LocalCreateRigidBody(0, Matrix.Translation(0, 0, 0) * Matrix.RotationZ((float)-Math.PI / 4), groundShape);
            ground.UserObject = "metal.wav";
            var groundShape2 = new BoxShape(5, 1, 30);
            ground = LocalCreateRigidBody(0, Matrix.Translation(25, -3, 0), groundShape2);
            ground.UserObject = "metal.wav";

            var boxShape = new BoxShape(1, 0.5f, 2);
            for (int i = 0; i < 4; i++)
            {
                var box = LocalCreateRigidBody(1, Matrix.Translation(i * 1.5f, i * 3 + 10, i * 3), boxShape);
                box.UserObject = "metal.wav";
            }

            var sphereShape = new SphereShape(1);
            for (int i = 0; i < 4; i++)
            {
                var sphere = LocalCreateRigidBody(1, Matrix.Translation(i, i * 3 + 20, 0), sphereShape);
                sphere.UserObject = "rubber.wav";
            }

            var cylinderShape = new CylinderShape(0.5f, 1, 0.5f);
            for (int i = 0; i < 4; i++)
            {
                var cylinder = LocalCreateRigidBody(1, Matrix.Translation(i, i * 3 + 20, 3), cylinderShape);
                cylinder.UserObject = "can.wav";
            }

            ManifoldPoint.ContactAdded += ContactAdded;
        }

        private void ContactAdded(ManifoldPoint cp, CollisionObjectWrapper colObj0Wrap, int partId0, int index0, CollisionObjectWrapper colObj1Wrap, int partId1, int index1)
        {
            float impulse = cp.AppliedImpulse;
            if (impulse < 0.4f) return;

            impulse -= 0.4f;
            impulse = Math.Min(impulse, 4.0f) * 0.25f;

            string sound0 = colObj0Wrap.CollisionObject.UserObject as string;
            if (sound0 != null)
            {
                _audioEngine.SetVolume(sound0, impulse);
                _audioEngine.Play(sound0);
            }

            string sound1 = colObj1Wrap.CollisionObject.UserObject as string;
            if (sound1 != null)
            {
                _audioEngine.SetVolume(sound1, impulse);
                _audioEngine.Play(sound1);
            }
        }

        public override RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            var body = base.LocalCreateRigidBody(mass, startTransform, shape);
            body.CollisionFlags |= CollisionFlags.CustomMaterialCallback;
            body.UserObject = "plastic.wav";
            return body;
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);

            if (disposing)
            {
                _audioEngine.Dispose();
            }
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new CollisionFeedbackDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
