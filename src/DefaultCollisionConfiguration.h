#pragma once

#include "CollisionConfiguration.h"

namespace BulletSharp
{
	public ref class DefaultCollisionConstructionInfo
	{
	private:
		btDefaultCollisionConstructionInfo* _constructionInfo;

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

		property int DefaultStackAllocatorSize
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

		property StackAlloc^ StackAllocator
		{
			StackAlloc^ get();
			void set(StackAlloc^ value);
		}

		property int UseEpaPenetrationAlgorithm
		{
			int get();
			void set(int value);
		}

	internal:
		property btDefaultCollisionConstructionInfo* UnmanagedPointer
		{
			virtual btDefaultCollisionConstructionInfo* get();
			void set(btDefaultCollisionConstructionInfo* value);
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

	internal:
		property btDefaultCollisionConfiguration* UnmanagedPointer
		{
			btDefaultCollisionConfiguration* get() new;
		}
	};
};
