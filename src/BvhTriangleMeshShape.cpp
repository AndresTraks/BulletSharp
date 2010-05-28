#include "StdAfx.h"

#include "BvhTriangleMeshShape.h"
#include "StridingMeshInterface.h"
#include "TriangleCallback.h"
#ifndef DISABLE_BVH
#include "OptimizedBvh.h"
#endif
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

BvhTriangleMeshShape::BvhTriangleMeshShape(btBvhTriangleMeshShape* shape)
: TriangleMeshShape(shape)
{
}

BvhTriangleMeshShape::BvhTriangleMeshShape()
: TriangleMeshShape(new btBvhTriangleMeshShape())
{
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression)
: TriangleMeshShape(new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression))
{
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, bool buildBvh)
: TriangleMeshShape(new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, buildBvh))
{
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax, bool buildBvh)
: TriangleMeshShape(0)
{
	btVector3* bvhAabbMinTemp = Math::Vector3ToBtVector3(bvhAabbMin);
	btVector3* bvhAabbMaxTemp = Math::Vector3ToBtVector3(bvhAabbMax);

	UnmanagedPointer = new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, *bvhAabbMinTemp, *bvhAabbMaxTemp, buildBvh);

	delete bvhAabbMinTemp;
	delete bvhAabbMaxTemp;
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax)
: TriangleMeshShape(0)
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

void BvhTriangleMeshShape::PerformConvexcast(TriangleCallback^ callback, Vector3 boxSource, Vector3 boxTarget, Vector3 boxMin, Vector3 boxMax)
{
	btVector3* boxSourceTemp = Math::Vector3ToBtVector3(boxSource);
	btVector3* boxTargetTemp = Math::Vector3ToBtVector3(boxTarget);
	btVector3* boxMinTemp = Math::Vector3ToBtVector3(boxMin);
	btVector3* boxMaxTemp = Math::Vector3ToBtVector3(boxMax);

	UnmanagedPointer->performConvexcast(callback->UnmanagedPointer, *boxSourceTemp, *boxTargetTemp, *boxMinTemp, *boxMaxTemp);

	delete boxSourceTemp;
	delete boxTargetTemp;
	delete boxMinTemp;
	delete boxMaxTemp;
}

void BvhTriangleMeshShape::PerformRaycast(TriangleCallback^ callback, Vector3 raySource, Vector3 rayTarget)
{
	btVector3* raySourceTemp = Math::Vector3ToBtVector3(raySource);
	btVector3* rayTargetTemp = Math::Vector3ToBtVector3(rayTarget);

	UnmanagedPointer->performRaycast(callback->UnmanagedPointer, *rayTargetTemp, *rayTargetTemp);

	delete raySourceTemp;
	delete rayTargetTemp;
}

void BvhTriangleMeshShape::ProcessAllTriangles(TriangleCallback^ callback, Vector3 aabbMin, Vector3 aabbMax)
{
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	UnmanagedPointer->processAllTriangles(callback->UnmanagedPointer, *aabbMinTemp, *aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
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

#ifndef DISABLE_BVH
void BvhTriangleMeshShape::SetOptimizedBvh(BulletSharp::OptimizedBvh^ bvh, Vector3 localScaling)
{
	btVector3* localScalingTemp = Math::Vector3ToBtVector3(localScaling);
	UnmanagedPointer->setOptimizedBvh(bvh->UnmanagedPointer, *localScalingTemp);
	delete localScalingTemp;
}
#endif

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

#ifndef DISABLE_BVH
#pragma managed(push, off)
void BvhTriangleMeshShape_SetOptimizedBvh(btBvhTriangleMeshShape* shape, btOptimizedBvh* bvh)
{
	shape->setOptimizedBvh(bvh);
}
#pragma managed(pop)
OptimizedBvh^ BvhTriangleMeshShape::OptimizedBvh::get()
{
	return gcnew BulletSharp::OptimizedBvh(UnmanagedPointer->getOptimizedBvh());
}
void BvhTriangleMeshShape::OptimizedBvh::set(BulletSharp::OptimizedBvh^ value)
{
	BvhTriangleMeshShape_SetOptimizedBvh(UnmanagedPointer, value->UnmanagedPointer);
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
