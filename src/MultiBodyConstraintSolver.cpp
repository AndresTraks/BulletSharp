#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "Dispatcher.h"
#include "DebugDraw.h"
#include "MultiBodyConstraintSolver.h"
#include "MultiBodyConstraint.h"
#include "PersistentManifold.h"
#include "TypedConstraint.h"

#define Native static_cast<btMultiBodyConstraintSolver*>(_native)

MultiBodyConstraintSolver::MultiBodyConstraintSolver(btMultiBodyConstraintSolver* native)
	: SequentialImpulseConstraintSolver(native)
{
}

MultiBodyConstraintSolver::MultiBodyConstraintSolver()
	: SequentialImpulseConstraintSolver(new btMultiBodyConstraintSolver())
{
}
/*
void MultiBodyConstraintSolver::SolveMultiBodyGroup(CollisionObject^ bodies, int numBodies,
	PersistentManifold^ manifold, int numManifolds, TypedConstraint^ constraints,
	int numConstraints, MultiBodyConstraint^ multiBodyConstraints, int numMultiBodyConstraints,
	ContactSolverInfo^ info, IDebugDraw^ debugDrawer, Dispatcher^ dispatcher)
{
	Native->solveMultiBodyGroup(bodies->_native, numBodies, manifold->_native, numManifolds,
		constraints->_native, numConstraints, multiBodyConstraints->_native, numMultiBodyConstraints,
		*(btContactSolverInfo*)info->_native, DebugDraw::GetUnmanaged(debugDrawer), dispatcher->_native);
}
*/
#endif
