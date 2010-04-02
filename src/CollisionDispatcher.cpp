#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionConfiguration.h"
#include "CollisionCreateFunc.h"
#include "CollisionDispatcher.h"
#include "Dispatcher.h"
#include "Enums.h"
#include "OverlappingPairCache.h"

CollisionDispatcher::CollisionDispatcher(BulletSharp::CollisionConfiguration^ collisionConfiguration)
: Dispatcher(new btCollisionDispatcher(collisionConfiguration->UnmanagedPointer))
{
}

CollisionDispatcher::CollisionDispatcher()
: Dispatcher(new btCollisionDispatcher(new btDefaultCollisionConfiguration()))
{
}

void CollisionDispatcher::DefaultNearCallback(BroadphasePair^ collisionPair,
	CollisionDispatcher^ dispatcher, DispatcherInfo^ dispatchInfo)
{
	btCollisionDispatcher::defaultNearCallback(*collisionPair->UnmanagedPointer,
		*dispatcher->UnmanagedPointer, *dispatchInfo->UnmanagedPointer);
}

void CollisionDispatcher::DispatchAllCollisionPairs(OverlappingPairCache^ pairCache,
	DispatcherInfo^ dispatchInfo, Dispatcher^ dispatcher)
{
	UnmanagedPointer->dispatchAllCollisionPairs(pairCache->UnmanagedPointer,
		*dispatchInfo->UnmanagedPointer, dispatcher->UnmanagedPointer);
}

void CollisionDispatcher::RegisterCollisionCreateFunc(BroadphaseNativeType proxyType0,
	BroadphaseNativeType proxyType1, CollisionAlgorithmCreateFunc^ createFunc)
{
	UnmanagedPointer->registerCollisionCreateFunc((int)proxyType0, (int)proxyType1, createFunc->UnmanagedPointer);
}

CollisionConfiguration^ CollisionDispatcher::CollisionConfiguration::get()
{
	return gcnew BulletSharp::CollisionConfiguration(UnmanagedPointer->getCollisionConfiguration());
}
void CollisionDispatcher::CollisionConfiguration::set(BulletSharp::CollisionConfiguration^ value)
{
	UnmanagedPointer->setCollisionConfiguration(value->UnmanagedPointer);
}

DispatcherFlags CollisionDispatcher::DispatcherFlags::get()
{
	return (BulletSharp::DispatcherFlags)UnmanagedPointer->getDispatcherFlags();
}
void CollisionDispatcher::DispatcherFlags::set(BulletSharp::DispatcherFlags value)
{
	UnmanagedPointer->setDispatcherFlags((int)value);
}

/*
BulletSharp::NearCallback^ CollisionDispatcher::NearCallback::get()
{
	return _nearCallback;
}
void CollisionDispatcher::NearCallback::set(BulletSharp::NearCallback^ value)
{
	_nearCallback = value;
	UnmanagedPointer->setNearCallback(value->UnmanagedPointer);
}
*/
btCollisionDispatcher* CollisionDispatcher::UnmanagedPointer::get()
{
	return (btCollisionDispatcher*)Dispatcher::UnmanagedPointer;
}
