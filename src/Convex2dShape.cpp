#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "Convex2DShape.h"

#define Unmanaged static_cast<btConvex2dShape*>(_unmanaged)

Convex2DShape::Convex2DShape(ConvexShape^ convexChildShape)
: ConvexShape(new btConvex2dShape((btConvexShape*)convexChildShape->_unmanaged))
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
		childShape = gcnew ConvexShape(Unmanaged->getChildShape());
	}
	return childShape;
}

#endif
