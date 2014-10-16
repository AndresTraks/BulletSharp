#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class FixedConstraint : TypedConstraint
	{
	private:
		RigidBody^ _rigidBodyA;
		RigidBody^ _rigidBodyB;

	internal:
		FixedConstraint(btFixedConstraint* native);

	public:
		FixedConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB);
	};
};
