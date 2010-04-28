#include "StdAfx.h"

#include "ConvexInternalShape.h"

using namespace BulletSharp;

ConvexInternalShape::ConvexInternalShape(btConvexInternalShape* convexInternalShape)
: BulletSharp::ConvexShape(convexInternalShape)
{
}

Vector3 ConvexInternalShape::ImplicitShapeDimensions::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getImplicitShapeDimensions());
}
void ConvexInternalShape::ImplicitShapeDimensions::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	UnmanagedPointer->setImplicitShapeDimensions(*valueTemp);
	delete valueTemp;
}

Vector3 ConvexInternalShape::LocalScalingNV::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getLocalScalingNV());
}

btScalar ConvexInternalShape::MarginNV::get()
{
	return UnmanagedPointer->getMarginNV();
}

btConvexInternalShape* ConvexInternalShape::UnmanagedPointer::get()
{
	return (btConvexInternalShape*)ConvexShape::UnmanagedPointer;
}


ConvexInternalAabbCachingShape::ConvexInternalAabbCachingShape(btConvexInternalAabbCachingShape* convexInternalAabbCachingShape)
: BulletSharp::ConvexInternalShape(convexInternalAabbCachingShape)
{
}
