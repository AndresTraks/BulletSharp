#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "Point2PointConstraint.h"
#include "RigidBody.h"

ConstraintSetting::ConstraintSetting(btConstraintSetting* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

ConstraintSetting::~ConstraintSetting()
{
	this->!ConstraintSetting();
}

ConstraintSetting::!ConstraintSetting()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

ConstraintSetting::ConstraintSetting()
{
	_native = new btConstraintSetting();
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

Point2PointConstraint::Point2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 pivotInA, Vector3 pivotInB)
	: TypedConstraint(0)
{
	VECTOR3_CONV(pivotInA);
	VECTOR3_CONV(pivotInB);
	UnmanagedPointer = new btPoint2PointConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB));
	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

Point2PointConstraint::Point2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA)
	: TypedConstraint(0)
{
	VECTOR3_CONV(pivotInA);
	UnmanagedPointer = new btPoint2PointConstraint(*(btRigidBody*)rigidBodyA->_native, VECTOR3_USE(pivotInA));
	VECTOR3_DEL(pivotInA);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = GetFixedBody();
}

void Point2PointConstraint::GetInfo1NonVirtual(ConstraintInfo1^ info)
{
	Native->getInfo1NonVirtual(info->_native);
}

void Point2PointConstraint::GetInfo2NonVirtual(ConstraintInfo2^ info, Matrix body0Trans,
	Matrix body1Trans)
{
	TRANSFORM_CONV(body0Trans);
	TRANSFORM_CONV(body1Trans);
	Native->getInfo2NonVirtual(info->_native, TRANSFORM_USE(body0Trans), TRANSFORM_USE(body1Trans));
	TRANSFORM_DEL(body0Trans);
	TRANSFORM_DEL(body1Trans);
}

void Point2PointConstraint::UpdateRhs(btScalar timeStep)
{
	Native->updateRHS(timeStep);
}

Point2PointFlags Point2PointConstraint::Flags::get()
{
	return (Point2PointFlags) Native->getFlags();
}

Vector3 Point2PointConstraint::PivotInA::get()
{
	return Math::BtVector3ToVector3(&Native->getPivotInA());
}
void Point2PointConstraint::PivotInA::set(Vector3 pivotA)
{
	VECTOR3_CONV(pivotA);
	Native->setPivotA(VECTOR3_USE(pivotA));
	VECTOR3_DEL(pivotA);
}

Vector3 Point2PointConstraint::PivotInB::get()
{
	return Math::BtVector3ToVector3(&Native->getPivotInB());
}
void Point2PointConstraint::PivotInB::set(Vector3 pivotB)
{
	VECTOR3_CONV(pivotB);
	Native->setPivotB(VECTOR3_USE(pivotB));
	VECTOR3_DEL(pivotB);
}

ConstraintSetting^ Point2PointConstraint::Setting::get()
{
	return gcnew ConstraintSetting(&Native->m_setting, true);
}
void Point2PointConstraint::Setting::set(ConstraintSetting^ value)
{
	Native->m_setting = *value->_native;
}

#endif
