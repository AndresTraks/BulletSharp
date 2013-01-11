#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "UniversalConstraint.h"

UniversalConstraint::UniversalConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 anchor, Vector3 axis1, Vector3 axis2)
: Generic6DofConstraint(0)
{
	VECTOR3_DEF(anchor);
	VECTOR3_DEF(axis1);
	VECTOR3_DEF(axis2);

	UnmanagedPointer = ALIGNED_NEW(btUniversalConstraint) (
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		VECTOR3_USE(anchor), VECTOR3_USE(axis1), VECTOR3_USE(axis2));

	VECTOR3_DEL(anchor);
	VECTOR3_DEL(axis1);
	VECTOR3_DEL(axis2);
}

void UniversalConstraint::SetLowerLimit(btScalar ang1min, btScalar ang2min)
{
	UnmanagedPointer->setLowerLimit(ang1min, ang2min);
}

void UniversalConstraint::SetUpperLimit(btScalar ang1max, btScalar ang2max)
{
	UnmanagedPointer->setUpperLimit(ang1max, ang2max);
}

Vector3 UniversalConstraint::Anchor::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getAnchor());
}

Vector3 UniversalConstraint::Anchor2::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getAnchor2());
}

btScalar UniversalConstraint::Angle1::get()
{
	return UnmanagedPointer->getAngle1();
}

btScalar UniversalConstraint::Angle2::get()
{
	return UnmanagedPointer->getAngle2();
}

Vector3 UniversalConstraint::Axis1::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getAxis1());
}

Vector3 UniversalConstraint::Axis2::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getAxis2());
}

btUniversalConstraint* UniversalConstraint::UnmanagedPointer::get()
{
	return (btUniversalConstraint*)TypedConstraint::UnmanagedPointer;
}

#endif
