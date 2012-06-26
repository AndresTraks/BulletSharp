#include "StdAfx.h"

#include "ConvexTriangleMeshShape.h"
#include "StridingMeshInterface.h"

ConvexTriangleMeshShape::ConvexTriangleMeshShape(btConvexTriangleMeshShape* meshShape)
: PolyhedralConvexAabbCachingShape(meshShape)
{
}

ConvexTriangleMeshShape::ConvexTriangleMeshShape(StridingMeshInterface^ meshInterface, bool calcAabb)
: PolyhedralConvexAabbCachingShape(new btConvexTriangleMeshShape(meshInterface->UnmanagedPointer, calcAabb))
{
}

ConvexTriangleMeshShape::ConvexTriangleMeshShape(StridingMeshInterface^ meshInterface)
: PolyhedralConvexAabbCachingShape(new btConvexTriangleMeshShape(meshInterface->UnmanagedPointer))
{
}

void ConvexTriangleMeshShape::CalculatePrincipalAxisTransform(Matrix principal, Vector3 inertia, btScalar volume)
{
	btTransform* principalTemp = Math::MatrixToBtTransform(principal);
	VECTOR3_DEF(inertia);

	UnmanagedPointer->calculatePrincipalAxisTransform(*principalTemp, VECTOR3_USE(inertia), volume);

	delete principalTemp;
	VECTOR3_DEL(inertia);
}

StridingMeshInterface^ ConvexTriangleMeshShape::MeshInterface::get()
{
	btStridingMeshInterface* stridingMeshInterface = UnmanagedPointer->getMeshInterface();
	ReturnCachedObject(StridingMeshInterface, _stridingMeshInterface, stridingMeshInterface);
}

btConvexTriangleMeshShape* ConvexTriangleMeshShape::UnmanagedPointer::get()
{
	return (btConvexTriangleMeshShape*)PolyhedralConvexAabbCachingShape::UnmanagedPointer;
}
