using BulletSharp;
using DemoFramework;
using System;
using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;

namespace ConstraintDemo
{
    class Physics
    {
        public float CubeHalfExtents = 1.0f;
        bool P2P = false;
        Vector3 lowerSliderLimit = new Vector3(-10, 0, 0);
        Vector3 hiSliderLimit = new Vector3(10, 0, 0);

        CollisionDispatcher dispatcher;
        BroadphaseInterface broadphase;
        ConstraintSolver solver;
        CollisionShapeArray collisionShapes = new CollisionShapeArray();

        public DynamicsWorld world;
        public RigidBody d6body0;
        Generic6DofConstraint spSlider6Dof;
        HingeConstraint spDoorHinge;
        HingeConstraint spHingeDynAB;
        ConeTwistConstraint coneTwist;

        void SetupEmptyDynamicsWorld()
        {
            CollisionConfiguration collisionConf;
            collisionConf = new DefaultCollisionConfiguration();
            dispatcher = new CollisionDispatcher(collisionConf);
            broadphase = new DbvtBroadphase();
            solver = new SequentialImpulseConstraintSolver();
            world = new DiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConf);
            world.Gravity = new Vector3(0, -10, 0);
        }

        public Physics()
        {
            SetupEmptyDynamicsWorld();

            CollisionShape groundShape = new BoxShape(50, 40, 50);
            //CollisionShape groundShape = new StaticPlaneShape(Vector3.UnitY, 40);
            collisionShapes.PushBack(groundShape);
            LocalCreateRigidBody(0, Matrix.Translation(0, -56, 0), groundShape);

            CollisionShape shape = new BoxShape(new Vector3(CubeHalfExtents));
            collisionShapes.PushBack(shape);


            float mass = 1.0f;

            RigidBody body0 = LocalCreateRigidBody( mass, Matrix.Translation(0,20,0),shape);

	        RigidBody body1 = null;//LocalCreateRigidBody(mass, Matrix.Translation(2*CUBE_HALF_EXTENTS,20,0), shape);
        	//RigidBody body1 = LocalCreateRigidBody(0, Matrix.Translation(2*CUBE_HALF_EXTENTS,20,0), null);
	        //body1.ActivationState = ActivationState.DisableDeactivation;
	        //body1.SetDamping(0.3f, 0.3f);

	        Vector3 pivotInA = new Vector3(CubeHalfExtents,-CubeHalfExtents,-CubeHalfExtents);
	        Vector3 axisInA = new Vector3(0,0,1);

            Vector3 pivotInB;
            if (body1 != null)
            {
                Matrix transform = Matrix.Invert(body1.CenterOfMassTransform) * body0.CenterOfMassTransform;
                pivotInB = Vector3.TransformCoordinate(pivotInA, transform);
            }
            else
            {
                pivotInB = pivotInA;
            }

            Vector3 axisInB;
            if (body1 != null)
            {
                Matrix transform = Matrix.Invert(body1.CenterOfMassTransform) * body1.CenterOfMassTransform;
                axisInB = Vector3.TransformCoordinate(axisInA, transform);
            }
            else
            {
                axisInB = Vector3.TransformCoordinate(axisInA, body0.CenterOfMassTransform);
            }

            if (P2P)
            {
                TypedConstraint p2p = new Point2PointConstraint(body0, pivotInA);
                //TypedConstraint p2p = new Point2PointConstraint(body0,body1,pivotInA,pivotInB);
                //TypedConstraint hinge = new HingeConstraint(body0,body1,pivotInA,pivotInB,axisInA,axisInB);
                world.AddConstraint(p2p);
                p2p.DebugDrawSize = 5;
            }
            else
            {
                HingeConstraint hinge = new HingeConstraint(body0, pivotInA, axisInA);
                
                //use zero targetVelocity and a small maxMotorImpulse to simulate joint friction
                //float	targetVelocity = 0.f;
                //float	maxMotorImpulse = 0.01;
                float targetVelocity = 1.0f;
                float maxMotorImpulse = 1.0f;
                hinge.EnableAngularMotor(true, targetVelocity, maxMotorImpulse);
                world.AddConstraint(hinge);
                hinge.DebugDrawSize = 5;
            }



            //create a slider, using the generic D6 constraint
	        Vector3 sliderWorldPos = new Vector3(0,10,0);
	        Vector3 sliderAxis= Vector3.UnitX;
	        float angle=0;//SIMD_RADS_PER_DEG * 10.f;
            Matrix trans = Matrix.RotationAxis(sliderAxis, angle) * Matrix.Translation(sliderWorldPos);
            d6body0 = LocalCreateRigidBody(mass, trans, shape);
            d6body0.ActivationState = ActivationState.DisableDeactivation;
	        
	        RigidBody fixedBody1 = LocalCreateRigidBody(0, trans, null);
	        world.AddRigidBody(fixedBody1);

	        Matrix frameInA = Matrix.Translation(0, 5, 0);
	        Matrix frameInB = Matrix.Translation(0, 5, 0);

            //bool useLinearReferenceFrameA = false;//use fixed frame B for linear llimits
	        bool useLinearReferenceFrameA = true;//use fixed frame A for linear llimits
	        spSlider6Dof = new Generic6DofConstraint(fixedBody1, d6body0, frameInA, frameInB, useLinearReferenceFrameA);
	        spSlider6Dof.SetLinearLowerLimit(lowerSliderLimit);
	        spSlider6Dof.SetLinearUpperLimit(hiSliderLimit);

	        //range should be small, otherwise singularities will 'explode' the constraint
            //spSlider6Dof.SetAngularLowerLimit(new Vector3(-1.5f,0,0));
            //spSlider6Dof.SetAngularUpperLimit(new Vector3(1.5f,0,0));
            //spSlider6Dof.SetAngularLowerLimit(new Vector3(0,0,0));
            //spSlider6Dof.SetAngularUpperLimit(new Vector3(0,0,0));
	        spSlider6Dof.SetAngularLowerLimit(new Vector3((float)-Math.PI,0,0));
	        spSlider6Dof.SetAngularUpperLimit(new Vector3(1.5f,0,0));

	        spSlider6Dof.TranslationalLimitMotor.set_EnableMotor(0, true);
	        spSlider6Dof.TranslationalLimitMotor.TargetVelocity = new Vector3(-5.0f, 0, 0);
	        spSlider6Dof.TranslationalLimitMotor.MaxMotorForce = new Vector3(0.1f, 0, 0);

	        world.AddConstraint(spSlider6Dof);
            spSlider6Dof.DebugDrawSize = 5;



            // create a door using hinge constraint attached to the world

            CollisionShape pDoorShape = new BoxShape(2.0f, 5.0f, 0.2f);
            collisionShapes.PushBack(pDoorShape);
            RigidBody pDoorBody = LocalCreateRigidBody(1.0f, Matrix.Translation(-5.0f, -2.0f, 0.0f), pDoorShape);
            pDoorBody.ActivationState = ActivationState.DisableDeactivation;
            Vector3 btPivotA = new Vector3(10.0f +  2.1f, -2.0f, 0.0f ); // right next to the door slightly outside
            Vector3 btAxisA = Vector3.UnitY; // pointing upwards, aka Y-axis

            spDoorHinge = new HingeConstraint(pDoorBody, btPivotA, btAxisA);

            //spDoorHinge.SetLimit(0.0f, (float)Math.PI / 2);
            // test problem values
            //spDoorHinge.SetLimit(-(float)Math.PI, (float)Math.PI * 0.8f);

            //spDoorHinge.SetLimit(1, -1);
            //spDoorHinge.SetLimit(-(float)Math.PI * 0.8f, (float)Math.PI);
            //spDoorHinge.SetLimit(-(float)Math.PI * 0.8f, (float)Math.PI, 0.9f, 0.3f, 0.0f);
            //spDoorHinge.SetLimit(-(float)Math.PI * 0.8f, (float)Math.PI, 0.9f, 0.01f, 0.0f); // "sticky limits"
            spDoorHinge.SetLimit(-(float)Math.PI * 0.25f, (float)Math.PI * 0.25f);
            //spDoorHinge.SetLimit(0, 0);
            world.AddConstraint(spDoorHinge);
            spDoorHinge.DebugDrawSize = 5;

            RigidBody pDropBody = LocalCreateRigidBody(10.0f, Matrix.Translation(-5.0f, 2.0f, 0.0f), shape);
            


            // create a generic 6DOF constraint

            //RigidBody pBodyA = LocalCreateRigidBody(mass, Matrix.Translation(10.0f, 6.0f, 0), shape);
            RigidBody pBodyA = LocalCreateRigidBody(0, Matrix.Translation(10, 6, 0), shape);
            //RigidBody pBodyA = LocalCreateRigidBody(0, Matrix.Translation(10, 6, 0), null);
            pBodyA.ActivationState = ActivationState.DisableDeactivation;

            RigidBody pBodyB = LocalCreateRigidBody(mass, Matrix.Translation(0, 6, 0), shape);
            //RigidBody pBodyB = LocalCreateRigidBody(0, Matrix.Translation(0, 6, 0), shape);
            pBodyB.ActivationState = ActivationState.DisableDeactivation;

            frameInA = Matrix.Translation(-5, 0, 0);
            frameInB = Matrix.Translation(5, 0, 0);

            Generic6DofConstraint pGen6DOF = new Generic6DofConstraint(pBodyA, pBodyB, frameInA, frameInB, true);
            //Generic6DofConstraint pGen6DOF = new Generic6DofConstraint(pBodyA, pBodyB, frameInA, frameInB, false);
            pGen6DOF.SetLinearLowerLimit(new Vector3(-10, -2, -1));
            pGen6DOF.SetLinearUpperLimit(new Vector3(10, 2, 1));
            //pGen6DOF.SetLinearLowerLimit(new Vector3(-10, 0, 0));
            //pGen6DOF.SetLinearUpperLimit(new Vector3(10, 0, 0));
            //pGen6DOF.SetLinearLowerLimit(new Vector3(0, 0, 0));
            //pGen6DOF.SetLinearUpperLimit(new Vector3(0, 0, 0));

            //pGen6DOF.TranslationalLimitMotor.set_EnableMotor(0, true);
            //pGen6DOF.TranslationalLimitMotor.TargetVelocity = new Vector3(5, 0, 0);
            //pGen6DOF.TranslationalLimitMotor.MaxMotorForce = new Vector3(0.1f, 0, 0);

            //pGen6DOF.SetAngularLowerLimit(new Vector3(0, (float)Math.PI * 0.9f, 0));
            //pGen6DOF.SetAngularUpperLimit(new Vector3(0, -(float)Math.PI * 0.9f, 0));
            //pGen6DOF.SetAngularLowerLimit(new Vector3(0, 0, -(float)Math.PI));
            //pGen6DOF.SetAngularUpperLimit(new Vector3(0, 0, (float)Math.PI));

            pGen6DOF.SetAngularLowerLimit(new Vector3(-(float)Math.PI / 4, -0.75f, -(float)Math.PI * 0.4f));
            pGen6DOF.SetAngularUpperLimit(new Vector3((float)Math.PI / 4, 0.75f, (float)Math.PI * 0.4f));
            //pGen6DOF.SetAngularLowerLimit(new Vector3(0, -0.75f, (float)Math.PI * 0.8f));
            //pGen6DOF.SetAngularUpperLimit(new Vector3(0, 0.75f, -(float)Math.PI * 0.8f));
            //pGen6DOF.SetAngularLowerLimit(new Vector3(0, -(float)Math.PI * 0.8f, (float)Math.PI * 1.98f));
            //pGen6DOF.SetAngularUpperLimit(new Vector3(0, (float)Math.PI * 0.8f, -(float)Math.PI * 1.98f));

            //pGen6DOF.SetAngularLowerLimit(new Vector3(-0.75f, -0.5f, -0.5f));
            //pGen6DOF.SetAngularUpperLimit(new Vector3(0.75f, 0.5f, 0.5f));
            //pGen6DOF.SetAngularLowerLimit(new Vector3(-0.75f, 0, 0));
            //pGen6DOF.SetAngularUpperLimit(new Vector3(0.75f, 0, 0));
            //pGen6DOF.SetAngularLowerLimit(new Vector3(0, -0.7f, 0));
            //pGen6DOF.SetAngularUpperLimit(new Vector3(0, 0.7f, 0));
            //pGen6DOF.SetAngularLowerLimit(new Vector3(-1, 0, 0));
            //pGen6DOF.SetAngularUpperLimit(new Vector3(1, 0, 0));



            // create a ConeTwist constraint

            pBodyA = LocalCreateRigidBody(1.0f, Matrix.Translation(-10, 5, 0), shape);
            //pBodyA = LocalCreateRigidBody(0, Matrix.Translation(-10, 5, 0), shape);
            pBodyA.ActivationState = ActivationState.DisableDeactivation;

            pBodyB = LocalCreateRigidBody(0, Matrix.Translation(-10, -5, 0), shape);
            //pBodyB = LocalCreateRigidBody(1.0f, Matrix.Translation(-10, -5, 0), shape);

            frameInA = Matrix.RotationYawPitchRoll(0, 0, (float)Math.PI / 2);
            frameInA *= Matrix.Translation(0, -5, 0);
            frameInB = Matrix.RotationYawPitchRoll(0, 0, (float)Math.PI / 2);
            frameInA *= Matrix.Translation(0, 5, 0);

            coneTwist = new ConeTwistConstraint(pBodyA, pBodyB, frameInA, frameInB);
            //coneTwist.SetLimit((float)Math.PI / 4, (float)Math.PI / 4, (float)Math.PI * 0.8f);
            //coneTwist.SetLimit((((float)Math.PI / 4) * 0.6f), (float)Math.PI / 4, (float)Math.PI * 0.8f, 1.0f); // soft limit == hard limit
            coneTwist.SetLimit((((float)Math.PI / 4) * 0.6f), (float)Math.PI / 4, (float)Math.PI * 0.8f, 0.5f);
            world.AddConstraint(coneTwist, true);
            coneTwist.DebugDrawSize = 5;



            // Hinge connected to the world, with motor (to hinge motor with new and old constraint solver)

            RigidBody pBody = LocalCreateRigidBody(1.0f, Matrix.Identity, shape);
            pBody.ActivationState = ActivationState.DisableDeactivation;
            Vector3 PivotA = new Vector3(10.0f, 0.0f, 0.0f);
            btAxisA = new Vector3(0.0f, 0.0f, 1.0f);

            HingeConstraint pHinge = new HingeConstraint(pBody, btPivotA, btAxisA );
            //pHinge.EnableAngularMotor(true, -1.0f, 0.165f); // use for the old solver
            pHinge.EnableAngularMotor(true, -1.0f, 1.65f); // use for the new SIMD solver
            world.AddConstraint(pHinge);
            pHinge.DebugDrawSize = 5;



            // create a universal joint using generic 6DOF constraint
            // create two rigid bodies
            // static bodyA (parent) on top:
            pBodyA = LocalCreateRigidBody(0, Matrix.Translation(20, 4, 0), shape);
            pBodyA.ActivationState = ActivationState.DisableDeactivation;
            // dynamic bodyB (child) below it :
            pBodyB = LocalCreateRigidBody(1.0f, Matrix.Translation(20, 0, 0), shape);
            pBodyB.ActivationState = ActivationState.DisableDeactivation;
            // add some (arbitrary) data to build constraint frames
            Vector3 parentAxis = new Vector3(1, 0, 0); 
            Vector3 childAxis = new Vector3(0, 0, 1); 
            Vector3 anchor = new Vector3(20, 2, 0);

            UniversalConstraint pUniv = new UniversalConstraint(pBodyA, pBodyB, anchor, parentAxis, childAxis);
            pUniv.SetLowerLimit(-(float)Math.PI /4, -(float)Math.PI / 4);
            pUniv.SetUpperLimit((float)Math.PI / 4, (float)Math.PI / 4);
            // add constraint to world
            world.AddConstraint(pUniv, true);
            // draw constraint frames and limits for debugging
            pUniv.DebugDrawSize = 5;

            world.AddConstraint(pGen6DOF, true);
            pGen6DOF.DebugDrawSize = 5;

            

            // create a generic 6DOF constraint with springs 

            pBodyA = LocalCreateRigidBody(0, Matrix.Translation(-20, 16, 0), shape);
            pBodyA.ActivationState = ActivationState.DisableDeactivation;

            pBodyB = LocalCreateRigidBody(1.0f, Matrix.Translation(-10, 16, 0), shape);
            pBodyB.ActivationState = ActivationState.DisableDeactivation;

            frameInA = Matrix.Translation(10, 0, 0);
            frameInB = Matrix.Identity;

            Generic6DofSpringConstraint pGen6DOFSpring = new Generic6DofSpringConstraint(pBodyA, pBodyB, frameInA, frameInB, true);
            pGen6DOFSpring.SetLinearUpperLimit(new Vector3(5, 0, 0));
            pGen6DOFSpring.SetLinearLowerLimit(new Vector3(-5, 0, 0));

            pGen6DOFSpring.SetAngularLowerLimit(new Vector3(0, 0, -1.5f));
            pGen6DOFSpring.SetAngularUpperLimit(new Vector3(0, 0, 1.5f));

            world.AddConstraint(pGen6DOFSpring, true);
            pGen6DOFSpring.DebugDrawSize = 5;

            pGen6DOFSpring.EnableSpring(0, true);
            pGen6DOFSpring.SetStiffness(0, 39.478f);
            pGen6DOFSpring.SetDamping(0, 0.5f);
            pGen6DOFSpring.EnableSpring(5, true);
            pGen6DOFSpring.SetStiffness(5, 39.478f);
            pGen6DOFSpring.SetDamping(0, 0.3f);
            pGen6DOFSpring.SetEquilibriumPoint();



            // create a Hinge2 joint
            // create two rigid bodies
            // static bodyA (parent) on top:
            pBodyA = LocalCreateRigidBody(0, Matrix.Translation(-20, 4, 0), shape);
            pBodyA.ActivationState = ActivationState.DisableDeactivation;
            // dynamic bodyB (child) below it :
            pBodyB = LocalCreateRigidBody(1.0f, Matrix.Translation(-20, 0, 0), shape);
            pBodyB.ActivationState = ActivationState.DisableDeactivation;
            // add some data to build constraint frames
            parentAxis = new Vector3(0, 1, 0); 
            childAxis = new Vector3(1, 0, 0); 
            anchor = new Vector3(-20, 0, 0);
            Hinge2Constraint pHinge2 = new Hinge2Constraint(pBodyA, pBodyB, anchor, parentAxis, childAxis);
            pHinge2.SetLowerLimit(-(float)Math.PI / 4);
            pHinge2.SetUpperLimit((float)Math.PI / 4);
            // add constraint to world
            world.AddConstraint(pHinge2, true);
            // draw constraint frames and limits for debugging
            pHinge2.DebugDrawSize = 5;



            // create a Hinge joint between two dynamic bodies
            // create two rigid bodies
            // static bodyA (parent) on top:
            pBodyA = LocalCreateRigidBody(1.0f, Matrix.Translation(-20, -2, 0), shape);
            pBodyA.ActivationState = ActivationState.DisableDeactivation;
            // dynamic bodyB:
            pBodyB = LocalCreateRigidBody(10.0f, Matrix.Translation(-30, -2, 0), shape);
            pBodyB.ActivationState = ActivationState.DisableDeactivation;
            // add some data to build constraint frames
            Vector3 axisA = new Vector3(0, 1, 0); 
            Vector3 axisB = new Vector3(0, 1, 0); 
            Vector3 pivotA = new Vector3(-5, 0, 0);
            Vector3 pivotB = new Vector3( 5, 0, 0);
            spHingeDynAB = new HingeConstraint(pBodyA, pBodyB, pivotA, pivotB, axisA, axisB);
            spHingeDynAB.SetLimit(-(float)Math.PI / 4, (float)Math.PI / 4);
            // add constraint to world
            world.AddConstraint(spHingeDynAB, true);
            // draw constraint frames and limits for debugging
            spHingeDynAB.DebugDrawSize = 5;



            world.Broadphase.ResetPool(dispatcher);
            solver.Reset();
        }

        public void Update(float elapsedTime)
        {
            world.StepSimulation(elapsedTime);
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

            world.AddRigidBody(body);

            return body;
        }
    }
}
