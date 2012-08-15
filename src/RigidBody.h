#pragma once

#include "CollisionObject.h"

namespace BulletSharp
{
	ref class CollisionShape;
	ref class MotionState;
	ref class RigidBodyConstructionInfo;
	ref class TypedConstraint;

	public ref class RigidBody : CollisionObject
	{
	private:
		MotionState^ _motionState;

	internal:
		RigidBody(btRigidBody* body);

	public:
		RigidBody(RigidBodyConstructionInfo^ info);

#ifndef DISABLE_CONSTRAINTS
		void AddConstraintRef(TypedConstraint^ constraint);
		TypedConstraint^ GetConstraintRef(int index);
		void RemoveConstraintRef(TypedConstraint^ constraint);

		property int ConstraintRefCount
		{
			int get();
		}
#endif
		void ApplyCentralForce(Vector3 force);
		void ApplyCentralImpulse(Vector3 force);
		void ApplyDamping(btScalar timeStep);
		void ApplyForce(Vector3 force, Vector3 relativePosition);
		void ApplyGravity();
		void ApplyImpulse(Vector3 impulse, Vector3 relativePosition);
		void ApplyTorque(Vector3 torque);
		void ApplyTorqueImpulse(Vector3 torque);
		bool CheckCollideWithOverride(CollisionObject^ co);
		void ClearForces();
		btScalar ComputeAngularImpulseDenominator(Vector3 axis);
		btScalar ComputeImpulseDenominator(Vector3 pos, Vector3 normal);
		void GetAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
		Vector3 GetVelocityInLocalPoint(Vector3 relativePosition);
		void IntegrateVelocities(btScalar step);
		bool IsInWorld();
		void PredictIntegratedTransform(btScalar step, Matrix predictedTransform);
		void ProceedToTransform(Matrix newTransform);
		void SaveKinematicState(btScalar step);
		void SetDamping(btScalar linearDamping, btScalar angularDamping);
		void SetMassProps(btScalar mass, Vector3 inertia);
		void SetSleepingThresholds(btScalar linear, btScalar angular);
		void Translate(Vector3 vector);
		void UpdateDeactivation(btScalar timeStep);
		void UpdateInertiaTensor();

#ifndef DISABLE_INTERNAL
		void InternalApplyImpulse(Vector3 linearComponent, Vector3 angularComponent, btScalar impulseMagnitude);
		void InternalApplyPushImpulse(Vector3 linearComponent, Vector3 angularComponent, btScalar impulseMagnitude);
		void InternalWritebackVelocity(btScalar timeStep);
		void InternalWritebackVelocity();

		property Vector3 InternalAngularFactor
		{
			Vector3 get();
		}

		property Vector3 InternalDeltaAngularVelocity
		{
			Vector3 get();
		}

		property Vector3 InternalDeltaLinearVelocity
		{
			Vector3 get();
		}

		property Vector3 InternalInvMass
		{
			Vector3 get();
		}

		property Vector3 InternalPushVelocity
		{
			Vector3 get();
		}

		property Vector3 InternalTurnVelocity
		{
			Vector3 get();
		}
#endif

		static RigidBody^ Upcast(CollisionObject^ colObj);

		property btScalar AngularDamping
		{
			btScalar get();
		}

		property Vector3 AngularFactor
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar AngularSleepingThreshold
		{
			btScalar get();
		}

		property Vector3 AngularVelocity
		{
			Vector3 get();
			void set(Vector3 value);
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
			void set(Matrix value);
		}

		property RigidBodyFlags Flags
		{
			RigidBodyFlags get();
			void set(RigidBodyFlags value);
		}

		property Vector3 Gravity
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 InvInertiaDiagLocal
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Matrix InvInertiaTensorWorld
		{
			Matrix get();
		}

		property btScalar InvMass
		{
			btScalar get();
		}

		property btScalar LinearDamping
		{
			btScalar get();
		}

		property Vector3 LinearFactor
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar LinearSleepingThreshold
		{
			btScalar get();
		}

		property Vector3 LinearVelocity
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property BulletSharp::MotionState^ MotionState
		{
			BulletSharp::MotionState^ get();
			void set(BulletSharp::MotionState^ value);
		}

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

	internal:
		property btRigidBody* UnmanagedPointer
		{
			btRigidBody* get() new;
		}
	};

	public ref class RigidBodyConstructionInfo
	{
	internal:
		btRigidBody::btRigidBodyConstructionInfo* _unmanaged;
		BulletSharp::MotionState^ _motionState;

	public:
		RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState,
			BulletSharp::CollisionShape^ collisionShape);
		RigidBodyConstructionInfo(btScalar mass, BulletSharp::MotionState^ motionState,
			BulletSharp::CollisionShape^ collisionShape, Vector3 localInertia);

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

		property Matrix StartWorldTransform
		{
			Matrix get();
			void set(Matrix value);
		}
	};
};
