#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
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

#ifndef DISABLE_SERIALIZE
int TypedConstraint::CalculateSerializeBufferSize()
{
	return _typedConstraint->calculateSerializeBufferSize();
}
#endif

void TypedConstraint::EnableFeedback(bool needsFeedback)
{
	_typedConstraint->enableFeedback(needsFeedback);
}

btScalar TypedConstraint::GetParam(ConstraintParam num, int axis)
{
	return UnmanagedPointer->getParam((int)num, axis);
}

btScalar TypedConstraint::GetParam(ConstraintParam num)
{
	return UnmanagedPointer->getParam((int)num);
}

void TypedConstraint::SetParam(ConstraintParam num, btScalar value, int axis)
{
	UnmanagedPointer->setParam((int)num, value, axis);
}

void TypedConstraint::SetParam(ConstraintParam num, btScalar value)
{
	UnmanagedPointer->setParam((int)num, value);
}

btScalar TypedConstraint::AppliedImpulse::get()
{
	if (NeedsFeedback == false)
		return 0;

	return _typedConstraint->getAppliedImpulse();
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

bool TypedConstraint::NeedsFeedback::get()
{
	return UnmanagedPointer->needsFeedback();
}

RigidBody^ TypedConstraint::RigidBodyA::get()
{
	return gcnew RigidBody(&UnmanagedPointer->getRigidBodyA());
}

RigidBody^ TypedConstraint::RigidBodyB::get()
{
	return gcnew RigidBody(&UnmanagedPointer->getRigidBodyB());
}

int TypedConstraint::Uid::get()
{
	return UnmanagedPointer->getUid();
}

int TypedConstraint::UserConstraintId::get()
{
	return UnmanagedPointer->getUserConstraintId();
}
void TypedConstraint::UserConstraintId::set(int value)
{
	return UnmanagedPointer->setUserConstraintId(value);
}

int TypedConstraint::UserConstraintType::get()
{
	return UnmanagedPointer->getUserConstraintType();
}
void TypedConstraint::UserConstraintType::set(int value)
{
	return UnmanagedPointer->setUserConstraintType(value);
}

btTypedConstraint* TypedConstraint::UnmanagedPointer::get()
{
	return _typedConstraint;
}
void TypedConstraint::UnmanagedPointer::set(btTypedConstraint* value)
{
	_typedConstraint = value;
}

#endif
