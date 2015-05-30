#include "StdAfx.h"

#include "CollisionObject.h"
#include "ConstraintSolver.h"
#include "ContactSolverInfo.h"
#include "Dispatcher.h"
#include "SequentialImpulseConstraintSolver.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ConstraintSolver::ConstraintSolver(btConstraintSolver* native)
{
	_native = native;
}

ConstraintSolver::~ConstraintSolver()
{
	this->!ConstraintSolver();
}

ConstraintSolver::!ConstraintSolver()
{
	if (this->IsDisposed)
		return;

	if (!_preventDelete)
	{
		ALIGNED_FREE(_native);
	}
	_native = NULL;
}

bool ConstraintSolver::IsDisposed::get()
{
	return (_native == NULL);
}

#ifndef DISABLE_CONSTRAINTS

void ConstraintSolver::AllSolved(ContactSolverInfo^ info
#ifndef DISABLE_DEBUGDRAW
	,IDebugDraw^ debugDrawer
#endif
	)
{
#ifndef DISABLE_DEBUGDRAW
	DebugDraw^ cast = dynamic_cast<DebugDraw^>(debugDrawer);
	if (cast) {
		_native->allSolved(*(btContactSolverInfo*)info->_native, cast->_native);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		_native->allSolved(*(btContactSolverInfo*)info->_native, wrapper);
		delete wrapper;
	}
#else
	_native->allSolved(*(btContactSolverInfo*)info->_native, 0);
#endif
}

void ConstraintSolver::PrepareSolve(int numBodies, int numManifolds)
{
	_native->prepareSolve(numBodies, numManifolds);
}

void ConstraintSolver::Reset()
{
	_native->reset();
}

btScalar ConstraintSolver::SolveGroup(array<CollisionObject^>^ bodies, array<PersistentManifold>^ manifold,
	array<TypedConstraint^>^ constraints, ContactSolverInfo^ info,
#ifndef DISABLE_DEBUGDRAW
	IDebugDraw^ debugDrawer,
#endif
	Dispatcher^ dispatcher)
{
	int i;
	int numBodies = bodies->Length;
	int numManifolds = bodies->Length;
	int numConstraints = bodies->Length;

	btCollisionObject** bodiesTemp = new btCollisionObject*[numBodies];
	btPersistentManifold** manifoldsTemp = new btPersistentManifold*[numManifolds];
	btTypedConstraint** constraintsTemp = new btTypedConstraint*[numConstraints];

	for (i=0; i<numBodies; i++)
		bodiesTemp[i] = bodies[i]->_native;

	btScalar ret;
#ifndef DISABLE_DEBUGDRAW
	DebugDraw^ cast = dynamic_cast<DebugDraw^>(debugDrawer);
	if (cast) {
		ret = _native->solveGroup(bodiesTemp, numBodies, manifoldsTemp, numManifolds,
			constraintsTemp, numConstraints, *(btContactSolverInfo*)info->_native, cast->_native, dispatcher->_native);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		ret = _native->solveGroup(bodiesTemp, numBodies, manifoldsTemp, numManifolds,
			constraintsTemp, numConstraints, *(btContactSolverInfo*)info->_native, wrapper, dispatcher->_native);
		delete wrapper;
	}
#else
	ret = _native->solveGroup(bodiesTemp, numBodies, manifoldsTemp, numManifolds,
		constraintsTemp, numConstraints, *(btContactSolverInfo*)info->_native, 0, dispatcher->_native);
#endif

	delete[] bodiesTemp;
	delete[] manifoldsTemp;
	delete[] constraintsTemp;

	return ret;
}

ConstraintSolverType ConstraintSolver::SolverType::get()
{
	return (ConstraintSolverType) _native->getSolverType();
}

#endif
