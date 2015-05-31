#include "StdAfx.h"

#include "TetrahedronShape.h"

#define Native static_cast<btBU_Simplex1to4*>(_native)

BuSimplex1To4::BuSimplex1To4(btBU_Simplex1to4* native)
	: PolyhedralConvexAabbCachingShape(native)
{
}

BuSimplex1To4::BuSimplex1To4()
	: PolyhedralConvexAabbCachingShape(new btBU_Simplex1to4())
{
}

BuSimplex1To4::BuSimplex1To4(Vector3 pt0)
	: PolyhedralConvexAabbCachingShape(0)
{
	VECTOR3_CONV(pt0);
	UnmanagedPointer = new btBU_Simplex1to4(VECTOR3_USE(pt0));
	VECTOR3_DEL(pt0);
}

BuSimplex1To4::BuSimplex1To4(Vector3 pt0, Vector3 pt1)
	: PolyhedralConvexAabbCachingShape(0)
{
	VECTOR3_CONV(pt0);
	VECTOR3_CONV(pt1);
	UnmanagedPointer = new btBU_Simplex1to4(VECTOR3_USE(pt0), VECTOR3_USE(pt1));
	VECTOR3_DEL(pt0);
	VECTOR3_DEL(pt1);
}

BuSimplex1To4::BuSimplex1To4(Vector3 pt0, Vector3 pt1, Vector3 pt2)
	: PolyhedralConvexAabbCachingShape(0)
{
	VECTOR3_CONV(pt0);
	VECTOR3_CONV(pt1);
	VECTOR3_CONV(pt2);
	UnmanagedPointer = new btBU_Simplex1to4(VECTOR3_USE(pt0), VECTOR3_USE(pt1), VECTOR3_USE(pt2));
	VECTOR3_DEL(pt0);
	VECTOR3_DEL(pt1);
	VECTOR3_DEL(pt2);
}

BuSimplex1To4::BuSimplex1To4(Vector3 pt0, Vector3 pt1, Vector3 pt2, Vector3 pt3)
	: PolyhedralConvexAabbCachingShape(0)
{
	VECTOR3_CONV(pt0);
	VECTOR3_CONV(pt1);
	VECTOR3_CONV(pt2);
	VECTOR3_CONV(pt3);
	UnmanagedPointer = new btBU_Simplex1to4(VECTOR3_USE(pt0), VECTOR3_USE(pt1), VECTOR3_USE(pt2),
		VECTOR3_USE(pt3));
	VECTOR3_DEL(pt0);
	VECTOR3_DEL(pt1);
	VECTOR3_DEL(pt2);
	VECTOR3_DEL(pt3);
}

void BuSimplex1To4::AddVertexRef(Vector3% pt)
{
	VECTOR3_CONV(pt);
	Native->addVertex(VECTOR3_USE(pt));
	VECTOR3_DEL(pt);
}

void BuSimplex1To4::AddVertex(Vector3 pt)
{
	VECTOR3_CONV(pt);
	Native->addVertex(VECTOR3_USE(pt));
	VECTOR3_DEL(pt);
}

int BuSimplex1To4::GetIndex(int i)
{
	return Native->getIndex(i);
}

void BuSimplex1To4::Reset()
{
	Native->reset();
}
