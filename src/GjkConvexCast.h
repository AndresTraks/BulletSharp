#pragma once

// Fully implemented as of 24 Nov 2010

#include "ConvexCast.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class ConvexShape;

	public ref class GjkConvexCast : ConvexCast
	{
	public:
		GjkConvexCast(ConvexShape^ convexA, ConvexShape^ convexB, SimplexSolverInterface^ simplexSolver);
	};
};
