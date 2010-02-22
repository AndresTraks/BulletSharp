#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class PolyhedralConvexShape abstract : BulletSharp::ConvexInternalShape
	{
		internal:
			PolyhedralConvexShape(btPolyhedralConvexShape* polyhedralConvexShape);
	};
};
