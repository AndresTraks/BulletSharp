#pragma once

#include "Enums.h"
#include "RigidBody.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class TypedConstraint abstract
	{
	private:
		btTypedConstraint* _typedConstraint;

	protected:
		TypedConstraint(btTypedConstraint* typedConstraint);
		RigidBody^ rigidBodyA;
		RigidBody^ rigidBodyB;

	public:
		int CalculateSerializeBufferSize();
		void EnableFeedback(bool needsFeedback);
		
		// Not a property to avoid crashing when feedback is not enabled
		btScalar GetAppliedImpulse();

		btScalar GetParam(int num, int axis);
		btScalar GetParam(int num);
		void SetParam(int num, btScalar value, int axis);
		void SetParam(int num, btScalar value);

		property TypedConstraintType ConstraintType
		{
			TypedConstraintType get();
		}

		property btScalar DebugDrawSize
		{
			btScalar get();
			void set(btScalar value);
		}

		property RigidBody^ RigidBodyA
		{
			RigidBody^ get();
		internal:
			void set(RigidBody^ value);
		}

		property RigidBody^ RigidBodyB
		{
			RigidBody^ get();
		internal:
			void set(RigidBody^ value);
		}

	internal:
		property btTypedConstraint* UnmanagedPointer
		{
			virtual btTypedConstraint* get();
			void set(btTypedConstraint* value);
		}
	};
};
