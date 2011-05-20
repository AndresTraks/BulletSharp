#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class Vector3Array;

	public ref class ConvexHullShape : PolyhedralConvexAabbCachingShape
	{
	private:
		Vector3Array^ _unscaledPoints;

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
