#pragma once

#include "ConvexInternalShape.h"

namespace BulletSharp
{
	public ref class PolyhedralConvexShape abstract : ConvexInternalShape
	{
	internal:
		PolyhedralConvexShape(btPolyhedralConvexShape* polyhedralConvexShape);
	};

	public ref class PolyhedralConvexAabbCachingShape : PolyhedralConvexShape
	{
	internal:
		PolyhedralConvexAabbCachingShape(btPolyhedralConvexAabbCachingShape* shape);
	};
};
