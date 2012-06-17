#pragma once

#include "DiscreteCollisionDetectorInterface.h"

namespace BulletSharp
{
	ref class CollisionObject;
	ref class CollisionObjectWrapper;
	ref class PersistentManifold;

	public ref class ManifoldResult : DiscreteCollisionDetectorInterface::Result
	{
	public:
		ManifoldResult();
		ManifoldResult(CollisionObjectWrapper^ body0, CollisionObjectWrapper^ body1);

		property CollisionObject^ Body0Internal
		{
			CollisionObject^ get();
		}

		property CollisionObject^ Body1Internal
		{
			CollisionObject^ get();
		}

		property CollisionObjectWrapper^ Body0Wrap
		{
			CollisionObjectWrapper^ get();
		}

		property CollisionObjectWrapper^ Body1Wrap
		{
			CollisionObjectWrapper^ get();
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
