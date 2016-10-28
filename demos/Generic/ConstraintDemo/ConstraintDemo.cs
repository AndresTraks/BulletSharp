using BulletSharp;
using DemoFramework;
using System;

namespace ConstraintDemo
{
    class ConstraintDemo : Demo
    {
        Vector3 eye = new Vector3(35, 10, 35);
        Vector3 target = new Vector3(0, 5, 0);

        const DebugDrawModes debugMode = DebugDrawModes.DrawConstraints | DebugDrawModes.DrawConstraintLimits;

        private const float CubeHalfExtent = 1.0f;
        BoxShape cubeShape;

        protected override void OnInitialize()
        {
            Freelook.SetEyeTarget(eye, target);

            Graphics.SetFormText("BulletSharp - Constraints Demo");

            IsDebugDrawEnabled = true;
            DebugDrawMode = debugMode;
        }

        protected override void OnInitializePhysics()
        {
            SetupDynamicsWorld();

            CreateGround();

            cubeShape = new BoxShape(CubeHalfExtent);
            CollisionShapes.Add(cubeShape);

            CreateGears();
            CreateHingedBoxes();
            CreateMotorHinge();
            CreateMotorHinge2();
            CreateSlider();
            CreateD6Slider();
            CreateDoor();
            CreateGeneric6DofConstraint();
            CreateConeTwist();
            CreateUniversalConstraint();
            CreateGeneric6DofSpringConstraint();
            CreateHinge();
            CreateHinge2();
        }

        void SetupDynamicsWorld()
        {
            CollisionConf = new DefaultCollisionConfiguration();
            Dispatcher = new CollisionDispatcher(CollisionConf);
            Broadphase = new DbvtBroadphase();
            Solver = new SequentialImpulseConstraintSolver();
            World = new DiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConf);
            World.Gravity = new Vector3(0, -10, 0);
        }

        private void CreateGround()
        {
            var groundShape = new BoxShape(50, 1, 50);
            //var groundShape = new StaticPlaneShape(Vector3.UnitY, 1);
            CollisionShapes.Add(groundShape);
            RigidBody body = LocalCreateRigidBody(0, Matrix.Translation(0, -16, 0), groundShape);
            body.UserObject = "Ground";
        }

        private void CreateGears()
        {
            const float theta = (float)Math.PI / 4.0f;
            float radiusA = 2 - (float)Math.Tan(theta);
            float radiusB = 1 / (float)Math.Cos(theta);
            float ratio = radiusB / radiusA;

            Matrix transform = Matrix.Translation(-8, 1, -8);
            RigidBody gearA = CreateGear(radiusA, transform);
            gearA.AngularFactor = new Vector3(0, 1, 0);

            var orientation = Quaternion.RotationAxis(new Vector3(0, 0, 1), -theta);
            transform = Matrix.RotationQuaternion(orientation) * Matrix.Translation(-10, 2, -8);
            RigidBody gearB = CreateGear(radiusB, transform);
            gearB.AngularVelocity = new Vector3(0, 3, 0);

            var hinge = new HingeConstraint(gearB, Vector3.Zero, new Vector3(0, 1, 0), true);
            World.AddConstraint(hinge);

            var axisA = new Vector3(0, 1, 0);
            var axisB = new Vector3(0, 1, 0);
            orientation = Quaternion.RotationAxis(new Vector3(0, 0, 1), -theta);
            Matrix mat = Matrix.RotationQuaternion(orientation);
            axisB = new Vector3(mat.M21, mat.M22, mat.M23);

            var gear = new GearConstraint(gearA, gearB, axisA, axisB, ratio);
            World.AddConstraint(gear, true);
        }

        private RigidBody CreateGear(float radius, Matrix transform)
        {
            const float mass = 6.28f;

            var shape = new CompoundShape();
            var axle = new CylinderShape(0.2f, 0.25f, 0.2f);
            var wheel = new CylinderShape(radius, 0.025f, radius);
            shape.AddChildShape(Matrix.Identity, axle);
            shape.AddChildShape(Matrix.Identity, wheel);
            CollisionShapes.Add(shape);
            CollisionShapes.Add(axle);
            CollisionShapes.Add(wheel);

            RigidBody body = LocalCreateRigidBody(mass, transform, shape);
            body.LinearFactor = Vector3.Zero;
            return body;
        }

        private void CreateHingedBoxes()
        {
            const float mass = 1.0f;

            RigidBody body0 = LocalCreateRigidBody(mass, Matrix.Translation(0, 24, 0), cubeShape);
            RigidBody body1 = LocalCreateRigidBody(mass, Matrix.Translation(2 * CubeHalfExtent, 24, 0), cubeShape);

            Vector3 pivotInA = new Vector3(CubeHalfExtent, -CubeHalfExtent, -CubeHalfExtent);
            Vector3 axisInA = new Vector3(0, 0, 1);

            Matrix transform = Matrix.Invert(body1.CenterOfMassTransform) * body0.CenterOfMassTransform;
            Vector3 pivotInB = Vector3.TransformCoordinate(pivotInA, transform);

            transform = Matrix.Invert(body1.CenterOfMassTransform) * body1.CenterOfMassTransform;
            Vector3 axisInB = Vector3.TransformCoordinate(axisInA, transform);

            //var pointToPoint = new Point2PointConstraint(body0, body1, pivotInA, pivotInB);
            //pointToPoint.DebugDrawSize = 5;
            //World.AddConstraint(pointToPoint);

            var hinge = new HingeConstraint(body0, body1, pivotInA, pivotInB, axisInA, axisInB);
            World.AddConstraint(hinge);
        }

        // Hinge connected to the world, with motor
        private void CreateMotorHinge()
        {
            const float mass = 1.0f;
            RigidBody body = LocalCreateRigidBody(mass, Matrix.Translation(0, 20, 0), cubeShape);

            Vector3 pivotInA = new Vector3(CubeHalfExtent, -CubeHalfExtent, -CubeHalfExtent);
            Vector3 axisInA = new Vector3(0, 0, 1);

            var hinge = new HingeConstraint(body, pivotInA, axisInA);

            //use zero targetVelocity and a small maxMotorImpulse to simulate joint friction
            //const float targetVelocity = 0;
            //const float maxMotorImpulse = 0.01f;
            const float targetVelocity = 1.0f;
            const float maxMotorImpulse = 1.0f;
            hinge.EnableAngularMotor(true, targetVelocity, maxMotorImpulse);
            hinge.DebugDrawSize = 5;
            World.AddConstraint(hinge);
        }

        private void CreateMotorHinge2()
        {
            RigidBody body = LocalCreateRigidBody(1.0f, Matrix.Identity, cubeShape);
            body.ActivationState = ActivationState.DisableDeactivation;

            Vector3 pivotInA = new Vector3(10.0f, 0.0f, 0.0f);
            Vector3 axisInA = new Vector3(0, 0, 1);

            var hinge = new HingeConstraint(body, pivotInA, axisInA);
            const float targetVelocity = -1.0f;
            const float maxMotorImpulse = 1.65f;
            hinge.EnableAngularMotor(true, targetVelocity, maxMotorImpulse);
            hinge.DebugDrawSize = 5;
            World.AddConstraint(hinge);
        }

        private void CreateSlider()
        {
            float mass = 1.0f;

            RigidBody bodyA = LocalCreateRigidBody(mass, Matrix.Translation(-20, 0, 15), cubeShape);
            bodyA.ActivationState = ActivationState.DisableDeactivation;

            // add dynamic rigid body B1
            RigidBody bodyB = LocalCreateRigidBody(0, Matrix.Translation(-30, 0, 15), cubeShape);
            //RigidBody bodyB = LocalCreateRigidBody(mass, Matrix.Translation(-20, 0, 15), cubeShape);
            bodyB.ActivationState = ActivationState.DisableDeactivation;

            // create slider constraint between A1 and B1 and add it to world
            var slider = new SliderConstraint(bodyA, bodyB, Matrix.Identity, Matrix.Identity, true)
            {
                LowerLinearLimit = -15.0f,
                UpperLinearLimit = -5.0f,
                //LowerLinearLimit = -10.0f,
                //UpperLinearLimit = -10.0f,
                LowerAngularLimit = -(float)Math.PI / 3.0f,
                UpperAngularLimit = (float)Math.PI / 3.0f,
                DebugDrawSize = 5.0f
            };
            World.AddConstraint(slider, true);
        }

        // Create a slider using the generic D6 constraint
        private void CreateD6Slider()
        {
            const float mass = 1.0f;

            Vector3 sliderAxis = Vector3.UnitX;
            const float angle = (float)Math.PI / 4;
            Matrix trans = Matrix.RotationAxis(sliderAxis, angle) * Matrix.Translation(0, 10, 0);
            RigidBody body = LocalCreateRigidBody(mass, trans, cubeShape);
            body.ActivationState = ActivationState.DisableDeactivation;

            RigidBody fixedBody = LocalCreateRigidBody(0, trans, null);
            World.AddRigidBody(fixedBody);

            Matrix frameInA = Matrix.Translation(0, 5, 0);
            Matrix frameInB = Matrix.Translation(0, 5, 0);

            Vector3 lowerSliderLimit = new Vector3(-10, 0, 0);
            Vector3 hiSliderLimit = new Vector3(10, 0, 0);

            //const bool useLinearReferenceFrameA = false; //use fixed frame B for linear llimits
            const bool useLinearReferenceFrameA = true; //use fixed frame A for linear llimits
            var slider = new Generic6DofConstraint(fixedBody, body, frameInA, frameInB, useLinearReferenceFrameA)
            {
                LinearLowerLimit = lowerSliderLimit,
                LinearUpperLimit = hiSliderLimit,

                //range should be small, otherwise singularities will 'explode' the constraint
                //AngularLowerLimit = new Vector3(-1.5f,0,0),
                //AngularUpperLimit = new Vector3(1.5f,0,0),
                //AngularLowerLimit = new Vector3(0,0,0),
                //AngularUpperLimit = new Vector3(0,0,0),
                AngularLowerLimit = new Vector3((float)-Math.PI, 0, 0),
                AngularUpperLimit = new Vector3(1.5f, 0, 0),
                DebugDrawSize = 5
            };

            //slider.TranslationalLimitMotor.EnableMotor[0] = true;
            slider.TranslationalLimitMotor.TargetVelocity = new Vector3(-5.0f, 0, 0);
            slider.TranslationalLimitMotor.MaxMotorForce = new Vector3(0.1f, 0, 0);

            World.AddConstraint(slider);
        }

        // Create a door using a hinge constraint attached to the world
        private void CreateDoor()
        {
            const float mass = 1.0f;

            var doorShape = new BoxShape(2.0f, 5.0f, 0.2f);
            CollisionShapes.Add(doorShape);
            RigidBody doorBody = LocalCreateRigidBody(mass, Matrix.Translation(-5.0f, -2.0f, 0.0f), doorShape);
            doorBody.ActivationState = ActivationState.DisableDeactivation;

            var pivotA = new Vector3(10.0f + 2.1f, -2.0f, 0.0f); // right next to the door slightly outside
            var axisA = Vector3.UnitY; // pointing upwards, aka Y-axis

            var hinge = new HingeConstraint(doorBody, pivotA, axisA);
            hinge.DebugDrawSize = 5;

            //hinge.SetLimit(0.0f, (float)Math.PI / 2);
            // test problem values
            //hinge.SetLimit(-(float)Math.PI, (float)Math.PI * 0.8f);
            //hinge.SetLimit(1, -1);
            //hinge.SetLimit(-(float)Math.PI * 0.8f, (float)Math.PI);
            //hinge.SetLimit(-(float)Math.PI * 0.8f, (float)Math.PI, 0.9f, 0.3f, 0.0f);
            //hinge.SetLimit(-(float)Math.PI * 0.8f, (float)Math.PI, 0.9f, 0.01f, 0.0f); // "sticky limits"
            hinge.SetLimit(-(float)Math.PI * 0.25f, (float)Math.PI * 0.25f);
            //hinge.SetLimit(0, 0);
            World.AddConstraint(hinge);
        }

        private void CreateGeneric6DofConstraint()
        {
            const float mass = 1.0f;

            RigidBody fixedBody = LocalCreateRigidBody(0, Matrix.Translation(10, 6, 0), cubeShape);
            fixedBody.ActivationState = ActivationState.DisableDeactivation;

            RigidBody dynamicbody = LocalCreateRigidBody(mass, Matrix.Translation(0, 6, 0), cubeShape);
            dynamicbody.ActivationState = ActivationState.DisableDeactivation;

            Matrix frameInA = Matrix.Translation(-5, 0, 0);
            Matrix frameInB = Matrix.Translation(5, 0, 0);

            bool useLinearReferenceFrameA = true;
            var generic6Dof = new Generic6DofConstraint(fixedBody, dynamicbody, frameInA, frameInB, useLinearReferenceFrameA)
            {
                LinearLowerLimit = new Vector3(-10, -2, -1),
                LinearUpperLimit = new Vector3(10, 2, 1),
                //LinearLowerLimit = new Vector3(-10, 0, 0),
                //LinearUpperLimit = new Vector3(10, 0, 0),
                //LinearLowerLimit = new Vector3(0, 0, 0),
                //LinearUpperLimit = new Vector3(0, 0, 0),

                AngularLowerLimit = new Vector3(-(float)Math.PI / 4, -0.75f, -(float)Math.PI * 0.4f),
                AngularUpperLimit = new Vector3((float)Math.PI / 4, 0.75f, (float)Math.PI * 0.4f),
                //AngularLowerLimit = new Vector3(0, (float)Math.PI * 0.9f, 0),
                //AngularUpperLimit = new Vector3(0, -(float)Math.PI * 0.9f, 0),
                //AngularLowerLimit = new Vector3(0, 0, -(float)Math.PI),
                //AngularUpperLimit = new Vector3(0, 0, (float)Math.PI),

                //AngularLowerLimit = new Vector3(0, -0.75f, (float)Math.PI * 0.8f),
                //AngularUpperLimit = new Vector3(0, 0.75f, -(float)Math.PI * 0.8f),
                //AngularLowerLimit = new Vector3(0, -(float)Math.PI * 0.8f, (float)Math.PI * 1.98f),
                //AngularUpperLimit = new Vector3(0, (float)Math.PI * 0.8f, -(float)Math.PI * 1.98f),

                //AngularLowerLimit = new Vector3(-0.75f, -0.5f, -0.5f),
                //AngularUpperLimit = new Vector3(0.75f, 0.5f, 0.5f),
                //AngularLowerLimit = new Vector3(-1, 0, 0),
                //AngularUpperLimit = new Vector3(1, 0, 0),

                DebugDrawSize = 5.0f
            };

            //generic6Dof.TranslationalLimitMotor.EnableMotor[0] = true;
            //generic6Dof.TranslationalLimitMotor.TargetVelocity = new Vector3(5, 0, 0);
            //generic6Dof.TranslationalLimitMotor.MaxMotorForce = new Vector3(0.1f, 0, 0);

            World.AddConstraint(generic6Dof, true);
        }

        private void CreateConeTwist()
        {
            RigidBody bodyA = LocalCreateRigidBody(1.0f, Matrix.Translation(-10, 5, 0), cubeShape);
            //bodyA = LocalCreateRigidBody(0, Matrix.Translation(-10, 5, 0), cubeShape);
            bodyA.ActivationState = ActivationState.DisableDeactivation;

            RigidBody bodyB = LocalCreateRigidBody(0, Matrix.Translation(-10, -5, 0), cubeShape);
            //bodyB = LocalCreateRigidBody(1.0f, Matrix.Translation(-10, -5, 0), cubeShape);

            Matrix frameInA = Matrix.RotationYawPitchRoll(0, 0, (float)Math.PI / 2);
            frameInA *= Matrix.Translation(0, -5, 0);
            Matrix frameInB = Matrix.RotationYawPitchRoll(0, 0, (float)Math.PI / 2);
            frameInB *= Matrix.Translation(0, 5, 0);

            var coneTwist = new ConeTwistConstraint(bodyA, bodyB, frameInA, frameInB);
            //coneTwist.SetLimit((float)Math.PI / 4, (float)Math.PI / 4, (float)Math.PI * 0.8f);
            //coneTwist.SetLimit((((float)Math.PI / 4) * 0.6f), (float)Math.PI / 4, (float)Math.PI * 0.8f, 1.0f); // soft limit == hard limit
            coneTwist.SetLimit((((float)Math.PI / 4) * 0.6f), (float)Math.PI / 4, (float)Math.PI * 0.8f, 0.5f);
            coneTwist.DebugDrawSize = 5;
            World.AddConstraint(coneTwist, true);
        }

        private void CreateUniversalConstraint()
        {
            // create two rigid bodies
            // static body A (parent) on top:
            RigidBody bodyA = LocalCreateRigidBody(0, Matrix.Translation(20, 4, 0), cubeShape);
            bodyA.ActivationState = ActivationState.DisableDeactivation;
            // dynamic bodyB (child) below it :
            RigidBody bodyB = LocalCreateRigidBody(1.0f, Matrix.Translation(20, 0, 0), cubeShape);
            bodyB.ActivationState = ActivationState.DisableDeactivation;

            // add some (arbitrary) data to build constraint frames
            Vector3 parentAxis = new Vector3(1, 0, 0);
            Vector3 childAxis = new Vector3(0, 0, 1);
            Vector3 anchor = new Vector3(20, 2, 0);

            var universal = new UniversalConstraint(bodyA, bodyB, anchor, parentAxis, childAxis);
            universal.SetLowerLimit(-(float)Math.PI / 4, -(float)Math.PI / 4);
            universal.SetUpperLimit((float)Math.PI / 4, (float)Math.PI / 4);

            // draw constraint frames and limits for debugging
            universal.DebugDrawSize = 5;

            World.AddConstraint(universal, true);
        }

        private void CreateGeneric6DofSpringConstraint()
        {
            RigidBody bodyA = LocalCreateRigidBody(0, Matrix.Translation(-20, 16, 0), cubeShape);
            bodyA.ActivationState = ActivationState.DisableDeactivation;

            RigidBody bodyB = LocalCreateRigidBody(1.0f, Matrix.Translation(-10, 16, 0), cubeShape);
            bodyB.ActivationState = ActivationState.DisableDeactivation;

            Matrix frameInA = Matrix.Translation(10, 0, 0);
            Matrix frameInB = Matrix.Identity;

            var generic6DofSpring = new Generic6DofSpringConstraint(bodyA, bodyB, frameInA, frameInB, true)
            {
                LinearUpperLimit = new Vector3(5, 0, 0),
                LinearLowerLimit = new Vector3(-5, 0, 0),
                AngularLowerLimit = new Vector3(0, 0, -1.5f),
                AngularUpperLimit = new Vector3(0, 0, 1.5f),
                DebugDrawSize = 5
            };

            generic6DofSpring.EnableSpring(0, true);
            generic6DofSpring.SetStiffness(0, 39.478f);
            generic6DofSpring.SetDamping(0, 0.5f);
            generic6DofSpring.EnableSpring(5, true);
            generic6DofSpring.SetStiffness(5, 39.478f);
            generic6DofSpring.SetDamping(0, 0.3f);
            generic6DofSpring.SetEquilibriumPoint();

            World.AddConstraint(generic6DofSpring, true);
        }

        // Create a Hinge joint between two dynamic bodies
        private void CreateHinge()
        {
            // static body (parent) on top
            RigidBody bodyA = LocalCreateRigidBody(1.0f, Matrix.Translation(-20, -2, 0), cubeShape);
            bodyA.ActivationState = ActivationState.DisableDeactivation;
            // dynamic body
            RigidBody bodyB = LocalCreateRigidBody(10.0f, Matrix.Translation(-30, -2, 0), cubeShape);
            bodyB.ActivationState = ActivationState.DisableDeactivation;

            // add some data to build constraint frames
            var axisA = new Vector3(0, 1, 0);
            var axisB = new Vector3(0, 1, 0);
            var pivotA = new Vector3(-5, 0, 0);
            var pivotB = new Vector3(5, 0, 0);
            var hinge = new HingeConstraint(bodyA, bodyB, pivotA, pivotB, axisA, axisB);
            hinge.SetLimit(-(float)Math.PI / 4, (float)Math.PI / 4);

            // draw constraint frames and limits for debugging
            hinge.DebugDrawSize = 5;

            World.AddConstraint(hinge, true);
        }

        private void CreateHinge2()
        {
            // static bodyA (parent) on top
            RigidBody bodyA = LocalCreateRigidBody(0, Matrix.Translation(-20, 4, 0), cubeShape);
            bodyA.ActivationState = ActivationState.DisableDeactivation;
            // dynamic bodyB (child) below it
            RigidBody bodyB = LocalCreateRigidBody(1.0f, Matrix.Translation(-20, 0, 0), cubeShape);
            bodyB.ActivationState = ActivationState.DisableDeactivation;

            // add some data to build constraint frames
            Vector3 parentAxis = new Vector3(0, 1, 0);
            Vector3 childAxis = new Vector3(1, 0, 0);
            Vector3 anchor = new Vector3(-20, 0, 0);
            var hinge2 = new Hinge2Constraint(bodyA, bodyB, anchor, parentAxis, childAxis);

            hinge2.SetLowerLimit(-(float)Math.PI / 4);
            hinge2.SetUpperLimit((float)Math.PI / 4);

            // draw constraint frames and limits for debugging
            hinge2.DebugDrawSize = 5;

            World.AddConstraint(hinge2, true);
        }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (Demo demo = new ConstraintDemo())
            {
                GraphicsLibraryManager.Run(demo);
            }
        }
    }
}
