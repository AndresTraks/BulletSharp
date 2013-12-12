#pragma once

#include "CompoundCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmConstructionInfo;
	ref class CollisionObject;
	ref class CollisionObjectWrapper;
	ref class PersistentManifold;

	public ref class CompoundCompoundCollisionAlgorithm : CompoundCollisionAlgorithm
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

		CompoundCompoundCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
			CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped);
	};
};
