#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "BvhTriangleMeshShape.h"
#include "ScaledBvhTriangleMeshShape.h"

#define Unmanaged static_cast<btScaledBvhTriangleMeshShape*>(_unmanaged)

ScaledBvhTriangleMeshShape::ScaledBvhTriangleMeshShape(btScaledBvhTriangleMeshShape* shape)
: ConcaveShape(shape)
{
}

ScaledBvhTriangleMeshShape::ScaledBvhTriangleMeshShape(BvhTriangleMeshShape^ childShape, Vector3 localScaling)
: ConcaveShape(0)
{
	VECTOR3_DEF(localScaling);
	UnmanagedPointer = new btScaledBvhTriangleMeshShape((btBvhTriangleMeshShape*)childShape->_unmanaged, VECTOR3_USE(localScaling));
	VECTOR3_DEL(localScaling);
}

BvhTriangleMeshShape^ ScaledBvhTriangleMeshShape::ChildShape::get()
{
	btBvhTriangleMeshShape* childShape = Unmanaged->getChildShape();
	ReturnCachedObjectCastTo(CollisionShape, BvhTriangleMeshShape, _childShape, childShape);
}

#endif
