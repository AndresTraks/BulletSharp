#pragma once

// Fully implemented as of 26 Feb 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btConvex2dShape.h>
#pragma managed(pop)

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class Convex2dShape : ConvexShape
	{
	private:
		ConvexShape^ childShape;
	public:
		Convex2dShape(ConvexShape^ convexChildShape);
	internal:
		Convex2dShape(btConvex2dShape* shape);

	public:
		static Convex2dShape^ Upcast2d(CollisionShape^ shape);

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
