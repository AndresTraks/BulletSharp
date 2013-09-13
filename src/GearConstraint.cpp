#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "GearConstraint.h"
#include "RigidBody.h"

#define Native static_cast<btGearConstraint*>(_native)

GearConstraint::GearConstraint(btGearConstraint* constraint)
: TypedConstraint(constraint)
{
}

GearConstraint::GearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA, Vector3 axisInB, btScalar ratio)
: TypedConstraint(0)
{
	VECTOR3_DEF(axisInA);
	VECTOR3_DEF(axisInB);

	UnmanagedPointer = new btGearConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		VECTOR3_USE(axisInA), VECTOR3_USE(axisInB), ratio);

	VECTOR3_DEL(axisInA);
	VECTOR3_DEL(axisInB);
}

Vector3 GearConstraint::AxisA::get()
{
	return Math::BtVector3ToVector3(&Native->getAxisA());
}

void GearConstraint::AxisA::set(Vector3 value)
{
	VECTOR3_DEF(value);
	Native->setAxisA(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

Vector3 GearConstraint::AxisB::get()
{
	return Math::BtVector3ToVector3(&Native->getAxisB());
}

void GearConstraint::AxisB::set(Vector3 value)
{
	VECTOR3_DEF(value);
	Native->setAxisB(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

btScalar GearConstraint::Ratio::get()
{
	return Native->getRatio();
}
void GearConstraint::Ratio::set(btScalar value)
{
	Native->setRatio(value);
}

#endif
