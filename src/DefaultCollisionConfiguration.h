#pragma once

// Fully implemented as of 09 May 2010

#include "CollisionConfiguration.h"

namespace BulletSharp
{
	public ref class DefaultCollisionConstructionInfo
	{
	private:
		btDefaultCollisionConstructionInfo* _constructionInfo;

	public:
		DefaultCollisionConstructionInfo();

		property PoolAllocator^ CollisionAlgorithmPool
		{
			PoolAllocator^ get();
			void set(PoolAllocator^ value);
		}

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

		property PoolAllocator^ PersistentManifoldPool
		{
			PoolAllocator^ get();
			void set(PoolAllocator^ value);
		}

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

		void SetConvexConvexMultipointIterations(int numPerturbationIterations);
		void SetConvexConvexMultipointIterations(int numPerturbationIterations, int minimumPointsPerturbationThreshold);

	internal:
		property btDefaultCollisionConfiguration* UnmanagedPointer
		{
			btDefaultCollisionConfiguration* get() new;
		}
	};
};
