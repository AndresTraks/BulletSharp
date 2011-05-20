#pragma once

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
