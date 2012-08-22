#include "StdAfx.h"

#include "TetrahedronShape.h"

#define Unmanaged static_cast<btBU_Simplex1to4*>(_unmanaged)

BU_Simplex1to4::BU_Simplex1to4(btBU_Simplex1to4* shape)
: PolyhedralConvexAabbCachingShape(shape)
{
}

BU_Simplex1to4::BU_Simplex1to4()
: PolyhedralConvexAabbCachingShape(new btBU_Simplex1to4())
{
}

BU_Simplex1to4::BU_Simplex1to4(Vector3 pt0)
: PolyhedralConvexAabbCachingShape(0)
{
	VECTOR3_DEF(pt0);
	UnmanagedPointer = new btBU_Simplex1to4(VECTOR3_USE(pt0));
	VECTOR3_DEL(pt0);
}

BU_Simplex1to4::BU_Simplex1to4(Vector3 pt0, Vector3 pt1)
: PolyhedralConvexAabbCachingShape(0)
{
	VECTOR3_DEF(pt0);
	VECTOR3_DEF(pt1);
	
	UnmanagedPointer = new btBU_Simplex1to4(VECTOR3_USE(pt0), VECTOR3_USE(pt1));
	
	VECTOR3_DEL(pt0);
	VECTOR3_DEL(pt1);
}

BU_Simplex1to4::BU_Simplex1to4(Vector3 pt0, Vector3 pt1, Vector3 pt2)
: PolyhedralConvexAabbCachingShape(0)
{
	VECTOR3_DEF(pt0);
	VECTOR3_DEF(pt1);
	VECTOR3_DEF(pt2);
	
	UnmanagedPointer = new btBU_Simplex1to4(VECTOR3_USE(pt0), VECTOR3_USE(pt1), VECTOR3_USE(pt2));
	
	VECTOR3_DEL(pt0);
	VECTOR3_DEL(pt1);
	VECTOR3_DEL(pt2);
}

BU_Simplex1to4::BU_Simplex1to4(Vector3 pt0, Vector3 pt1, Vector3 pt2, Vector3 pt3)
: PolyhedralConvexAabbCachingShape(0)
{
	VECTOR3_DEF(pt0);
	VECTOR3_DEF(pt1);
	VECTOR3_DEF(pt2);
	VECTOR3_DEF(pt3);
	
	UnmanagedPointer = new btBU_Simplex1to4(VECTOR3_USE(pt0), VECTOR3_USE(pt1), VECTOR3_USE(pt2), VECTOR3_USE(pt3));
	
	VECTOR3_DEL(pt0);
	VECTOR3_DEL(pt1);
	VECTOR3_DEL(pt2);
	VECTOR3_DEL(pt3);
}

void BU_Simplex1to4::AddVertex(Vector3 pt)
{
	VECTOR3_DEF(pt);
	Unmanaged->addVertex(VECTOR3_USE(pt));
	VECTOR3_DEL(pt);
}

int BU_Simplex1to4::GetIndex(int i)
{
	return Unmanaged->getIndex(i);
}

void BU_Simplex1to4::Reset()
{
	Unmanaged->reset();
}
