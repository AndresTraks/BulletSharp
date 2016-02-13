#include "StdAfx.h"

#include "CollisionConfiguration.h"
#ifndef DISABLE_UNCOMMON
#include "PoolAllocator.h"
#endif

CollisionConfiguration::CollisionConfiguration(btCollisionConfiguration* native,
	PoolAllocator^ collisionAlgorithmPool, PoolAllocator^ persistentManifoldPool)
{
	_native = native;
	_collisionAlgorithmPool = collisionAlgorithmPool;
	_persistentManifoldPool = persistentManifoldPool;
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

bool CollisionConfiguration::IsDisposed::get()
{
	return (_native == NULL);
}

#ifndef DISABLE_UNCOMMON
PoolAllocator^ CollisionConfiguration::CollisionAlgorithmPool::get()
{
	if (!_collisionAlgorithmPool)
	{
		_collisionAlgorithmPool = gcnew PoolAllocator(_native->getCollisionAlgorithmPool(), true);
	}
	return _collisionAlgorithmPool;
}

PoolAllocator^ CollisionConfiguration::PersistentManifoldPool::get()
{
	if (!_persistentManifoldPool)
	{
		_persistentManifoldPool = gcnew PoolAllocator(_native->getPersistentManifoldPool(), true);
	}
	return _persistentManifoldPool;
}
#endif
