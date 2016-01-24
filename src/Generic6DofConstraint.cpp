#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "Collections.h"
#include "Generic6DofConstraint.h"
#include "RigidBody.h"

RotationalLimitMotor::RotationalLimitMotor(btRotationalLimitMotor* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

RotationalLimitMotor::~RotationalLimitMotor()
{
	this->!RotationalLimitMotor();
}

RotationalLimitMotor::!RotationalLimitMotor()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

RotationalLimitMotor::RotationalLimitMotor()
{
	_native = new btRotationalLimitMotor();
}

RotationalLimitMotor::RotationalLimitMotor(RotationalLimitMotor^ limitMotor)
{
	_native = new btRotationalLimitMotor(*limitMotor->_native);
}

btScalar RotationalLimitMotor::SolveAngularLimits(btScalar timeStep, Vector3 axis,
	btScalar jacDiagABInv, RigidBody^ body0, RigidBody^ body1)
{
	VECTOR3_CONV(axis);
	btScalar ret = _native->solveAngularLimits(timeStep, VECTOR3_USE(axis), jacDiagABInv,
		(btRigidBody*)body0->_native, (btRigidBody*)body1->_native);
	VECTOR3_DEL(axis);
	return ret;
}

int RotationalLimitMotor::TestLimitValue(btScalar testValue)
{
	return _native->testLimitValue(testValue);
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

btScalar RotationalLimitMotor::NormalCfm::get()
{
	return _native->m_normalCFM;
}
void RotationalLimitMotor::NormalCfm::set(btScalar value)
{
	_native->m_normalCFM = value;
}

btScalar RotationalLimitMotor::StopCfm::get()
{
	return _native->m_stopCFM;
}
void RotationalLimitMotor::StopCfm::set(btScalar value)
{
	_native->m_stopCFM = value;
}

btScalar RotationalLimitMotor::StopErp::get()
{
	return _native->m_stopERP;
}
void RotationalLimitMotor::StopErp::set(btScalar value)
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


TranslationalLimitMotor::TranslationalLimitMotor(btTranslationalLimitMotor* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

TranslationalLimitMotor::~TranslationalLimitMotor()
{
	this->!TranslationalLimitMotor();
}

TranslationalLimitMotor::!TranslationalLimitMotor()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
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

btScalar TranslationalLimitMotor::SolveLinearAxis(btScalar timeStep, btScalar jacDiagABInv,
	RigidBody^ body1, Vector3 pointInA, RigidBody^ body2, Vector3 pointInB, int limitIndex,
	Vector3 axisNormalOnA, Vector3 anchorPos)
{
	VECTOR3_CONV(pointInA);
	VECTOR3_CONV(pointInB);
	VECTOR3_CONV(axisNormalOnA);
	VECTOR3_CONV(anchorPos);
	btScalar ret = _native->solveLinearAxis(timeStep, jacDiagABInv, *(btRigidBody*)body1->_native,
		VECTOR3_USE(pointInA), *(btRigidBody*)body2->_native, VECTOR3_USE(pointInB),
		limitIndex, VECTOR3_USE(axisNormalOnA), VECTOR3_USE(anchorPos));
	VECTOR3_DEL(pointInA);
	VECTOR3_DEL(pointInB);
	VECTOR3_DEL(axisNormalOnA);
	VECTOR3_DEL(anchorPos);
	return ret;
}

int TranslationalLimitMotor::TestLimitValue(int limitIndex, btScalar testValue)
{
	return _native->testLimitValue(limitIndex, testValue);
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

Vector3 TranslationalLimitMotor::NormalCfm::get()
{
	return Math::BtVector3ToVector3(&_native->m_normalCFM);
}
void TranslationalLimitMotor::NormalCfm::set(Vector3 value)
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

Vector3 TranslationalLimitMotor::StopCfm::get()
{
	return Math::BtVector3ToVector3(&_native->m_stopCFM);
}
void TranslationalLimitMotor::StopCfm::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_stopCFM);
}

Vector3 TranslationalLimitMotor::StopErp::get()
{
	return Math::BtVector3ToVector3(&_native->m_stopERP);
}
void TranslationalLimitMotor::StopErp::set(Vector3 value)
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
	_angularLimits = gcnew array<RotationalLimitMotor^>(3);
}

Generic6DofConstraint::Generic6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(frameInA);
	TRANSFORM_CONV(frameInB);
	UnmanagedPointer = new btGeneric6DofConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(frameInA), TRANSFORM_USE(frameInB), useLinearReferenceFrameA);
	TRANSFORM_DEL(frameInA);
	TRANSFORM_DEL(frameInB);

	_angularLimits = gcnew array<RotationalLimitMotor^>(3);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

Generic6DofConstraint::Generic6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB,
	bool useLinearReferenceFrameB)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(frameInB);
	UnmanagedPointer = new btGeneric6DofConstraint(*(btRigidBody*)rigidBodyB->_native, TRANSFORM_USE(frameInB),
		useLinearReferenceFrameB);
	TRANSFORM_DEL(frameInB);

	_angularLimits = gcnew array<RotationalLimitMotor^>(3);
	_rigidBodyA = GetFixedBody();
	_rigidBodyB = rigidBodyB;
}

void Generic6DofConstraint::CalcAnchorPos()
{
	Native->calcAnchorPos();
}

void Generic6DofConstraint::CalculateTransforms(Matrix transA, Matrix transB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	Native->calculateTransforms(TRANSFORM_USE(transA), TRANSFORM_USE(transB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
}

void Generic6DofConstraint::CalculateTransforms()
{
	Native->calculateTransforms();
}

int Generic6DofConstraint::GetLimitMotorInfo2(RotationalLimitMotor^ limitMotor, Matrix transA,
	Matrix transB, Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB,
	ConstraintInfo2^ info, int row, Vector3 ax1, int rotational, int rotAllowed)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	VECTOR3_CONV(linVelA);
	VECTOR3_CONV(linVelB);
	VECTOR3_CONV(angVelA);
	VECTOR3_CONV(angVelB);
	VECTOR3_CONV(ax1);
	int ret = Native->get_limit_motor_info2(limitMotor->_native, TRANSFORM_USE(transA),
		TRANSFORM_USE(transB), VECTOR3_USE(linVelA), VECTOR3_USE(linVelB), VECTOR3_USE(angVelA),
		VECTOR3_USE(angVelB), info->_native, row, VECTOR3_USE(ax1), rotational, rotAllowed);
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
	VECTOR3_DEL(linVelA);
	VECTOR3_DEL(linVelB);
	VECTOR3_DEL(angVelA);
	VECTOR3_DEL(angVelB);
	VECTOR3_DEL(ax1);
	return ret;
}

int Generic6DofConstraint::GetLimitMotorInfo2(RotationalLimitMotor^ limitMotor, Matrix transA,
	Matrix transB, Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB,
	ConstraintInfo2^ info, int row, Vector3 ax1, int rotational)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	VECTOR3_CONV(linVelA);
	VECTOR3_CONV(linVelB);
	VECTOR3_CONV(angVelA);
	VECTOR3_CONV(angVelB);
	VECTOR3_CONV(ax1);
	int ret = Native->get_limit_motor_info2(limitMotor->_native, TRANSFORM_USE(transA),
		TRANSFORM_USE(transB), VECTOR3_USE(linVelA), VECTOR3_USE(linVelB), VECTOR3_USE(angVelA),
		VECTOR3_USE(angVelB), info->_native, row, VECTOR3_USE(ax1), rotational);
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
	VECTOR3_DEL(linVelA);
	VECTOR3_DEL(linVelB);
	VECTOR3_DEL(angVelA);
	VECTOR3_DEL(angVelB);
	VECTOR3_DEL(ax1);
	return ret;
}

btScalar Generic6DofConstraint::GetAngle(int axisIndex)
{
	return Native->getAngle(axisIndex);
}

#pragma managed(push, off)
void Generic6DofConstraint_GetAxis(btGeneric6DofConstraint* constraint, int axis_index, btVector3* axis)
{
	axis = &constraint->getAxis(axis_index);
}
#pragma managed(pop)
Vector3 Generic6DofConstraint::GetAxis(int axisIndex)
{
	btVector3* axisTemp = ALIGNED_NEW(btVector3);
	Generic6DofConstraint_GetAxis(Native, axisIndex, axisTemp);
	Vector3 ret = Math::BtVector3ToVector3(axisTemp);
	ALIGNED_FREE(axisTemp);
	return ret;
}

void Generic6DofConstraint::GetInfo1NonVirtual(ConstraintInfo1^ info)
{
	Native->getInfo1NonVirtual(info->_native);
}

void Generic6DofConstraint::GetInfo2NonVirtual(ConstraintInfo2^ info, Matrix transA,
	Matrix transB, Vector3 linVelA, Vector3 linVelB, Vector3 angVelA, Vector3 angVelB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	VECTOR3_CONV(linVelA);
	VECTOR3_CONV(linVelB);
	VECTOR3_CONV(angVelA);
	VECTOR3_CONV(angVelB);
	Native->getInfo2NonVirtual(info->_native, TRANSFORM_USE(transA), TRANSFORM_USE(transB),
		VECTOR3_USE(linVelA), VECTOR3_USE(linVelB), VECTOR3_USE(angVelA), VECTOR3_USE(angVelB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
	VECTOR3_DEL(linVelA);
	VECTOR3_DEL(linVelB);
	VECTOR3_DEL(angVelA);
	VECTOR3_DEL(angVelB);
}

btScalar Generic6DofConstraint::GetRelativePivotPosition(int axisIndex)
{
	return Native->getRelativePivotPosition(axisIndex);
}

RotationalLimitMotor^ Generic6DofConstraint::GetRotationalLimitMotor(int index)
{
	if (_angularLimits[index] == nullptr)
    {
        _angularLimits[index] = gcnew RotationalLimitMotor(Native->getRotationalLimitMotor(index), true);
    }
    return _angularLimits[index];
}

bool Generic6DofConstraint::IsLimited(int limitIndex)
{
	return Native->isLimited(limitIndex);
}

void Generic6DofConstraint::SetAxis(Vector3 axis1, Vector3 axis2)
{
	VECTOR3_CONV(axis1);
	VECTOR3_CONV(axis2);
	Native->setAxis(VECTOR3_USE(axis1), VECTOR3_USE(axis2));
	VECTOR3_DEL(axis1);
	VECTOR3_DEL(axis2);
}

void Generic6DofConstraint::SetFrames(Matrix frameA, Matrix frameB)
{
	TRANSFORM_CONV(frameA);
	TRANSFORM_CONV(frameB);
	Native->setFrames(TRANSFORM_USE(frameA), TRANSFORM_USE(frameB));
	TRANSFORM_DEL(frameA);
	TRANSFORM_DEL(frameB);
}

void Generic6DofConstraint::SetLimit(int axis, btScalar lo, btScalar hi)
{
	Native->setLimit(axis, lo, hi);
}

bool Generic6DofConstraint::TestAngularLimitMotor(int axisIndex)
{
	return Native->testAngularLimitMotor(axisIndex);
}

void Generic6DofConstraint::UpdateRhs(btScalar timeStep)
{
	Native->updateRHS(timeStep);
}

Vector3 Generic6DofConstraint::AngularLowerLimit::get()
{
	btVector3* limitTemp = ALIGNED_NEW(btVector3);
	Native->getAngularLowerLimit(*limitTemp);
	Vector3 limit = Math::BtVector3ToVector3(limitTemp);
	ALIGNED_FREE(limitTemp);
	return limit;
}
void Generic6DofConstraint::AngularLowerLimit::set(Vector3 angularLower)
{
	VECTOR3_CONV(angularLower);
	Native->setAngularLowerLimit(VECTOR3_USE(angularLower));
	VECTOR3_DEL(angularLower);
}

Vector3 Generic6DofConstraint::AngularUpperLimit::get()
{
	btVector3* limitTemp = ALIGNED_NEW(btVector3);
	Native->getAngularUpperLimit(*limitTemp);
	Vector3 limit = Math::BtVector3ToVector3(limitTemp);
	ALIGNED_FREE(limitTemp);
	return limit;
}
void Generic6DofConstraint::AngularUpperLimit::set(Vector3 angularUpper)
{
	VECTOR3_CONV(angularUpper);
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

SixDofFlags Generic6DofConstraint::Flags::get()
{
	return (SixDofFlags) Native->getFlags();
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
	ALIGNED_FREE(m);
	ALIGNED_FREE(a);
#else
	btScalar m[16];
	btTransform* a = Math::MatrixToBtTransform(value);
	a->getOpenGLMatrix(m);
	Native->getFrameOffsetA().setFromOpenGLMatrix(m);
	ALIGNED_FREE(a);
#endif
}

Matrix Generic6DofConstraint::FrameOffsetB::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetB());
}
void Generic6DofConstraint::FrameOffsetB::set(Matrix value)
{
#if defined(BT_USE_SIMD_VECTOR3) && defined(BT_USE_SSE_IN_API) && defined(BT_USE_SSE)
	btScalar* m = (btScalar*)btAlignedAlloc(sizeof(btScalar) * 16, 16);
	btTransform* a = Math::MatrixToBtTransform(value);
	a->getOpenGLMatrix(m);
	Native->getFrameOffsetB().setFromOpenGLMatrix(m);
	btAlignedFree(m);
	ALIGNED_FREE(a);
#else
	btScalar m[16];
	btTransform* a = Math::MatrixToBtTransform(value);
	a->getOpenGLMatrix(m);
	Native->getFrameOffsetB().setFromOpenGLMatrix(m);
	ALIGNED_FREE(a);
#endif
}

Vector3 Generic6DofConstraint::LinearLowerLimit::get()
{
	btVector3* limitTemp = ALIGNED_NEW(btVector3);
	Native->getLinearLowerLimit(*limitTemp);
	Vector3 limit = Math::BtVector3ToVector3(limitTemp);
	ALIGNED_FREE(limitTemp);
	return limit;
}
void Generic6DofConstraint::LinearLowerLimit::set(Vector3 linearLower)
{
	VECTOR3_CONV(linearLower);
	Native->setLinearLowerLimit(VECTOR3_USE(linearLower));
	VECTOR3_DEL(linearLower);
}

Vector3 Generic6DofConstraint::LinearUpperLimit::get()
{
	btVector3* limitTemp = ALIGNED_NEW(btVector3);
	Native->getLinearUpperLimit(*limitTemp);
	Vector3 limit = Math::BtVector3ToVector3(limitTemp);
	ALIGNED_FREE(limitTemp);
	return limit;
}
void Generic6DofConstraint::LinearUpperLimit::set(Vector3 linearUpper)
{
	VECTOR3_CONV(linearUpper);
	Native->setLinearUpperLimit(VECTOR3_USE(linearUpper));
	VECTOR3_DEL(linearUpper);
}

BulletSharp::TranslationalLimitMotor^ Generic6DofConstraint::TranslationalLimitMotor::get()
{
	if (_linearLimits == nullptr)
    {
        _linearLimits = gcnew BulletSharp::TranslationalLimitMotor(Native->getTranslationalLimitMotor(), true);
    }
    return _linearLimits;
}

bool Generic6DofConstraint::UseFrameOffset::get()
{
	return Native->getUseFrameOffset();
}
void Generic6DofConstraint::UseFrameOffset::set(bool frameOffsetOnOff)
{
	Native->setUseFrameOffset(frameOffsetOnOff);
}

bool Generic6DofConstraint::UseLinearReferenceFrameA::get()
{
	return Native->getUseLinearReferenceFrameA();
}
void Generic6DofConstraint::UseLinearReferenceFrameA::set(bool linearReferenceFrameA)
{
	Native->setUseLinearReferenceFrameA(linearReferenceFrameA);
}

#endif
