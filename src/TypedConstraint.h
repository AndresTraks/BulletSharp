#pragma once

// Fully implemented as of 12 May 2010

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

	private:
		btTypedConstraint* _typedConstraint;

	internal:
		TypedConstraint(btTypedConstraint* typedConstraint);

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
		btScalar GetParam(ConstraintParam num, int axis);
		btScalar GetParam(ConstraintParam num);
		void SetParam(ConstraintParam num, btScalar value, int axis);
		void SetParam(ConstraintParam num, btScalar value);

		property btScalar AppliedImpulse
		{
			btScalar get();
		}

		property TypedConstraintType ConstraintType
		{
			TypedConstraintType get();
		}

		property btScalar DebugDrawSize
		{
			btScalar get();
			void set(btScalar value);
		}

		property bool NeedsFeedback
		{
			bool get();
		}

		property RigidBody^ RigidBodyA
		{
			RigidBody^ get();
		}

		property RigidBody^ RigidBodyB
		{
			RigidBody^ get();
		}

		property int Uid
		{
			int get();
		}

		property int UserConstraintId
		{
			int get();
			void set(int value);
		}

		property int UserConstraintType
		{
			int get();
			void set(int value);
		}

	internal:
		property btTypedConstraint* UnmanagedPointer
		{
			virtual btTypedConstraint* get();
			void set(btTypedConstraint* value);
		}
	};
};
