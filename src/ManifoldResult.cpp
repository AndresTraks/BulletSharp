#include "StdAfx.h"

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "ManifoldResult.h"
#include "PersistentManifold.h"

#define Native static_cast<btManifoldResult*>(_native)

ManifoldResult::ManifoldResult()
: DiscreteCollisionDetectorInterface::Result(0)
{
	_native = ALIGNED_NEW(btManifoldResult) ();
}

ManifoldResult::ManifoldResult(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
: DiscreteCollisionDetectorInterface::Result(
	new btManifoldResult(body0Wrap->_native, body1Wrap->_native))
{
}

btScalar ManifoldResult::CalculateCombinedFriction(CollisionObject^ body0, CollisionObject^ body1)
{
	return btManifoldResult::calculateCombinedFriction(body0->_native, body1->_native);
}

btScalar ManifoldResult::CalculateCombinedRestitution(CollisionObject^ body0, CollisionObject^ body1)
{
	return btManifoldResult::calculateCombinedRestitution(body0->_native, body1->_native);
}

CollisionObject^ ManifoldResult::Body0Internal::get()
{
	const btCollisionObject* body0 = Native->getBody0Internal();
	return CollisionObject::GetManaged((btCollisionObject*)body0);
}

CollisionObject^ ManifoldResult::Body1Internal::get()
{
	const btCollisionObject* body1 = Native->getBody1Internal();
	return CollisionObject::GetManaged((btCollisionObject*)body1);
}

CollisionObjectWrapper^ ManifoldResult::Body0Wrap::get()
{
	return gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)Native->getBody0Wrap());
}

CollisionObjectWrapper^ ManifoldResult::Body1Wrap::get()
{
	return gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)Native->getBody1Wrap());
}

PersistentManifold^ ManifoldResult::PersistentManifold::get()
{
	return gcnew BulletSharp::PersistentManifold(Native->getPersistentManifold());
}
void ManifoldResult::PersistentManifold::set(BulletSharp::PersistentManifold^ value)
{
	Native->setPersistentManifold((btPersistentManifold*)GetUnmanagedNullable(value));
}
