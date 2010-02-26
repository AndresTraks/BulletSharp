#pragma once

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h>
#pragma managed(pop)

#include "CollisionCreateFunc.h"
#include "ConvexPenetrationDepthSolver.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
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
