#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "FixedConstraint.h"
#include "RigidBody.h"

FixedConstraint::FixedConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA,
	Matrix frameInB)
	: Generic6DofSpring2Constraint(0)
{
	TRANSFORM_CONV(frameInA);
	TRANSFORM_CONV(frameInB);
	UnmanagedPointer = new btFixedConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(frameInA), TRANSFORM_USE(frameInB));
	TRANSFORM_DEL(frameInA);
	TRANSFORM_DEL(frameInB);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

#endif
