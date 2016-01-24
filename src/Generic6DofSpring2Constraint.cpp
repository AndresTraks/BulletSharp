#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "Collections.h"
#include "Generic6DofSpring2Constraint.h"
#include "RigidBody.h"

RotationalLimitMotor2::RotationalLimitMotor2(btRotationalLimitMotor2* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

RotationalLimitMotor2::~RotationalLimitMotor2()
{
	this->!RotationalLimitMotor2();
}

RotationalLimitMotor2::!RotationalLimitMotor2()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

RotationalLimitMotor2::RotationalLimitMotor2()
{
	_native = new btRotationalLimitMotor2();
}

RotationalLimitMotor2::RotationalLimitMotor2(RotationalLimitMotor2^ limitMotor)
{
	_native = new btRotationalLimitMotor2(*limitMotor->_native);
}

void RotationalLimitMotor2::TestLimitValue(btScalar testValue)
{
	_native->testLimitValue(testValue);
}

btScalar RotationalLimitMotor2::Bounce::get()
{
	return _native->m_bounce;
}
void RotationalLimitMotor2::Bounce::set(btScalar value)
{
	_native->m_bounce = value;
}

int RotationalLimitMotor2::CurrentLimit::get()
{
	return _native->m_currentLimit;
}
void RotationalLimitMotor2::CurrentLimit::set(int value)
{
	_native->m_currentLimit = value;
}

btScalar RotationalLimitMotor2::CurrentLimitError::get()
{
	return _native->m_currentLimitError;
}
void RotationalLimitMotor2::CurrentLimitError::set(btScalar value)
{
	_native->m_currentLimitError = value;
}

btScalar RotationalLimitMotor2::CurrentLimitErrorHi::get()
{
	return _native->m_currentLimitErrorHi;
}
void RotationalLimitMotor2::CurrentLimitErrorHi::set(btScalar value)
{
	_native->m_currentLimitErrorHi = value;
}

btScalar RotationalLimitMotor2::CurrentPosition::get()
{
	return _native->m_currentPosition;
}
void RotationalLimitMotor2::CurrentPosition::set(btScalar value)
{
	_native->m_currentPosition = value;
}

bool RotationalLimitMotor2::EnableMotor::get()
{
	return _native->m_enableMotor;
}
void RotationalLimitMotor2::EnableMotor::set(bool value)
{
	_native->m_enableMotor = value;
}

bool RotationalLimitMotor2::EnableSpring::get()
{
	return _native->m_enableSpring;
}
void RotationalLimitMotor2::EnableSpring::set(bool value)
{
	_native->m_enableSpring = value;
}

btScalar RotationalLimitMotor2::EquilibriumPoint::get()
{
	return _native->m_equilibriumPoint;
}
void RotationalLimitMotor2::EquilibriumPoint::set(btScalar value)
{
	_native->m_equilibriumPoint = value;
}

btScalar RotationalLimitMotor2::HiLimit::get()
{
	return _native->m_hiLimit;
}
void RotationalLimitMotor2::HiLimit::set(btScalar value)
{
	_native->m_hiLimit = value;
}

bool RotationalLimitMotor2::IsLimited::get()
{
	return _native->isLimited();
}

btScalar RotationalLimitMotor2::LoLimit::get()
{
	return _native->m_loLimit;
}
void RotationalLimitMotor2::LoLimit::set(btScalar value)
{
	_native->m_loLimit = value;
}

btScalar RotationalLimitMotor2::MaxMotorForce::get()
{
	return _native->m_maxMotorForce;
}
void RotationalLimitMotor2::MaxMotorForce::set(btScalar value)
{
	_native->m_maxMotorForce = value;
}

btScalar RotationalLimitMotor2::MotorCfm::get()
{
	return _native->m_motorCFM;
}
void RotationalLimitMotor2::MotorCfm::set(btScalar value)
{
	_native->m_motorCFM = value;
}

btScalar RotationalLimitMotor2::MotorErp::get()
{
	return _native->m_motorERP;
}
void RotationalLimitMotor2::MotorErp::set(btScalar value)
{
	_native->m_motorERP = value;
}

bool RotationalLimitMotor2::ServoMotor::get()
{
	return _native->m_servoMotor;
}
void RotationalLimitMotor2::ServoMotor::set(bool value)
{
	_native->m_servoMotor = value;
}

btScalar RotationalLimitMotor2::ServoTarget::get()
{
	return _native->m_servoTarget;
}
void RotationalLimitMotor2::ServoTarget::set(btScalar value)
{
	_native->m_servoTarget = value;
}

btScalar RotationalLimitMotor2::SpringDamping::get()
{
	return _native->m_springDamping;
}
void RotationalLimitMotor2::SpringDamping::set(btScalar value)
{
	_native->m_springDamping = value;
}

bool RotationalLimitMotor2::SpringDampingLimited::get()
{
	return _native->m_springDampingLimited;
}
void RotationalLimitMotor2::SpringDampingLimited::set(bool value)
{
	_native->m_springDampingLimited = value;
}

btScalar RotationalLimitMotor2::SpringStiffness::get()
{
	return _native->m_springStiffness;
}
void RotationalLimitMotor2::SpringStiffness::set(btScalar value)
{
	_native->m_springStiffness = value;
}

bool RotationalLimitMotor2::SpringStiffnessLimited::get()
{
	return _native->m_springStiffnessLimited;
}
void RotationalLimitMotor2::SpringStiffnessLimited::set(bool value)
{
	_native->m_springStiffnessLimited = value;
}

btScalar RotationalLimitMotor2::StopCfm::get()
{
	return _native->m_stopCFM;
}
void RotationalLimitMotor2::StopCfm::set(btScalar value)
{
	_native->m_stopCFM = value;
}

btScalar RotationalLimitMotor2::StopErp::get()
{
	return _native->m_stopERP;
}
void RotationalLimitMotor2::StopErp::set(btScalar value)
{
	_native->m_stopERP = value;
}

btScalar RotationalLimitMotor2::TargetVelocity::get()
{
	return _native->m_targetVelocity;
}
void RotationalLimitMotor2::TargetVelocity::set(btScalar value)
{
	_native->m_targetVelocity = value;
}


TranslationalLimitMotor2::TranslationalLimitMotor2(btTranslationalLimitMotor2* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

TranslationalLimitMotor2::~TranslationalLimitMotor2()
{
	this->!TranslationalLimitMotor2();
}

TranslationalLimitMotor2::!TranslationalLimitMotor2()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

TranslationalLimitMotor2::TranslationalLimitMotor2()
{
	_native = new btTranslationalLimitMotor2();
}

TranslationalLimitMotor2::TranslationalLimitMotor2(TranslationalLimitMotor2^ other)
{
	_native = new btTranslationalLimitMotor2(*other->_native);
}

bool TranslationalLimitMotor2::IsLimited(int limitIndex)
{
	return _native->isLimited(limitIndex);
}

void TranslationalLimitMotor2::TestLimitValue(int limitIndex, btScalar testValue)
{
	_native->testLimitValue(limitIndex, testValue);
}

Vector3 TranslationalLimitMotor2::Bounce::get()
{
	return Math::BtVector3ToVector3(&_native->m_bounce);
}
void TranslationalLimitMotor2::Bounce::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_bounce);
}

IntArray^ TranslationalLimitMotor2::CurrentLimit::get()
{
	return gcnew IntArray(_native->m_currentLimit, 3);
}

Vector3 TranslationalLimitMotor2::CurrentLimitError::get()
{
	return Math::BtVector3ToVector3(&_native->m_currentLimitError);
}
void TranslationalLimitMotor2::CurrentLimitError::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_currentLimitError);
}

Vector3 TranslationalLimitMotor2::CurrentLimitErrorHi::get()
{
	return Math::BtVector3ToVector3(&_native->m_currentLimitErrorHi);
}
void TranslationalLimitMotor2::CurrentLimitErrorHi::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_currentLimitErrorHi);
}

Vector3 TranslationalLimitMotor2::CurrentLinearDiff::get()
{
	return Math::BtVector3ToVector3(&_native->m_currentLinearDiff);
}
void TranslationalLimitMotor2::CurrentLinearDiff::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_currentLinearDiff);
}

BoolArray^ TranslationalLimitMotor2::EnableMotor::get()
{
	return gcnew BoolArray(_native->m_enableMotor, 3);
}

BoolArray^ TranslationalLimitMotor2::EnableSpring::get()
{
	return gcnew BoolArray(_native->m_enableSpring, 3);
}

Vector3 TranslationalLimitMotor2::EquilibriumPoint::get()
{
	return Math::BtVector3ToVector3(&_native->m_equilibriumPoint);
}
void TranslationalLimitMotor2::EquilibriumPoint::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_equilibriumPoint);
}

Vector3 TranslationalLimitMotor2::LowerLimit::get()
{
	return Math::BtVector3ToVector3(&_native->m_lowerLimit);
}
void TranslationalLimitMotor2::LowerLimit::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_lowerLimit);
}

Vector3 TranslationalLimitMotor2::MaxMotorForce::get()
{
	return Math::BtVector3ToVector3(&_native->m_maxMotorForce);
}
void TranslationalLimitMotor2::MaxMotorForce::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_maxMotorForce);
}

Vector3 TranslationalLimitMotor2::MotorCfm::get()
{
	return Math::BtVector3ToVector3(&_native->m_motorCFM);
}
void TranslationalLimitMotor2::MotorCfm::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_motorCFM);
}

Vector3 TranslationalLimitMotor2::MotorErp::get()
{
	return Math::BtVector3ToVector3(&_native->m_motorERP);
}
void TranslationalLimitMotor2::MotorErp::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_motorERP);
}

BoolArray^ TranslationalLimitMotor2::ServoMotor::get()
{
	return gcnew BoolArray(_native->m_servoMotor, 3);
}

Vector3 TranslationalLimitMotor2::ServoTarget::get()
{
	return Math::BtVector3ToVector3(&_native->m_servoTarget);
}
void TranslationalLimitMotor2::ServoTarget::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_servoTarget);
}

Vector3 TranslationalLimitMotor2::SpringDamping::get()
{
	return Math::BtVector3ToVector3(&_native->m_springDamping);
}
void TranslationalLimitMotor2::SpringDamping::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_springDamping);
}

BoolArray^ TranslationalLimitMotor2::SpringDampingLimited::get()
{
	return gcnew BoolArray(_native->m_springDampingLimited, 3);
}

Vector3 TranslationalLimitMotor2::SpringStiffness::get()
{
	return Math::BtVector3ToVector3(&_native->m_springStiffness);
}
void TranslationalLimitMotor2::SpringStiffness::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_springStiffness);
}

BoolArray^ TranslationalLimitMotor2::SpringStiffnessLimited::get()
{
	return gcnew BoolArray(_native->m_springStiffnessLimited, 3);
}

Vector3 TranslationalLimitMotor2::StopCfm::get()
{
	return Math::BtVector3ToVector3(&_native->m_stopCFM);
}
void TranslationalLimitMotor2::StopCfm::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_stopCFM);
}

Vector3 TranslationalLimitMotor2::StopErp::get()
{
	return Math::BtVector3ToVector3(&_native->m_stopERP);
}
void TranslationalLimitMotor2::StopErp::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_stopERP);
}

Vector3 TranslationalLimitMotor2::TargetVelocity::get()
{
	return Math::BtVector3ToVector3(&_native->m_targetVelocity);
}
void TranslationalLimitMotor2::TargetVelocity::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_targetVelocity);
}

Vector3 TranslationalLimitMotor2::UpperLimit::get()
{
	return Math::BtVector3ToVector3(&_native->m_upperLimit);
}
void TranslationalLimitMotor2::UpperLimit::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_upperLimit);
}


#define Native static_cast<btGeneric6DofSpring2Constraint*>(_native)

Generic6DofSpring2Constraint::Generic6DofSpring2Constraint(btGeneric6DofSpring2Constraint* native)
	: TypedConstraint(native)
{
	_angularLimits = gcnew array<RotationalLimitMotor2^>(3);
}

Generic6DofSpring2Constraint::Generic6DofSpring2Constraint(RigidBody^ rigidBodyA,
	RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, BulletSharp::RotateOrder rotOrder)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(frameInA);
	TRANSFORM_CONV(frameInB);
	UnmanagedPointer = new btGeneric6DofSpring2Constraint(*(btRigidBody*)rigidBodyA->_native,
		*(btRigidBody*)rigidBodyB->_native, TRANSFORM_USE(frameInA), TRANSFORM_USE(frameInB),
		(::RotateOrder)rotOrder);
	TRANSFORM_DEL(frameInA);
	TRANSFORM_DEL(frameInB);

	_angularLimits = gcnew array<RotationalLimitMotor2^>(3);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

Generic6DofSpring2Constraint::Generic6DofSpring2Constraint(RigidBody^ rigidBodyA,
	RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(frameInA);
	TRANSFORM_CONV(frameInB);
	UnmanagedPointer = new btGeneric6DofSpring2Constraint(*(btRigidBody*)rigidBodyA->_native,
		*(btRigidBody*)rigidBodyB->_native, TRANSFORM_USE(frameInA), TRANSFORM_USE(frameInB));
	TRANSFORM_DEL(frameInA);
	TRANSFORM_DEL(frameInB);

	_angularLimits = gcnew array<RotationalLimitMotor2^>(3);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

Generic6DofSpring2Constraint::Generic6DofSpring2Constraint(RigidBody^ rigidBodyB,
	Matrix frameInB, BulletSharp::RotateOrder rotOrder)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(frameInB);
	UnmanagedPointer = new btGeneric6DofSpring2Constraint(*(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(frameInB), (::RotateOrder)rotOrder);
	TRANSFORM_DEL(frameInB);

	_angularLimits = gcnew array<RotationalLimitMotor2^>(3);
	_rigidBodyA = GetFixedBody();
	_rigidBodyB = rigidBodyB;
}

Generic6DofSpring2Constraint::Generic6DofSpring2Constraint(RigidBody^ rigidBodyB,
	Matrix frameInB)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(frameInB);
	UnmanagedPointer = new btGeneric6DofSpring2Constraint(*(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(frameInB));
	TRANSFORM_DEL(frameInB);

	_angularLimits = gcnew array<RotationalLimitMotor2^>(3);
	_rigidBodyA = GetFixedBody();
	_rigidBodyB = rigidBodyB;
}

void Generic6DofSpring2Constraint::CalculateTransforms(Matrix transA, Matrix transB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	Native->calculateTransforms(TRANSFORM_USE(transA), TRANSFORM_USE(transB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
}

void Generic6DofSpring2Constraint::CalculateTransforms()
{
	Native->calculateTransforms();
}

void Generic6DofSpring2Constraint::EnableMotor(int index, bool onOff)
{
	Native->enableMotor(index, onOff);
}

void Generic6DofSpring2Constraint::EnableSpring(int index, bool onOff)
{
	Native->enableSpring(index, onOff);
}

btScalar Generic6DofSpring2Constraint::GetAngle(int axisIndex)
{
	return Native->getAngle(axisIndex);
}

#pragma managed(push, off)
void Generic6DofSpring2Constraint_GetAxis(btGeneric6DofSpring2Constraint* constraint, int axis_index, btVector3* axis)
{
	axis = &constraint->getAxis(axis_index);
}
#pragma managed(pop)
Vector3 Generic6DofSpring2Constraint::GetAxis(int axisIndex)
{
	btVector3* axisTemp = ALIGNED_NEW(btVector3);
	Generic6DofSpring2Constraint_GetAxis(Native, axisIndex, axisTemp);
	Vector3 ret = Math::BtVector3ToVector3(axisTemp);
	ALIGNED_FREE(axisTemp);
	return ret;
}

btScalar Generic6DofSpring2Constraint::GetRelativePivotPosition(int axisIndex)
{
	return Native->getRelativePivotPosition(axisIndex);
}

RotationalLimitMotor2^ Generic6DofSpring2Constraint::GetRotationalLimitMotor(int index)
{
	if (_angularLimits[index] == nullptr)
    {
        _angularLimits[index] = gcnew RotationalLimitMotor2(Native->getRotationalLimitMotor(index), true);
    }
    return _angularLimits[index];
}

bool Generic6DofSpring2Constraint::IsLimited(int limitIndex)
{
	return Native->isLimited(limitIndex);
}

void Generic6DofSpring2Constraint::SetAxis(Vector3 axis1, Vector3 axis2)
{
	VECTOR3_CONV(axis1);
	VECTOR3_CONV(axis2);
	Native->setAxis(VECTOR3_USE(axis1), VECTOR3_USE(axis2));
	VECTOR3_DEL(axis1);
	VECTOR3_DEL(axis2);
}

void Generic6DofSpring2Constraint::SetBounce(int index, btScalar bounce)
{
	Native->setBounce(index, bounce);
}

void Generic6DofSpring2Constraint::SetDamping(int index, btScalar damping, bool limitIfNeeded)
{
	Native->setDamping(index, damping, limitIfNeeded);
}

void Generic6DofSpring2Constraint::SetDamping(int index, btScalar damping)
{
	Native->setDamping(index, damping);
}

void Generic6DofSpring2Constraint::SetEquilibriumPoint()
{
	Native->setEquilibriumPoint();
}

void Generic6DofSpring2Constraint::SetEquilibriumPoint(int index, btScalar val)
{
	Native->setEquilibriumPoint(index, val);
}

void Generic6DofSpring2Constraint::SetEquilibriumPoint(int index)
{
	Native->setEquilibriumPoint(index);
}

void Generic6DofSpring2Constraint::SetFrames(Matrix frameA, Matrix frameB)
{
	TRANSFORM_CONV(frameA);
	TRANSFORM_CONV(frameB);
	Native->setFrames(TRANSFORM_USE(frameA), TRANSFORM_USE(frameB));
	TRANSFORM_DEL(frameA);
	TRANSFORM_DEL(frameB);
}

void Generic6DofSpring2Constraint::SetLimit(int axis, btScalar lo, btScalar hi)
{
	Native->setLimit(axis, lo, hi);
}

void Generic6DofSpring2Constraint::SetLimitReversed(int axis, btScalar lo, btScalar hi)
{
	Native->setLimitReversed(axis, lo, hi);
}

void Generic6DofSpring2Constraint::SetMaxMotorForce(int index, btScalar force)
{
	Native->setMaxMotorForce(index, force);
}

void Generic6DofSpring2Constraint::SetServo(int index, bool onOff)
{
	Native->setServo(index, onOff);
}

void Generic6DofSpring2Constraint::SetServoTarget(int index, btScalar target)
{
	Native->setServoTarget(index, target);
}

void Generic6DofSpring2Constraint::SetStiffness(int index, btScalar stiffness, bool limitIfNeeded)
{
	Native->setStiffness(index, stiffness, limitIfNeeded);
}

void Generic6DofSpring2Constraint::SetStiffness(int index, btScalar stiffness)
{
	Native->setStiffness(index, stiffness);
}

void Generic6DofSpring2Constraint::SetTargetVelocity(int index, btScalar velocity)
{
	Native->setTargetVelocity(index, velocity);
}

Vector3 Generic6DofSpring2Constraint::AngularLowerLimit::get()
{
	btVector3* angularLowerTemp = ALIGNED_NEW(btVector3);
	Native->getAngularLowerLimit(*angularLowerTemp);
	Vector3 ret = Math::BtVector3ToVector3(angularLowerTemp);
	ALIGNED_FREE(angularLowerTemp);
	return ret;
}
void Generic6DofSpring2Constraint::AngularLowerLimit::set(Vector3 angularLower)
{
	VECTOR3_CONV(angularLower);
	Native->setAngularLowerLimit(VECTOR3_USE(angularLower));
	VECTOR3_DEL(angularLower);
}

Vector3 Generic6DofSpring2Constraint::AngularLowerLimitReversed::get()
{
	btVector3* angularLowerTemp = ALIGNED_NEW(btVector3);
	Native->getAngularLowerLimitReversed(*angularLowerTemp);
	Vector3 ret = Math::BtVector3ToVector3(angularLowerTemp);
	ALIGNED_FREE(angularLowerTemp);
	return ret;
}
void Generic6DofSpring2Constraint::AngularLowerLimitReversed::set(Vector3 angularLower)
{
	VECTOR3_CONV(angularLower);
	Native->setAngularLowerLimitReversed(VECTOR3_USE(angularLower));
	VECTOR3_DEL(angularLower);
}

Vector3 Generic6DofSpring2Constraint::AngularUpperLimit::get()
{
	btVector3* angularUpperTemp = ALIGNED_NEW(btVector3);
	Native->getAngularUpperLimit(*angularUpperTemp);
	Vector3 ret = Math::BtVector3ToVector3(angularUpperTemp);
	ALIGNED_FREE(angularUpperTemp);
	return ret;
}
void Generic6DofSpring2Constraint::AngularUpperLimit::set(Vector3 angularUpper)
{
	VECTOR3_CONV(angularUpper);
	Native->setAngularUpperLimit(VECTOR3_USE(angularUpper));
	VECTOR3_DEL(angularUpper);
}

Vector3 Generic6DofSpring2Constraint::AngularUpperLimitReversed::get()
{
	btVector3* angularUpperTemp = ALIGNED_NEW(btVector3);
	Native->getAngularUpperLimitReversed(*angularUpperTemp);
	Vector3 ret = Math::BtVector3ToVector3(angularUpperTemp);
	ALIGNED_FREE(angularUpperTemp);
	return ret;
}
void Generic6DofSpring2Constraint::AngularUpperLimitReversed::set(Vector3 angularUpper)
{
	VECTOR3_CONV(angularUpper);
	Native->setAngularUpperLimitReversed(VECTOR3_USE(angularUpper));
	VECTOR3_DEL(angularUpper);
}

Matrix Generic6DofSpring2Constraint::CalculatedTransformA::get()
{
	return Math::BtTransformToMatrix(&Native->getCalculatedTransformA());
}

Matrix Generic6DofSpring2Constraint::CalculatedTransformB::get()
{
	return Math::BtTransformToMatrix(&Native->getCalculatedTransformB());
}

Matrix Generic6DofSpring2Constraint::FrameOffsetA::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetA());
}

Matrix Generic6DofSpring2Constraint::FrameOffsetB::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetB());
}

Vector3 Generic6DofSpring2Constraint::LinearLowerLimit::get()
{
	btVector3* linearLowerTemp = ALIGNED_NEW(btVector3);
	Native->getLinearLowerLimit(*linearLowerTemp);
	Vector3 ret = Math::BtVector3ToVector3(linearLowerTemp);
	ALIGNED_FREE(linearLowerTemp);
	return ret;
}
void Generic6DofSpring2Constraint::LinearLowerLimit::set(Vector3 linearLower)
{
	VECTOR3_CONV(linearLower);
	Native->setLinearLowerLimit(VECTOR3_USE(linearLower));
	VECTOR3_DEL(linearLower);
}

Vector3 Generic6DofSpring2Constraint::LinearUpperLimit::get()
{
	btVector3* linearUpperTemp = ALIGNED_NEW(btVector3);
	Native->getLinearUpperLimit(*linearUpperTemp);
	Vector3 ret = Math::BtVector3ToVector3(linearUpperTemp);
	ALIGNED_FREE(linearUpperTemp);
	return ret;
}
void Generic6DofSpring2Constraint::LinearUpperLimit::set(Vector3 linearUpper)
{
	VECTOR3_CONV(linearUpper);
	Native->setLinearUpperLimit(VECTOR3_USE(linearUpper));
	VECTOR3_DEL(linearUpper);
}

BulletSharp::RotateOrder Generic6DofSpring2Constraint::RotationOrder::get()
{
	return (BulletSharp::RotateOrder)Native->getRotationOrder();
}
void Generic6DofSpring2Constraint::RotationOrder::set(BulletSharp::RotateOrder order)
{
	Native->setRotationOrder((::RotateOrder)order);
}

TranslationalLimitMotor2^ Generic6DofSpring2Constraint::TranslationalLimitMotor::get()
{
	if (_linearLimits == nullptr)
    {
        _linearLimits = gcnew BulletSharp::TranslationalLimitMotor2(Native->getTranslationalLimitMotor(), true);
    }
    return _linearLimits;
}

#endif
