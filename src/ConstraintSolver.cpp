#include "StdAfx.h"

#include "CollisionObject.h"
#include "ConstraintSolver.h"
#include "ContactSolverInfo.h"
#include "Dispatcher.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

ConstraintSolver::ConstraintSolver(btConstraintSolver* solver)
{
	_native = solver;
}

ConstraintSolver::~ConstraintSolver()
{
	this->!ConstraintSolver();
}

ConstraintSolver::!ConstraintSolver()
{
	if (this->IsDisposed)
		return;
	
	OnDisposing(this, nullptr);
	
	ALIGNED_FREE(_native);
	_native = NULL;
	
	OnDisposed(this, nullptr);
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
	_native->allSolved(*info->UnmanagedPointer,
#ifndef DISABLE_DEBUGDRAW
		DebugDraw::GetUnmanaged(debugDrawer)
#else
		0
#endif
	);
}

void ConstraintSolver::PrepareSolve(int numBodies, int numManifolds)
{
	_native->prepareSolve(numBodies, numManifolds);
}

void ConstraintSolver::Reset()
{
	_native->reset();
}

btScalar ConstraintSolver::SolveGroup(array<CollisionObject^>^ bodies, array<PersistentManifold^>^ manifold,
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
		bodiesTemp[i] = bodies[i]->UnmanagedPointer;

	btScalar ret = _native->solveGroup(bodiesTemp, numBodies, manifoldsTemp, numManifolds,
		constraintsTemp, numConstraints, *info->UnmanagedPointer,
#ifndef DISABLE_DEBUGDRAW
		DebugDraw::GetUnmanaged(debugDrawer),
#else
		0,
#endif
		dispatcher->UnmanagedPointer);

	delete[] bodiesTemp;
	delete[] manifoldsTemp;
	delete[] constraintsTemp;

	return ret;
}

#endif
