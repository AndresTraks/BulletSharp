#include "StdAfx.h"

#include "CollisionObject.h"
#include "ManifoldResult.h"
#include "PersistentManifold.h"

ManifoldResult::ManifoldResult()
: DiscreteCollisionDetectorInterface::Result(new btManifoldResult())
{
}

ManifoldResult::ManifoldResult(BulletSharp::CollisionObject ^body0, BulletSharp::CollisionObject ^body1)
: DiscreteCollisionDetectorInterface::Result(
	new btManifoldResult(body0->UnmanagedPointer, body1->UnmanagedPointer))
{
}

CollisionObject^ ManifoldResult::Body0Internal::get()
{
	const btCollisionObject* body0 = UnmanagedPointer->getBody0Internal();
	if (body0 == 0)
		return nullptr;
	return gcnew CollisionObject((btCollisionObject*)body0);
}

CollisionObject^ ManifoldResult::Body1Internal::get()
{
	const btCollisionObject* body1 = UnmanagedPointer->getBody1Internal();
	if (body1 == 0)
		return nullptr;
	return gcnew CollisionObject((btCollisionObject*)body1);
}

PersistentManifold^ ManifoldResult::PersistentManifold::get()
{
	return gcnew BulletSharp::PersistentManifold(UnmanagedPointer->getPersistentManifold());
}
void ManifoldResult::PersistentManifold::set(BulletSharp::PersistentManifold^ value)
{
	UnmanagedPointer->setPersistentManifold(value->UnmanagedPointer);
}

btManifoldResult* ManifoldResult::UnmanagedPointer::get()
{
	return (btManifoldResult*)DiscreteCollisionDetectorInterface::Result::UnmanagedPointer;
}