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
	return Math::BtVector3ToVector3(&_native->applied_force);
}
void MultibodyLink::AppliedForce::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->applied_force);
}

Vector3 MultibodyLink::AppliedTorque::get()
{
	return Math::BtVector3ToVector3(&_native->applied_torque);
}
void MultibodyLink::AppliedTorque::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->applied_torque);
}

Vector3 MultibodyLink::AxisBottom::get()
{
	return Math::BtVector3ToVector3(&_native->axis_bottom);
}
void MultibodyLink::AxisBottom::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->axis_bottom);
}

Vector3 MultibodyLink::AxisTop::get()
{
	return Math::BtVector3ToVector3(&_native->axis_top);
}
void MultibodyLink::AxisTop::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->axis_top);
}

Quaternion MultibodyLink::CachedRotParentToThis::get()
{
	return Math::BtQuatToQuaternion(&_native->cached_rot_parent_to_this);
}
void MultibodyLink::CachedRotParentToThis::set(Quaternion value)
{
	return Math::QuaternionToBt(value, &_native->cached_rot_parent_to_this);
}

Vector3 MultibodyLink::CachedRVector::get()
{
	return Math::BtVector3ToVector3(&_native->cached_r_vector);
}
void MultibodyLink::CachedRVector::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->cached_r_vector);
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
	return Math::BtVector3ToVector3(&_native->d_vector);
}
void MultibodyLink::DVector::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->d_vector);
}

Vector3 MultibodyLink::EVector::get()
{
	return Math::BtVector3ToVector3(&_native->e_vector);
}
void MultibodyLink::EVector::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->e_vector);
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
	return Math::BtVector3ToVector3(&_native->inertia);
}
void MultibodyLink::Inertia::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->inertia);
}

bool MultibodyLink::IsRevolute::get()
{
	return _native->is_revolute;
}
void MultibodyLink::IsRevolute::set(bool value)
{
	_native->is_revolute = value;
}

float MultibodyLink::JointPos::get()
{
	return _native->joint_pos;
}
void MultibodyLink::JointPos::set(float value)
{
	_native->joint_pos = value;
}

float MultibodyLink::JointTorque::get()
{
	return _native->joint_torque;
}
void MultibodyLink::JointTorque::set(float value)
{
	_native->joint_torque = value;
}

float MultibodyLink::Mass::get()
{
	return _native->mass;
}
void MultibodyLink::Mass::set(float value)
{
	_native->mass = value;
}

int MultibodyLink::Parent::get()
{
	return _native->parent;
}
void MultibodyLink::Parent::set(int value)
{
	_native->parent = value;
}

Quaternion MultibodyLink::ZeroRotParentToThis::get()
{
	return Math::BtQuatToQuaternion(&_native->zero_rot_parent_to_this);
}
void MultibodyLink::ZeroRotParentToThis::set(Quaternion value)
{
	return Math::QuaternionToBt(value, &_native->zero_rot_parent_to_this);
}

#endif
