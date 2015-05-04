#pragma once

#include "Generic6DofSpring2Constraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class FixedConstraint : Generic6DofSpring2Constraint
	{
	public:
		FixedConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA,
			Matrix frameInB);
	};
};
