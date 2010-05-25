#include "StdAfx.h"

#include "BvhTriangleMeshShape.h"
#include "ScaledBvhTriangleMeshShape.h"

ScaledBvhTriangleMeshShape::ScaledBvhTriangleMeshShape(btScaledBvhTriangleMeshShape* shape)
: ConcaveShape(shape)
{
}

ScaledBvhTriangleMeshShape::ScaledBvhTriangleMeshShape(BvhTriangleMeshShape^ childShape, Vector3 localScaling)
: ConcaveShape(0)
{
	btVector3* localScalingTemp = Math::Vector3ToBtVector3(localScaling);
	UnmanagedPointer = new btScaledBvhTriangleMeshShape(childShape->UnmanagedPointer, *localScalingTemp);
	delete localScalingTemp;
}

BvhTriangleMeshShape^ ScaledBvhTriangleMeshShape::ChildShape::get()
{
	return gcnew BvhTriangleMeshShape(UnmanagedPointer->getChildShape());
}

btScaledBvhTriangleMeshShape* ScaledBvhTriangleMeshShape::UnmanagedPointer::get()
{
	return (btScaledBvhTriangleMeshShape*)ConcaveShape::UnmanagedPointer;
}
