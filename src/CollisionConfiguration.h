#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmCreateFunc;
	ref class PoolAllocator;
	ref class StackAlloc;

	public ref class CollisionConfiguration
	{
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

#ifndef DISABLE_UNCOMMON
		property PoolAllocator^ CollisionAlgorithmPool
		{
			PoolAllocator^ get();
		}

		property PoolAllocator^ PersistentManifoldPool
		{
			PoolAllocator^ get();
		}
#endif

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
