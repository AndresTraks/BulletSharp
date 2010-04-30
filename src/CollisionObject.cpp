#include "StdAfx.h"

#include "BroadphaseProxy.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

#include <msclr/auto_gcroot.h>

#define __GCHANDLE_TO_VOIDPTR(x) ((GCHandle::operator System::IntPtr(x)).ToPointer())
#define __VOIDPTR_TO_GCHANDLE(x) (GCHandle::operator GCHandle(System::IntPtr(x)))

CollisionObject::CollisionObject(btCollisionObject* collisionObject)
{
	_collisionObject = collisionObject;
}

CollisionObject::CollisionObject(IntPtr collisionObject)
{
	_collisionObject = (btCollisionObject*)collisionObject.ToPointer();
}

CollisionObject::~CollisionObject()
{
	this->!CollisionObject();
}

CollisionObject::!CollisionObject()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_collisionObject = NULL;
	
	OnDisposed( this, nullptr );
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

#ifndef DISABLE_SERIALIZE
int CollisionObject::CalculateSerializeBufferSize()
{
	return _collisionObject->calculateSerializeBufferSize();
}

String^ CollisionObject::Serialize(IntPtr dataBuffer, Serializer^ serializer)
{
	const char* name = UnmanagedPointer->serialize(dataBuffer.ToPointer(), serializer->UnmanagedPointer);
	return gcnew String(name);
}

void CollisionObject::SerializeSingleObject(Serializer^ serializer)
{
	UnmanagedPointer->serializeSingleObject(serializer->UnmanagedPointer);
}
#endif

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
	return gcnew BroadphaseProxy(_collisionObject->getBroadphaseHandle());
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
	if (_collisionShape == nullptr)
	{
		btCollisionShape* shape = _collisionObject->getCollisionShape();
		if ( shape != nullptr)
			_collisionShape = gcnew BulletSharp::CollisionShape(shape);
	}
	return _collisionShape;
}
void CollisionObject::CollisionShape::set(BulletSharp::CollisionShape^ value)
{
	_collisionShape = value;
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
	return _rootCollisionShape;
}

Object^ CollisionObject::UserObject::get()
{
	void* obj = _collisionObject->getUserPointer();
	if (obj == nullptr)
		return nullptr;
	return static_cast<Object^>(__VOIDPTR_TO_GCHANDLE(obj).Target);
}
void CollisionObject::UserObject::set(Object^ value)
{
	void* obj = _collisionObject->getUserPointer();
	if (obj != nullptr)
		__VOIDPTR_TO_GCHANDLE(obj).Free();

	GCHandle handle = GCHandle::Alloc(value);
	_collisionObject->setUserPointer(__GCHANDLE_TO_VOIDPTR(handle));
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
}
