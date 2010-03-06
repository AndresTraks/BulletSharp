#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>
#pragma managed(pop)

#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "ConstraintSolver.h"
#include "Dispatcher.h"
#include "SoftRigidDynamicsWorld.h"
#include "SoftBody.h"

SoftRigidDynamicsWorld::SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher,
	BroadphaseInterface^ pairCache, ConstraintSolver^ constraintSolver,
	CollisionConfiguration^ collisionConfiguration)
: DiscreteDynamicsWorld(new btSoftRigidDynamicsWorld(dispatcher->UnmanagedPointer,
		pairCache->UnmanagedPointer, constraintSolver->UnmanagedPointer,
		collisionConfiguration->UnmanagedPointer))
{
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

void SoftRigidDynamicsWorld::AddSoftBody(SoftBody^ body,
	CollisionFilterGroups collisionFilterGroup,	CollisionFilterGroups collisionFilterMask)
{
	UnmanagedPointer->addSoftBody(body->UnmanagedPointer,
		(short int)collisionFilterGroup, (short int)collisionFilterMask);
}

void SoftRigidDynamicsWorld::AddSoftBody(SoftBody^ body,
	CollisionFilterGroups collisionFilterGroup)
{
	UnmanagedPointer->addSoftBody(body->UnmanagedPointer,
		(short int)collisionFilterGroup);
}

void SoftRigidDynamicsWorld::AddSoftBody(SoftBody^ body)
{
	UnmanagedPointer->addSoftBody(body->UnmanagedPointer);
}

btSoftRigidDynamicsWorld* SoftRigidDynamicsWorld::UnmanagedPointer::get()
{
	return (btSoftRigidDynamicsWorld*)DiscreteDynamicsWorld::UnmanagedPointer;
}
