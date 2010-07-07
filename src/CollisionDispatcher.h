#pragma once

// Fully implemented as of 07 May 2010

#include "Dispatcher.h"

namespace BulletSharp
{
	ref class CollisionConfiguration;
	ref class CollisionAlgorithmCreateFunc;

	public delegate void NearCallback(BroadphasePair^ collisionPair,
		CollisionDispatcher^ dispatcher, DispatcherInfo^ dispatchInfo);

	class btCollisionDispatcherWrapper : public btCollisionDispatcher
	{
	public:
		void* _nearCallback;

	public:
		btCollisionDispatcherWrapper (btCollisionConfiguration* collisionConfiguration);
	};

	class NearCallbackWrapper
	{
	public:
		static void nearCallback (btBroadphasePair& collisionPair, btCollisionDispatcherWrapper& dispatcher, const btDispatcherInfo& dispatchInfo);
	};

	public ref class CollisionDispatcher : Dispatcher
	{
	private:
		btNearCallback originalCallback;

	internal:
		CollisionDispatcher(btCollisionDispatcher* dispatcher);

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

		property BulletSharp::NearCallback^ NearCallback
		{
			BulletSharp::NearCallback^ get();
			void set(BulletSharp::NearCallback^ value);
		}

		property btCollisionDispatcherWrapper* UnmanagedPointer
		{
			virtual btCollisionDispatcherWrapper* get() new;
		}
	};
};
