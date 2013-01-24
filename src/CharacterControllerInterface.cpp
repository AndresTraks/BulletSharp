#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "CharacterControllerInterface.h"
#include "CollisionWorld.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

CharacterControllerInterface::CharacterControllerInterface(btCharacterControllerInterface* controllerInterface)
{
	_native = controllerInterface;
}

CharacterControllerInterface::~CharacterControllerInterface()
{
	this->!CharacterControllerInterface();
}

CharacterControllerInterface::!CharacterControllerInterface()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

#ifndef DISABLE_DEBUGDRAW
void CharacterControllerInterface::DebugDraw(IDebugDraw^ debugDrawer)
{
	_native->debugDraw(DebugDraw::GetUnmanaged(debugDrawer));
}
#endif

void CharacterControllerInterface::UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep)
{
	_native->updateAction(collisionWorld->_native, deltaTimeStep);
}

void CharacterControllerInterface::PlayerStep(CollisionWorld^ collisionWorld, btScalar dt)
{
	_native->playerStep(collisionWorld->_native, dt);
}

void CharacterControllerInterface::Jump()
{
	_native->jump();
}

void CharacterControllerInterface::Reset()
{
	_native->reset();
}

void CharacterControllerInterface::SetVelocityForTimeInterval(Vector3 velocity, btScalar timeInterval)
{
	VECTOR3_DEF(velocity);
	_native->setVelocityForTimeInterval(VECTOR3_USE(velocity), timeInterval);
	VECTOR3_DEL(velocity);
}

void CharacterControllerInterface::SetWalkDirection(Vector3 walkDirection)
{
	VECTOR3_DEF(walkDirection);
	_native->setWalkDirection(VECTOR3_USE(walkDirection));
	VECTOR3_DEL(walkDirection);
}

void CharacterControllerInterface::Warp(Vector3 origin)
{
	VECTOR3_DEF(origin);
	_native->warp(VECTOR3_USE(origin));
	VECTOR3_DEL(origin);
}

bool CharacterControllerInterface::CanJump::get()
{
	return _native->canJump();
}

bool CharacterControllerInterface::IsDisposed::get()
{
	return ( _native == NULL );
}

bool CharacterControllerInterface::OnGround::get()
{
	return _native->onGround();
}

#endif
