#pragma once

#include "Dispatcher.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmCreateFunc;
	ref class CollisionConfiguration;

	public delegate void NearCallback(BroadphasePair^ collisionPair,
		CollisionDispatcher^ dispatcher, DispatcherInfo^ dispatchInfo);

	public ref class CollisionDispatcher : Dispatcher
	{
	private:
		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		delegate void NearCallbackUnmanagedDelegate(IntPtr collisionPair,
			IntPtr dispatcher, IntPtr dispatchInfo);

	protected:
		CollisionConfiguration^ _collisionConfiguration;

	private:
		System::Collections::Generic::List<CollisionAlgorithmCreateFunc^>^ _collisionCreateFuncs;
		NearCallbackUnmanagedDelegate^ _nearCallbackUnmanaged;
		IntPtr _nearCallbackUnmanagedPtr;

	internal:
		NearCallback^ _nearCallback;

		CollisionDispatcher(btCollisionDispatcher* native);

	private:
		void NearCallbackUnmanaged(IntPtr  collisionPair, IntPtr dispatcher, IntPtr dispatchInfo);

	public:
		CollisionDispatcher(CollisionConfiguration^ collisionConfiguration);

		static void DefaultNearCallback(BroadphasePair^ collisionPair, CollisionDispatcher^ dispatcher,
			DispatcherInfo^ dispatchInfo);
		void RegisterCollisionCreateFunc(BroadphaseNativeType proxyType0,
			BroadphaseNativeType proxyType1, CollisionAlgorithmCreateFunc^ createFunc);

		property CollisionConfiguration^ CollisionConfiguration
		{
			BulletSharp::CollisionConfiguration^ get();
			void set(BulletSharp::CollisionConfiguration^ value);
		}

		property BulletSharp::DispatcherFlags DispatcherFlags
		{
			BulletSharp::DispatcherFlags get();
			void set(BulletSharp::DispatcherFlags value);
		}

		property BulletSharp::NearCallback^ NearCallback
		{
			BulletSharp::NearCallback^ get();
			void set(BulletSharp::NearCallback^ value);
		}
	};
};
