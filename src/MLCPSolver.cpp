#include "StdAfx.h"

#ifndef DISABLE_MLCP

#include "MLCPSolver.h"

#define Native static_cast<btMLCPSolver*>(_native)

MLCPSolver::MLCPSolver(btMLCPSolver* native)
	: SequentialImpulseConstraintSolver(native)
{
}

MLCPSolver::MLCPSolver(MLCPSolverInterface^ solver)
	: SequentialImpulseConstraintSolver(new btMLCPSolver(solver->_native))
{
}

void MLCPSolver::SetMLCPSolver(MLCPSolverInterface^ solver)
{
	Native->setMLCPSolver(solver->_native);
}

int MLCPSolver::NumFallbacks::get()
{
	return Native->getNumFallbacks();
}
void MLCPSolver::NumFallbacks::set(int num)
{
	Native->setNumFallbacks(num);
}

btScalar MLCPSolver::Cfm::get()
{
	return Native->getCfm();
}
void MLCPSolver::Cfm::set(btScalar value)
{
	Native->setCfm(value);
}

#endif
