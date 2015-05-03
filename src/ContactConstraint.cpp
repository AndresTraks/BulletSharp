#include "StdAfx.h"

#if 0
#ifndef DISABLE_CONSTRAINTS

#include "ContactConstraint.h"
#include "PersistentManifold.h"
#include "RigidBody.h"

#define Native static_cast<btContactConstraint*>(_native)

PersistentManifold ContactConstraint::ContactManifold::get()
{
	return PersistentManifold(Native->getContactManifold());
}
void ContactConstraint::ContactManifold::set(PersistentManifold contactManifold)
{
	Native->setContactManifold(contactManifold._native);
}

#endif
#endif
