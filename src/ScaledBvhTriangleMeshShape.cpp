#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BvhTriangleMeshShape.h"
#include "ScaledBvhTriangleMeshShape.h"

#define Native static_cast<btScaledBvhTriangleMeshShape*>(_native)

ScaledBvhTriangleMeshShape::ScaledBvhTriangleMeshShape(BvhTriangleMeshShape^ childShape,
	Vector3 localScaling)
	: ConcaveShape(0)
{
	VECTOR3_CONV(localScaling);
	UnmanagedPointer = new btScaledBvhTriangleMeshShape((btBvhTriangleMeshShape*)childShape->_native,
		VECTOR3_USE(localScaling));
	VECTOR3_DEL(localScaling);
	_childShape = childShape;
}

BvhTriangleMeshShape^ ScaledBvhTriangleMeshShape::ChildShape::get()
{
	return _childShape;
}

#endif
