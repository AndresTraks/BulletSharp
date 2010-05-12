#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class PersistentManifold;
	ref class RigidBody;

	public ref class ContactConstraint : TypedConstraint
	{
	internal:
		ContactConstraint(btContactConstraint* constraint);
	
	public:
		ContactConstraint(PersistentManifold^ contactManifold, RigidBody^ rbA, RigidBody^ rbB);
	};
};
