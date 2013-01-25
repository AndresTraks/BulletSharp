#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "ConeTwistConstraint.h"
#include "RigidBody.h"

#define Native static_cast<btConeTwistConstraint*>(_native)

ConeTwistConstraint::ConeTwistConstraint(btConeTwistConstraint* constraint)
: TypedConstraint(constraint)
{
}

ConeTwistConstraint::ConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
: TypedConstraint(0)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	UnmanagedPointer = new btConeTwistConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp);

	ALIGNED_FREE(rigidBodyAFrameTemp);
	ALIGNED_FREE(rigidBodyBFrameTemp);
}

ConeTwistConstraint::ConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
: TypedConstraint(0)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	UnmanagedPointer = new btConeTwistConstraint(*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp);

	ALIGNED_FREE(rigidBodyAFrameTemp);
}

void ConeTwistConstraint::CalcAngleInfo()
{
	Native->calcAngleInfo();
}

void ConeTwistConstraint::CalcAngleInfo2(Matrix transA, Matrix transB, Matrix invInertiaWorldA, Matrix invInertiaWorldB)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);
	btMatrix3x3* invInertiaWorldATemp = Math::MatrixToBtMatrix3x3(invInertiaWorldA);
	btMatrix3x3* invInertiaWorldBTemp = Math::MatrixToBtMatrix3x3(invInertiaWorldB);

	Native->calcAngleInfo2(*transATemp, *transBTemp, *invInertiaWorldATemp, *invInertiaWorldBTemp);

	ALIGNED_FREE(transATemp);
	ALIGNED_FREE(transBTemp);
	delete invInertiaWorldATemp;
	delete invInertiaWorldBTemp;
}

void ConeTwistConstraint::EnableMotor(bool b)
{
	Native->enableMotor(b);
}

void ConeTwistConstraint::SetAngularOnly(bool angularOnly)
{
	Native->setAngularOnly(angularOnly);
}

void ConeTwistConstraint::SetDamping(btScalar damping)
{
	Native->setDamping(damping);
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
	btVector3* pointTemp = new btVector3;
	ConeTwistConstraint_GetPointForAngle(Native, fAngleInRadians, fLength, pointTemp);
	Vector3 point = Math::BtVector3ToVector3(pointTemp);
	delete pointTemp;
	return point;
}

void ConeTwistConstraint::SetLimit(btScalar _swingSpan1, btScalar _swingSpan2,
	btScalar _twistSpan, btScalar _softness, btScalar _biasFactor, btScalar _relaxationFactor)
{
	Native->setLimit(_swingSpan1, _swingSpan2, _twistSpan, _softness,
		_biasFactor, _relaxationFactor);
}

void ConeTwistConstraint::SetLimit(btScalar _swingSpan1, btScalar _swingSpan2,
	btScalar _twistSpan, btScalar _softness, btScalar _biasFactor)
{
	Native->setLimit(_swingSpan1, _swingSpan2, _twistSpan, _softness, _biasFactor);
}

void ConeTwistConstraint::SetLimit(btScalar _swingSpan1, btScalar _swingSpan2,
	btScalar _twistSpan, btScalar _softness)
{
	Native->setLimit(_swingSpan1, _swingSpan2, _twistSpan, _softness);
}

void ConeTwistConstraint::SetLimit(btScalar _swingSpan1, btScalar _swingSpan2, btScalar _twistSpan)
{
	Native->setLimit(_swingSpan1, _swingSpan2, _twistSpan);
}

void ConeTwistConstraint::SetLimit(int limitIndex, btScalar limitValue)
{
	Native->setLimit(limitIndex, limitValue);
}

void ConeTwistConstraint::SetMaxMotorImpulse(btScalar maxMotorImpulse)
{
	Native->setMaxMotorImpulse(maxMotorImpulse);
}

void ConeTwistConstraint::SetMaxMotorImpulseNormalized(btScalar maxMotorImpulse)
{
	Native->setMaxMotorImpulseNormalized(maxMotorImpulse);
}

void ConeTwistConstraint::SetMotorTarget(Quaternion q)
{
	btQuaternion* qTemp = Math::QuaternionToBtQuat(q);
	Native->setMotorTarget(*qTemp);
	ALIGNED_FREE(qTemp);
}

void ConeTwistConstraint::SetMotorTargetInConstraintSpace(Quaternion q)
{
	btQuaternion* qTemp = Math::QuaternionToBtQuat(q);
	Native->setMotorTargetInConstraintSpace(*qTemp);
	ALIGNED_FREE(qTemp);
}

void ConeTwistConstraint::UpdateRHS(btScalar timeStep)
{
	Native->updateRHS(timeStep);
}

Matrix ConeTwistConstraint::AFrame::get()
{
	return Math::BtTransformToMatrix(&Native->getAFrame());
}

Matrix ConeTwistConstraint::BFrame::get()
{
	return Math::BtTransformToMatrix(&Native->getBFrame());
}

btScalar ConeTwistConstraint::FixThresh::get()
{
	return Native->getFixThresh();
}
void ConeTwistConstraint::FixThresh::set(btScalar value)
{
	Native->setFixThresh(value);
}

Matrix ConeTwistConstraint::FrameOffsetA::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetA());
}

Matrix ConeTwistConstraint::FrameOffsetB::get()
{
	return Math::BtTransformToMatrix(&Native->getFrameOffsetB());
}

bool ConeTwistConstraint::IsPastSwingLimit::get()
{
	return Native->isPastSwingLimit();
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
