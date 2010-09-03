#include "StdAfx.h"

#include "Convex2DShape.h"

using namespace BulletSharp;

Convex2DShape::Convex2DShape(ConvexShape^ convexChildShape)
: ConvexShape(new btConvex2dShape(convexChildShape->UnmanagedPointer))
{
	childShape = convexChildShape;
}

Convex2DShape::Convex2DShape(btConvex2dShape* shape)
: ConvexShape(shape)
{
}

Convex2DShape^ Convex2DShape::Upcast2D(CollisionShape^ shape)
{
	return gcnew Convex2DShape((btConvex2dShape*)shape->UnmanagedPointer);
}

ConvexShape^ Convex2DShape::ChildShape::get()
{
	if (childShape == nullptr)
	{
		childShape = gcnew ConvexShape(UnmanagedPointer->getChildShape());
	}
	return childShape;
}

btConvex2dShape* Convex2DShape::UnmanagedPointer::get()
{
	return (btConvex2dShape*)ConvexShape::UnmanagedPointer;
}
