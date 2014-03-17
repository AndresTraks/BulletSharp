#pragma once

#include "ConvexCast.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class ConvexPenetrationDepthSolver;
	ref class ConvexShape;
	ref class StaticPlaneShape;

	public ref class ContinuousConvexCollision : ConvexCast
	{
	public:
		ContinuousConvexCollision(ConvexShape^ shapeA, ConvexShape^ shapeB, SimplexSolverInterface^ simplexSolver,
			ConvexPenetrationDepthSolver^ penetrationDepthSolver);
		ContinuousConvexCollision(ConvexShape^ shapeA, StaticPlaneShape^ plane);
	};
};
