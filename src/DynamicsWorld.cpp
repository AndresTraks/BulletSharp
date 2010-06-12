#include "StdAfx.h"

#include "ActionInterface.h"
#include "ConstraintSOlver.h"
#include "ContactSolverInfo.h"
#include "DynamicsWorld.h"
#include "RigidBody.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif

DynamicsWorld::RayResultCallback::RayResultCallback(btDynamicsWorld::RayResultCallback* callback)
{
	_callback = callback;
}

DynamicsWorld::RayResultCallback::~RayResultCallback()
{
	this->!RayResultCallback();
}

DynamicsWorld::RayResultCallback::!RayResultCallback()
{
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_callback = NULL;

	OnDisposed( this, nullptr );
}

bool DynamicsWorld::RayResultCallback::IsDisposed::get()
{
	return (_callback == NULL);
}

btDynamicsWorld::RayResultCallback* DynamicsWorld::RayResultCallback::UnmanagedPointer::get()
{
	return _callback;
}
void DynamicsWorld::RayResultCallback::UnmanagedPointer::set(btDynamicsWorld::RayResultCallback* value)
{
	_callback = value;
}


DynamicsWorld::ClosestRayResultCallback::ClosestRayResultCallback(Vector3 rayFromWorld, Vector3 rayToWorld)
: RayResultCallback(0)
{
	btVector3* rayFromWorldTemp = Math::Vector3ToBtVector3(rayFromWorld);
	btVector3* rayToWorldTemp = Math::Vector3ToBtVector3(rayToWorld);

	UnmanagedPointer = new btDynamicsWorld::ClosestRayResultCallback(*rayFromWorldTemp, *rayToWorldTemp);

	delete rayFromWorldTemp;
	delete rayToWorldTemp;
}


DynamicsWorld::DynamicsWorld(btDynamicsWorld* world)
: CollisionWorld(world)
{
}

void DynamicsWorld::AddAction(ActionInterface^ actionInterface)
{
	UnmanagedPointer->addAction(actionInterface->UnmanagedPointer);
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
	return gcnew TypedConstraint(UnmanagedPointer->getConstraint(index));
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
	return static_cast<Object^>(VoidPtrToGCHandle(obj).Target);
}

void DynamicsWorld::WorldUserInfo::set(Object^ value)
{
	void* obj = UnmanagedPointer->getWorldUserInfo();
	if (obj != nullptr)
		VoidPtrToGCHandle(obj).Free();

	GCHandle handle = GCHandle::Alloc(value);
	UnmanagedPointer->setWorldUserInfo(GCHandleToVoidPtr(handle));
}

DynamicsWorldType DynamicsWorld::WorldType::get()
{
	return (DynamicsWorldType) UnmanagedPointer->getWorldType();
}

btDynamicsWorld* DynamicsWorld::UnmanagedPointer::get()
{
	return (btDynamicsWorld*)CollisionWorld::UnmanagedPointer;
}
