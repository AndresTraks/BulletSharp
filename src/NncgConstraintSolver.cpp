#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "NncgConstraintSolver.h"

#define Native static_cast<btNNCGConstraintSolver*>(_native)

NncgConstraintSolver::NncgConstraintSolver()
	: SequentialImpulseConstraintSolver(new btNNCGConstraintSolver())
{
}

bool NncgConstraintSolver::OnlyForNoneContact::get()
{
	return Native->m_onlyForNoneContact;
}
void NncgConstraintSolver::OnlyForNoneContact::set(bool value)
{
	Native->m_onlyForNoneContact = value;
}

#endif
