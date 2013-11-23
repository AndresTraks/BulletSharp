#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "MultiBodyConstraintSolver.h"

MultiBodyConstraintSolver::MultiBodyConstraintSolver(btMultiBodyConstraintSolver* native)
{
	_native = native;
}

MultiBodyConstraintSolver::MultiBodyConstraintSolver()
{
	_native = new btMultiBodyConstraintSolver();
}
/*
void MultiBodyConstraintSolver::SolveMultiBodyGroup(CollisionObject^ bodies, int numBodies, PersistentManifold^ manifold, int numManifolds, TypedConstraint^ constraints, int numConstraints, MultiBodyConstraint^ multiBodyConstraints, int numMultiBodyConstraints, ContactSolverInfo^ info, IDebugDraw^ debugDrawer, Dispatcher^ dispatcher)
{
	_native->solveMultiBodyGroup(bodies->_native, numBodies, manifold->_native, numManifolds, constraints->_native, numConstraints, multiBodyConstraints->_native, numMultiBodyConstraints, info->_native, debugDrawer->_native, dispatcher->_native);
}
*/
#endif
