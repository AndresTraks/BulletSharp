#include "StdAfx.h"

#include "Generic6DofSpringConstraint.h"

Generic6DofSpringConstraint::Generic6DofSpringConstraint(btGeneric6DofSpringConstraint* constraint)
: Generic6DofConstraint(constraint)
{
}

Generic6DofSpringConstraint::Generic6DofSpringConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Matrix frameInA, Matrix frameInB, bool useReferenceFrameA)
: Generic6DofConstraint(new btGeneric6DofSpringConstraint(*rbA->UnmanagedPointer,
	*rbB->UnmanagedPointer, *Math::MatrixToBtTransform(frameInA),
	*Math::MatrixToBtTransform(frameInB), useReferenceFrameA))
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;
}

void Generic6DofSpringConstraint::EnableSpring(int index, bool onOff)
{
	UnmanagedPointer->enableSpring(index, onOff);
}

void Generic6DofSpringConstraint::SetDamping(int index, btScalar damping)
{
	UnmanagedPointer->setDamping(index, damping);
}

void Generic6DofSpringConstraint::SetEquilibriumPoint(int index)
{
	UnmanagedPointer->setEquilibriumPoint(index);
}

void Generic6DofSpringConstraint::SetEquilibriumPoint()
{
	UnmanagedPointer->setEquilibriumPoint();
}

void Generic6DofSpringConstraint::SetStiffness(int index, btScalar stiffness)
{
	UnmanagedPointer->setStiffness(index, stiffness);
}

btGeneric6DofSpringConstraint* Generic6DofSpringConstraint::UnmanagedPointer::get()
{
	return (btGeneric6DofSpringConstraint*)Generic6DofConstraint::UnmanagedPointer;
}
