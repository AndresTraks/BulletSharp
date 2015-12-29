#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "RigidBody.h"
#ifndef DISABLE_FEATHERSTONE
#include "MultiBodyLinkCollider.h"
#endif
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif
#ifndef DISABLE_SOFTBODY
#include "SoftBody.h"
#endif

CollisionObject::CollisionObject(btCollisionObject* native)
{
	UnmanagedPointer = native;
}

CollisionObject::~CollisionObject()
{
	this->!CollisionObject();
}

CollisionObject::!CollisionObject()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	if (!_preventDelete)
	{
		void* userObj = _native->getUserPointer();
		if (userObj)
			VoidPtrToGCHandle(userObj).Free();
		delete _native;
	}
	_isDisposed = true;

	OnDisposed(this, nullptr);
}

CollisionObject::CollisionObject()
{
	UnmanagedPointer = new btCollisionObject();
}

void CollisionObject::Activate(bool forceActivation)
{
	_native->activate(forceActivation);
}

void CollisionObject::Activate()
{
	_native->activate();
}

#ifndef DISABLE_SERIALIZE
int CollisionObject::CalculateSerializeBufferSize()
{
	return _native->calculateSerializeBufferSize();
}
#endif

bool CollisionObject::CheckCollideWith(CollisionObject^ collisionObject)
{
	return _native->checkCollideWith(collisionObject->_native);
}

bool CollisionObject::CheckCollideWithOverride(CollisionObject^ collisionObject)
{
	return _native->checkCollideWithOverride(collisionObject->_native);
}

void CollisionObject::ForceActivationState(BulletSharp::ActivationState newState)
{
	_native->forceActivationState((int)newState);
}

int CollisionObject::GetHashCode()
{
	return (int)_native;
}

void CollisionObject::GetWorldTransform([Out] Matrix% outTransform)
{
	BtTransformToMatrixFast(_native->getWorldTransform(), outTransform);
}

bool CollisionObject::HasAnisotropicFriction(AnisotropicFrictionFlags frictionMode)
{
	return _native->hasAnisotropicFriction((int)frictionMode);
}

bool CollisionObject::HasAnisotropicFriction()
{
	return _native->hasAnisotropicFriction();
}

#ifndef DISABLE_SERIALIZE
String^ CollisionObject::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	return gcnew String(_native->serialize(dataBuffer.ToPointer(), serializer->_native));
}

void CollisionObject::SerializeSingleObject(BulletSharp::Serializer^ serializer)
{
	_native->serializeSingleObject(serializer->_native);
}
#endif

void CollisionObject::SetAnisotropicFriction(Vector3 anisotropicFriction, AnisotropicFrictionFlags frictionMode)
{
	VECTOR3_CONV(anisotropicFriction);
	_native->setAnisotropicFriction(VECTOR3_USE(anisotropicFriction), (int)frictionMode);
	VECTOR3_DEL(anisotropicFriction);
}

void CollisionObject::SetAnisotropicFriction(Vector3 anisotropicFriction)
{
	VECTOR3_CONV(anisotropicFriction);
	_native->setAnisotropicFriction(VECTOR3_USE(anisotropicFriction));
	VECTOR3_DEL(anisotropicFriction);
}

void CollisionObject::SetIgnoreCollisionCheck(CollisionObject^ collisionObject, bool ignoreCollisionCheck)
{
	_native->setIgnoreCollisionCheck(collisionObject->_native, ignoreCollisionCheck);
}

CollisionObject^ CollisionObject::GetManaged(btCollisionObject* collisionObject)
{
	if (collisionObject == 0)
		return nullptr;

	void* userObj = collisionObject->getUserPointer();
	if (userObj)
		return static_cast<CollisionObject^>(VoidPtrToGCHandle(userObj).Target);

	throw gcnew InvalidOperationException("Unknown collision object!");
}

BulletSharp::ActivationState CollisionObject::ActivationState::get()
{
	return (BulletSharp::ActivationState)_native->getActivationState();
}
void CollisionObject::ActivationState::set(BulletSharp::ActivationState value)
{
	_native->setActivationState((int)value);
}

Vector3 CollisionObject::AnisotropicFriction::get()
{
	return Math::BtVector3ToVector3(&_native->getAnisotropicFriction());
}
void CollisionObject::AnisotropicFriction::set(Vector3 value)
{
	VECTOR3_CONV(value);
	_native->setAnisotropicFriction(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

BroadphaseProxy^ CollisionObject::BroadphaseHandle::get()
{
	return _broadphaseHandle;
}
void CollisionObject::BroadphaseHandle::set(BroadphaseProxy^ handle)
{
	_native->setBroadphaseHandle(GetUnmanagedNullable(handle));
	_broadphaseHandle = handle;
}

btScalar CollisionObject::CcdMotionThreshold::get()
{
	return _native->getCcdMotionThreshold();
}
void CollisionObject::CcdMotionThreshold::set(btScalar ccdMotionThreshold)
{
	_native->setCcdMotionThreshold(ccdMotionThreshold);
}

btScalar CollisionObject::CcdSquareMotionThreshold::get()
{
	return _native->getCcdSquareMotionThreshold();
}

btScalar CollisionObject::CcdSweptSphereRadius::get()
{
	return _native->getCcdSweptSphereRadius();
}
void CollisionObject::CcdSweptSphereRadius::set(btScalar radius)
{
	_native->setCcdSweptSphereRadius(radius);
}

CollisionFlags CollisionObject::CollisionFlags::get()
{
	return (BulletSharp::CollisionFlags)_native->getCollisionFlags();
}
void CollisionObject::CollisionFlags::set(BulletSharp::CollisionFlags flags)
{
	_native->setCollisionFlags((int)flags);
}

CollisionShape^ CollisionObject::CollisionShape::get()
{
	return _collisionShape;
}
void CollisionObject::CollisionShape::set(BulletSharp::CollisionShape^ collisionShape)
{
	_native->setCollisionShape(GetUnmanagedNullable(collisionShape));
	_collisionShape = collisionShape;
}

int CollisionObject::CompanionId::get()
{
	return _native->getCompanionId();
}
void CollisionObject::CompanionId::set(int id)
{
	_native->setCompanionId(id);
}

btScalar CollisionObject::ContactProcessingThreshold::get()
{
	return _native->getContactProcessingThreshold();
}
void CollisionObject::ContactProcessingThreshold::set(btScalar contactProcessingThreshold)
{
	_native->setContactProcessingThreshold(contactProcessingThreshold);
}

btScalar CollisionObject::DeactivationTime::get()
{
	return _native->getDeactivationTime();
}
void CollisionObject::DeactivationTime::set(btScalar time)
{
	_native->setDeactivationTime(time);
}

btScalar CollisionObject::Friction::get()
{
	return _native->getFriction();
}
void CollisionObject::Friction::set(btScalar frict)
{
	_native->setFriction(frict);
}

bool CollisionObject::HasContactResponse::get()
{
	return _native->hasContactResponse();
}

btScalar CollisionObject::HitFraction::get()
{
	return _native->getHitFraction();
}
void CollisionObject::HitFraction::set(btScalar hitFraction)
{
	_native->setHitFraction(hitFraction);
}

Vector3 CollisionObject::InterpolationAngularVelocity::get()
{
	return Math::BtVector3ToVector3(&_native->getInterpolationAngularVelocity());
}
void CollisionObject::InterpolationAngularVelocity::set(Vector3 angvel)
{
	VECTOR3_CONV(angvel);
	_native->setInterpolationAngularVelocity(VECTOR3_USE(angvel));
	VECTOR3_DEL(angvel);
}

Vector3 CollisionObject::InterpolationLinearVelocity::get()
{
	return Math::BtVector3ToVector3(&_native->getInterpolationLinearVelocity());
}
void CollisionObject::InterpolationLinearVelocity::set(Vector3 linvel)
{
	VECTOR3_CONV(linvel);
	_native->setInterpolationLinearVelocity(VECTOR3_USE(linvel));
	VECTOR3_DEL(linvel);
}

Matrix CollisionObject::InterpolationWorldTransform::get()
{
	return Math::BtTransformToMatrix(&_native->getInterpolationWorldTransform());
}
void CollisionObject::InterpolationWorldTransform::set(Matrix trans)
{
	TRANSFORM_CONV(trans);
	_native->setInterpolationWorldTransform(TRANSFORM_USE(trans));
	TRANSFORM_DEL(trans);
}

bool CollisionObject::IsActive::get()
{
	return _native->isActive();
}

bool CollisionObject::IsDisposed::get()
{
	return _isDisposed;
}

bool CollisionObject::IsKinematicObject::get()
{
	return _native->isKinematicObject();
}

int CollisionObject::IslandTag::get()
{
	return _native->getIslandTag();
}
void CollisionObject::IslandTag::set(int tag)
{
	_native->setIslandTag(tag);
}

bool CollisionObject::IsStaticObject::get()
{
	return _native->isStaticObject();
}

bool CollisionObject::IsStaticOrKinematicObject::get()
{
	return _native->isStaticOrKinematicObject();
}

bool CollisionObject::MergesSimulationIslands::get()
{
	return _native->mergesSimulationIslands();
}

btScalar CollisionObject::Restitution::get()
{
	return _native->getRestitution();
}
void CollisionObject::Restitution::set(btScalar rest)
{
	_native->setRestitution(rest);
}

btScalar CollisionObject::RollingFriction::get()
{
	return _native->getRollingFriction();
}
void CollisionObject::RollingFriction::set(btScalar frict)
{
	_native->setRollingFriction(frict);
}

int CollisionObject::UpdateRevisionInternal::get()
{
	return _native->getUpdateRevisionInternal();
}

int CollisionObject::UserIndex::get()
{
	return _native->getUserIndex();
}
void CollisionObject::UserIndex::set(int index)
{
	_native->setUserIndex(index);
}

Object^ CollisionObject::UserObject::get()
{
	return _userObject;
}
void CollisionObject::UserObject::set(Object^ value)
{
	_userObject = value;
}

Matrix CollisionObject::WorldTransform::get()
{
	return Math::BtTransformToMatrix(&_native->getWorldTransform());
}
void CollisionObject::WorldTransform::set(Matrix worldTrans)
{
	TRANSFORM_CONV(worldTrans);
	_native->setWorldTransform(TRANSFORM_USE(worldTrans));
	TRANSFORM_DEL(worldTrans);
}

btCollisionObject* CollisionObject::UnmanagedPointer::get()
{
	return _native;
}
void CollisionObject::UnmanagedPointer::set(btCollisionObject* value)
{
	// Inheriting classes such as SoftBody may pass 0 and then do
	// additional processing before storing the native pointer.
	if (value == 0) {
		return;
	}

	_native = value;

	if (_native->getUserPointer() == 0)
	{
		GCHandle handle = GCHandle::Alloc(this, GCHandleType::Weak);
		void* obj = GCHandleToVoidPtr(handle);
		_native->setUserPointer(obj);
	}
}
