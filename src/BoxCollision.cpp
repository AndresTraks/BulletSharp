#include "StdAfx.h"

#ifndef DISABLE_BVH

#include "BoxCollision.h"

Aabb::Aabb(btAABB* aabb)
{
	_aabb = aabb;
}

btAABB* Aabb::UnmanagedPointer::get()
{
	return _aabb;
}

#endif
