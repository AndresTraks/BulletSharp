#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;

	public ref class SphereTriangleCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			CreateFunc(btSphereTriangleCollisionAlgorithm::CreateFunc* native);

		public:
			CreateFunc();
		};

		SphereTriangleCollisionAlgorithm(PersistentManifold mf, CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			bool swapped);
		SphereTriangleCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci);
	};
};
