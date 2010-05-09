#pragma once

// Fully implemented as of 09 May 2010

#include "DiscreteCollisionDetectorInterface.h"

namespace BulletSharp
{
	ref class CollisionObject;
	ref class PersistentManifold;

	public ref class ManifoldResult : DiscreteCollisionDetectorInterface::Result
	{
	public:
		ManifoldResult();
		ManifoldResult(CollisionObject^ body0, CollisionObject^ body1);

		property CollisionObject^ Body0Internal
		{
			CollisionObject^ get();
		}

		property CollisionObject^ Body1Internal
		{
			CollisionObject^ get();
		}

		property BulletSharp::PersistentManifold^ PersistentManifold
		{
			BulletSharp::PersistentManifold^ get();
			void set(BulletSharp::PersistentManifold^ value);
		}

	internal:
		property btManifoldResult* UnmanagedPointer
		{
			btManifoldResult* get() new;
		}
	};
};
