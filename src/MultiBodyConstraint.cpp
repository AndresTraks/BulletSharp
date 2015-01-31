#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "AlignedObjectArray.h"
#include "MultiBody.h"
#include "MultiBodyConstraint.h"

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
/*
#ifndef DISABLE_CONSTRAINTS
void MultiBodyConstraint::CreateConstraintRows(MultiBodyConstraintArray^ constraintRows,
	MultiBodyJacobianData^ data, ContactSolverInfo^ infoGlobal)
{
	_native->createConstraintRows(*constraintRows->_native, *data->_native, *(btContactSolverInfo*)infoGlobal->_native);
}
#endif
*/
btScalar MultiBodyConstraint::GetPosition(int row)
{
	return _native->getPosition(row);
}
/*
FloatArray^ MultiBodyConstraint::JacobianA(int row)
{
	_native->jacobianA(row);
}

FloatArray^ MultiBodyConstraint::JacobianB(int row)
{
	_native->jacobianB(row);
}
*/
void MultiBodyConstraint::SetPosition(int row, btScalar pos)
{
	_native->setPosition(row, pos);
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
