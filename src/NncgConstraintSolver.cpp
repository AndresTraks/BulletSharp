#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "NNCGConstraintSolver.h"

#define Native static_cast<btNNCGConstraintSolver*>(_native)

NncgConstraintSolver::NncgConstraintSolver(btNNCGConstraintSolver* native)
	: SequentialImpulseConstraintSolver(native)
{
}

NncgConstraintSolver::NncgConstraintSolver()
{
	_native = new btNNCGConstraintSolver();
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
