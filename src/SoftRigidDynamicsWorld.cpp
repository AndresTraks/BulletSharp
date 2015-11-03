#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "ConstraintSolver.h"
#include "DefaultSoftBodySolver.h"
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
	CollisionConfiguration^ collisionConfiguration, SoftBodySolver^ softBodySolver)
	: DiscreteDynamicsWorld(0)
{
	if (softBodySolver) {
		_softBodySolver = softBodySolver;
		_ownsSolver = false;
	} else {
		_softBodySolver = gcnew DefaultSoftBodySolver();
		_ownsSolver = true;
	}

	_native = new btSoftRigidDynamicsWorld(dispatcher->_native, pairCache->_native,
#ifndef DISABLE_CONSTRAINTS
		GetUnmanagedNullable(constraintSolver),
#else
		nullptr,
#endif
		collisionConfiguration->_native, _softBodySolver->_native);

	_collisionObjectArray = gcnew AlignedCollisionObjectArray(&_native->getCollisionObjectArray(), _native);
	_softBodyArray = gcnew AlignedSoftBodyArray(&Native->getSoftBodyArray());

#ifndef DISABLE_CONSTRAINTS
	_constraintSolver = constraintSolver;
#endif
	Dispatcher = dispatcher;
	_broadphase = pairCache;
	_worldInfo = gcnew SoftBodyWorldInfo(&Native->getWorldInfo());
	_worldInfo->Dispatcher = dispatcher;
	_worldInfo->Broadphase = pairCache;
}

SoftRigidDynamicsWorld::SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
#ifndef DISABLE_CONSTRAINTS
	BulletSharp::ConstraintSolver^ constraintSolver,
#endif
	CollisionConfiguration^ collisionConfiguration)
	: DiscreteDynamicsWorld(0)
{
	_softBodySolver = gcnew DefaultSoftBodySolver();
	_ownsSolver = true;

	_native = new btSoftRigidDynamicsWorld(dispatcher->_native, pairCache->_native,
#ifndef DISABLE_CONSTRAINTS
		GetUnmanagedNullable(constraintSolver),
#else
		nullptr,
#endif
		collisionConfiguration->_native, _softBodySolver->_native);

	_collisionObjectArray = gcnew AlignedCollisionObjectArray(&_native->getCollisionObjectArray(), _native);
	_softBodyArray = gcnew AlignedSoftBodyArray(&Native->getSoftBodyArray());

#ifndef DISABLE_CONSTRAINTS
	_constraintSolver = constraintSolver;
#endif
	Dispatcher = dispatcher;
	_broadphase = pairCache;
	_worldInfo = gcnew SoftBodyWorldInfo(&Native->getWorldInfo());
	_worldInfo->Dispatcher = dispatcher;
	_worldInfo->Broadphase = pairCache;
}

SoftRigidDynamicsWorld::~SoftRigidDynamicsWorld()
{
	this->!SoftRigidDynamicsWorld();
}

SoftRigidDynamicsWorld::!SoftRigidDynamicsWorld()
{
	if (_ownsSolver)
	{
		delete _softBodySolver;
	}
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body,
	CollisionFilterGroups collisionFilterGroup,	CollisionFilterGroups collisionFilterMask)
{
	body->SoftBodySolver = _softBodySolver;
	_collisionObjectArray->Add(body, (short)collisionFilterGroup, (short)collisionFilterMask);
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body,
	short collisionFilterGroup, short collisionFilterMask)
{
	body->SoftBodySolver = _softBodySolver;
	_collisionObjectArray->Add(body, collisionFilterGroup, collisionFilterMask);
}

void SoftRigidDynamicsWorld::AddSoftBody(BulletSharp::SoftBody::SoftBody^ body)
{
	body->SoftBodySolver = _softBodySolver;
	_collisionObjectArray->Add(body);
}

void SoftRigidDynamicsWorld::RemoveSoftBody(BulletSharp::SoftBody::SoftBody^ body)
{
	_collisionObjectArray->Remove(body);
}

BulletSharp::SoftBody::DrawFlags SoftRigidDynamicsWorld::DrawFlags::get()
{
	return (BulletSharp::SoftBody::DrawFlags)Native->getDrawFlags();
}
void SoftRigidDynamicsWorld::DrawFlags::set(BulletSharp::SoftBody::DrawFlags f)
{
	Native->setDrawFlags((int)f);
}

AlignedSoftBodyArray^ SoftRigidDynamicsWorld::SoftBodyArray::get()
{
	return _softBodyArray;
}

SoftBodyWorldInfo^ SoftRigidDynamicsWorld::WorldInfo::get()
{
	return _worldInfo;
}

#endif
