#pragma once

#include "CollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	public ref class EmptyAlgorithm : CollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			CreateFunc(btEmptyAlgorithm::CreateFunc* native);

		public:
			CreateFunc();
		};

		EmptyAlgorithm(CollisionAlgorithmConstructionInfo^ ci);
	};
};
