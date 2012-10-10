#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "PointCollector.h"

#define Native static_cast<btPointCollector*>(_native)

PointCollector::PointCollector()
: DiscreteCollisionDetectorInterface::Result(new btPointCollector)
{
}

btScalar PointCollector::Distance::get()
{
	return Native->m_distance;
}
void PointCollector::Distance::set(btScalar value)
{
	Native->m_distance = value;
}

bool PointCollector::HasResult::get()
{
	return Native->m_hasResult;
}
void PointCollector::HasResult::set(bool value)
{
	Native->m_hasResult = value;
}

Vector3 PointCollector::NormalOnBInWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_normalOnBInWorld);
}
void PointCollector::NormalOnBInWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_normalOnBInWorld);
}

Vector3 PointCollector::PointInWorld::get()
{
	return Math::BtVector3ToVector3(&Native->m_pointInWorld);
}
void PointCollector::PointInWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_pointInWorld);
}

#endif
