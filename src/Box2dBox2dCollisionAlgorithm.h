#pragma once

#pragma managed(push, off)
#include <BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h>
#pragma managed(pop)

#include "CollisionCreateFunc.h"
#include "ConvexPenetrationDepthSolver.h"
#include "SimplexSolverInterface.h"

namespace BulletSharp
{
	public ref class Box2dBox2dCollisionAlgorithm
	{
	public:
		ref class CreateFunc : CollisionAlgorithmCreateFunc
		{
		public:
			CreateFunc();
		};
	};
};
