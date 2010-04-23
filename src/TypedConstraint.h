#pragma once

#include "Enums.h"
#include "IDisposable.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class TypedConstraint : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	protected:
		RigidBody^ rigidBodyA;
		RigidBody^ rigidBodyB;

	internal:
		TypedConstraint(btTypedConstraint* typedConstraint);
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

	public:
#ifndef DISABLE_SERIALIZE
		int CalculateSerializeBufferSize();
#endif
		void EnableFeedback(bool needsFeedback);
		btScalar GetAppliedImpulse(); // Not a property to avoid crashing when feedback is not enabled
		btScalar GetParam(ConstraintParam num, int axis);
		btScalar GetParam(ConstraintParam num);
		void SetParam(ConstraintParam num, btScalar value, int axis);
		void SetParam(ConstraintParam num, btScalar value);

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
