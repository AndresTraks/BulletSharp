#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionConfiguration.h"
#include "CollisionCreateFunc.h"
#include "CollisionDispatcher.h"
#include "Dispatcher.h"
#include "Enums.h"
#include "OverlappingPairCache.h"

void NearCallbackWrapper::nearCallback (btBroadphasePair& collisionPair, btCollisionDispatcherWrapper& dispatcher, const btDispatcherInfo& dispatchInfo)
{
	void* callback = dispatcher._nearCallback;
	if (callback == nullptr)
		return;
	BulletSharp::NearCallback^ callbackManaged = static_cast<BulletSharp::NearCallback^>(VoidPtrToGCHandle(callback).Target);
	callbackManaged(gcnew BroadphasePair(&collisionPair), gcnew CollisionDispatcher(&dispatcher), gcnew DispatcherInfo((btDispatcherInfo*)&dispatchInfo));
}


btCollisionDispatcherWrapper::btCollisionDispatcherWrapper(btCollisionConfiguration* collisionConfiguration)
: btCollisionDispatcher(collisionConfiguration)
{
}


CollisionDispatcher::CollisionDispatcher(btCollisionDispatcherWrapper* dispatcher)
: Dispatcher(dispatcher)
{
}

CollisionDispatcher::CollisionDispatcher(BulletSharp::CollisionConfiguration^ collisionConfiguration)
: Dispatcher(new btCollisionDispatcherWrapper(collisionConfiguration->UnmanagedPointer))
{
}

CollisionDispatcher::CollisionDispatcher()
: Dispatcher(new btCollisionDispatcherWrapper(new btDefaultCollisionConfiguration()))
{
}

void CollisionDispatcher::DefaultNearCallback(BroadphasePair^ collisionPair,
	CollisionDispatcher^ dispatcher, DispatcherInfo^ dispatchInfo)
{
	btCollisionDispatcherWrapper::defaultNearCallback(*collisionPair->UnmanagedPointer,
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

BulletSharp::NearCallback^ CollisionDispatcher::NearCallback::get()
{
	void* callback = UnmanagedPointer->_nearCallback;
	if (callback == nullptr)
		return nullptr;
	
	return static_cast<BulletSharp::NearCallback^>(VoidPtrToGCHandle(callback).Target);
}
void CollisionDispatcher::NearCallback::set(BulletSharp::NearCallback^ value)
{
	if (value == nullptr)
	{
		// Don't actually set the callback to 0 as this would crash,
		// just revert to the original internal callback.
		UnmanagedPointer->_nearCallback = nullptr;
		UnmanagedPointer->setNearCallback(originalCallback);
		return;
	}

	void* current = UnmanagedPointer->_nearCallback;
	if (current != nullptr)
		VoidPtrToGCHandle(current).Free();

	GCHandle handle = GCHandle::Alloc(value);
	UnmanagedPointer->_nearCallback = GCHandleToVoidPtr(handle);

	if (originalCallback == nullptr)
		originalCallback = UnmanagedPointer->getNearCallback();
	
	UnmanagedPointer->setNearCallback((btNearCallback)&NearCallbackWrapper::nearCallback);
}

btCollisionDispatcherWrapper* CollisionDispatcher::UnmanagedPointer::get()
{
	return (btCollisionDispatcherWrapper*)Dispatcher::UnmanagedPointer;
}
