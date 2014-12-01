#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "CharacterControllerInterface.h"
#include "CollisionWorld.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

CharacterControllerInterface::CharacterControllerInterface(btCharacterControllerInterface* native)
{
	_native = native;
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
	BulletSharp::DebugDraw^ cast = dynamic_cast<BulletSharp::DebugDraw^>(debugDrawer);
	if (cast) {
		_native->debugDraw(cast->_native);
	} else {
		// Temporary IDebugDraw wrapper
		DebugDrawWrapper* wrapper = new DebugDrawWrapper(debugDrawer, false);
		_native->debugDraw(wrapper);
		delete wrapper;
	}
}
#endif

void CharacterControllerInterface::UpdateAction(CollisionWorld^ collisionWorld, btScalar deltaTimeStep)
{
	_native->updateAction(collisionWorld->_native, deltaTimeStep);
}

void CharacterControllerInterface::Jump()
{
	_native->jump();
}

void CharacterControllerInterface::PlayerStep(CollisionWorld^ collisionWorld, btScalar dt)
{
	_native->playerStep(collisionWorld->_native, dt);
}

void CharacterControllerInterface::PreStep(CollisionWorld^ collisionWorld)
{
	_native->preStep(collisionWorld->_native);
}

void CharacterControllerInterface::Reset(CollisionWorld^ collisionWorld)
{
	_native->reset(collisionWorld->_native);
}

void CharacterControllerInterface::SetUpInterpolate(bool value)
{
	_native->setUpInterpolate(value);
}

void CharacterControllerInterface::SetVelocityForTimeInterval(Vector3 velocity, btScalar timeInterval)
{
	VECTOR3_CONV(velocity);
	_native->setVelocityForTimeInterval(VECTOR3_USE(velocity), timeInterval);
	VECTOR3_DEL(velocity);
}

void CharacterControllerInterface::SetWalkDirection(Vector3 walkDirection)
{
	VECTOR3_CONV(walkDirection);
	_native->setWalkDirection(VECTOR3_USE(walkDirection));
	VECTOR3_DEL(walkDirection);
}

void CharacterControllerInterface::Warp(Vector3 origin)
{
	VECTOR3_CONV(origin);
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
