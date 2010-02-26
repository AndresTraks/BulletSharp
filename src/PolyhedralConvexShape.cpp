#include "StdAfx.h"

#include "PolyhedralConvexShape.h"

using namespace BulletSharp;

PolyhedralConvexShape::PolyhedralConvexShape(btPolyhedralConvexShape* polyhedralConvexShape) : BulletSharp::ConvexInternalShape(polyhedralConvexShape)
{
}

PolyhedralConvexAabbCachingShape::PolyhedralConvexAabbCachingShape(btPolyhedralConvexAabbCachingShape *shape)
: PolyhedralConvexShape(shape)
{
}
