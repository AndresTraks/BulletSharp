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

#define Native static_cast<btSoftRigidDynamicsWorld*>(_native)

SoftRigidDynamicsWorld::SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
	BulletSharp::ConstraintSolver^ constraintSolver,
#endif
	CollisionConfiguration^ collisionConfiguration)
: DiscreteDynamicsWorld(new btSoftRigidDynamicsWorld(dispatcher->_native, pairCache->_native,
#ifndef DISABLE_CONSTRAINTS
		GetUnmanagedNullable(constraintSolver),
#else
		nullptr,
#endif
		collisionConfiguration->_native))
{
#ifndef DISABLE_CONSTRAINTS
	_constraintSolver = constraintSolver;
#endif
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

SoftRigidDynamicsWorld::SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
	BulletSharp::ConstraintSolver^ constraintSolver,
#endif
	CollisionConfiguration^ collisionConfiguration, SoftBodySolver^ softBodySolver)
: DiscreteDynamicsWorld(new btSoftRigidDynamicsWorld(dispatcher->_native, pairCache->_native,
#ifndef DISABLE_CONSTRAINTS
		GetUnmanagedNullable(constraintSolver),
#else
		nullptr,
#endif
		collisionConfiguration->_native, softBodySolver->_native))
{
#ifndef DISABLE_CONSTRAINTS
	_constraintSolver = constraintSolver;
#endif
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body,
	CollisionFilterGroups collisionFilterGroup,	CollisionFilterGroups collisionFilterMask)
{
	Native->addSoftBody((btSoftBody*)body->_native,
		(short int)collisionFilterGroup, (short int)collisionFilterMask);
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body,
	CollisionFilterGroups collisionFilterGroup)
{
	Native->addSoftBody((btSoftBody*)body->_native,
		(short int)collisionFilterGroup);
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body)
{
	Native->addSoftBody((btSoftBody*)body->_native);
}

void SoftRigidDynamicsWorld::RemoveSoftBody(BulletSharp::SoftBody::SoftBody^ body)
{
	Native->removeSoftBody((btSoftBody*)body->_native);
}

AlignedSoftBodyArray^ SoftRigidDynamicsWorld::SoftBodyArray::get()
{
	if (_softBodyArray == nullptr)
	{
		_softBodyArray = gcnew AlignedSoftBodyArray(&Native->getSoftBodyArray());
	}
	return _softBodyArray;
}

SoftBodyWorldInfo^ SoftRigidDynamicsWorld::WorldInfo::get()
{
	if (_worldInfo == nullptr)
	{
		_worldInfo = gcnew SoftBodyWorldInfo(&Native->getWorldInfo());
	}
	return _worldInfo;
}

#endif
