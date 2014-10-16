#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "PointCollector.h"

#define Native static_cast<btPointCollector*>(_native)

PointCollector::PointCollector()
	: Result(ALIGNED_NEW(btPointCollector)())
{
}

void PointCollector::AddContactPoint(Vector3 normalOnBInWorld, Vector3 pointInWorld,
	btScalar depth)
{
	VECTOR3_CONV(normalOnBInWorld);
	VECTOR3_CONV(pointInWorld);
	_native->addContactPoint(VECTOR3_USE(normalOnBInWorld), VECTOR3_USE(pointInWorld),
		depth);
	VECTOR3_DEL(normalOnBInWorld);
	VECTOR3_DEL(pointInWorld);
}

void PointCollector::SetShapeIdentifiersA(int partId0, int index0)
{
	_native->setShapeIdentifiersA(partId0, index0);
}

void PointCollector::SetShapeIdentifiersB(int partId1, int index1)
{
	_native->setShapeIdentifiersB(partId1, index1);
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
