#include "StdAfx.h"

#include "CollisionObjectWrapper.h"
#include "ManifoldPoint.h"

ManifoldPoint::ManifoldPoint(btManifoldPoint* point)
{
	_native = point;
}

#ifdef BT_CALLBACKS_ARE_EVENTS
bool onContactAdded(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap,
	int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	/*
	ContactAddedEventArgs^ args = gcnew ContactAddedEventArgs();
	args->ContactPoint = gcnew ManifoldPoint(&cp);
	args->CollisionObject0Wrapper = gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj0Wrap);
	args->PartID0 = partId0;
	args->Index0 = index0;
	args->CollisionObject1Wrapper = gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj1Wrap);
	args->PartID1 = partId1;
	args->Index1 = index1;
	ManifoldPoint::_contactAdded(nullptr, args);
	return args->IsContactModified;
	*/
	ManifoldPoint::_contactAdded(gcnew ManifoldPoint(&cp),
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj0Wrap), partId0, index0,
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj1Wrap), partId1, index1);
	return false;
}

void ManifoldPoint::ContactAdded::add(ContactAddedEventHandler^ callback)
{
	gContactAddedCallback = onContactAdded;
	_contactAdded += callback;
}
void ManifoldPoint::ContactAdded::remove(ContactAddedEventHandler^ callback)
{
	_contactAdded -= callback;
	if (!_contactAdded)
	{
		gContactAddedCallback = 0;
	}
}
#else
bool onContactAdded(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap,
	int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	return ManifoldPoint::_contactAdded(gcnew ManifoldPoint(&cp),
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj0Wrap), partId0, index0,
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj1Wrap), partId1, index1);
}

ContactAdded^ ManifoldPoint::ContactAdded::get()
{
	return _contactAdded;
}
void ManifoldPoint::ContactAdded::set(::ContactAdded^ value)
{
	if (value != nullptr)
	{
		_contactAdded = value;
		gContactAddedCallback = onContactAdded;
	}
	else
	{
		gContactAddedCallback = 0;
		_contactAdded = nullptr;
	}
}
#endif

ManifoldPoint::ManifoldPoint()
{
	_native = new btManifoldPoint();
}

ManifoldPoint::ManifoldPoint(Vector3 pointA, Vector3 pointB, Vector3 normal, btScalar distance)
{
	VECTOR3_DEF(pointA);
	VECTOR3_DEF(pointB);
	VECTOR3_DEF(normal);

	_native = new btManifoldPoint(VECTOR3_USE(pointA), VECTOR3_USE(pointB), VECTOR3_USE(normal), distance);

	VECTOR3_DEL(pointA);
	VECTOR3_DEL(pointB);
	VECTOR3_DEL(normal);
}

btScalar ManifoldPoint::AppliedImpulse::get()
{
	return _native->getAppliedImpulse();
}
void ManifoldPoint::AppliedImpulse::set(btScalar value)
{
	_native->m_appliedImpulse = value;
}

btScalar ManifoldPoint::CombinedFriction::get()
{
	return _native->m_combinedFriction;
}
void ManifoldPoint::CombinedFriction::set(btScalar value)
{
	_native->m_combinedFriction = value;
}

btScalar ManifoldPoint::CombinedRestitution::get()
{
	return _native->m_combinedRestitution;
}
void ManifoldPoint::CombinedRestitution::set(btScalar value)
{
	_native->m_combinedRestitution = value;
}

btScalar ManifoldPoint::CombinedRollingFriction::get()
{
	return _native->m_combinedRollingFriction;
}
void ManifoldPoint::CombinedRollingFriction::set(btScalar value)
{
	_native->m_combinedRollingFriction = value;
}

btScalar ManifoldPoint::ContactCfm1::get()
{
	return _native->m_contactCFM1;
}
void ManifoldPoint::ContactCfm1::set(btScalar value)
{
	_native->m_contactCFM1 = value;
}

btScalar ManifoldPoint::ContactCfm2::get()
{
	return _native->m_contactCFM2;
}
void ManifoldPoint::ContactCfm2::set(btScalar value)
{
	_native->m_contactCFM2 = value;
}

btScalar ManifoldPoint::ContactMotion1::get()
{
	return _native->m_contactMotion1;
}
void ManifoldPoint::ContactMotion1::set(btScalar value)
{
	_native->m_contactMotion1 = value;
}

btScalar ManifoldPoint::ContactMotion2::get()
{
	return _native->m_contactMotion2;
}
void ManifoldPoint::ContactMotion2::set(btScalar value)
{
	_native->m_contactMotion2 = value;
}

btScalar ManifoldPoint::Distance::get()
{
	return _native->getDistance();
}
void ManifoldPoint::Distance::set(btScalar value)
{
	_native->setDistance(value);
}

btScalar ManifoldPoint::Distance1::get()
{
	return _native->m_distance1;
}
void ManifoldPoint::Distance1::set(btScalar value)
{
	_native->m_distance1 = value;
}

int ManifoldPoint::Index0::get()
{
	return _native->m_index0;
}
void ManifoldPoint::Index0::set(int value)
{
	_native->m_index0 = value;
}

int ManifoldPoint::Index1::get()
{
	return _native->m_index1;
}
void ManifoldPoint::Index1::set(int value)
{
	_native->m_index1 = value;
}

Vector3 ManifoldPoint::LateralFrictionDir1::get()
{
	return Math::BtVector3ToVector3(&_native->m_lateralFrictionDir1);
}
void ManifoldPoint::LateralFrictionDir1::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_native->m_lateralFrictionDir1);
}

Vector3 ManifoldPoint::LateralFrictionDir2::get()
{
	return Math::BtVector3ToVector3(&_native->m_lateralFrictionDir2);
}
void ManifoldPoint::LateralFrictionDir2::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_native->m_lateralFrictionDir2);
}

bool ManifoldPoint::LateralFrictionInitialized::get()
{
	return _native->m_lateralFrictionInitialized;
}
void ManifoldPoint::LateralFrictionInitialized::set(bool value)
{
	_native->m_lateralFrictionInitialized = value;
}

int ManifoldPoint::LifeTime::get()
{
	return _native->getLifeTime();
}
void ManifoldPoint::LifeTime::set(int value)
{
	_native->m_lifeTime = value;
}

Vector3 ManifoldPoint::LocalPointA::get()
{
	return Math::BtVector3ToVector3(&_native->m_localPointA);
}
void ManifoldPoint::LocalPointA::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_native->m_localPointA);
}

Vector3 ManifoldPoint::LocalPointB::get()
{
	return Math::BtVector3ToVector3(&_native->m_localPointB);
}
void ManifoldPoint::LocalPointB::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_native->m_localPointB);
}

Vector3 ManifoldPoint::NormalWorldOnB::get()
{
	return Math::BtVector3ToVector3(&_native->m_normalWorldOnB);
}
void ManifoldPoint::NormalWorldOnB::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_native->m_normalWorldOnB);
}

int ManifoldPoint::PartId0::get()
{
	return _native->m_partId0;
}
void ManifoldPoint::PartId0::set(int value)
{
	_native->m_partId0 = value;
}

int ManifoldPoint::PartId1::get()
{
	return _native->m_partId1;
}
void ManifoldPoint::PartId1::set(int value)
{
	_native->m_partId1 = value;
}

Vector3 ManifoldPoint::PositionWorldOnA::get()
{
	return Math::BtVector3ToVector3(&_native->getPositionWorldOnA());
}
void ManifoldPoint::PositionWorldOnA::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_native->m_positionWorldOnA);
}

Vector3 ManifoldPoint::PositionWorldOnB::get()
{
	return Math::BtVector3ToVector3(&_native->getPositionWorldOnB());
}
void ManifoldPoint::PositionWorldOnB::set(Vector3 value)
{
	return Math::Vector3ToBtVector3(value, &_native->m_positionWorldOnB);
}

Object^ ManifoldPoint::UserPersistentData::get()
{
	if (!_native->m_userPersistentData) {
		return nullptr;
	}
	return VoidPtrToGCHandle(_native->m_userPersistentData).Target;
}
void ManifoldPoint::UserPersistentData::set(Object^ value)
{
	if (value != nullptr) {
		if (!_native->m_userPersistentData) {
			GCHandle handle = GCHandle::Alloc(value);
			_native->m_userPersistentData = GCHandleToVoidPtr(handle);
		}
	} else {
		if (_native->m_userPersistentData) {
			VoidPtrToGCHandle(_native->m_userPersistentData).Free();
		}
		_native->m_userPersistentData = 0;
	}
}
