#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class JointFeedback
	{
	internal:
		btJointFeedback* _native;

		JointFeedback(btJointFeedback* jointFeedback);

	public:
		!JointFeedback();
	protected:
		~JointFeedback();

	public:
		JointFeedback();

		property Vector3 AppliedForceBodyA
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AppliedForceBodyB
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AppliedTorqueBodyA
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AppliedTorqueBodyB
		{
			Vector3 get();
			void set(Vector3 value);
		}
	};

	public ref class TypedConstraint : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		bool _doesNotOwnObject;
		Object^ _userObject;
		JointFeedback^ _jointFeedback;

	internal:
		btTypedConstraint* _native;
		TypedConstraint(btTypedConstraint* typedConstraint, bool doesNotOwnObject);
		TypedConstraint(btTypedConstraint* typedConstraint);

	public:
		!TypedConstraint();
	protected:
		~TypedConstraint();

	public:
#ifndef DISABLE_SERIALIZE
		int CalculateSerializeBufferSize();
#endif
		void EnableFeedback(bool needsFeedback);
		btScalar GetParam(ConstraintParam num, int axis);
		btScalar GetParam(ConstraintParam num);
		void SetParam(ConstraintParam num, btScalar value, int axis);
		void SetParam(ConstraintParam num, btScalar value);

		static property RigidBody^ FixedBody
		{
			RigidBody^ get();
		}

	internal:
		static TypedConstraint^ Upcast(btTypedConstraint* typedConstraint);

	public:
		property btScalar AppliedImpulse
		{
			btScalar get();
		}

		property btScalar BreakingImpulseThreshold
		{
			btScalar get();
			void set(btScalar value);
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

		property bool IsDisposed
		{
			virtual bool get();
		}

		property bool IsEnabled
		{
			bool get();
			void set(bool value);
		}

		property BulletSharp::JointFeedback^ JointFeedback
		{
			BulletSharp::JointFeedback^ get();
			void set(BulletSharp::JointFeedback^ value);
		}

		property bool NeedsFeedback
		{
			bool get();
			void set(bool value);
		}

		property int OverrideNumSolverIterations
		{
			int get();
			void set(int value);
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

		// UserConstraintId/UserConstraintPtr union implemented as UserObject
		property Object^ UserObject
		{
			Object^ get();
			void set(Object^ value);
		}

		property int UserConstraintType
		{
			int get();
			void set(int value);
		}

	internal:
		property btTypedConstraint* UnmanagedPointer
		{
			btTypedConstraint* get();
			void set(btTypedConstraint* value);
		}
	};

#ifdef _BT_USE_CENTER_LIMIT_
#ifdef IN_PARALLELL_SOLVER
	public ref class AngularLimit
	{
	private:
		btAngularLimit* _angularLimit;

	public:
		AngularLimit();
	};
#endif
#endif
};
