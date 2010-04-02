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
	public:
		void AddPoint(Vector3 point);
		Vector3 GetScaledPoint(int i);
		//array<Vector3>^ GetUnscaledPoints();

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
