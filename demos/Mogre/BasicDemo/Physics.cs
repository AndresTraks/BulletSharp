using System.Collections.Generic;
using BulletSharp;
using Mogre;

namespace BasicDemo
{
    // For more info:
    // http://bulletphysics.org/mediawiki-1.5.8/index.php/MotionStates#Ogre3d
    class MogreMotionState : MotionState
    {
        Entity entity;
        SceneNode node;
        public RigidBody Body { get; set; }

        public MogreMotionState(Entity entity, SceneNode node, Matrix4 startTransform)
        {
            this.entity = entity;
            this.node = node;
            
            node.Position = startTransform.GetTrans();
            node.Orientation = startTransform.ExtractQuaternion();
        }

        public override Matrix4 WorldTransform
        {
            get
            {
                Matrix4 transform = new Matrix4(node.Orientation);
                transform.SetTrans(node.Position);
                return transform;
            }
            set
            {
                node.Position = value.GetTrans();
                node.Orientation = value.ExtractQuaternion();

                if (Body.ActivationState == ActivationState.ActiveTag)
                {
                    entity.SetMaterialName("BoxMaterial/Active");
                }
                else
                {
                    entity.SetMaterialName("BoxMaterial/Passive");
                }
            }
        }
    }

    class Physics
    {
        public DynamicsWorld World;

        CollisionDispatcher Dispatcher;
        BroadphaseInterface Broadphase;
        List<CollisionShape> CollisionShapes = new List<CollisionShape>();
        CollisionConfiguration collisionConf;

        ///create 125 (5x5x5) dynamic objects
        public int ArraySizeX = 5, ArraySizeY = 5, ArraySizeZ = 5;

        ///scaling of the objects (0.1 = 20 centimeter boxes )
        float StartPosX = -5;
        float StartPosY = -5;
        float StartPosZ = -3;

        public Physics(SceneManager sceneMgr)
        {
            // collision configuration contains default setup for memory, collision setup
            collisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(collisionConf);

            Broadphase = new DbvtBroadphase();

            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, null, collisionConf);
            World.Gravity = new Vector3(0, -10, 0);

            // create the ground
            CollisionShape groundShape = new BoxShape(50, 1, 50);
            CollisionShapes.Add(groundShape);
            CollisionObject ground = LocalCreateRigidBody(0, Matrix4.IDENTITY, groundShape);
            ground.UserObject = "Ground";

            // create a few dynamic rigidbodies
            float mass = 1.0f;

            CollisionShape colShape = new BoxShape(1);
            CollisionShapes.Add(colShape);
            Vector3 localInertia = colShape.CalculateLocalInertia(mass);

            var rbInfo = new RigidBodyConstructionInfo(mass, null, colShape, localInertia);

            float start_x = StartPosX - ArraySizeX / 2;
            float start_y = StartPosY;
            float start_z = StartPosZ - ArraySizeZ / 2;

            int k, i, j;
            for (k = 0; k < ArraySizeY; k++)
            {
                for (i = 0; i < ArraySizeX; i++)
                {
                    for (j = 0; j < ArraySizeZ; j++)
                    {
                        Matrix4 startTransform = new Matrix4();
                        startTransform.MakeTrans(
                            new Vector3(
                                2*i + start_x,
                                2*k + start_y,
                                2*j + start_z
                                )
                            );

                        // using motionstate is recommended, it provides interpolation capabilities
                        // and only synchronizes 'active' objects
                        int index = (k * ArraySizeX + i) * ArraySizeZ + j;
                        Entity box = sceneMgr.CreateEntity("Box" + index.ToString(), "box.mesh");
                        box.SetMaterialName("BoxMaterial/Active");
                        SceneNode boxNode = sceneMgr.RootSceneNode.CreateChildSceneNode("BoxNode" + index.ToString());
                        boxNode.AttachObject(box);
                        boxNode.Scale(new Vector3(2, 2, 2));
                        var mogreMotionState = new MogreMotionState(box, boxNode, startTransform);
                        rbInfo.MotionState = mogreMotionState;

                        RigidBody body = new RigidBody(rbInfo);
                        mogreMotionState.Body = body;

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
            //remove/dispose constraints
            int i;
            for (i = World.NumConstraints - 1; i >= 0; i--)
            {
                TypedConstraint constraint = World.GetConstraint(i);
                World.RemoveConstraint(constraint);
                constraint.Dispose(); ;
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
            if (Dispatcher != null)
            {
                Dispatcher.Dispose();
            }
        }

        public RigidBody LocalCreateRigidBody(float mass, Matrix4 startTransform, CollisionShape shape)
        {
            bool isDynamic = (mass != 0.0f);

            Vector3 localInertia = Vector3.ZERO;
            if (isDynamic)
                shape.CalculateLocalInertia(mass, out localInertia);

            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);

            RigidBody body;
            using (var rbInfo = new RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia))
            {
                body = new RigidBody(rbInfo);
            }

            World.AddRigidBody(body);

            return body;
        }
    }
}
