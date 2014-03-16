#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "RigidBody.h"
#include "TypedConstraint.h"

JointFeedback::JointFeedback(btJointFeedback* jointFeedback)
{
	_native = jointFeedback;
}

JointFeedback::JointFeedback()
{
	_native = new btJointFeedback();
}

JointFeedback::~JointFeedback()
{
	this->!JointFeedback();
}

JointFeedback::!JointFeedback()
{
	delete _native;
	_native = NULL;
}

Vector3 JointFeedback::AppliedForceBodyA::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedForceBodyA);
}
void JointFeedback::AppliedForceBodyA::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedForceBodyA);
}

Vector3 JointFeedback::AppliedForceBodyB::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedForceBodyB);
}
void JointFeedback::AppliedForceBodyB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedForceBodyB);
}

Vector3 JointFeedback::AppliedTorqueBodyA::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedTorqueBodyA);
}
void JointFeedback::AppliedTorqueBodyA::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedTorqueBodyA);
}

Vector3 JointFeedback::AppliedTorqueBodyB::get()
{
	return Math::BtVector3ToVector3(&_native->m_appliedTorqueBodyB);
}
void JointFeedback::AppliedTorqueBodyB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_appliedTorqueBodyB);
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
		if (_native->getUserConstraintId() != -1)
			VoidPtrToGCHandle(_native->getUserConstraintPtr()).Free();
		delete _native;
	}
	_native = NULL;
	
	OnDisposed(this, nullptr);
}

#ifndef DISABLE_SERIALIZE
int TypedConstraint::CalculateSerializeBufferSize()
{
	return _native->calculateSerializeBufferSize();
}
#endif

void TypedConstraint::EnableFeedback(bool needsFeedback)
{
	_native->enableFeedback(needsFeedback);
}

btScalar TypedConstraint::GetParam(ConstraintParam num, int axis)
{
	return _native->getParam((int)num, axis);
}

btScalar TypedConstraint::GetParam(ConstraintParam num)
{
	return _native->getParam((int)num);
}

void TypedConstraint::SetParam(ConstraintParam num, btScalar value, int axis)
{
	_native->setParam((int)num, value, axis);
}

void TypedConstraint::SetParam(ConstraintParam num, btScalar value)
{
	_native->setParam((int)num, value);
}

RigidBody^ TypedConstraint::FixedBody::get()
{
	return (RigidBody^)CollisionObject::GetManaged(&btTypedConstraint::getFixedBody());
}

TypedConstraint^ TypedConstraint::GetManaged(btTypedConstraint* typedConstraint)
{
	if (typedConstraint == 0)
		return nullptr;

	if (typedConstraint->getUserConstraintId() != -1)
		return static_cast<TypedConstraint^>(VoidPtrToGCHandle(typedConstraint->getUserConstraintPtr()).Target);

	return gcnew TypedConstraint(typedConstraint, true);
}

btScalar TypedConstraint::AppliedImpulse::get()
{
	if (NeedsFeedback == false)
		return 0;

	return _native->getAppliedImpulse();
}

btScalar TypedConstraint::BreakingImpulseThreshold::get()
{
	return _native->getBreakingImpulseThreshold();
}
void TypedConstraint::BreakingImpulseThreshold::set(btScalar value)
{
	_native->setBreakingImpulseThreshold(value);
}

TypedConstraintType TypedConstraint::ConstraintType::get()
{
	return (TypedConstraintType)_native->getConstraintType();
}

btScalar TypedConstraint::DebugDrawSize::get()
{
	return _native->getDbgDrawSize();
}
void TypedConstraint::DebugDrawSize::set(btScalar value)
{
	_native->setDbgDrawSize(value);
}

bool TypedConstraint::IsDisposed::get()
{
	return (_native == NULL);
}

bool TypedConstraint::IsEnabled::get()
{
	return _native->isEnabled();
}
void TypedConstraint::IsEnabled::set(bool value)
{
	_native->setEnabled(value);
}

JointFeedback^ TypedConstraint::JointFeedback::get()
{
	btJointFeedback* jointFeedback = _native->getJointFeedback();
	ReturnCachedObjectGcnewNullable(BulletSharp::JointFeedback, _jointFeedback, jointFeedback);
}
void TypedConstraint::JointFeedback::set(BulletSharp::JointFeedback^ value)
{
	_native->setJointFeedback(GetUnmanagedNullable(value));
	_jointFeedback = value;
}

bool TypedConstraint::NeedsFeedback::get()
{
	return _native->needsFeedback();
}
void TypedConstraint::NeedsFeedback::set(bool value)
{
	return _native->enableFeedback(value);
}

int TypedConstraint::OverrideNumSolverIterations::get()
{
	return _native->getOverrideNumSolverIterations();
}
void TypedConstraint::OverrideNumSolverIterations::set(int value)
{
	return _native->setOverrideNumSolverIterations(value);
}

RigidBody^ TypedConstraint::RigidBodyA::get()
{
	return (RigidBody^)CollisionObject::GetManaged(&_native->getRigidBodyA());
}

RigidBody^ TypedConstraint::RigidBodyB::get()
{
	return (RigidBody^)CollisionObject::GetManaged(&_native->getRigidBodyB());
}

int TypedConstraint::Uid::get()
{
	return _native->getUid();
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
	return _native->getUserConstraintType();
}
void TypedConstraint::UserConstraintType::set(int value)
{
	return _native->setUserConstraintType(value);
}

btTypedConstraint* TypedConstraint::UnmanagedPointer::get()
{
	return _native;
}
void TypedConstraint::UnmanagedPointer::set(btTypedConstraint* value)
{
	_native = value;

	if (_native->getUserConstraintId() == -1)
	{
		GCHandle handle = GCHandle::Alloc(this);
		void* obj = GCHandleToVoidPtr(handle);
		_native->setUserConstraintPtr(obj);
	}
}


#ifdef _BT_USE_CENTER_LIMIT_
#ifdef IN_PARALLELL_SOLVER
AngularLimit::AngularLimit()
{
	_angularLimit = new btAngularLimit();
}
#endif
#endif

#endif
