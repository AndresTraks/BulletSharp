#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "Hinge2Constraint.h"
#include "RigidBody.h"

Hinge2Constraint::Hinge2Constraint(RigidBody^ rbA, RigidBody^ rbB,
	Vector3 anchor, Vector3 axis1, Vector3 axis2)
: Generic6DofSpringConstraint(0)
{
	this->RigidBodyA = rbA;
	this->RigidBodyA = rbB;

	btVector3* anchorTemp = Math::Vector3ToBtVector3(anchor);
	btVector3* axis1Temp = Math::Vector3ToBtVector3(axis1);
	btVector3* axis2Temp = Math::Vector3ToBtVector3(axis2);

	UnmanagedPointer = new btHinge2Constraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
		*anchorTemp, *axis1Temp, *axis2Temp);

	delete anchorTemp;
	delete axis1Temp;
	delete axis2Temp;
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
