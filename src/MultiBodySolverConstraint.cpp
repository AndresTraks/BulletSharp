#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "MultiBody.h"
#include "MultiBodySolverConstraint.h"

MultiBodySolverConstraint::MultiBodySolverConstraint(btMultiBodySolverConstraint* native)
{
	_native = native;
}

MultiBodySolverConstraint::~MultiBodySolverConstraint()
{
	this->!MultiBodySolverConstraint();
}

MultiBodySolverConstraint::!MultiBodySolverConstraint()
{
	delete _native;
	_native = NULL;
}

MultiBodySolverConstraint::MultiBodySolverConstraint()
{
	_native = new btMultiBodySolverConstraint();
}

Vector3 MultiBodySolverConstraint::AngularComponentA::get()
{
	return Math::BtVector3ToVector3(&_native->m_angularComponentA);
}
void MultiBodySolverConstraint::AngularComponentA::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_angularComponentA);
}

Vector3 MultiBodySolverConstraint::AngularComponentB::get()
{
	return Math::BtVector3ToVector3(&_native->m_angularComponentB);
}
void MultiBodySolverConstraint::AngularComponentB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_angularComponentB);
}

btScalar MultiBodySolverConstraint::AppliedImpulse::get()
{
	return _native->m_appliedImpulse;
}/*
void MultiBodySolverConstraint::AppliedImpulse::set(btScalar value)
{
	_native->m_appliedImpulse = value;
}
*/
btScalar MultiBodySolverConstraint::AppliedPushImpulse::get()
{
	return _native->m_appliedPushImpulse;
}/*
void MultiBodySolverConstraint::AppliedPushImpulse::set(btScalar value)
{
	_native->m_appliedPushImpulse = value;
}
*/
btScalar MultiBodySolverConstraint::Cfm::get()
{
	return _native->m_cfm;
}
void MultiBodySolverConstraint::Cfm::set(btScalar value)
{
	_native->m_cfm = value;
}

Vector3 MultiBodySolverConstraint::ContactNormal1::get()
{
	return Math::BtVector3ToVector3(&_native->m_contactNormal1);
}
void MultiBodySolverConstraint::ContactNormal1::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_contactNormal1);
}

Vector3 MultiBodySolverConstraint::ContactNormal2::get()
{
	return Math::BtVector3ToVector3(&_native->m_contactNormal2);
}
void MultiBodySolverConstraint::ContactNormal2::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_contactNormal2);
}

int MultiBodySolverConstraint::DeltaVelAindex::get()
{
	return _native->m_deltaVelAindex;
}
void MultiBodySolverConstraint::DeltaVelAindex::set(int value)
{
	_native->m_deltaVelAindex = value;
}

int MultiBodySolverConstraint::DeltaVelBindex::get()
{
	return _native->m_deltaVelBindex;
}
void MultiBodySolverConstraint::DeltaVelBindex::set(int value)
{
	_native->m_deltaVelBindex = value;
}

btScalar MultiBodySolverConstraint::Friction::get()
{
	return _native->m_friction;
}
void MultiBodySolverConstraint::Friction::set(btScalar value)
{
	_native->m_friction = value;
}

int MultiBodySolverConstraint::FrictionIndex::get()
{
	return _native->m_frictionIndex;
}
void MultiBodySolverConstraint::FrictionIndex::set(int value)
{
	_native->m_frictionIndex = value;
}

int MultiBodySolverConstraint::JacAindex::get()
{
	return _native->m_jacAindex;
}
void MultiBodySolverConstraint::JacAindex::set(int value)
{
	_native->m_jacAindex = value;
}

int MultiBodySolverConstraint::JacBindex::get()
{
	return _native->m_jacBindex;
}
void MultiBodySolverConstraint::JacBindex::set(int value)
{
	_native->m_jacBindex = value;
}

btScalar MultiBodySolverConstraint::JacDiagABInv::get()
{
	return _native->m_jacDiagABInv;
}
void MultiBodySolverConstraint::JacDiagABInv::set(btScalar value)
{
	_native->m_jacDiagABInv = value;
}

int MultiBodySolverConstraint::LinkA::get()
{
	return _native->m_linkA;
}
void MultiBodySolverConstraint::LinkA::set(int value)
{
	_native->m_linkA = value;
}

int MultiBodySolverConstraint::LinkB::get()
{
	return _native->m_linkB;
}
void MultiBodySolverConstraint::LinkB::set(int value)
{
	_native->m_linkB = value;
}

btScalar MultiBodySolverConstraint::LowerLimit::get()
{
	return _native->m_lowerLimit;
}
void MultiBodySolverConstraint::LowerLimit::set(btScalar value)
{
	_native->m_lowerLimit = value;
}

MultiBody^ MultiBodySolverConstraint::MultiBodyA::get()
{
	if (_multiBodyA == nullptr) {
		_multiBodyA = gcnew MultiBody(_native->m_multiBodyA);
	}
	return _multiBodyA;
}
void MultiBodySolverConstraint::MultiBodyA::set(MultiBody^ value)
{
	_multiBodyA = value;
	_native->m_multiBodyA = value->_native;
}

MultiBody^ MultiBodySolverConstraint::MultiBodyB::get()
{
	if (_multiBodyB == nullptr) {
		_multiBodyB = gcnew MultiBody(_native->m_multiBodyB);
	}
	return _multiBodyB;
}
void MultiBodySolverConstraint::MultiBodyB::set(MultiBody^ value)
{
	_multiBodyB = value;
	_native->m_multiBodyB = value->_native;
}
/*
MultiBodyConstraint^ MultiBodySolverConstraint::OrgConstraint::get()
{
	return _native->m_orgConstraint;
}
void MultiBodySolverConstraint::OrgConstraint::set(MultiBodyConstraint^ value)
{
	_native->m_orgConstraint = value->_native;
}
*/
int MultiBodySolverConstraint::OrgDofIndex::get()
{
	return _native->m_orgDofIndex;
}
void MultiBodySolverConstraint::OrgDofIndex::set(int value)
{
	_native->m_orgDofIndex = value;
}

IntPtr MultiBodySolverConstraint::OriginalContactPoint::get()
{
	return IntPtr(_native->m_originalContactPoint);
}
void MultiBodySolverConstraint::OriginalContactPoint::set(IntPtr value)
{
	_native->m_originalContactPoint = value.ToPointer();
}

int MultiBodySolverConstraint::OverrideNumSolverIterations::get()
{
	return _native->m_overrideNumSolverIterations;
}
void MultiBodySolverConstraint::OverrideNumSolverIterations::set(int value)
{
	_native->m_overrideNumSolverIterations = value;
}

Vector3 MultiBodySolverConstraint::Relpos1CrossNormal::get()
{
	return Math::BtVector3ToVector3(&_native->m_relpos1CrossNormal);
}
void MultiBodySolverConstraint::Relpos1CrossNormal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_relpos1CrossNormal);
}

Vector3 MultiBodySolverConstraint::Relpos2CrossNormal::get()
{
	return Math::BtVector3ToVector3(&_native->m_relpos2CrossNormal);
}
void MultiBodySolverConstraint::Relpos2CrossNormal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_relpos2CrossNormal);
}

btScalar MultiBodySolverConstraint::Rhs::get()
{
	return _native->m_rhs;
}
void MultiBodySolverConstraint::Rhs::set(btScalar value)
{
	_native->m_rhs = value;
}

btScalar MultiBodySolverConstraint::RhsPenetration::get()
{
	return _native->m_rhsPenetration;
}
void MultiBodySolverConstraint::RhsPenetration::set(btScalar value)
{
	_native->m_rhsPenetration = value;
}

int MultiBodySolverConstraint::SolverBodyIdA::get()
{
	return _native->m_solverBodyIdA;
}
void MultiBodySolverConstraint::SolverBodyIdA::set(int value)
{
	_native->m_solverBodyIdA = value;
}

int MultiBodySolverConstraint::SolverBodyIdB::get()
{
	return _native->m_solverBodyIdB;
}
void MultiBodySolverConstraint::SolverBodyIdB::set(int value)
{
	_native->m_solverBodyIdB = value;
}

btScalar MultiBodySolverConstraint::UpperLimit::get()
{
	return _native->m_upperLimit;
}
void MultiBodySolverConstraint::UpperLimit::set(btScalar value)
{
	_native->m_upperLimit = value;
}

#endif
