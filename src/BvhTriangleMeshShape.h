#pragma once

#include "ConcaveShape.h"

namespace BulletSharp
{
	ref class StridingMeshInterface;

	public ref class BvhTriangleMeshShape : ConcaveShape
	{
	public:
		BvhTriangleMeshShape();
		BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression);
		BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, bool buildBvh);
		BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax, bool buildBvh);

		void PartialRefitTree(Vector3 bvhAabbMin, Vector3 bvhAabbMax);
		//void PerformConvexcast(TriangleCallback^ callback, Vector3 boxSource, Vector3 boxTarget, Vector3 boxMin, Vector3 boxMax);
		//void PerformRaycast(TriangleCallback^ callback, Vector3 raySource, Vector3 rayTarget);
		void RecalcLocalAabb();
		//void SetOptimizedBvh(BulletSharp::OptimizedBvh^ bvh, Vector3 localScaling);

		//property BulletSharp::OptimizedBvh^ OptimizedBvh
		//{
		//	BulletSharp::OptimizedBvh^ get();
		//	void set(BulletSharp::OptimizedBvh^ value);
		//}

		property bool OwnsBvh
		{
			bool get();
		}

	internal:
		property btBvhTriangleMeshShape* UnmanagedPointer
		{
			btBvhTriangleMeshShape* get() new;
		}
	};
};
