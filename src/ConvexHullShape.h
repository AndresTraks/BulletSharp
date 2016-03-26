#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class Vector3Array;

	public ref class ConvexHullShape : PolyhedralConvexAabbCachingShape
	{
	private:
		Vector3Array^ _unscaledPoints;

	public:
		ConvexHullShape(IEnumerable<Vector3>^ points);
		ConvexHullShape();

		void AddPoint(Vector3 point, bool recalculateLocalAabb);
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
	};
};
