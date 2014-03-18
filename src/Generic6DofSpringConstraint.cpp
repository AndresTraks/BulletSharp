#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "Generic6DofSpringConstraint.h"
#include "RigidBody.h"

#define Native static_cast<btGeneric6DofSpringConstraint*>(_native)

Generic6DofSpringConstraint::Generic6DofSpringConstraint(btGeneric6DofSpringConstraint* native)
	: Generic6DofConstraint(native)
{
}

Generic6DofSpringConstraint::Generic6DofSpringConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
	: Generic6DofConstraint(0)
{
	TRANSFORM_CONV(frameInA);
	TRANSFORM_CONV(frameInB);
	UnmanagedPointer = new btGeneric6DofSpringConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(frameInA), TRANSFORM_USE(frameInB), useLinearReferenceFrameA);
	TRANSFORM_DEL(frameInA);
	TRANSFORM_DEL(frameInB);
}

Generic6DofSpringConstraint::Generic6DofSpringConstraint(RigidBody^ rigidBodyB, Matrix frameInB,
	bool useLinearReferenceFrameB)
	: Generic6DofConstraint(0)
{
	TRANSFORM_CONV(frameInB);
	UnmanagedPointer = new btGeneric6DofSpringConstraint(*(btRigidBody*)rigidBodyB->_native, TRANSFORM_USE(frameInB),
		useLinearReferenceFrameB);
	TRANSFORM_DEL(frameInB);
}

void Generic6DofSpringConstraint::EnableSpring(int index, bool onOff)
{
	Native->enableSpring(index, onOff);
}

void Generic6DofSpringConstraint::SetDamping(int index, btScalar damping)
{
	Native->setDamping(index, damping);
}

void Generic6DofSpringConstraint::SetEquilibriumPoint()
{
	Native->setEquilibriumPoint();
}

void Generic6DofSpringConstraint::SetEquilibriumPoint(int index)
{
	Native->setEquilibriumPoint(index);
}

void Generic6DofSpringConstraint::SetEquilibriumPoint(int index, btScalar val)
{
	Native->setEquilibriumPoint(index, val);
}

void Generic6DofSpringConstraint::SetStiffness(int index, btScalar stiffness)
{
	Native->setStiffness(index, stiffness);
}

#endif
