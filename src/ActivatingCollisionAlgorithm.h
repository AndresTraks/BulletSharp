#pragma once

#include "CollisionAlgorithm.h"

namespace BulletSharp
{
	public ref class ActivatingCollisionAlgorithm abstract : CollisionAlgorithm
	{
	internal:
		ActivatingCollisionAlgorithm(btActivatingCollisionAlgorithm* native);
	};
};
