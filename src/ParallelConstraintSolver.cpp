#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED

#include "ParallelConstraintSolver.h"

MultiThreaded::ParallelConstraintSolver::ParallelConstraintSolver(ThreadSupportInterface^ solverThreadSupport)
: SequentialImpulseConstraintSolver(ALIGNED_NEW(btParallelConstraintSolver) (solverThreadSupport->_native))
{
	_solverThreadSupport = solverThreadSupport;
}

#endif
