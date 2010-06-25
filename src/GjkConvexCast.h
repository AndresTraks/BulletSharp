#pragma once

// Fully implemented as of 25 Jun 2010

#include "ConvexCast.h"
#include "SimplexSolverInterface.h"

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btGjkConvexCast.h>
#pragma managed(pop)

namespace BulletSharp
{
	ref class ConvexShape;

	public ref class GjkConvexCast : ConvexCast
	{
	public:
		GjkConvexCast(ConvexShape^ convexA, ConvexShape^ convexB, SimplexSolverInterface^ simplexSolver);
	};
};
