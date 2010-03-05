#pragma once

#include "Generic6DofConstraint.h"

namespace BulletSharp
{
	public ref class Generic6DofSpringConstraint : Generic6DofConstraint
	{
	internal:
		Generic6DofSpringConstraint(btGeneric6DofSpringConstraint* constraint);
	public:
		Generic6DofSpringConstraint(RigidBody^ rbA, RigidBody^ rbB,
			Matrix frameInA, Matrix frameInB, bool useReferenceFrameA);

		void EnableSpring(int index, bool onOff);
		void SetDamping(int index, btScalar damping);
		void SetEquilibriumPoint(int index, btScalar val);
		void SetEquilibriumPoint(int index);
		void SetEquilibriumPoint();
		void SetStiffness(int index, btScalar stiffness);

		property btGeneric6DofSpringConstraint* UnmanagedPointer
		{
			btGeneric6DofSpringConstraint* get() new;
		}
	};
};
