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

MultiBodyPoint2Point::MultiBodyPoint2Point(MultiBody^ body, int link, RigidBody^ bodyB,
	Vector3 pivotInA, Vector3 pivotInB)
	: MultiBodyConstraint(0)
{
	VECTOR3_CONV(pivotInA);
	VECTOR3_CONV(pivotInB);
	_native = new btMultiBodyPoint2Point(body->_native, link, (btRigidBody*)GetUnmanagedNullable(bodyB),
		VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB));
	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);

	_multiBodyA = body;
}

MultiBodyPoint2Point::MultiBodyPoint2Point(MultiBody^ bodyA, int linkA, MultiBody^ bodyB,
	int linkB, Vector3 pivotInA, Vector3 pivotInB)
	: MultiBodyConstraint(0)
{
	VECTOR3_CONV(pivotInA);
	VECTOR3_CONV(pivotInB);
	_native = new btMultiBodyPoint2Point(bodyA->_native, linkA, bodyB->_native, linkB,
		VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB));
	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);

	_multiBodyA = bodyA;
	_multiBodyB = bodyB;
}

#ifndef DISABLE_DEBUGDRAW
void MultiBodyPoint2Point::DebugDraw(IDebugDraw^ drawer)
{
	// TODO
}
#endif

Vector3 MultiBodyPoint2Point::PivotInB::get()
{
	return Math::BtVector3ToVector3(&Native->getPivotInB());
}
void MultiBodyPoint2Point::PivotInB::set(Vector3 pivotInB)
{
	VECTOR3_CONV(pivotInB);
	Native->setPivotInB(VECTOR3_USE(pivotInB));
	VECTOR3_DEL(pivotInB);
}

#endif
