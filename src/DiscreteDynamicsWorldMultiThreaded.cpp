#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "DiscreteDynamicsWorldMultiThreaded.h"
#include "Dispatcher.h"
#include "SequentialImpulseConstraintSolver.h"

ConstraintSolverPoolMultiThreaded::ConstraintSolverPoolMultiThreaded(int numSolvers)
	: ConstraintSolver(ALIGNED_NEW(btConstraintSolverPoolMt)(numSolvers))
{
}


DiscreteDynamicsWorldMultiThreaded::DiscreteDynamicsWorldMultiThreaded(BulletSharp::Dispatcher^ dispatcher,
	BroadphaseInterface^ pairCache, ConstraintSolverPoolMultiThreaded^ constraintSolver,
	CollisionConfiguration^ collisionConfiguration)
{
	if (!dispatcher)
	{
		throw gcnew ArgumentNullException("dispatcher");
	}
	if (!pairCache)
	{
		throw gcnew ArgumentNullException("pairCache");
	}
	if (!constraintSolver)
	{
		throw gcnew ArgumentNullException("constraintSolver");
	}

	auto native = new btDiscreteDynamicsWorldMt(dispatcher->_native,
		pairCache->_native, (btConstraintSolverPoolMt*)constraintSolver->_native,
		collisionConfiguration != nullptr ? collisionConfiguration->_native : nullptr);

	_constraintSolver = constraintSolver;
	SetInternalReferences(native, dispatcher, pairCache);
}

#endif
