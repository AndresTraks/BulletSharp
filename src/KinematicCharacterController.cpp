#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexShape.h"
#include "GhostObject.h"
#include "KinematicCharacterController.h"

#define Native (static_cast<btKinematicCharacterController*>(_native))

KinematicCharacterController::KinematicCharacterController(btKinematicCharacterController* native)
	: CharacterControllerInterface(native)
{
}

KinematicCharacterController::KinematicCharacterController(PairCachingGhostObject^ ghostObject,
	ConvexShape^ convexShape, btScalar stepHeight, int upAxis)
	: CharacterControllerInterface(new btKinematicCharacterController((btPairCachingGhostObject*)ghostObject->_native,
		(btConvexShape*)convexShape->_native, stepHeight, upAxis))
{
}

KinematicCharacterController::KinematicCharacterController(PairCachingGhostObject^ ghostObject,
	ConvexShape^ convexShape, btScalar stepHeight)
	: CharacterControllerInterface(new btKinematicCharacterController((btPairCachingGhostObject*)ghostObject->_native,
		(btConvexShape*)convexShape->_native, stepHeight))
{
}

void KinematicCharacterController::SetFallSpeed(btScalar fallSpeed)
{
	Native->setFallSpeed(fallSpeed);
}

void KinematicCharacterController::SetJumpSpeed(btScalar jumpSpeed)
{
	Native->setJumpSpeed(jumpSpeed);
}

void KinematicCharacterController::SetMaxJumpHeight(btScalar maxJumpHeight)
{
	Native->setMaxJumpHeight(maxJumpHeight);
}

void KinematicCharacterController::SetUpAxis(int axis)
{
	Native->setUpAxis(axis);
}

void KinematicCharacterController::SetUseGhostSweepTest(bool useGhostObjectSweepTest)
{
	Native->setUseGhostSweepTest(useGhostObjectSweepTest);
}

PairCachingGhostObject^ KinematicCharacterController::GhostObject::get()
{
	return static_cast<PairCachingGhostObject^>(CollisionObject::GetManaged(Native->getGhostObject()));
}

btScalar KinematicCharacterController::Gravity::get()
{
	return Native->getGravity();
}
void KinematicCharacterController::Gravity::set(btScalar gravity)
{
	Native->setGravity(gravity);
}

btScalar KinematicCharacterController::MaxSlope::get()
{
	return Native->getMaxSlope();
}
void KinematicCharacterController::MaxSlope::set(btScalar slopeRadians)
{
	Native->setMaxSlope(slopeRadians);
}

#endif
