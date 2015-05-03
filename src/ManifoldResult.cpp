#include "StdAfx.h"

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "ManifoldResult.h"
#include "PersistentManifold.h"

#define Native static_cast<btManifoldResult*>(_native)

ManifoldResult::ManifoldResult()
	: DiscreteCollisionDetectorInterface::Result(ALIGNED_NEW(btManifoldResult)())
{
}

ManifoldResult::ManifoldResult(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
	: Result(new btManifoldResult(body0Wrap->_native, body1Wrap->_native))
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

void ManifoldResult::RefreshContactPoints()
{
	Native->refreshContactPoints();
}

CollisionObject^ ManifoldResult::Body0Internal::get()
{
	return CollisionObject::GetManaged((btCollisionObject*)Native->getBody0Internal());
}

CollisionObjectWrapper^ ManifoldResult::Body0Wrap::get()
{
	return gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)Native->getBody0Wrap());
}
void ManifoldResult::Body0Wrap::set(CollisionObjectWrapper^ obj0Wrap)
{
	Native->setBody0Wrap(obj0Wrap->_native);
}

CollisionObject^ ManifoldResult::Body1Internal::get()
{
	return CollisionObject::GetManaged((btCollisionObject*)Native->getBody1Internal());
}

CollisionObjectWrapper^ ManifoldResult::Body1Wrap::get()
{
	return gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)Native->getBody1Wrap());
}
void ManifoldResult::Body1Wrap::set(CollisionObjectWrapper^ obj1Wrap)
{
	Native->setBody1Wrap(obj1Wrap->_native);
}

PersistentManifold ManifoldResult::PersistentManifold::get()
{
	return BulletSharp::PersistentManifold(Native->getPersistentManifold());
}
void ManifoldResult::PersistentManifold::set(BulletSharp::PersistentManifold manifold)
{
	Native->setPersistentManifold(manifold._native);
}
