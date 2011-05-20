#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmConstructionInfo;
	ref class CollisionObject;
	ref class PersistentManifold;

	public ref class BoxBoxCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};

		BoxBoxCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci);
		BoxBoxCollisionAlgorithm(PersistentManifold^ mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObject^ body0, CollisionObject^ body1);
	};
};
