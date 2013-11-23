#include "StdAfx.h"

#ifndef DISABLE_FEATHERSTONE

#include "MultiBody.h"
#include "MultiBodyPoint2Point.h"
#include "RigidBody.h"

#define Native static_cast<btMultiBodyPoint2Point*>(_native)

MultiBodyPoint2Point::MultiBodyPoint2Point(btMultiBodyPoint2Point* native)
	: MultiBodyConstraint(native)
{
}

MultiBodyPoint2Point::MultiBodyPoint2Point(MultiBody^ body, int link, RigidBody^ bodyB, Vector3 pivotInA, Vector3 pivotInB)
	: MultiBodyConstraint(0)
{
	VECTOR3_DEF(pivotInA);
	VECTOR3_DEF(pivotInB);
	_native = new btMultiBodyPoint2Point(body->_native, link, (btRigidBody*)bodyB->_native, VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB));
	VECTOR3_DEL(pivotInB);
	VECTOR3_DEL(pivotInA);
}

MultiBodyPoint2Point::MultiBodyPoint2Point(MultiBody^ bodyA, int linkA, MultiBody^ bodyB, int linkB, Vector3 pivotInA, Vector3 pivotInB)
	: MultiBodyConstraint(0)
{
	VECTOR3_DEF(pivotInA);
	VECTOR3_DEF(pivotInB);
	_native = new btMultiBodyPoint2Point(bodyA->_native, linkA, bodyB->_native, linkB, VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB));
	VECTOR3_DEL(pivotInB);
	VECTOR3_DEL(pivotInA);
}

Vector3 MultiBodyPoint2Point::PivotInB::get()
{
	return Math::BtVector3ToVector3(&Native->getPivotInB());
}
void MultiBodyPoint2Point::PivotInB::set(Vector3 pivotInB)
{
	VECTOR3_DEF(pivotInB);
	Native->setPivotInB(VECTOR3_USE(pivotInB));
	VECTOR3_DEL(pivotInB);
}

#endif
