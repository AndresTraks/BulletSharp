#pragma once

#include "CollisionConfiguration.h"

namespace BulletSharp
{
	ref class VoronoiSimplexSolver;

	public ref class DefaultCollisionConstructionInfo : IDisposable
	{
	internal:
		btDefaultCollisionConstructionInfo* _native;
		
	private:
		PoolAllocator^ _collisionAlgorithmPool;
		PoolAllocator^ _persistentManifoldPool;

	public:
		!DefaultCollisionConstructionInfo();
	protected:
		~DefaultCollisionConstructionInfo();

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
		DefaultCollisionConfiguration(btDefaultCollisionConfiguration* native);

	private:
		VoronoiSimplexSolver^ _simplexSolver;

	public:
		DefaultCollisionConfiguration(DefaultCollisionConstructionInfo^ constructionInfo);
		DefaultCollisionConfiguration();

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
