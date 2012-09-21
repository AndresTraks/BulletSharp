#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "ConvexShape.h"
#include "GhostObject.h"
#include "KinematicCharacterController.h"

#define Unmanaged (static_cast<btKinematicCharacterController*>(_unmanaged))

KinematicCharacterController::KinematicCharacterController(btKinematicCharacterController* characterController)
: CharacterControllerInterface(characterController)
{
}

KinematicCharacterController::KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape, btScalar stepHeight, int upAxis)
: CharacterControllerInterface(new btKinematicCharacterController(ghostObject->UnmanagedPointer, (btConvexShape*)convexShape->_unmanaged, stepHeight, upAxis))
{
}

KinematicCharacterController::KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape, btScalar stepHeight)
: CharacterControllerInterface(new btKinematicCharacterController(ghostObject->UnmanagedPointer, (btConvexShape*)convexShape->_unmanaged, stepHeight))
{
}

void KinematicCharacterController::SetFallSpeed(btScalar fallSpeed)
{
	Unmanaged->setFallSpeed(fallSpeed);
}

void KinematicCharacterController::SetJumpSpeed(btScalar jumpSpeed)
{
	Unmanaged->setJumpSpeed(jumpSpeed);
}

void KinematicCharacterController::SetMaxJumpHeight(btScalar maxJumpHeight)
{
	Unmanaged->setMaxJumpHeight(maxJumpHeight);
}

void KinematicCharacterController::SetUpAxis(int axis)
{
	Unmanaged->setUpAxis(axis);
}

void KinematicCharacterController::SetUseGhostSweepTest(bool useGhostObjectSweepTest)
{
	Unmanaged->setUseGhostSweepTest(useGhostObjectSweepTest);
}

BulletSharp::GhostObject^ KinematicCharacterController::GhostObject::get()
{
	return static_cast<BulletSharp::GhostObject^>(CollisionObject::GetManaged(Unmanaged->getGhostObject()));
}

#endif
