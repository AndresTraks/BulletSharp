#include "StdAfx.h"

#ifndef DISABLE_MULTITHREADED

#include "CollisionConfiguration.h"
#include "SpuGatheringCollisionDispatcher.h"
#include "ThreadSupportInterface.h"

#define Native static_cast<::SpuGatheringCollisionDispatcher*>(_native)

MultiThreaded::SpuGatheringCollisionDispatcher::SpuGatheringCollisionDispatcher(ThreadSupportInterface^ threadInterface,
	unsigned int maxNumOutstandingTasks, BulletSharp::CollisionConfiguration^ collisionConfiguration)
	: CollisionDispatcher(new ::SpuGatheringCollisionDispatcher(threadInterface->_native,
		maxNumOutstandingTasks, collisionConfiguration->_native))
{
	_collisionConfiguration = collisionConfiguration;
	_threadInterface = threadInterface;
}

bool MultiThreaded::SpuGatheringCollisionDispatcher::SupportsDispatchPairOnSpu(int proxyType0, int proxyType1)
{
	return Native->supportsDispatchPairOnSpu(proxyType0, proxyType1);
}

#endif
