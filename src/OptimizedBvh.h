#pragma once

#include "QuantizedBvh.h"

namespace BulletSharp
{
	ref class StridingMeshInterface;

	public ref class OptimizedBvh : QuantizedBvh
	{
	internal:
		OptimizedBvh(btOptimizedBvh* native, bool preventDelete);

	public:
		OptimizedBvh();
#ifndef DISABLE_BVH
		void Build(StridingMeshInterface^ triangles, bool useQuantizedAabbCompression,
			Vector3 bvhAabbMin, Vector3 bvhAabbMax);
		static OptimizedBvh^ DeSerializeInPlace(IntPtr alignedDataBuffer, unsigned int dataBufferSize,
			bool swapEndian);
		void Refit(StridingMeshInterface^ triangles, Vector3 aabbMin, Vector3 aabbMax);
		void RefitPartial(StridingMeshInterface^ triangles, Vector3 aabbMin, Vector3 aabbMax);
		bool SerializeInPlace(IntPtr alignedDataBuffer, unsigned int dataBufferSize,
			bool swapEndian);
		void UpdateBvhNodes(StridingMeshInterface^ meshInterface, int firstNode,
			int endNode, int index);
#endif
	};
};
