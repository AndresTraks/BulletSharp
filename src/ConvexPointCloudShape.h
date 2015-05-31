#pragma once

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class Vector3Array;

	public ref class ConvexPointCloudShape : PolyhedralConvexAabbCachingShape
	{
	private:
		Vector3Array^ _unscaledPoints;

	public:
		ConvexPointCloudShape();
		ConvexPointCloudShape(array<Vector3>^ points, Vector3 localScaling, bool computeAabb);
		ConvexPointCloudShape(array<Vector3>^ points, Vector3 localScaling);

		Vector3 GetScaledPoint(int index);
		void SetPoints(array<Vector3>^ points, bool computeAabb, Vector3 localScaling);
		void SetPoints(array<Vector3>^ points, bool computeAabb);
		void SetPoints(array<Vector3>^ points);

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
