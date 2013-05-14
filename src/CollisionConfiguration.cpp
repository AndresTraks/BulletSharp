#include "StdAfx.h"

#include "CollisionConfiguration.h"
#include "CollisionCreateFunc.h"
#ifndef DISABLE_UNCOMMON
#include "PoolAllocator.h"
#endif

CollisionConfiguration::CollisionConfiguration(btCollisionConfiguration* collisionConfiguration)
{
	_native = collisionConfiguration;
}

CollisionConfiguration::~CollisionConfiguration()
{
	this->!CollisionConfiguration();
}

CollisionConfiguration::!CollisionConfiguration()
{
	delete _native;
	_native = NULL;
}

CollisionAlgorithmCreateFunc^ CollisionConfiguration::GetCollisionAlgorithmCreateFunc(BroadphaseNativeType proxyType0, BroadphaseNativeType proxyType1)
{
	return gcnew CollisionAlgorithmCreateFunc(_native->getCollisionAlgorithmCreateFunc((int)proxyType0, (int)proxyType1));
}

bool CollisionConfiguration::IsDisposed::get()
{
	return (_native == NULL);
}

#ifndef DISABLE_UNCOMMON
PoolAllocator^ CollisionConfiguration::CollisionAlgorithmPool::get()
{
	return gcnew PoolAllocator(_native->getCollisionAlgorithmPool());
}

PoolAllocator^ CollisionConfiguration::PersistentManifoldPool::get()
{
	return gcnew PoolAllocator(_native->getPersistentManifoldPool());
}
#endif
