#include "StdAfx.h"

#include "Dispatcher.h"
#include "Enums.h"
#include "CollisionConfiguration.h"
#include "CollisionDispatcher.h"

CollisionDispatcher::CollisionDispatcher(CollisionConfiguration^ collisionConfiguration)
: Dispatcher(new btCollisionDispatcher(collisionConfiguration->UnmanagedPointer))
{
}

CollisionDispatcher::CollisionDispatcher()
: Dispatcher(new btCollisionDispatcher(new btDefaultCollisionConfiguration()))
{
}

void CollisionDispatcher::RegisterCollisionCreateFunc(BulletSharp::BroadphaseNativeTypes proxyType0,
	BulletSharp::BroadphaseNativeTypes proxyType1, CollisionAlgorithmCreateFunc^ createFunc)
{
	UnmanagedPointer->registerCollisionCreateFunc((int)proxyType0, (int)proxyType1, createFunc->UnmanagedPointer);
}

btCollisionDispatcher* CollisionDispatcher::UnmanagedPointer::get()
{
	return (btCollisionDispatcher*)Dispatcher::UnmanagedPointer;
}
