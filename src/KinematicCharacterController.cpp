#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexShape.h"
#include "GhostObject.h"
#include "KinematicCharacterController.h"

#define Native (static_cast<btKinematicCharacterController*>(_native))

KinematicCharacterController::KinematicCharacterController(btKinematicCharacterController* characterController)
: CharacterControllerInterface(characterController)
{
}

KinematicCharacterController::KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape, btScalar stepHeight, int upAxis)
: CharacterControllerInterface(new btKinematicCharacterController((btPairCachingGhostObject*)ghostObject->_native, (btConvexShape*)convexShape->_native, stepHeight, upAxis))
{
}

KinematicCharacterController::KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape, btScalar stepHeight)
: CharacterControllerInterface(new btKinematicCharacterController((btPairCachingGhostObject*)ghostObject->_native, (btConvexShape*)convexShape->_native, stepHeight))
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

BulletSharp::GhostObject^ KinematicCharacterController::GhostObject::get()
{
	return static_cast<BulletSharp::GhostObject^>(CollisionObject::GetManaged(Native->getGhostObject()));
}

#endif
