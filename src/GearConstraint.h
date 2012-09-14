#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class GearConstraint : TypedConstraint
	{
	internal:
		GearConstraint(btGearConstraint* constraint);

	public:
		GearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA, Vector3 axisInB, btScalar ratio);
	};
};
