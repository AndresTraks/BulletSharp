#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "CollisionWorld.h"
#include "Dispatcher.h"
#ifndef DISABLE_DEBUGDRAW
#include "DebugDraw.h"
#endif

CollisionWorld::ContactResultCallback::ContactResultCallback(btCollisionWorld::ContactResultCallback* callback)
{
	_callback = callback;
}

CollisionWorld::ContactResultCallback::~ContactResultCallback()
{
	this->!ContactResultCallback();
}

CollisionWorld::ContactResultCallback::!ContactResultCallback()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_callback = NULL;
	
	OnDisposed( this, nullptr );
}

bool CollisionWorld::ContactResultCallback::IsDisposed::get()
{
	return (_callback == NULL);
}

btCollisionWorld::ContactResultCallback* CollisionWorld::ContactResultCallback::UnmanagedPointer::get()
{
	return _callback;
}
void CollisionWorld::ContactResultCallback::UnmanagedPointer::set(btCollisionWorld::ContactResultCallback* value)
{
	_callback = value;
}


CollisionWorld::RayResultCallback::RayResultCallback(btCollisionWorld::RayResultCallback* callback)
{
	_callback = callback;
}

CollisionWorld::RayResultCallback::~RayResultCallback()
{
	this->!RayResultCallback();
}

CollisionWorld::RayResultCallback::!RayResultCallback()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_callback = NULL;
	
	OnDisposed( this, nullptr );
}

BulletSharp::CollisionObject^ CollisionWorld::RayResultCallback::CollisionObject::get()
{
	return gcnew BulletSharp::CollisionObject(_callback->m_collisionObject);
}

bool CollisionWorld::RayResultCallback::HasHit::get()
{
	return _callback->hasHit();
}

bool CollisionWorld::RayResultCallback::IsDisposed::get()
{
	return (_callback == NULL);
}

btCollisionWorld::RayResultCallback* CollisionWorld::RayResultCallback::UnmanagedPointer::get()
{
	return _callback;
}
void CollisionWorld::RayResultCallback::UnmanagedPointer::set(btCollisionWorld::RayResultCallback* value)
{
	_callback = value;
}


CollisionWorld::ClosestRayResultCallback::ClosestRayResultCallback(Vector3 rayFromWorld, Vector3 rayToWorld)
: RayResultCallback(new btCollisionWorld::ClosestRayResultCallback(
	*Math::Vector3ToBtVector3(rayFromWorld), *Math::Vector3ToBtVector3(rayToWorld)))
{
}

Vector3 CollisionWorld::ClosestRayResultCallback::HitPointWorld::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_hitPointWorld);
}
void CollisionWorld::ClosestRayResultCallback::HitPointWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_hitPointWorld);
}

btCollisionWorld::ClosestRayResultCallback* CollisionWorld::ClosestRayResultCallback::UnmanagedPointer::get()
{
	return (btCollisionWorld::ClosestRayResultCallback*)RayResultCallback::UnmanagedPointer;
}


CollisionWorld::CollisionWorld(btCollisionWorld* world)
{
	_world = world;
}

CollisionWorld::CollisionWorld(BulletSharp::Dispatcher^ dispatcher, BroadphaseInterface^ pairCache, CollisionConfiguration^ collisionConfiguration)
{
	_world = new btCollisionWorld(dispatcher->UnmanagedPointer, pairCache->UnmanagedPointer, collisionConfiguration->UnmanagedPointer);
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

CollisionWorld::~CollisionWorld()
{
	this->!CollisionWorld();
}

CollisionWorld::!CollisionWorld()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_world = NULL;
	
	OnDisposed( this, nullptr );
}

bool CollisionWorld::IsDisposed::get()
{
	return (_world == NULL);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject,
	CollisionFilterGroups collisionFilterGroup, CollisionFilterGroups collisionFilterMask)
{
	_world->addCollisionObject(collisionObject->UnmanagedPointer, (short int)collisionFilterGroup, (short int)collisionFilterMask);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject,
	CollisionFilterGroups collisionFilterGroup)
{
	_world->addCollisionObject(collisionObject->UnmanagedPointer, (short int)collisionFilterGroup);
}

void CollisionWorld::AddCollisionObject(CollisionObject^ collisionObject)
{
	_world->addCollisionObject(collisionObject->UnmanagedPointer);
}

void CollisionWorld::ContactPairTest(CollisionObject^ colObjA, CollisionObject^ colObjB, ContactResultCallback^ resultCallback)
{
	_world->contactPairTest(colObjA->UnmanagedPointer, colObjB->UnmanagedPointer, *resultCallback->UnmanagedPointer);
}

void CollisionWorld::ContactTest(CollisionObject^ colObj, ContactResultCallback^ resultCallback)
{
	_world->contactTest(colObj->UnmanagedPointer, *resultCallback->UnmanagedPointer);
}

#ifndef DISABLE_DEBUGDRAW
void CollisionWorld::DebugDrawWorld()
{
	UnmanagedPointer->debugDrawWorld();
}
#endif

void CollisionWorld::PerformDiscreteCollisionDetection()
{
	_world->performDiscreteCollisionDetection();
}

void CollisionWorld::RayTest(Vector3 rayFromWorld, Vector3 rayToWorld, RayResultCallback^ resultCallback)
{
	_world->rayTest(*Math::Vector3ToBtVector3(rayFromWorld), *Math::Vector3ToBtVector3(rayToWorld),
		*resultCallback->UnmanagedPointer);
}

void CollisionWorld::RayTestSingle(Matrix rayFromTrans, Matrix rayToTrans, CollisionObject^ collisionObject,
	CollisionShape^ collisionShape, Matrix colObjWorldTransform, RayResultCallback^ resultCallback)
{
	_world->rayTestSingle(*Math::MatrixToBtTransform(rayFromTrans), *Math::MatrixToBtTransform(rayToTrans),
		collisionObject->UnmanagedPointer, collisionShape->UnmanagedPointer,
		*Math::MatrixToBtTransform(colObjWorldTransform), *resultCallback->UnmanagedPointer);
}

void CollisionWorld::RemoveCollisionObject(CollisionObject^ collisionObject)
{
	_world->removeCollisionObject(collisionObject->UnmanagedPointer);
}

void CollisionWorld::UpdateAabbs()
{
	_world->updateAabbs();
}

void CollisionWorld::UpdateSingleAabb(CollisionObject^ colObj)
{
	_world->updateSingleAabb(colObj->UnmanagedPointer);
}

BroadphaseInterface^ CollisionWorld::Broadphase::get()
{
	return _broadphase;
}
void CollisionWorld::Broadphase::set(BroadphaseInterface^ value)
{
	_world->setBroadphase(value->UnmanagedPointer);
	_broadphase = value;
}

BulletSharp::CollisionObjectArray^ CollisionWorld::CollisionObjectArray::get()
{
	if (_collisionObjects == nullptr)
	{
		btCollisionObjectArray* objArray = new btCollisionObjectArray;
		*objArray = _world->getCollisionObjectArray();;
		_collisionObjects = gcnew BulletSharp::CollisionObjectArray(objArray);
	}
	return _collisionObjects;
}

#ifndef DISABLE_DEBUGDRAW
DebugDraw^ CollisionWorld::DebugDrawer::get()
{
	return _debugDraw;
}
void CollisionWorld::DebugDrawer::set(DebugDraw^ value)
{
	if (value == nullptr)
		_world->setDebugDrawer(0);
	else
		_world->setDebugDrawer(value->UnmanagedPointer);
}
#endif

BulletSharp::Dispatcher^ CollisionWorld::Dispatcher::get()
{
	return _dispatcher;
}

DispatcherInfo^ CollisionWorld::DispatchInfo::get()
{
	return gcnew DispatcherInfo(&_world->getDispatchInfo());;
}

bool CollisionWorld::ForceUpdateAllAabbs::get()
{
	return _world->getForceUpdateAllAabbs();
}
void CollisionWorld::ForceUpdateAllAabbs::set(bool value)
{
	_world->setForceUpdateAllAabbs(value);
}

int CollisionWorld::NumCollisionObjects::get()
{
	return _world->getNumCollisionObjects();
}

OverlappingPairCache^ CollisionWorld::PairCache::get()
{
	return _pairCache;
}

btCollisionWorld* CollisionWorld::UnmanagedPointer::get()
{
	return _world;
}
void CollisionWorld::UnmanagedPointer::set(btCollisionWorld* value)
{
	_world = value;
}
