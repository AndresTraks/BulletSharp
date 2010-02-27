#pragma once

#include "ConvexShape.h"

namespace BulletSharp
{
	public ref class ConvexInternalShape abstract : ConvexShape
	{
	internal:
		ConvexInternalShape(btConvexInternalShape* convexInternalShape);
	};
};
