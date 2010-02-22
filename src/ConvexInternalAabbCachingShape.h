#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class ConvexInternalAabbCachingShape abstract : BulletSharp::ConvexInternalShape
	{
		internal:
			ConvexInternalAabbCachingShape(btConvexInternalAabbCachingShape* convexInternalAabbCachingShape);
	};
};
