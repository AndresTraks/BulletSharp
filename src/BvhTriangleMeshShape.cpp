#include "StdAfx.h"

#include "BvhTriangleMeshShape.h"
#include "StridingMeshInterface.h"

BvhTriangleMeshShape::BvhTriangleMeshShape()
: ConcaveShape(new btBvhTriangleMeshShape())
{
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression)
: ConcaveShape(new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression))
{
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, bool buildBvh)
: ConcaveShape(new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, buildBvh))
{
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax, bool buildBvh)
: ConcaveShape(new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, *Math::Vector3ToBtVec3(bvhAabbMin), *Math::Vector3ToBtVec3(bvhAabbMax), buildBvh))
{
}

void BvhTriangleMeshShape::PartialRefitTree(Vector3 bvhAabbMin, Vector3 bvhAabbMax)
{
	UnmanagedPointer->partialRefitTree(*Math::Vector3ToBtVec3(bvhAabbMin), *Math::Vector3ToBtVec3(bvhAabbMax));
}

void BvhTriangleMeshShape::RecalcLocalAabb()
{
	UnmanagedPointer->recalcLocalAabb();
}

bool BvhTriangleMeshShape::OwnsBvh::get()
{
	return UnmanagedPointer->getOwnsBvh();
}

btBvhTriangleMeshShape* BvhTriangleMeshShape::UnmanagedPointer::get()
{
	return (btBvhTriangleMeshShape*)ConcaveShape::UnmanagedPointer;
}
