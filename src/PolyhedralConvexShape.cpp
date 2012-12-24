#include "StdAfx.h"

#include "PolyhedralConvexShape.h"
#ifndef DISABLE_UNCOMMON
#include "ConvexPolyhedron.h"
#endif

#define Native static_cast<btPolyhedralConvexShape*>(_native)

PolyhedralConvexShape::PolyhedralConvexShape(btPolyhedralConvexShape* polyhedralConvexShape)
: BulletSharp::ConvexInternalShape(polyhedralConvexShape)
{
}

void PolyhedralConvexShape::GetEdge(int index, [Out] Vector3% pointA, [Out] Vector3% pointB)
{
	btVector3* paTemp = new btVector3;
	btVector3* pbTemp = new btVector3;

	Native->getEdge(index, *paTemp, *pbTemp);

	Math::BtVector3ToVector3(paTemp, pointA);
	Math::BtVector3ToVector3(pbTemp, pointB);

	delete paTemp;
	delete pbTemp;
}

void PolyhedralConvexShape::GetPlane([Out] Vector3% planeNormal, [Out] Vector3% planeSupport, int index)
{
	btVector3* planeNormalTemp = new btVector3;
	btVector3* planeSupportTemp = new btVector3;

	Native->getPlane(*planeNormalTemp, *planeSupportTemp, index);

	Math::BtVector3ToVector3(planeNormalTemp, planeNormal);
	Math::BtVector3ToVector3(planeSupportTemp, planeSupport);

	delete planeNormalTemp;
	delete planeSupportTemp;
}

void PolyhedralConvexShape::GetVertex(int index, [Out] Vector3% vertex)
{
	btVector3* vtxTemp = new btVector3;

	Native->getVertex(index, *vtxTemp);

	Math::BtVector3ToVector3(vtxTemp, vertex);
	delete vtxTemp;
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
	VECTOR3_DEF(point);
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

int PolyhedralConvexShape::EdgeCount::get()
{
	return Native->getNumEdges();
}

int PolyhedralConvexShape::PlaneCount::get()
{
	return Native->getNumPlanes();
}

int PolyhedralConvexShape::VertexCount::get()
{
	return Native->getNumVertices();
}


#undef Native
#define Native static_cast<btPolyhedralConvexAabbCachingShape*>(_native)

PolyhedralConvexAabbCachingShape::PolyhedralConvexAabbCachingShape(btPolyhedralConvexAabbCachingShape *shape)
: PolyhedralConvexShape(shape)
{
}

void PolyhedralConvexAabbCachingShape::GetNonvirtualAabb(Matrix trans, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax, btScalar margin)
{
	btTransform* transTemp = Math::MatrixToBtTransform(trans);
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	Native->getNonvirtualAabb(*transTemp, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), margin);

	Math::BtVector3ToVector3(VECTOR3_PTR(aabbMin), aabbMin);
	Math::BtVector3ToVector3(VECTOR3_PTR(aabbMax), aabbMax);

	ALIGNED_FREE(transTemp);
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void PolyhedralConvexAabbCachingShape::RecalcLocalAabb()
{
	Native->recalcLocalAabb();
}
