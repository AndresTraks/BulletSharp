#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "CharacterControllerInterface.h"
#include "CollisionWorld.h"

#define Unmanaged (static_cast<btCharacterControllerInterface*>(_unmanaged))

CharacterControllerInterface::CharacterControllerInterface(btCharacterControllerInterface* controllerInterface)
: ActionInterface(controllerInterface)
{
}

void CharacterControllerInterface::PlayerStep(CollisionWorld^ collisionWorld, btScalar dt)
{
	Unmanaged->playerStep(collisionWorld->UnmanagedPointer, dt);
}

void CharacterControllerInterface::Jump()
{
	Unmanaged->jump();
}

void CharacterControllerInterface::Reset()
{
	Unmanaged->reset();
}

void CharacterControllerInterface::SetVelocityForTimeInterval(Vector3 velocity, btScalar timeInterval)
{
	VECTOR3_DEF(velocity);
	Unmanaged->setVelocityForTimeInterval(VECTOR3_USE(velocity), timeInterval);
	VECTOR3_DEL(velocity);
}

void CharacterControllerInterface::SetWalkDirection(Vector3 walkDirection)
{
	VECTOR3_DEF(walkDirection);
	Unmanaged->setWalkDirection(VECTOR3_USE(walkDirection));
	VECTOR3_DEL(walkDirection);
}

void CharacterControllerInterface::Warp(Vector3 origin)
{
	VECTOR3_DEF(origin);
	Unmanaged->warp(VECTOR3_USE(origin));
	VECTOR3_DEL(origin);
}

bool CharacterControllerInterface::CanJump::get()
{
	return Unmanaged->canJump();
}

bool CharacterControllerInterface::OnGround::get()
{
	return Unmanaged->onGround();
}

#endif
