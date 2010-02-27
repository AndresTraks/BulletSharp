#include "StdAfx.h"

#include "PersistentManifold.h"

PersistentManifold::PersistentManifold(btPersistentManifold* manifold)
: TypedObject(manifold)
{
}

PersistentManifold::PersistentManifold()
: TypedObject(new btPersistentManifold())
{
}

btPersistentManifold* PersistentManifold::UnmanagedPointer::get()
{
	return (btPersistentManifold*)TypedObject::UnmanagedPointer;
}
