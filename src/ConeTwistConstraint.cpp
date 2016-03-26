#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "ConeTwistConstraint.h"
#include "RigidBody.h"

#define Native static_cast<btConeTwistConstraint*>(_native)

ConeTwistConstraint::ConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(rigidBodyAFrame);
	TRANSFORM_CONV(rigidBodyBFrame);
	UnmanagedPointer = new btConeTwistConstraint(*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(rigidBodyAFrame), TRANSFORM_USE(rigidBodyBFrame));
	TRANSFORM_DEL(rigidBodyAFrame);
	TRANSFORM_DEL(rigidBodyBFrame);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = rigidBodyB;
}

ConeTwistConstraint::ConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
	: TypedConstraint(0)
{
	TRANSFORM_CONV(rigidBodyAFrame);
	UnmanagedPointer = new btConeTwistConstraint(*(btRigidBody*)rigidBodyA->_native, TRANSFORM_USE(rigidBodyAFrame));
	TRANSFORM_DEL(rigidBodyAFrame);
	_rigidBodyA = rigidBodyA;
	_rigidBodyB = GetFixedBody();
}

void ConeTwistConstraint::CalcAngleInfo()
{
	Native->calcAngleInfo();
}

void ConeTwistConstraint::CalcAngleInfo2(Matrix transA, Matrix transB, Matrix invInertiaWorldA,
	Matrix invInertiaWorldB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	MATRIX3X3_CONV(invInertiaWorldA);
	MATRIX3X3_CONV(invInertiaWorldB);
	Native->calcAngleInfo2(TRANSFORM_USE(transA), TRANSFORM_USE(transB), MATRIX3X3_USE(invInertiaWorldA),
		MATRIX3X3_USE(invInertiaWorldB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
	MATRIX3X3_DEL(invInertiaWorldA);
	MATRIX3X3_DEL(invInertiaWorldB);
}

void ConeTwistConstraint::EnableMotor(bool b)
{
	Native->enableMotor(b);
}

void ConeTwistConstraint::GetInfo1NonVirtual(ConstraintInfo1^ info)
{
	Native->getInfo1NonVirtual(info->_native);
}

void ConeTwistConstraint::GetInfo2NonVirtual(ConstraintInfo2^ info, Matrix transA,
	Matrix transB, Matrix invInertiaWorldA, Matrix invInertiaWorldB)
{
	TRANSFORM_CONV(transA);
	TRANSFORM_CONV(transB);
	MATRIX3X3_CONV(invInertiaWorldA);
	MATRIX3X3_CONV(invInertiaWorldB);
	Native->getInfo2NonVirtual(info->_native, TRANSFORM_USE(transA), TRANSFORM_USE(transB),
		MATRIX3X3_USE(invInertiaWorldA), MATRIX3X3_USE(invInertiaWorldB));
	TRANSFORM_DEL(transA);
	TRANSFORM_DEL(transB);
	MATRIX3X3_DEL(invInertiaWorldA);
	MATRIX3X3_DEL(invInertiaWorldB);
}

btScalar ConeTwistConstraint::GetLimit(int limitIndex)
{
	return Native->getLimit(limitIndex);
}

#pragma managed(push, off)
void ConeTwistConstraint_GetPointForAngle(btConeTwistConstraint* constraint,
	btScalar fAngleInRadians, btScalar fLength, btVector3* point)
{
	*point = constraint->GetPointForAngle(fAngleInRadians, fLength);
}
#pragma managed(pop)
Vector3 ConeTwistConstraint::GetPointForAngle(btScalar fAngleInRadians, btScalar fLength)
{
	btVector3* pointTemp = ALIGNED_NEW(btVector3);
	ConeTwistConstraint_GetPointForAngle(Native, fAngleInRadians, fLength, pointTemp);
	Vector3 point = Math::BtVector3ToVector3(pointTemp);
	ALIGNED_FREE(pointTemp);
	return point;
}

void ConeTwistConstraint::SetFrames(Matrix frameA, Matrix frameB)
{
	TRANSFORM_CONV(frameA);
	TRANSFORM_CONV(frameB);
	Native->setFrames(TRANSFORM_USE(frameA), TRANSFORM_USE(frameB));
	TRANSFORM_DEL(frameA);
	TRANSFORM_DEL(frameB);
}

void ConeTwistConstraint::SetLimit(int limitIndex, btScalar limitValue)
{
	Native->setLimit(limitIndex, limitValue);
}

void ConeTwistConstraint::SetLimit(btScalar swingSpan1, btScalar swingSpan2, btScalar twistSpan,
	btScalar softness, btScalar biasFactor, btScalar relaxationFactor)
{
	Native->setLimit(swingSpan1, swingSpan2, twistSpan, softness, biasFactor, relaxationFactor);
}

void ConeTwistConstraint::SetLimit(btScalar swingSpan1, btScalar swingSpan2, btScalar twistSpan,
	btScalar softness, btScalar biasFactor)
{
	Native->setLimit(swingSpan1, swingSpan2, twistSpan, softness, biasFactor);
}

void ConeTwistConstraint::SetLimit(btScalar swingSpan1, btScalar swingSpan2, btScalar twistSpan,
	btScalar softness)
{
	Native->setLimit(swingSpan1, swingSpan2, twistSpan, softness);
}

void ConeTwistConstraint::SetLimit(btScalar swingSpan1, btScalar swingSpan2, btScalar twistSpan)
{
	Native->setLimit(swingSpan1, swingSpan2, twistSpan);
}

void ConeTwistConstraint::SetMaxMotorImpulseNormalized(btScalar maxMotorImpulse)
{
	Native->setMaxMotorImpulseNormalized(maxMotorImpulse);
}

void ConeTwistConstraint::SetMotorTargetInConstraintSpace(Quaternion q)
{
	QUATERNION_CONV(q);
	Native->setMotorTargetInConstraintSpace(QUATERNION_USE(q));
	QUATERNION_DEL(q);
}

void ConeTwistConstraint::UpdateRhs(btScalar timeStep)
{
	Native->updateRHS(timeStep);
}

Matrix ConeTwistConstraint::AFrame::get()
{
	return Math::BtTransformToMatrix(&Native->getAFrame());
}

bool ConeTwistConstraint::AngularOnly::get()
{
	return Native->getAngularOnly();
}
void ConeTwistConstraint::AngularOnly::set(bool angularOnly)
{
	Native->setAngularOnly(angularOnly);
}

Matrix ConeTwistConstraint::BFrame::get()
{
	return Math::BtTransformToMatrix(&Native->getBFrame());
}

btScalar ConeTwistConstraint::BiasFactor::get()
{
	return Native->getBiasFactor();
}

btScalar ConeTwistConstraint::Damping::get()
{
	return Native->getDamping();
}
void ConeTwistConstraint::Damping::set(btScalar damping)
{
	Native->setDamping(damping);
}

btScalar ConeTwistConstraint::FixThresh::get()
{
	return Native->getFixThresh();
}
void ConeTwistConstraint::FixThresh::set(btScalar fixThresh)
{
	Native->setFixThresh(fixThresh);
}

ConeTwistFlags ConeTwistConstraint::Flags::get()
{
	return (ConeTwistFlags) Native->getFlags();
}

Matrix ConeTwistConstraint::FrameOffsetA::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetA());
}

Matrix ConeTwistConstraint::FrameOffsetB::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetB());
}

bool ConeTwistConstraint::IsMaxMotorImpulseNormalized::get()
{
	return Native->isMaxMotorImpulseNormalized();
}

bool ConeTwistConstraint::IsMotorEnabled::get()
{
	return Native->isMotorEnabled();
}

bool ConeTwistConstraint::IsPastSwingLimit::get()
{
	return Native->isPastSwingLimit();
}

btScalar ConeTwistConstraint::LimitSoftness::get()
{
	return Native->getLimitSoftness();
}

btScalar ConeTwistConstraint::MaxMotorImpulse::get()
{
	return Native->getMaxMotorImpulse();
}
void ConeTwistConstraint::MaxMotorImpulse::set(btScalar maxMotorImpulse)
{
	Native->setMaxMotorImpulse(maxMotorImpulse);
}

Quaternion ConeTwistConstraint::MotorTarget::get()
{
	return Math::BtQuatToQuaternion(&Native->getMotorTarget());
}
void ConeTwistConstraint::MotorTarget::set(Quaternion q)
{
	QUATERNION_CONV(q);
	Native->setMotorTarget(QUATERNION_USE(q));
	QUATERNION_DEL(q);
}

btScalar ConeTwistConstraint::RelaxationFactor::get()
{
	return Native->getRelaxationFactor();
}

int ConeTwistConstraint::SolveSwingLimit::get()
{
	return Native->getSolveSwingLimit();
}

int ConeTwistConstraint::SolveTwistLimit::get()
{
	return Native->getSolveTwistLimit();
}

btScalar ConeTwistConstraint::SwingSpan1::get()
{
	return Native->getSwingSpan1();
}

btScalar ConeTwistConstraint::SwingSpan2::get()
{
	return Native->getSwingSpan2();
}

btScalar ConeTwistConstraint::TwistAngle::get()
{
	return Native->getTwistAngle();
}

btScalar ConeTwistConstraint::TwistLimitSign::get()
{
	return Native->getTwistLimitSign();
}

btScalar ConeTwistConstraint::TwistSpan::get()
{
	return Native->getTwistSpan();
}

#endif
