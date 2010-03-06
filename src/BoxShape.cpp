#include "StdAfx.h"

#include "BoxShape.h"

BoxShape::BoxShape(Vector3 boxHalfExtents)
: PolyhedralConvexShape(new btBoxShape(*Math::Vector3ToBtVector3(boxHalfExtents)))
{
}

BoxShape::BoxShape(float boxHalfExtentsX, float boxHalfExtentsY, float boxHalfExtentsZ)
: PolyhedralConvexShape(new btBoxShape(*(new btVector3(boxHalfExtentsX,boxHalfExtentsY,boxHalfExtentsZ))))
{
}
