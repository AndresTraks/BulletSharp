#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;

	public ref class SphereSphereCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			CreateFunc(btSphereSphereCollisionAlgorithm::CreateFunc* native);

		public:
			CreateFunc();
		};

		SphereSphereCollisionAlgorithm(PersistentManifold mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ col0Wrap, CollisionObjectWrapper^ col1Wrap);
		SphereSphereCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci);
	};
};
