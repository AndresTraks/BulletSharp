#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "DiscreteDynamicsWorldMultiThreaded.h"
#include "Dispatcher.h"

ConstraintSolverPoolMultiThreaded::ConstraintSolverPoolMultiThreaded(int numSolvers)
	: ConstraintSolver(new btConstraintSolverPoolMt(numSolvers))
{
}


DiscreteDynamicsWorldMultiThreaded::DiscreteDynamicsWorldMultiThreaded(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
	ConstraintSolverPoolMultiThreaded^ constraintSolver, CollisionConfiguration^ collisionConfiguration)
	: DiscreteDynamicsWorld(new btDiscreteDynamicsWorldMt(dispatcher != nullptr ? dispatcher->_native : nullptr,
		pairCache != nullptr ? pairCache->_native : nullptr, constraintSolver != nullptr ? constraintSolver->_native : nullptr,
		collisionConfiguration != nullptr ? collisionConfiguration->_native : nullptr), dispatcher, pairCache)
{
}

#endif
