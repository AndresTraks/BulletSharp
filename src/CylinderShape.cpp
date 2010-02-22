#include "StdAfx.h"

#include "CylinderShape.h"

CylinderShape::CylinderShape(Vector3 boxHalfExtents)
: ConvexInternalShape(new btCylinderShape(*Math::Vector3ToBtVec3(boxHalfExtents)))
{
}

CylinderShape::CylinderShape(float boxHalfExtentsX, float boxHalfExtentsY, float boxHalfExtentsZ)
: ConvexInternalShape(new btCylinderShape(*(new btVector3(boxHalfExtentsX,boxHalfExtentsY,boxHalfExtentsZ))))
{
}

CylinderShapeX::CylinderShapeX(Vector3 boxHalfExtents)
: ConvexInternalShape(new btCylinderShapeX(*Math::Vector3ToBtVec3(boxHalfExtents)))
{
}

CylinderShapeX::CylinderShapeX(float boxHalfExtentsX, float boxHalfExtentsY, float boxHalfExtentsZ)
: ConvexInternalShape(new btCylinderShapeX(*(new btVector3(boxHalfExtentsX,boxHalfExtentsY,boxHalfExtentsZ))))
{
}

CylinderShapeZ::CylinderShapeZ(Vector3 boxHalfExtents)
: ConvexInternalShape(new btCylinderShapeZ(*Math::Vector3ToBtVec3(boxHalfExtents)))
{
}

CylinderShapeZ::CylinderShapeZ(float boxHalfExtentsX, float boxHalfExtentsY, float boxHalfExtentsZ)
: ConvexInternalShape(new btCylinderShapeZ(*(new btVector3(boxHalfExtentsX,boxHalfExtentsY,boxHalfExtentsZ))))
{
}
