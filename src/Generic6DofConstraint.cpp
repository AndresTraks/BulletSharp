#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "Collections.h"
#include "Generic6DofConstraint.h"
#include "RigidBody.h"

RotationalLimitMotor::RotationalLimitMotor()
{
	_native = new btRotationalLimitMotor();
}

RotationalLimitMotor::RotationalLimitMotor(RotationalLimitMotor^ _native)
{
	this->_native = new btRotationalLimitMotor(*_native->_native);
}

RotationalLimitMotor::RotationalLimitMotor(btRotationalLimitMotor* _native)
{
	this->_native = _native;
}

btScalar RotationalLimitMotor::SolveAngularLimits(btScalar timeStep, Vector3 axis, btScalar jacDiagABInv, RigidBody^ body0, RigidBody^ body1)
{
	VECTOR3_DEF(axis);
	
	btScalar ret = _native->solveAngularLimits(timeStep, VECTOR3_USE(axis),
		jacDiagABInv, (btRigidBody*)body0->_native, (btRigidBody*)body1->_native);

	VECTOR3_DEL(axis);
	return ret;
}

int RotationalLimitMotor::TestLimitValue(btScalar test_value)
{
	return _native->testLimitValue(test_value);
}

btScalar RotationalLimitMotor::AccumulatedImpulse::get()
{
	return _native->m_accumulatedImpulse;
}
void RotationalLimitMotor::AccumulatedImpulse::set(btScalar value)
{
	_native->m_accumulatedImpulse = value;
}

btScalar RotationalLimitMotor::Bounce::get()
{
	return _native->m_bounce;
}
void RotationalLimitMotor::Bounce::set(btScalar value)
{
	_native->m_bounce = value;
}

int RotationalLimitMotor::CurrentLimit::get()
{
	return _native->m_currentLimit;
}
void RotationalLimitMotor::CurrentLimit::set(int value)
{
	_native->m_currentLimit = value;
}

btScalar RotationalLimitMotor::CurrentLimitError::get()
{
	return _native->m_currentLimitError;
}
void RotationalLimitMotor::CurrentLimitError::set(btScalar value)
{
	_native->m_currentLimitError = value;
}

btScalar RotationalLimitMotor::CurrentPosition::get()
{
	return _native->m_currentPosition;
}
void RotationalLimitMotor::CurrentPosition::set(btScalar value)
{
	_native->m_currentPosition = value;
}

btScalar RotationalLimitMotor::Damping::get()
{
	return _native->m_damping;
}
void RotationalLimitMotor::Damping::set(btScalar value)
{
	_native->m_damping = value;
}

bool RotationalLimitMotor::EnableMotor::get()
{
	return _native->m_enableMotor;
}
void RotationalLimitMotor::EnableMotor::set(bool value)
{
	_native->m_enableMotor = value;
}

btScalar RotationalLimitMotor::HiLimit::get()
{
	return _native->m_hiLimit;
}
void RotationalLimitMotor::HiLimit::set(btScalar value)
{
	_native->m_hiLimit = value;
}

bool RotationalLimitMotor::IsLimited::get()
{
	return _native->isLimited();
}

btScalar RotationalLimitMotor::LimitSoftness::get()
{
	return _native->m_limitSoftness;
}
void RotationalLimitMotor::LimitSoftness::set(btScalar value)
{
	_native->m_limitSoftness = value;
}

btScalar RotationalLimitMotor::LoLimit::get()
{
	return _native->m_loLimit;
}
void RotationalLimitMotor::LoLimit::set(btScalar value)
{
	_native->m_loLimit = value;
}

btScalar RotationalLimitMotor::MaxLimitForce::get()
{
	return _native->m_maxLimitForce;
}
void RotationalLimitMotor::MaxLimitForce::set(btScalar value)
{
	_native->m_maxLimitForce = value;
}

btScalar RotationalLimitMotor::MaxMotorForce::get()
{
	return _native->m_maxMotorForce;
}
void RotationalLimitMotor::MaxMotorForce::set(btScalar value)
{
	_native->m_maxMotorForce = value;
}

bool RotationalLimitMotor::NeedApplyTorques::get()
{
	return _native->needApplyTorques();
}

btScalar RotationalLimitMotor::NormalCFM::get()
{
	return _native->m_normalCFM;
}
void RotationalLimitMotor::NormalCFM::set(btScalar value)
{
	_native->m_normalCFM = value;
}

btScalar RotationalLimitMotor::StopCFM::get()
{
	return _native->m_stopCFM;
}
void RotationalLimitMotor::StopCFM::set(btScalar value)
{
	_native->m_stopCFM = value;
}

btScalar RotationalLimitMotor::StopERP::get()
{
	return _native->m_stopERP;
}
void RotationalLimitMotor::StopERP::set(btScalar value)
{
	_native->m_stopERP = value;
}

btScalar RotationalLimitMotor::TargetVelocity::get()
{
	return _native->m_targetVelocity;
}
void RotationalLimitMotor::TargetVelocity::set(btScalar value)
{
	_native->m_targetVelocity = value;
}

TranslationalLimitMotor::TranslationalLimitMotor(btTranslationalLimitMotor* native)
{
	_native = native;
}

TranslationalLimitMotor::TranslationalLimitMotor()
{
	_native = new btTranslationalLimitMotor();
}

TranslationalLimitMotor::TranslationalLimitMotor(TranslationalLimitMotor^ other)
{
	_native = new btTranslationalLimitMotor(*other->_native);
}

bool TranslationalLimitMotor::IsLimited(int limitIndex)
{
	return _native->isLimited(limitIndex);
}

bool TranslationalLimitMotor::NeedApplyForce(int limitIndex)
{
	return _native->needApplyForce(limitIndex);
}

btScalar TranslationalLimitMotor::SolveLinearAxis(btScalar timeStep, btScalar jacDiagABInv, RigidBody^ body1, Vector3 pointInA, RigidBody^ body2, Vector3 pointInB, int limit_index, Vector3 axis_normal_on_a, Vector3 anchorPos)
{
	VECTOR3_DEF(pointInA);
	VECTOR3_DEF(pointInB);
	VECTOR3_DEF(axis_normal_on_a);
	VECTOR3_DEF(anchorPos);

	btScalar ret =  _native->solveLinearAxis(timeStep, jacDiagABInv,
		*(btRigidBody*)body1->_native, VECTOR3_USE(pointInA),
		*(btRigidBody*)body2->_native, VECTOR3_USE(pointInB),
		limit_index, VECTOR3_USE(axis_normal_on_a), VECTOR3_USE(anchorPos)
	);

	VECTOR3_DEL(pointInA);
	VECTOR3_DEL(pointInB);
	VECTOR3_DEL(axis_normal_on_a);
	VECTOR3_DEL(anchorPos);

	return ret;
}

int TranslationalLimitMotor::TestLimitValue(int limitIndex, btScalar test_value)
{
	return _native->testLimitValue(limitIndex, test_value);
}

Vector3 TranslationalLimitMotor::AccumulatedImpulse::get()
{
	return Math::BtVector3ToVector3(&_native->m_accumulatedImpulse);
}
void TranslationalLimitMotor::AccumulatedImpulse::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_accumulatedImpulse);
}

IntArray^ TranslationalLimitMotor::CurrentLimit::get()
{
	return gcnew IntArray(_native->m_currentLimit, 3);
}

Vector3 TranslationalLimitMotor::CurrentLimitError::get()
{
	return Math::BtVector3ToVector3(&_native->m_currentLimitError);
}
void TranslationalLimitMotor::CurrentLimitError::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_currentLimitError);
}

Vector3 TranslationalLimitMotor::CurrentLinearDiff::get()
{
	return Math::BtVector3ToVector3(&_native->m_currentLinearDiff);
}
void TranslationalLimitMotor::CurrentLinearDiff::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_currentLinearDiff);
}

btScalar TranslationalLimitMotor::Damping::get()
{
	return _native->m_damping;
}
void TranslationalLimitMotor::Damping::set(btScalar value)
{
	_native->m_damping = value;
}

BoolArray^ TranslationalLimitMotor::EnableMotor::get()
{
	return gcnew BoolArray(_native->m_enableMotor, 3);
}

btScalar TranslationalLimitMotor::LimitSoftness::get()
{
	return _native->m_limitSoftness;
}
void TranslationalLimitMotor::LimitSoftness::set(btScalar value)
{
	_native->m_limitSoftness = value;
}

Vector3 TranslationalLimitMotor::LowerLimit::get()
{
	return Math::BtVector3ToVector3(&_native->m_lowerLimit);
}
void TranslationalLimitMotor::LowerLimit::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_lowerLimit);
}

Vector3 TranslationalLimitMotor::MaxMotorForce::get()
{
	return Math::BtVector3ToVector3(&_native->m_maxMotorForce);
}
void TranslationalLimitMotor::MaxMotorForce::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_maxMotorForce);
}

Vector3 TranslationalLimitMotor::NormalCFM::get()
{
	return Math::BtVector3ToVector3(&_native->m_normalCFM);
}
void TranslationalLimitMotor::NormalCFM::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_normalCFM);
}

btScalar TranslationalLimitMotor::Restitution::get()
{
	return _native->m_restitution;
}
void TranslationalLimitMotor::Restitution::set(btScalar value)
{
	_native->m_restitution = value;
}

Vector3 TranslationalLimitMotor::StopCFM::get()
{
	return Math::BtVector3ToVector3(&_native->m_stopCFM);
}
void TranslationalLimitMotor::StopCFM::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_stopCFM);
}

Vector3 TranslationalLimitMotor::StopERP::get()
{
	return Math::BtVector3ToVector3(&_native->m_stopERP);
}
void TranslationalLimitMotor::StopERP::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_stopERP);
}

Vector3 TranslationalLimitMotor::TargetVelocity::get()
{
	return Math::BtVector3ToVector3(&_native->m_targetVelocity);
}
void TranslationalLimitMotor::TargetVelocity::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_targetVelocity);
}

Vector3 TranslationalLimitMotor::UpperLimit::get()
{
	return Math::BtVector3ToVector3(&_native->m_upperLimit);
}
void TranslationalLimitMotor::UpperLimit::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_upperLimit);
}


#define Native static_cast<btGeneric6DofConstraint*>(_native)

Generic6DofConstraint::Generic6DofConstraint(btGeneric6DofConstraint* native)
	: TypedConstraint(native)
{
}

Generic6DofConstraint::Generic6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
: TypedConstraint(0)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	UnmanagedPointer = new btGeneric6DofConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*frameInATemp, *frameInBTemp, useLinearReferenceFrameA);

	ALIGNED_FREE(frameInATemp);
	ALIGNED_FREE(frameInBTemp);
}

Generic6DofConstraint::Generic6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB)
: TypedConstraint(0)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);
	UnmanagedPointer = new btGeneric6DofConstraint(*(btRigidBody*)rigidBodyB->_native, *frameInBTemp, useLinearReferenceFrameB);
	ALIGNED_FREE(frameInBTemp);
}

void Generic6DofConstraint::CalcAnchorPos()
{
	Native->calcAnchorPos();
}

void Generic6DofConstraint::CalculateTransforms(Matrix transA, Matrix transB)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);

	Native->calculateTransforms(*transATemp, *transBTemp);

	ALIGNED_FREE(transATemp);
	ALIGNED_FREE(transBTemp);
}

void Generic6DofConstraint::CalculateTransforms()
{
	Native->calculateTransforms();
}
/*
int Generic6DofConstraint::GetLimitMotorInfo2(RotationalLimitMotor^ limitMotor, Matrix transA, Matrix transB, Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB, btConstraintInfo2^ info, int row, Vector3 ax1, int rotational, int rotAllowed)
{
	Native->get_limit_motor_info2(limitMotor->_native, transA->_native, transB->_native, linVelA->_native, linVelB->_native, angVelA->_native, angVelB->_native, info->_native, row, ax1->_native, rotational, rotAllowed);
}

int Generic6DofConstraint::GetLimitMotorInfo2(RotationalLimitMotor^ limitMotor, Matrix transA, Matrix transB, Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB, btConstraintInfo2^ info, int row, Vector3 ax1, int rotational)
{
	Native->get_limit_motor_info2(limitMotor->_native, transA->_native, transB->_native, linVelA->_native, linVelB->_native, angVelA->_native, angVelB->_native, info->_native, row, ax1->_native, rotational);
}
*/
btScalar Generic6DofConstraint::GetAngle(int axis_index)
{
	return Native->getAngle(axis_index);
}

#pragma managed(push, off)
btVector3* Generic6DofConstraint_GetAxis(btGeneric6DofConstraint* constraint, int axis_index)
{
	return &constraint->getAxis(axis_index);
}
#pragma managed(pop)
Vector3 Generic6DofConstraint::GetAxis(int axis_index)
{
	return Math::BtVector3ToVector3(Generic6DofConstraint_GetAxis(Native, axis_index));
}
/*
void Generic6DofConstraint::GetInfo2NonVirtual(btConstraintInfo2^ info, Matrix transA, Matrix transB, Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB)
{
	Native->getInfo2NonVirtual(info->_native, transA->_native, transB->_native, linVelA->_native, linVelB->_native, angVelA->_native, angVelB->_native);
}
*/
btScalar Generic6DofConstraint::GetRelativePivotPosition(int axis_index)
{
	return Native->getRelativePivotPosition(axis_index);
}

RotationalLimitMotor^ Generic6DofConstraint::GetRotationalLimitMotor(int index)
{
	return gcnew RotationalLimitMotor(Native->getRotationalLimitMotor(index));
}

bool Generic6DofConstraint::IsLimited(int limitIndex)
{
	return Native->isLimited(limitIndex);
}

void Generic6DofConstraint::SetAxis(Vector3 axis1, Vector3 axis2)
{
	VECTOR3_DEF(axis1);
	VECTOR3_DEF(axis2);

	Native->setAxis(VECTOR3_USE(axis1), VECTOR3_USE(axis2));

	VECTOR3_DEL(axis1);
	VECTOR3_DEL(axis2);
}

void Generic6DofConstraint::SetFrames(Matrix frameA, Matrix frameB)
{
	btTransform* frameATemp = Math::MatrixToBtTransform(frameA);
	btTransform* frameBTemp = Math::MatrixToBtTransform(frameB);

	Native->setFrames(*frameATemp, *frameBTemp);

	ALIGNED_FREE(frameBTemp);
	ALIGNED_FREE(frameATemp);
}

void Generic6DofConstraint::SetLimit(int axis, btScalar lo, btScalar hi)
{
	Native->setLimit(axis, lo, hi);
}

bool Generic6DofConstraint::TestAngularLimitMotor(int axis_index)
{
	return Native->testAngularLimitMotor(axis_index);
}

void Generic6DofConstraint::UpdateRHS(btScalar timeStep)
{
	Native->updateRHS(timeStep);
}

Vector3 Generic6DofConstraint::AngularLowerLimit::get()
{
	btVector3* limitTemp = new btVector3;
	Native->getAngularLowerLimit(*limitTemp);
	Vector3 limit = Math::BtVector3ToVector3(limitTemp);
	delete limitTemp;
	return limit;
}
void Generic6DofConstraint::AngularLowerLimit::set(Vector3 angularLower)
{
	VECTOR3_DEF(angularLower);
	Native->setAngularLowerLimit(VECTOR3_USE(angularLower));
	VECTOR3_DEL(angularLower);
}

Vector3 Generic6DofConstraint::AngularUpperLimit::get()
{
	btVector3* limitTemp = new btVector3;
	Native->getAngularUpperLimit(*limitTemp);
	Vector3 limit = Math::BtVector3ToVector3(limitTemp);
	delete limitTemp;
	return limit;
}
void Generic6DofConstraint::AngularUpperLimit::set(Vector3 angularUpper)
{
	VECTOR3_DEF(angularUpper);
	Native->setAngularUpperLimit(VECTOR3_USE(angularUpper));
	VECTOR3_DEL(angularUpper);
}

Matrix Generic6DofConstraint::CalculatedTransformA::get()
{
	return Math::BtTransformToMatrix(&Native->getCalculatedTransformA());
}

Matrix Generic6DofConstraint::CalculatedTransformB::get()
{
	return Math::BtTransformToMatrix(&Native->getCalculatedTransformB());
}

Matrix Generic6DofConstraint::FrameOffsetA::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetA());
}
void Generic6DofConstraint::FrameOffsetA::set(Matrix value)
{
#if defined(BT_USE_SIMD_VECTOR3) && defined(BT_USE_SSE_IN_API) && defined(BT_USE_SSE)
	btScalar* m = (btScalar*)btAlignedAlloc(sizeof(btScalar) * 16, 16);
	btTransform* a = Math::MatrixToBtTransform(value);
	a->getOpenGLMatrix(m);
	Native->getFrameOffsetA().setFromOpenGLMatrix(m);
	btAlignedFree(m);
#else
	btScalar m[16];
	btTransform* a = Math::MatrixToBtTransform(value);
	a->getOpenGLMatrix(m);
	Native->getFrameOffsetA().setFromOpenGLMatrix(m);
#endif
}

Matrix Generic6DofConstraint::FrameOffsetB::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetB());
}
void Generic6DofConstraint::FrameOffsetB::set(Matrix value)
{
	btScalar m[16];
	btTransform* a = Math::MatrixToBtTransform(value);
	a->getOpenGLMatrix(m);
	Native->getFrameOffsetB().setFromOpenGLMatrix(m);
	ALIGNED_FREE(a);
}
/*
void Generic6DofConstraint::Info1NonVirtual::get()
{
	return _native->getInfo1NonVirtual();
}
*/
Vector3 Generic6DofConstraint::LinearLowerLimit::get()
{
	btVector3* limitTemp = new btVector3;
	Native->getLinearLowerLimit(*limitTemp);
	Vector3 limit = Math::BtVector3ToVector3(limitTemp);
	delete limitTemp;
	return limit;
}
void Generic6DofConstraint::LinearLowerLimit::set(Vector3 linearLower)
{
	VECTOR3_DEF(linearLower);
	Native->setLinearLowerLimit(VECTOR3_USE(linearLower));
	VECTOR3_DEL(linearLower);
}

Vector3 Generic6DofConstraint::LinearUpperLimit::get()
{
	btVector3* limitTemp = new btVector3;
	Native->getLinearUpperLimit(*limitTemp);
	Vector3 limit = Math::BtVector3ToVector3(limitTemp);
	delete limitTemp;
	return limit;
}
void Generic6DofConstraint::LinearUpperLimit::set(Vector3 linearUpper)
{
	VECTOR3_DEF(linearUpper);
	Native->setLinearUpperLimit(VECTOR3_USE(linearUpper));
	VECTOR3_DEL(linearUpper);
}

BulletSharp::TranslationalLimitMotor^ Generic6DofConstraint::TranslationalLimitMotor::get()
{
	return gcnew BulletSharp::TranslationalLimitMotor(Native->getTranslationalLimitMotor());
}

bool Generic6DofConstraint::UseFrameOffset::get()
{
	return Native->getUseFrameOffset();
}
void Generic6DofConstraint::UseFrameOffset::set(bool value)
{
	Native->setUseFrameOffset(value);
}

#endif
