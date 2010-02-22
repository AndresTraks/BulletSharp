#pragma once

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class ConvexInternalShape abstract : BulletSharp::ConvexShape
	{
		internal:
			ConvexInternalShape(btConvexInternalShape* convexInternalShape);
	};
};
