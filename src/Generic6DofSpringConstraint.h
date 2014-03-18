#pragma once

#include "Generic6DofConstraint.h"

namespace BulletSharp
{
	public ref class Generic6DofSpringConstraint : Generic6DofConstraint
	{
	internal:
		Generic6DofSpringConstraint(btGeneric6DofSpringConstraint* native);

	public:
		Generic6DofSpringConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA,
			Matrix frameInB, bool useLinearReferenceFrameA);
		Generic6DofSpringConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB);

		void EnableSpring(int index, bool onOff);
		void SetDamping(int index, btScalar damping);
		void SetEquilibriumPoint();
		void SetEquilibriumPoint(int index);
		void SetEquilibriumPoint(int index, btScalar val);
		void SetStiffness(int index, btScalar stiffness);
	};
};
