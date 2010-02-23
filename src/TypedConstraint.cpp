#include "StdAfx.h"

#include "TypedConstraint.h"

TypedConstraint::TypedConstraint(btTypedConstraint* typedConstraint)
{
	_typedConstraint = typedConstraint;
}

int TypedConstraint::CalculateSerializeBufferSize()
{
	return _typedConstraint->calculateSerializeBufferSize();
}

void TypedConstraint::EnableFeedback(bool needsFeedback)
{
	_typedConstraint->enableFeedback(needsFeedback);
}

btScalar TypedConstraint::GetAppliedImpulse()
{
	return _typedConstraint->getAppliedImpulse();
}

btScalar TypedConstraint::GetParam(int num, int axis)
{
	return UnmanagedPointer->getParam(num, axis);
}

btScalar TypedConstraint::GetParam(int num)
{
	return UnmanagedPointer->getParam(num);
}

void TypedConstraint::SetParam(int num, btScalar value, int axis)
{
	UnmanagedPointer->setParam(num, value, axis);
}

void TypedConstraint::SetParam(int num, btScalar value)
{
	UnmanagedPointer->setParam(num, value);
}

TypedConstraintType TypedConstraint::ConstraintType::get()
{
	return (TypedConstraintType)_typedConstraint->getConstraintType();
}

btScalar TypedConstraint::DebugDrawSize::get()
{
	return _typedConstraint->getDbgDrawSize();
}

void TypedConstraint::DebugDrawSize::set(btScalar value)
{
	_typedConstraint->setDbgDrawSize(value);
}

RigidBody^ TypedConstraint::RigidBodyA::get()
{
	return rigidBodyA;
}

RigidBody^ TypedConstraint::RigidBodyB::get()
{
	return rigidBodyB;
}

void TypedConstraint::RigidBodyA::set(RigidBody^ value)
{
	rigidBodyA = value;
}

void TypedConstraint::RigidBodyB::set(RigidBody^ value)
{
	rigidBodyB = value;
}

btTypedConstraint* TypedConstraint::UnmanagedPointer::get()
{
	return _typedConstraint;
}
void TypedConstraint::UnmanagedPointer::set(btTypedConstraint* value)
{
	_typedConstraint = value;
}
