#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
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
		void* userObj = _collisionObject->getUserPointer();
		if (userObj)
			VoidPtrToGCHandle(userObj).Free();
		delete _collisionObject;
	}
	_collisionObject = NULL;
	
	OnDisposed(this, nullptr);
}

bool CollisionObject::IsDisposed::get()
{
	return (_collisionObject == NULL);
}

void CollisionObject::Activate()
{
	_collisionObject->activate();
}

void CollisionObject::Activate(bool forceActivation)
{
	_collisionObject->activate(forceActivation);
}

bool CollisionObject::CheckCollideWith(CollisionObject^ collisionObject)
{
	return _collisionObject->checkCollideWith(collisionObject->UnmanagedPointer);
}

void CollisionObject::ForceActivationState(BulletSharp::ActivationState newState)
{
	_collisionObject->forceActivationState((int)newState);
}

void CollisionObject::GetWorldTransform([Out] Matrix% outTransform)
{
	BtTransformToMatrixFast(_collisionObject->getWorldTransform(), outTransform);
}

#ifndef DISABLE_SERIALIZE
int CollisionObject::CalculateSerializeBufferSize()
{
	return _collisionObject->calculateSerializeBufferSize();
}

String^ CollisionObject::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	const char* name = UnmanagedPointer->serialize(dataBuffer.ToPointer(), serializer->UnmanagedPointer);
	return gcnew String(name);
}

void CollisionObject::SerializeSingleObject(BulletSharp::Serializer^ serializer)
{
	UnmanagedPointer->serializeSingleObject(serializer->UnmanagedPointer);
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

	CollisionObject^ colObject = gcnew CollisionObject(collisionObject);
	colObject->_doesNotOwnObject = true;
	return colObject;
}

BulletSharp::ActivationState CollisionObject::ActivationState::get()
{
	return (BulletSharp::ActivationState)_collisionObject->getActivationState();
}
void CollisionObject::ActivationState::set(BulletSharp::ActivationState value)
{
	_collisionObject->setActivationState((int)value);
}

Vector3 CollisionObject::AnisotropicFriction::get()
{
	return Math::BtVector3ToVector3(&_collisionObject->getAnisotropicFriction());
}
void CollisionObject::AnisotropicFriction::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	_collisionObject->setAnisotropicFriction(*valueTemp);
	delete valueTemp;
}

BroadphaseProxy^ CollisionObject::BroadphaseHandle::get()
{
	btBroadphaseProxy* broadphaseHandle = _collisionObject->getBroadphaseHandle();
	ReturnCachedObject(BroadphaseProxy, _broadphaseHandle, broadphaseHandle);
}

btScalar CollisionObject::CcdMotionThreshold::get()
{
	return _collisionObject->getCcdMotionThreshold();
}
void CollisionObject::CcdMotionThreshold::set(btScalar value)
{
	_collisionObject->setCcdMotionThreshold(value);
}

btScalar CollisionObject::CcdSquareMotionThreshold::get()
{
	return _collisionObject->getCcdSquareMotionThreshold();
}

btScalar CollisionObject::CcdSweptSphereRadius::get()
{
	return _collisionObject->getCcdSweptSphereRadius();
}
void CollisionObject::CcdSweptSphereRadius::set(btScalar value)
{
	_collisionObject->setCcdSweptSphereRadius(value);
}

CollisionFlags CollisionObject::CollisionFlags::get()
{
	return (BulletSharp::CollisionFlags)_collisionObject->getCollisionFlags();
}
void CollisionObject::CollisionFlags::set(BulletSharp::CollisionFlags value)
{
	_collisionObject->setCollisionFlags((int)value);
}

CollisionShape^ CollisionObject::CollisionShape::get()
{
	return BulletSharp::CollisionShape::GetManaged(_collisionObject->getCollisionShape());
}
void CollisionObject::CollisionShape::set(BulletSharp::CollisionShape^ value)
{
	_collisionObject->setCollisionShape(value->UnmanagedPointer);
}

int CollisionObject::CompanionId::get()
{
	return _collisionObject->getCompanionId();
}
void CollisionObject::CompanionId::set(int value)
{
	_collisionObject->setCompanionId(value);
}

btScalar CollisionObject::ContactProcessingThreshold::get()
{
	return _collisionObject->getContactProcessingThreshold();
}
void CollisionObject::ContactProcessingThreshold::set(btScalar value)
{
	_collisionObject->setContactProcessingThreshold(value);
}

btScalar CollisionObject::DeactivationTime::get()
{
	return _collisionObject->getDeactivationTime();
}
void CollisionObject::DeactivationTime::set(btScalar value)
{
	_collisionObject->setDeactivationTime(value);
}

btScalar CollisionObject::Friction::get()
{
	return _collisionObject->getFriction();
}
void CollisionObject::Friction::set(btScalar value)
{
	_collisionObject->setFriction(value);
}

bool CollisionObject::HasAnisotropicFriction::get()
{
	return _collisionObject->hasAnisotropicFriction();
}

bool CollisionObject::HasContactResponse::get()
{
	return _collisionObject->hasContactResponse();
}

btScalar CollisionObject::HitFraction::get()
{
	return _collisionObject->getHitFraction();
}
void CollisionObject::HitFraction::set(btScalar value)
{
	_collisionObject->setHitFraction(value);
}

Vector3 CollisionObject::InterpolationAngularVelocity::get()
{
	return Math::BtVector3ToVector3(&_collisionObject->getInterpolationAngularVelocity());
}
void CollisionObject::InterpolationAngularVelocity::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	_collisionObject->setInterpolationAngularVelocity(*valueTemp);
	delete valueTemp;
}

Vector3 CollisionObject::InterpolationLinearVelocity::get()
{
	return Math::BtVector3ToVector3(&_collisionObject->getInterpolationLinearVelocity());
}
void CollisionObject::InterpolationLinearVelocity::set(Vector3 value)
{
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	_collisionObject->setInterpolationLinearVelocity(*valueTemp);
	delete valueTemp;
}

Matrix CollisionObject::InterpolationWorldTransform::get()
{
	return Math::BtTransformToMatrix(&_collisionObject->getInterpolationWorldTransform());
}
void CollisionObject::InterpolationWorldTransform::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	_collisionObject->setInterpolationWorldTransform(*valueTemp);
	delete valueTemp;
}

bool CollisionObject::IsActive::get()
{
	return _collisionObject->isActive();
}

bool CollisionObject::IsKinematicObject::get()
{
	return _collisionObject->isKinematicObject();
}

int CollisionObject::IslandTag::get()
{
	return _collisionObject->getIslandTag();
}
void CollisionObject::IslandTag::set(int value)
{
	_collisionObject->setIslandTag(value);
}

bool CollisionObject::IsStaticObject::get()
{
	return _collisionObject->isStaticObject();
}

bool CollisionObject::IsStaticOrKinematicObject::get()
{
	return _collisionObject->isStaticOrKinematicObject();
}

bool CollisionObject::MergesSimulationIslands::get()
{
	return _collisionObject->mergesSimulationIslands();
}

btScalar CollisionObject::Restitution::get()
{
	return _collisionObject->getRestitution();
}
void CollisionObject::Restitution::set(btScalar value)
{
	_collisionObject->setRestitution(value);
}

CollisionShape^ CollisionObject::RootCollisionShape::get()
{
	return BulletSharp::CollisionShape::GetManaged(_collisionObject->getRootCollisionShape());
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
	return Math::BtTransformToMatrix(&_collisionObject->getWorldTransform());
}
void CollisionObject::WorldTransform::set(Matrix value)
{
	btTransform* valueTemp = Math::MatrixToBtTransform(value);
	_collisionObject->setWorldTransform(*valueTemp);
	delete valueTemp;
}

btCollisionObject* CollisionObject::UnmanagedPointer::get()
{
	return _collisionObject;
}
void CollisionObject::UnmanagedPointer::set(btCollisionObject* value)
{
	_collisionObject = value;

	if (_collisionObject->getUserPointer() == 0)
	{
		GCHandle handle = GCHandle::Alloc(this);
		void* obj = GCHandleToVoidPtr(handle);
		_collisionObject->setUserPointer(obj);
	}
}
