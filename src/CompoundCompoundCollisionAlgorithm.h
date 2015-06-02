#pragma once

#include "CompoundCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmConstructionInfo;
	ref class CollisionObjectWrapper;

	public ref class CompoundCompoundCollisionAlgorithm : CompoundCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			CreateFunc(btCompoundCompoundCollisionAlgorithm::CreateFunc* native);

		public:
			CreateFunc();
		};

		ref class SwappedCreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			SwappedCreateFunc(btCompoundCompoundCollisionAlgorithm::SwappedCreateFunc* native);

		public:
			SwappedCreateFunc();
		};

		CompoundCompoundCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			bool isSwapped);
	};
};
