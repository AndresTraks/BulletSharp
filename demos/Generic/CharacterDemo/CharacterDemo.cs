using BulletSharp;
using DemoFramework;
using DemoFramework.FileLoaders;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace CharacterDemo
{
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

            //ConvexHullShape creates an internal copy of the vertices
            var verticesTransformed = vertices.Select(v => new Vector3(0.5f * v.X, 0.375f * v.Z, -0.5f * v.Y));
            var shape = new ConvexHullShape(verticesTransformed);

            const float mass = 0.0f;
            //can use a shift
            Matrix startTransform = Matrix.Translation(0, -10.0f, 0);
            _demo.LocalCreateRigidBody(mass, startTransform, shape);
        }
    }

    sealed class CharacterDemo : Demo
    {
        private PairCachingGhostObject _ghostObject;
        private KinematicCharacterController _character;
        private ClosestConvexResultCallback _convexResultCallback;
        private SphereShape _cameraSphere;
        private CapsuleShape _capsuleShape;

        protected override void OnInitialize()
        {
            Freelook.Up = Vector3.UnitY;
            Freelook.Eye = new Vector3(10, 0, 10);
            Freelook.Target = Vector3.Zero;

            Graphics.SetFormText("BulletSharp - Character Demo");
            DemoText = "Space - Jump";
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new AxisSweep3(new Vector3(-1000, -1000, -1000), new Vector3(1000, 1000, 1000));
            Solver = new SequentialImpulseConstraintSolver();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.DispatchInfo.AllowedCcdPenetration = 0.0001f;
            //World.Gravity = Freelook.Up * -10.0f;

            Broadphase.OverlappingPairCache.SetInternalGhostPairCallback(new GhostPairCallback());

            const float characterHeight = 1.75f;
            const float characterWidth = 1.75f;
            _capsuleShape = new CapsuleShape(characterWidth, characterHeight);
            _ghostObject = new PairCachingGhostObject()
            {
                CollisionShape = _capsuleShape,
                CollisionFlags = CollisionFlags.CharacterObject,
                WorldTransform = Matrix.Translation(10.210098f, -1.6433364f, 16.453260f)
            };
            World.AddCollisionObject(_ghostObject, CollisionFilterGroups.CharacterFilter, CollisionFilterGroups.StaticFilter | CollisionFilterGroups.DefaultFilter);

            const float stepHeight = 0.35f;
            _character = new KinematicCharacterController(_ghostObject, _capsuleShape, stepHeight);
            World.AddAction(_character);

            var bspLoader = new BspLoader();
            bspLoader.LoadBspFile(Path.Combine("data", "BspDemo.bsp"));
            var bsp2Bullet = new BspToBulletConverter(this);
            bsp2Bullet.ConvertBsp(bspLoader, 0.1f);

            _convexResultCallback = new ClosestConvexResultCallback();
            _convexResultCallback.CollisionFilterMask = CollisionFilterGroups.StaticFilter;
            _cameraSphere = new SphereShape(0.2f);
        }

        public override void ClientResetScene()
        {
            World.Broadphase.OverlappingPairCache.CleanProxyFromPairs(_ghostObject.BroadphaseHandle, World.Dispatcher);

            _character.Reset(World);
            Vector3 warp = new Vector3(10.210001f, -2.0306311f, 16.576973f);
            _character.Warp(warp);
        }

        public override void OnHandleInput()
        {
            Matrix transform = _ghostObject.WorldTransform;

            Vector3 forwardDir = new Vector3(transform.M31, transform.M32, transform.M33);
            forwardDir.Normalize();
            //Console.WriteLine("forwardDir={0}", forwardDir);

            Vector3 upDir = new Vector3(transform.M21, transform.M22, transform.M23);
            upDir.Normalize();

            Vector3 walkDirection = Vector3.Zero;
            const float walkVelocity = 1.1f * 4.0f;
            float walkSpeed = walkVelocity * FrameDelta * 10;// * 0.0001f;
            float turnSpeed = FrameDelta * 3;
            Vector3 position = transform.Origin;

            if (Input.KeysDown.Contains(Keys.Left))
            {
                transform.Origin = Vector3.Zero;
                transform *= Matrix.RotationAxis(upDir, -turnSpeed);
                transform.Origin = position;
                _ghostObject.WorldTransform = transform;
            }
            if (Input.KeysDown.Contains(Keys.Right))
            {
                transform.Origin = Vector3.Zero;
                transform *= Matrix.RotationAxis(upDir, turnSpeed);
                transform.Origin = position;
                _ghostObject.WorldTransform = transform;
            }

            if (Input.KeysDown.Contains(Keys.Up))
            {
                walkDirection += forwardDir;
            }
            if (Input.KeysDown.Contains(Keys.Down))
            {
                walkDirection -= forwardDir;
            }

            Vector3 cameraPos = position - forwardDir * 12 + upDir * 5;

            //use the convex sweep test to find a safe position for the camera (not blocked by static geometry)
            _convexResultCallback.ConvexFromWorld = position;
            _convexResultCallback.ConvexToWorld = cameraPos;
            _convexResultCallback.ClosestHitFraction = 1.0f;
            World.ConvexSweepTest(_cameraSphere, Matrix.Translation(position), Matrix.Translation(cameraPos), _convexResultCallback);
            if (_convexResultCallback.HasHit)
            {
                cameraPos = Vector3.Lerp(position, cameraPos, _convexResultCallback.ClosestHitFraction);
            }
            Freelook.Eye = cameraPos;
            Freelook.Target = position;

            _character.SetWalkDirection(walkDirection * walkSpeed);

            if (Input.KeysDown.Contains(Keys.Space))
            {
                _character.Jump();
                return;
            }

            base.OnHandleInput();
        }

        public override void ExitPhysics()
        {
            _cameraSphere.Dispose();
            _capsuleShape.Dispose();

            base.ExitPhysics();
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new CharacterDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
