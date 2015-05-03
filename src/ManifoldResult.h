#pragma once

#include "DiscreteCollisionDetectorInterface.h"

namespace BulletSharp
{
	ref class CollisionObject;
	ref class CollisionObjectWrapper;
	value struct PersistentManifold;

	public ref class ManifoldResult abstract : DiscreteCollisionDetectorInterface::Result
	{
	public:
		ManifoldResult();
		ManifoldResult(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap);

		static btScalar CalculateCombinedFriction(CollisionObject^ body0, CollisionObject^ body1);
		static btScalar CalculateCombinedRestitution(CollisionObject^ body0, CollisionObject^ body1);
		void RefreshContactPoints();

		property CollisionObject^ Body0Internal
		{
			CollisionObject^ get();
		}

		property CollisionObjectWrapper^ Body0Wrap
		{
			CollisionObjectWrapper^ get();
			void set(CollisionObjectWrapper^ obj0Wrap);
		}

		property CollisionObject^ Body1Internal
		{
			CollisionObject^ get();
		}

		property CollisionObjectWrapper^ Body1Wrap
		{
			CollisionObjectWrapper^ get();
			void set(CollisionObjectWrapper^ obj1Wrap);
		}

		property PersistentManifold PersistentManifold
		{
			BulletSharp::PersistentManifold get();
			void set(BulletSharp::PersistentManifold manifoldPtr);
		}
	};
};
