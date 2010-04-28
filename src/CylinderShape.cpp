#include "StdAfx.h"

#include "CylinderShape.h"

CylinderShape::CylinderShape(btCylinderShape* shape)
: ConvexInternalShape(shape)
{
}

CylinderShape::CylinderShape(Vector3 halfExtents)
: ConvexInternalShape(0)
{
	btVector3* halfExtentsTemp = Math::Vector3ToBtVector3(halfExtents);
	UnmanagedPointer = new btCylinderShape(*halfExtentsTemp);
	delete halfExtentsTemp;
}

CylinderShape::CylinderShape(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ)
: ConvexInternalShape(0)
{
	btVector3* halfExtentsTemp = new btVector3(halfExtentsX,halfExtentsY,halfExtentsZ);
	UnmanagedPointer = new btCylinderShape(*halfExtentsTemp);
	delete halfExtentsTemp;
}

CylinderShape::CylinderShape(btScalar halfExtents)
: ConvexInternalShape(0)
{
	btVector3* halfExtentsTemp = new btVector3(halfExtents,halfExtents,halfExtents);
	UnmanagedPointer = new btCylinderShape(*halfExtentsTemp);
	delete halfExtentsTemp;
}

#pragma managed(push, off)
btVector3* CylinderShape_GetHalfExtentsWithMargin(btCylinderShape* shape)
{
	btVector3* extents = new btVector3;
	*extents = shape->getHalfExtentsWithMargin();
	return extents;
}
#pragma managed(pop)

Vector3 CylinderShape::HalfExtentsWithMargin::get()
{
	return Math::BtVector3ToVector3(CylinderShape_GetHalfExtentsWithMargin(UnmanagedPointer));
}

Vector3 CylinderShape::HalfExtentsWithoutMargin::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getHalfExtentsWithoutMargin());
}

btCylinderShape* CylinderShape::UnmanagedPointer::get()
{
	return (btCylinderShape*)ConvexInternalShape::UnmanagedPointer;
}


CylinderShapeX::CylinderShapeX(Vector3 halfExtents)
: CylinderShape(new btCylinderShapeX(*Math::Vector3ToBtVector3(halfExtents)))
{
}

CylinderShapeX::CylinderShapeX(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ)
: CylinderShape(new btCylinderShapeX(*(new btVector3(halfExtentsX,halfExtentsY,halfExtentsZ))))
{
}

CylinderShapeX::CylinderShapeX(btScalar halfExtents)
: CylinderShape(new btCylinderShapeX(*(new btVector3(halfExtents,halfExtents,halfExtents))))
{
}


CylinderShapeZ::CylinderShapeZ(Vector3 halfExtents)
: CylinderShape(new btCylinderShapeZ(*Math::Vector3ToBtVector3(halfExtents)))
{
}

CylinderShapeZ::CylinderShapeZ(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ)
: CylinderShape(new btCylinderShapeZ(*(new btVector3(halfExtentsX,halfExtentsY,halfExtentsZ))))
{
}

CylinderShapeZ::CylinderShapeZ(btScalar halfExtents)
: CylinderShape(new btCylinderShapeZ(*(new btVector3(halfExtents,halfExtents,halfExtents))))
{
}