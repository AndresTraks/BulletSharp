#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionConfiguration.h"
#include "CollisionCreateFunc.h"
#include "CollisionDispatcher.h"
#include "DefaultCollisionConfiguration.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"

void nearCallback(btBroadphasePair& collisionPair, btCollisionDispatcherWrapper& dispatcher, const btDispatcherInfo& dispatchInfo)
{
	CollisionDispatcher^ collisionDispatcher = dispatcher._collisionDispatcher;
	if (collisionDispatcher->IsDisposed)
		return;
	collisionDispatcher->_nearCallback(gcnew BroadphasePair(&collisionPair), collisionDispatcher, gcnew DispatcherInfo((btDispatcherInfo*)&dispatchInfo));
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
	Native->_collisionDispatcher = this;
	_collisionConfiguration = collisionConfiguration;
}

CollisionDispatcher::CollisionDispatcher()
: Dispatcher(new btCollisionDispatcherWrapper(new btDefaultCollisionConfiguration()))
{
	Native->_collisionDispatcher = this;
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
	return _nearCallback;
}
void CollisionDispatcher::NearCallback::set(BulletSharp::NearCallback^ value)
{
	_nearCallback = value;

	if (value == nullptr)
	{
		Native->setNearCallback(btCollisionDispatcher::defaultNearCallback);
		return;
	}

	Native->setNearCallback((btNearCallback)nearCallback);
}
