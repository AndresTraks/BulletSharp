#include "StdAfx.h"

#include "CollisionConfiguration.h"

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

bool CollisionConfiguration::IsDisposed::get()
{
	return (_collisionConfiguration == NULL);
}

btCollisionConfiguration* CollisionConfiguration::UnmanagedPointer::get()
{
	return _collisionConfiguration;
}

void CollisionConfiguration::UnmanagedPointer::set( btCollisionConfiguration* value )
{
	_collisionConfiguration = value;
}
