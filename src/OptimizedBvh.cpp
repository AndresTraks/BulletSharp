#include "StdAfx.h"

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
	btVector3* bvhAabbMinTemp = Math::Vector3ToBtVector3(bvhAabbMin);
	btVector3* bvhAabbMaxTemp = Math::Vector3ToBtVector3(bvhAabbMax);

	UnmanagedPointer->build(triangles->UnmanagedPointer, useQuantizedAabbCompression, *bvhAabbMinTemp, *bvhAabbMaxTemp);

	delete bvhAabbMinTemp;
	delete bvhAabbMaxTemp;
}

void OptimizedBvh::Refit(StridingMeshInterface^ triangles, Vector3 aabbMin, Vector3 aabbMax)
{
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	UnmanagedPointer->refit(triangles->UnmanagedPointer, *aabbMinTemp, *aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void OptimizedBvh::RefitPartial(StridingMeshInterface^ triangles, Vector3 aabbMin, Vector3 aabbMax)
{
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	UnmanagedPointer->refit(triangles->UnmanagedPointer, *aabbMinTemp, *aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void OptimizedBvh::UpdateBvhNodes(StridingMeshInterface^ meshInterface, int firstNode, int endNode, int index)
{
	UnmanagedPointer->updateBvhNodes(meshInterface->UnmanagedPointer, firstNode, endNode, index);
}

btOptimizedBvh* OptimizedBvh::UnmanagedPointer::get()
{
	return (btOptimizedBvh*)QuantizedBvh::UnmanagedPointer;
}
