using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;
using BulletSharp;

namespace DemoFramework
{
    public abstract class Demo : IDisposable
    {
        protected Graphics Graphics { get; set; }
        public FreeLook Freelook { get; set; }
        public Input Input { get; set; }

        // Info text
        CultureInfo _culture = CultureInfo.InvariantCulture;
        string _demoText = "";
        protected string DemoText
        {
            get { return _demoText; }
            set
            {
                _demoText = value;
                SetInfoText();
            }
        }

        // Frame counting
        public Clock Clock { get; } = new Clock();

        public float FrameDelta { get; private set; }
        public float FramesPerSecond { get; private set; }
        float _frameAccumulator;

        // Physics
        public DynamicsWorld World { get; protected set; }

        protected CollisionConfiguration CollisionConf;
        protected CollisionDispatcher Dispatcher;
        protected BroadphaseInterface Broadphase;
        protected ConstraintSolver Solver;
        public List<CollisionShape> CollisionShapes { get; } = new List<CollisionShape>();

        protected BoxShape shootBoxShape;
        protected float shootBoxInitialSpeed = 40;
        private BodyPicker _bodyPicker;

        // Debug drawing
        bool _isDebugDrawEnabled;
        DebugDrawModes _debugDrawMode = DebugDrawModes.DrawWireframe;
        IDebugDraw _debugDrawer;

        public DebugDrawModes DebugDrawMode
        {
            get
            {
                return _debugDrawMode;
            }
            set
            {
                _debugDrawMode = value;
                if (_debugDrawer != null)
                    _debugDrawer.DebugMode = value;
            }
        }

        public bool IsDebugDrawEnabled
        {
            get
            {
                return _isDebugDrawEnabled;
            }
            set
            {
                if (value)
                {
                    if (_debugDrawer == null)
                    {
                        _debugDrawer = Graphics.GetPhysicsDebugDrawer();
                        _debugDrawer.DebugMode = _debugDrawMode;
                        if (World != null)
                        {
                            World.DebugDrawer = _debugDrawer;
                        }
                    }
                }
                else
                {
                    if (_debugDrawer != null)
                    {
                        if (World != null)
                        {
                            World.DebugDrawer = null;
                        }
                        if (_debugDrawer is IDisposable)
                        {
                            (_debugDrawer as IDisposable).Dispose();
                        }
                        _debugDrawer = null;
                    }
                }
                _isDebugDrawEnabled = value;
            }
        }

        bool isCullingEnabled = true;
        public bool CullingEnabled
        {
            get
            {
                return isCullingEnabled;
            }
            set
            {
                Graphics.CullingEnabled = value;
                isCullingEnabled = value;
            }
        }

        public void Run()
        {
            using (Graphics = GraphicsLibraryManager.GetGraphics(this))
            {
                Input = new Input(Graphics.Form);
                Freelook = new FreeLook(Input);

                _bodyPicker = new BodyPicker(this);

                Graphics.Initialize();
                Graphics.CullingEnabled = isCullingEnabled;
                OnInitialize();
                if (World == null)
                {
                    OnInitializePhysics();
                }
                if (_isDebugDrawEnabled)
                {
                    if (_debugDrawer == null)
                    {
                        _debugDrawer = Graphics.GetPhysicsDebugDrawer();
                        _debugDrawer.DebugMode = DebugDrawMode;
                    }
                    if (World != null)
                    {
                        World.DebugDrawer = _debugDrawer;
                    }
                }
                Graphics.UpdateView();
                SetInfoText();

                Graphics.Run();

                if (_debugDrawer != null)
                {
                    if (World != null)
                    {
                        World.DebugDrawer = null;
                    }
                    if (_debugDrawer is IDisposable)
                    {
                        (_debugDrawer as IDisposable).Dispose();
                    }
                    _debugDrawer = null;
                }
            }
            Graphics = null;
        }

        protected virtual void OnInitialize()
        {
        }

        protected abstract void OnInitializePhysics();

        public virtual void ClientResetScene()
        {
            _bodyPicker.RemovePickingConstraint();
            ExitPhysics();
            OnInitializePhysics();
            if (World != null && _debugDrawer != null)
            {
                World.DebugDrawer = _debugDrawer;
            }
        }

        public virtual void ExitPhysics()
        {
            if (World != null)
            {
                //remove/dispose constraints
                int i;
                for (i = World.NumConstraints - 1; i >= 0; i--)
                {
                    TypedConstraint constraint = World.GetConstraint(i);
                    World.RemoveConstraint(constraint);
                    constraint.Dispose();
                }

                //remove the rigidbodies from the dynamics world and delete them
                for (i = World.NumCollisionObjects - 1; i >= 0; i--)
                {
                    CollisionObject obj = World.CollisionObjectArray[i];
                    RigidBody body = obj as RigidBody;
                    if (body != null && body.MotionState != null)
                    {
                        body.MotionState.Dispose();
                    }
                    World.RemoveCollisionObject(obj);
                    obj.Dispose();
                }

                //delete collision shapes
                foreach (CollisionShape shape in CollisionShapes)
                    shape.Dispose();
                CollisionShapes.Clear();

                World.Dispose();
                Broadphase.Dispose();
                Dispatcher.Dispose();
                CollisionConf.Dispose();
            }

            if (Broadphase != null)
            {
                Broadphase.Dispose();
            }
            if (Dispatcher != null)
            {
                Dispatcher.Dispose();
            }
            if (CollisionConf != null)
            {
                CollisionConf.Dispose();
            }
        }

        void SetInfoText()
        {
            Graphics.SetInfoText(
                $"Physics: {Clock.PhysicsAverage.ToString("0.000", _culture)} ms\n" +
                $"Render: {Clock.RenderAverage.ToString("0.000", _culture)} ms\n" +
                $"{Clock.FrameCount} FPS\n" +
                "F1 - Help\n" +
                _demoText);
        }

        public virtual void OnUpdate()
        {
            FrameDelta = Clock.GetFrameDelta();
            _frameAccumulator += FrameDelta;
            if (_frameAccumulator >= 1.0f)
            {
                FramesPerSecond = Clock.FrameCount / _frameAccumulator;
                SetInfoText();

                _frameAccumulator = 0.0f;
                Clock.Reset();
            }

            if (World != null)
            {
                Clock.StartPhysics();
                World.StepSimulation(FrameDelta);
                Clock.StopPhysics();
            }

            if (Freelook.Update(FrameDelta))
            {
                Graphics.UpdateView();
            }

            Input.ClearKeyCache();
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                ExitPhysics();
            }
        }

        public virtual void OnHandleInput()
        {
            if (Input.KeysPressed.Count != 0)
            {
                switch (Input.KeysPressed[0])
                {
                    case Keys.Escape:
                    case Keys.Q:
                        Graphics.Form.Close();
                        return;
                    case Keys.F1:
                        MessageBox.Show(
                            "Move using WASD + shift\n" +
                            "Left click - point camera\n" +
                            "Right click - pick up an object using a Point2PointConstraint\n" +
                            "Right click + shift - pick up an object using a fixed Generic6DofConstraint\n" +
                            "Space - shoot box\n" +
                            "Q - quit\n" +
                            Graphics.InfoText,
                            "Help");
                        // Key release won't be captured
                        Input.KeysDown.Remove(Keys.F1);
                        break;
                    case Keys.F3:
                        IsDebugDrawEnabled = !IsDebugDrawEnabled;
                        break;
                    case Keys.F8:
                        Input.ClearKeyCache();
                        GraphicsLibraryManager.ExitWithReload = true;
                        Graphics.Form.Close();
                        break;
                    case Keys.F11:
                        Graphics.IsFullScreen = !Graphics.IsFullScreen;
                        break;
                    case (Keys.Control | Keys.F):
                        const int maxSerializeBufferSize = 1024 * 1024 * 5;
                        using (var serializer = new DefaultSerializer(maxSerializeBufferSize))
                        {
                            World.Serialize(serializer);
                            byte[] dataBytes = new byte[serializer.CurrentBufferSize];
                            System.Runtime.InteropServices.Marshal.Copy(serializer.BufferPointer, dataBytes, 0,
                                dataBytes.Length);
                            using (var file = new System.IO.FileStream("world.bullet", System.IO.FileMode.Create))
                            {
                                file.Write(dataBytes, 0, dataBytes.Length);
                            }
                        }
                        break;
                    case Keys.G:
                        //shadowsEnabled = !shadowsEnabled;
                        break;
                    case Keys.Space:
                        ShootBox(Freelook.Eye, GetCameraRayTo());
                        break;
                    case Keys.Return:
                        ClientResetScene();
                        break;
                }
            }

            _bodyPicker.Update();
        }

        public Vector3 GetCameraRayTo()
        {
            return GetRayTo(Input.MousePoint, Freelook.Eye, Freelook.Target, Graphics.FieldOfView);
        }

        protected Vector3 GetRayTo(Point point, Vector3 eye, Vector3 target, float fov)
        {
            float aspect;

            Vector3 rayForward = target - eye;
            rayForward.Normalize();
            const float farPlane = 10000.0f;
            rayForward *= farPlane;

            Vector3 vertical = Freelook.Up;

            Vector3 hor = Vector3.Cross(rayForward, vertical);
            hor.Normalize();
            vertical = Vector3.Cross(hor, rayForward);
            vertical.Normalize();

            float tanFov = (float)Math.Tan(fov / 2);
            hor *= 2.0f * farPlane * tanFov;
            vertical *= 2.0f * farPlane * tanFov;

            Size clientSize = Graphics.Form.ClientSize;
            if (clientSize.Width > clientSize.Height)
            {
                aspect = (float)clientSize.Width / (float)clientSize.Height;
                hor *= aspect;
            }
            else
            {
                aspect = (float)clientSize.Height / (float)clientSize.Width;
                vertical *= aspect;
            }

            Vector3 rayToCenter = eye + rayForward;
            Vector3 dHor = hor / (float)clientSize.Width;
            Vector3 dVert = vertical / (float)clientSize.Height;

            Vector3 rayTo = rayToCenter - 0.5f * hor + 0.5f * vertical;
            rayTo += (clientSize.Width - point.X) * dHor;
            rayTo -= point.Y * dVert;
            return rayTo;
        }

        public virtual void ShootBox(Vector3 camPos, Vector3 destination)
        {
            if (World == null)
                return;

            const float mass = 1.0f;

            if (shootBoxShape == null)
            {
                shootBoxShape = new BoxShape(1.0f);
                //shootBoxShape.InitializePolyhedralFeatures();
            }

            RigidBody body = LocalCreateRigidBody(mass, Matrix.Translation(camPos), shootBoxShape);
            body.LinearFactor = new Vector3(1, 1, 1);
            //body.Restitution = 1;

            Vector3 linVel = destination - camPos;
            linVel.Normalize();

            body.LinearVelocity = linVel * shootBoxInitialSpeed;
            body.CcdMotionThreshold = 0.5f;
            body.CcdSweptSphereRadius = 0.9f;
        }

        public virtual RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            //rigidbody is dynamic if and only if mass is non zero, otherwise static
            bool isDynamic = (mass != 0.0f);

            Vector3 localInertia = Vector3.Zero;
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);

            RigidBodyConstructionInfo rbInfo = new RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia);
            RigidBody body = new RigidBody(rbInfo);
            rbInfo.Dispose();

            World.AddRigidBody(body);

            return body;
        }
    }
}
