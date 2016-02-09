#include "StdAfx.h"

#include "OptimizedBvh.h"
#include "StridingMeshInterface.h"

#define Native static_cast<btOptimizedBvh*>(_native)

OptimizedBvh::OptimizedBvh(btOptimizedBvh* native, bool preventDelete)
	: QuantizedBvh(native, preventDelete)
{
}

OptimizedBvh::OptimizedBvh()
	: QuantizedBvh(new btOptimizedBvh(), false)
{
}
#ifndef DISABLE_BVH
void OptimizedBvh::Build(StridingMeshInterface^ triangles, bool useQuantizedAabbCompression,
	Vector3 bvhAabbMin, Vector3 bvhAabbMax)
{
	VECTOR3_CONV(bvhAabbMin);
	VECTOR3_CONV(bvhAabbMax);
	Native->build(triangles->_native, useQuantizedAabbCompression, VECTOR3_USE(bvhAabbMin),
		VECTOR3_USE(bvhAabbMax));
	VECTOR3_DEL(bvhAabbMin);
	VECTOR3_DEL(bvhAabbMax);
}

OptimizedBvh^ OptimizedBvh::DeSerializeInPlace(IntPtr alignedDataBuffer, unsigned int dataBufferSize,
	bool swapEndian)
{
	if (alignedDataBuffer == IntPtr::Zero) {
		return nullptr;
	}

	btOptimizedBvh* quantizedBvhPtr = btOptimizedBvh::deSerializeInPlace(alignedDataBuffer.ToPointer(), dataBufferSize,
		swapEndian);

	return gcnew OptimizedBvh(quantizedBvhPtr, true);
}

void OptimizedBvh::Refit(StridingMeshInterface^ triangles, Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	Native->refit(triangles->_native, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void OptimizedBvh::RefitPartial(StridingMeshInterface^ triangles, Vector3 aabbMin,
	Vector3 aabbMax)
{
	VECTOR3_CONV(aabbMin);
	VECTOR3_CONV(aabbMax);
	Native->refitPartial(triangles->_native, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

bool OptimizedBvh::SerializeInPlace(IntPtr alignedDataBuffer, unsigned int dataBufferSize,
	bool swapEndian)
{
	return Native->serializeInPlace(alignedDataBuffer.ToPointer(), dataBufferSize,
		swapEndian);
}

void OptimizedBvh::UpdateBvhNodes(StridingMeshInterface^ meshInterface, int firstNode,
	int endNode, int index)
{
	Native->updateBvhNodes(meshInterface->_native, firstNode, endNode, index);
}

#endif
