#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#pragma managed(pop)

#include "ConvexShape.h"
#include "GhostObject.h"
#include "KinematicCharacterController.h"

KinematicCharacterController::KinematicCharacterController(btKinematicCharacterController* characterController)
: CharacterControllerInterface(characterController)
{
}

KinematicCharacterController::KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape, btScalar stepHeight, int upAxis)
: CharacterControllerInterface(new btKinematicCharacterController(ghostObject->UnmanagedPointer, convexShape->UnmanagedPointer, stepHeight, upAxis))
{
}

KinematicCharacterController::KinematicCharacterController(PairCachingGhostObject^ ghostObject, ConvexShape^ convexShape, btScalar stepHeight)
: CharacterControllerInterface(new btKinematicCharacterController(ghostObject->UnmanagedPointer, convexShape->UnmanagedPointer, stepHeight))
{
}

void KinematicCharacterController::SetFallSpeed(btScalar fallSpeed)
{
	UnmanagedPointer->setFallSpeed(fallSpeed);
}

void KinematicCharacterController::SetJumpSpeed(btScalar jumpSpeed)
{
	UnmanagedPointer->setJumpSpeed(jumpSpeed);
}

void KinematicCharacterController::SetMaxJumpHeight(btScalar maxJumpHeight)
{
	UnmanagedPointer->setMaxJumpHeight(maxJumpHeight);
}

void KinematicCharacterController::SetUpAxis(int axis)
{
	UnmanagedPointer->setUpAxis(axis);
}

void KinematicCharacterController::SetUseGhostSweepTest(bool useGhostObjectSweepTest)
{
	UnmanagedPointer->setUseGhostSweepTest(useGhostObjectSweepTest);
}

BulletSharp::GhostObject^ KinematicCharacterController::GhostObject::get()
{
	return gcnew BulletSharp::GhostObject(UnmanagedPointer->getGhostObject());
}

btKinematicCharacterController* KinematicCharacterController::UnmanagedPointer::get()
{
	return (btKinematicCharacterController*)CharacterControllerInterface::UnmanagedPointer;
}
