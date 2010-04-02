#pragma once

// Fully implemented as of 02 Apr 2010

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmConstructionInfo;
	ref class CollisionObject;
	ref class PersistentManifold;

	public ref class Box2dBox2dCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};

		Box2dBox2dCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci);
		Box2dBox2dCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObject^ body0, CollisionObject^ body1);
	};
};
