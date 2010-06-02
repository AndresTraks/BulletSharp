#include "StdAfx.h"

#if 0
#ifndef DISABLE_CONSTRAINTS

#include "ContactConstraint.h"
#include "PersistentManifold.h"
#include "RigidBody.h"

ContactConstraint::ContactConstraint(btContactConstraint* constraint)
: TypedConstraint(constraint)
{
}

ContactConstraint::ContactConstraint(PersistentManifold^ contactManifold, RigidBody^ rbA, RigidBody^ rbB)
: TypedConstraint(new btContactConstraint(contactManifold->UnmanagedPointer, *rbA->UnmanagedPointer, *rbB->UnmanagedPointer))
{
}

#endif
#endif
