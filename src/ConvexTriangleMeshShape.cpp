#include "StdAfx.h"

#include "ConvexTriangleMeshShape.h"
#include "StridingMeshInterface.h"

#define Native static_cast<btConvexTriangleMeshShape*>(_native)

ConvexTriangleMeshShape::ConvexTriangleMeshShape(btConvexTriangleMeshShape* native)
	: PolyhedralConvexAabbCachingShape(native)
{
}

ConvexTriangleMeshShape::ConvexTriangleMeshShape(StridingMeshInterface^ meshInterface,
	bool calcAabb)
	: PolyhedralConvexAabbCachingShape(new btConvexTriangleMeshShape(meshInterface->_native,
		calcAabb))
{
	_meshInterface = meshInterface;
}

ConvexTriangleMeshShape::ConvexTriangleMeshShape(StridingMeshInterface^ meshInterface)
	: PolyhedralConvexAabbCachingShape(new btConvexTriangleMeshShape(meshInterface->_native))
{
	_meshInterface = meshInterface;
}

void ConvexTriangleMeshShape::CalculatePrincipalAxisTransform(Matrix% principal, [Out] Vector3% inertia,
	[Out] btScalar% volume)
{
	TRANSFORM_CONV(principal);
	btVector3* inertiaTemp = ALIGNED_NEW(btVector3);
	btScalar volumeTemp;
	Native->calculatePrincipalAxisTransform(TRANSFORM_USE(principal), *inertiaTemp,
		volumeTemp);
	Math::BtTransformToMatrix(TRANSFORM_PTR(principal), principal);
	Math::BtVector3ToVector3(inertiaTemp, inertia);
	volume = volumeTemp;
	TRANSFORM_DEL(principal);
	ALIGNED_FREE(inertiaTemp);
}

StridingMeshInterface^ ConvexTriangleMeshShape::MeshInterface::get()
{
	btStridingMeshInterface* meshInterface = Native->getMeshInterface();
	ReturnCachedObject(StridingMeshInterface, _meshInterface, meshInterface);
}
