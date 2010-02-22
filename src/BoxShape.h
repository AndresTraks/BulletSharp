#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	public ref class BoxShape : BulletSharp::PolyhedralConvexShape
	{
		public:
			BoxShape(Vector3 boxHalfExtents);
			BoxShape(float boxHalfExtentsX, float boxHalfExtentsY, float boxHalfExtentsZ);
	};
};
