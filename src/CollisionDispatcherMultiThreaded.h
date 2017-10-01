#pragma once

#include "CollisionDispatcher.h"

namespace BulletSharp
{
	ref class CollisionConfiguration;

	public ref class CollisionDispatcherMultiThreaded : CollisionDispatcher
	{
	public:
		CollisionDispatcherMultiThreaded(BulletSharp::CollisionConfiguration^ configuration, int grainSize);
		CollisionDispatcherMultiThreaded(BulletSharp::CollisionConfiguration^ configuration);
	};
}
