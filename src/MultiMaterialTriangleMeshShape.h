#pragma once

// Fully implemented as of 24 Nov 2010

#include "BvhTriangleMeshShape.h"

namespace BulletSharp
{
	value class BulletMaterial;
	ref class StridingMeshInterface;

	public ref class MultimaterialTriangleMeshShape : BvhTriangleMeshShape
	{
	internal:
		MultimaterialTriangleMeshShape(btMultimaterialTriangleMeshShape* meshShape);

	public:
		MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, bool buildBvh);
		MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression);
		MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression,
			Vector3 bvhAabbMin, Vector3 bvhAabbMax, bool buildBvh);
		MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression,
			Vector3 bvhAabbMin, Vector3 bvhAabbMax);

		BulletMaterial GetMaterialProperties(int partID, int triIndex);

	internal:
		property btMultimaterialTriangleMeshShape* UnmanagedPointer
		{
			btMultimaterialTriangleMeshShape* get() new;
		}
	};
};
