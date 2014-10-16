#include "StdAfx.h"

#if 0
#ifndef DISABLE_UNCOMMON

#include "LemkeSolver.h"

#define Native static_cast<btLemkeSolver*>(_native)

LemkeSolver::LemkeSolver(btLemkeSolver* native)
	: MlcpSolverInterface(native)
{
}

LemkeSolver::LemkeSolver()
	: MlcpSolverInterface(new btLemkeSolver())
{
}

int LemkeSolver::DebugLevel::get()
{
	return Native->m_debugLevel;
}
void LemkeSolver::DebugLevel::set(int value)
{
	Native->m_debugLevel = value;
}

int LemkeSolver::MaxLoops::get()
{
	return Native->m_maxLoops;
}
void LemkeSolver::MaxLoops::set(int value)
{
	Native->m_maxLoops = value;
}

btScalar LemkeSolver::MaxValue::get()
{
	return Native->m_maxValue;
}
void LemkeSolver::MaxValue::set(btScalar value)
{
	Native->m_maxValue = value;
}

bool LemkeSolver::UseLoHighBounds::get()
{
	return Native->m_useLoHighBounds;
}
void LemkeSolver::UseLoHighBounds::set(bool value)
{
	Native->m_useLoHighBounds = value;
}

#endif
#endif
