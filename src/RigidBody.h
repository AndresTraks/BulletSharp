#pragma once

#include "CollisionObject.h"
#include "MotionState.h"
#include "RigidBodyConstructionInfo.h"
#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class TypedConstraint;

	public ref class RigidBody : BulletSharp::CollisionObject
	{
		private:
			MotionState^ _motionState;

		private:
			RigidBody(btRigidBody* body);

		public:
			RigidBody(RigidBodyConstructionInfo^ info);

			void AddConstraintRef(TypedConstraint^ c);
			void ApplyCentralForce(Vector3 force);
			void ApplyCentralImpulse(Vector3 force);
			void ApplyDamping(btScalar timeStep);
			void ApplyForce(Vector3 force, Vector3 rel_pos);
			void ApplyGravity();
			void ApplyImpulse(Vector3 impulse, Vector3 rel_pos);
			void ApplyTorque(Vector3 torque);
			void ApplyTorqueImpulse(Vector3 torque);
			virtual bool CheckCollideWithOverride(CollisionObject^ collisionObject) override;
			void ClearForces();
			btScalar ComputeAngularImpulseDenominator(Vector3 axis);
			btScalar ComputeImpulseDenominator(Vector3 pos, Vector3 normal);
			void GetAabb([Out] Vector3% aabbMin, [Out] Vector3% aabbMax);
			void SetDamping(btScalar lin_damping, btScalar ang_damping);
			void SetMassProps(btScalar mass, Vector3 inertia);
			void SetSleepingThresholds(btScalar linear, btScalar angular);
			void Translate(Vector3 v);
			void UpdateDeactivation(btScalar timeStep);
			void UpdateInertiaTensor();
			bool WantsSleeping();

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

			property Vector3 CenterOfMassPosition
			{
				Vector3 get();
			}

			property Matrix CenterOfMassTransform
			{
				Matrix get();
				void set(Matrix value);
			}

			property Vector3 Gravity
			{
				Vector3 get();
				void set( Vector3 value );
			}
			
			property Vector3 InvInertiaDiagLocal
			{
				Vector3 get();
				void set( Vector3 value );
			}

			property Vector3 LinearFactor
			{
				Vector3 get();
				void set(Vector3 value);
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

		internal:
			property btRigidBody* UnmanagedPointer
			{
				btRigidBody* get() new;
			}
	};
};
