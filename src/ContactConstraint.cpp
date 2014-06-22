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

ContactConstraint::ContactConstraint(PersistentManifold^ contactManifold, RigidBody^ rigidBodyA, RigidBody^ rigidBodyB)
: TypedConstraint(new btContactConstraint(contactManifold->_native, *rigidBodyA->_native, *rigidBodyB->_native))
{
}

#endif
#endif
