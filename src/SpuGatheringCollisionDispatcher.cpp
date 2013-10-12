#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED

#include "CollisionConfiguration.h"
#include "SpuGatheringCollisionDispatcher.h"
#include "ThreadSupportInterface.h"

MultiThreaded::SpuGatheringCollisionDispatcher::SpuGatheringCollisionDispatcher(ThreadSupportInterface^ threadInterface,
	int maxNumOutstandingTasks, BulletSharp::CollisionConfiguration^ collisionConfiguration)
: CollisionDispatcher(new ::SpuGatheringCollisionDispatcher(threadInterface->_native,
	maxNumOutstandingTasks, collisionConfiguration->_native))
{
	_collisionConfiguration = collisionConfiguration;
	_threadInterface = threadInterface;
}

#endif
