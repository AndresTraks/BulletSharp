using System;
using System.Drawing;
using System.Windows.Forms;
using BulletSharp;

namespace DemoFramework
{
    public abstract class Demo : System.IDisposable
    {
        bool disposed = false;
        Graphics _graphics;
        protected Graphics Graphics
        {
            get { return _graphics; }
            private set { _graphics = value; }
        }
        public FreeLook Freelook { get; private set; }

        Input _input;
        protected Input Input
        {
            get { return _input; }
            private set { _input = value; }
        }


        // Frame counting
        Clock clock = new Clock();
        float frameAccumulator;
        int frameCount;

        float _frameDelta;
        public float FrameDelta
        {
            get { return _frameDelta; }
            private set { _frameDelta = value; }
        }
        public float FramesPerSecond { get; private set; }


        // Physics
        DynamicsWorld _world;
        public DynamicsWorld World
        {
            get { return _world; }
            protected set { _world = value; }
        }

        protected CollisionConfiguration CollisionConf;
        protected CollisionDispatcher Dispatcher;
        protected BroadphaseInterface Broadphase;
        protected ConstraintSolver Solver;
        public AlignedCollisionShapeArray CollisionShapes { get; private set; }

        protected BoxShape shootBoxShape;
        protected float shootBoxInitialSpeed = 40;
        RigidBody pickedBody;
        bool use6Dof = false;
        protected TypedConstraint pickConstraint;
        float oldPickingDist;


        public Demo()
        {
            CollisionShapes = new AlignedCollisionShapeArray();
        }

        public void Run()
        {
            if (_graphics != null)
            {
                _graphics.Form.Close();
            }
            _graphics = LibraryManager.GetGraphics(this);

            _input = new Input(Graphics.Form);
            Freelook = new FreeLook(_input);

            _graphics.Initialize();
            OnInitialize();
            OnInitializePhysics();
            _graphics.UpdateView();

            clock.Start();
            _graphics.Run();
        }

        protected virtual void OnInitialize()
        {
        }

        protected abstract void OnInitializePhysics();

        public virtual void ClientResetScene()
        {
            RemovePickingConstraint();
            ExitPhysics();
            OnInitializePhysics();
        }

        public void ExitPhysics()
        {
            //removed/dispose constraints
            int i;
            for (i = _world.NumConstraints - 1; i >= 0; i--)
            {
                TypedConstraint constraint = _world.GetConstraint(i);
                _world.RemoveConstraint(constraint);
                constraint.Dispose(); ;
            }

            //remove the rigidbodies from the dynamics world and delete them
            for (i = _world.NumCollisionObjects - 1; i >= 0; i--)
            {
                CollisionObject obj = _world.CollisionObjectArray[i];
                RigidBody body = obj as RigidBody;
                if (body != null && body.MotionState != null)
                {
                    body.MotionState.Dispose();
                }
                _world.RemoveCollisionObject(obj);
                obj.Dispose();
            }

            //delete collision shapes
            foreach (CollisionShape shape in CollisionShapes)
                shape.Dispose();
            CollisionShapes.Clear();

            _world.Dispose();
            Broadphase.Dispose();
            Dispatcher.Dispose();
            CollisionConf.Dispose();
        }

        public virtual void OnUpdate()
        {
            _frameDelta = clock.Update();
            frameAccumulator += _frameDelta;
            ++frameCount;
            if (frameAccumulator >= 1.0f)
            {
                FramesPerSecond = frameCount / frameAccumulator;

                frameAccumulator = 0.0f;
                frameCount = 0;
            }

            _world.StepSimulation(_frameDelta);

            if (Freelook.Update(_frameDelta))
                _graphics.UpdateView();

            _input.ClearKeyCache();
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposed)
            {
                if (disposing)
                {
                    // Free other state (managed objects).
                }
                // Free your own state (unmanaged objects).
                // Set large fields to null.
                disposed = true;
            }
        }

        ~Demo()
        {
            Dispose(false);
        }

        public virtual void OnHandleInput()
        {
            if (_input.KeysPressed.Count != 0)
            {
                Keys key = _input.KeysPressed[0];
                switch (key)
                {
                    case Keys.Escape:
                    case Keys.Q:
                        Graphics.Form.Close();
                        return;
                    case Keys.F3:
                        //IsDebugDrawEnabled = !IsDebugDrawEnabled;
                        break;
                    case Keys.F8:
                        Input.ClearKeyCache();
                        LibraryManager.ExitWithReload = true;
                        Graphics.Form.Close();
                        break;
                    case Keys.F11:
                        //ToggleFullScreen();
                        break;
                    case Keys.G:
                        //shadowsEnabled = !shadowsEnabled;
                        break;
                    case Keys.Space:
                        ShootBox(Freelook.Eye, GetRayTo(_input.MousePoint, Freelook.Eye, Freelook.Target, Graphics.FieldOfView));
                        break;
                    case Keys.Return:
                        ClientResetScene();
                        break;
                }
            }

            if (_input.MousePressed != MouseButtons.None)
            {
                Vector3 rayTo = GetRayTo(_input.MousePoint, Freelook.Eye, Freelook.Target, Graphics.FieldOfView);

                if (_input.MousePressed == MouseButtons.Right)
                {
                    if (World != null)
                    {
                        Vector3 rayFrom = Freelook.Eye;

                        CollisionWorld.ClosestRayResultCallback rayCallback = new CollisionWorld.ClosestRayResultCallback(rayFrom, rayTo);
                        World.RayTest(rayFrom, rayTo, rayCallback);
                        if (rayCallback.HasHit)
                        {
                            RigidBody body = rayCallback.CollisionObject as RigidBody;
                            if (body != null)
                            {
                                if (!(body.IsStaticObject || body.IsKinematicObject))
                                {
                                    pickedBody = body;
                                    pickedBody.ActivationState = ActivationState.DisableDeactivation;

                                    Vector3 pickPos = rayCallback.HitPointWorld;
                                    Vector3 localPivot = Vector3.TransformCoordinate(pickPos, Matrix.Invert(body.CenterOfMassTransform));

                                    if (use6Dof)
                                    {
                                        Generic6DofConstraint dof6 = new Generic6DofConstraint(body, Matrix.Translation(localPivot), false);
                                        dof6.LinearLowerLimit = Vector3.Zero;
                                        dof6.LinearUpperLimit = Vector3.Zero;
                                        dof6.AngularLowerLimit = Vector3.Zero;
                                        dof6.AngularUpperLimit = Vector3.Zero;

                                        World.AddConstraint(dof6);
                                        pickConstraint = dof6;

                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 0);
                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 1);
                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 2);
                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 3);
                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 4);
                                        dof6.SetParam(ConstraintParam.StopCfm, 0.8f, 5);

                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 0);
                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 1);
                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 2);
                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 3);
                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 4);
                                        dof6.SetParam(ConstraintParam.StopErp, 0.1f, 5);
                                    }
                                    else
                                    {
                                        Point2PointConstraint p2p = new Point2PointConstraint(body, localPivot);
                                        World.AddConstraint(p2p);
                                        pickConstraint = p2p;
                                        p2p.Setting.ImpulseClamp = 30;
                                        //very weak constraint for picking
                                        p2p.Setting.Tau = 0.001f;
                                        /*
                                        p2p.SetParam(ConstraintParams.Cfm, 0.8f, 0);
                                        p2p.SetParam(ConstraintParams.Cfm, 0.8f, 1);
                                        p2p.SetParam(ConstraintParams.Cfm, 0.8f, 2);
                                        p2p.SetParam(ConstraintParams.Erp, 0.1f, 0);
                                        p2p.SetParam(ConstraintParams.Erp, 0.1f, 1);
                                        p2p.SetParam(ConstraintParams.Erp, 0.1f, 2);
                                        */
                                    }
                                    use6Dof = !use6Dof;

                                    oldPickingDist = (pickPos - rayFrom).Length();
                                }
                            }
                        }
                    }
                }
            }
            else if (_input.MouseReleased == MouseButtons.Right)
            {
                RemovePickingConstraint();
            }

            // Mouse movement
            if (_input.MouseDown == MouseButtons.Right)
            {
                if (pickConstraint != null)
                {
                    Vector3 newRayTo = GetRayTo(_input.MousePoint, Freelook.Eye, Freelook.Target, Graphics.FieldOfView);

                    if (pickConstraint.ConstraintType == TypedConstraintType.D6)
                    {
                        Generic6DofConstraint pickCon = pickConstraint as Generic6DofConstraint;

                        //keep it at the same picking distance
                        Vector3 rayFrom = Freelook.Eye;
                        Vector3 dir = newRayTo - rayFrom;
                        dir.Normalize();
                        dir *= oldPickingDist;
                        Vector3 newPivotB = rayFrom + dir;

                        Matrix tempFrameOffsetA = pickCon.FrameOffsetA;
                        tempFrameOffsetA.M41 = newPivotB.X;
                        tempFrameOffsetA.M42 = newPivotB.Y;
                        tempFrameOffsetA.M43 = newPivotB.Z;
                        pickCon.FrameOffsetA = tempFrameOffsetA;
                    }
                    else
                    {
                        Point2PointConstraint pickCon = pickConstraint as Point2PointConstraint;

                        //keep it at the same picking distance
                        Vector3 rayFrom = Freelook.Eye;
                        Vector3 dir = newRayTo - rayFrom;
                        dir.Normalize();
                        dir *= oldPickingDist;
                        pickCon.PivotInB = rayFrom + dir;
                    }
                }
            }
        }

        void RemovePickingConstraint()
        {
            if (pickConstraint != null && World != null)
            {
                World.RemoveConstraint(pickConstraint);
                pickConstraint.Dispose();
                pickConstraint = null;
                pickedBody.ForceActivationState(ActivationState.ActiveTag);
                pickedBody.DeactivationTime = 0;
                pickedBody = null;
            }
        }

        Vector3 GetRayTo(Point point, Vector3 eye, Vector3 target, float fov)
        {
            float aspect;

            Vector3 rayForward = target - eye;
            rayForward.Normalize();
            float farPlane = 10000.0f;
            rayForward *= farPlane;

            Vector3 vertical = Vector3.UnitY;

            Vector3 hor = Vector3.Cross(rayForward, vertical);
            hor.Normalize();
            vertical = Vector3.Cross(hor, rayForward);
            vertical.Normalize();

            float tanFov = (float)Math.Tan(fov / 2);
            hor *= 2.0f * farPlane * tanFov;
            vertical *= 2.0f * farPlane * tanFov;

            Size clientSize = _graphics.Form.ClientSize;
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
            if (_world == null)
                return;

            float mass = 1.0f;

            if (shootBoxShape == null)
            {
                shootBoxShape = new BoxShape(1.0f);
                shootBoxShape.InitializePolyhedralFeatures();
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

            _world.AddRigidBody(body);

            return body;
        }
    }
}
