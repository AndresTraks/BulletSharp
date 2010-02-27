#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class ConvexInternalAabbCachingShape abstract : ConvexInternalShape
	{
	internal:
		ConvexInternalAabbCachingShape(btConvexInternalAabbCachingShape* convexInternalAabbCachingShape);
	};
};
