#include "StdAfx.h"

#include "StridingMeshInterface.h"
#include "TriangleMeshShape.h"

#define Unmanaged static_cast<btTriangleMeshShape*>(_unmanaged)

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
	VECTOR3_DEF(vec);
	btVector3* vecOut = new btVector3;
	
	TriangleMeshShape_LocalGetSupportingVertex(Unmanaged, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	VECTOR3_DEL(vec);
	delete vecOut;
	
	return vertex;
}

Vector3 TriangleMeshShape::LocalGetSupportingVertexWithoutMargin(Vector3 vec)
{
	VECTOR3_DEF(vec);
	btVector3* vecOut = new btVector3;
	
	TriangleMeshShape_LocalGetSupportingVertexWithoutMargin(Unmanaged, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	VECTOR3_DEL(vec);
	delete vecOut;
	
	return vertex;
}

void TriangleMeshShape::RecalcLocalAabb()
{
	Unmanaged->recalcLocalAabb();
}

Vector3 TriangleMeshShape::LocalAabbMax::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getLocalAabbMax());
}

Vector3 TriangleMeshShape::LocalAabbMin::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->getLocalAabbMin());
}

StridingMeshInterface^ TriangleMeshShape::MeshInterface::get()
{
	btStridingMeshInterface* meshInterface = Unmanaged->getMeshInterface();
	ReturnCachedObject(StridingMeshInterface, _meshInterface, meshInterface);
}
