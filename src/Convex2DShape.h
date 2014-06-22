#pragma once

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class Convex2DShape : ConvexShape
	{
	internal:
		Convex2DShape(btConvex2dShape* native);

	public:
		Convex2DShape(ConvexShape^ convexChildShape);

		property ConvexShape^ ChildShape
		{
			ConvexShape^ get();
		}
	};
};
