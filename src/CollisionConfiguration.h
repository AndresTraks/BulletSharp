#pragma once

// Fully implemented as of 23 apr 2010

#include "Enums.h"
#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmCreateFunc;
	ref class PoolAllocator;
	ref class StackAlloc;

	public ref class CollisionConfiguration : BulletSharp::IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		btCollisionConfiguration* _collisionConfiguration;

	internal:
		CollisionConfiguration(btCollisionConfiguration* collisionConfiguration);

	public:
		!CollisionConfiguration();
	protected:
		~CollisionConfiguration();

	public:
		CollisionAlgorithmCreateFunc^ GetCollisionAlgorithmCreateFunc(BroadphaseNativeType proxyType0, BroadphaseNativeType proxyType1);

		property bool IsDisposed
		{
			virtual bool get();
		}

		property PoolAllocator^ CollisionAlgorithmPool
		{
			PoolAllocator^ get();
		}

		property PoolAllocator^ PersistentManifoldPool
		{
			PoolAllocator^ get();
		}

		property StackAlloc^ StackAllocator
		{
			StackAlloc^ get();
		}

	internal:
		property btCollisionConfiguration* UnmanagedPointer
		{
			virtual btCollisionConfiguration* get();
			void set(btCollisionConfiguration* value);
		}
	};
};
