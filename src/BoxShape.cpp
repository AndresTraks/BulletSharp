#include "StdAfx.h"

#include "BoxShape.h"

#define Native static_cast<btBoxShape*>(_native)

BoxShape::BoxShape(Vector3 boxHalfExtents)
	: PolyhedralConvexShape(0)
{
	VECTOR3_CONV(boxHalfExtents);
	UnmanagedPointer = new btBoxShape(VECTOR3_USE(boxHalfExtents));
	VECTOR3_DEL(boxHalfExtents);
}

BoxShape::BoxShape(btScalar boxHalfExtentsX, btScalar boxHalfExtentsY, btScalar boxHalfExtentsZ)
	: PolyhedralConvexShape(0)
{
	btVector3* boxHalfExtentsTemp = ALIGNED_NEW(btVector3) (boxHalfExtentsX,boxHalfExtentsY,boxHalfExtentsZ);
	UnmanagedPointer = new btBoxShape(*boxHalfExtentsTemp);
	ALIGNED_FREE(boxHalfExtentsTemp);
}

BoxShape::BoxShape(btScalar boxHalfExtents)
	: PolyhedralConvexShape(0)
{
	btVector3* boxHalfExtentsTemp = ALIGNED_NEW(btVector3) (boxHalfExtents, boxHalfExtents, boxHalfExtents);
	UnmanagedPointer = new btBoxShape(*boxHalfExtentsTemp);
	ALIGNED_FREE(boxHalfExtentsTemp);
}

Vector4 BoxShape::GetPlaneEquation(int index)
{
	btVector4* equationTemp = new btVector4;
	Native->getPlaneEquation(*equationTemp, index);
	Vector4 equation = Math::BtVector4ToVector4(equationTemp);
	delete equationTemp;
	return equation;
}

Vector3 BoxShape::HalfExtentsWithMargin::get()
{
	btVector3* extentsTemp = ALIGNED_NEW(btVector3) (Native->getHalfExtentsWithMargin());
	Vector3 extents = Math::BtVector3ToVector3(extentsTemp);
	ALIGNED_FREE(extentsTemp);
	return extents;
}

Vector3 BoxShape::HalfExtentsWithoutMargin::get()
{
	return Math::BtVector3ToVector3(&Native->getHalfExtentsWithoutMargin());
}
