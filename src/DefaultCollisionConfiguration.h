#pragma once

#include "CollisionConfiguration.h"

namespace BulletSharp
{
	public ref class DefaultCollisionConstructionInfo
	{
	internal:
		btDefaultCollisionConstructionInfo* _native;
		
	private:
		PoolAllocator^ _collisionAlgorithmPool;
		PoolAllocator^ _persistentManifoldPool;

	public:
		DefaultCollisionConstructionInfo();

#ifndef DISABLE_UNCOMMON
		property PoolAllocator^ CollisionAlgorithmPool
		{
			PoolAllocator^ get();
			void set(PoolAllocator^ value);
		}
#endif

		property int CustomCollisionAlgorithmMaxElementSize
		{
			int get();
			void set(int value);
		}

		property int DefaultMaxCollisionAlgorithmPoolSize
		{
			int get();
			void set(int value);
		}

		property int DefaultMaxPersistentManifoldPoolSize
		{
			int get();
			void set(int value);
		}

#ifndef DISABLE_UNCOMMON
		property PoolAllocator^ PersistentManifoldPool
		{
			PoolAllocator^ get();
			void set(PoolAllocator^ value);
		}
#endif

		property int UseEpaPenetrationAlgorithm
		{
			int get();
			void set(int value);
		}
	};

	public ref class DefaultCollisionConfiguration : CollisionConfiguration
	{
	internal:
		DefaultCollisionConfiguration(btDefaultCollisionConfiguration* conf);

	public:
		DefaultCollisionConfiguration(DefaultCollisionConstructionInfo^ constructionInfo);
		DefaultCollisionConfiguration();

		void SetConvexConvexMultipointIterations();
		void SetConvexConvexMultipointIterations(int numPerturbationIterations);
		void SetConvexConvexMultipointIterations(int numPerturbationIterations, int minimumPointsPerturbationThreshold);
		void SetPlaneConvexMultipointIterations();
		void SetPlaneConvexMultipointIterations(int numPerturbationIterations);
		void SetPlaneConvexMultipointIterations(int numPerturbationIterations, int minimumPointsPerturbationThreshold);
	};
};
