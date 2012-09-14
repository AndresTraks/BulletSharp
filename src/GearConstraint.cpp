#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "GearConstraint.h"
#include "RigidBody.h"

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
		*(btRigidBody*)rigidBodyA->_unmanaged, *(btRigidBody*)rigidBodyB->_unmanaged,
		VECTOR3_USE(axisInA), VECTOR3_USE(axisInB), ratio);

	VECTOR3_DEL(axisInA);
	VECTOR3_DEL(axisInB);
}

#endif
