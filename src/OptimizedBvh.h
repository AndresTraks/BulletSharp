#pragma once

// Fully implemented as of 25 May 2010

#include "QuantizedBvh.h"

namespace BulletSharp
{
	ref class StridingMeshInterface;

	public ref class OptimizedBvh : QuantizedBvh
	{
	internal:
		OptimizedBvh(btOptimizedBvh* bvh);
	
	public:
		OptimizedBvh();

		void Build(StridingMeshInterface^ triangles, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax);
		void Refit(StridingMeshInterface^ triangles, Vector3 aabbMin, Vector3 aabbMax);
		void RefitPartial(StridingMeshInterface^ triangles, Vector3 aabbMin, Vector3 aabbMax);
		void UpdateBvhNodes(StridingMeshInterface^ meshInterface, int firstNode, int endNode, int index);

	internal:
		property btOptimizedBvh* UnmanagedPointer
		{
			btOptimizedBvh* get() new;
		}
	};
};
