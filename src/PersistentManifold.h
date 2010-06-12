#pragma once

#include "Scalar.h"

namespace BulletSharp
{
	public ref class PersistentManifold : TypedObject
	{
	internal:
		PersistentManifold(btPersistentManifold* manifold);

	public:
		PersistentManifold();

	internal:
		property btPersistentManifold* UnmanagedPointer
		{
			btPersistentManifold* get() new;
		}
	};
};
