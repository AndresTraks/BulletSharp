#include "StdAfx.h"

#include "PolyhedralConvexShape.h"
#ifndef DISABLE_UNCOMMON
#include "ConvexPolyhedron.h"
#endif

#define Unmanaged static_cast<btPolyhedralConvexShape*>(_unmanaged)

PolyhedralConvexShape::PolyhedralConvexShape(btPolyhedralConvexShape* polyhedralConvexShape)
: BulletSharp::ConvexInternalShape(polyhedralConvexShape)
{
}

void PolyhedralConvexShape::GetEdge(int index, [Out] Vector3% pointA, [Out] Vector3% pointB)
{
	btVector3* paTemp = new btVector3;
	btVector3* pbTemp = new btVector3;

	Unmanaged->getEdge(index, *paTemp, *pbTemp);

	Math::BtVector3ToVector3(paTemp, pointA);
	Math::BtVector3ToVector3(pbTemp, pointB);

	delete paTemp;
	delete pbTemp;
}

void PolyhedralConvexShape::GetPlane([Out] Vector3% planeNormal, [Out] Vector3% planeSupport, int index)
{
	btVector3* planeNormalTemp = new btVector3;
	btVector3* planeSupportTemp = new btVector3;

	Unmanaged->getPlane(*planeNormalTemp, *planeSupportTemp, index);

	Math::BtVector3ToVector3(planeNormalTemp, planeNormal);
	Math::BtVector3ToVector3(planeSupportTemp, planeSupport);

	delete planeNormalTemp;
	delete planeSupportTemp;
}

void PolyhedralConvexShape::GetVertex(int index, [Out] Vector3% vertex)
{
	btVector3* vtxTemp = new btVector3;

	Unmanaged->getVertex(index, *vtxTemp);

	Math::BtVector3ToVector3(vtxTemp, vertex);
	delete vtxTemp;
}

bool PolyhedralConvexShape::InitializePolyhedralFeatures()
{
	return Unmanaged->initializePolyhedralFeatures();
}

bool PolyhedralConvexShape::IsInside(Vector3 point, btScalar tolerance)
{
	VECTOR3_DEF(point);
	bool ret = Unmanaged->isInside(VECTOR3_USE(point), tolerance);
	VECTOR3_DEL(point);
	return ret;
}

#ifndef DISABLE_UNCOMMON
ConvexPolyhedron^ PolyhedralConvexShape::ConvexPolyhedron::get()
{
	btConvexPolyhedron* convexPolyhedron = (btConvexPolyhedron*)Unmanaged->getConvexPolyhedron();
	ReturnCachedObjectNullable(BulletSharp::ConvexPolyhedron, _convexPolyhedron, convexPolyhedron);
}
#endif

int PolyhedralConvexShape::EdgeCount::get()
{
	return Unmanaged->getNumEdges();
}

int PolyhedralConvexShape::PlaneCount::get()
{
	return Unmanaged->getNumPlanes();
}

int PolyhedralConvexShape::VertexCount::get()
{
	return Unmanaged->getNumVertices();
}


#define Unmanaged static_cast<btPolyhedralConvexAabbCachingShape*>(_unmanaged)

PolyhedralConvexAabbCachingShape::PolyhedralConvexAabbCachingShape(btPolyhedralConvexAabbCachingShape *shape)
: PolyhedralConvexShape(shape)
{
}

void PolyhedralConvexAabbCachingShape::GetNonvirtualAabb(Matrix trans, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax, btScalar margin)
{
	btTransform* transTemp = Math::MatrixToBtTransform(trans);
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	Unmanaged->getNonvirtualAabb(*transTemp, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax), margin);

	Math::BtVector3ToVector3(VECTOR3_PTR(aabbMin), aabbMin);
	Math::BtVector3ToVector3(VECTOR3_PTR(aabbMax), aabbMax);

	delete transTemp;
	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void PolyhedralConvexAabbCachingShape::RecalcLocalAabb()
{
	Unmanaged->recalcLocalAabb();
}
