#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED

#include "ParallelConstraintSolver.h"

MultiThreaded::ParallelConstraintSolver::ParallelConstraintSolver(ThreadSupportInterface^ solverThreadSupport)
: SequentialImpulseConstraintSolver(new btParallelConstraintSolver(solverThreadSupport->UnmanagedPointer))
{
}

#endif
