#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "CharacterControllerInterface.h"
#include "CollisionWorld.h"

#define Native (static_cast<btCharacterControllerInterface*>(_native))

CharacterControllerInterface::CharacterControllerInterface(btCharacterControllerInterface* controllerInterface)
: ActionInterface(controllerInterface)
{
}

void CharacterControllerInterface::PlayerStep(CollisionWorld^ collisionWorld, btScalar dt)
{
	Native->playerStep(collisionWorld->_native, dt);
}

void CharacterControllerInterface::Jump()
{
	Native->jump();
}

void CharacterControllerInterface::Reset()
{
	Native->reset();
}

void CharacterControllerInterface::SetVelocityForTimeInterval(Vector3 velocity, btScalar timeInterval)
{
	VECTOR3_DEF(velocity);
	Native->setVelocityForTimeInterval(VECTOR3_USE(velocity), timeInterval);
	VECTOR3_DEL(velocity);
}

void CharacterControllerInterface::SetWalkDirection(Vector3 walkDirection)
{
	VECTOR3_DEF(walkDirection);
	Native->setWalkDirection(VECTOR3_USE(walkDirection));
	VECTOR3_DEL(walkDirection);
}

void CharacterControllerInterface::Warp(Vector3 origin)
{
	VECTOR3_DEF(origin);
	Native->warp(VECTOR3_USE(origin));
	VECTOR3_DEL(origin);
}

bool CharacterControllerInterface::CanJump::get()
{
	return Native->canJump();
}

bool CharacterControllerInterface::OnGround::get()
{
	return Native->onGround();
}

#endif
