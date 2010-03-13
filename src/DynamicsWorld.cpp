#include "StdAfx.h"

#include "ActionInterface.h"
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
: RayResultCallback(new btDynamicsWorld::ClosestRayResultCallback(
	*Math::Vector3ToBtVector3(rayFromWorld), *Math::Vector3ToBtVector3(rayToWorld)))
{
}


void DynamicsWorld::AddRigidBody(RigidBody^ rigidBody)
{
	UnmanagedPointer->addRigidBody(rigidBody->UnmanagedPointer);
}

void DynamicsWorld::AddAction(ActionInterface^ actionInterface)
{
	UnmanagedPointer->addAction(actionInterface->UnmanagedPointer);
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
#endif

void DynamicsWorld::StepSimulation(btScalar timeStep)
{
	UnmanagedPointer->stepSimulation(timeStep);
}

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
	btVector3* gravity = new btVector3(value.X,value.Y,value.Z);
	UnmanagedPointer->setGravity(*gravity);
	delete gravity;
}

ContactSolverInfo^ DynamicsWorld::SolverInfo::get()
{
	return gcnew ContactSolverInfo(&UnmanagedPointer->getSolverInfo());
}

btDynamicsWorld* DynamicsWorld::UnmanagedPointer::get()
{
	return (btDynamicsWorld*)CollisionWorld::UnmanagedPointer;
}
