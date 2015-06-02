#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmConstructionInfo;
	ref class CollisionObjectWrapper;
	value struct PersistentManifold;

	public ref class BoxBoxCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			CreateFunc(btBoxBoxCollisionAlgorithm::CreateFunc* native);

		public:
			CreateFunc();
		};

		BoxBoxCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci);
		BoxBoxCollisionAlgorithm(PersistentManifold mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap);
	};
};
