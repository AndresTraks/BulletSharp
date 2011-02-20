#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "TypedConstraint.h"

TypedConstraint::TypedConstraint(btTypedConstraint* typedConstraint, bool doesNotOwnObject)
{
	_doesNotOwnObject = doesNotOwnObject;

	if (typedConstraint)
		UnmanagedPointer = typedConstraint;
}

TypedConstraint::TypedConstraint(btTypedConstraint* typedConstraint)
{
	if (typedConstraint)
		UnmanagedPointer = typedConstraint;
}

TypedConstraint::~TypedConstraint()
{
	this->!TypedConstraint();
}

TypedConstraint::!TypedConstraint()
{
	if (this->IsDisposed)
		return;
	
	OnDisposing(this, nullptr);
	
	if (_doesNotOwnObject == false)
	{
		void* userObj = _typedConstraint->getUserConstraintPtr();
		if (userObj != (void*)-1)
			VoidPtrToGCHandle(userObj).Free();
		delete _typedConstraint;
	}
	_typedConstraint = NULL;
	
	OnDisposed(this, nullptr);
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

TypedConstraint^ TypedConstraint::Upcast(btTypedConstraint* typedConstraint)
{
	if (typedConstraint == 0)
		return nullptr;

	void* userObj = typedConstraint->getUserConstraintPtr();
	if (userObj)
		return static_cast<TypedConstraint^>(VoidPtrToGCHandle(userObj).Target);

	return gcnew TypedConstraint(typedConstraint, true);
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
	return (RigidBody^)CollisionObject::Upcast(&UnmanagedPointer->getRigidBodyA());
}

RigidBody^ TypedConstraint::RigidBodyB::get()
{
	return (RigidBody^)CollisionObject::Upcast(&UnmanagedPointer->getRigidBodyB());
}

int TypedConstraint::Uid::get()
{
	return UnmanagedPointer->getUid();
}

Object^ TypedConstraint::UserObject::get()
{
	return _userObject;
}
void TypedConstraint::UserObject::set(Object^ value)
{
	_userObject = value;
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

	if (_typedConstraint->getUserConstraintPtr() == (void*)-1)
	{
		GCHandle handle = GCHandle::Alloc(this);
		void* obj = GCHandleToVoidPtr(handle);
		_typedConstraint->setUserConstraintPtr(obj);
	}
}


#ifdef _BT_USE_CENTER_LIMIT_
#ifdef IN_PARALLELL_SOLVER
AngularLimit::AngularLimit()
{
	_angularLimit = new btAngularLimit();
}

btAngularLimit* AngularLimit::UnmanagedPointer::get()
{
	return _angularLimit;
}
void AngularLimit::UnmanagedPointer::set(btAngularLimit* value)
{
	_angularLimit = value;
}
#endif
#endif

#endif
