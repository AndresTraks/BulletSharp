#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class RigidBody;

	public ref class GearConstraint : TypedConstraint
	{
	public:
		GearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA,
			Vector3 axisInB, btScalar ratio);
		GearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA,
			Vector3 axisInB);

		property Vector3 AxisA
		{
			Vector3 get();
			void set(Vector3 axisA);
		}

		property Vector3 AxisB
		{
			Vector3 get();
			void set(Vector3 axisB);
		}

		property btScalar Ratio
		{
			btScalar get();
			void set(btScalar ratio);
		}
	};
};
