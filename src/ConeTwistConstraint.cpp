#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "ConeTwistConstraint.h"
#include "RigidBody.h"

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
	UnmanagedPointer->calcAngleInfo();
}

void ConeTwistConstraint::CalcAngleInfo2(Matrix transA, Matrix transB, Matrix invInertiaWorldA, Matrix invInertiaWorldB)
{
	btTransform* transATemp = Math::MatrixToBtTransform(transA);
	btTransform* transBTemp = Math::MatrixToBtTransform(transB);
	btMatrix3x3* invInertiaWorldATemp = Math::MatrixToBtMatrix3x3(invInertiaWorldA);
	btMatrix3x3* invInertiaWorldBTemp = Math::MatrixToBtMatrix3x3(invInertiaWorldB);

	UnmanagedPointer->calcAngleInfo2(*transATemp, *transBTemp, *invInertiaWorldATemp, *invInertiaWorldBTemp);

	ALIGNED_FREE(transATemp);
	ALIGNED_FREE(transBTemp);
	delete invInertiaWorldATemp;
	delete invInertiaWorldBTemp;
}

void ConeTwistConstraint::EnableMotor(bool b)
{
	UnmanagedPointer->enableMotor(b);
}

void ConeTwistConstraint::SetAngularOnly(bool angularOnly)
{
	UnmanagedPointer->setAngularOnly(angularOnly);
}

void ConeTwistConstraint::SetDamping(btScalar damping)
{
	UnmanagedPointer->setDamping(damping);
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
	ConeTwistConstraint_GetPointForAngle(UnmanagedPointer, fAngleInRadians, fLength, pointTemp);
	Vector3 point = Math::BtVector3ToVector3(pointTemp);
	delete pointTemp;
	return point;
}

void ConeTwistConstraint::SetLimit(btScalar _swingSpan1, btScalar _swingSpan2,
	btScalar _twistSpan, btScalar _softness, btScalar _biasFactor, btScalar _relaxationFactor)
{
	UnmanagedPointer->setLimit(_swingSpan1, _swingSpan2, _twistSpan, _softness,
		_biasFactor, _relaxationFactor);
}

void ConeTwistConstraint::SetLimit(btScalar _swingSpan1, btScalar _swingSpan2,
	btScalar _twistSpan, btScalar _softness, btScalar _biasFactor)
{
	UnmanagedPointer->setLimit(_swingSpan1, _swingSpan2, _twistSpan, _softness, _biasFactor);
}

void ConeTwistConstraint::SetLimit(btScalar _swingSpan1, btScalar _swingSpan2,
	btScalar _twistSpan, btScalar _softness)
{
	UnmanagedPointer->setLimit(_swingSpan1, _swingSpan2, _twistSpan, _softness);
}

void ConeTwistConstraint::SetLimit(btScalar _swingSpan1, btScalar _swingSpan2, btScalar _twistSpan)
{
	UnmanagedPointer->setLimit(_swingSpan1, _swingSpan2, _twistSpan);
}

void ConeTwistConstraint::SetLimit(int limitIndex, btScalar limitValue)
{
	UnmanagedPointer->setLimit(limitIndex, limitValue);
}

void ConeTwistConstraint::SetMaxMotorImpulse(btScalar maxMotorImpulse)
{
	UnmanagedPointer->setMaxMotorImpulse(maxMotorImpulse);
}

void ConeTwistConstraint::SetMaxMotorImpulseNormalized(btScalar maxMotorImpulse)
{
	UnmanagedPointer->setMaxMotorImpulseNormalized(maxMotorImpulse);
}

void ConeTwistConstraint::SetMotorTarget(Quaternion q)
{
	btQuaternion* qTemp = Math::QuaternionToBtQuat(q);
	UnmanagedPointer->setMotorTarget(*qTemp);
	delete qTemp;
}

void ConeTwistConstraint::SetMotorTargetInConstraintSpace(Quaternion q)
{
	btQuaternion* qTemp = Math::QuaternionToBtQuat(q);
	UnmanagedPointer->setMotorTargetInConstraintSpace(*qTemp);
	delete qTemp;
}

void ConeTwistConstraint::UpdateRHS(btScalar timeStep)
{
	UnmanagedPointer->updateRHS(timeStep);
}

Matrix ConeTwistConstraint::AFrame::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getAFrame());
}

Matrix ConeTwistConstraint::BFrame::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getBFrame());
}

btScalar ConeTwistConstraint::FixThresh::get()
{
	return UnmanagedPointer->getFixThresh();
}
void ConeTwistConstraint::FixThresh::set(btScalar value)
{
	UnmanagedPointer->setFixThresh(value);
}

Matrix ConeTwistConstraint::FrameOffsetA::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getFrameOffsetA());
}

Matrix ConeTwistConstraint::FrameOffsetB::get()
{
	return Math::BtTransformToMatrix(&UnmanagedPointer->getFrameOffsetB());
}

bool ConeTwistConstraint::IsPastSwingLimit::get()
{
	return UnmanagedPointer->isPastSwingLimit();
}

int ConeTwistConstraint::SolveSwingLimit::get()
{
	return UnmanagedPointer->getSolveSwingLimit();
}

int ConeTwistConstraint::SolveTwistLimit::get()
{
	return UnmanagedPointer->getSolveTwistLimit();
}

btScalar ConeTwistConstraint::SwingSpan1::get()
{
	return UnmanagedPointer->getSwingSpan1();
}

btScalar ConeTwistConstraint::SwingSpan2::get()
{
	return UnmanagedPointer->getSwingSpan2();
}

btScalar ConeTwistConstraint::TwistAngle::get()
{
	return UnmanagedPointer->getTwistAngle();
}

btScalar ConeTwistConstraint::TwistLimitSign::get()
{
	return UnmanagedPointer->getTwistLimitSign();
}

btScalar ConeTwistConstraint::TwistSpan::get()
{
	return UnmanagedPointer->getTwistSpan();
}

btConeTwistConstraint* ConeTwistConstraint::UnmanagedPointer::get()
{
	return (btConeTwistConstraint*)TypedConstraint::UnmanagedPointer;
}

#endif
