#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "TypedConstraint.h"

JointFeedback::JointFeedback(btJointFeedback* jointFeedback)
{
	_unmanaged = jointFeedback;
}

JointFeedback::JointFeedback()
{
	_unmanaged = new btJointFeedback();
}

JointFeedback::~JointFeedback()
{
	this->!JointFeedback();
}

JointFeedback::!JointFeedback()
{
	delete _unmanaged;
	_unmanaged = NULL;
}

Vector3 JointFeedback::AppliedForceBodyA::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->m_appliedForceBodyA);
}
void JointFeedback::AppliedForceBodyA::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_unmanaged->m_appliedForceBodyA);
}

Vector3 JointFeedback::AppliedForceBodyB::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->m_appliedForceBodyB);
}
void JointFeedback::AppliedForceBodyB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_unmanaged->m_appliedForceBodyB);
}

Vector3 JointFeedback::AppliedTorqueBodyA::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->m_appliedTorqueBodyA);
}
void JointFeedback::AppliedTorqueBodyA::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_unmanaged->m_appliedTorqueBodyA);
}

Vector3 JointFeedback::AppliedTorqueBodyB::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->m_appliedTorqueBodyB);
}
void JointFeedback::AppliedTorqueBodyB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_unmanaged->m_appliedTorqueBodyB);
}


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

RigidBody^ TypedConstraint::FixedBody::get()
{
	return (RigidBody^)CollisionObject::GetManaged(&btTypedConstraint::getFixedBody());
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

btScalar TypedConstraint::BreakingImpulseThreshold::get()
{
	return _typedConstraint->getBreakingImpulseThreshold();
}
void TypedConstraint::BreakingImpulseThreshold::set(btScalar value)
{
	_typedConstraint->setBreakingImpulseThreshold(value);
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

bool TypedConstraint::IsDisposed::get()
{
	return (_typedConstraint == NULL);
}

bool TypedConstraint::IsEnabled::get()
{
	return _typedConstraint->isEnabled();
}
void TypedConstraint::IsEnabled::set(bool value)
{
	_typedConstraint->setEnabled(value);
}

JointFeedback^ TypedConstraint::JointFeedback::get()
{
	btJointFeedback* jointFeedback = _typedConstraint->getJointFeedback();
	ReturnCachedObjectGcnewNullable(BulletSharp::JointFeedback, _jointFeedback, jointFeedback);
}
void TypedConstraint::JointFeedback::set(BulletSharp::JointFeedback^ value)
{
	_typedConstraint->setJointFeedback(GetUnmanagedNullable(value));
	_jointFeedback = value;
}

bool TypedConstraint::NeedsFeedback::get()
{
	return UnmanagedPointer->needsFeedback();
}

int TypedConstraint::OverrideNumSolverIterations::get()
{
	return UnmanagedPointer->getOverrideNumSolverIterations();
}
void TypedConstraint::OverrideNumSolverIterations::set(int value)
{
	return UnmanagedPointer->setOverrideNumSolverIterations(value);
}

RigidBody^ TypedConstraint::RigidBodyA::get()
{
	return (RigidBody^)CollisionObject::GetManaged(&UnmanagedPointer->getRigidBodyA());
}

RigidBody^ TypedConstraint::RigidBodyB::get()
{
	return (RigidBody^)CollisionObject::GetManaged(&UnmanagedPointer->getRigidBodyB());
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
