#pragma once

// Fully implemented as of 23 Nov 2010

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class Convex2DShape : ConvexShape
	{
	private:
		ConvexShape^ childShape;

	internal:
		Convex2DShape(btConvex2dShape* shape);

	public:
		Convex2DShape(ConvexShape^ convexChildShape);

		property ConvexShape^ ChildShape
		{
			ConvexShape^ get();
		}

	internal:
		property btConvex2dShape* UnmanagedPointer
		{
			btConvex2dShape* get() new;
		}
	};
};
