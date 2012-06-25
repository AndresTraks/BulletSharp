#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "CollisionShape.h"
#include "ConstraintSolver.h"
#include "Dispatcher.h"
#include "SoftRigidDynamicsWorld.h"
#include "SoftBody.h"
#include "SoftBodySolver.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

using namespace BulletSharp::SoftBody;

#define Unmanaged static_cast<btSoftRigidDynamicsWorld*>(_unmanaged)

SoftRigidDynamicsWorld::SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
	BulletSharp::ConstraintSolver^ constraintSolver,
#endif
	CollisionConfiguration^ collisionConfiguration)
: DiscreteDynamicsWorld(new btSoftRigidDynamicsWorld(dispatcher->UnmanagedPointer, pairCache->UnmanagedPointer,
#ifndef DISABLE_CONSTRAINTS
		GetUnmanagedNullable(constraintSolver),
#else
		nullptr,
#endif
		collisionConfiguration->UnmanagedPointer))
{
	_collisionConfiguration = collisionConfiguration;
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
		GetUnmanagedNullable(constraintSolver),
#else
		nullptr,
#endif
		collisionConfiguration->UnmanagedPointer, softBodySolver->UnmanagedPointer))
{
	_collisionConfiguration = collisionConfiguration;
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body,
	CollisionFilterGroups collisionFilterGroup,	CollisionFilterGroups collisionFilterMask)
{
	Unmanaged->addSoftBody(body->UnmanagedPointer,
		(short int)collisionFilterGroup, (short int)collisionFilterMask);
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body,
	CollisionFilterGroups collisionFilterGroup)
{
	Unmanaged->addSoftBody(body->UnmanagedPointer,
		(short int)collisionFilterGroup);
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body)
{
	Unmanaged->addSoftBody(body->UnmanagedPointer);
}

void SoftRigidDynamicsWorld::RemoveSoftBody(BulletSharp::SoftBody::SoftBody^ body)
{
	Unmanaged->removeSoftBody(body->UnmanagedPointer);
}

AlignedSoftBodyArray^ SoftRigidDynamicsWorld::SoftBodyArray::get()
{
	return gcnew AlignedSoftBodyArray(&Unmanaged->getSoftBodyArray());
}

SoftBodyWorldInfo^ SoftRigidDynamicsWorld::WorldInfo::get()
{
	return gcnew SoftBodyWorldInfo(&Unmanaged->getWorldInfo());
}

#endif
