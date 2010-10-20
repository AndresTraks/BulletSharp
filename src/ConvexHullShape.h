#pragma once

// Fully implemented as of 21 Oct 2010

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class Vector3Array;

	public ref class ConvexHullShape : PolyhedralConvexAabbCachingShape
	{
	internal:
		ConvexHullShape(btConvexHullShape* shape);
	
	public:
		ConvexHullShape();
		ConvexHullShape(array<Vector3>^ points);

		void AddPoint(Vector3 point);
		Vector3 GetScaledPoint(int i);

		property int NumPoints
		{
			int get();
		}

		property Vector3Array^ UnscaledPoints
		{
			Vector3Array^ get();
		}

	internal:
		property btConvexHullShape* UnmanagedPointer
		{
			btConvexHullShape* get() new;
		}
	};
};
