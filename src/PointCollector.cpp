#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletCollision/NarrowPhaseCollision/btPointCollector.h>
#pragma managed(pop)

#include "PointCollector.h"

PointCollector::PointCollector()
: DiscreteCollisionDetectorInterface::Result(new btPointCollector)
{
}

btScalar PointCollector::Distance::get()
{
	return UnmanagedPointer->m_distance;
}
void PointCollector::Distance::set(btScalar value)
{
	UnmanagedPointer->m_distance = value;
}

bool PointCollector::HasResult::get()
{
	return UnmanagedPointer->m_hasResult;
}
void PointCollector::HasResult::set(bool value)
{
	UnmanagedPointer->m_hasResult = value;
}

Vector3 PointCollector::NormalOnBInWorld::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_normalOnBInWorld);
}
void PointCollector::NormalOnBInWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_normalOnBInWorld);
}

Vector3 PointCollector::PointInWorld::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_pointInWorld);
}
void PointCollector::PointInWorld::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_pointInWorld);
}

btPointCollector* PointCollector::UnmanagedPointer::get()
{
	return (btPointCollector*) DiscreteCollisionDetectorInterface::Result::UnmanagedPointer;
}
