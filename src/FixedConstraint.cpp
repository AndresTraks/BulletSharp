#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "FixedConstraint.h"
#include "RigidBody.h"

#define Native static_cast<btFixedConstraint*>(_native)

FixedConstraint::FixedConstraint(btFixedConstraint* constraint)
: TypedConstraint(constraint)
{
}

FixedConstraint::FixedConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB)
: TypedConstraint(0)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	UnmanagedPointer = new btFixedConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*frameInATemp, *frameInBTemp);

	ALIGNED_FREE(frameInATemp);
	ALIGNED_FREE(frameInBTemp);
}

#endif
