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
: ConcaveShape(new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, *Math::Vector3ToBtVector3(bvhAabbMin), *Math::Vector3ToBtVector3(bvhAabbMax), buildBvh))
{
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax)
: ConcaveShape(new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, *Math::Vector3ToBtVector3(bvhAabbMin), *Math::Vector3ToBtVector3(bvhAabbMax)))
{
}

void BvhTriangleMeshShape::BuildOptimizedBvh()
{
	UnmanagedPointer->buildOptimizedBvh();
}

void BvhTriangleMeshShape::PartialRefitTree(Vector3 bvhAabbMin, Vector3 bvhAabbMax)
{
	UnmanagedPointer->partialRefitTree(*Math::Vector3ToBtVector3(bvhAabbMin), *Math::Vector3ToBtVector3(bvhAabbMax));
}

void BvhTriangleMeshShape::RecalcLocalAabb()
{
	UnmanagedPointer->recalcLocalAabb();
}

void BvhTriangleMeshShape::RefitTree(Vector3 bvhAabbMin, Vector3 bvhAabbMax)
{
	UnmanagedPointer->refitTree(*Math::Vector3ToBtVector3(bvhAabbMin), *Math::Vector3ToBtVector3(bvhAabbMax));
}

bool BvhTriangleMeshShape::OwnsBvh::get()
{
	return UnmanagedPointer->getOwnsBvh();
}

bool BvhTriangleMeshShape::UsesQuantizedAabbCompression::get()
{
	return UnmanagedPointer->usesQuantizedAabbCompression();
}

btBvhTriangleMeshShape* BvhTriangleMeshShape::UnmanagedPointer::get()
{
	return (btBvhTriangleMeshShape*)ConcaveShape::UnmanagedPointer;
}
