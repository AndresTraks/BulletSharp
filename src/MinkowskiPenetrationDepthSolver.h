#pragma once

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h>
#pragma managed(pop)

#include "ConvexPenetrationDepthSolver.h"

namespace BulletSharp
{
	public ref class MinkowskiPenetrationDepthSolver : ConvexPenetrationDepthSolver
	{
	public:
		MinkowskiPenetrationDepthSolver();
	};
};
