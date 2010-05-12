#pragma once

// Fully implemented as of 12 May 2010

#include "Generic6DofConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class UniversalConstraint : Generic6DofConstraint
	{
	public:
		UniversalConstraint(RigidBody^ rbA, RigidBody^ rbB,
			Vector3 anchor, Vector3 axis1, Vector3 axis2);

		void SetLowerLimit(btScalar ang1min, btScalar ang2min);
		void SetUpperLimit(btScalar ang1max, btScalar ang2max);

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
		property btUniversalConstraint* UnmanagedPointer
		{
			btUniversalConstraint* get() new;
		}
	};
};
