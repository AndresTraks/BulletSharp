#pragma once

#include "Generic6DofSpring2Constraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class Hinge2Constraint : Generic6DofSpring2Constraint
	{
	public:
		Hinge2Constraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 anchor,
			Vector3 axis1, Vector3 axis2);

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
	};
};
