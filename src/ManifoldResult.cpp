#include "StdAfx.h"

#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "ManifoldResult.h"
#include "PersistentManifold.h"

#define Unmanaged static_cast<btManifoldResult*>(_unmanaged)

ManifoldResult::ManifoldResult()
: DiscreteCollisionDetectorInterface::Result(new btManifoldResult())
{
}

ManifoldResult::ManifoldResult(CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
: DiscreteCollisionDetectorInterface::Result(
	new btManifoldResult(body0Wrap->_unmanaged, body1Wrap->_unmanaged))
{
}

btScalar ManifoldResult::CalculateCombinedFriction(CollisionObject^ body0, CollisionObject^ body1)
{
	return btManifoldResult::calculateCombinedFriction(body0->_unmanaged, body1->_unmanaged);
}

btScalar ManifoldResult::CalculateCombinedRestitution(CollisionObject^ body0, CollisionObject^ body1)
{
	return btManifoldResult::calculateCombinedRestitution(body0->_unmanaged, body1->_unmanaged);
}

CollisionObject^ ManifoldResult::Body0Internal::get()
{
	const btCollisionObject* body0 = Unmanaged->getBody0Internal();
	return CollisionObject::GetManaged((btCollisionObject*)body0);
}

CollisionObject^ ManifoldResult::Body1Internal::get()
{
	const btCollisionObject* body1 = Unmanaged->getBody1Internal();
	return CollisionObject::GetManaged((btCollisionObject*)body1);
}

CollisionObjectWrapper^ ManifoldResult::Body0Wrap::get()
{
	return gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)Unmanaged->getBody0Wrap());
}

CollisionObjectWrapper^ ManifoldResult::Body1Wrap::get()
{
	return gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)Unmanaged->getBody1Wrap());
}

PersistentManifold^ ManifoldResult::PersistentManifold::get()
{
	return gcnew BulletSharp::PersistentManifold(Unmanaged->getPersistentManifold());
}
void ManifoldResult::PersistentManifold::set(BulletSharp::PersistentManifold^ value)
{
	Unmanaged->setPersistentManifold((btPersistentManifold*)GetUnmanagedNullable(value));
}
