#pragma once

#include "TriangleMeshShape.h"

namespace BulletSharp
{
	ref class OptimizedBvh;
	ref class StridingMeshInterface;
	ref class TriangleCallback;

	public ref class BvhTriangleMeshShape : TriangleMeshShape
	{
	private:
#ifndef DISABLE_BVH
		OptimizedBvh^ _optimizedBvh;
#endif

	internal:
		BvhTriangleMeshShape(btBvhTriangleMeshShape* shape);

	public:
		BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression);
		BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, bool buildBvh);
		BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax, bool buildBvh);
		BvhTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax);

		void BuildOptimizedBvh();
		void PartialRefitTree(Vector3 bvhAabbMin, Vector3 bvhAabbMax);
		void PerformConvexcast(TriangleCallback^ callback, Vector3 boxSource, Vector3 boxTarget, Vector3 boxMin, Vector3 boxMax);
		void PerformRaycast(TriangleCallback^ callback, Vector3 raySource, Vector3 rayTarget);
		void ProcessAllTriangles(TriangleCallback^ callback, Vector3 aabbMin, Vector3 aabbMax);
		void RecalcLocalAabb();
		void RefitTree(Vector3 bvhAabbMin, Vector3 bvhAabbMax);
#ifndef DISABLE_BVH
		void SetOptimizedBvh(BulletSharp::OptimizedBvh^ bvh, Vector3 localScaling);
#endif

#ifndef DISABLE_SERIALIZE
		void SerializeSingleBvh(Serializer^ serializer);
		void SerializeSingleTriangleInfoMap(Serializer^ serializer);
#endif

#ifndef DISABLE_BVH
		property BulletSharp::OptimizedBvh^ OptimizedBvh
		{
			BulletSharp::OptimizedBvh^ get();
			void set(BulletSharp::OptimizedBvh^ value);
		}
#endif

		property bool OwnsBvh
		{
			bool get();
		}

		property bool UsesQuantizedAabbCompression
		{
			bool get();
		}
	};
};
