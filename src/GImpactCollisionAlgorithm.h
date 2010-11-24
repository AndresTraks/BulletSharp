#pragma once

#include "ActivatingCollisionAlgorithm.h"

namespace BulletSharp
{
	ref class CollisionDispatcher;

	public ref class GImpactCollisionAlgorithm : ActivatingCollisionAlgorithm
	{
	internal:
		GImpactCollisionAlgorithm(btGImpactCollisionAlgorithm* algorithm);

	public:
		static void RegisterAlgorithm(CollisionDispatcher^ dispatcher);
	};
};
