#include "StdAfx.h"

#ifndef DISABLE_GIMPACT

#include "BoxCollision.h"

Aabb::Aabb(btAABB* aabb)
{
	_aabb = aabb;
}

Vector3 Aabb::Max::get()
{
	return Math::BtVector3ToVector3(&_aabb->m_max);
}
void Aabb::Max::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_aabb->m_max);
}

Vector3 Aabb::Min::get()
{
	return Math::BtVector3ToVector3(&_aabb->m_min);
}
void Aabb::Min::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_aabb->m_min);
}

btAABB* Aabb::UnmanagedPointer::get()
{
	return _aabb;
}

#endif
