#include "StdAfx.h"

#include "CollisionObject.h"
#include "ConstraintSolver.h"
#include "ContactSolverInfo.h"
#include "Dispatcher.h"
#include "StackAlloc.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ConstraintSolver::ConstraintSolver(btConstraintSolver* solver)
{
	_solver = solver;
}

ConstraintSolver::~ConstraintSolver()
{
	this->!ConstraintSolver();
}

ConstraintSolver::!ConstraintSolver()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_solver = NULL;
	
	OnDisposed( this, nullptr );
}

bool ConstraintSolver::IsDisposed::get()
{
	return (_solver == NULL);
}

#ifndef DISABLE_CONSTRAINTS

void ConstraintSolver::AllSolved(ContactSolverInfo^ info,
#ifndef DISABLE_DEBUGDRAW
	DebugDraw^ debugDrawer,
#endif
	StackAlloc^ stackAlloc)
{
	_solver->allSolved(*info->UnmanagedPointer,
#ifndef DISABLE_DEBUGDRAW
		(debugDrawer != nullptr) ? debugDrawer->UnmanagedPointer : 0,
#else
		0,
#endif
		stackAlloc->UnmanagedPointer);
}

void ConstraintSolver::PrepareSolve(int numBodies, int numManifolds)
{
	_solver->prepareSolve(numBodies, numManifolds);
}

void ConstraintSolver::Reset()
{
	UnmanagedPointer->reset();
}

btScalar ConstraintSolver::SolveGroup(array<CollisionObject^>^ bodies, array<PersistentManifold^>^ manifold,
	array<TypedConstraint^>^ constraints, ContactSolverInfo^ info,
#ifndef DISABLE_DEBUGDRAW
	DebugDraw^ debugDrawer,
#endif
	StackAlloc^ stackAlloc, Dispatcher^ dispatcher)
{
	int i;
	int numBodies = bodies->Length;
	int numManifolds = bodies->Length;
	int numConstraints = bodies->Length;

	btCollisionObject** bodiesTemp = new btCollisionObject*[numBodies];
	btPersistentManifold** manifoldsTemp = new btPersistentManifold*[numManifolds];
	btTypedConstraint** constraintsTemp = new btTypedConstraint*[numConstraints];

	for (i=0; i<numBodies; i++)
		bodiesTemp[i] = bodies[i]->UnmanagedPointer;

	btScalar ret = _solver->solveGroup(bodiesTemp, numBodies, manifoldsTemp, numManifolds,
		constraintsTemp, numConstraints, *info->UnmanagedPointer,
#ifndef DISABLE_DEBUGDRAW
		(debugDrawer != nullptr) ? debugDrawer->UnmanagedPointer : 0,
#else
		0,
#endif
		stackAlloc->UnmanagedPointer, dispatcher->UnmanagedPointer);

	delete bodiesTemp;
	delete manifoldsTemp;
	delete constraintsTemp;

	return ret;
}

btConstraintSolver* ConstraintSolver::UnmanagedPointer::get()
{
	return _solver;
}
void ConstraintSolver::UnmanagedPointer::set(btConstraintSolver* value)
{
	_solver = value;
}

#endif
