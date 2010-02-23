#include "StdAfx.h"

#include "Point2PointConstraint.h"

Point2PointConstraint::Point2PointConstraint(RigidBody^ rbA, RigidBody^ rbB, Vector3 pivotInA, Vector3 pivotInB)
: TypedConstraint(new btPoint2PointConstraint(*rbA->UnmanagedPointer, *rbB->UnmanagedPointer,
	*Math::Vector3ToBtVec3(pivotInA), *Math::Vector3ToBtVec3(pivotInB)))
{
	this->RigidBodyA = rbA;
	this->RigidBodyB = rbB;
}

Point2PointConstraint::Point2PointConstraint(RigidBody^ rbA, Vector3 pivotInA)
: TypedConstraint(new btPoint2PointConstraint(*rbA->UnmanagedPointer, *Math::Vector3ToBtVec3(pivotInA)))
{
	this->RigidBodyA = rbA;
}

int Point2PointConstraint::CalculateSerializeBufferSize()
{
	return UnmanagedPointer->calculateSerializeBufferSize();
}

btScalar Point2PointConstraint::GetParam(int num, int axis)
{
	return UnmanagedPointer->getParam(num, axis);
}

btScalar Point2PointConstraint::GetParam(int num)
{
	return UnmanagedPointer->getParam(num);
}

void Point2PointConstraint::SetParam(int num, btScalar value, int axis)
{
	UnmanagedPointer->setParam(num, value, axis);
}

void Point2PointConstraint::SetParam(int num, btScalar value)
{
	UnmanagedPointer->setParam(num, value);
}

Vector3 Point2PointConstraint::PivotInA::get()
{
	return Math::BtVec3ToVector3(&UnmanagedPointer->getPivotInA());
}

void Point2PointConstraint::PivotInA::set(Vector3 value)
{
	UnmanagedPointer->setPivotA(*Math::Vector3ToBtVec3(value));
}

Vector3 Point2PointConstraint::PivotInB::get()
{
	return Math::BtVec3ToVector3(&UnmanagedPointer->getPivotInB());
}

void Point2PointConstraint::PivotInB::set(Vector3 value)
{
	UnmanagedPointer->setPivotB(*Math::Vector3ToBtVec3(value));
}

void Point2PointConstraint::UpdateRHS(btScalar timeStep)
{
	UnmanagedPointer->updateRHS(timeStep);
}

btPoint2PointConstraint* Point2PointConstraint::UnmanagedPointer::get()
{
	return (btPoint2PointConstraint*)TypedConstraint::UnmanagedPointer;
}
