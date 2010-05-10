#pragma once

// Fully implemented as of 11 May 2010

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	public ref class ConvexHullShape : PolyhedralConvexAabbCachingShape
	{
	internal:
		ConvexHullShape(btConvexHullShape* shape);
	
	public:
		ConvexHullShape();
		ConvexHullShape(array<Vector3>^ points);

		void AddPoint(Vector3 point);
		Vector3 GetScaledPoint(int i);
		array<Vector3>^ GetUnscaledPoints();

		property int NumPoints
		{
			int get();
		}

	internal:
		property btConvexHullShape* UnmanagedPointer
		{
			btConvexHullShape* get() new;
		}
	};
};
