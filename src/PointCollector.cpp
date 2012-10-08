#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "PointCollector.h"

#define Unmanaged static_cast<btPointCollector*>(_unmanaged)

PointCollector::PointCollector()
: DiscreteCollisionDetectorInterface::Result(new btPointCollector)
{
}

btScalar PointCollector::Distance::get()
{
	return Unmanaged->m_distance;
}
void PointCollector::Distance::set(btScalar value)
{
	Unmanaged->m_distance = value;
}

bool PointCollector::HasResult::get()
{
	return Unmanaged->m_hasResult;
}
void PointCollector::HasResult::set(bool value)
{
	Unmanaged->m_hasResult = value;
}

Vector3 PointCollector::NormalOnBInWorld::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->m_normalOnBInWorld);
}
void PointCollector::NormalOnBInWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Unmanaged->m_normalOnBInWorld);
}

Vector3 PointCollector::PointInWorld::get()
{
	return Math::BtVector3ToVector3(&Unmanaged->m_pointInWorld);
}
void PointCollector::PointInWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Unmanaged->m_pointInWorld);
}

#endif
