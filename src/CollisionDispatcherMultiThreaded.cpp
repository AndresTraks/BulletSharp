#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADING

#include "CollisionConfiguration.h"
#include "CollisionDispatcherMultiThreaded.h"

BulletSharp::CollisionDispatcherMultiThreaded::CollisionDispatcherMultiThreaded(
	BulletSharp::CollisionConfiguration^ configuration, int grainSize)
	: CollisionDispatcher(new btCollisionDispatcherMt(configuration->_native, grainSize))
{
	_collisionConfiguration = configuration;
}

BulletSharp::CollisionDispatcherMultiThreaded::CollisionDispatcherMultiThreaded(
	BulletSharp::CollisionConfiguration^ configuration)
	: CollisionDispatcherMultiThreaded(configuration, 40)
{
}

#endif
