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
                    DebugDrawer.SetDebugMode(0);
                IsDebugDrawEnabled = false;
            }
            else
            {
                if (DebugDrawer == null)
                {
                    DebugDrawer = new PhysicsDebugDraw(device);
                    World.DebugDrawer = DebugDrawer;
                }
                DebugDrawer.SetDebugMode(modes);
                IsDebugDrawEnabled = true;
            }
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

            Vector3 localInertia = new Vector3(0, 0, 0);
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);

            RigidBody.RigidBodyConstructionInfo rbInfo = new RigidBody.RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia);
            RigidBody body = new RigidBody(rbInfo);

            World.AddRigidBody(body);

            return body;
        }
    };

    public class PhysicsDebugDraw : DebugDraw
    {
        SlimDX.Direct3D9.Device device;

        public PhysicsDebugDraw(SlimDX.Direct3D9.Device device)
        {
            this.device = device;
        }

        public override void DrawLine(Vector3 from, Vector3 to, Color4 color)
        {
            PositionColored[] vertices = new PositionColored[2];
            vertices[0] = new PositionColored(from, color.ToArgb());
            vertices[1] = new PositionColored(to, color.ToArgb());
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
