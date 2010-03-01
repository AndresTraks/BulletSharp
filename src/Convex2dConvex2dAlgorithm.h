#pragma once

#include "CollisionCreateFunc.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	ref class ConvexPenetrationDepthSolver;

	public ref class Convex2dConvex2dAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc(SimplexSolverInterface^ simplexSolver,
				ConvexPenetrationDepthSolver^ pdSolver);
		};
	};
};
