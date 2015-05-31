#include "StdAfx.h"

#ifndef DISABLE_MLCP

#include "MlcpSolver.h"
#include "MlcpSolverInterface.h"

#define Native static_cast<btMLCPSolver*>(_native)

MlcpSolver::MlcpSolver(MlcpSolverInterface^ solver)
	: SequentialImpulseConstraintSolver(new btMLCPSolver(solver->_native))
{
	_mlcpSolver = solver;
}

void MlcpSolver::SetMLCPSolver(MlcpSolverInterface^ solver)
{
	Native->setMLCPSolver(solver->_native);
	_mlcpSolver = solver;
}

btScalar MlcpSolver::Cfm::get()
{
	return Native->getCfm();
}
void MlcpSolver::Cfm::set(btScalar cfm)
{
	Native->setCfm(cfm);
}

int MlcpSolver::NumFallbacks::get()
{
	return Native->getNumFallbacks();
}
void MlcpSolver::NumFallbacks::set(int num)
{
	Native->setNumFallbacks(num);
}

#endif
