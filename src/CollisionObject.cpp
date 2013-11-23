#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "MultiBodyLinkCollider.h"
#include "RigidBody.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif
#ifndef DISABLE_SOFTBODY
#include "SoftBody.h"
#endif

CollisionObject::CollisionObject(btCollisionObject* collisionObject)
{
	UnmanagedPointer = collisionObject;
}

CollisionObject::CollisionObject()
{
	UnmanagedPointer = new btCollisionObject();
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

	if (_doesNotOwnObject == false)
	{
		void* userObj = _native->getUserPointer();
		if (userObj)
			VoidPtrToGCHandle(userObj).Free();
		delete _native;
	}
	_native = NULL;
	
	OnDisposed(this, nullptr);
}

bool CollisionObject::IsDisposed::get()
{
	return (_native == NULL);
}

void CollisionObject::Activate()
{
	_native->activate();
}

void CollisionObject::Activate(bool forceActivation)
{
	_native->activate(forceActivation);
}

bool CollisionObject::CheckCollideWith(CollisionObject^ collisionObject)
{
	return _native->checkCollideWith(collisionObject->_native);
}

void CollisionObject::ForceActivationState(BulletSharp::ActivationState newState)
{
	_native->forceActivationState((int)newState);
}

void CollisionObject::GetWorldTransform([Out] Matrix% outTransform)
{
	BtTransformToMatrixFast(_native->getWorldTransform(), outTransform);
}

bool CollisionObject::HasAnisotropicFriction()
{
	return _native->hasAnisotropicFriction();
}
bool CollisionObject::HasAnisotropicFriction(AnisotropicFrictionFlags frictionMode)
{
	return _native->hasAnisotropicFriction((int)frictionMode);
}

void CollisionObject::SetAnisotropicFriction(Vector3 anisotropicFriction, AnisotropicFrictionFlags frictionMode)
{
	VECTOR3_DEF(anisotropicFriction);
	_native->setAnisotropicFriction(VECTOR3_USE(anisotropicFriction), (int)frictionMode);
	VECTOR3_DEL(anisotropicFriction);
}
void CollisionObject::SetAnisotropicFriction(Vector3 anisotropicFriction)
{
	VECTOR3_DEF(anisotropicFriction);
	_native->setAnisotropicFriction(VECTOR3_USE(anisotropicFriction));
	VECTOR3_DEL(anisotropicFriction);
}

#ifndef DISABLE_SERIALIZE
int CollisionObject::CalculateSerializeBufferSize()
{
	return _native->calculateSerializeBufferSize();
}

String^ CollisionObject::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	const char* name = _native->serialize(dataBuffer.ToPointer(), serializer->_native);
	return gcnew String(name);
}

void CollisionObject::SerializeSingleObject(BulletSharp::Serializer^ serializer)
{
	_native->serializeSingleObject(serializer->_native);
}
#endif

CollisionObject^ CollisionObject::GetManaged(btCollisionObject* collisionObject)
{
	if (collisionObject == 0)
		return nullptr;

	void* userObj = collisionObject->getUserPointer();
	if (userObj)
		return static_cast<CollisionObject^>(VoidPtrToGCHandle(userObj).Target);

	// If we reach here, then collisionObject was created from within unmanaged code,
	// mark the wrapper object we create here so we don't try to destroy it later.
	btRigidBody* rigidBody = static_cast<btRigidBody*>(collisionObject);
	if (rigidBody)
	{
		RigidBody^ body = gcnew RigidBody(rigidBody);
		body->_doesNotOwnObject = true;
		return body;
	}

#ifndef DISABLE_SOFTBODY
	btSoftBody* softBody = static_cast<btSoftBody*>(collisionObject);
	if (softBody)
	{
		SoftBody::SoftBody^ body = gcnew SoftBody::SoftBody(softBody);
		body->_doesNotOwnObject = true;
		return body;
	}
#endif

#ifndef DISABLE_FEATHERSTONE
	btMultiBodyLinkCollider* multiBody = static_cast<btMultiBodyLinkCollider*>(collisionObject);
	if (multiBody)
	{
		MultiBodyLinkCollider^ body = gcnew MultiBodyLinkCollider(multiBody);
		body->_doesNotOwnObject = true;
		return body;
	}
#endif

	CollisionObject^ colObject = gcnew CollisionObject(collisionObject);
	colObject->_doesNotOwnObject = true;
	return colObject;
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
	VECTOR3_DEF(value);
	_native->setAnisotropicFriction(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

BroadphaseProxy^ CollisionObject::BroadphaseHandle::get()
{
	btBroadphaseProxy* broadphaseHandle = _native->getBroadphaseHandle();
	ReturnCachedObject(BroadphaseProxy, _broadphaseHandle, broadphaseHandle);
}

btScalar CollisionObject::CcdMotionThreshold::get()
{
	return _native->getCcdMotionThreshold();
}
void CollisionObject::CcdMotionThreshold::set(btScalar value)
{
	_native->setCcdMotionThreshold(value);
}

btScalar CollisionObject::CcdSquareMotionThreshold::get()
{
	return _native->getCcdSquareMotionThreshold();
}

btScalar CollisionObject::CcdSweptSphereRadius::get()
{
	return _native->getCcdSweptSphereRadius();
}
void CollisionObject::CcdSweptSphereRadius::set(btScalar value)
{
	_native->setCcdSweptSphereRadius(value);
}

CollisionFlags CollisionObject::CollisionFlags::get()
{
	return (BulletSharp::CollisionFlags)_native->getCollisionFlags();
}
void CollisionObject::CollisionFlags::set(BulletSharp::CollisionFlags value)
{
	_native->setCollisionFlags((int)value);
}

CollisionShape^ CollisionObject::CollisionShape::get()
{
	return BulletSharp::CollisionShape::GetManaged(_native->getCollisionShape());
}
void CollisionObject::CollisionShape::set(BulletSharp::CollisionShape^ value)
{
	_native->setCollisionShape(value->_native);
}

int CollisionObject::CompanionId::get()
{
	return _native->getCompanionId();
}
void CollisionObject::CompanionId::set(int value)
{
	_native->setCompanionId(value);
}

btScalar CollisionObject::ContactProcessingThreshold::get()
{
	return _native->getContactProcessingThreshold();
}
void CollisionObject::ContactProcessingThreshold::set(btScalar value)
{
	_native->setContactProcessingThreshold(value);
}

btScalar CollisionObject::DeactivationTime::get()
{
	return _native->getDeactivationTime();
}
void CollisionObject::DeactivationTime::set(btScalar value)
{
	_native->setDeactivationTime(value);
}

btScalar CollisionObject::Friction::get()
{
	return _native->getFriction();
}
void CollisionObject::Friction::set(btScalar value)
{
	_native->setFriction(value);
}

bool CollisionObject::HasContactResponse::get()
{
	return _native->hasContactResponse();
}

btScalar CollisionObject::HitFraction::get()
{
	return _native->getHitFraction();
}
void CollisionObject::HitFraction::set(btScalar value)
{
	_native->setHitFraction(value);
}

Vector3 CollisionObject::InterpolationAngularVelocity::get()
{
	return Math::BtVector3ToVector3(&_native->getInterpolationAngularVelocity());
}
void CollisionObject::InterpolationAngularVelocity::set(Vector3 value)
{
	VECTOR3_DEF(value);
	_native->setInterpolationAngularVelocity(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

Vector3 CollisionObject::InterpolationLinearVelocity::get()
{
	return Math::BtVector3ToVector3(&_native->getInterpolationLinearVelocity());
}
void CollisionObject::InterpolationLinearVelocity::set(Vector3 value)
{
	VECTOR3_DEF(value);
	_native->setInterpolationLinearVelocity(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

Matrix CollisionObject::InterpolationWorldTransform::get()
{
	return Math::BtTransformToMatrix(&_native->getInterpolationWorldTransform());
}
void CollisionObject::InterpolationWorldTransform::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	_native->setInterpolationWorldTransform(*valueTemp);
	ALIGNED_FREE(valueTemp);
}

bool CollisionObject::IsActive::get()
{
	return _native->isActive();
}

bool CollisionObject::IsKinematicObject::get()
{
	return _native->isKinematicObject();
}

int CollisionObject::IslandTag::get()
{
	return _native->getIslandTag();
}
void CollisionObject::IslandTag::set(int value)
{
	_native->setIslandTag(value);
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
void CollisionObject::Restitution::set(btScalar value)
{
	_native->setRestitution(value);
}

btScalar CollisionObject::RollingFriction::get()
{
	return _native->getRollingFriction();
}
void CollisionObject::RollingFriction::set(btScalar value)
{
	_native->setRollingFriction(value);
}

int CollisionObject::UpdateRevisionInternal::get()
{
	return _native->getUpdateRevisionInternal();
}

int CollisionObject::UserIndex::get()
{
	return _native->getUserIndex();
}
void CollisionObject::UserIndex::set(int value)
{
	_native->setUserIndex(value);
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
void CollisionObject::WorldTransform::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	_native->setWorldTransform(*valueTemp);
	ALIGNED_FREE(valueTemp);
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
		GCHandle handle = GCHandle::Alloc(this);
		void* obj = GCHandleToVoidPtr(handle);
		_native->setUserPointer(obj);
	}
}
