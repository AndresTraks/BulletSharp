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

#define Native static_cast<btBvhTriangleMeshShape*>(_native)

BvhTriangleMeshShape::BvhTriangleMeshShape(btBvhTriangleMeshShape* shape)
: TriangleMeshShape(shape)
{
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression)
: TriangleMeshShape(new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression))
{
	_meshInterface = meshInterface;
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, bool buildBvh)
: TriangleMeshShape(new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, buildBvh))
{
	_meshInterface = meshInterface;
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax, bool buildBvh)
: TriangleMeshShape(0)
{
	VECTOR3_DEF(bvhAabbMin);
	VECTOR3_DEF(bvhAabbMax);

	UnmanagedPointer = new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, VECTOR3_USE(bvhAabbMin), VECTOR3_USE(bvhAabbMax), buildBvh);

	VECTOR3_DEL(bvhAabbMin);
	VECTOR3_DEL(bvhAabbMax);
}

BvhTriangleMeshShape::BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax)
: TriangleMeshShape(0)
{
	VECTOR3_DEF(bvhAabbMin);
	VECTOR3_DEF(bvhAabbMax);

	UnmanagedPointer = new btBvhTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, VECTOR3_USE(bvhAabbMin), VECTOR3_USE(bvhAabbMax));

	VECTOR3_DEL(bvhAabbMin);
	VECTOR3_DEL(bvhAabbMax);
}

void BvhTriangleMeshShape::BuildOptimizedBvh()
{
	Native->buildOptimizedBvh();
}

void BvhTriangleMeshShape::PartialRefitTree(Vector3 bvhAabbMin, Vector3 bvhAabbMax)
{
	VECTOR3_DEF(bvhAabbMin);
	VECTOR3_DEF(bvhAabbMax);

	Native->partialRefitTree(VECTOR3_USE(bvhAabbMin), VECTOR3_USE(bvhAabbMax));

	VECTOR3_DEL(bvhAabbMin);
	VECTOR3_DEL(bvhAabbMax);
}

void BvhTriangleMeshShape::PerformConvexcast(TriangleCallback^ callback, Vector3 boxSource, Vector3 boxTarget, Vector3 boxMin, Vector3 boxMax)
{
	VECTOR3_DEF(boxSource);
	VECTOR3_DEF(boxTarget);
	VECTOR3_DEF(boxMin);
	VECTOR3_DEF(boxMax);

	Native->performConvexcast(callback->_native, VECTOR3_USE(boxSource),
		VECTOR3_USE(boxTarget), VECTOR3_USE(boxMin), VECTOR3_USE(boxMax));

	VECTOR3_DEL(boxSource);
	VECTOR3_DEL(boxTarget);
	VECTOR3_DEL(boxMin);
	VECTOR3_DEL(boxMax);
}

void BvhTriangleMeshShape::PerformRaycast(TriangleCallback^ callback, Vector3 raySource, Vector3 rayTarget)
{
	VECTOR3_DEF(raySource);
	VECTOR3_DEF(rayTarget);

	Native->performRaycast(callback->_native, VECTOR3_USE(raySource), VECTOR3_USE(rayTarget));

	VECTOR3_DEL(raySource);
	VECTOR3_DEL(rayTarget);
}

void BvhTriangleMeshShape::ProcessAllTriangles(TriangleCallback^ callback, Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	Native->processAllTriangles(callback->_native, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void BvhTriangleMeshShape::RecalcLocalAabb()
{
	Native->recalcLocalAabb();
}

void BvhTriangleMeshShape::RefitTree(Vector3 bvhAabbMin, Vector3 bvhAabbMax)
{
	VECTOR3_DEF(bvhAabbMin);
	VECTOR3_DEF(bvhAabbMax);

	Native->refitTree(VECTOR3_USE(bvhAabbMin), VECTOR3_USE(bvhAabbMax));

	VECTOR3_DEL(bvhAabbMin);
	VECTOR3_DEL(bvhAabbMax);
}

#ifndef DISABLE_BVH
void BvhTriangleMeshShape::SetOptimizedBvh(BulletSharp::OptimizedBvh^ bvh, Vector3 localScaling)
{
	VECTOR3_DEF(localScaling);
	Native->setOptimizedBvh(bvh->UnmanagedPointer, VECTOR3_USE(localScaling));
	VECTOR3_DEL(localScaling);
}
#endif

#ifndef DISABLE_SERIALIZE
void BvhTriangleMeshShape::SerializeSingleBvh(BulletSharp::Serializer^ serializer)
{
	Native->serializeSingleBvh(serializer->UnmanagedPointer);
}

void BvhTriangleMeshShape::SerializeSingleTriangleInfoMap(BulletSharp::Serializer^ serializer)
{
	Native->serializeSingleTriangleInfoMap(serializer->UnmanagedPointer);
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
	btOptimizedBvh* optimizedBvh = UnmanagedPointer->getOptimizedBvh();
	ReturnCachedObject(BulletSharp::OptimizedBvh, _optimizedBvh, optimizedBvh)
}
void BvhTriangleMeshShape::OptimizedBvh::set(BulletSharp::OptimizedBvh^ value)
{
	BvhTriangleMeshShape_SetOptimizedBvh(UnmanagedPointer, value->UnmanagedPointer);
}
#endif

bool BvhTriangleMeshShape::OwnsBvh::get()
{
	return Native->getOwnsBvh();
}

bool BvhTriangleMeshShape::UsesQuantizedAabbCompression::get()
{
	return Native->usesQuantizedAabbCompression();
}
