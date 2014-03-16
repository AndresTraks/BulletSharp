#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class GearConstraint : TypedConstraint
	{
	internal:
		GearConstraint(btGearConstraint* native);

	public:
		GearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA, Vector3 axisInB, btScalar ratio);

		property Vector3 AxisA
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 AxisB
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property btScalar Ratio
		{
			btScalar get();
			void set(btScalar value);
		}
	};
};
