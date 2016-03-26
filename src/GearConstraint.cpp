#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "GearConstraint.h"
#include "RigidBody.h"

#define Native static_cast<btGearConstraint*>(_native)

GearConstraint::GearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA,
	Vector3 axisInB, btScalar ratio)
	: TypedConstraint(0)
{
	VECTOR3_CONV(axisInA);
	VECTOR3_CONV(axisInB);
	UnmanagedPointer = new btGearConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		VECTOR3_USE(axisInA), VECTOR3_USE(axisInB), ratio);
	VECTOR3_DEL(axisInA);
	VECTOR3_DEL(axisInB);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

GearConstraint::GearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA,
	Vector3 axisInB)
	: TypedConstraint(0)
{
	VECTOR3_CONV(axisInA);
	VECTOR3_CONV(axisInB);
	UnmanagedPointer = new btGearConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		VECTOR3_USE(axisInA), VECTOR3_USE(axisInB));
	VECTOR3_DEL(axisInA);
	VECTOR3_DEL(axisInB);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

Vector3 GearConstraint::AxisA::get()
{
	return Math::BtVector3ToVector3(&Native->getAxisA());
}
void GearConstraint::AxisA::set(Vector3 axisA)
{
	VECTOR3_CONV(axisA);
	Native->setAxisA(VECTOR3_USE(axisA));
	VECTOR3_DEL(axisA);
}

Vector3 GearConstraint::AxisB::get()
{
	return Math::BtVector3ToVector3(&Native->getAxisB());
}
void GearConstraint::AxisB::set(Vector3 axisB)
{
	VECTOR3_CONV(axisB);
	Native->setAxisB(VECTOR3_USE(axisB));
	VECTOR3_DEL(axisB);
}

btScalar GearConstraint::Ratio::get()
{
	return Native->getRatio();
}
void GearConstraint::Ratio::set(btScalar ratio)
{
	Native->setRatio(ratio);
}

#endif
