#include "StdAfx.h"

#include "ActionInterface.h"
#include "ConstraintSOlver.h"
#include "ContactSolverInfo.h"
#include "DynamicsWorld.h"
#include "RigidBody.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif

#define Native static_cast<btDynamicsWorld*>(_native)

DynamicsWorld::DynamicsWorld(btDynamicsWorld* world)
: CollisionWorld(world)
{
}

void DynamicsWorld::AddAction(ActionInterface^ actionInterface)
{
	Native->addAction(actionInterface->_native);
}

void DynamicsWorld::AddRigidBody(RigidBody^ rigidBody, CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask)
{
	Native->addRigidBody((btRigidBody*)rigidBody->_native, (short)collisionFilterGroup, (short)collisionFilterMask);
}

void DynamicsWorld::AddRigidBody(RigidBody^ rigidBody)
{
	Native->addRigidBody((btRigidBody*)rigidBody->_native);
}

#ifndef DISABLE_CONSTRAINTS
void DynamicsWorld::AddConstraint(TypedConstraint^ constraint,
	bool disableCollisionsBetweenLinkedBodies)
{
	Native->addConstraint(constraint->UnmanagedPointer, disableCollisionsBetweenLinkedBodies);
}

void DynamicsWorld::AddConstraint(TypedConstraint^ constraint)
{
	Native->addConstraint(constraint->UnmanagedPointer);
}

void DynamicsWorld::RemoveConstraint(TypedConstraint^ constraint)
{
	Native->removeConstraint(constraint->UnmanagedPointer);
}

TypedConstraint^ DynamicsWorld::GetConstraint(int index)
{
	return TypedConstraint::Upcast(Native->getConstraint(index));
}
#endif

void DynamicsWorld::ClearForces()
{
	Native->clearForces();
}

void DynamicsWorld::RemoveAction(ActionInterface^ actionInterface)
{
	Native->removeAction(actionInterface->_native);
}

void DynamicsWorld::RemoveRigidBody(RigidBody^ rigidBody)
{
	Native->removeRigidBody((btRigidBody*)rigidBody->_native);
}

void callback(btDynamicsWorld* world, btScalar timeStep)
{
	void* userInfo = world->getWorldUserInfo();
	WeakReference^ worldWeakRef = static_cast<WeakReference^>(VoidPtrToGCHandle(userInfo).Target);
	DynamicsWorld^ dynamicsWorld = static_cast<DynamicsWorld^>(worldWeakRef->Target);
	if (dynamicsWorld != nullptr) {
		dynamicsWorld->_callback(dynamicsWorld, timeStep);
	}
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo, bool isPreTick)
{
	_callback = cb;
	_userObject = worldUserInfo;

	void* nativeUserInfo = Native->getWorldUserInfo();
	if (cb != nullptr) {
		if (!nativeUserInfo) {
			GCHandle handle = GCHandle::Alloc(gcnew WeakReference(this));
			nativeUserInfo = GCHandleToVoidPtr(handle);
		}
		Native->setInternalTickCallback(callback, nativeUserInfo, isPreTick);
	} else {
		if (nativeUserInfo) {
			VoidPtrToGCHandle(nativeUserInfo).Free();
		}
		Native->setInternalTickCallback(0, 0, isPreTick);
	}
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo)
{
	SetInternalTickCallback(cb, worldUserInfo, false);
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb)
{
	SetInternalTickCallback(cb, _userObject, false);
}

int DynamicsWorld::StepSimulation(btScalar timeStep, int maxSubSteps, btScalar fixedTimeStep)
{
	return Native->stepSimulation(timeStep, maxSubSteps, fixedTimeStep);
}

int DynamicsWorld::StepSimulation(btScalar timeStep, int maxSubSteps)
{
	return Native->stepSimulation(timeStep, maxSubSteps);
}

int DynamicsWorld::StepSimulation(btScalar timeStep)
{
	return Native->stepSimulation(timeStep);
}

void DynamicsWorld::SynchronizeMotionStates()
{
	Native->synchronizeMotionStates();
}

#ifndef DISABLE_CONSTRAINTS
ConstraintSolver^ DynamicsWorld::ConstraintSolver::get()
{
	return gcnew BulletSharp::ConstraintSolver(Native->getConstraintSolver());
}
void DynamicsWorld::ConstraintSolver::set(BulletSharp::ConstraintSolver^ value)
{
	Native->setConstraintSolver(value->UnmanagedPointer);
}

int DynamicsWorld::NumConstraints::get()
{
	return Native->getNumConstraints();
}

ContactSolverInfo^ DynamicsWorld::SolverInfo::get()
{
	return gcnew ContactSolverInfo(&Native->getSolverInfo());
}
#endif

#pragma managed(push, off)
btVector3* World_GetGravity(btDynamicsWorld* world)
{
	return &world->getGravity();
}
#pragma managed(pop)

Vector3 DynamicsWorld::Gravity::get()
{
	return Math::BtVector3ToVector3(World_GetGravity(Native));
}

void DynamicsWorld::Gravity::set(Vector3 value)
{
	VECTOR3_DEF(value);
	Native->setGravity(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

Object^ DynamicsWorld::WorldUserInfo::get()
{
	return _userObject;
}
void DynamicsWorld::WorldUserInfo::set(Object^ value)
{
	_userObject = value;
}

DynamicsWorldType DynamicsWorld::WorldType::get()
{
	return (DynamicsWorldType) Native->getWorldType();
}
