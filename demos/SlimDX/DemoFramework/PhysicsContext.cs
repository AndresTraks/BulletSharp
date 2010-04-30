using BulletSharp;
using SlimDX;
using SlimDX.Direct3D9;
using System;

namespace DemoFramework
{
    public class PhysicsContext
    {
        public DynamicsWorld World;
        public bool IsDebugDrawEnabled { get; private set; }

        protected CollisionDispatcher Dispatcher;
        protected BroadphaseInterface Broadphase;
        protected ConstraintSolver Solver;
        protected CollisionShapeArray CollisionShapes;

        PhysicsDebugDraw DebugDrawer;
        BoxShape shootBoxShape;

        public PhysicsContext()
        {
            CollisionShapes = new CollisionShapeArray();
        }

        public void SetDebugDraw(Device device, DebugDrawModes modes)
        {
            if (World == null)
                throw new System.Exception("Physics world not initialized.");

            if (modes == 0)
            {
                if (DebugDrawer != null)
                    DebugDrawer.DebugMode = DebugDrawModes.None;
                IsDebugDrawEnabled = false;
            }
            else
            {
                if (DebugDrawer == null)
                {
                    DebugDrawer = new PhysicsDebugDraw(device);
                    World.DebugDrawer = DebugDrawer;
                }
                DebugDrawer.DebugMode = modes;
                IsDebugDrawEnabled = true;
            }
        }

        public void SetDebugDraw(PhysicsDebugDraw debugDraw)
        {
            if (World == null)
                throw new System.Exception("Physics world not initialized.");

            World.DebugDrawer = debugDraw;
            IsDebugDrawEnabled = (debugDraw != null);
        }

        public void SetDebugDraw(PhysicsDebugDraw debugDraw, DebugDrawModes modes)
        {
            debugDraw.DebugMode = modes;
            SetDebugDraw(debugDraw);
        }

        public void DebugDrawWorld()
        {
            if (IsDebugDrawEnabled)
                DebugDrawer.DrawDebugWorld(World);
        }

        public virtual void Update(float elapsedTime)
        {
            World.StepSimulation(elapsedTime);
        }

        public RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            bool isDynamic = (mass != 0.0f);

            Vector3 localInertia = Vector3.Zero;
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);

            RigidBody.RigidBodyConstructionInfo rbInfo = new RigidBody.RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia);
            RigidBody body = new RigidBody(rbInfo);

            World.AddRigidBody(body);

            return body;
        }

        public void ShootBox(Vector3 camPos, Vector3 destination)
        {
	        if (World == null)
                return;
	        
            float mass = 1.0f;
            float speed = 10;

            if (shootBoxShape == null)
                shootBoxShape = new BoxShape(0.5f);

	        RigidBody body = LocalCreateRigidBody(mass, Matrix.Translation(camPos), shootBoxShape);
            body.LinearFactor = new Vector3(1,1,1);
            //body.Restitution = 1;

	        Vector3 linVel = destination - camPos;
	        linVel.Normalize();

            body.LinearVelocity = linVel * speed;
            body.CcdMotionThreshold = 1;
            body.CcdSweptSphereRadius = 0.2f;

            Broadphase.ResetPool(Dispatcher);
        }
    };

    public class PhysicsDebugDraw : DebugDraw
    {
        SlimDX.Direct3D9.Device device;

        public PhysicsDebugDraw(SlimDX.Direct3D9.Device device)
        {
            this.device = device;
        }

        public override void DrawLine(Vector3 from, Vector3 to, Color4 fromColor, Color4 toColor)
        {
            PositionColored[] vertices = new PositionColored[2];
            vertices[0] = new PositionColored(from, fromColor.ToArgb());
            vertices[1] = new PositionColored(to, toColor.ToArgb());
            device.DrawUserPrimitives(PrimitiveType.LineList, 1, vertices);
        }

        public override void DrawLine(Vector3 from, Vector3 to, Color4 color)
        {
            int intColor = color.ToArgb();
            PositionColored[] vertices = new PositionColored[2];
            vertices[0] = new PositionColored(from, intColor);
            vertices[1] = new PositionColored(to, intColor);
            device.DrawUserPrimitives(PrimitiveType.LineList, 1, vertices);
        }

        public override void DrawBox(Vector3 bbMin, Vector3 bbMax, Color4 color)
        {
            var p1 = new Vector3(bbMin.X, bbMin.Y, bbMin.Z);
            var p2 = new Vector3(bbMax.X, bbMin.Y, bbMin.Z);
            var p3 = new Vector3(bbMax.X, bbMax.Y, bbMin.Z);
            var p4 = new Vector3(bbMin.X, bbMax.Y, bbMin.Z);
            var p5 = new Vector3(bbMin.X, bbMin.Y, bbMax.Z);
            var p6 = new Vector3(bbMax.X, bbMin.Y, bbMax.Z);
            var p7 = new Vector3(bbMax.X, bbMax.Y, bbMax.Z);
            var p8 = new Vector3(bbMin.X, bbMax.Y, bbMax.Z);

            int intColor = color.ToArgb();
            PositionColored[] vertices = new PositionColored[] {
                new PositionColored(p1, intColor), new PositionColored(p2, intColor),
                new PositionColored(p2, intColor), new PositionColored(p3, intColor),
                new PositionColored(p3, intColor), new PositionColored(p4, intColor),
                new PositionColored(p4, intColor), new PositionColored(p1, intColor),
                
                new PositionColored(p1, intColor), new PositionColored(p5, intColor),
                new PositionColored(p2, intColor), new PositionColored(p6, intColor),
                new PositionColored(p3, intColor), new PositionColored(p7, intColor),
                new PositionColored(p4, intColor), new PositionColored(p8, intColor),
                
                new PositionColored(p5, intColor), new PositionColored(p6, intColor),
                new PositionColored(p6, intColor), new PositionColored(p7, intColor),
                new PositionColored(p7, intColor), new PositionColored(p8, intColor),
                new PositionColored(p8, intColor), new PositionColored(p5, intColor),
            };

            device.DrawUserPrimitives(PrimitiveType.LineList, 12, vertices);
        }

        public override void DrawBox(Vector3 bbMin, Vector3 bbMax, Matrix trans, Color4 color)
        {
            var p1 = Vector3.TransformCoordinate(bbMin, trans);
            var p2 = Vector3.TransformCoordinate(new Vector3(bbMax.X, bbMin.Y, bbMin.Z), trans);
            var p3 = Vector3.TransformCoordinate(new Vector3(bbMax.X, bbMax.Y, bbMin.Z), trans);
            var p4 = Vector3.TransformCoordinate(new Vector3(bbMin.X, bbMax.Y, bbMin.Z), trans);
            var p5 = Vector3.TransformCoordinate(new Vector3(bbMin.X, bbMin.Y, bbMax.Z), trans);
            var p6 = Vector3.TransformCoordinate(new Vector3(bbMax.X, bbMin.Y, bbMax.Z), trans);
            var p7 = Vector3.TransformCoordinate(bbMax, trans);
            var p8 = Vector3.TransformCoordinate(new Vector3(bbMin.X, bbMax.Y, bbMax.Z), trans);

            int intColor = color.ToArgb();
            PositionColored[] vertices = new PositionColored[] {
                new PositionColored(p1, intColor), new PositionColored(p2, intColor),
                new PositionColored(p2, intColor), new PositionColored(p3, intColor),
                new PositionColored(p3, intColor), new PositionColored(p4, intColor),
                new PositionColored(p4, intColor), new PositionColored(p1, intColor),
                
                new PositionColored(p1, intColor), new PositionColored(p5, intColor),
                new PositionColored(p2, intColor), new PositionColored(p6, intColor),
                new PositionColored(p3, intColor), new PositionColored(p7, intColor),
                new PositionColored(p4, intColor), new PositionColored(p8, intColor),
                
                new PositionColored(p5, intColor), new PositionColored(p6, intColor),
                new PositionColored(p6, intColor), new PositionColored(p7, intColor),
                new PositionColored(p7, intColor), new PositionColored(p8, intColor),
                new PositionColored(p8, intColor), new PositionColored(p5, intColor),
            };

            device.DrawUserPrimitives(PrimitiveType.LineList, 12, vertices);
        }

        public override void DrawTriangle(Vector3 v0, Vector3 v1, Vector3 v2, Color4 color, float __unnamed004)
        {
            int intColor = color.ToArgb();
            PositionColored[] vertices = new PositionColored[] {
                new PositionColored(v0, intColor),
                new PositionColored(v1, intColor),
                new PositionColored(v2, intColor),
                new PositionColored(v0, intColor),
            };

            device.DrawUserPrimitives(PrimitiveType.LineStrip, 3, vertices);
        }

        public override void DrawTransform(Matrix transform, float orthoLen)
        {
            Vector3 start = new Vector3(transform.M41, transform.M42, transform.M43);

            PositionColored[] vertices = new PositionColored[] {
                new PositionColored(start, 0xff0000), new PositionColored(start + new Vector3(orthoLen,0,0), 0xff0000),
                new PositionColored(start, 0x00ff00), new PositionColored(start + new Vector3(0,orthoLen,0), 0x00ff00),
                new PositionColored(start, 0x0000ff), new PositionColored(start + new Vector3(0,0,orthoLen), 0x0000ff),
            };

            device.DrawUserPrimitives(PrimitiveType.LineList, 3, vertices);
        }

        public override void DrawArc(Vector3 center, Vector3 normal, Vector3 axis, float radiusA, float radiusB, float minAngle, float maxAngle, Color4 color, bool drawSect)
        {
            DrawArc(center, normal, axis, radiusA, radiusB, minAngle, maxAngle, color, drawSect, 10.0f);
        }

        public override void DrawArc(Vector3 center, Vector3 normal, Vector3 axis, float radiusA, float radiusB, float minAngle, float maxAngle, Color4 color, bool drawSect, float stepDegrees)
        {
            Vector3 vx = axis;
            Vector3 vy = Vector3.Cross(normal, axis);
            float step = stepDegrees * ((float)Math.PI / 180.0f);
            int nSteps = (int)((maxAngle - minAngle) / step);
            if (nSteps == 0)
                nSteps = 1;

            Vector3 next = center + radiusA * vx * (float)Math.Cos(minAngle) + radiusB * vy * (float)Math.Sin(minAngle);

            if (drawSect)
                DrawLine(center, next, color);

            int intColor = color.ToArgb();
            PositionColored[] vertices = new PositionColored[nSteps + 1];
            vertices[0] = new PositionColored(next, intColor);
            for (int i = 1; i <= nSteps; i++)
            {
                float angle = minAngle + (maxAngle - minAngle) * (float)i / (float)nSteps;
                next = center + radiusA * vx * (float)Math.Cos(angle) + radiusB * vy * (float)Math.Sin(angle);
                vertices[i] = new PositionColored(next, intColor);
            }
            device.DrawUserPrimitives(PrimitiveType.LineStrip, nSteps, vertices);

            if (drawSect)
                DrawLine(center, next, color);
        }

        public void DrawDebugWorld(DynamicsWorld world)
        {
            device.SetRenderState(RenderState.Lighting, false);
            device.SetTransform(TransformState.World, Matrix.Identity);
            device.VertexFormat = PositionColored.FVF;
            world.DebugDrawWorld();
            device.SetRenderState(RenderState.Lighting, true);
        }
    }
};
