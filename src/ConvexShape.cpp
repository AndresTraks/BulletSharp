#include "StdAfx.h"

#include "ConvexShape.h"

using namespace BulletSharp;

ConvexShape::ConvexShape(btConvexShape* convexShape)
: CollisionShape(convexShape)
{
}

void ConvexShape::GetAabbNonVirtual(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;
	
	UnmanagedPointer->getAabbNonVirtual(*Math::MatrixToBtTransform(t), *aabbMinTemp, *aabbMaxTemp);

	aabbMin = Math::BtVector3ToVector3(aabbMinTemp);
	aabbMax = Math::BtVector3ToVector3(aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void ConvexShape::GetAabbSlow(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;
	
	UnmanagedPointer->getAabbSlow(*Math::MatrixToBtTransform(t), *aabbMinTemp, *aabbMaxTemp);

	aabbMin = Math::BtVector3ToVector3(aabbMinTemp);
	aabbMax = Math::BtVector3ToVector3(aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void ConvexShape::GetPreferredPenetrationDirection(int index, [Out] Vector3% penetrationVector)
{
	btVector3* penetrationVectorTemp = new btVector3;
	UnmanagedPointer->getPreferredPenetrationDirection(index, *penetrationVectorTemp);
	penetrationVector = Math::BtVector3ToVector3(penetrationVectorTemp);
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
	btVector3* vecTemp = new btVector3;
	ConvexShape_LocalGetSupportingVertex(UnmanagedPointer, Math::Vector3ToBtVector3(vec), vecTemp);
	Vector3 vertex = Math::BtVector3ToVector3(vecTemp);
	delete vecTemp;
	return vertex;
}

Vector3 ConvexShape::LocalGetSupportingVertexWithoutMargin(Vector3 vec)
{
	btVector3* vecTemp = new btVector3;
	ConvexShape_LocalGetSupportingVertexWithoutMargin(UnmanagedPointer, Math::Vector3ToBtVector3(vec), vecTemp);
	Vector3 vertex = Math::BtVector3ToVector3(vecTemp);
	delete vecTemp;
	return vertex;
}

Vector3 ConvexShape::LocalGetSupportVertexNonVirtual(Vector3 vec)
{
	btVector3* vecTemp = new btVector3;
	ConvexShape_LocalGetSupportVertexNonVirtual(UnmanagedPointer, Math::Vector3ToBtVector3(vec), vecTemp);
	Vector3 vertex = Math::BtVector3ToVector3(vecTemp);
	delete vecTemp;
	return vertex;
}

Vector3 ConvexShape::LocalGetSupportVertexWithoutMarginNonVirtual(Vector3 vec)
{
	btVector3* vecTemp = new btVector3;
	ConvexShape_LocalGetSupportVertexWithoutMarginNonVirtual(UnmanagedPointer, Math::Vector3ToBtVector3(vec), vecTemp);
	Vector3 vertex = Math::BtVector3ToVector3(vecTemp);
	delete vecTemp;
	return vertex;
}

ConvexShape^ ConvexShape::Upcast(CollisionShape^ shape)
{
	return gcnew ConvexShape((btConvexShape*)shape->UnmanagedPointer);
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
