#include "StdAfx.h"

#ifndef DISABLE_BVH

#include "OptimizedBvh.h"
#include "StridingMeshInterface.h"

OptimizedBvh::OptimizedBvh(btOptimizedBvh* bvh)
: QuantizedBvh(bvh)
{
}

OptimizedBvh::OptimizedBvh()
: QuantizedBvh(new btOptimizedBvh())
{
}

void OptimizedBvh::Build(StridingMeshInterface^ triangles, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax)
{
	VECTOR3_DEF(bvhAabbMin);
	VECTOR3_DEF(bvhAabbMax);

	UnmanagedPointer->build(triangles->UnmanagedPointer, useQuantizedAabbCompression,
		VECTOR3_USE(bvhAabbMin), VECTOR3_USE(bvhAabbMax));

	VECTOR3_DEL(bvhAabbMin);
	VECTOR3_DEL(bvhAabbMax);
}

void OptimizedBvh::Refit(StridingMeshInterface^ triangles, Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	UnmanagedPointer->refit(triangles->UnmanagedPointer, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void OptimizedBvh::RefitPartial(StridingMeshInterface^ triangles, Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	UnmanagedPointer->refitPartial(triangles->UnmanagedPointer, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void OptimizedBvh::UpdateBvhNodes(StridingMeshInterface^ meshInterface, int firstNode, int endNode, int index)
{
	UnmanagedPointer->updateBvhNodes(meshInterface->UnmanagedPointer, firstNode, endNode, index);
}

btOptimizedBvh* OptimizedBvh::UnmanagedPointer::get()
{
	return (btOptimizedBvh*)QuantizedBvh::UnmanagedPointer;
}

#endif