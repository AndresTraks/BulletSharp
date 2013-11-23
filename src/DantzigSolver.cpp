#include "StdAfx.h"

#ifndef DISABLE_MLCP

#include "DantzigSolver.h"

DantzigSolver::DantzigSolver(btDantzigSolver* native)
	: MLCPSolverInterface(native)
{
}

DantzigSolver::DantzigSolver()
	: MLCPSolverInterface(new btDantzigSolver())
{
}

#endif
