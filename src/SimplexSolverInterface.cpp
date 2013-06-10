#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON
#ifndef NO_VIRTUAL_INTERFACE

#include "SimplexSolverInterface.h"

SimplexSolverInterface::SimplexSolverInterface(btSimplexSolverInterface* simplexSolver)
{
	_native = simplexSolver;
}

SimplexSolverInterface::~SimplexSolverInterface()
{
	this->!SimplexSolverInterface();
}

SimplexSolverInterface::!SimplexSolverInterface()
{
	delete _native;
	_native = NULL;
}

bool SimplexSolverInterface::IsDisposed::get()
{
	return (_native == NULL);
}

#endif
#endif
