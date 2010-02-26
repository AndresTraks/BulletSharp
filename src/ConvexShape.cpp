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

ConvexShape^ ConvexShape::Upcast(CollisionShape^ shape)
{
	return gcnew ConvexShape((btConvexShape*)shape->UnmanagedPointer);
}
