#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "CharacterControllerInterface.h"
#include "CollisionWorld.h"

CharacterControllerInterface::CharacterControllerInterface(btCharacterControllerInterface* controllerInterface)
: ActionInterface(controllerInterface)
{
}

void CharacterControllerInterface::PlayerStep(CollisionWorld^ collisionWorld, btScalar dt)
{
	UnmanagedPointer->playerStep(collisionWorld->UnmanagedPointer, dt);
}

void CharacterControllerInterface::Jump()
{
	UnmanagedPointer->jump();
}

void CharacterControllerInterface::Reset()
{
	UnmanagedPointer->reset();
}

void CharacterControllerInterface::SetVelocityForTimeInterval(Vector3 velocity, btScalar timeInterval)
{
	VECTOR3_DEF(velocity);
	UnmanagedPointer->setVelocityForTimeInterval(VECTOR3_USE(velocity), timeInterval);
	VECTOR3_DEL(velocity);
}

void CharacterControllerInterface::SetWalkDirection(Vector3 walkDirection)
{
	VECTOR3_DEF(walkDirection);
	UnmanagedPointer->setWalkDirection(VECTOR3_USE(walkDirection));
	VECTOR3_DEL(walkDirection);
}

void CharacterControllerInterface::Warp(Vector3 origin)
{
	VECTOR3_DEF(origin);
	UnmanagedPointer->warp(VECTOR3_USE(origin));
	VECTOR3_DEL(origin);
}

bool CharacterControllerInterface::CanJump::get()
{
	return UnmanagedPointer->canJump();
}

bool CharacterControllerInterface::OnGround::get()
{
	return UnmanagedPointer->onGround();
}

btCharacterControllerInterface* CharacterControllerInterface::UnmanagedPointer::get()
{
	return (btCharacterControllerInterface*)ActionInterface::UnmanagedPointer;
}

#endif
