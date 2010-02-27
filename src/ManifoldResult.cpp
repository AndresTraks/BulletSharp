#include "StdAfx.h"

#include "CollisionObject.h"
#include "ManifoldResult.h"

ManifoldResult::ManifoldResult()
: DiscreteCollisionDetectorInterface::Result(new btManifoldResult())
{
}

ManifoldResult::ManifoldResult(BulletSharp::CollisionObject ^body0, BulletSharp::CollisionObject ^body1)
: DiscreteCollisionDetectorInterface::Result(
	new btManifoldResult(body0->UnmanagedPointer, body1->UnmanagedPointer))
{
}

btManifoldResult* ManifoldResult::UnmanagedPointer::get()
{
	return (btManifoldResult*)DiscreteCollisionDetectorInterface::Result::UnmanagedPointer;
}