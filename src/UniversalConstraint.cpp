#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "UniversalConstraint.h"

#define Native static_cast<btUniversalConstraint*>(_native)

UniversalConstraint::UniversalConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 anchor, Vector3 axis1, Vector3 axis2)
	: Generic6DofConstraint(0)
{
	VECTOR3_CONV(anchor);
	VECTOR3_CONV(axis1);
	VECTOR3_CONV(axis2);
	UnmanagedPointer = new btUniversalConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		VECTOR3_USE(anchor), VECTOR3_USE(axis1), VECTOR3_USE(axis2));
	VECTOR3_DEL(anchor);
	VECTOR3_DEL(axis1);
	VECTOR3_DEL(axis2);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

void UniversalConstraint::SetLowerLimit(btScalar ang1min, btScalar ang2min)
{
	Native->setLowerLimit(ang1min, ang2min);
}

void UniversalConstraint::SetUpperLimit(btScalar ang1max, btScalar ang2max)
{
	Native->setUpperLimit(ang1max, ang2max);
}

Vector3 UniversalConstraint::Anchor::get()
{
	return Math::BtVector3ToVector3(&Native->getAnchor());
}

Vector3 UniversalConstraint::Anchor2::get()
{
	return Math::BtVector3ToVector3(&Native->getAnchor2());
}

btScalar UniversalConstraint::Angle1::get()
{
	return Native->getAngle1();
}

btScalar UniversalConstraint::Angle2::get()
{
	return Native->getAngle2();
}

Vector3 UniversalConstraint::Axis1::get()
{
	return Math::BtVector3ToVector3(&Native->getAxis1());
}

Vector3 UniversalConstraint::Axis2::get()
{
	return Math::BtVector3ToVector3(&Native->getAxis2());
}

#endif
