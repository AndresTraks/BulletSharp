#pragma once

#include "DiscreteCollisionDetectorInterface.h"

namespace BulletSharp
{
	ref class CollisionObject;

	public ref class ManifoldResult : DiscreteCollisionDetectorInterface::Result
	{
	public:
		ManifoldResult();
		ManifoldResult(CollisionObject^ body0, CollisionObject^ body1);

		property btManifoldResult* UnmanagedPointer
		{
			btManifoldResult* get() new;
		}
	};
};
