#pragma once

// Fully implemented as of 11 May 2010

#include "Generic6DofSpringConstraint.h"

namespace BulletSharp
{
	public ref class Hinge2Constraint : Generic6DofSpringConstraint
	{
	public:
		Hinge2Constraint(RigidBody^ rbA, RigidBody^ rbB,
			Vector3 anchor, Vector3 axis1, Vector3 axis2);

		void SetLowerLimit(btScalar ang1min);
		void SetUpperLimit(btScalar ang1max);

		property Vector3 Anchor
		{
			Vector3 get();
		}

		property Vector3 Anchor2
		{
			Vector3 get();
		}

		property btScalar Angle1
		{
			btScalar get();
		}

		property btScalar Angle2
		{
			btScalar get();
		}

		property Vector3 Axis1
		{
			Vector3 get();
		}

		property Vector3 Axis2
		{
			Vector3 get();
		}

	internal:
		property btHinge2Constraint* UnmanagedPointer
		{
			btHinge2Constraint* get() new;
		}
	};
};
