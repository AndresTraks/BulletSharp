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
		ConvexHullShape(btConvexHullShape* native);

	public:
		ConvexHullShape();
		ConvexHullShape(System::Collections::Generic::IEnumerable<Vector3>^ points);

		void AddPoint(Vector3 point, bool recalculateLocalAabb);
		void AddPoint(Vector3 point);
		Vector3 GetScaledPoint(int i);
		void Project(Matrix trans, Vector3 dir, [Out] float% minProj, [Out] float% maxProj, [Out] Vector3% witnesPtMin,
			[Out] Vector3% witnesPtMax);

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
