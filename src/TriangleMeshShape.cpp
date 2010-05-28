#include "StdAfx.h"

#include "StridingMeshInterface.h"
#include "TriangleMeshShape.h"

TriangleMeshShape::TriangleMeshShape(btTriangleMeshShape* shape)
: ConcaveShape(shape)
{
}

#pragma managed(push, off)
void TriangleMeshShape_LocalGetSupportingVertex(btTriangleMeshShape* shape, btVector3* vec, btVector3* vecOut)
{
	*vecOut = shape->localGetSupportingVertex(*vec);
}

void TriangleMeshShape_LocalGetSupportingVertexWithoutMargin(btTriangleMeshShape* shape, btVector3* vec, btVector3* vecOut)
{
	*vecOut = shape->localGetSupportingVertex(*vec);
}
#pragma managed(pop)

Vector3 TriangleMeshShape::LocalGetSupportingVertex(Vector3 vec)
{
	btVector3* vecTemp = Math::Vector3ToBtVector3(vec);
	btVector3* vecOut = new btVector3();
	
	TriangleMeshShape_LocalGetSupportingVertex(UnmanagedPointer, vecTemp, vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	delete vecTemp;
	delete vecOut;
	
	return vertex;
}

Vector3 TriangleMeshShape::LocalGetSupportingVertexWithoutMargin(Vector3 vec)
{
	btVector3* vecTemp = Math::Vector3ToBtVector3(vec);
	btVector3* vecOut = new btVector3();
	
	TriangleMeshShape_LocalGetSupportingVertexWithoutMargin(UnmanagedPointer, vecTemp, vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	delete vecTemp;
	delete vecOut;
	
	return vertex;
}

void TriangleMeshShape::RecalcLocalAabb()
{
	UnmanagedPointer->recalcLocalAabb();
}

Vector3 TriangleMeshShape::LocalAabbMax::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getLocalAabbMax());
}

Vector3 TriangleMeshShape::LocalAabbMin::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getLocalAabbMin());
}

StridingMeshInterface^ TriangleMeshShape::MeshInterface::get()
{
	return gcnew StridingMeshInterface(UnmanagedPointer->getMeshInterface());
}

btTriangleMeshShape* TriangleMeshShape::UnmanagedPointer::get()
{
	return (btTriangleMeshShape*)ConcaveShape::UnmanagedPointer;
}
