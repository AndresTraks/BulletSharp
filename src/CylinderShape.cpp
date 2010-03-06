#include "StdAfx.h"

#include "CylinderShape.h"

CylinderShape::CylinderShape(Vector3 halfExtents)
: ConvexInternalShape(new btCylinderShape(*Math::Vector3ToBtVector3(halfExtents)))
{
}

CylinderShape::CylinderShape(float halfExtentsX, float halfExtentsY, float halfExtentsZ)
: ConvexInternalShape(new btCylinderShape(*(new btVector3(halfExtentsX,halfExtentsY,halfExtentsZ))))
{
}

CylinderShape::CylinderShape(float halfExtents)
: ConvexInternalShape(new btCylinderShape(*(new btVector3(halfExtents,halfExtents,halfExtents))))
{
}


CylinderShapeX::CylinderShapeX(Vector3 halfExtents)
: ConvexInternalShape(new btCylinderShapeX(*Math::Vector3ToBtVector3(halfExtents)))
{
}

CylinderShapeX::CylinderShapeX(float halfExtentsX, float halfExtentsY, float halfExtentsZ)
: ConvexInternalShape(new btCylinderShapeX(*(new btVector3(halfExtentsX,halfExtentsY,halfExtentsZ))))
{
}

CylinderShapeX::CylinderShapeX(float halfExtents)
: ConvexInternalShape(new btCylinderShapeX(*(new btVector3(halfExtents,halfExtents,halfExtents))))
{
}


CylinderShapeZ::CylinderShapeZ(Vector3 halfExtents)
: ConvexInternalShape(new btCylinderShapeZ(*Math::Vector3ToBtVector3(halfExtents)))
{
}

CylinderShapeZ::CylinderShapeZ(float halfExtentsX, float halfExtentsY, float halfExtentsZ)
: ConvexInternalShape(new btCylinderShapeZ(*(new btVector3(halfExtentsX,halfExtentsY,halfExtentsZ))))
{
}

CylinderShapeZ::CylinderShapeZ(float halfExtents)
: ConvexInternalShape(new btCylinderShapeZ(*(new btVector3(halfExtents,halfExtents,halfExtents))))
{
}