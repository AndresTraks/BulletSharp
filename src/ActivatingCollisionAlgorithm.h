#pragma once

// Fully implemented as of 02 Apr 2010

#include "CollisionAlgorithm.h"

namespace BulletSharp
{
	public ref class ActivatingCollisionAlgorithm abstract : CollisionAlgorithm
	{
	internal:
		ActivatingCollisionAlgorithm(btActivatingCollisionAlgorithm* algorithm);
	};
};
