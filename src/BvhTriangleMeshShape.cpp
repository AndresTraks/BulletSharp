#include "StdAfx.h"

#include "BvhTriangleMeshShape.h"
#include "StridingMeshInterface.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

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
: ConcaveShape(0)
{
	btVector3* bvhAabbMinTemp = Math::Vector3ToBtVector3(bvhAabbMin);
	btVector3* bvhAabbMaxTemp = Math::Vector3ToBtVector3(bvhAabbMax);

	UnmanagedPointer = new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, *bvhAabbMinTemp, *bvhAabbMaxTemp, buildBvh);

	delete bvhAabbMinTemp;
	delete bvhAabbMaxTemp;
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax)
: ConcaveShape(0)
{
	btVector3* bvhAabbMinTemp = Math::Vector3ToBtVector3(bvhAabbMin);
	btVector3* bvhAabbMaxTemp = Math::Vector3ToBtVector3(bvhAabbMax);

	UnmanagedPointer = new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, *bvhAabbMinTemp, *bvhAabbMaxTemp);

	delete bvhAabbMinTemp;
	delete bvhAabbMaxTemp;
}

void BvhTriangleMeshShape::BuildOptimizedBvh()
{
	UnmanagedPointer->buildOptimizedBvh();
}

void BvhTriangleMeshShape::PartialRefitTree(Vector3 bvhAabbMin, Vector3 bvhAabbMax)
{
	btVector3* bvhAabbMinTemp = Math::Vector3ToBtVector3(bvhAabbMin);
	btVector3* bvhAabbMaxTemp = Math::Vector3ToBtVector3(bvhAabbMax);

	UnmanagedPointer->partialRefitTree(*bvhAabbMinTemp, *bvhAabbMaxTemp);

	delete bvhAabbMinTemp;
	delete bvhAabbMaxTemp;
}

void BvhTriangleMeshShape::RecalcLocalAabb()
{
	UnmanagedPointer->recalcLocalAabb();
}

void BvhTriangleMeshShape::RefitTree(Vector3 bvhAabbMin, Vector3 bvhAabbMax)
{
	btVector3* bvhAabbMinTemp = Math::Vector3ToBtVector3(bvhAabbMin);
	btVector3* bvhAabbMaxTemp = Math::Vector3ToBtVector3(bvhAabbMax);

	UnmanagedPointer->refitTree(*bvhAabbMinTemp, *bvhAabbMaxTemp);

	delete bvhAabbMinTemp;
	delete bvhAabbMaxTemp;
}

#ifndef DISABLE_SERIALIZE
void BvhTriangleMeshShape::SerializeSingleBvh(Serializer^ serializer)
{
	UnmanagedPointer->serializeSingleBvh(serializer->UnmanagedPointer);
}

void BvhTriangleMeshShape::SerializeSingleTriangleInfoMap(Serializer^ serializer)
{
	UnmanagedPointer->serializeSingleTriangleInfoMap(serializer->UnmanagedPointer);
}
#endif

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
