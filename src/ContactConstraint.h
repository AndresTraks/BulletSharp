#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	ref class PersistentManifold;

	public ref class ContactConstraint abstract : TypedConstraint
	{
	public:
		property PersistentManifold^ ContactManifold
		{
			PersistentManifold^ get();
			void set(PersistentManifold^ contactManifold);
		}
	};
};
