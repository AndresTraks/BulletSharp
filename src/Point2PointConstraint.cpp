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

Point2PointConstraint::Point2PointConstraint(btPoint2PointConstraint* native)
	: TypedConstraint(native)
{
}

Point2PointConstraint::Point2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 pivotInA,
	Vector3 pivotInB)
	: TypedConstraint(0)
{
	VECTOR3_DEF(pivotInA);
	VECTOR3_DEF(pivotInB);
	UnmanagedPointer = new btPoint2PointConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
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

/*
void Point2PointConstraint::GetInfo1NonVirtual(btConstraintInfo1^ info)
{
	Native->getInfo1NonVirtual(info->_native);
}

void Point2PointConstraint::GetInfo2NonVirtual(btConstraintInfo2^ info, Matrix body0_trans,
	Matrix body1_trans)
{
	TRANSFORM_CONV(body0_trans);
	TRANSFORM_CONV(body1_trans);
	Native->getInfo2NonVirtual(info->_native, TRANSFORM_USE(body0_trans), TRANSFORM_USE(body1_trans));
	TRANSFORM_DEL(body0_trans);
	TRANSFORM_DEL(body1_trans);
}
*/

void Point2PointConstraint::UpdateRhs(btScalar timeStep)
{
	Native->updateRHS(timeStep);
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

#endif
