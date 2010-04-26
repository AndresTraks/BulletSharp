using BulletSharp;
using SlimDX;
using SlimDX.Direct3D9;

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
