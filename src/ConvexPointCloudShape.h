#pragma once

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btConvexPointCloudShape.h>
#pragma managed(pop)

#include "PolyhedralConvexShape.h"

namespace BulletSharp
{
	public ref class ConvexPointCloudShape : PolyhedralConvexAabbCachingShape
	{
	internal:
		ConvexPointCloudShape(btConvexPointCloudShape* shape);
	
	public:
		ConvexPointCloudShape(array<Vector3>^ points, Vector3 localScaling, bool computeAabb);
		ConvexPointCloudShape(array<Vector3>^ points, Vector3 localScaling);
		ConvexPointCloudShape();

		void SetPoints(array<Vector3>^ points, bool computeAabb, Vector3 localScaling);
		//void SetPoints(array<Vector3>^ points, bool computeAabb);
		//void SetPoints(array<Vector3>^ points);

		Vector3 GetScaledPoint(int i);
		//array<Vector3>^ GetUnscaledPoints();

		property int NumPoints
		{
			int get();
		}

	internal:
		property btConvexPointCloudShape* UnmanagedPointer
		{
			btConvexPointCloudShape* get() new;
		}
	};
};
