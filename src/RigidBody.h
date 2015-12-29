#pragma once

#include "CollisionObject.h"

namespace BulletSharp
{
	ref class CollisionShape;
	ref class MotionState;
	ref class TypedConstraint;

	public ref class RigidBodyConstructionInfo
	{
	internal:
		btRigidBody::btRigidBodyConstructionInfo* _native;
		BulletSharp::MotionState^ _motionState;

	private:
		BulletSharp::CollisionShape^ _collisionShape;

		!RigidBodyConstructionInfo();
		~RigidBodyConstructionInfo();

	public:
		RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState, CollisionShape^ collisionShape,
			Vector3 localInertia);
		RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState, CollisionShape^ collisionShape);

		property btScalar AdditionalAngularDampingFactor
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar AdditionalAngularDampingThresholdSqr
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool AdditionalDamping
		{
			bool get();
			void set(bool value);
		}

		property btScalar AdditionalDampingFactor
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar AdditionalLinearDampingThresholdSqr
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar AngularDamping
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar AngularSleepingThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

		property BulletSharp::CollisionShape^ CollisionShape
		{
			BulletSharp::CollisionShape^ get();
			void set(BulletSharp::CollisionShape^ value);
		}

		property btScalar Friction
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar LinearDamping
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar LinearSleepingThreshold
		{
			btScalar get();
			void set(btScalar value);
		}

		property Vector3 LocalInertia
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar Mass
		{
			btScalar get();
			void set(btScalar value);
		}

		property BulletSharp::MotionState^ MotionState
		{
			BulletSharp::MotionState^ get();
			void set(BulletSharp::MotionState^ value);
		}

		property btScalar Restitution
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar RollingFriction
		{
			btScalar get();
			void set(btScalar value);
		}

		property Matrix StartWorldTransform
		{
			Matrix get();
			void set(Matrix value);
		}
	};

	public ref class RigidBody : CollisionObject
	{
	private:
		MotionState^ _motionState;

	public:
		RigidBody(RigidBodyConstructionInfo^ constructionInfo);

#ifndef DISABLE_CONSTRAINTS
		void AddConstraintRef(TypedConstraint^ constraint);
#endif
		void ApplyCentralForce(Vector3 force);
		void ApplyCentralImpulse(Vector3 impulse);
		void ApplyDamping(btScalar timeStep);
		void ApplyForce(Vector3 force, Vector3 relativePosition);
		void ApplyGravity();
		void ApplyImpulse(Vector3 impulse, Vector3 relativePosition);
		void ApplyTorque(Vector3 torque);
		void ApplyTorqueImpulse(Vector3 torque);
		void ClearForces();
		btScalar ComputeAngularImpulseDenominator(Vector3 axis);
		Vector3 ComputeGyroscopicForceExplicit(btScalar maxGyroscopicForce);
		Vector3 ComputeGyroscopicImpulseImplicitBody(btScalar step);
		Vector3 ComputeGyroscopicImpulseImplicitWorld(btScalar deltaTime);
		btScalar ComputeImpulseDenominator(Vector3 pos, Vector3 normal);
		void GetAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
#ifndef DISABLE_CONSTRAINTS
		TypedConstraint^ GetConstraintRef(int index);
#endif
		Vector3 GetVelocityInLocalPoint(Vector3 relativePosition);
		void IntegrateVelocities(btScalar step);
		void PredictIntegratedTransform(btScalar step, [Out] Matrix% predictedTransform);
		void ProceedToTransform(Matrix newTrans);
#ifndef DISABLE_CONSTRAINTS
		void RemoveConstraintRef(TypedConstraint^ c);
#endif
		void SaveKinematicState(btScalar step);
		void SetDamping(btScalar linearDamping, btScalar angularDamping);
		void SetMassProps(btScalar mass, Vector3 inertia);
		void SetSleepingThresholds(btScalar linear, btScalar angular);
		void Translate(Vector3 v);
		static RigidBody^ Upcast(CollisionObject^ colObj);
		void UpdateDeactivation(btScalar timeStep);
		void UpdateInertiaTensor();

		property btScalar AngularDamping
		{
			btScalar get();
		}

		property Vector3 AngularFactor
		{
			Vector3 get();
			void set(Vector3 angFac);
		}

		property btScalar AngularSleepingThreshold
		{
			btScalar get();
		}

		property Vector3 AngularVelocity
		{
			Vector3 get();
			void set(Vector3 angVel);
		}

		property BroadphaseProxy^ BroadphaseProxy
		{
			BulletSharp::BroadphaseProxy^ get();
			void set(BulletSharp::BroadphaseProxy^ value);
		}

		property Vector3 CenterOfMassPosition
		{
			Vector3 get();
		}

		property Matrix CenterOfMassTransform
		{
			Matrix get();
			void set(Matrix xform);
		}

		property int ContactSolverType
		{
			int get();
			void set(int value);
		}

		property RigidBodyFlags Flags
		{
			RigidBodyFlags get();
			void set(RigidBodyFlags value);
		}

		property int FrictionSolverType
		{
			int get();
			void set(int value);
		}

		property Vector3 Gravity
		{
			Vector3 get();
			void set(Vector3 acceleration);
		}

		property Vector3 InvInertiaDiagLocal
		{
			Vector3 get();
			void set(Vector3 diagInvInertia);
		}

		property Matrix InvInertiaTensorWorld
		{
			Matrix get();
		}

		property btScalar InvMass
		{
			btScalar get();
		}

		property bool IsInWorld
		{
			bool get();
		}

		property btScalar LinearDamping
		{
			btScalar get();
		}

		property Vector3 LinearFactor
		{
			Vector3 get();
			void set(Vector3 linearFactor);
		}

		property btScalar LinearSleepingThreshold
		{
			btScalar get();
		}

		property Vector3 LinearVelocity
		{
			Vector3 get();
			void set(Vector3 linVel);
		}

		property Vector3 LocalInertia
		{
			Vector3 get();
		}

		property BulletSharp::MotionState^ MotionState
		{
			BulletSharp::MotionState^ get();
			void set(BulletSharp::MotionState^ motionState);
		}
#ifndef DISABLE_CONSTRAINTS
		property int NumConstraintRefs
		{
			int get();
		}
#endif
		property Quaternion Orientation
		{
			Quaternion get();
		}

		property Vector3 TotalForce
		{
			Vector3 get();
		}

		property Vector3 TotalTorque
		{
			Vector3 get();
		}

		property bool WantsSleeping
		{
			bool get();
		}
	};
};
