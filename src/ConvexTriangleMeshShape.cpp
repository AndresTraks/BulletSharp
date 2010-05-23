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
	btVector3* inertiaTemp = Math::Vector3ToBtVector3(inertia);

	UnmanagedPointer->calculatePrincipalAxisTransform(*principalTemp, *inertiaTemp, volume);

	delete principalTemp;
	delete inertiaTemp;
}

StridingMeshInterface^ ConvexTriangleMeshShape::MeshInterface::get()
{
	return gcnew StridingMeshInterface(UnmanagedPointer->getMeshInterface());
}

btConvexTriangleMeshShape* ConvexTriangleMeshShape::UnmanagedPointer::get()
{
	return (btConvexTriangleMeshShape*)PolyhedralConvexAabbCachingShape::UnmanagedPointer;
}
