#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BulletMaterial.h"
#include "MultimaterialTriangleMeshShape.h"
#include "StridingMeshInterface.h"

#define Native static_cast<btMultimaterialTriangleMeshShape*>(_native)

MultimaterialTriangleMeshShape::MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface,
	bool useQuantizedAabbCompression, bool buildBvh)
	: BvhTriangleMeshShape(0)
{
	UnmanagedPointer = new btMultimaterialTriangleMeshShape(meshInterface->_native,
		useQuantizedAabbCompression, buildBvh);

	_meshInterface = meshInterface;
}

MultimaterialTriangleMeshShape::MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface,
	bool useQuantizedAabbCompression)
	: BvhTriangleMeshShape(0)
{
	UnmanagedPointer = new btMultimaterialTriangleMeshShape(meshInterface->_native,
		useQuantizedAabbCompression);

	_meshInterface = meshInterface;
}

MultimaterialTriangleMeshShape::MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface,
	bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax, bool buildBvh)
	: BvhTriangleMeshShape(0)
{
	VECTOR3_CONV(bvhAabbMin);
	VECTOR3_CONV(bvhAabbMax);
	UnmanagedPointer = new btMultimaterialTriangleMeshShape(meshInterface->_native, useQuantizedAabbCompression,
		VECTOR3_USE(bvhAabbMin), VECTOR3_USE(bvhAabbMax), buildBvh);
	VECTOR3_DEL(bvhAabbMin);
	VECTOR3_DEL(bvhAabbMax);

	_meshInterface = meshInterface;
}

MultimaterialTriangleMeshShape::MultimaterialTriangleMeshShape(StridingMeshInterface^ meshInterface,
	bool useQuantizedAabbCompression, Vector3 bvhAabbMin, Vector3 bvhAabbMax)
	: BvhTriangleMeshShape(0)
{
	VECTOR3_CONV(bvhAabbMin);
	VECTOR3_CONV(bvhAabbMax);
	UnmanagedPointer = new btMultimaterialTriangleMeshShape(meshInterface->_native, useQuantizedAabbCompression,
		VECTOR3_USE(bvhAabbMin), VECTOR3_USE(bvhAabbMax));
	VECTOR3_DEL(bvhAabbMin);
	VECTOR3_DEL(bvhAabbMax);

	_meshInterface = meshInterface;
}

BulletMaterial MultimaterialTriangleMeshShape::GetMaterialProperties(int partID, int triIndex)
{
	return BulletMaterial((btMaterial*)Native->getMaterialProperties(partID, triIndex));
}

#endif
