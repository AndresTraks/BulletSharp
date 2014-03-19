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
	_native = new btMultiBodyJacobianData();
}

AlignedScalarArray^ MultiBodyJacobianData::DeltaVelocities::get()
{
	return _native->m_deltaVelocities;
}
void MultiBodyJacobianData::DeltaVelocities::set(AlignedScalarArray^ value)
{
	_native->m_deltaVelocities = value->_native;
}

AlignedScalarArray^ MultiBodyJacobianData::DeltaVelocitiesUnitImpulse::get()
{
	return _native->m_deltaVelocitiesUnitImpulse;
}
void MultiBodyJacobianData::DeltaVelocitiesUnitImpulse::set(AlignedScalarArray^ value)
{
	_native->m_deltaVelocitiesUnitImpulse = value->_native;
}

int MultiBodyJacobianData::FixedBodyId::get()
{
	return _native->m_fixedBodyId;
}
void MultiBodyJacobianData::FixedBodyId::set(int value)
{
	_native->m_fixedBodyId = value;
}

AlignedScalarArray^ MultiBodyJacobianData::Jacobians::get()
{
	return _native->m_jacobians;
}
void MultiBodyJacobianData::Jacobians::set(AlignedScalarArray^ value)
{
	_native->m_jacobians = value->_native;
}

AlignedMatrix3x3Array^ MultiBodyJacobianData::ScratchM::get()
{
	return _native->scratch_m;
}
void MultiBodyJacobianData::ScratchM::set(AlignedMatrix3x3Array^ value)
{
	_native->scratch_m = value->_native;
}

AlignedScalarArray^ MultiBodyJacobianData::ScratchR::get()
{
	return _native->scratch_r;
}
void MultiBodyJacobianData::ScratchR::set(AlignedScalarArray^ value)
{
	_native->scratch_r = value->_native;
}

AlignedVector3Array^ MultiBodyJacobianData::ScratchV::get()
{
	return _native->scratch_v;
}
void MultiBodyJacobianData::ScratchV::set(AlignedVector3Array^ value)
{
	_native->scratch_v = value->_native;
}

AlignedObjectArray^ MultiBodyJacobianData::SolverBodyPool::get()
{
	return _native->m_solverBodyPool;
}
void MultiBodyJacobianData::SolverBodyPool::set(AlignedObjectArray^ value)
{
	_native->m_solverBodyPool = value->_native;
}
*/


MultiBodyConstraint::MultiBodyConstraint(btMultiBodyConstraint* native)
{
	_native = native;
}
/*
void MultiBodyConstraint::CreateConstraintRows(MultiBodyConstraintArray^ constraintRows,
	MultiBodyJacobianData^ data, ContactSolverInfo^ infoGlobal)
{
	_native->createConstraintRows(*constraintRows->_native, *data->_native, *(btContactSolverInfo*)infoGlobal->_native);
}
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