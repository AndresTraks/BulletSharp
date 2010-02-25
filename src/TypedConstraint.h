#pragma once

#include "Enums.h"
#include "IDisposable.h"
#include "RigidBody.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class TypedConstraint abstract : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btTypedConstraint* _typedConstraint;
	public:
		!TypedConstraint();
	protected:
		~TypedConstraint();
	public:
		property bool IsDisposed
		{
			virtual bool get();
		}

	protected:
		TypedConstraint(btTypedConstraint* typedConstraint);
		RigidBody^ rigidBodyA;
		RigidBody^ rigidBodyB;

	public:
		int CalculateSerializeBufferSize();
		void EnableFeedback(bool needsFeedback);
		
		// Not a property to avoid crashing when feedback is not enabled
		btScalar GetAppliedImpulse();

		btScalar GetParam(ConstraintParams num, int axis);
		btScalar GetParam(ConstraintParams num);
		void SetParam(ConstraintParams num, btScalar value, int axis);
		void SetParam(ConstraintParams num, btScalar value);

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
