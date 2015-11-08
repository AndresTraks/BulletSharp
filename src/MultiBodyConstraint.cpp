#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "AlignedObjectArray.h"
#ifndef DISABLE_CONSTRAINTS
#include "ContactSolverInfo.h"
#endif
#include "MultiBody.h"
#include "MultiBodyConstraint.h"
#include "MultiBodySolverConstraint.h"

MultiBodyConstraint::MultiBodyConstraint(btMultiBodyConstraint* native)
{
	_native = native;
}

MultiBodyConstraint::~MultiBodyConstraint()
{
	this->!MultiBodyConstraint();
}

MultiBodyConstraint::!MultiBodyConstraint()
{
	delete _native;
	_native = NULL;
}

void MultiBodyConstraint::AllocateJacobiansMultiDof()
{
	_native->allocateJacobiansMultiDof();
}
/*
#ifndef DISABLE_CONSTRAINTS
void MultiBodyConstraint::CreateConstraintRows(MultiBodyConstraintArray^ constraintRows,
	MultiBodyJacobianData^ data, ContactSolverInfo^ infoGlobal)
{
	_native->createConstraintRows(*constraintRows->_native, *data->_native, *(btContactSolverInfo*)infoGlobal->_native);
}
#endif
*/
void MultiBodyConstraint::FinalizeMultiDof()
{
	_native->finalizeMultiDof();
}

btScalar MultiBodyConstraint::GetAppliedImpulse(int dof)
{
	return _native->getAppliedImpulse(dof);
}

btScalar MultiBodyConstraint::GetPosition(int row)
{
	return _native->getPosition(row);
}

void MultiBodyConstraint::InternalSetAppliedImpulse(int dof, btScalar appliedImpulse)
{
	_native->internalSetAppliedImpulse(dof, appliedImpulse);
}
/*
ScalarArray^ MultiBodyConstraint::JacobianA(int row)
{
	return _native->jacobianA(row);
}

ScalarArray^ MultiBodyConstraint::JacobianB(int row)
{
	return _native->jacobianB(row);
}
*/
void MultiBodyConstraint::SetPosition(int row, btScalar pos)
{
	_native->setPosition(row, pos);
}

void MultiBodyConstraint::UpdateJacobianSizes()
{
	_native->updateJacobianSizes();
}

int MultiBodyConstraint::IslandIdA::get()
{
	return _native->getIslandIdA();
}

int MultiBodyConstraint::IslandIdB::get()
{
	return _native->getIslandIdB();
}

bool MultiBodyConstraint::IsUnilateral::get()
{
	return _native->isUnilateral();
}

btScalar MultiBodyConstraint::MaxAppliedImpulse::get()
{
	return _native->getMaxAppliedImpulse();
}
void MultiBodyConstraint::MaxAppliedImpulse::set(btScalar maxImp)
{
	_native->setMaxAppliedImpulse(maxImp);
}

MultiBody^ MultiBodyConstraint::MultiBodyA::get()
{
	return _multiBodyA;
}

MultiBody^ MultiBodyConstraint::MultiBodyB::get()
{
	return _multiBodyB;
}

int MultiBodyConstraint::NumRows::get()
{
	return _native->getNumRows();
}

#endif
