using System;
using System.Collections.Generic;
using BulletSharp;
using DemoFramework;

namespace MotorDemo
{
    class MotorDemo : Demo
    {
        private const float CyclePeriod = 2000.0f;
        private const float MuscleStrength = 0.5f;
        private float time;

        private List<TestRig> rigs = new List<TestRig>();

        void MotorPreTickCallback(DynamicsWorld world, float timeStep)
        {
            SetMotorTargets(timeStep);
        }

        protected override void OnInitialize()
        {
            Freelook.Eye = new Vector3(8, 4, 8);
            Freelook.Target = new Vector3(0, 0, 0);

            Graphics.SetFormText("BulletSharp - Motor Demo");

            DebugDrawMode = DebugDrawModes.DrawConstraintLimits | DebugDrawModes.DrawConstraints | DebugDrawModes.DrawWireframe;
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Vector3 worldAabbMin = new Vector3(-10000, -10000, -10000);
            Vector3 worldAabbMax = new Vector3(10000, 10000, 10000);
            Broadphase = new AxisSweep3(worldAabbMin, worldAabbMax);

            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);
            World.SetInternalTickCallback(MotorPreTickCallback, this, true);

            // create the ground
            CollisionShape groundShape = new BoxShape(200, 10, 200);
            CollisionShapes.Add(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Translation(0, -10, 0), groundShape);
            ground.UserObject = "Ground";

            time = 0;

            SpawnTestRig(new Vector3(1, 1, 0), false);
            SpawnTestRig(new Vector3(-2, 1, 0), true);
        }

        private void SpawnTestRig(Vector3 startOffset, bool isFixed)
        {
            TestRig rig = new TestRig(World, startOffset, isFixed);
            rigs.Add(rig);
        }


        void SetMotorTargets(float deltaTime)
        {
            float ms = deltaTime * 1000000.0f;
            float minFPS = 1000000.0f / 60.0f;
            if (ms > minFPS)
                ms = minFPS;

            time += ms;

            //
            // set per-frame sinusoidal position targets using angular motor (hacky?)
            //
            foreach (var rig in rigs)
            {
                foreach (HingeConstraint hinge in rig.Joints)
                {
                    float currentAngle = hinge.HingeAngle;

                    float targetPercent = ((int)(time / 1000.0f) % (int)CyclePeriod) / CyclePeriod;
                    float targetAngle = (float)(0.5 * (1 + Math.Sin(2.0f * Math.PI * targetPercent)));
                    float targetLimitAngle = hinge.LowerLimit + targetAngle * (hinge.UpperLimit - hinge.LowerLimit);
                    float angleError = targetLimitAngle - currentAngle;
                    float desiredAngularVel = 1000000.0f * angleError / ms;
                    hinge.EnableAngularMotor(true, desiredAngularVel, MuscleStrength);
                }
            }
        }

        public override void ExitPhysics()
        {
            foreach (var testRig in rigs)
            {
                testRig.Dispose();
            }
            rigs.Clear();
            base.ExitPhysics();
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new MotorDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
