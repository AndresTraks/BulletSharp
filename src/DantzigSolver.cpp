#include "StdAfx.h"

#ifndef DISABLE_MLCP

#include "DantzigSolver.h"

DantzigSolver::DantzigSolver(btDantzigSolver* native)
	: MlcpSolverInterface(native)
{
}

DantzigSolver::DantzigSolver()
	: MlcpSolverInterface(new btDantzigSolver())
{
}

#endif
