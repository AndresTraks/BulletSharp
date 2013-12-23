using System;
using BulletSharp;
using DemoFramework;

namespace FeatherStoneDemo
{
    class MultiBodySettings
    {
        public Vector3 BasePosition { get; set; }
        public bool CanSleep { get; set; }
        public bool CreateConstraints { get; set; }
        public bool DisableParentCollision { get; set; }
        public bool IsFixedBase { get; set; }
        public int NumLinks { get; set; }
        public bool UsePrismatic { get; set; }
    }

    class FeatherStoneDemo: Demo
    {
        Vector3 eye = new Vector3(-50, 25, 35);
        Vector3 target = new Vector3(0, 5, -10);

        // create 125 (5x5x5) dynamic objects
        const int ArraySizeX = 5, ArraySizeY = 5, ArraySizeZ = 5;

        // scaling of the objects (0.1 = 20 centimeter boxes )
        const float StartPosX = -5;
        const float StartPosY = 2;
        const float StartPosZ = -3;

        const float Scaling = 0.4f;
        const float Friction = 1.0f;

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - FeatherStone Demo");
            Graphics.SetInfoText("Move using mouse and WASD+shift\n" +
                "F3 - Toggle debug\n" +
                //"F11 - Toggle fullscreen\n" +
                "Space - Shoot box");
        }

        protected override void OnInitializePhysics()
        {
            // collision configuration contains default setup for memory, collision setup
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);

            Broadphase = new DbvtBroadphase();
            Solver = new MultiBodyConstraintSolver();

            World = new MultiBodyDynamicsWorld(Dispatcher, Broadphase, Solver as MultiBodyConstraintSolver, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            // create a few basic rigid bodies
            BoxShape groundShape = new BoxShape(50, 50, 50);
            //groundShape.InitializePolyhedralFeatures();
            //CollisionShape groundShape = new StaticPlaneShape(new Vector3(0,1,0), 50);

            CollisionShapes.Add(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix.Translation(0, -50, 0), groundShape);
            ground.UserObject = "Ground";

            // create a few dynamic rigidbodies
            const float mass = 1.0f;

            BoxShape colShape = new BoxShape(1);
            CollisionShapes.Add(colShape);
            Vector3 localInertia = colShape.CalculateLocalInertia(mass);

            const float start_x = StartPosX - ArraySizeX / 2;
            const float start_y = StartPosY;
            const float start_z = StartPosZ - ArraySizeZ / 2;

            int k, i, j;
            for (k = 0; k < ArraySizeY; k++)
            {
                for (i = 0; i < ArraySizeX; i++)
                {
                    for (j = 0; j < ArraySizeZ; j++)
                    {
                        Matrix startTransform = Matrix.Translation(
                            3 * i + start_x,
                            3 * k + start_y,
                            3 * j + start_z
                        );

                        // using motionstate is recommended, it provides interpolation capabilities
                        // and only synchronizes 'active' objects
                        DefaultMotionState myMotionState = new DefaultMotionState(startTransform);
                        RigidBodyConstructionInfo rbInfo =
                            new RigidBodyConstructionInfo(mass, myMotionState, colShape, localInertia);
                        RigidBody body = new RigidBody(rbInfo);
                        rbInfo.Dispose();

                        World.AddRigidBody(body);
                    }
                }
            }

            var settings = new MultiBodySettings()
            {
                BasePosition = new Vector3(60, 29.5f, -2) * Scaling,
                CanSleep = true,
                CreateConstraints = true,
                DisableParentCollision = true, // the self-collision has conflicting/non-resolvable contact normals
                IsFixedBase = false,
                NumLinks = 2,
                UsePrismatic = true
            };
            var multiBodyA = CreateFeatherstoneMultiBody(World as MultiBodyDynamicsWorld, settings);

            settings.NumLinks = 10;
            settings.BasePosition = new Vector3(0, 29.5f, -settings.NumLinks * 4);
            settings.IsFixedBase = true;
            settings.UsePrismatic = false;
            var multiBodyB = CreateFeatherstoneMultiBody(World as MultiBodyDynamicsWorld, settings);

            settings.BasePosition = new Vector3(-20 * Scaling, 29.5f * Scaling, -settings.NumLinks * 4 * Scaling);
            settings.IsFixedBase = false;
            var multiBodyC = CreateFeatherstoneMultiBody(World as MultiBodyDynamicsWorld, settings);

            settings.BasePosition = new Vector3(-20, 9.5f, -settings.NumLinks * 4);
            settings.IsFixedBase = true;
            settings.UsePrismatic = true;
            settings.DisableParentCollision = true;
            var multiBodyPrim = CreateFeatherstoneMultiBody(World as MultiBodyDynamicsWorld, settings);
        }

        MultiBody CreateFeatherstoneMultiBody(MultiBodyDynamicsWorld world, MultiBodySettings settings)
        {
            int nLinks = settings.NumLinks;
            float mass = 13.5f * Scaling;
            Vector3 inertia = new Vector3(91, 344, 253) * Scaling * Scaling;

            var body = new MultiBody(nLinks, mass, inertia, settings.IsFixedBase, settings.CanSleep);
            //body.HasSelfCollision = false;

            //Quaternion orn = new Quaternion(0, 0, 1, -0.125f * Math.PI);
            Quaternion orn = new Quaternion(0, 0, 0, 1);
            body.BasePosition = settings.BasePosition;
            body.WorldToBaseRot = orn;
            body.BaseVelocity = Vector3.Zero;


            Vector3 joint_axis_hinge = new Vector3(1, 0, 0);
            Vector3 joint_axis_prismatic = new Vector3(0, 0, 1);
            Quaternion parent_to_child = orn.Inverse();
            Vector3 joint_axis_child_prismatic = parent_to_child.Rotate(joint_axis_prismatic);
            Vector3 joint_axis_child_hinge = parent_to_child.Rotate(joint_axis_hinge);

            int this_link_num = -1;
            int link_num_counter = 0;

            Vector3 pos = new Vector3(0, 0, 9.0500002f) * Scaling;
            Vector3 joint_axis_position = new Vector3(0, 0, 4.5250001f) * Scaling;

            for (int i = 0; i < nLinks; i++)
            {
                float initial_joint_angle = 0.3f;
                if (i > 0)
                    initial_joint_angle = -0.06f;

                int child_link_num = link_num_counter++;

                if (settings.UsePrismatic) // i == (nLinks - 1))
                {
                    body.SetupPrismatic(child_link_num, mass, inertia, this_link_num,
                        parent_to_child, joint_axis_child_prismatic, parent_to_child.Rotate(pos), settings.DisableParentCollision);
                }
                else
                {
                    body.SetupRevolute(child_link_num, mass, inertia, this_link_num,
                        parent_to_child, joint_axis_child_hinge, joint_axis_position, parent_to_child.Rotate(pos - joint_axis_position), settings.DisableParentCollision);
                }
                body.SetJointPos(child_link_num, initial_joint_angle);
                this_link_num = i;

                /*if (false) //!useGroundShape && i == 4)
                {
                    Vector3 pivotInAworld = new Vector3(0, 20, 46);
                    Vector3 pivotInAlocal = body.WorldPosToLocal(i, pivotInAworld);
                    Vector3 pivotInBworld = pivotInAworld;
                    MultiBodyPoint2Point p2p = new MultiBodyPoint2Point(body, i, TypedConstraint.FixedBody, pivotInAlocal, pivotInBworld);
                    (World as MultiBodyDynamicsWorld).AddMultiBodyConstraint(p2p);
                }*/

                if (settings.UsePrismatic)
                {
                    //MultiBodyConstraint con = new MultiBodyJointLimitConstraint(body, nLinks - 1, 2, 3);

                    if (settings.CreateConstraints)
                    {
                        MultiBodyConstraint con = new MultiBodyJointLimitConstraint(body, i, -1, 1);
                        (World as MultiBodyDynamicsWorld).AddMultiBodyConstraint(con);
                    }
                }
                else
                {
                    //if (true)
                    {
                        var con = new MultiBodyJointMotor(body, i, 0, 50000);
                        (World as MultiBodyDynamicsWorld).AddMultiBodyConstraint(con);
                    }

                    var con2 = new MultiBodyJointLimitConstraint(body, i, -1, 1);
                    (World as MultiBodyDynamicsWorld).AddMultiBodyConstraint(con2);
                }
            }

            // Add a collider for the base
            Quaternion[] worldToLocal = new Quaternion[nLinks + 1];
            Vector3[] localOrigin = new Vector3[nLinks + 1];

            worldToLocal[0] = body.WorldToBaseRot;
            localOrigin[0] = body.BasePosition;

            //Vector3 halfExtents = new Vector3(7.5f, 0.05f, 4.5f);
            Vector3 halfExtents = new Vector3(7.5f, 0.45f, 4.5f);

            float[] posB = new float[] { localOrigin[0].X, localOrigin[0].Y, localOrigin[0].Z, 1 };
            //float[] quatB = new float[] { worldToLocal[0].X, worldToLocal[0].Y, worldToLocal[0].Z, worldToLocal[0].W };

            //if (true)
            {
                CollisionShape box = new BoxShape(halfExtents * Scaling);
                var bodyInfo = new RigidBodyConstructionInfo(mass, null, box, inertia);
                RigidBody bodyB = new RigidBody(bodyInfo);
                var collider = new MultiBodyLinkCollider(body, -1);

                collider.CollisionShape = box;
                Matrix tr = Matrix.RotationQuaternion(worldToLocal[0].Inverse()) * Matrix.Translation(localOrigin[0]);
                collider.WorldTransform = tr;
                bodyB.WorldTransform = tr;

                World.AddCollisionObject(collider, CollisionFilterGroups.StaticFilter,
                    CollisionFilterGroups.DefaultFilter | CollisionFilterGroups.StaticFilter);
                collider.Friction = Friction;
                body.BaseCollider = collider;
            }


            for (int i = 0; i < body.NumLinks; i++)
            {
                int parent = body.GetParent(i);
                worldToLocal[i + 1] = body.GetParentToLocalRot(i) * worldToLocal[parent + 1];
                localOrigin[i + 1] = localOrigin[parent + 1] + (worldToLocal[i + 1].Inverse().Rotate(body.GetRVector(i)));
            }

            for (int i = 0; i < body.NumLinks; i++)
            {
                CollisionShape box = new BoxShape(halfExtents * Scaling);
                var collider = new MultiBodyLinkCollider(body, i);

                collider.CollisionShape = box;
                Matrix tr = Matrix.RotationQuaternion(worldToLocal[i + 1].Inverse()) * Matrix.Translation(localOrigin[i + 1]);
                collider.WorldTransform = tr;
                World.AddCollisionObject(collider, CollisionFilterGroups.StaticFilter,
                    CollisionFilterGroups.DefaultFilter | CollisionFilterGroups.StaticFilter);
                collider.Friction = Friction;

                body.GetLink(i).Collider = collider;
                //World.DebugDrawer.DrawBox(halfExtents, pos, quat);
            }

            (World as MultiBodyDynamicsWorld).AddMultiBody(body);
            return body;
        }

        public override RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            //rigidbody is dynamic if and only if mass is non zero, otherwise static
            bool isDynamic = (mass != 0.0f);

            Vector3 localInertia = Vector3.Zero;
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

            RigidBodyConstructionInfo rbInfo = new RigidBodyConstructionInfo(mass, null, shape, localInertia);
            RigidBody body = new RigidBody(rbInfo);
            rbInfo.Dispose();
            body.WorldTransform = startTransform;

            World.AddRigidBody(body, CollisionFilterGroups.DefaultFilter,
                CollisionFilterGroups.DefaultFilter | CollisionFilterGroups.StaticFilter);

            return body;
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new FeatherStoneDemo())
            {
                LibraryManager.Initialize(demo);
            }
        }
    }
}
