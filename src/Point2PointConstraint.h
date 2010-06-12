#pragma once

// Fully implemented as of 12 May 2010

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class ConstraintSetting
	{
	private:
		btConstraintSetting* _setting;

	internal:
		ConstraintSetting(btConstraintSetting* setting);

	public:
		ConstraintSetting();

		property btScalar Damping
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar ImpulseClamp
		{
			btScalar get();
			void set(btScalar value);
		}

		property btScalar Tau
		{
			btScalar get();
			void set(btScalar value);
		}

	internal:
		property btConstraintSetting* UnmanagedPointer
		{
			virtual btConstraintSetting* get();
			void set(btConstraintSetting* value);
		}
	};

	public ref class Point2PointConstraint : TypedConstraint
	{
	internal:
		Point2PointConstraint(btPoint2PointConstraint* constraint);

	public:
		Point2PointConstraint(RigidBody^ rbA, RigidBody^ rbB, Vector3 pivotInA, Vector3 pivotInB);
		Point2PointConstraint(RigidBody^ rbA, Vector3 pivotInA);

		btScalar GetParam(int num, int axis);
		btScalar GetParam(int num);
		void SetParam(int num, btScalar value, int axis);
		void SetParam(int num, btScalar value);
		void UpdateRHS(btScalar timeStep);

		property Vector3 PivotInA
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 PivotInB
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property ConstraintSetting^ Setting
		{
			ConstraintSetting^ get();
			void set(ConstraintSetting^ value);
		}

	internal:
		property btPoint2PointConstraint* UnmanagedPointer
		{
			btPoint2PointConstraint* get() new;
		}
	};
};
