#pragma once

#include "TypedConstraint.h"

namespace BulletSharp
{
	value struct PersistentManifold;

	public ref class ContactConstraint abstract : TypedConstraint
	{
	public:
		property PersistentManifold ContactManifold
		{
			PersistentManifold get();
			void set(PersistentManifold contactManifold);
		}
	};
};
