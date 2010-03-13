#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "HingeConstraint.h"
#include "RigidBody.h"

HingeConstraint::HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Vector3 pivotInA, Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB, bool useReferenceFrameA)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
	*Math::Vector3ToBtVector3(pivotInA), *Math::Vector3ToBtVector3(pivotInB),
	*Math::Vector3ToBtVector3(axisInA), *Math::Vector3ToBtVector3(axisInB),
	useReferenceFrameA))
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Vector3 pivotInA, Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
	*Math::Vector3ToBtVector3(pivotInA), *Math::Vector3ToBtVector3(pivotInB),
	*Math::Vector3ToBtVector3(axisInA), *Math::Vector3ToBtVector3(axisInB)))
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, Vector3 pivotInA, Vector3 axisInA,
	bool useReferenceFrameA)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer,
	*Math::Vector3ToBtVector3(pivotInA), *Math::Vector3ToBtVector3(axisInA),
	useReferenceFrameA))
{
	this->RigidBodyA = rbA;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, Vector3 pivotInA, Vector3 axisInA)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer,
	*Math::Vector3ToBtVector3(pivotInA), *Math::Vector3ToBtVector3(axisInA)))
{
	this->RigidBodyA = rbA;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Matrix rbAFrame, Matrix rbBFrame, bool useReferenceFrameA)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
	*Math::MatrixToBtTransform(rbAFrame), *Math::MatrixToBtTransform(rbBFrame), useReferenceFrameA))
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Matrix rbAFrame, Matrix rbBFrame)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
	*Math::MatrixToBtTransform(rbAFrame), *Math::MatrixToBtTransform(rbBFrame)))
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, Matrix rbAFrame, bool useReferenceFrameA)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer,	*Math::MatrixToBtTransform(rbAFrame), useReferenceFrameA))
{
	this->RigidBodyA = rbA;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, Matrix rbAFrame)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer, *Math::MatrixToBtTransform(rbAFrame)))
{
	this->RigidBodyA = rbA;
}

void HingeConstraint::EnableAngularMotor(bool enableMotor,
	btScalar targetVelocity, btScalar maxMotorImpulse)
{
	UnmanagedPointer->enableAngularMotor(enableMotor, targetVelocity, maxMotorImpulse);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high,
	btScalar _softness, btScalar _biasFactor, btScalar _relaxationFactor)
{
	UnmanagedPointer->setLimit(low, high, _softness, _biasFactor, _relaxationFactor);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high,
	btScalar _softness, btScalar _biasFactor)
{
	UnmanagedPointer->setLimit(low, high, _softness, _biasFactor);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high, btScalar _softness)
{
	UnmanagedPointer->setLimit(low, high, _softness);
}

void HingeConstraint::SetLimit(btScalar low, btScalar high)
{
	UnmanagedPointer->setLimit(low, high);
}

btHingeConstraint* HingeConstraint::UnmanagedPointer::get()
{
	return (btHingeConstraint*)TypedConstraint::UnmanagedPointer;
}

#endif
