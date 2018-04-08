#pragma once

#include "ConstraintSolver.h"
#include "DiscreteDynamicsWorld.h"

namespace BulletSharp
{
	public ref class ConstraintSolverPoolMultiThreaded : ConstraintSolver
	{
	public:
		ConstraintSolverPoolMultiThreaded(int numSolvers);
	};

	public ref class DiscreteDynamicsWorldMultiThreaded : DiscreteDynamicsWorld
	{
	public:
		DiscreteDynamicsWorldMultiThreaded(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
			ConstraintSolverPoolMultiThreaded^ constraintSolver, BulletSharp::ConstraintSolver^ constraintSolverMultiThreaded,
			CollisionConfiguration^ collisionConfiguration);
	};
}
