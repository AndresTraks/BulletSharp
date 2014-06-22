#include "StdAfx.h"

#include "ConvexShape.h"

#define Native static_cast<btConvexShape*>(_native)

ConvexShape::ConvexShape(btConvexShape* native)
	: CollisionShape(native)
{
}

void ConvexShape::BatchedUnitVectorGetSupportingVertexWithoutMargin(array<Vector3>^ vectors, [Out] array<Vector3>^% supportVerticesOut)
{
	int numVertices = vectors->Length;
	btVector3* vectorsTemp = Math::Vector3ArrayToUnmanaged(vectors);
	btVector3* supportVerticesOutTemp = new btVector3[numVertices];

	Native->batchedUnitVectorGetSupportingVertexWithoutMargin(vectorsTemp, supportVerticesOutTemp, numVertices);
	delete[] vectorsTemp;

	supportVerticesOut = Math::Vector3ArrayToManaged(supportVerticesOutTemp, numVertices);
	delete[] supportVerticesOutTemp;
}

void ConvexShape::GetAabbNonVirtual(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	btTransform* tTemp = Math::MatrixToBtTransform(t);
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	
	Native->getAabbNonVirtual(*tTemp, *aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	ALIGNED_FREE(tTemp);
	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

void ConvexShape::GetAabbSlow(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	btTransform* tTemp = Math::MatrixToBtTransform(t);
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	
	Native->getAabbSlow(*tTemp, *aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	ALIGNED_FREE(tTemp);
	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

void ConvexShape::GetPreferredPenetrationDirection(int index, [Out] Vector3% penetrationVector)
{
	btVector3* penetrationVectorTemp = ALIGNED_NEW(btVector3);
	Native->getPreferredPenetrationDirection(index, *penetrationVectorTemp);
	Math::BtVector3ToVector3(penetrationVectorTemp, penetrationVector);
	ALIGNED_FREE(penetrationVectorTemp);
}

#pragma managed(push, off)
void ConvexShape_LocalGetSupportingVertex(btConvexShape* shape, btVector3* vec, btVector3* vecOut)
{
	*vecOut = shape->localGetSupportingVertex(*vec);
}
void ConvexShape_LocalGetSupportingVertexWithoutMargin(btConvexShape* shape, btVector3* vec, btVector3* vecOut)
{
	*vecOut = shape->localGetSupportingVertexWithoutMargin(*vec);
}
void ConvexShape_LocalGetSupportVertexNonVirtual(btConvexShape* shape, btVector3* vec, btVector3* vecOut)
{
	*vecOut = shape->localGetSupportVertexNonVirtual(*vec);
}
void ConvexShape_LocalGetSupportVertexWithoutMarginNonVirtual(btConvexShape* shape, btVector3* vec, btVector3* vecOut)
{
	*vecOut = shape->localGetSupportVertexWithoutMarginNonVirtual(*vec);
}
#pragma managed(pop)
Vector3 ConvexShape::LocalGetSupportingVertex(Vector3 vec)
{
	VECTOR3_DEF(vec);
	btVector3* vecOut = ALIGNED_NEW(btVector3);
	
	ConvexShape_LocalGetSupportingVertex(Native, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	VECTOR3_DEL(vec);
	ALIGNED_FREE(vecOut);
	
	return vertex;
}

Vector3 ConvexShape::LocalGetSupportingVertexWithoutMargin(Vector3 vec)
{
	VECTOR3_DEF(vec);
	btVector3* vecOut = ALIGNED_NEW(btVector3);
	
	ConvexShape_LocalGetSupportingVertexWithoutMargin(Native, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	VECTOR3_DEL(vec);
	ALIGNED_FREE(vecOut);
	
	return vertex;
}

Vector3 ConvexShape::LocalGetSupportVertexNonVirtual(Vector3 vec)
{
	VECTOR3_DEF(vec);
	btVector3* vecOut = ALIGNED_NEW(btVector3);
	
	ConvexShape_LocalGetSupportVertexNonVirtual(Native, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	VECTOR3_DEL(vec);
	ALIGNED_FREE(vecOut);
	
	return vertex;
}

Vector3 ConvexShape::LocalGetSupportVertexWithoutMarginNonVirtual(Vector3 vec)
{
	VECTOR3_DEF(vec);
	btVector3* vecOut = ALIGNED_NEW(btVector3);
	
	ConvexShape_LocalGetSupportVertexWithoutMarginNonVirtual(Native, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	VECTOR3_DEL(vec);
	ALIGNED_FREE(vecOut);
	
	return vertex;
}

void ConvexShape::Project(Matrix transform, Vector3 direction, [Out] btScalar% min, [Out] btScalar% max)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	VECTOR3_DEF(direction);
	btScalar minTemp;
	btScalar maxTemp;
	
	Native->project(*transformTemp, VECTOR3_USE(direction), minTemp, maxTemp);
	min = minTemp;
	max = maxTemp;
	
	VECTOR3_DEL(direction);
	ALIGNED_FREE(transformTemp);
}

btScalar ConvexShape::MarginNonVirtual::get()
{
	return Native->getMarginNonVirtual();
}

int ConvexShape::NumPreferredPenetrationDirections::get()
{
	return Native->getNumPreferredPenetrationDirections();
}
