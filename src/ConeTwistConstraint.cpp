#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "ConeTwistConstraint.h"
#include "RigidBody.h"

ConeTwistConstraint::ConeTwistConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Matrix rbAFrame, Matrix rbBFrame)
: TypedConstraint(0)
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;

	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);
	btTransform* rbBFrameTemp = Math::MatrixToBtTransform(rbBFrame);

	UnmanagedPointer = new btConeTwistConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer, *rbAFrameTemp, *rbBFrameTemp);

	delete rbAFrameTemp;
	delete rbBFrameTemp;
}

ConeTwistConstraint::ConeTwistConstraint(RigidBody^ rbA, Matrix rbAFrame)
: TypedConstraint(0)
{
	this->RigidBodyA = rbA;

	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);

	UnmanagedPointer = new btConeTwistConstraint(*rbA->UnmanagedPointer, *rbAFrameTemp);

	delete rbAFrameTemp;
}

void ConeTwistConstraint::CalcAngleInfo()
{
	UnmanagedPointer->calcAngleInfo();
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

btConeTwistConstraint* ConeTwistConstraint::UnmanagedPointer::get()
{
	return (btConeTwistConstraint*)TypedConstraint::UnmanagedPointer;
}

#endif
