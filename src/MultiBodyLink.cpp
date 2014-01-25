#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

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

void MultibodyLink::UpdateCache()
{
	_native->updateCache();
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
Vector3 MultibodyLink::AxesBottom::get()
{
	return Math::BtVector3ToVector3(&_native->m_axesBottom);
}
void MultibodyLink::AxesBottom::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_axesBottom);
}

Vector3 MultibodyLink::AxesTop::get()
{
	return Math::BtVector3ToVector3(&_native->m_axesTop);
}
void MultibodyLink::AxesTop::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_axesTop);
}
*/
Quaternion MultibodyLink::CachedRotParentToThis::get()
{
	return Math::BtQuatToQuaternion(&_native->m_cachedRotParentToThis);
}
void MultibodyLink::CachedRotParentToThis::set(Quaternion value)
{
	return Math::QuaternionToBt(value, &_native->m_cachedRotParentToThis);
}

Vector3 MultibodyLink::CachedRVector::get()
{
	return Math::BtVector3ToVector3(&_native->m_cachedRVector);
}
void MultibodyLink::CachedRVector::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_cachedRVector);
}

MultiBodyLinkCollider^ MultibodyLink::Collider::get()
{
	return (MultiBodyLinkCollider^)CollisionObject::GetManaged(_native->m_collider);
}
void MultibodyLink::Collider::set(MultiBodyLinkCollider^ value)
{
	_native->m_collider = (btMultiBodyLinkCollider*)value->_native;
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
float MultibodyLink::JointPos::get()
{
	return _native->m_jointPos;
}
void MultibodyLink::JointPos::set(float value)
{
	_native->m_jointPos = value;
}

float MultibodyLink::JointTorque::get()
{
	return _native->m_jointTorque;
}
void MultibodyLink::JointTorque::set(float value)
{
	_native->m_jointTorque = value;
}
*/
float MultibodyLink::Mass::get()
{
	return _native->m_mass;
}
void MultibodyLink::Mass::set(float value)
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

Quaternion MultibodyLink::ZeroRotParentToThis::get()
{
	return Math::BtQuatToQuaternion(&_native->m_zeroRotParentToThis);
}
void MultibodyLink::ZeroRotParentToThis::set(Quaternion value)
{
	return Math::QuaternionToBt(value, &_native->m_zeroRotParentToThis);
}

#endif
