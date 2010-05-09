#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletDynamics/Character/btCharacterControllerInterface.h>
#pragma managed(pop)

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
	btVector3* velocityTemp = Math::Vector3ToBtVector3(velocity);
	UnmanagedPointer->setVelocityForTimeInterval(*velocityTemp, timeInterval);
	delete velocityTemp;
}

void CharacterControllerInterface::SetWalkDirection(Vector3 walkDirection)
{
	btVector3* walkDirectionTemp = Math::Vector3ToBtVector3(walkDirection);
	UnmanagedPointer->setWalkDirection(*walkDirectionTemp);
	delete walkDirectionTemp;
}

void CharacterControllerInterface::Warp(Vector3 origin)
{
	btVector3* originTemp = Math::Vector3ToBtVector3(origin);
	UnmanagedPointer->warp(*originTemp);
	delete originTemp;
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
