#include "StdAfx.h"

#include "BoxShape.h"

BoxShape::BoxShape(btBoxShape* shape)
: PolyhedralConvexShape(shape)
{
}

BoxShape::BoxShape(Vector3 boxHalfExtents)
: PolyhedralConvexShape(0)
{
	btVector3* boxHalfExtentsTemp = Math::Vector3ToBtVector3(boxHalfExtents);
	UnmanagedPointer = new btBoxShape(*boxHalfExtentsTemp);
	delete boxHalfExtentsTemp;
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
	UnmanagedPointer->getPlaneEquation(*equationTemp, index);
	Vector4 equation = Math::BtVector4ToVector4(equationTemp);
	delete equationTemp;
	return equation;
}

Vector3 BoxShape::HalfExtentsWithMargin::get()
{
	btVector3* extentsTemp = new btVector3(UnmanagedPointer->getHalfExtentsWithMargin());
	Vector3 extents = Math::BtVector3ToVector3(extentsTemp);
	delete extentsTemp;
	return extents;
}

Vector3 BoxShape::HalfExtentsWithoutMargin::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getHalfExtentsWithoutMargin());
}

btBoxShape* BoxShape::UnmanagedPointer::get()
{
	return (btBoxShape*)PolyhedralConvexShape::UnmanagedPointer;
}
