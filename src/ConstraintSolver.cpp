#include "StdAfx.h"

#include "ConstraintSolver.h"

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

void ConstraintSolver::Reset()
{
	UnmanagedPointer->reset();
}

btConstraintSolver* ConstraintSolver::UnmanagedPointer::get()
{
	return _solver;
}
void ConstraintSolver::UnmanagedPointer::set(btConstraintSolver* value)
{
	_solver = value;
}