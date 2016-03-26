#pragma once

namespace BulletSharp
{
	ref class CollisionAlgorithmCreateFunc;
	ref class PoolAllocator;

	public ref class CollisionConfiguration abstract
	{
	internal:
		btCollisionConfiguration* _native;

		CollisionConfiguration(btCollisionConfiguration* native, PoolAllocator^ collisionAlgorithmPool,
			PoolAllocator^ persistentManifoldPool);

	private:
		PoolAllocator^ _collisionAlgorithmPool;
		PoolAllocator^ _persistentManifoldPool;

		~CollisionConfiguration();
		!CollisionConfiguration();

	public:
		virtual CollisionAlgorithmCreateFunc^ GetCollisionAlgorithmCreateFunc(BroadphaseNativeType proxyType0,
			BroadphaseNativeType proxyType1) = 0;

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
