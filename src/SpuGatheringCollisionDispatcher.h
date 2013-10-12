#pragma once

#include "CollisionDispatcher.h"

namespace BulletSharp
{
	namespace MultiThreaded
	{
		ref class CollisionConfiguration;
		ref class ThreadSupportInterface;

		public ref class SpuGatheringCollisionDispatcher : CollisionDispatcher
		{
		private:
			ThreadSupportInterface^ _threadInterface;

		public:
			SpuGatheringCollisionDispatcher(ThreadSupportInterface^ threadInterface,
				int maxNumOutstandingTasks, BulletSharp::CollisionConfiguration^ collisionConfiguration);
		};
	};
};
