#pragma once

#include "CollisionConfiguration.h"

namespace BulletSharp
{
	ref class VoronoiSimplexSolver;

	public ref class DefaultCollisionConstructionInfo
	{
	internal:
		btDefaultCollisionConstructionInfo* _native;

	private:
		PoolAllocator^ _collisionAlgorithmPool;
		PoolAllocator^ _persistentManifoldPool;

		~DefaultCollisionConstructionInfo();
		!DefaultCollisionConstructionInfo();

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
		DefaultCollisionConfiguration(btDefaultCollisionConfiguration* native, PoolAllocator^ collisionAlgorithmPool,
			PoolAllocator^ persistentManifoldPool);

	private:
		VoronoiSimplexSolver^ _simplexSolver;

	public:
		DefaultCollisionConfiguration(DefaultCollisionConstructionInfo^ constructionInfo);
		DefaultCollisionConfiguration();

		virtual CollisionAlgorithmCreateFunc^ GetCollisionAlgorithmCreateFunc(BroadphaseNativeType proxyType0,
			BroadphaseNativeType proxyType1) override;
		void SetConvexConvexMultipointIterations(int numPerturbationIterations, int minimumPointsPerturbationThreshold);
		void SetConvexConvexMultipointIterations(int numPerturbationIterations);
		void SetConvexConvexMultipointIterations();
		void SetPlaneConvexMultipointIterations(int numPerturbationIterations, int minimumPointsPerturbationThreshold);
		void SetPlaneConvexMultipointIterations(int numPerturbationIterations);
		void SetPlaneConvexMultipointIterations();
#ifndef DISABLE_UNCOMMON
		property VoronoiSimplexSolver^ SimplexSolver
		{
			VoronoiSimplexSolver^ get();
		}
#endif
	};
};
