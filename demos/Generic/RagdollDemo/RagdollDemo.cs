﻿using System;
using System.Collections.Generic;
using BulletSharp;
using DemoFramework;

namespace RagdollDemo
{
    sealed class RagdollDemo : Demo
    {
        List<Ragdoll> _ragdolls = new List<Ragdoll>();

        protected override void OnInitialize()
        {
            Freelook.Eye = new Vector3(0, 1, 5);
            Freelook.Target = new Vector3(0, 1, 0);

            Graphics.SetFormText("BulletSharp - Ragdoll Demo");
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new AxisSweep3(new Vector3(-10000, -10000, -10000), new Vector3(10000, 10000, 10000));
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            //World.DispatchInfo.UseConvexConservativeDistanceUtil = true;
            //World.DispatchInfo.ConvexConservativeDistanceThreshold = 0.01f;

            // Setup a big ground box
            CollisionShape groundShape = new BoxShape(100, 10, 100);
            Matrix groundTransform = Matrix.Translation(0, -10, 0);

            RigidBody ground = LocalCreateRigidBody(0, groundTransform, groundShape);
            ground.UserObject = "Ground";

            // Spawn one ragdoll
            SpawnRagdoll(new Vector3(1, 0.5f, 0));
            SpawnRagdoll(new Vector3(-1, 0.5f, 0));
        }

        private void SpawnRagdoll(Vector3 startOffset)
        {
            Ragdoll ragdoll = new Ragdoll(World, startOffset);
            _ragdolls.Add(ragdoll);
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new RagdollDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
