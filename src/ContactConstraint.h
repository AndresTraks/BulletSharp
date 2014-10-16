#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class PersistentManifold;
	ref class RigidBody;

	public ref class ContactConstraint abstract : TypedConstraint
	{
	internal:
		ContactConstraint(btContactConstraint* native);

	public:
		property PersistentManifold^ ContactManifold
		{
			PersistentManifold^ get();
			void set(PersistentManifold^ contactManifold);
		}
	};
};
