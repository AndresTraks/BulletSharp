#include "StdAfx.h"

#if 0
#ifndef DISABLE_CONSTRAINTS

#include "ContactConstraint.h"
#include "PersistentManifold.h"
#include "RigidBody.h"

ContactConstraint::ContactConstraint(btContactConstraint* native)
	: TypedConstraint(native)
{
}

PersistentManifold^ ContactConstraint::ContactManifold::get()
{
	return gcnew PersistentManifold(Native->getContactManifold());
}
void ContactConstraint::ContactManifold::set(PersistentManifold^ contactManifold)
{
	Native->setContactManifold((btPersistentManifold*)contactManifold->_native);
}

#endif
#endif
