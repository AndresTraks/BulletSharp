#include "StdAfx.h"

#include "PolyhedralConvexShape.h"
#ifndef DISABLE_UNCOMMON
#include "ConvexPolyhedron.h"
#endif

using namespace BulletSharp;

PolyhedralConvexShape::PolyhedralConvexShape(btPolyhedralConvexShape* polyhedralConvexShape)
: BulletSharp::ConvexInternalShape(polyhedralConvexShape)
{
}

void PolyhedralConvexShape::GetEdge(int index, [Out] Vector3% pointA, [Out] Vector3% pointB)
{
	btVector3* paTemp = new btVector3;
	btVector3* pbTemp = new btVector3;

	UnmanagedPointer->getEdge(index, *paTemp, *pbTemp);

	Math::BtVector3ToVector3(paTemp, pointA);
	Math::BtVector3ToVector3(pbTemp, pointB);

	delete paTemp;
	delete pbTemp;
}

void PolyhedralConvexShape::GetPlane([Out] Vector3% planeNormal, [Out] Vector3% planeSupport, int index)
{
	btVector3* planeNormalTemp = new btVector3;
	btVector3* planeSupportTemp = new btVector3;

	UnmanagedPointer->getPlane(*planeNormalTemp, *planeSupportTemp, index);

	Math::BtVector3ToVector3(planeNormalTemp, planeNormal);
	Math::BtVector3ToVector3(planeSupportTemp, planeSupport);

	delete planeNormalTemp;
	delete planeSupportTemp;
}

void PolyhedralConvexShape::GetVertex(int index, [Out] Vector3% vertex)
{
	btVector3* vtxTemp = new btVector3;

	UnmanagedPointer->getVertex(index, *vtxTemp);

	Math::BtVector3ToVector3(vtxTemp, vertex);
	delete vtxTemp;
}

bool PolyhedralConvexShape::InitializePolyhedralFeatures()
{
	return UnmanagedPointer->initializePolyhedralFeatures();
}

bool PolyhedralConvexShape::IsInside(Vector3 point, btScalar tolerance)
{
	btVector3* ptTemp = Math::Vector3ToBtVector3(point);

	bool ret = UnmanagedPointer->isInside(*ptTemp, tolerance);

	delete ptTemp;
	return ret;
}

#ifndef DISABLE_UNCOMMON
ConvexPolyhedron^ PolyhedralConvexShape::ConvexPolyhedron::get()
{
	btConvexPolyhedron* convexPolyhedron = (btConvexPolyhedron*)UnmanagedPointer->getConvexPolyhedron();
	ReturnCachedObjectNullable(BulletSharp::ConvexPolyhedron, _convexPolyhedron, convexPolyhedron);
}
#endif

int PolyhedralConvexShape::EdgeCount::get()
{
	return UnmanagedPointer->getNumEdges();
}

int PolyhedralConvexShape::PlaneCount::get()
{
	return UnmanagedPointer->getNumPlanes();
}

int PolyhedralConvexShape::VertexCount::get()
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

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

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
