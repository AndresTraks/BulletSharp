#pragma once

#include "CollisionShape.h"

namespace BulletSharp
{
	public ref class ConvexShape abstract : BulletSharp::CollisionShape
	{
		internal:
			ConvexShape(btConvexShape* convexShape);
	};
};
