#pragma once

// Fully implemented as of 25 Jun 2010

#include "ConvexCast.h"
#include "SimplexSolverInterface.h"

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.h>
#pragma managed(pop)

namespace BulletSharp
{
	ref class ConvexPenetrationDepthSolver;
	ref class ConvexShape;

	public ref class ContinuousConvexCollision : ConvexCast
	{
	public:
		ContinuousConvexCollision(ConvexShape^ convexA, ConvexShape^ convexB,
			SimplexSolverInterface^ simplexSolver, ConvexPenetrationDepthSolver^ penetrationDepthSolver);
	};
};
