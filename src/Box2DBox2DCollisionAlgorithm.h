#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmConstructionInfo;
	ref class CollisionObjectWrapper;
	value struct PersistentManifold;

	public ref class Box2DBox2DCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			CreateFunc(btBox2dBox2dCollisionAlgorithm::CreateFunc* native);

		public:
			CreateFunc();
		};

		Box2DBox2DCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci);
		Box2DBox2DCollisionAlgorithm(PersistentManifold mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap);
	};
};
