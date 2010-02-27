#pragma once

#include "Dispatcher.h"

namespace BulletSharp
{
	ref class CollisionConfiguration;
	ref class CollisionAlgorithmCreateFunc;

	public delegate void NearCallback(BroadphasePair^ collisionPair,
		CollisionDispatcher^ dispatcher, DispatcherInfo^ dispatchInfo);

	public ref class CollisionDispatcher : Dispatcher
	{
	private:
		BulletSharp::NearCallback^ _nearCallback;
	public:
		CollisionDispatcher(CollisionConfiguration^ collisionConfiguration);
		CollisionDispatcher();

		void RegisterCollisionCreateFunc(BroadphaseNativeType proxyType0,
			BroadphaseNativeType proxyType1, CollisionAlgorithmCreateFunc^ createFunc);

		property BulletSharp::NearCallback^ NearCallback
		{
			BulletSharp::NearCallback^ get();
			void set(BulletSharp::NearCallback^ value);
		}

		property btCollisionDispatcher* UnmanagedPointer
		{
			virtual btCollisionDispatcher* get() new;
		}
	};
};
