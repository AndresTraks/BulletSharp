#include "StdAfx.h"

#include "CylinderShape.h"

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


CylinderShapeX::CylinderShapeX(Vector3 halfExtents)
: ConvexInternalShape(new btCylinderShapeX(*Math::Vector3ToBtVector3(halfExtents)))
{
}

CylinderShapeX::CylinderShapeX(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ)
: ConvexInternalShape(new btCylinderShapeX(*(new btVector3(halfExtentsX,halfExtentsY,halfExtentsZ))))
{
}

CylinderShapeX::CylinderShapeX(btScalar halfExtents)
: ConvexInternalShape(new btCylinderShapeX(*(new btVector3(halfExtents,halfExtents,halfExtents))))
{
}


CylinderShapeZ::CylinderShapeZ(Vector3 halfExtents)
: ConvexInternalShape(new btCylinderShapeZ(*Math::Vector3ToBtVector3(halfExtents)))
{
}

CylinderShapeZ::CylinderShapeZ(btScalar halfExtentsX, btScalar halfExtentsY, btScalar halfExtentsZ)
: ConvexInternalShape(new btCylinderShapeZ(*(new btVector3(halfExtentsX,halfExtentsY,halfExtentsZ))))
{
}

CylinderShapeZ::CylinderShapeZ(btScalar halfExtents)
: ConvexInternalShape(new btCylinderShapeZ(*(new btVector3(halfExtents,halfExtents,halfExtents))))
{
}