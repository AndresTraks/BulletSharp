#include "StdAfx.h"

#include "CollisionConfiguration.h"
#include "CollisionCreateFunc.h"
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
