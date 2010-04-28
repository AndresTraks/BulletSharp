#include "StdAfx.h"

#ifndef DISABLE_CONSTRAINTS

#include "HingeConstraint.h"
#include "RigidBody.h"

HingeConstraint::HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Vector3 pivotInA, Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB, bool useReferenceFrameA)
: TypedConstraint(0)
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;

	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);
	btVector3* pivotInBTemp = Math::Vector3ToBtVector3(pivotInB);
	btVector3* axisInATemp = Math::Vector3ToBtVector3(axisInA);
	btVector3* axisInBTemp = Math::Vector3ToBtVector3(axisInB);

	UnmanagedPointer = new btHingeConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
		*pivotInATemp, *pivotInBTemp, *axisInATemp, *axisInBTemp, useReferenceFrameA);

	delete pivotInATemp;
	delete pivotInBTemp;
	delete axisInATemp;
	delete axisInBTemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Vector3 pivotInA, Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB)
: TypedConstraint(0)
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;

	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);
	btVector3* pivotInBTemp = Math::Vector3ToBtVector3(pivotInB);
	btVector3* axisInATemp = Math::Vector3ToBtVector3(axisInA);
	btVector3* axisInBTemp = Math::Vector3ToBtVector3(axisInB);

	UnmanagedPointer = new btHingeConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
		*pivotInATemp, *pivotInBTemp, *axisInATemp, *axisInBTemp);

	delete pivotInATemp;
	delete pivotInBTemp;
	delete axisInATemp;
	delete axisInBTemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, Vector3 pivotInA, Vector3 axisInA,
	bool useReferenceFrameA)
: TypedConstraint(0)
{
	this->RigidBodyA = rbA;

	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);
	btVector3* axisInATemp = Math::Vector3ToBtVector3(axisInA);

	UnmanagedPointer = new btHingeConstraint(*rbA->UnmanagedPointer, *pivotInATemp, *axisInATemp, useReferenceFrameA);

	delete pivotInATemp;
	delete axisInATemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, Vector3 pivotInA, Vector3 axisInA)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer,
	*Math::Vector3ToBtVector3(pivotInA), *Math::Vector3ToBtVector3(axisInA)))
{
	this->RigidBodyA = rbA;

	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);
	btVector3* axisInATemp = Math::Vector3ToBtVector3(axisInA);

	UnmanagedPointer = new btHingeConstraint(*rbA->UnmanagedPointer, *pivotInATemp, *axisInATemp);

	delete pivotInATemp;
	delete axisInATemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Matrix rbAFrame, Matrix rbBFrame, bool useReferenceFrameA)
: TypedConstraint(0)
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;

	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);
	btTransform* rbBFrameTemp = Math::MatrixToBtTransform(rbBFrame);

	UnmanagedPointer = new btHingeConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
		*rbAFrameTemp, *rbBFrameTemp, useReferenceFrameA);

	delete rbAFrameTemp;
	delete rbBFrameTemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix rbAFrame, Matrix rbBFrame)
: TypedConstraint(0)
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;

	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);
	btTransform* rbBFrameTemp = Math::MatrixToBtTransform(rbBFrame);

	UnmanagedPointer = new btHingeConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
		*rbAFrameTemp, *rbBFrameTemp);

	delete rbAFrameTemp;
	delete rbBFrameTemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, Matrix rbAFrame, bool useReferenceFrameA)
: TypedConstraint(0)
{
	this->RigidBodyA = rbA;

	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);

	UnmanagedPointer = new btHingeConstraint(*rbA->UnmanagedPointer, *rbAFrameTemp, useReferenceFrameA);

	delete rbAFrameTemp;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, Matrix rbAFrame)
: TypedConstraint(0)
{
	this->RigidBodyA = rbA;

	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);

	UnmanagedPointer = new btHingeConstraint(*rbA->UnmanagedPointer, *rbAFrameTemp);

	delete rbAFrameTemp;
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
