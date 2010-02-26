#pragma once

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btConvex2dShape.h>
#pragma managed(pop)

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class Convex2dShape : ConvexShape
	{
	public:
		Convex2dShape(ConvexShape^ convexChildShape);
	};
};
