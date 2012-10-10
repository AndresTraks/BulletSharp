#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Convex2DShape.h"

#define Native static_cast<btConvex2dShape*>(_native)

Convex2DShape::Convex2DShape(ConvexShape^ convexChildShape)
: ConvexShape(new btConvex2dShape((btConvexShape*)convexChildShape->_native))
{
	childShape = convexChildShape;
}

Convex2DShape::Convex2DShape(btConvex2dShape* shape)
: ConvexShape(shape)
{
}

ConvexShape^ Convex2DShape::ChildShape::get()
{
	if (childShape == nullptr)
	{
		childShape = gcnew ConvexShape(Native->getChildShape());
	}
	return childShape;
}

#endif
