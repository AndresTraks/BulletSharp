#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class FixedConstraint : TypedConstraint
	{
	internal:
		FixedConstraint(btFixedConstraint* native);

	public:
		FixedConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB);
	};
};
