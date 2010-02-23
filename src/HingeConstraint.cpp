#include "StdAfx.h"

#include "HingeConstraint.h"

HingeConstraint::HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Vector3 pivotInA, Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB, bool useReferenceFrameA)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
	*Math::Vector3ToBtVec3(pivotInA), *Math::Vector3ToBtVec3(pivotInB),
	*Math::Vector3ToBtVec3(axisInA), *Math::Vector3ToBtVec3(axisInB),
	useReferenceFrameA))
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Vector3 pivotInA, Vector3 pivotInB, Vector3 axisInA, Vector3 axisInB)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
	*Math::Vector3ToBtVec3(pivotInA), *Math::Vector3ToBtVec3(pivotInB),
	*Math::Vector3ToBtVec3(axisInA), *Math::Vector3ToBtVec3(axisInB)))
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, Vector3 pivotInA, Vector3 axisInA,
	bool useReferenceFrameA)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer,
	*Math::Vector3ToBtVec3(pivotInA), *Math::Vector3ToBtVec3(axisInA),
	useReferenceFrameA))
{
	this->RigidBodyA = rbA;
}

HingeConstraint::HingeConstraint(RigidBody^ rbA, Vector3 pivotInA, Vector3 axisInA)
: TypedConstraint(new btHingeConstraint(*rbA->UnmanagedPointer,
	*Math::Vector3ToBtVec3(pivotInA), *Math::Vector3ToBtVec3(axisInA)))
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
