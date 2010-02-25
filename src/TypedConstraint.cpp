#include "StdAfx.h"

#include "TypedConstraint.h"

TypedConstraint::TypedConstraint(btTypedConstraint* typedConstraint)
{
	_typedConstraint = typedConstraint;
}

TypedConstraint::~TypedConstraint()
{
	this->!TypedConstraint();
}

TypedConstraint::!TypedConstraint()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_typedConstraint = NULL;
	
	OnDisposed( this, nullptr );
}

bool TypedConstraint::IsDisposed::get()
{
	return (_typedConstraint == NULL);
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

btScalar TypedConstraint::GetParam(ConstraintParams num, int axis)
{
	return UnmanagedPointer->getParam((int)num, axis);
}

btScalar TypedConstraint::GetParam(ConstraintParams num)
{
	return UnmanagedPointer->getParam((int)num);
}

void TypedConstraint::SetParam(ConstraintParams num, btScalar value, int axis)
{
	UnmanagedPointer->setParam((int)num, value, axis);
}

void TypedConstraint::SetParam(ConstraintParams num, btScalar value)
{
	UnmanagedPointer->setParam((int)num, value);
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
