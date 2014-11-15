#pragma once

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class Convex2DShape : ConvexShape
	{
	private:
		ConvexShape^ _childShape;

	public:
		Convex2DShape(ConvexShape^ convexChildShape);

		property ConvexShape^ ChildShape
		{
			ConvexShape^ get();
		}
	};
};
