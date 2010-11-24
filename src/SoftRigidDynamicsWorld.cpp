#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "ConstraintSolver.h"
#include "Dispatcher.h"
#include "SoftRigidDynamicsWorld.h"
#include "SoftBody.h"
#include "SoftBodySolver.h"

using namespace BulletSharp::SoftBody;

SoftRigidDynamicsWorld::SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
	BulletSharp::ConstraintSolver^ constraintSolver,
#endif
	CollisionConfiguration^ collisionConfiguration)
: DiscreteDynamicsWorld(new btSoftRigidDynamicsWorld(dispatcher->UnmanagedPointer, pairCache->UnmanagedPointer,
#ifndef DISABLE_CONSTRAINTS
		(constraintSolver != nullptr) ? constraintSolver->UnmanagedPointer : 0,
#else
		nullptr,
#endif
		collisionConfiguration->UnmanagedPointer))
{
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

SoftRigidDynamicsWorld::SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
	BulletSharp::ConstraintSolver^ constraintSolver,
#endif
	CollisionConfiguration^ collisionConfiguration, SoftBodySolver^ softBodySolver)
: DiscreteDynamicsWorld(new btSoftRigidDynamicsWorld(dispatcher->UnmanagedPointer, pairCache->UnmanagedPointer,
#ifndef DISABLE_CONSTRAINTS
		(constraintSolver != nullptr) ? constraintSolver->UnmanagedPointer : 0,
#else
		nullptr,
#endif
		collisionConfiguration->UnmanagedPointer, softBodySolver->UnmanagedPointer))
{
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body,
	CollisionFilterGroups collisionFilterGroup,	CollisionFilterGroups collisionFilterMask)
{
	UnmanagedPointer->addSoftBody(body->UnmanagedPointer,
		(short int)collisionFilterGroup, (short int)collisionFilterMask);
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body,
	CollisionFilterGroups collisionFilterGroup)
{
	UnmanagedPointer->addSoftBody(body->UnmanagedPointer,
		(short int)collisionFilterGroup);
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body)
{
	UnmanagedPointer->addSoftBody(body->UnmanagedPointer);
}

void SoftRigidDynamicsWorld::RemoveSoftBody(BulletSharp::SoftBody::SoftBody^ body)
{
	UnmanagedPointer->removeSoftBody(body->UnmanagedPointer);
}

AlignedSoftBodyArray^ SoftRigidDynamicsWorld::SoftBodyArray::get()
{
	return gcnew AlignedSoftBodyArray(&UnmanagedPointer->getSoftBodyArray());
}

SoftBodyWorldInfo^ SoftRigidDynamicsWorld::WorldInfo::get()
{
	return gcnew SoftBodyWorldInfo(&UnmanagedPointer->getWorldInfo());
}

btSoftRigidDynamicsWorld* SoftRigidDynamicsWorld::UnmanagedPointer::get()
{
	return (btSoftRigidDynamicsWorld*)DiscreteDynamicsWorld::UnmanagedPointer;
}

#endif
