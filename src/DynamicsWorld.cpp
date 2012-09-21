#include "StdAfx.h"

#include "ActionInterface.h"
#include "ConstraintSOlver.h"
#include "ContactSolverInfo.h"
#include "DynamicsWorld.h"
#include "RigidBody.h"
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#endif

#define Unmanaged static_cast<btDynamicsWorld*>(_unmanaged)

DynamicsWorld::DynamicsWorld(btDynamicsWorld* world)
: CollisionWorld(world)
{
}

void DynamicsWorld::AddAction(ActionInterface^ actionInterface)
{
	Unmanaged->addAction(actionInterface->_unmanaged);
}

void DynamicsWorld::AddRigidBody(RigidBody^ rigidBody, CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask)
{
	Unmanaged->addRigidBody((btRigidBody*)rigidBody->_unmanaged, (short)collisionFilterGroup, (short)collisionFilterMask);
}

void DynamicsWorld::AddRigidBody(RigidBody^ rigidBody)
{
	Unmanaged->addRigidBody((btRigidBody*)rigidBody->_unmanaged);
}

#ifndef DISABLE_CONSTRAINTS
void DynamicsWorld::AddConstraint(TypedConstraint^ constraint,
	bool disableCollisionsBetweenLinkedBodies)
{
	Unmanaged->addConstraint(constraint->UnmanagedPointer, disableCollisionsBetweenLinkedBodies);
}

void DynamicsWorld::AddConstraint(TypedConstraint^ constraint)
{
	Unmanaged->addConstraint(constraint->UnmanagedPointer);
}

void DynamicsWorld::RemoveConstraint(TypedConstraint^ constraint)
{
	Unmanaged->removeConstraint(constraint->UnmanagedPointer);
}

TypedConstraint^ DynamicsWorld::GetConstraint(int index)
{
	return TypedConstraint::Upcast(Unmanaged->getConstraint(index));
}
#endif

void DynamicsWorld::ClearForces()
{
	Unmanaged->clearForces();
}

void DynamicsWorld::RemoveAction(ActionInterface^ actionInterface)
{
	Unmanaged->removeAction(actionInterface->_unmanaged);
}

void DynamicsWorld::RemoveRigidBody(RigidBody^ rigidBody)
{
	Unmanaged->removeRigidBody((btRigidBody*)rigidBody->_unmanaged);
}

void callback(btDynamicsWorld* world, btScalar timeStep)
{
	DynamicsWorld^ dynamicsWorld = static_cast<DynamicsWorld^>(CollisionWorld::GetManaged(world));
	dynamicsWorld->_callback(dynamicsWorld, timeStep);
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo, bool isPreTick)
{
	_callback = cb;
	_userObject = worldUserInfo;
	Unmanaged->setInternalTickCallback(callback, Unmanaged->getWorldUserInfo(), isPreTick);
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb, Object^ worldUserInfo)
{
	_callback = cb;
	_userObject = worldUserInfo;
	Unmanaged->setInternalTickCallback(callback, Unmanaged->getWorldUserInfo());
}

void DynamicsWorld::SetInternalTickCallback(InternalTickCallback^ cb)
{
	_callback = cb;
	Unmanaged->setInternalTickCallback(callback, Unmanaged->getWorldUserInfo());
}

int DynamicsWorld::StepSimulation(btScalar timeStep, int maxSubSteps, btScalar fixedTimeStep)
{
	return Unmanaged->stepSimulation(timeStep, maxSubSteps, fixedTimeStep);
}

int DynamicsWorld::StepSimulation(btScalar timeStep, int maxSubSteps)
{
	return Unmanaged->stepSimulation(timeStep, maxSubSteps);
}

int DynamicsWorld::StepSimulation(btScalar timeStep)
{
	return Unmanaged->stepSimulation(timeStep);
}

void DynamicsWorld::SynchronizeMotionStates()
{
	Unmanaged->synchronizeMotionStates();
}

#ifndef DISABLE_CONSTRAINTS
ConstraintSolver^ DynamicsWorld::ConstraintSolver::get()
{
	return gcnew BulletSharp::ConstraintSolver(Unmanaged->getConstraintSolver());
}
void DynamicsWorld::ConstraintSolver::set(BulletSharp::ConstraintSolver^ value)
{
	Unmanaged->setConstraintSolver(value->UnmanagedPointer);
}

int DynamicsWorld::NumConstraints::get()
{
	return Unmanaged->getNumConstraints();
}

ContactSolverInfo^ DynamicsWorld::SolverInfo::get()
{
	return gcnew ContactSolverInfo(&Unmanaged->getSolverInfo());
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
	return Math::BtVector3ToVector3(World_GetGravity(Unmanaged));
}

void DynamicsWorld::Gravity::set(Vector3 value)
{
	VECTOR3_DEF(value);
	Unmanaged->setGravity(VECTOR3_USE(value));
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
	return (DynamicsWorldType) Unmanaged->getWorldType();
}

btDynamicsWorld* DynamicsWorld::UnmanagedPointer::get()
{
	return (btDynamicsWorld*)CollisionWorld::UnmanagedPointer;
}
