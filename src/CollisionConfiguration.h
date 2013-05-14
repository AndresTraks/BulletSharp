#pragma once

#include "IDisposable.h"

namespace BulletSharp
{
	ref class CollisionAlgorithmCreateFunc;
	ref class PoolAllocator;

	public ref class CollisionConfiguration
	{
	internal:
		btCollisionConfiguration* _native;
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
	};
};
