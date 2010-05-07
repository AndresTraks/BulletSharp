#pragma once

#pragma managed(push, off)
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#pragma managed(pop)

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
