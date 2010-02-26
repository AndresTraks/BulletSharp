#include "StdAfx.h"

#include "ConvexShape.h"

using namespace BulletSharp;

ConvexShape::ConvexShape(btConvexShape* convexShape)
: CollisionShape(convexShape)
{
}

btConvexShape* ConvexShape::UnmanagedPointer::get()
{
	return (btConvexShape*)CollisionShape::UnmanagedPointer;
}
