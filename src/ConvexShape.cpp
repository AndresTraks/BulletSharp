#include "StdAfx.h"

#include "ConvexShape.h"

using namespace BulletSharp;

ConvexShape::ConvexShape(btConvexShape* convexShape)
: CollisionShape(convexShape)
{
}

void ConvexShape::BatchedUnitVectorGetSupportingVertexWithoutMargin(array<Vector3>^ vectors, [Out] array<Vector3>^% supportVerticesOut)
{
	int numVertices = vectors->Length;
	btVector3* vectorsTemp = Math::Vector3ArrayToUnmanaged(vectors);
	btVector3* supportVerticesOutTemp = new btVector3[numVertices];

	UnmanagedPointer->batchedUnitVectorGetSupportingVertexWithoutMargin(vectorsTemp, supportVerticesOutTemp, numVertices);
	delete[] vectorsTemp;

	supportVerticesOut = Math::Vector3ArrayToManaged(supportVerticesOutTemp, numVertices);
	delete[] supportVerticesOutTemp;
}

void ConvexShape::GetAabbNonVirtual(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	btTransform* tTemp = Math::MatrixToBtTransform(t);
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;
	
	UnmanagedPointer->getAabbNonVirtual(*tTemp, *aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	delete tTemp;
	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void ConvexShape::GetAabbSlow(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	btTransform* tTemp = Math::MatrixToBtTransform(t);
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;
	
	UnmanagedPointer->getAabbSlow(*tTemp, *aabbMinTemp, *aabbMaxTemp);

	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);

	delete tTemp;
	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void ConvexShape::GetPreferredPenetrationDirection(int index, [Out] Vector3% penetrationVector)
{
	btVector3* penetrationVectorTemp = new btVector3;
	UnmanagedPointer->getPreferredPenetrationDirection(index, *penetrationVectorTemp);
	Math::BtVector3ToVector3(penetrationVectorTemp, penetrationVector);
	delete penetrationVectorTemp;
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
	btVector3* vecOut = new btVector3;
	
	ConvexShape_LocalGetSupportingVertex(UnmanagedPointer, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	VECTOR3_DEL(vec);
	delete vecOut;
	
	return vertex;
}

Vector3 ConvexShape::LocalGetSupportingVertexWithoutMargin(Vector3 vec)
{
	VECTOR3_DEF(vec);
	btVector3* vecOut = new btVector3;
	
	ConvexShape_LocalGetSupportingVertexWithoutMargin(UnmanagedPointer, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	VECTOR3_DEL(vec);
	delete vecOut;
	
	return vertex;
}

Vector3 ConvexShape::LocalGetSupportVertexNonVirtual(Vector3 vec)
{
	VECTOR3_DEF(vec);
	btVector3* vecOut = new btVector3;
	
	ConvexShape_LocalGetSupportVertexNonVirtual(UnmanagedPointer, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	VECTOR3_DEL(vec);
	delete vecOut;
	
	return vertex;
}

Vector3 ConvexShape::LocalGetSupportVertexWithoutMarginNonVirtual(Vector3 vec)
{
	VECTOR3_DEF(vec);
	btVector3* vecOut = new btVector3;
	
	ConvexShape_LocalGetSupportVertexWithoutMarginNonVirtual(UnmanagedPointer, VECTOR3_PTR(vec), vecOut);
	Vector3 vertex = Math::BtVector3ToVector3(vecOut);
	
	VECTOR3_DEL(vec);
	delete vecOut;
	
	return vertex;
}

void ConvexShape::Project(Matrix transform, Vector3 direction, [Out] btScalar% min, [Out] btScalar% max)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	VECTOR3_DEF(direction);
	btScalar minTemp;
	btScalar maxTemp;
	
	UnmanagedPointer->project(*transformTemp, VECTOR3_USE(direction), minTemp, maxTemp);
	min = minTemp;
	max = maxTemp;
	
	VECTOR3_DEL(direction);
	delete transformTemp;
}

btScalar ConvexShape::MarginNonVirtual::get()
{
	return UnmanagedPointer->getMarginNonVirtual();
}

int ConvexShape::NumPreferredPenetrationDirections::get()
{
	return UnmanagedPointer->getNumPreferredPenetrationDirections();
}

btConvexShape* ConvexShape::UnmanagedPointer::get()
{
	return (btConvexShape*)CollisionShape::UnmanagedPointer;
}
