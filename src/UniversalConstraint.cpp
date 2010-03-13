#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "UniversalConstraint.h"

UniversalConstraint::UniversalConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Vector3 anchor, Vector3 axis1, Vector3 axis2)
	: Generic6DofConstraint(new btUniversalConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
	*Math::Vector3ToBtVector3(anchor), *Math::Vector3ToBtVector3(axis1), *Math::Vector3ToBtVector3(axis2)))
{
	this->RigidBodyA = rbA;
	this->RigidBodyA = rbB;
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
