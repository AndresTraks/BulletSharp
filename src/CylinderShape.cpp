#include "StdAfx.h"

#include "CylinderShape.h"

CylinderShape::CylinderShape(btCylinderShape* shape)
: ConvexInternalShape(shape)
{
}

CylinderShape::CylinderShape(Vector3 halfExtents)
: ConvexInternalShape(new btCylinderShape(*Math::Vector3ToBtVector3(halfExtents)))
{
}

CylinderShape::CylinderShape(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ)
: ConvexInternalShape(new btCylinderShape(*(new btVector3(halfExtentsX,halfExtentsY,halfExtentsZ))))
{
}

CylinderShape::CylinderShape(btScalar halfExtents)
: ConvexInternalShape(new btCylinderShape(*(new btVector3(halfExtents,halfExtents,halfExtents))))
{
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