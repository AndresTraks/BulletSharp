#include "StdAfx.h"

#include "PolyhedralConvexShape.h"
#ifndef DISABLE_UNCOMMON
#include "ConvexPolyhedron.h"
#endif

#define Native static_cast<btPolyhedralConvexShape*>(_native)

PolyhedralConvexShape::PolyhedralConvexShape(btPolyhedralConvexShape* native)
	: ConvexInternalShape(native)
{
}

void PolyhedralConvexShape::GetEdge(int index, [Out] Vector3% pointA, [Out] Vector3% pointB)
{
	btVector3* paTemp = ALIGNED_NEW(btVector3);
	btVector3* pbTemp = ALIGNED_NEW(btVector3);

	Native->getEdge(index, *paTemp, *pbTemp);

	Math::BtVector3ToVector3(paTemp, pointA);
	Math::BtVector3ToVector3(pbTemp, pointB);

	ALIGNED_FREE(paTemp);
	ALIGNED_FREE(pbTemp);
}

void PolyhedralConvexShape::GetPlane([Out] Vector3% planeNormal, [Out] Vector3% planeSupport, int index)
{
	btVector3* planeNormalTemp = ALIGNED_NEW(btVector3);
	btVector3* planeSupportTemp = ALIGNED_NEW(btVector3);

	Native->getPlane(*planeNormalTemp, *planeSupportTemp, index);

	Math::BtVector3ToVector3(planeNormalTemp, planeNormal);
	Math::BtVector3ToVector3(planeSupportTemp, planeSupport);

	ALIGNED_FREE(planeNormalTemp);
	ALIGNED_FREE(planeSupportTemp);
}

void PolyhedralConvexShape::GetVertex(int index, [Out] Vector3% vertex)
{
	btVector3* vtxTemp = ALIGNED_NEW(btVector3);

	Native->getVertex(index, *vtxTemp);

	Math::BtVector3ToVector3(vtxTemp, vertex);
	ALIGNED_FREE(vtxTemp);
}

bool PolyhedralConvexShape::InitializePolyhedralFeatures(int shiftVerticesByMargin)
{
	return Native->initializePolyhedralFeatures(shiftVerticesByMargin);
}

bool PolyhedralConvexShape::InitializePolyhedralFeatures()
{
	return Native->initializePolyhedralFeatures();
}

bool PolyhedralConvexShape::IsInside(Vector3 point, btScalar tolerance)
{
	VECTOR3_CONV(point);
	bool ret = Native->isInside(VECTOR3_USE(point), tolerance);
	VECTOR3_DEL(point);
	return ret;
}

#ifndef DISABLE_UNCOMMON
ConvexPolyhedron^ PolyhedralConvexShape::ConvexPolyhedron::get()
{
	btConvexPolyhedron* convexPolyhedron = (btConvexPolyhedron*)Native->getConvexPolyhedron();
	ReturnCachedObjectGcnewNullable(BulletSharp::ConvexPolyhedron, _convexPolyhedron, convexPolyhedron);
}
#endif

int PolyhedralConvexShape::NumEdges::get()
{
	return Native->getNumEdges();
}

int PolyhedralConvexShape::NumPlanes::get()
{
	return Native->getNumPlanes();
}

int PolyhedralConvexShape::NumVertices::get()
{
	return Native->getNumVertices();
}


#undef Native
#define Native static_cast<btPolyhedralConvexAabbCachingShape*>(_native)

PolyhedralConvexAabbCachingShape::PolyhedralConvexAabbCachingShape(btPolyhedralConvexAabbCachingShape* native)
	: PolyhedralConvexShape(native)
{
}

void PolyhedralConvexAabbCachingShape::GetNonvirtualAabb(Matrix trans, [Out] Vector3% aabbMin,
	[Out] Vector3% aabbMax, btScalar margin)
{
	TRANSFORM_CONV(trans);
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	Native->getNonvirtualAabb(TRANSFORM_USE(trans), *aabbMinTemp, *aabbMinTemp,
		margin);
	TRANSFORM_DEL(trans);
	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);
	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

void PolyhedralConvexAabbCachingShape::RecalcLocalAabb()
{
	Native->recalcLocalAabb();
}
