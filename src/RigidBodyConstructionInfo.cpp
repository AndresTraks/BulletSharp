#include "StdAfx.h"

#include "RigidBodyConstructionInfo.h"

btRigidBody::btRigidBodyConstructionInfo* RigidBody_GetUnmanagedConstructionInfo(
	btScalar mass, btMotionState* motionState, btCollisionShape* collisionShape, btVector3* localInertia = new btVector3())
{
	return new btRigidBody::btRigidBodyConstructionInfo(mass, motionState, collisionShape, *localInertia);
}

RigidBodyConstructionInfo::RigidBodyConstructionInfo(btScalar mass, MotionState^ motionState, CollisionShape^ collisionShape)
{
	if (collisionShape != nullptr)
		_info = RigidBody_GetUnmanagedConstructionInfo(mass, motionState->UnmanagedPointer, collisionShape->UnmanagedPointer);
	else
		_info = RigidBody_GetUnmanagedConstructionInfo(mass, motionState->UnmanagedPointer, nullptr);
	_collisionShape = collisionShape;
	_motionState = motionState;
}

RigidBodyConstructionInfo::RigidBodyConstructionInfo(btScalar mass, MotionState^ motionState, CollisionShape^ collisionShape, Vector3 localInertia)
{
	if (collisionShape != nullptr)
		_info = RigidBody_GetUnmanagedConstructionInfo(mass, motionState->UnmanagedPointer, collisionShape->UnmanagedPointer, Math::Vector3ToBtVec3(localInertia));
	else
		_info = RigidBody_GetUnmanagedConstructionInfo(mass, motionState->UnmanagedPointer, nullptr, Math::Vector3ToBtVec3(localInertia));
	_collisionShape = collisionShape;
	_motionState = motionState;
}

btScalar RigidBodyConstructionInfo::Mass::get()
{
	return _info->m_mass;
}
void RigidBodyConstructionInfo::Mass::set(btScalar mass)
{
	_info->m_mass = mass;
}

btRigidBody::btRigidBodyConstructionInfo* RigidBodyConstructionInfo::UnmanagedPointer::get()
{
	return _info;
}
