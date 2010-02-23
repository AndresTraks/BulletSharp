#pragma once

#include "RigidBody.h"
#include "TypedConstraint.h"

namespace BulletSharp
{
	public ref class Point2PointConstraint : TypedConstraint
	{
	public:
		Point2PointConstraint(RigidBody^ rbA, RigidBody^ rbB,
			Vector3 pivotInA, Vector3 pivotInB);
		Point2PointConstraint(RigidBody^ rbA, Vector3 pivotInA);

		int CalculateSerializeBufferSize();
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

		property btPoint2PointConstraint* UnmanagedPointer
		{
			btPoint2PointConstraint* get() new;
		}
	};
};
