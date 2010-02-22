#include "StdAfx.h"

#include "CollisionWorld.h"

CollisionWorld::CollisionWorld(btCollisionWorld* world)
{
	_world = world;
}

CollisionWorld::CollisionWorld(BulletSharp::IDispatcher^ dispatcher, BroadphaseInterface^ pairCache, CollisionConfiguration^ collisionConfiguration)
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
	short int collisionFilterGroup, short int collisionFilterMask)
{
	_world->addCollisionObject(collisionObject->UnmanagedPointer, collisionFilterGroup, collisionFilterMask);
}

void CollisionWorld::PerformDiscreteCollisionDetection()
{
	_world->performDiscreteCollisionDetection();
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

DebugDraw^ CollisionWorld::DebugDrawer::get()
{
	return _debugDraw;
}
void CollisionWorld::DebugDrawer::set(DebugDraw^ value)
{
	_debugDraw = value;
	_world->setDebugDrawer(_debugDraw->_debugWrapper);
}

BulletSharp::IDispatcher^ CollisionWorld::IDispatcher::get()
{
	return _dispatcher;
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
