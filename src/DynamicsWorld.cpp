#include "StdAfx.h"

#include "ActionInterface.h"
#include "ConstraintSOlver.h"
#include "ContactSolverInfo.h"
#include "DynamicsWorld.h"
#include "RigidBody.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif

DynamicsWorld::DynamicsWorld(btDynamicsWorld* world)
: CollisionWorld(world)
{
}

void DynamicsWorld::AddAction(ActionInterface^ actionInterface)
{
	UnmanagedPointer->addAction(actionInterface->UnmanagedPointer);
}

void DynamicsWorld::AddRigidBody(RigidBody^ rigidBody, CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask)
{
	UnmanagedPointer->addRigidBody(rigidBody->UnmanagedPointer, (short)collisionFilterGroup, (short)collisionFilterMask);
}

void DynamicsWorld::AddRigidBody(RigidBody^ rigidBody)
{
	UnmanagedPointer->addRigidBody(rigidBody->UnmanagedPointer);
}

#ifndef DISABLE_CONSTRAINTS
void DynamicsWorld::AddConstraint(TypedConstraint^ constraint,
	bool disableCollisionsBetweenLinkedBodies)
{
	UnmanagedPointer->addConstraint(constraint->UnmanagedPointer,
		disableCollisionsBetweenLinkedBodies);
}

void DynamicsWorld::AddConstraint(TypedConstraint^ constraint)
{
	UnmanagedPointer->addConstraint(constraint->UnmanagedPointer);
}

void DynamicsWorld::RemoveConstraint(TypedConstraint^ constraint)
{
	UnmanagedPointer->removeConstraint(constraint->UnmanagedPointer);
}

TypedConstraint^ DynamicsWorld::GetConstraint(int index)
{
	return TypedConstraint::Upcast(UnmanagedPointer->getConstraint(index));
}
#endif

void DynamicsWorld::ClearForces()
{
	UnmanagedPointer->clearForces();
}

void DynamicsWorld::RemoveAction(ActionInterface^ actionInterface)
{
	UnmanagedPointer->removeAction(actionInterface->UnmanagedPointer);
}

void DynamicsWorld::RemoveRigidBody(RigidBody^ rigidBody)
{
	UnmanagedPointer->removeRigidBody(rigidBody->UnmanagedPointer);
}

void callback(btDynamicsWorld *world, btScalar timeStep)
{
	void* obj = world->getWorldUserInfo();
	if (obj == nullptr)
		return;
	UserInfoWrapper^ userInfo = static_cast<UserInfoWrapper^>(VoidPtrToGCHandle(obj).Target);
	if (userInfo == nullptr)
		return;
	userInfo->Callback(gcnew DynamicsWorld(world), timeStep);
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo, bool isPreTick)
{
	UserInfoWrapper^ userInfo;

	void* obj = UnmanagedPointer->getWorldUserInfo();
	if (obj != nullptr)
	{
		userInfo = static_cast<UserInfoWrapper^>(VoidPtrToGCHandle(obj).Target);
	}
	else
	{
		userInfo = gcnew UserInfoWrapper(worldUserInfo);
		GCHandle handle = GCHandle::Alloc(userInfo);
		obj = GCHandleToVoidPtr(handle);
	}
	userInfo->Callback = cb;

	UnmanagedPointer->setInternalTickCallback(callback, obj, isPreTick);
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo)
{
	UserInfoWrapper^ userInfo;

	void* obj = UnmanagedPointer->getWorldUserInfo();
	if (obj != nullptr)
	{
		userInfo = static_cast<UserInfoWrapper^>(VoidPtrToGCHandle(obj).Target);
	}
	else
	{
		userInfo = gcnew UserInfoWrapper(worldUserInfo);
		GCHandle handle = GCHandle::Alloc(userInfo);
		obj = GCHandleToVoidPtr(handle);
	}
	userInfo->Callback = cb;

	UnmanagedPointer->setInternalTickCallback(callback, obj);
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb)
{
	UserInfoWrapper^ userInfo;

	void* obj = UnmanagedPointer->getWorldUserInfo();
	if (obj != nullptr)
	{
		userInfo = static_cast<UserInfoWrapper^>(VoidPtrToGCHandle(obj).Target);
	}
	else
	{
		userInfo = gcnew UserInfoWrapper();
		GCHandle handle = GCHandle::Alloc(userInfo);
		obj = GCHandleToVoidPtr(handle);
	}
	userInfo->Callback = cb;

	UnmanagedPointer->setInternalTickCallback(callback, obj);
}

int DynamicsWorld::StepSimulation(btScalar timeStep, int maxSubSteps, btScalar fixedTimeStep)
{
	return UnmanagedPointer->stepSimulation(timeStep, maxSubSteps, fixedTimeStep);
}

int DynamicsWorld::StepSimulation(btScalar timeStep, int maxSubSteps)
{
	return UnmanagedPointer->stepSimulation(timeStep, maxSubSteps);
}

int DynamicsWorld::StepSimulation(btScalar timeStep)
{
	return UnmanagedPointer->stepSimulation(timeStep);
}

void DynamicsWorld::SynchronizeMotionStates()
{
	UnmanagedPointer->synchronizeMotionStates();
}

#ifndef DISABLE_CONSTRAINTS
ConstraintSolver^ DynamicsWorld::ConstraintSolver::get()
{
	return gcnew BulletSharp::ConstraintSolver(UnmanagedPointer->getConstraintSolver());
}
void DynamicsWorld::ConstraintSolver::set(BulletSharp::ConstraintSolver^ value)
{
	UnmanagedPointer->setConstraintSolver(value->UnmanagedPointer);
}

int DynamicsWorld::NumConstraints::get()
{
	return UnmanagedPointer->getNumConstraints();
}

ContactSolverInfo^ DynamicsWorld::SolverInfo::get()
{
	return gcnew ContactSolverInfo(&UnmanagedPointer->getSolverInfo());
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
	return Math::BtVector3ToVector3(World_GetGravity(UnmanagedPointer));
}

void DynamicsWorld::Gravity::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	UnmanagedPointer->setGravity(*valueTemp);
	delete valueTemp;
}

Object^ DynamicsWorld::WorldUserInfo::get()
{
	void* obj = UnmanagedPointer->getWorldUserInfo();
	if (obj == nullptr)
		return nullptr;
	return (static_cast<UserInfoWrapper^>(VoidPtrToGCHandle(obj).Target)->UserObject);
}
void DynamicsWorld::WorldUserInfo::set(Object^ value)
{
	UserInfoWrapper^ userInfo;

	void* obj = UnmanagedPointer->getWorldUserInfo();
	if (obj != nullptr)
	{
		userInfo = static_cast<UserInfoWrapper^>(VoidPtrToGCHandle(obj).Target);
	}
	else
	{
		userInfo = gcnew UserInfoWrapper(value);
		GCHandle handle = GCHandle::Alloc(userInfo);
		UnmanagedPointer->setWorldUserInfo(GCHandleToVoidPtr(handle));
	}

	userInfo->UserObject = value;
}

DynamicsWorldType DynamicsWorld::WorldType::get()
{
	return (DynamicsWorldType) UnmanagedPointer->getWorldType();
}

btDynamicsWorld* DynamicsWorld::UnmanagedPointer::get()
{
	return (btDynamicsWorld*)CollisionWorld::UnmanagedPointer;
}


UserInfoWrapper::UserInfoWrapper(Object^ userObject)
{
	_userObject = userObject;
}

UserInfoWrapper::UserInfoWrapper()
{
	_userObject = nullptr;
}

DynamicsWorld::InternalTickCallback^ UserInfoWrapper::Callback::get()
{
	return _callback;
}
void UserInfoWrapper::Callback::set(DynamicsWorld::InternalTickCallback^ value)
{
	_callback = value;
}

Object^ UserInfoWrapper::UserObject::get()
{
	return _userObject;
}
void UserInfoWrapper::UserObject::set(Object^ value)
{
	_userObject = value;
}
