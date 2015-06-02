#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionObjectWrapper;

	public ref class ConvexConcaveCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			CreateFunc(btConvexConcaveCollisionAlgorithm::CreateFunc* native);

		public:
			CreateFunc();
		};

		ref class SwappedCreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			SwappedCreateFunc(btConvexConcaveCollisionAlgorithm::SwappedCreateFunc* native);

		public:
			SwappedCreateFunc();
		};

		ConvexConcaveCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci, CollisionObjectWrapper^ body0Wrap,
			CollisionObjectWrapper^ body1Wrap, bool isSwapped);

		void ClearCache();
	};
};
