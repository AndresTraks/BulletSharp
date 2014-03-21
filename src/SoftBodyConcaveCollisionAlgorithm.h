#pragma once

#include "CollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionObject;
	ref class CollisionObjectWrapper;

	public ref class SoftBodyConcaveCollisionAlgorithm abstract : CollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};

		ref class SwappedCreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			SwappedCreateFunc();
		};

	internal:
		SoftBodyConcaveCollisionAlgorithm(btSoftBodyConcaveCollisionAlgorithm* native);

	public:
		SoftBodyConcaveCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap,
			bool isSwapped);

		void ClearCache();
	};
};
