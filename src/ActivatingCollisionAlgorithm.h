#pragma once

#include "CollisionAlgorithm.h"

namespace BulletSharp
{
	public ref class ActivatingCollisionAlgorithm : CollisionAlgorithm
	{
	internal:
		ActivatingCollisionAlgorithm(btActivatingCollisionAlgorithm* algorithm);
	};
};
