#include "StdAfx.h"

#include "ConeTwistConstraint.h"
#include "RigidBody.h"

ConeTwistConstraint::ConeTwistConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Matrix rbAFrame, Matrix rbBFrame)
: TypedConstraint(new btConeTwistConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
	*Math::MatrixToBtTransform(rbAFrame), *Math::MatrixToBtTransform(rbBFrame)))
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;
}

ConeTwistConstraint::ConeTwistConstraint(RigidBody^ rbA, Matrix rbAFrame)
: TypedConstraint(new btConeTwistConstraint(*rbA->UnmanagedPointer,	*Math::MatrixToBtTransform(rbAFrame)))
{
	this->RigidBodyA = rbA;
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
