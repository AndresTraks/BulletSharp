#include "StdAfx.h"

#include "BulletMaterial.h"
#include "MultiMaterialTriangleMeshShape.h"
#include "StridingMeshInterface.h"

MultiMaterialTriangleMeshShape::MultiMaterialTriangleMeshShape(btMultimaterialTriangleMeshShape* meshShape)
: BvhTriangleMeshShape(meshShape)
{
}

MultiMaterialTriangleMeshShape::MultiMaterialTriangleMeshShape()
: BvhTriangleMeshShape(new btMultimaterialTriangleMeshShape())
{
}

MultiMaterialTriangleMeshShape::MultiMaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression, bool buildBvh)
: BvhTriangleMeshShape(new btMultimaterialTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression, buildBvh))
{
}

MultiMaterialTriangleMeshShape::MultiMaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression)
: BvhTriangleMeshShape(new btMultimaterialTriangleMeshShape(meshInterface->UnmanagedPointer, useQuantizedAabbCompression))
{
}

MultiMaterialTriangleMeshShape::MultiMaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression,
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

MultiMaterialTriangleMeshShape::MultiMaterialTriangleMeshShape(StridingMeshInterface^ meshInterface, bool useQuantizedAabbCompression,
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

BulletMaterial^ MultiMaterialTriangleMeshShape::GetMaterialProperties(int partID, int triIndex)
{
	return gcnew BulletMaterial((btMaterial*)UnmanagedPointer->getMaterialProperties(partID, triIndex));
}

btMultimaterialTriangleMeshShape* MultiMaterialTriangleMeshShape::UnmanagedPointer::get()
{
	return (btMultimaterialTriangleMeshShape*)BvhTriangleMeshShape::UnmanagedPointer;
}
