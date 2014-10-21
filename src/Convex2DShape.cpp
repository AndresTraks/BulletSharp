#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Convex2DShape.h"

#define Native static_cast<btConvex2dShape*>(_native)

Convex2DShape::Convex2DShape(btConvex2dShape* native)
	: ConvexShape(native)
{
}

Convex2DShape::Convex2DShape(ConvexShape^ convexChildShape)
	: ConvexShape(new btConvex2dShape((btConvexShape*)convexChildShape->_native))
{
	_convexChildShape = convexChildShape;
}

ConvexShape^ Convex2DShape::ChildShape::get()
{
	return _convexChildShape;
}

#endif
