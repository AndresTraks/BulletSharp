#pragma once

#include "Generic6DofConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class UniversalConstraint : Generic6DofConstraint
	{
	public:
		UniversalConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 anchor,
			Vector3 axis1, Vector3 axis2);

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
	};
};
