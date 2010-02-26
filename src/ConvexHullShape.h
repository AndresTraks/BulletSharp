#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	public ref class ConvexHullShape : PolyhedralConvexAabbCachingShape 
	{
	public:
		ConvexHullShape();
		ConvexHullShape(array<Vector3>^ points);
	internal:
		ConvexHullShape(btConvexHullShape* shape);

		property btConvexHullShape* UnmanagedPointer
		{
			btConvexHullShape* get() new;
		}
	};
};
