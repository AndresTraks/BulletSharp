#include "StdAfx.h"

#include "CollisionObjectWrapper.h"
#include "CollisionShape.h"
#include "ManifoldPoint.h"

ManifoldPoint::ManifoldPoint(btManifoldPoint* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

#ifdef BT_CALLBACKS_ARE_EVENTS
bool onContactAdded(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap,
	int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	/*
	ContactAddedEventArgs^ args = gcnew ContactAddedEventArgs();
	args->ContactPoint = gcnew ManifoldPoint(&cp, true);
	args->CollisionObject0Wrapper = gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj0Wrap);
	args->PartID0 = partId0;
	args->Index0 = index0;
	args->CollisionObject1Wrapper = gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj1Wrap);
	args->PartID1 = partId1;
	args->Index1 = index1;
	ManifoldPoint::_contactAdded(nullptr, args);
	return args->IsContactModified;
	*/
	CollisionObjectWrapper^ colObj0WrapManaged = gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj0Wrap);
	CollisionObjectWrapper^ colObj1WrapManaged = gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj1Wrap);

	ManifoldPoint::_contactAdded(gcnew ManifoldPoint(&cp, true),
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj0Wrap), partId0, index0,
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj1Wrap), partId1, index1);

	// Bullet may use temporary btTriangleShapes that can be destroyed before before non-deterministic disposal.
	// Check if these collision shapes were referenced in managed code and clean up any references here.
	btCollisionShape* collisionShape0 = (btCollisionShape*)colObj0Wrap->getCollisionShape();
	btCollisionShape* collisionShape1 = (btCollisionShape*)colObj1Wrap->getCollisionShape();
	
	if (collisionShape0->getUserPointer() &&
		collisionShape0->getShapeType() == TRIANGLE_SHAPE_PROXYTYPE &&
		colObj0Wrap->getCollisionObject()->getCollisionShape() != collisionShape0)
	{
		delete CollisionShape::GetManaged(collisionShape0);
		collisionShape0->setUserPointer(0);
	}
	if (collisionShape1->getUserPointer() &&
		collisionShape1->getShapeType() == TRIANGLE_SHAPE_PROXYTYPE &&
		colObj1Wrap->getCollisionObject()->getCollisionShape() != collisionShape1)
	{
		delete CollisionShape::GetManaged(collisionShape1);
		collisionShape1->setUserPointer(0);
	}

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
	bool ret = ManifoldPoint::_contactAdded(gcnew ManifoldPoint(&cp, true),
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj0Wrap), partId0, index0,
		gcnew CollisionObjectWrapper((btCollisionObjectWrapper*)colObj1Wrap), partId1, index1);

	// Bullet may use temporary btTriangleShapes that can be destroyed before before non-deterministic disposal.
	// Check if these collision shapes were referenced in managed code and clean up any references here.
	btCollisionShape* collisionShape0 = (btCollisionShape*)colObj0Wrap->getCollisionShape();
	btCollisionShape* collisionShape1 = (btCollisionShape*)colObj1Wrap->getCollisionShape();
	
	if (collisionShape0->getUserPointer() &&
		collisionShape0->getShapeType() == TRIANGLE_SHAPE_PROXYTYPE &&
		colObj0Wrap->getCollisionObject()->getCollisionShape() != collisionShape0)
	{
		delete CollisionShape::GetManaged(collisionShape0);
		collisionShape0->setUserPointer(0);
	}
	if (collisionShape1->getUserPointer() &&
		collisionShape1->getShapeType() == TRIANGLE_SHAPE_PROXYTYPE &&
		colObj1Wrap->getCollisionObject()->getCollisionShape() != collisionShape1)
	{
		delete CollisionShape::GetManaged(collisionShape1);
		collisionShape1->setUserPointer(0);
	}

	return ret;
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

ManifoldPoint::~ManifoldPoint()
{
	this->!ManifoldPoint();
}

ManifoldPoint::!ManifoldPoint()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

ManifoldPoint::ManifoldPoint()
{
	_native = new btManifoldPoint();
}

ManifoldPoint::ManifoldPoint(Vector3 pointA, Vector3 pointB, Vector3 normal, btScalar distance)
{
	VECTOR3_CONV(pointA);
	VECTOR3_CONV(pointB);
	VECTOR3_CONV(normal);
	_native = new btManifoldPoint(VECTOR3_USE(pointA), VECTOR3_USE(pointB), VECTOR3_USE(normal),
		distance);
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

btScalar ManifoldPoint::AppliedImpulseLateral1::get()
{
	return _native->m_appliedImpulseLateral1;
}
void ManifoldPoint::AppliedImpulseLateral1::set(btScalar value)
{
	_native->m_appliedImpulseLateral1 = value;
}

btScalar ManifoldPoint::AppliedImpulseLateral2::get()
{
	return _native->m_appliedImpulseLateral2;
}
void ManifoldPoint::AppliedImpulseLateral2::set(btScalar value)
{
	_native->m_appliedImpulseLateral2 = value;
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

btScalar ManifoldPoint::ContactCfm::get()
{
	return _native->m_contactCFM;
}
void ManifoldPoint::ContactCfm::set(btScalar value)
{
	_native->m_contactCFM = value;
}

btScalar ManifoldPoint::ContactErp::get()
{
	return _native->m_contactERP;
}
void ManifoldPoint::ContactErp::set(btScalar value)
{
	_native->m_contactERP = value;
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

ContactPointFlags ManifoldPoint::ContactPointFlags::get()
{
	return (BulletSharp::ContactPointFlags)_native->m_contactPointFlags;
}
void ManifoldPoint::ContactPointFlags::set(BulletSharp::ContactPointFlags value)
{
	_native->m_contactPointFlags = (btContactPointFlags)value;
}

btScalar ManifoldPoint::Distance::get()
{
	return _native->getDistance();
}
void ManifoldPoint::Distance::set(btScalar dist)
{
	_native->setDistance(dist);
}

btScalar ManifoldPoint::Distance1::get()
{
	return _native->m_distance1;
}
void ManifoldPoint::Distance1::set(btScalar value)
{
	_native->m_distance1 = value;
}

btScalar ManifoldPoint::FrictionCfm::get()
{
	return _native->m_frictionCFM;
}
void ManifoldPoint::FrictionCfm::set(btScalar value)
{
	_native->m_frictionCFM = value;
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
	Math::Vector3ToBtVector3(value, &_native->m_lateralFrictionDir1);
}

Vector3 ManifoldPoint::LateralFrictionDir2::get()
{
	return Math::BtVector3ToVector3(&_native->m_lateralFrictionDir2);
}
void ManifoldPoint::LateralFrictionDir2::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_lateralFrictionDir2);
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
	Math::Vector3ToBtVector3(value, &_native->m_localPointA);
}

Vector3 ManifoldPoint::LocalPointB::get()
{
	return Math::BtVector3ToVector3(&_native->m_localPointB);
}
void ManifoldPoint::LocalPointB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_localPointB);
}

Vector3 ManifoldPoint::NormalWorldOnB::get()
{
	return Math::BtVector3ToVector3(&_native->m_normalWorldOnB);
}
void ManifoldPoint::NormalWorldOnB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_normalWorldOnB);
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
	Math::Vector3ToBtVector3(value, &_native->m_positionWorldOnA);
}

Vector3 ManifoldPoint::PositionWorldOnB::get()
{
	return Math::BtVector3ToVector3(&_native->getPositionWorldOnB());
}
void ManifoldPoint::PositionWorldOnB::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &_native->m_positionWorldOnB);
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
