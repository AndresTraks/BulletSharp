#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "Generic6DofSpringConstraint.h"
#include "RigidBody.h"

#define Native static_cast<btGeneric6DofSpringConstraint*>(_native)

Generic6DofSpringConstraint::Generic6DofSpringConstraint(btGeneric6DofSpringConstraint* constraint)
: Generic6DofConstraint(constraint)
{
}

Generic6DofSpringConstraint::Generic6DofSpringConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Matrix frameInA, Matrix frameInB, bool useReferenceFrameA)
: Generic6DofConstraint(0)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	UnmanagedPointer = new btGeneric6DofSpringConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*frameInATemp, *frameInBTemp, useReferenceFrameA);

	ALIGNED_FREE(frameInATemp);
	ALIGNED_FREE(frameInBTemp);
}

void Generic6DofSpringConstraint::EnableSpring(int index, bool onOff)
{
	Native->enableSpring(index, onOff);
}

void Generic6DofSpringConstraint::SetDamping(int index, btScalar damping)
{
	Native->setDamping(index, damping);
}

void Generic6DofSpringConstraint::SetEquilibriumPoint(int index, btScalar val)
{
	Native->setEquilibriumPoint(index, val);
}

void Generic6DofSpringConstraint::SetEquilibriumPoint(int index)
{
	Native->setEquilibriumPoint(index);
}

void Generic6DofSpringConstraint::SetEquilibriumPoint()
{
	Native->setEquilibriumPoint();
}

void Generic6DofSpringConstraint::SetStiffness(int index, btScalar stiffness)
{
	Native->setStiffness(index, stiffness);
}

#endif
