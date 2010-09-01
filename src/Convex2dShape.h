#pragma once

// Fully implemented as of 26 Feb 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btConvex2dShape.h>
#pragma managed(pop)

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

		static Convex2DShape^ Upcast2d(CollisionShape^ shape);

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
