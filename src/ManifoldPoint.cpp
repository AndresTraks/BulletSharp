#include "StdAfx.h"

#include "ManifoldPoint.h"

ManifoldPoint::ManifoldPoint(btManifoldPoint* point)
{
	_point = point;
}

ManifoldPoint::ManifoldPoint()
{
	_point = new btManifoldPoint();
}

ManifoldPoint::ManifoldPoint(Vector3 pointA, Vector3 pointB, Vector3 normal, btScalar distance)
{
	btVector3* pointATemp = Math::Vector3ToBtVector3(pointA);
	btVector3* pointBTemp = Math::Vector3ToBtVector3(pointB);
	btVector3* normalTemp = Math::Vector3ToBtVector3(normal);

	_point = new btManifoldPoint(*pointATemp, *pointBTemp, *normalTemp, distance);

	delete pointATemp;
	delete pointBTemp;
	delete normalTemp;
}

btScalar ManifoldPoint::AppliedImpulse::get()
{
	return _point->getAppliedImpulse();
}
void ManifoldPoint::AppliedImpulse::set(btScalar value)
{
	_point->m_appliedImpulse = value;
}

btScalar ManifoldPoint::CombinedFriction::get()
{
	return _point->m_combinedFriction;
}
void ManifoldPoint::CombinedFriction::set(btScalar value)
{
	_point->m_combinedFriction = value;
}

btScalar ManifoldPoint::CombinedRestitution::get()
{
	return _point->m_combinedRestitution;
}
void ManifoldPoint::CombinedRestitution::set(btScalar value)
{
	_point->m_combinedRestitution = value;
}

btScalar ManifoldPoint::ContactCfm1::get()
{
	return _point->m_contactCFM1;
}
void ManifoldPoint::ContactCfm1::set(btScalar value)
{
	_point->m_contactCFM1 = value;
}

btScalar ManifoldPoint::ContactCfm2::get()
{
	return _point->m_contactCFM2;
}
void ManifoldPoint::ContactCfm2::set(btScalar value)
{
	_point->m_contactCFM2 = value;
}

btScalar ManifoldPoint::ContactMotion1::get()
{
	return _point->m_contactMotion1;
}
void ManifoldPoint::ContactMotion1::set(btScalar value)
{
	_point->m_contactMotion1 = value;
}

btScalar ManifoldPoint::ContactMotion2::get()
{
	return _point->m_contactMotion2;
}
void ManifoldPoint::ContactMotion2::set(btScalar value)
{
	_point->m_contactMotion2 = value;
}

btScalar ManifoldPoint::Distance::get()
{
	return _point->getDistance();
}
void ManifoldPoint::Distance::set(btScalar value)
{
	_point->setDistance(value);
}

btScalar ManifoldPoint::Distance1::get()
{
	return _point->m_distance1;
}
void ManifoldPoint::Distance1::set(btScalar value)
{
	_point->m_distance1 = value;
}

int ManifoldPoint::Index0::get()
{
	return _point->m_index0;
}
void ManifoldPoint::Index0::set(int value)
{
	_point->m_index0 = value;
}

int ManifoldPoint::Index1::get()
{
	return _point->m_index1;
}
void ManifoldPoint::Index1::set(int value)
{
	_point->m_index1 = value;
}

Vector3 ManifoldPoint::LateralFrictionDir1::get()
{
	return Math::BtVector3ToVector3(&_point->m_lateralFrictionDir1);
}
void ManifoldPoint::LateralFrictionDir1::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_point->m_lateralFrictionDir1);
}

Vector3 ManifoldPoint::LateralFrictionDir2::get()
{
	return Math::BtVector3ToVector3(&_point->m_lateralFrictionDir2);
}
void ManifoldPoint::LateralFrictionDir2::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_point->m_lateralFrictionDir2);
}

bool ManifoldPoint::LateralFrictionInitialized::get()
{
	return _point->m_lateralFrictionInitialized;
}
void ManifoldPoint::LateralFrictionInitialized::set(bool value)
{
	_point->m_lateralFrictionInitialized = value;
}

int ManifoldPoint::LifeTime::get()
{
	return _point->getLifeTime();
}
void ManifoldPoint::LifeTime::set(int value)
{
	_point->m_lifeTime = value;
}

Vector3 ManifoldPoint::LocalPointA::get()
{
	return Math::BtVector3ToVector3(&_point->m_localPointA);
}
void ManifoldPoint::LocalPointA::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_point->m_localPointA);
}

Vector3 ManifoldPoint::LocalPointB::get()
{
	return Math::BtVector3ToVector3(&_point->m_localPointB);
}
void ManifoldPoint::LocalPointB::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_point->m_localPointB);
}

Vector3 ManifoldPoint::NormalWorldOnB::get()
{
	return Math::BtVector3ToVector3(&_point->m_normalWorldOnB);
}
void ManifoldPoint::NormalWorldOnB::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_point->m_normalWorldOnB);
}

int ManifoldPoint::PartId0::get()
{
	return _point->m_partId0;
}
void ManifoldPoint::PartId0::set(int value)
{
	_point->m_partId0 = value;
}

int ManifoldPoint::PartId1::get()
{
	return _point->m_partId1;
}
void ManifoldPoint::PartId1::set(int value)
{
	_point->m_partId1 = value;
}

Vector3 ManifoldPoint::PositionWorldOnA::get()
{
	return Math::BtVector3ToVector3(&_point->getPositionWorldOnA());
}
void ManifoldPoint::PositionWorldOnA::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_point->m_positionWorldOnA);
}

Vector3 ManifoldPoint::PositionWorldOnB::get()
{
	return Math::BtVector3ToVector3(&_point->getPositionWorldOnB());
}
void ManifoldPoint::PositionWorldOnB::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_point->m_positionWorldOnB);
}

Object^ ManifoldPoint::UserPersistentData::get()
{
	void* obj = _point->m_userPersistentData;
	if (obj == nullptr)
		return nullptr;
	return static_cast<Object^>(VoidPtrToGCHandle(obj).Target);
}
void ManifoldPoint::UserPersistentData::set(Object^ value)
{
	void* obj = _point->m_userPersistentData;
	if (obj != nullptr)
		VoidPtrToGCHandle(obj).Free();

	GCHandle handle = GCHandle::Alloc(value);
	_point->m_userPersistentData = GCHandleToVoidPtr(handle);
}

btManifoldPoint* ManifoldPoint::UnmanagedPointer::get()
{
	return _point;
}
void ManifoldPoint::UnmanagedPointer::set(btManifoldPoint* value)
{
	_point = value;
}
