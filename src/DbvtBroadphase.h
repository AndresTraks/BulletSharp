#pragma once

#include "BroadphaseInterface.h"

namespace BulletSharp
{
	ref class Dispatcher;
	ref class OverlappingPairCache;

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