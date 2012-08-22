#include "StdAfx.h"

#include "BoxShape.h"

#define Unmanaged static_cast<btBoxShape*>(_unmanaged)

BoxShape::BoxShape(btBoxShape* shape)
: PolyhedralConvexShape(shape)
{
}

BoxShape::BoxShape(Vector3 boxHalfExtents)
: PolyhedralConvexShape(0)
{
	VECTOR3_DEF(boxHalfExtents);
	UnmanagedPointer = new btBoxShape(VECTOR3_USE(boxHalfExtents));
	VECTOR3_DEL(boxHalfExtents);
}

BoxShape::BoxShape(btScalar boxHalfExtentsX, btScalar boxHalfExtentsY, btScalar boxHalfExtentsZ)
: PolyhedralConvexShape(0)
{
	btVector3* boxHalfExtentsTemp = new btVector3(boxHalfExtentsX,boxHalfExtentsY,boxHalfExtentsZ);
	UnmanagedPointer = new btBoxShape(*boxHalfExtentsTemp);
	delete boxHalfExtentsTemp;
}

BoxShape::BoxShape(btScalar boxHalfExtents)
: PolyhedralConvexShape(0)
{
	btVector3* boxHalfExtentsTemp = new btVector3(boxHalfExtents,boxHalfExtents,boxHalfExtents);
	UnmanagedPointer = new btBoxShape(*boxHalfExtentsTemp);
	delete boxHalfExtentsTemp;
}

Vector4 BoxShape::GetPlaneEquation(int index)
{
	btVector4* equationTemp = new btVector4;
	Unmanaged->getPlaneEquation(*equationTemp, index);
	Vector4 equation = Math::BtVector4ToVector4(equationTemp);
	delete equationTemp;
	return equation;
}

Vector3 BoxShape::HalfExtentsWithMargin::get()
{
	btVector3* extentsTemp = new btVector3(Unmanaged->getHalfExtentsWithMargin());
	Vector3 extents = Math::BtVector3ToVector3(extentsTemp);
	delete extentsTemp;
	return extents;
}

Vector3 BoxShape::HalfExtentsWithoutMargin::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getHalfExtentsWithoutMargin());
}
