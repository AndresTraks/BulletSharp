#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "AlignedObjectArray.h"
#include "MultiBody.h"
#include "MultiBodyConstraint.h"
/*
MultiBodyJacobianData::MultiBodyJacobianData(btMultiBodyJacobianData* native)
{
	_native = native;
}

MultiBodyJacobianData::MultiBodyJacobianData()
{
	_native->btMultiBodyJacobianData();
}

AlignedScalarArray^ MultiBodyJacobianData::GetDeltaVelocities()
{
	_native->getDeltaVelocities();
}

AlignedScalarArray^ MultiBodyJacobianData::GetDeltaVelocitiesUnitImpulse()
{
	_native->getDeltaVelocitiesUnitImpulse();
}

int MultiBodyJacobianData::GetFixedBodyId()
{
	_native->getFixedBodyId();
}

AlignedScalarArray^ MultiBodyJacobianData::GetJacobians()
{
	_native->getJacobians();
}

AlignedObjectArray<btMatrix3x3> MultiBodyJacobianData::GetScratch_m()
{
	_native->getScratch_m();
}

AlignedScalarArray^ MultiBodyJacobianData::GetScratch_r()
{
	_native->getScratch_r();
}

AlignedObjectArray<btVector3> MultiBodyJacobianData::GetScratch_v()
{
	_native->getScratch_v();
}

AlignedObjectArray^ MultiBodyJacobianData::GetSolverBodyPool()
{
	_native->getSolverBodyPool();
}

void MultiBodyJacobianData::SetDeltaVelocities(AlignedScalarArray^ value)
{
	_native->setDeltaVelocities(value->_native);
}

void MultiBodyJacobianData::SetDeltaVelocitiesUnitImpulse(AlignedScalarArray^ value)
{
	_native->setDeltaVelocitiesUnitImpulse(value->_native);
}

void MultiBodyJacobianData::SetFixedBodyId(int value)
{
	_native->setFixedBodyId(value);
}

void MultiBodyJacobianData::SetJacobians(AlignedScalarArray^ value)
{
	_native->setJacobians(value->_native);
}

void MultiBodyJacobianData::SetScratch_m(AlignedObjectArray<btMatrix3x3> value)
{
	_native->setScratch_m(value->_native);
}

void MultiBodyJacobianData::SetScratch_r(AlignedScalarArray^ value)
{
	_native->setScratch_r(value->_native);
}

void MultiBodyJacobianData::SetScratch_v(AlignedObjectArray<btVector3> value)
{
	_native->setScratch_v(value->_native);
}

void MultiBodyJacobianData::SetSolverBodyPool(AlignedObjectArray^ value)
{
	_native->setSolverBodyPool(value->_native);
}

AlignedScalarArray^ MultiBodyJacobianData::deltaVelocities::get()
{
	return _native->getDeltaVelocities();
}
void MultiBodyJacobianData::deltaVelocities::set(AlignedScalarArray^ value)
{
	_native->setDeltaVelocities(value->_native);
}

AlignedScalarArray^ MultiBodyJacobianData::deltaVelocitiesUnitImpulse::get()
{
	return _native->getDeltaVelocitiesUnitImpulse();
}
void MultiBodyJacobianData::deltaVelocitiesUnitImpulse::set(AlignedScalarArray^ value)
{
	_native->setDeltaVelocitiesUnitImpulse(value->_native);
}

int MultiBodyJacobianData::fixedBodyId::get()
{
	return _native->getFixedBodyId();
}
void MultiBodyJacobianData::fixedBodyId::set(int value)
{
	_native->setFixedBodyId(value);
}

AlignedScalarArray^ MultiBodyJacobianData::jacobians::get()
{
	return _native->getJacobians();
}
void MultiBodyJacobianData::jacobians::set(AlignedScalarArray^ value)
{
	_native->setJacobians(value->_native);
}

AlignedObjectArray<btMatrix3x3> MultiBodyJacobianData::scratch_m::get()
{
	return _native->getScratch_m();
}
void MultiBodyJacobianData::scratch_m::set(AlignedObjectArray<btMatrix3x3> value)
{
	_native->setScratch_m(value->_native);
}

AlignedScalarArray^ MultiBodyJacobianData::scratch_r::get()
{
	return _native->getScratch_r();
}
void MultiBodyJacobianData::scratch_r::set(AlignedScalarArray^ value)
{
	_native->setScratch_r(value->_native);
}

AlignedObjectArray<btVector3> MultiBodyJacobianData::scratch_v::get()
{
	return _native->getScratch_v();
}
void MultiBodyJacobianData::scratch_v::set(AlignedObjectArray<btVector3> value)
{
	_native->setScratch_v(value->_native);
}

AlignedObjectArray^ MultiBodyJacobianData::solverBodyPool::get()
{
	return _native->getSolverBodyPool();
}
void MultiBodyJacobianData::solverBodyPool::set(AlignedObjectArray^ value)
{
	_native->setSolverBodyPool(value->_native);
}
*/

MultiBodyConstraint::MultiBodyConstraint(btMultiBodyConstraint* native)
{
	_native = native;
}
/*
void MultiBodyConstraint::CreateConstraintRows(MultiBodyConstraintArray^ constraintRows, MultiBodyJacobianData^ data, ContactSolverInfo^ infoGlobal)
{
	_native->createConstraintRows(constraintRows->_native, data->_native, infoGlobal->_native);
}
*/
float MultiBodyConstraint::GetPosition(int row)
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
void MultiBodyConstraint::SetMaxAppliedImpulse(float maxImp)
{
	_native->setMaxAppliedImpulse(maxImp);
}

void MultiBodyConstraint::SetPosition(int row, float pos)
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

float MultiBodyConstraint::MaxAppliedImpulse::get()
{
	return _native->getMaxAppliedImpulse();
}
void MultiBodyConstraint::MaxAppliedImpulse::set(float maxImp)
{
	_native->setMaxAppliedImpulse(maxImp);
}

MultiBody^ MultiBodyConstraint::MultiBodyA::get()
{
	return gcnew MultiBody(_native->getMultiBodyA());
}

MultiBody^ MultiBodyConstraint::MultiBodyB::get()
{
	return gcnew MultiBody(_native->getMultiBodyB());
}

int MultiBodyConstraint::NumRows::get()
{
	return _native->getNumRows();
}

#endif