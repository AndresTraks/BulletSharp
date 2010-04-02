#include "StdAfx.h"

#include "ConvexShape.h"

using namespace BulletSharp;

ConvexShape::ConvexShape(btConvexShape* convexShape)
: CollisionShape(convexShape)
{
}

void ConvexShape::GetAabbNonVirtual(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* tmpAabbMin = new btVector3;
	btVector3* tmpAabbMax = new btVector3;
	
	UnmanagedPointer->getAabbNonVirtual(*Math::MatrixToBtTransform(t), *tmpAabbMin, *tmpAabbMax);

	aabbMin = Math::BtVector3ToVector3(tmpAabbMin);
	aabbMax = Math::BtVector3ToVector3(tmpAabbMax);
}

void ConvexShape::GetAabbSlow(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* tmpAabbMin = new btVector3;
	btVector3* tmpAabbMax = new btVector3;
	
	UnmanagedPointer->getAabbSlow(*Math::MatrixToBtTransform(t), *tmpAabbMin, *tmpAabbMax);

	aabbMin = Math::BtVector3ToVector3(tmpAabbMin);
	aabbMax = Math::BtVector3ToVector3(tmpAabbMax);
}

void ConvexShape::GetPreferredPenetrationDirection(int index, [Out] Vector3% penetrationVector)
{
	btVector3* tmpPenetrationVector = new btVector3;
	UnmanagedPointer->getPreferredPenetrationDirection(index, *tmpPenetrationVector);
	penetrationVector = Math::BtVector3ToVector3(tmpPenetrationVector);
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
	btVector3* btVec = new btVector3;
	ConvexShape_LocalGetSupportingVertex(UnmanagedPointer, Math::Vector3ToBtVector3(vec), btVec);
	return Math::BtVector3ToVector3(btVec);
}

Vector3 ConvexShape::LocalGetSupportingVertexWithoutMargin(Vector3 vec)
{
	btVector3* btVec = new btVector3;
	ConvexShape_LocalGetSupportingVertexWithoutMargin(UnmanagedPointer, Math::Vector3ToBtVector3(vec), btVec);
	return Math::BtVector3ToVector3(btVec);
}

Vector3 ConvexShape::LocalGetSupportVertexNonVirtual(Vector3 vec)
{
	btVector3* btVec = new btVector3;
	ConvexShape_LocalGetSupportVertexNonVirtual(UnmanagedPointer, Math::Vector3ToBtVector3(vec), btVec);
	return Math::BtVector3ToVector3(btVec);
}

Vector3 ConvexShape::LocalGetSupportVertexWithoutMarginNonVirtual(Vector3 vec)
{
	btVector3* btVec = new btVector3;
	ConvexShape_LocalGetSupportVertexWithoutMarginNonVirtual(UnmanagedPointer, Math::Vector3ToBtVector3(vec), btVec);
	return Math::BtVector3ToVector3(btVec);
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
