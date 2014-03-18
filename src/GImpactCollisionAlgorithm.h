#pragma once

#include "ActivatingCollisionAlgorithm.h"
#include "CollisionCreateFunc.h"

namespace BulletSharp
{
	ref class CollisionDispatcher;

	public ref class GImpactCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		internal:
			CreateFunc(btGImpactCollisionAlgorithm::CreateFunc* native);

		public:
			CreateFunc();
		};

	internal:
		GImpactCollisionAlgorithm(btGImpactCollisionAlgorithm* native);

	public:
		static void RegisterAlgorithm(CollisionDispatcher^ dispatcher);
	};
};
