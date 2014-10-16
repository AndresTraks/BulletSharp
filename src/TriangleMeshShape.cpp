#include "StdAfx.h"

#include "StridingMeshInterface.h"
#include "TriangleMeshShape.h"

#define Native static_cast<btTriangleMeshShape*>(_native)

TriangleMeshShape::TriangleMeshShape(btTriangleMeshShape* native)
	: ConcaveShape(native)
{
}

#pragma managed(push, off)
void TriangleMeshShape_LocalGetSupportingVertex(btTriangleMeshShape* shape, btVector3* vec, btVector3* vecOut)
{
	*vecOut = shape->localGetSupportingVertex(*vec);
}

void TriangleMeshShape_LocalGetSupportingVertexWithoutMargin(btTriangleMeshShape* shape, btVector3* vec, btVector3* vecOut)
{
	*vecOut = shape->localGetSupportingVertexWithoutMargin(*vec);
}
#pragma managed(pop)

Vector3 TriangleMeshShape::LocalGetSupportingVertex(Vector3 vec)
{
	VECTOR3_CONV(vec);
	btVector3* vecOut = ALIGNED_NEW(btVector3);
	TriangleMeshShape_LocalGetSupportingVertex(Native, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	VECTOR3_DEL(vec);
	ALIGNED_FREE(vecOut);
	return vertex;
}

Vector3 TriangleMeshShape::LocalGetSupportingVertexWithoutMargin(Vector3 vec)
{
	VECTOR3_CONV(vec);
	btVector3* vecOut = ALIGNED_NEW(btVector3);
	TriangleMeshShape_LocalGetSupportingVertexWithoutMargin(Native, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);	VECTOR3_DEL(vec);
	ALIGNED_FREE(vecOut);
	return vertex;
}

void TriangleMeshShape::RecalcLocalAabb()
{
	Native->recalcLocalAabb();
}

Vector3 TriangleMeshShape::LocalAabbMax::get()
{
	return Math::BtVector3ToVector3(&Native->getLocalAabbMax());
}

Vector3 TriangleMeshShape::LocalAabbMin::get()
{
	return Math::BtVector3ToVector3(&Native->getLocalAabbMin());
}

StridingMeshInterface^ TriangleMeshShape::MeshInterface::get()
{
	btStridingMeshInterface* meshInterface = Native->getMeshInterface();
	ReturnCachedObject(StridingMeshInterface, _meshInterface, meshInterface);
}
