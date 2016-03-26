using System;
using System.Collections.Generic;
using System.Linq;
using BulletSharp;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace BasicDemo
{
    class Physics
    {
        public DynamicsWorld World { get; }

        CollisionDispatcher _dispatcher;
        BroadphaseInterface _broadphase;
        List<CollisionShape> _collisionShapes = new List<CollisionShape>();
        CollisionConfiguration _collisionConf;

        ///create 125 (5x5x5) dynamic objects
        const int ArraySizeX = 5, ArraySizeY = 5, ArraySizeZ = 5;

        Vector3 _start = new Vector3(
            -5 - ArraySizeX / 2,
            -5,
            -3 - ArraySizeZ / 2);

        public Physics()
        {
            // collision configuration contains default setup for memory, collision setup
            _collisionConf = new DefaultCollisionConfiguration();
            _dispatcher = new CollisionDispatcher(_collisionConf);

            _broadphase = new DbvtBroadphase();

            World = new DiscreteDynamicsWorld(_dispatcher, _broadphase, null, _collisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            // create the ground
            var groundShape = new BoxShape(50, 1, 50);
            _collisionShapes.Add(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Identity, groundShape);
            ground.UserObject = "Ground";

            // create a few dynamic rigidbodies
            const float mass = 1.0f;

            var colShape = new BoxShape(1);
            _collisionShapes.Add(colShape);

            var rbInfo = new RigidBodyConstructionInfo(mass, null, colShape);
            rbInfo.LocalInertia = colShape.CalculateLocalInertia(mass);

            for (int k = 0; k < ArraySizeY; k++)
            {
                for (int i = 0; i < ArraySizeX; i++)
                {
                    for (int j = 0; j < ArraySizeZ; j++)
                    {
                        Matrix startTransform = Matrix.CreateTranslation(
                            _start + new Vector3(2 * i, 2 * k, 2 * j));

                        // using motionstate is recommended, it provides interpolation capabilities
                        // and only synchronizes 'active' objects
                        rbInfo.MotionState = new DefaultMotionState(startTransform);

                        var body = new RigidBody(rbInfo);
                        
                        // make it drop from a height
                        body.Translate(new Vector3(0, 20, 0));

                        World.AddRigidBody(body);
                    }
                }
            }

            rbInfo.Dispose();
        }

        public virtual void Update(float elapsedTime)
        {
            World.StepSimulation(elapsedTime);
        }

        public void ExitPhysics()
        {
            // Remove/dispose constraints
            for (int i = World.NumConstraints - 1; i >= 0; i--)
            {
                var constraint = World.GetConstraint(i);
                World.RemoveConstraint(constraint);
                constraint.Dispose();
            }

            // Remove/dispose rigid bodies
            for (int i = World.NumCollisionObjects - 1; i >= 0; i--)
            {
                var obj = World.CollisionObjectArray[i];
                var body = obj as RigidBody;
                if (body != null && body.MotionState != null)
                {
                    body.MotionState.Dispose();
                }
                World.RemoveCollisionObject(obj);
                obj.Dispose();
            }

            //delete collision shapes
            foreach (var shape in _collisionShapes)
                shape.Dispose();
            _collisionShapes.Clear();

            World.Dispose();
            _broadphase.Dispose();
            if (_dispatcher != null)
            {
                _dispatcher.Dispose();
            }
            _collisionConf.Dispose();
        }

        public RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            using (var rbInfo = new RigidBodyConstructionInfo(mass, null, shape))
            {
                bool isDynamic = mass != 0.0f;
                if (isDynamic)
                {
                    rbInfo.LocalInertia = shape.CalculateLocalInertia(mass);
                    rbInfo.MotionState = new DefaultMotionState(startTransform);
                }

                var body = new RigidBody(rbInfo);
                World.AddRigidBody(body);
                return body;
            }
        }

        public class PhysicsDebugDraw : DebugDraw
        {
            GraphicsDevice _device;

            public override DebugDrawModes DebugMode { get; set; }

            public PhysicsDebugDraw(GraphicsDevice device)
            {
                _device = device;
            }

            public override void Draw3dText(ref Vector3 location, string textString)
            {
                throw new NotImplementedException();
            }

            public override void DrawContactPoint(ref Vector3 pointOnB, ref Vector3 normalOnB, float distance, int lifeTime, Color color)
            {
                var vertices = new[]
                {
                    new VertexPositionColor(pointOnB, color),
                    new VertexPositionColor(pointOnB + normalOnB, color)
                };
                _device.DrawUserPrimitives(PrimitiveType.LineList, vertices, 0, 1);
            }

            public override void DrawLine(ref Vector3 from, ref Vector3 to, Color color)
            {
                var vertices = new[]
                {
                    new VertexPositionColor(from, color),
                    new VertexPositionColor(to, color)
                };
                _device.DrawUserPrimitives(PrimitiveType.LineList, vertices, 0, 1);
            }

            public void DrawDebugWorld(DynamicsWorld world)
            {
                world.DebugDrawWorld();
            }

            public override void ReportErrorWarning(string warningString)
            {
                throw new NotImplementedException();
            }
        }
    }
}
