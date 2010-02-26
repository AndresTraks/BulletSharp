#include "StdAfx.h"

#include "Convex2dShape.h"

using namespace BulletSharp;

Convex2dShape::Convex2dShape(ConvexShape^ convexChildShape)
: ConvexShape(new btConvex2dShape(convexChildShape->UnmanagedPointer))
{
}
