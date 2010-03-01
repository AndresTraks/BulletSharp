#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btConvex2dShape.h>
#pragma managed(pop)

#include "Convex2dShape.h"

using namespace BulletSharp;

Convex2dShape::Convex2dShape(ConvexShape^ convexChildShape)
: ConvexShape(new btConvex2dShape(convexChildShape->UnmanagedPointer))
{
	childShape = convexChildShape;
}

Convex2dShape::Convex2dShape(btConvex2dShape* shape)
: ConvexShape(shape)
{
}

Convex2dShape^ Convex2dShape::Upcast2d(CollisionShape^ shape)
{
	return gcnew Convex2dShape((btConvex2dShape*)shape->UnmanagedPointer);
}

ConvexShape^ Convex2dShape::ChildShape::get()
{
	if (childShape == nullptr)
	{
		childShape = gcnew ConvexShape(UnmanagedPointer->getChildShape());
	}
	return childShape;
}

btConvex2dShape* Convex2dShape::UnmanagedPointer::get()
{
	return (btConvex2dShape*)ConvexShape::UnmanagedPointer;
}
