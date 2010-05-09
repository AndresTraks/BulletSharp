#pragma once

// Fully implemented as of 09 May 2010

#include "CollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	public ref class EmptyAlgorithm : CollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};

		EmptyAlgorithm(CollisionAlgorithmConstructionInfo^ ci);
	};
};
