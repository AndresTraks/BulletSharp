#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionConfiguration.h"
#include "CollisionCreateFunc.h"
#include "CollisionDispatcher.h"
#include "DefaultCollisionConfiguration.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"

#define Native static_cast<btCollisionDispatcher*>(_native)

CollisionDispatcher::CollisionDispatcher(btCollisionDispatcher* native)
	: Dispatcher(native)
{
}

void CollisionDispatcher::NearCallbackUnmanaged(IntPtr collisionPair, IntPtr dispatcher, IntPtr dispatchInfo)
{
	DispatcherInfo^ dispatcherInfoRef;
	if (_dispatcherInfoRefs->ContainsKey(dispatchInfo)) {
		dispatcherInfoRef = _dispatcherInfoRefs[dispatchInfo];
	} else {
		dispatcherInfoRef = gcnew DispatcherInfo(static_cast<btDispatcherInfo*>(dispatchInfo.ToPointer()));
	}

	_nearCallback(
		gcnew BroadphasePair(static_cast<btBroadphasePair*>(collisionPair.ToPointer())), this,
		dispatcherInfoRef);
}

CollisionDispatcher::CollisionDispatcher(BulletSharp::CollisionConfiguration^ collisionConfiguration)
	: Dispatcher(new btCollisionDispatcher(collisionConfiguration->_native))
{
	_collisionConfiguration = collisionConfiguration;
}

void CollisionDispatcher::DefaultNearCallback(BroadphasePair^ collisionPair, CollisionDispatcher^ dispatcher,
	DispatcherInfo^ dispatchInfo)
{
	btCollisionDispatcher::defaultNearCallback(*collisionPair->_native,
		*(btCollisionDispatcher*)dispatcher->_native, *dispatchInfo->_native);
}

void CollisionDispatcher::RegisterCollisionCreateFunc(BroadphaseNativeType proxyType0,
	BroadphaseNativeType proxyType1, CollisionAlgorithmCreateFunc^ createFunc)
{
	if (_collisionCreateFuncs == nullptr)
	{
		_collisionCreateFuncs = gcnew List<CollisionAlgorithmCreateFunc^>();
	}
	_collisionCreateFuncs->Add(createFunc);

	Native->registerCollisionCreateFunc((int)proxyType0, (int)proxyType1, createFunc->_native);
}

CollisionConfiguration^ CollisionDispatcher::CollisionConfiguration::get()
{
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
void CollisionDispatcher::DispatcherFlags::set(BulletSharp::DispatcherFlags flags)
{
	Native->setDispatcherFlags((int)flags);
}

BulletSharp::NearCallback^ CollisionDispatcher::NearCallback::get()
{
	return _nearCallback;
}
void CollisionDispatcher::NearCallback::set(BulletSharp::NearCallback^ nearCallback)
{
	_nearCallback = nearCallback;

	if (nearCallback == nullptr)
	{
		Native->setNearCallback(btCollisionDispatcher::defaultNearCallback);
		_nearCallbackUnmanaged = nullptr;
		return;
	}

	if (_nearCallbackUnmanaged == nullptr)
	{
		_nearCallbackUnmanaged = gcnew NearCallbackUnmanagedDelegate(this, &CollisionDispatcher::NearCallbackUnmanaged);
		_nearCallbackUnmanagedPtr = Marshal::GetFunctionPointerForDelegate(_nearCallbackUnmanaged);
	}

	Native->setNearCallback((btNearCallback)_nearCallbackUnmanagedPtr.ToPointer());
}
