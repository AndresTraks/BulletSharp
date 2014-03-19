#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BvhTriangleMeshShape.h"
#include "ScaledBvhTriangleMeshShape.h"

#define Native static_cast<btScaledBvhTriangleMeshShape*>(_native)

ScaledBvhTriangleMeshShape::ScaledBvhTriangleMeshShape(btScaledBvhTriangleMeshShape* native)
	: ConcaveShape(native)
{
}

ScaledBvhTriangleMeshShape::ScaledBvhTriangleMeshShape(BvhTriangleMeshShape^ childShape,
	Vector3 localScaling)
	: ConcaveShape(0)
{
	VECTOR3_DEF(localScaling);
	UnmanagedPointer = new btScaledBvhTriangleMeshShape((btBvhTriangleMeshShape*)childShape->_native,
		VECTOR3_USE(localScaling));
	VECTOR3_DEL(localScaling);
}

BvhTriangleMeshShape^ ScaledBvhTriangleMeshShape::ChildShape::get()
{
	return static_cast<BvhTriangleMeshShape^>(CollisionShape::GetManaged(Native->getChildShape()));
}

#endif
