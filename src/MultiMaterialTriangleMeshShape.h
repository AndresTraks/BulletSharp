#pragma once

// Fully implemented as of 25 May 2010

#pragma managed(push, off)
#include <BulletCollision/CollisionShapes/btMultiMaterialTriangleMeshShape.h>
#pragma managed(pop)

#include "BvhTriangleMeshShape.h"

namespace BulletSharp
{
	ref class BulletMaterial;
	ref class StridingMeshInterface;

	public ref class MultiMaterialTriangleMeshShape : BvhTriangleMeshShape
	{
	internal:
		MultiMaterialTriangleMeshShape(btMultimaterialTriangleMeshShape* meshShape);

	public:
		MultiMaterialTriangleMeshShape();
		MultiMaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, bool buildBvh);
		MultiMaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression);
		MultiMaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression,
			Vector3 bvhAabbMin, Vector3 bvhAabbMax, bool buildBvh);
		MultiMaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression,
			Vector3 bvhAabbMin, Vector3 bvhAabbMax);

		BulletMaterial^ GetMaterialProperties(int partID, int triIndex);

	internal:
		property btMultimaterialTriangleMeshShape* UnmanagedPointer
		{
			btMultimaterialTriangleMeshShape* get() new;
		}
	};
};
