#include "StdAfx.h"

#include "CollisionConfiguration.h"
#include "CollisionCreateFunc.h"
#include "PoolAllocator.h"
#include "StackAlloc.h"

CollisionConfiguration::CollisionConfiguration(btCollisionConfiguration* collisionConfiguration)
{
	_collisionConfiguration = collisionConfiguration;
}

CollisionConfiguration::~CollisionConfiguration()
{
	this->!CollisionConfiguration();
}

CollisionConfiguration::!CollisionConfiguration()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_collisionConfiguration = NULL;
	
	OnDisposed( this, nullptr );
}

CollisionAlgorithmCreateFunc^ CollisionConfiguration::GetCollisionAlgorithmCreateFunc(BroadphaseNativeType proxyType0, BroadphaseNativeType proxyType1)
{
	return gcnew CollisionAlgorithmCreateFunc(_collisionConfiguration->getCollisionAlgorithmCreateFunc((int)proxyType0, (int)proxyType1));
}

bool CollisionConfiguration::IsDisposed::get()
{
	return (_collisionConfiguration == NULL);
}

PoolAllocator^ CollisionConfiguration::CollisionAlgorithmPool::get()
{
	return gcnew PoolAllocator(_collisionConfiguration->getCollisionAlgorithmPool());
}

PoolAllocator^ CollisionConfiguration::PersistentManifoldPool::get()
{
	return gcnew PoolAllocator(_collisionConfiguration->getPersistentManifoldPool());
}

StackAlloc^ CollisionConfiguration::StackAllocator::get()
{
	return gcnew StackAlloc(_collisionConfiguration->getStackAllocator());
}

btCollisionConfiguration* CollisionConfiguration::UnmanagedPointer::get()
{
	return _collisionConfiguration;
}
void CollisionConfiguration::UnmanagedPointer::set( btCollisionConfiguration* value )
{
	_collisionConfiguration = value;
}
