#include "StdAfx.h"

#include "CollisionConfiguration.h"
#include "CollisionCreateFunc.h"
#include "CollisionDispatcher.h"
#include "Dispatcher.h"
#include "Enums.h"

CollisionDispatcher::CollisionDispatcher(CollisionConfiguration^ collisionConfiguration)
: Dispatcher(new btCollisionDispatcher(collisionConfiguration->UnmanagedPointer))
{
}

CollisionDispatcher::CollisionDispatcher()
: Dispatcher(new btCollisionDispatcher(new btDefaultCollisionConfiguration()))
{
}

void CollisionDispatcher::RegisterCollisionCreateFunc(BroadphaseNativeType proxyType0,
	BroadphaseNativeType proxyType1, CollisionAlgorithmCreateFunc^ createFunc)
{
	UnmanagedPointer->registerCollisionCreateFunc((int)proxyType0, (int)proxyType1, createFunc->UnmanagedPointer);
}

BulletSharp::NearCallback^ CollisionDispatcher::NearCallback::get()
{
	return _nearCallback;
}
void CollisionDispatcher::NearCallback::set(BulletSharp::NearCallback^ value)
{
	_nearCallback = value;
	//UnmanagedPointer->setNearCallback();
}

btCollisionDispatcher* CollisionDispatcher::UnmanagedPointer::get()
{
	return (btCollisionDispatcher*)Dispatcher::UnmanagedPointer;
}
