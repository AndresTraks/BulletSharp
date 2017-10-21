using BulletSharp;
using System;
using System.Collections.Generic;

namespace MotorDemo
{
    public class TestRig
    {
        private const int NumLegs = 6;
        private const int JointCount = 2 * NumLegs;

        private const float BodyRadius = 0.25f;
        private const float BodyHeight = 0.25f;

        private const float ThighLength = 0.45f;
        private const float ShinLength = 0.75f;

        private DynamicsWorld _ownerWorld;
        private bool _isFixed;

        private CollisionShape _rootShape;
        private CollisionShape _thighShape;
        private CollisionShape _shinShape;
        private RigidBody _rootBody;
        private List<RigidBody> _jointBodies = new List<RigidBody>(JointCount);

        private const float PI_4 = (float)(0.25f * Math.PI);
        private const float PI_8 = (float)(0.125f * Math.PI);

        public HingeConstraint[] Joints { get; } = new HingeConstraint[JointCount];

        public TestRig(DynamicsWorld ownerWorld, Vector3 position, bool isFixed)
        {
            _ownerWorld = ownerWorld;
            _isFixed = isFixed;

            Matrix transform = Matrix.Translation(position);
            CreateRoot(transform);
            CreateLegs(transform);
        }

        private void CreateRoot(Matrix transform)
        {
            _rootShape = new CapsuleShape(BodyRadius, BodyHeight);
            float mass = _isFixed ? 0 : 1;
            _rootBody = LocalCreateRigidBody(mass, transform, _rootShape);
            SetDamping(_rootBody);
        }

        private void CreateLegs(Matrix rootTransform)
        {
            _thighShape = new CapsuleShape(0.10f, ThighLength);
            _shinShape = new CapsuleShape(0.08f, ShinLength);

            const float PI_2 = (float)(0.5f * Math.PI);
            Vector3 up = new Vector3(0, 1, 0);
            for (int i = 0; i < NumLegs; i++)
            {
                float direction = (float)(2 * Math.PI * i / NumLegs);

                Vector3 thighOrigin = ToCartesian(direction, BodyRadius + 0.5f * ThighLength);
                Vector3 toBone = thighOrigin.Normalized;
                Vector3 vAxis = Vector3.Cross(toBone, up);
                Matrix transform = Matrix.RotationQuaternion(Quaternion.RotationAxis(vAxis, PI_2)) * Matrix.Translation(thighOrigin);
                RigidBody thigh = LocalCreateRigidBody(1, transform * rootTransform, _thighShape);
                SetDamping(thigh);

                Vector3 translation = ToCartesian(direction, BodyRadius + ThighLength);
                translation.Y = -0.5f * ShinLength;
                transform = Matrix.Translation(translation);
                RigidBody shin = LocalCreateRigidBody(1, transform * rootTransform, _shinShape);
                SetDamping(shin);

                Joints[2 * i] = CreateHipJoint(_rootBody, thigh, direction);
                _ownerWorld.AddConstraint(Joints[2 * i], true);

                Joints[2 * i + 1] = CreateKneeJoint(_rootBody, thigh, shin, direction);
                _ownerWorld.AddConstraint(Joints[2 * i + 1], true);

                _jointBodies.Add(thigh);
                _jointBodies.Add(shin);
            }
        }

        private static HingeConstraint CreateHipJoint(RigidBody root, RigidBody thigh, float direction)
        {
            Vector3 origin = ToCartesian(direction, BodyRadius);
            Matrix rootFrame = Matrix.RotationYawPitchRoll(-direction, 0, 0) * Matrix.Translation(origin);

            Matrix thighFrame = rootFrame * root.WorldTransform * Matrix.Invert(thigh.WorldTransform);

            var hinge = new HingeConstraint(root, thigh, rootFrame, thighFrame);
            hinge.SetLimit(-0.75f * PI_4, PI_8);
            //hingeC.SetLimit(-0.1f, 0.1f);

            return hinge;
        }

        private static HingeConstraint CreateKneeJoint(RigidBody root, RigidBody thigh, RigidBody shin, float direction)
        {
            Vector3 origin = ToCartesian(direction, BodyRadius + ThighLength);
            Matrix localFrame = Matrix.RotationYawPitchRoll(-direction, 0, 0) * Matrix.Translation(origin);

            Matrix thighFrame = localFrame * root.WorldTransform * Matrix.Invert(thigh.WorldTransform);
            Matrix shinFrame = localFrame * root.WorldTransform * Matrix.Invert(shin.WorldTransform);

            var hinge = new HingeConstraint(thigh, shin, thighFrame, shinFrame);
            //hingeC.SetLimit(-0.01f, 0.01f);
            hinge.SetLimit(-PI_8, 0.2f);

            return hinge;
        }

        private static void SetDamping(RigidBody body)
        {
            body.SetDamping(0.05f, 0.85f);
            body.DeactivationTime = 0.8f;
            //body.SetSleepingThresholds(1.6f, 2.5f);
            body.SetSleepingThresholds(0.5f, 0.5f);
        }

        public void Dispose()
        {
            int i;

            // Remove all constraints
            for (i = 0; i < JointCount; ++i)
            {
                _ownerWorld.RemoveConstraint(Joints[i]);
                Joints[i].Dispose();
                Joints[i] = null;
            }

            // Remove all bodies and shapes
            for (i = 0; i < JointCount; ++i)
            {
                _ownerWorld.RemoveRigidBody(_jointBodies[i]);
                _jointBodies[i].MotionState.Dispose();
                _jointBodies[i].Dispose();
            }
            _jointBodies = null;

            _thighShape.Dispose();
            _thighShape = null;
            _shinShape.Dispose();
            _shinShape = null;
        }

        private RigidBody LocalCreateRigidBody(float mass, Matrix startTransform, CollisionShape shape)
        {
            //rigidbody is dynamic if and only if mass is non zero, otherwise static
            Vector3 localInertia;
            if (mass != 0.0f)
            {
                shape.CalculateLocalInertia(mass, out localInertia);
            }
            else
            {
                localInertia = Vector3.Zero;
            }

            //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
            DefaultMotionState myMotionState = new DefaultMotionState(startTransform);
            RigidBody body;
            using (var rbInfo = new RigidBodyConstructionInfo(mass, myMotionState, shape, localInertia))
            {
                body = new RigidBody(rbInfo);
            }

            _ownerWorld.AddRigidBody(body);

            return body;
        }

        private static Vector3 ToCartesian(float angle, float radius)
        {
            return new Vector3(
                (float)Math.Cos(angle) * radius,
                0,
                (float)Math.Sin(angle) * radius);
        }
    };
}
