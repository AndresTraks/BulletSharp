#include "StdAfx.h"

#ifndef DISABLE_GIMPACT

#include "BoxCollision.h"

Aabb::Aabb(btAABB* aabb)
{
	_native = aabb;
}

Vector3 Aabb::Max::get()
{
	return Math::BtVector3ToVector3(&_native->m_max);
}
void Aabb::Max::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_max);
}

Vector3 Aabb::Min::get()
{
	return Math::BtVector3ToVector3(&_native->m_min);
}
void Aabb::Min::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_min);
}

#endif
