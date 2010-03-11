#include "StdAfx.h"

#include "CollisionObject.h"
#include "CollisionShape.h"

#include <msclr/auto_gcroot.h>

#define __GCHANDLE_TO_VOIDPTR(x) ((GCHandle::operator System::IntPtr(x)).ToPointer())
#define __VOIDPTR_TO_GCHANDLE(x) (GCHandle::operator GCHandle(System::IntPtr(x)))

// Unmanaged functions to let us use the unmanaged btVector3 and btTransform
#pragma managed(push, off)
void CollisionObject_GetAnisotropicFriction(btCollisionObject* collisionObject, btVector3* friction)
{
	*friction = collisionObject->getAnisotropicFriction();
}

void CollisionObject_GetInterpolationAngularVelocity(btCollisionObject* collisionObject, btVector3* velocity)
{
	*velocity = collisionObject->getInterpolationAngularVelocity();
}

void CollisionObject_GetInterpolationLinearVelocity(btCollisionObject* collisionObject, btVector3* velocity)
{
	*velocity = collisionObject->getInterpolationLinearVelocity();
}

void CollisionObject_GetInterpolationWorldTransform(btCollisionObject* collisionObject, btTransform* transform)
{
	*transform = collisionObject->getInterpolationWorldTransform();
}

void CollisionObject_GetWorldTransform(btCollisionObject* collisionObject, btTransform* transform)
{
	*transform = collisionObject->getWorldTransform();
}
#pragma managed(pop)

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
	btVector3* friction = new btVector3;
	CollisionObject_GetAnisotropicFriction(_collisionObject, friction);
	Vector3 v = Math::BtVector3ToVector3(friction);
	delete friction;
	return v;
}
void CollisionObject::AnisotropicFriction::set(Vector3 value)
{
	_collisionObject->setAnisotropicFriction(*Math::Vector3ToBtVector3(value));
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
	btVector3* velocity = new btVector3;
	CollisionObject_GetInterpolationAngularVelocity(_collisionObject, velocity);
	return Math::BtVector3ToVector3(velocity);
}
void CollisionObject::InterpolationAngularVelocity::set(Vector3 value)
{
	_collisionObject->setInterpolationAngularVelocity(*Math::Vector3ToBtVector3(value));
}

Vector3 CollisionObject::InterpolationLinearVelocity::get()
{
	btVector3* velocity = new btVector3;
	CollisionObject_GetInterpolationLinearVelocity(_collisionObject, velocity);
	return Math::BtVector3ToVector3(velocity);
}
void CollisionObject::InterpolationLinearVelocity::set(Vector3 value)
{
	_collisionObject->setInterpolationLinearVelocity(*Math::Vector3ToBtVector3(value));
}

Matrix CollisionObject::InterpolationWorldTransform::get()
{
	btTransform* transform = new btTransform;
	CollisionObject_GetInterpolationWorldTransform(UnmanagedPointer, transform);
	Matrix m = Math::BtTransformToMatrix(transform);
	delete transform;
	return m;
}
void CollisionObject::InterpolationWorldTransform::set(Matrix value)
{
	_collisionObject->setInterpolationWorldTransform(*Math::MatrixToBtTransform(value));
}

int CollisionObject::IslandTag::get()
{
	return _collisionObject->getIslandTag();
}
void CollisionObject::IslandTag::set(int value)
{
	_collisionObject->setIslandTag(value);
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
	btTransform* transform = new btTransform;
	CollisionObject_GetWorldTransform(_collisionObject, transform);
	Matrix m = Math::BtTransformToMatrix(transform);
	delete transform;
	return m;
}
void CollisionObject::WorldTransform::set(Matrix value)
{
	_collisionObject->setWorldTransform(*Math::MatrixToBtTransform(value));
}

bool CollisionObject::HasAnisotropicFriction()
{
	return _collisionObject->hasAnisotropicFriction();
}

bool CollisionObject::HasContactResponse()
{
	return _collisionObject->hasContactResponse();
}

bool CollisionObject::IsActive()
{
	return _collisionObject->isActive();
}

bool CollisionObject::IsKinematicObject()
{
	return _collisionObject->isKinematicObject();
}

bool CollisionObject::IsStaticObject()
{
	return _collisionObject->isStaticObject();
}

bool CollisionObject::IsStaticOrKinematicObject()
{
	return _collisionObject->isStaticOrKinematicObject();
}

bool CollisionObject::mergesSimulationIslands()
{
	return _collisionObject->mergesSimulationIslands();
}

btCollisionObject* CollisionObject::UnmanagedPointer::get()
{
	return _collisionObject;
}
void CollisionObject::UnmanagedPointer::set(btCollisionObject* value)
{
	_collisionObject = value;
}
