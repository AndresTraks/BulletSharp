#pragma once

// Fully implemented as of 07 Dec 2010

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	ref class Vector3Array;

	public ref class ConvexPointCloudShape : PolyhedralConvexAabbCachingShape
	{
	private:
		Vector3Array^ _unscaledPoints;

	internal:
		ConvexPointCloudShape(btConvexPointCloudShape* shape);

	public:
		ConvexPointCloudShape(array<Vector3>^ points, Vector3 localScaling, bool computeAabb);
		ConvexPointCloudShape(array<Vector3>^ points, Vector3 localScaling);
		ConvexPointCloudShape();

		void SetPoints(array<Vector3>^ points, bool computeAabb, Vector3 localScaling);
		void SetPoints(array<Vector3>^ points, bool computeAabb);
		void SetPoints(array<Vector3>^ points);

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
		property btConvexPointCloudShape* UnmanagedPointer
		{
			btConvexPointCloudShape* get() new;
		}
	};
};
