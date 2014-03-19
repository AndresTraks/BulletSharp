#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "Collections.h"
#include "MultiBodyLink.h"
#include "MultiBodyLinkCollider.h"

MultibodyLink::MultibodyLink(btMultibodyLink* native)
{
	_native = native;
}

MultibodyLink::MultibodyLink()
{
	_native = new btMultibodyLink();
}

Vector3 MultibodyLink::GetAxisBottom(int dof)
{
	return Math::BtVector3ToVector3(&_native->getAxisBottom(dof));
}

Vector3 MultibodyLink::GetAxisTop(int dof)
{
	return Math::BtVector3ToVector3(&_native->getAxisTop(dof));
}

void MultibodyLink::SetAxisBottom(int dof, Vector3 axis)
{
	VECTOR3_DEF(axis);
	_native->setAxisBottom(dof, VECTOR3_USE(axis));
	VECTOR3_DEL(axis);
}

void MultibodyLink::SetAxisBottom(int dof, float x, float y, float z)
{
	_native->setAxisBottom(dof, x, y, z);
}

void MultibodyLink::SetAxisTop(int dof, Vector3 axis)
{
	VECTOR3_DEF(axis);
	_native->setAxisTop(dof, VECTOR3_USE(axis));
	VECTOR3_DEL(axis);
}

void MultibodyLink::SetAxisTop(int dof, float x, float y, float z)
{
	_native->setAxisTop(dof, x, y, z);
}

void MultibodyLink::UpdateCache()
{
	_native->updateCache();
}

void MultibodyLink::UpdateCacheMultiDof(FloatArray^ pq)
{
	_native->updateCacheMultiDof((btScalar*)pq->_native);
}

void MultibodyLink::UpdateCacheMultiDof()
{
	_native->updateCacheMultiDof();
}

Vector3 MultibodyLink::AppliedForce::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedForce);
}
void MultibodyLink::AppliedForce::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedForce);
}

Vector3 MultibodyLink::AppliedTorque::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedTorque);
}
void MultibodyLink::AppliedTorque::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedTorque);
}
/*
SpatialMotionVector^ MultibodyLink::Axes::get()
{
	return gcnew SpatialMotionVector(&_native->m_axes);
}
void MultibodyLink::Axes::set(SpatialMotionVector^ value)
{
	_native->m_axes = value->_native;
}
*/
Quaternion MultibodyLink::CachedRotParentToThis::get()
{
	return Math::BtQuatToQuaternion(&_native->m_cachedRotParentToThis);
}
void MultibodyLink::CachedRotParentToThis::set(Quaternion value)
{
	Math::QuaternionToBtQuat(value, &_native->m_cachedRotParentToThis);
}

Vector3 MultibodyLink::CachedRVector::get()
{
	return Math::BtVector3ToVector3(&_native->m_cachedRVector);
}
void MultibodyLink::CachedRVector::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_cachedRVector);
}

int MultibodyLink::CfgOffset::get()
{
	return _native->m_cfgOffset;
}
void MultibodyLink::CfgOffset::set(int value)
{
	_native->m_cfgOffset = value;
}

MultiBodyLinkCollider^ MultibodyLink::Collider::get()
{
	return static_cast<MultiBodyLinkCollider^>(CollisionObject::GetManaged(_native->m_collider));
}
void MultibodyLink::Collider::set(MultiBodyLinkCollider^ value)
{
	_native->m_collider = (btMultiBodyLinkCollider*)value->_native;
}

int MultibodyLink::DofCount::get()
{
	return _native->m_dofCount;
}
void MultibodyLink::DofCount::set(int value)
{
	_native->m_dofCount = value;
}

int MultibodyLink::DofOffset::get()
{
	return _native->m_dofOffset;
}
void MultibodyLink::DofOffset::set(int value)
{
	_native->m_dofOffset = value;
}

Vector3 MultibodyLink::DVector::get()
{
	return Math::BtVector3ToVector3(&_native->m_dVector);
}
void MultibodyLink::DVector::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_dVector);
}

Vector3 MultibodyLink::EVector::get()
{
	return Math::BtVector3ToVector3(&_native->m_eVector);
}
void MultibodyLink::EVector::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_eVector);
}

int MultibodyLink::Flags::get()
{
	return _native->m_flags;
}
void MultibodyLink::Flags::set(int value)
{
	_native->m_flags = value;
}

Vector3 MultibodyLink::Inertia::get()
{
	return Math::BtVector3ToVector3(&_native->m_inertia);
}
void MultibodyLink::Inertia::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_inertia);
}
/*
float^ MultibodyLink::JointPos::get()
{
	return _native->m_jointPos;
}
void MultibodyLink::JointPos::set(float^ value)
{
	_native->m_jointPos = value->_native;
}

float^ MultibodyLink::JointTorque::get()
{
	return _native->m_jointTorque;
}
void MultibodyLink::JointTorque::set(float^ value)
{
	_native->m_jointTorque = value->_native;
}
*/
FeatherstoneJointType MultibodyLink::JointType::get()
{
	return (FeatherstoneJointType)_native->m_jointType;
}
void MultibodyLink::JointType::set(FeatherstoneJointType value)
{
	_native->m_jointType = (btMultibodyLink::eFeatherstoneJointType)value;
}

btScalar MultibodyLink::Mass::get()
{
	return _native->m_mass;
}
void MultibodyLink::Mass::set(btScalar value)
{
	_native->m_mass = value;
}

int MultibodyLink::Parent::get()
{
	return _native->m_parent;
}
void MultibodyLink::Parent::set(int value)
{
	_native->m_parent = value;
}

int MultibodyLink::PosVarCount::get()
{
	return _native->m_posVarCount;
}
void MultibodyLink::PosVarCount::set(int value)
{
	_native->m_posVarCount = value;
}

Quaternion MultibodyLink::ZeroRotParentToThis::get()
{
	return Math::BtQuatToQuaternion(&_native->m_zeroRotParentToThis);
}
void MultibodyLink::ZeroRotParentToThis::set(Quaternion value)
{
	Math::QuaternionToBtQuat(value, &_native->m_zeroRotParentToThis);
}

#endif
