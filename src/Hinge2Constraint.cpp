#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "Hinge2Constraint.h"
#include "RigidBody.h"

Hinge2Constraint::Hinge2Constraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 anchor, Vector3 axis1, Vector3 axis2)
: Generic6DofSpringConstraint(0)
{
	VECTOR3_DEF(anchor);
	VECTOR3_DEF(axis1);
	VECTOR3_DEF(axis2);

	UnmanagedPointer = new btHinge2Constraint(*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer,
		VECTOR3_USE(anchor), VECTOR3_USE(axis1), VECTOR3_USE(axis2));

	VECTOR3_DEL(anchor);
	VECTOR3_DEL(axis1);
	VECTOR3_DEL(axis2);
}


void Hinge2Constraint::SetLowerLimit(btScalar ang1min)
{
	UnmanagedPointer->setLowerLimit(ang1min);
}

void Hinge2Constraint::SetUpperLimit(btScalar ang1max)
{
	UnmanagedPointer->setUpperLimit(ang1max);
}

Vector3 Hinge2Constraint::Anchor::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getAnchor());
}

Vector3 Hinge2Constraint::Anchor2::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getAnchor2());
}

btScalar Hinge2Constraint::Angle1::get()
{
	return UnmanagedPointer->getAngle1();
}

btScalar Hinge2Constraint::Angle2::get()
{
	return UnmanagedPointer->getAngle2();
}

Vector3 Hinge2Constraint::Axis1::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getAxis1());
}

Vector3 Hinge2Constraint::Axis2::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->getAxis2());
}

btHinge2Constraint* Hinge2Constraint::UnmanagedPointer::get()
{
	return (btHinge2Constraint*)Generic6DofSpringConstraint::UnmanagedPointer;
}

#endif
