#include "StdAfx.h"

#include "PolyhedralConvexShape.h"

using namespace BulletSharp;

PolyhedralConvexShape::PolyhedralConvexShape(btPolyhedralConvexShape* polyhedralConvexShape)
: BulletSharp::ConvexInternalShape(polyhedralConvexShape)
{
}

void PolyhedralConvexShape::GetEdge(int i, [Out] Vector3% pa, [Out] Vector3% pb)
{
	btVector3* paTemp = new btVector3();
	btVector3* pbTemp = new btVector3();

	UnmanagedPointer->getEdge(i, *paTemp, *pbTemp);

	pa = Math::BtVector3ToVector3(paTemp);
	pb = Math::BtVector3ToVector3(pbTemp);

	delete paTemp;
	delete pbTemp;
}

void PolyhedralConvexShape::GetPlane([Out] Vector3% planeNormal, [Out] Vector3% planeSupport, int i)
{
	btVector3* planeNormalTemp = new btVector3();
	btVector3* planeSupportTemp = new btVector3();

	UnmanagedPointer->getPlane(*planeNormalTemp, *planeSupportTemp, i);

	planeNormal = Math::BtVector3ToVector3(planeNormalTemp);
	planeSupport = Math::BtVector3ToVector3(planeSupportTemp);

	delete planeNormalTemp;
	delete planeSupportTemp;
}

void PolyhedralConvexShape::GetVertex(int i, [Out] Vector3% vtx)
{
	btVector3* vtxTemp = new btVector3();

	UnmanagedPointer->getVertex(i, *vtxTemp);

	vtx = Math::BtVector3ToVector3(vtxTemp);
	delete vtxTemp;
}

bool PolyhedralConvexShape::IsInside(Vector3 pt, btScalar tolerance)
{
	btVector3* ptTemp = Math::Vector3ToBtVector3(pt);

	bool ret = UnmanagedPointer->isInside(*ptTemp, tolerance);

	delete ptTemp;
	return ret;
}

int PolyhedralConvexShape::NumEdges::get()
{
	return UnmanagedPointer->getNumEdges();
}

int PolyhedralConvexShape::NumPlanes::get()
{
	return UnmanagedPointer->getNumPlanes();
}

int PolyhedralConvexShape::NumVertices::get()
{
	return UnmanagedPointer->getNumVertices();
}

btPolyhedralConvexShape* PolyhedralConvexShape::UnmanagedPointer::get()
{
	return (btPolyhedralConvexAabbCachingShape*)ConvexInternalShape::UnmanagedPointer;
}


PolyhedralConvexAabbCachingShape::PolyhedralConvexAabbCachingShape(btPolyhedralConvexAabbCachingShape *shape)
: PolyhedralConvexShape(shape)
{
}

void PolyhedralConvexAabbCachingShape::GetNonvirtualAabb(Matrix trans, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax, btScalar margin)
{
	btTransform* transTemp = Math::MatrixToBtTransform(trans);
	btVector3* aabbMinTemp = Math::Vector3ToBtVector3(aabbMin);
	btVector3* aabbMaxTemp = Math::Vector3ToBtVector3(aabbMax);

	UnmanagedPointer->getNonvirtualAabb(*transTemp, *aabbMinTemp, *aabbMaxTemp, margin);

	aabbMin = Math::BtVector3ToVector3(aabbMinTemp);
	aabbMax = Math::BtVector3ToVector3(aabbMaxTemp);

	delete transTemp;
	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void PolyhedralConvexAabbCachingShape::RecalcLocalAabb()
{
	UnmanagedPointer->recalcLocalAabb();
}

btPolyhedralConvexAabbCachingShape* PolyhedralConvexAabbCachingShape::UnmanagedPointer::get()
{
	return (btPolyhedralConvexAabbCachingShape*)PolyhedralConvexShape::UnmanagedPointer;
}
