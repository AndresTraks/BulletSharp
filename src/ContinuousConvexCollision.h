#pragma once

// Fully implemented as of 24 Nov 2010

#include "ConvexCast.h"
#include "SimplexSolverInterface.h"

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
