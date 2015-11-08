#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "StringConv.h"
#include "MultiBodyJointFeedback.h"
#include "MultiBodyLink.h"
#include "MultiBodyLinkCollider.h"

MultiBodyLink::MultiBodyLink(btMultibodyLink* native)
{
	_native = native;
}

Vector3 MultiBodyLink::GetAxisBottom(int dof)
{
	return Math::BtVector3ToVector3(&_native->getAxisBottom(dof));
}

Vector3 MultiBodyLink::GetAxisTop(int dof)
{
	return Math::BtVector3ToVector3(&_native->getAxisTop(dof));
}

void MultiBodyLink::SetAxisBottom(int dof, btScalar x, btScalar y, btScalar z)
{
	_native->setAxisBottom(dof, x, y, z);
}

void MultiBodyLink::SetAxisBottom(int dof, Vector3 axis)
{
	VECTOR3_CONV(axis);
	_native->setAxisBottom(dof, VECTOR3_USE(axis));
	VECTOR3_DEL(axis);
}

void MultiBodyLink::SetAxisTop(int dof, btScalar x, btScalar y, btScalar z)
{
	_native->setAxisTop(dof, x, y, z);
}

void MultiBodyLink::SetAxisTop(int dof, Vector3 axis)
{
	VECTOR3_CONV(axis);
	_native->setAxisTop(dof, VECTOR3_USE(axis));
	VECTOR3_DEL(axis);
}

void MultiBodyLink::UpdateCacheMultiDof(array<btScalar>^ pq)
{
	pin_ptr<btScalar> pqPtr = &pq[0];
	_native->updateCacheMultiDof(pqPtr);
}

void MultiBodyLink::UpdateCacheMultiDof()
{
	_native->updateCacheMultiDof();
}
/*
SpatialMotionVector MultiBodyLink::AbsFrameLocVelocity::get()
{
	return _native->m_absFrameLocVelocity;
}
void MultiBodyLink::AbsFrameLocVelocity::set(SpatialMotionVector value)
{
	_native->m_absFrameLocVelocity = value->_native;
}

SpatialMotionVector MultiBodyLink::AbsFrameTotVelocity::get()
{
	return _native->m_absFrameTotVelocity;
}
void MultiBodyLink::AbsFrameTotVelocity::set(SpatialMotionVector value)
{
	_native->m_absFrameTotVelocity = value->_native;
}
*/
Vector3 MultiBodyLink::AppliedConstraintForce::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedConstraintForce);
}
void MultiBodyLink::AppliedConstraintForce::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedConstraintForce);
}

Vector3 MultiBodyLink::AppliedConstraintTorque::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedConstraintTorque);
}
void MultiBodyLink::AppliedConstraintTorque::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedConstraintTorque);
}

Vector3 MultiBodyLink::AppliedForce::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedForce);
}
void MultiBodyLink::AppliedForce::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedForce);
}

Vector3 MultiBodyLink::AppliedTorque::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedTorque);
}
void MultiBodyLink::AppliedTorque::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedTorque);
}
/*
SpatialMotionVector^ MultiBodyLink::Axes::get()
{
	return _native->m_axes;
}
*/
Quaternion MultiBodyLink::CachedRotParentToThis::get()
{
	return Math::BtQuatToQuaternion(&_native->m_cachedRotParentToThis);
}
void MultiBodyLink::CachedRotParentToThis::set(Quaternion value)
{
	Math::QuaternionToBtQuat(value, &_native->m_cachedRotParentToThis);
}

Vector3 MultiBodyLink::CachedRVector::get()
{
	return Math::BtVector3ToVector3(&_native->m_cachedRVector);
}
void MultiBodyLink::CachedRVector::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_cachedRVector);
}

Matrix MultiBodyLink::CachedWorldTransform::get()
{
	return Math::BtTransformToMatrix(&_native->m_cachedWorldTransform);
}
void MultiBodyLink::CachedWorldTransform::set(Matrix value)
{
	Math::MatrixToBtTransform(value, &_native->m_cachedWorldTransform);
}

int MultiBodyLink::CfgOffset::get()
{
	return _native->m_cfgOffset;
}
void MultiBodyLink::CfgOffset::set(int value)
{
	_native->m_cfgOffset = value;
}

MultiBodyLinkCollider^ MultiBodyLink::Collider::get()
{
	return (MultiBodyLinkCollider^)CollisionObject::GetManaged(_native->m_collider);
}
void MultiBodyLink::Collider::set(MultiBodyLinkCollider^ value)
{
	_native->m_collider = (btMultiBodyLinkCollider*)value->_native;
}

int MultiBodyLink::DofCount::get()
{
	return _native->m_dofCount;
}
void MultiBodyLink::DofCount::set(int value)
{
	_native->m_dofCount = value;
}

int MultiBodyLink::DofOffset::get()
{
	return _native->m_dofOffset;
}
void MultiBodyLink::DofOffset::set(int value)
{
	_native->m_dofOffset = value;
}

Vector3 MultiBodyLink::DVector::get()
{
	return Math::BtVector3ToVector3(&_native->m_dVector);
}
void MultiBodyLink::DVector::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_dVector);
}

Vector3 MultiBodyLink::EVector::get()
{
	return Math::BtVector3ToVector3(&_native->m_eVector);
}
void MultiBodyLink::EVector::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_eVector);
}

int MultiBodyLink::Flags::get()
{
	return _native->m_flags;
}
void MultiBodyLink::Flags::set(int value)
{
	_native->m_flags = value;
}

Vector3 MultiBodyLink::InertiaLocal::get()
{
	return Math::BtVector3ToVector3(&_native->m_inertiaLocal);
}
void MultiBodyLink::InertiaLocal::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_inertiaLocal);
}
/*
MultiBodyJointFeedback^ MultiBodyLink::JointFeedback::get()
{
	return _native->m_jointFeedback;
}
void MultiBodyLink::JointFeedback::set(MultiBodyJointFeedback^ value)
{
	_native->m_jointFeedback = value->_native;
}
*/
String^ MultiBodyLink::JointName::get()
{
	return StringConv::UnmanagedToManaged(_native->m_jointName);
}
/*
void MultiBodyLink::JointName::set(String^ value)
{
	_native->m_jointName = value->_native;
}

array<btScalar>^ MultiBodyLink::JointPos::get()
{
	return _native->m_jointPos;
}

array<btScalar>^ MultiBodyLink::JointTorque::get()
{
	return _native->m_jointTorque;
}
*/
FeatherstoneJointType MultiBodyLink::JointType::get()
{
	return (FeatherstoneJointType)_native->m_jointType;
}
void MultiBodyLink::JointType::set(FeatherstoneJointType value)
{
	_native->m_jointType = (btMultibodyLink::eFeatherstoneJointType)value;
}

String^ MultiBodyLink::LinkName::get()
{
	return StringConv::UnmanagedToManaged(_native->m_linkName);
}
/*
void MultiBodyLink::LinkName::set(String^ value)
{
	_native->m_linkName = value->_native;
}
*/
btScalar MultiBodyLink::Mass::get()
{
	return _native->m_mass;
}
void MultiBodyLink::Mass::set(btScalar value)
{
	_native->m_mass = value;
}

int MultiBodyLink::Parent::get()
{
	return _native->m_parent;
}
void MultiBodyLink::Parent::set(int value)
{
	_native->m_parent = value;
}

int MultiBodyLink::PosVarCount::get()
{
	return _native->m_posVarCount;
}
void MultiBodyLink::PosVarCount::set(int value)
{
	_native->m_posVarCount = value;
}

Quaternion MultiBodyLink::ZeroRotParentToThis::get()
{
	return Math::BtQuatToQuaternion(&_native->m_zeroRotParentToThis);
}
void MultiBodyLink::ZeroRotParentToThis::set(Quaternion value)
{
	Math::QuaternionToBtQuat(value, &_native->m_zeroRotParentToThis);
}

#endif
