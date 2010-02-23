#include "StdAfx.h"

#include "SimplexSolverInterface.h"

#ifndef NO_VIRTUAL_INTERFACE

SimplexSolverInterface::SimplexSolverInterface(btSimplexSolverInterface* simplexSolver)
{
	_simplexSolver = simplexSolver;
}

SimplexSolverInterface::~SimplexSolverInterface()
{
	this->!SimplexSolverInterface();
}

SimplexSolverInterface::!SimplexSolverInterface()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_simplexSolver = NULL;
	
	OnDisposed( this, nullptr );
}

bool SimplexSolverInterface::IsDisposed::get()
{
	return (_simplexSolver == NULL);
}

btSimplexSolverInterface* SimplexSolverInterface::UnmanagedPointer::get()
{
	return _simplexSolver;
}
void SimplexSolverInterface::UnmanagedPointer::set(btSimplexSolverInterface* value)
{
	_simplexSolver = value;
}

#endif
