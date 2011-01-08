#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BulletMaterial.h"
#include "MultimaterialTriangleMeshShape.h"
#include "StridingMeshInterface.h"

MultimaterialTriangleMeshShape::MultimaterialTriangleMeshShape(btMultimaterialTriangleMeshShape* meshShape)
: BvhTriangleMeshShape(meshShape)
{
}

MultimaterialTriangleMeshShape::MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, bool buildBvh)
: BvhTriangleMeshShape(new btMultimaterialTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, buildBvh))
{
}

MultimaterialTriangleMeshShape::MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression)
: BvhTriangleMeshShape(new btMultimaterialTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression))
{
}

MultimaterialTriangleMeshShape::MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression,
	Vector3 bvhAabbMin, Vector3 bvhAabbMax, bool buildBvh)
: BvhTriangleMeshShape(0)
{
	btVector3* bvhAabbMinTemp = Math::Vector3ToBtVector3(bvhAabbMin);
	btVector3* bvhAabbMaxTemp = Math::Vector3ToBtVector3(bvhAabbMax);

	UnmanagedPointer = new btMultimaterialTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression,
		*bvhAabbMinTemp, *bvhAabbMaxTemp, buildBvh);

	delete bvhAabbMinTemp;
	delete bvhAabbMaxTemp;
}

MultimaterialTriangleMeshShape::MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression,
	Vector3 bvhAabbMin, Vector3 bvhAabbMax)
: BvhTriangleMeshShape(0)
{
	btVector3* bvhAabbMinTemp = Math::Vector3ToBtVector3(bvhAabbMin);
	btVector3* bvhAabbMaxTemp = Math::Vector3ToBtVector3(bvhAabbMax);

	UnmanagedPointer = new btMultimaterialTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression,
		*bvhAabbMinTemp, *bvhAabbMaxTemp);

	delete bvhAabbMinTemp;
	delete bvhAabbMaxTemp;
}

BulletMaterial MultimaterialTriangleMeshShape::GetMaterialProperties(int partID, int triIndex)
{
	return BulletMaterial((btMaterial*)UnmanagedPointer->getMaterialProperties(partID, triIndex));
}

btMultimaterialTriangleMeshShape* MultimaterialTriangleMeshShape::UnmanagedPointer::get()
{
	return (btMultimaterialTriangleMeshShape*)BvhTriangleMeshShape::UnmanagedPointer;
}

#endif
