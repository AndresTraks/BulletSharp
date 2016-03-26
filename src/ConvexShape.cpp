#include "StdAfx.h"

#include "ConvexShape.h"

#define Native static_cast<btConvexShape*>(_native)

ConvexShape::ConvexShape(btConvexShape* native)
	: CollisionShape(native)
{
}

void ConvexShape::BatchedUnitVectorGetSupportingVertexWithoutMargin(array<Vector3>^ vectors,
	[Out] array<Vector3>^% supportVerticesOut)
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
	TRANSFORM_CONV(t);
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	Native->getAabbNonVirtual(TRANSFORM_USE(t), *aabbMinTemp, *aabbMaxTemp);
	TRANSFORM_DEL(t);
	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);
	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

void ConvexShape::GetAabbSlow(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	TRANSFORM_CONV(t);
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	Native->getAabbSlow(TRANSFORM_USE(t), *aabbMinTemp, *aabbMaxTemp);
	TRANSFORM_DEL(t);
	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);
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
	VECTOR3_CONV(vec);
	btVector3* vecOut = ALIGNED_NEW(btVector3);
	ConvexShape_LocalGetSupportingVertex(Native, VECTOR3_PTR(vec), vecOut);
	VECTOR3_DEL(vec);
	Vector3 ret = Math::BtVector3ToVector3(vecOut);
	ALIGNED_FREE(vecOut);
	return ret;
}

Vector3 ConvexShape::LocalGetSupportingVertexWithoutMargin(Vector3 vec)
{
	VECTOR3_CONV(vec);
	btVector3* vecOut = ALIGNED_NEW(btVector3);
	ConvexShape_LocalGetSupportingVertexWithoutMargin(Native, VECTOR3_PTR(vec), vecOut);
	VECTOR3_DEL(vec);
	Vector3 ret = Math::BtVector3ToVector3(vecOut);
	ALIGNED_FREE(vecOut);
	return ret;
}

Vector3 ConvexShape::LocalGetSupportVertexNonVirtual(Vector3 vec)
{
	VECTOR3_CONV(vec);
	btVector3* vecOut = ALIGNED_NEW(btVector3);
	ConvexShape_LocalGetSupportVertexNonVirtual(Native, VECTOR3_PTR(vec), vecOut);
	VECTOR3_DEL(vec);
	Vector3 ret = Math::BtVector3ToVector3(vecOut);
	ALIGNED_FREE(vecOut);
	return ret;
}

Vector3 ConvexShape::LocalGetSupportVertexWithoutMarginNonVirtual(Vector3 vec)
{
	VECTOR3_CONV(vec);
	btVector3* vecOut = ALIGNED_NEW(btVector3);
	ConvexShape_LocalGetSupportVertexWithoutMarginNonVirtual(Native, VECTOR3_PTR(vec), vecOut);
	VECTOR3_DEL(vec);
	Vector3 ret = Math::BtVector3ToVector3(vecOut);
	ALIGNED_FREE(vecOut);
	return ret;
}

void ConvexShape::Project(Matrix% transform, Vector3% direction, [Out] btScalar% minProj, [Out] btScalar% maxProj,
	[Out] Vector3% witnesPtMin, [Out] Vector3% witnesPtMax)
{
	TRANSFORM_CONV(transform);
	VECTOR3_CONV(direction);
	btScalar minProjTemp;
	btScalar maxProjTemp;
	btVector3* witnesPtMinTemp = ALIGNED_NEW(btVector3);
	btVector3* witnesPtMaxTemp = ALIGNED_NEW(btVector3);
	Native->project(TRANSFORM_USE(transform), VECTOR3_USE(direction), minProjTemp, maxProjTemp,
		*witnesPtMinTemp, *witnesPtMaxTemp);
	TRANSFORM_DEL(transform);
	VECTOR3_DEL(direction);
	Math::BtVector3ToVector3(witnesPtMinTemp, witnesPtMin);
	Math::BtVector3ToVector3(witnesPtMaxTemp, witnesPtMax);
	ALIGNED_FREE(witnesPtMinTemp);
	ALIGNED_FREE(witnesPtMaxTemp);
	minProj = minProjTemp;
	maxProj = maxProjTemp;
}

btScalar ConvexShape::MarginNonVirtual::get()
{
	return Native->getMarginNonVirtual();
}

int ConvexShape::NumPreferredPenetrationDirections::get()
{
	return Native->getNumPreferredPenetrationDirections();
}
