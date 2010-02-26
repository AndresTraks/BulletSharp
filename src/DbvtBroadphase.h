#pragma once

#include "BroadphaseInterface.h"
#include "Dispatcher.h"
#include "OverlappingPairCache.h"

namespace BulletSharp
{
	public ref class DbvtBroadphase : BulletSharp::BroadphaseInterface
	{
		public:
			DbvtBroadphase(BulletSharp::OverlappingPairCache^ pairCache);
			DbvtBroadphase();

			static void Benchmark(BroadphaseInterface^ broadphase);

			void Collide(Dispatcher^ dispatcher);
			void Optimize();
			void PerformDeferredRemoval(Dispatcher^ dispatcher);

			property btScalar VelocityPrediction
			{
				btScalar get();
				void set(btScalar prediction);
			}

		internal:
			property btDbvtBroadphase* UnmanagedPointer
			{
				btDbvtBroadphase* get() new;
			}
	};
};