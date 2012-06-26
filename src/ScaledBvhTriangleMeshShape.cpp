#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BvhTriangleMeshShape.h"
#include "ScaledBvhTriangleMeshShape.h"

ScaledBvhTriangleMeshShape::ScaledBvhTriangleMeshShape(btScaledBvhTriangleMeshShape* shape)
: ConcaveShape(shape)
{
}

ScaledBvhTriangleMeshShape::ScaledBvhTriangleMeshShape(BvhTriangleMeshShape^ childShape, Vector3 localScaling)
: ConcaveShape(0)
{
	VECTOR3_DEF(localScaling);
	UnmanagedPointer = new btScaledBvhTriangleMeshShape(childShape->UnmanagedPointer, VECTOR3_USE(localScaling));
	VECTOR3_DEL(localScaling);
}

BvhTriangleMeshShape^ ScaledBvhTriangleMeshShape::ChildShape::get()
{
	btBvhTriangleMeshShape* childShape = UnmanagedPointer->getChildShape();
	ReturnCachedObjectUpcastNullableCastTo(CollisionShape, BvhTriangleMeshShape, _childShape, childShape);
}

btScaledBvhTriangleMeshShape* ScaledBvhTriangleMeshShape::UnmanagedPointer::get()
{
	return (btScaledBvhTriangleMeshShape*)ConcaveShape::UnmanagedPointer;
}

#endif
