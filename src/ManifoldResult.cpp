#include "StdAfx.h"

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "ManifoldResult.h"
#include "PersistentManifold.h"

ManifoldResult::ManifoldResult()
: DiscreteCollisionDetectorInterface::Result(new btManifoldResult())
{
}

ManifoldResult::ManifoldResult(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
: DiscreteCollisionDetectorInterface::Result(
	new btManifoldResult(body0Wrap->_unmanaged, body1Wrap->_unmanaged))
{
}

CollisionObject^ ManifoldResult::Body0Internal::get()
{
	const btCollisionObject* body0 = UnmanagedPointer->getBody0Internal();
	return CollisionObject::GetManaged((btCollisionObject*)body0);
}

CollisionObject^ ManifoldResult::Body1Internal::get()
{
	const btCollisionObject* body1 = UnmanagedPointer->getBody1Internal();
	return CollisionObject::GetManaged((btCollisionObject*)body1);
}

CollisionObjectWrapper^ ManifoldResult::Body0Wrap::get()
{
	return gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)UnmanagedPointer->getBody0Wrap());
}

CollisionObjectWrapper^ ManifoldResult::Body1Wrap::get()
{
	return gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)UnmanagedPointer->getBody1Wrap());
}

PersistentManifold^ ManifoldResult::PersistentManifold::get()
{
	return gcnew BulletSharp::PersistentManifold(UnmanagedPointer->getPersistentManifold());
}
void ManifoldResult::PersistentManifold::set(BulletSharp::PersistentManifold^ value)
{
	UnmanagedPointer->setPersistentManifold((btPersistentManifold*)GetUnmanagedNullable(value));
}

btManifoldResult* ManifoldResult::UnmanagedPointer::get()
{
	return (btManifoldResult*)DiscreteCollisionDetectorInterface::Result::UnmanagedPointer;
}