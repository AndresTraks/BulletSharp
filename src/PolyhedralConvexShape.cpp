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

	pointA = Math::BtVector3ToVector3(paTemp);
	pointB = Math::BtVector3ToVector3(pbTemp);

	delete paTemp;
	delete pbTemp;
}

void PolyhedralConvexShape::GetPlane([Out] Vector3% planeNormal, [Out] Vector3% planeSupport, int index)
{
	btVector3* planeNormalTemp = new btVector3;
	btVector3* planeSupportTemp = new btVector3;

	UnmanagedPointer->getPlane(*planeNormalTemp, *planeSupportTemp, index);

	planeNormal = Math::BtVector3ToVector3(planeNormalTemp);
	planeSupport = Math::BtVector3ToVector3(planeSupportTemp);

	delete planeNormalTemp;
	delete planeSupportTemp;
}

void PolyhedralConvexShape::GetVertex(int index, [Out] Vector3% vertex)
{
	btVector3* vtxTemp = new btVector3;

	UnmanagedPointer->getVertex(index, *vtxTemp);

	vertex = Math::BtVector3ToVector3(vtxTemp);
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
	return gcnew BulletSharp::ConvexPolyhedron((btConvexPolyhedron*)UnmanagedPointer->getConvexPolyhedron());
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
