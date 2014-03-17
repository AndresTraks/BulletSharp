#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionConfiguration.h"
#include "CollisionCreateFunc.h"
#include "CollisionDispatcher.h"
#include "DefaultCollisionConfiguration.h"
#include "Dispatcher.h"
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


#define Native static_cast<btCollisionDispatcherWrapper*>(_native)

CollisionDispatcher::CollisionDispatcher(btCollisionDispatcher* native)
	: Dispatcher(native)
{
}

CollisionDispatcher::CollisionDispatcher(BulletSharp::CollisionConfiguration^ collisionConfiguration)
	: Dispatcher(new btCollisionDispatcherWrapper(collisionConfiguration->_native))
{
	_collisionConfiguration = collisionConfiguration;
}

CollisionDispatcher::CollisionDispatcher()
: Dispatcher(new btCollisionDispatcherWrapper(new btDefaultCollisionConfiguration()))
{
}

void CollisionDispatcher::DefaultNearCallback(BroadphasePair^ collisionPair, CollisionDispatcher^ dispatcher,
	DispatcherInfo^ dispatchInfo)
{
	btCollisionDispatcherWrapper::defaultNearCallback(*collisionPair->_native,
		*(btCollisionDispatcher*)dispatcher->_native, *dispatchInfo->_native);
}

void CollisionDispatcher::RegisterCollisionCreateFunc(BroadphaseNativeType proxyType0,
	BroadphaseNativeType proxyType1, CollisionAlgorithmCreateFunc^ createFunc)
{
	if (_collisionCreateFuncs == nullptr)
	{
		_collisionCreateFuncs = gcnew System::Collections::Generic::List<CollisionAlgorithmCreateFunc^>();
	}
	_collisionCreateFuncs->Add(createFunc);

	Native->registerCollisionCreateFunc((int)proxyType0, (int)proxyType1, createFunc->_native);
}

CollisionConfiguration^ CollisionDispatcher::CollisionConfiguration::get()
{
	if (_collisionConfiguration == nullptr)
	{
		_collisionConfiguration = gcnew DefaultCollisionConfiguration((btDefaultCollisionConfiguration*)Native->getCollisionConfiguration());
	}
	return _collisionConfiguration;
}
void CollisionDispatcher::CollisionConfiguration::set(BulletSharp::CollisionConfiguration^ config)
{
	_collisionConfiguration = config;
	Native->setCollisionConfiguration(config->_native);
}

DispatcherFlags CollisionDispatcher::DispatcherFlags::get()
{
	return (BulletSharp::DispatcherFlags)Native->getDispatcherFlags();
}
void CollisionDispatcher::DispatcherFlags::set(BulletSharp::DispatcherFlags value)
{
	Native->setDispatcherFlags((int)value);
}

BulletSharp::NearCallback^ CollisionDispatcher::NearCallback::get()
{
	void* callback = Native->_nearCallback;
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
		Native->_nearCallback = nullptr;
		Native->setNearCallback(originalCallback);
		return;
	}

	void* current = Native->_nearCallback;
	if (current != nullptr)
		VoidPtrToGCHandle(current).Free();

	GCHandle handle = GCHandle::Alloc(value);
	Native->_nearCallback = GCHandleToVoidPtr(handle);

	if (originalCallback == nullptr)
		originalCallback = Native->getNearCallback();
	
	Native->setNearCallback((btNearCallback)&NearCallbackWrapper::nearCallback);
}
