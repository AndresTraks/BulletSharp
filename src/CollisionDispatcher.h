#pragma once

#include "Dispatcher.h"

namespace BulletSharp
{
	ref class CollisionConfiguration;
	ref class CollisionAlgorithmCreateFunc;

	//public delegate void NearCallback(BroadphasePair^ collisionPair,
	//	CollisionDispatcher^ dispatcher, DispatcherInfo^ dispatchInfo);

	public ref class CollisionDispatcher : Dispatcher
	{
	//private:
	//	NearCallback^ _nearCallback;
	public:
		CollisionDispatcher(CollisionConfiguration^ collisionConfiguration);
		CollisionDispatcher();

		static void DefaultNearCallback(BroadphasePair^ collisionPair,
			CollisionDispatcher^ dispatcher, DispatcherInfo^ dispatchInfo);

		void DispatchAllCollisionPairs(OverlappingPairCache^ pairCache,
			DispatcherInfo^ dispatchInfo, Dispatcher^ dispatcher);
		void RegisterCollisionCreateFunc(BroadphaseNativeType proxyType0,
			BroadphaseNativeType proxyType1, CollisionAlgorithmCreateFunc^ createFunc);

		property CollisionConfiguration^ CollisionConfiguration
		{
			BulletSharp::CollisionConfiguration^ get();
			void set(BulletSharp::CollisionConfiguration^ value);
		}

		property DispatcherFlags DispatcherFlags
		{
			BulletSharp::DispatcherFlags get();
			void set(BulletSharp::DispatcherFlags value);
		}
/*
		property BulletSharp::NearCallback^ NearCallback
		{
			BulletSharp::NearCallback^ get();
			void set(BulletSharp::NearCallback^ value);
		}
*/
		property btCollisionDispatcher* UnmanagedPointer
		{
			virtual btCollisionDispatcher* get() new;
		}
	};
};
