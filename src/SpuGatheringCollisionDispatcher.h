#pragma once

#include "CollisionDispatcher.h"

namespace BulletSharp
{
	ref class CollisionConfiguration;

	namespace MultiThreaded
	{
		ref class ThreadSupportInterface;

		public ref class SpuGatheringCollisionDispatcher : CollisionDispatcher
		{
		private:
			ThreadSupportInterface^ _threadInterface;

		public:
			SpuGatheringCollisionDispatcher(ThreadSupportInterface^ threadInterface, unsigned int maxNumOutstandingTasks,
				BulletSharp::CollisionConfiguration^ collisionConfiguration);

			bool SupportsDispatchPairOnSpu(int proxyType0, int proxyType1);
		};
	};
};
