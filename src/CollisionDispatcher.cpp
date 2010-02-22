#include "StdAfx.h"

#include "IDispatcher.h"
#include "CollisionConfiguration.h"
#include "CollisionDispatcher.h"

CollisionDispatcher::CollisionDispatcher(CollisionConfiguration^ collisionConfiguration)
{
	_dispatcher = new btCollisionDispatcher(collisionConfiguration->UnmanagedPointer);
}

CollisionDispatcher::CollisionDispatcher()
{
	_dispatcher = new btCollisionDispatcher(new btDefaultCollisionConfiguration());
}

btDispatcher* CollisionDispatcher::UnmanagedPointer::get()
{
	return _dispatcher;
}
