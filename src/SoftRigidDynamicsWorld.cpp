#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "ConstraintSolver.h"
#include "DefaultSoftBodySolver.h"
#include "Dispatcher.h"
#include "SequentialImpulseConstraintSolver.h"
#include "SoftRigidDynamicsWorld.h"
#include "SoftBody.h"
#include "SoftBodySolver.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

using namespace BulletSharp::SoftBody;

#define Native static_cast<btSoftRigidDynamicsWorld*>(_native)

SoftRigidDynamicsWorld::SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
	BulletSharp::ConstraintSolver^ constraintSolver,
	CollisionConfiguration^ collisionConfiguration, SoftBodySolver^ softBodySolver)
{
	if (softBodySolver) {
		_softBodySolver = softBodySolver;
		_ownsSolver = false;
	} else {
		_softBodySolver = gcnew DefaultSoftBodySolver();
		_ownsSolver = true;
	}

	if (constraintSolver)
	{
		_ownsConstraintSolver = false;
	}
	else
	{
		constraintSolver = gcnew SequentialImpulseConstraintSolver();
		_ownsConstraintSolver = true;
	}

	auto native = new btSoftRigidDynamicsWorld(dispatcher->_native, pairCache->_native,
		constraintSolver->_native, collisionConfiguration->_native, _softBodySolver->_native);

	_constraintSolver = constraintSolver;
	SetInternalReferences(native, dispatcher, pairCache);

	_softBodyArray = gcnew AlignedSoftBodyArray(&native->getSoftBodyArray());

	_worldInfo = gcnew SoftBodyWorldInfo(&native->getWorldInfo());
	_worldInfo->Dispatcher = dispatcher;
	_worldInfo->Broadphase = pairCache;
}

SoftRigidDynamicsWorld::SoftRigidDynamicsWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache,
	BulletSharp::ConstraintSolver^ constraintSolver,
	CollisionConfiguration^ collisionConfiguration)
{
	_softBodySolver = gcnew DefaultSoftBodySolver();
	_ownsSolver = true;

	if (constraintSolver)
	{
		_ownsConstraintSolver = false;
	}
	else
	{
		constraintSolver = gcnew SequentialImpulseConstraintSolver();
		_ownsConstraintSolver = true;
	}

	auto native = new btSoftRigidDynamicsWorld(dispatcher->_native, pairCache->_native,
		constraintSolver->_native, collisionConfiguration->_native, _softBodySolver->_native);

	_constraintSolver = constraintSolver;
	SetInternalReferences(native, dispatcher, pairCache);

	_softBodyArray = gcnew AlignedSoftBodyArray(&native->getSoftBodyArray());

	_worldInfo = gcnew SoftBodyWorldInfo(&native->getWorldInfo());
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
