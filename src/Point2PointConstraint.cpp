#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "Point2PointConstraint.h"
#include "RigidBody.h"
/*
ConstraintSetting::ConstraintSetting()
{
	_native = new btConstraintSetting();
}
*/
ConstraintSetting::ConstraintSetting(btConstraintSetting* setting)
{
	_native = setting;
}

btScalar ConstraintSetting::Damping::get()
{
	return _native->m_damping;
}
void ConstraintSetting::Damping::set(btScalar value)
{
	_native->m_damping = value;
}

btScalar ConstraintSetting::ImpulseClamp::get()
{
	return _native->m_impulseClamp;
}
void ConstraintSetting::ImpulseClamp::set(btScalar value)
{
	_native->m_impulseClamp = value;
}

btScalar ConstraintSetting::Tau::get()
{
	return _native->m_tau;
}
void ConstraintSetting::Tau::set(btScalar value)
{
	_native->m_tau = value;
}


#define Native static_cast<btPoint2PointConstraint*>(_native)

Point2PointConstraint::Point2PointConstraint(btPoint2PointConstraint* constraint)
: TypedConstraint(constraint)
{
}

Point2PointConstraint::Point2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 pivotInA, Vector3 pivotInB)
: TypedConstraint(0)
{
	VECTOR3_DEF(pivotInA);
	VECTOR3_DEF(pivotInB);

	UnmanagedPointer = new btPoint2PointConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB));

	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);
}

Point2PointConstraint::Point2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA)
: TypedConstraint(0)
{
	VECTOR3_DEF(pivotInA);
	UnmanagedPointer = new btPoint2PointConstraint(*(btRigidBody*)rigidBodyA->_native, VECTOR3_USE(pivotInA));
	VECTOR3_DEL(pivotInA);
}

btScalar Point2PointConstraint::GetParam(int num, int axis)
{
	return Native->getParam(num, axis);
}

btScalar Point2PointConstraint::GetParam(int num)
{
	return Native->getParam(num);
}

void Point2PointConstraint::SetParam(int num, btScalar value, int axis)
{
	Native->setParam(num, value, axis);
}

void Point2PointConstraint::SetParam(int num, btScalar value)
{
	Native->setParam(num, value);
}

Vector3 Point2PointConstraint::PivotInA::get()
{
	return Math::BtVector3ToVector3(&Native->getPivotInA());
}

void Point2PointConstraint::PivotInA::set(Vector3 value)
{
	VECTOR3_DEF(value);
	Native->setPivotA(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

Vector3 Point2PointConstraint::PivotInB::get()
{
	return Math::BtVector3ToVector3(&Native->getPivotInB());
}

void Point2PointConstraint::PivotInB::set(Vector3 value)
{
	VECTOR3_DEF(value);
	Native->setPivotB(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

ConstraintSetting^ Point2PointConstraint::Setting::get()
{
	return gcnew ConstraintSetting(&Native->m_setting);
}

void Point2PointConstraint::Setting::set(ConstraintSetting^ setting)
{
	Native->m_setting = *setting->_native;
}

void Point2PointConstraint::UpdateRHS(btScalar timeStep)
{
	Native->updateRHS(timeStep);
}

#endif
