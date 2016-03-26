#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "Dispatcher.h"
#include "MultiBodyConstraintSolver.h"
#include "PersistentManifold.h"
#ifndef DISABLE_CONSTRAINTS
#include "MultiBodyConstraint.h"
#include "TypedConstraint.h"
#endif
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

#define Native static_cast<btMultiBodyConstraintSolver*>(_native)

MultiBodyConstraintSolver::MultiBodyConstraintSolver()
	: SequentialImpulseConstraintSolver(new btMultiBodyConstraintSolver())
{
}
/*
#ifndef DISABLE_CONSTRAINTS
btScalar MultiBodyConstraintSolver::SolveGroupCacheFriendlyFinish(CollisionObject^ bodies,
	int numBodies, ContactSolverInfo^ infoGlobal)
{
	return Native->solveGroupCacheFriendlyFinish(bodies->_native, numBodies, *(btContactSolverInfo*)infoGlobal->_native);
}
#endif

#ifndef DISABLE_CONSTRAINTS
#ifndef DISABLE_DEBUGDRAW
void MultiBodyConstraintSolver::SolveMultiBodyGroup(CollisionObject^ bodies, int numBodies,
	PersistentManifold manifold, int numManifolds, TypedConstraint^ constraints, int numConstraints,
	MultiBodyConstraint^ multiBodyConstraints, int numMultiBodyConstraints, ContactSolverInfo^ info,
	IDebugDraw^ debugDrawer, Dispatcher^ dispatcher)
{
	Native->solveMultiBodyGroup(bodies->_native, numBodies, manifold->_native, numManifolds,
		constraints->_native, numConstraints, multiBodyConstraints->_native, numMultiBodyConstraints,
		*(btContactSolverInfo*)info->_native, DebugDraw::GetUnmanaged(debugDrawer),
		dispatcher->_native);
}
#endif
#endif
*/
#endif
