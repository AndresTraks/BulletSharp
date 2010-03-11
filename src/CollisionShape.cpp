#include "StdAfx.h"

#include "CollisionShape.h"
#include "StringConv.h"

#define __GCHANDLE_TO_VOIDPTR(x) ((GCHandle::operator System::IntPtr(x)).ToPointer())
#define __VOIDPTR_TO_GCHANDLE(x) (GCHandle::operator GCHandle(System::IntPtr(x)))

CollisionShape::CollisionShape(btCollisionShape* collisionShape)
{
	_collisionShape = collisionShape;
}

CollisionShape::~CollisionShape()
{
	this->!CollisionShape();
}

CollisionShape::!CollisionShape()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );

	_collisionShape = NULL;

	OnDisposed( this, nullptr );
}

bool CollisionShape::IsDisposed::get()
{
	return ( _collisionShape == NULL );
}

void CollisionShape::CalculateLocalInertia(btScalar mass, Vector3% inertia)
{
	btVector3* vector = new btVector3;
	_collisionShape->calculateLocalInertia(mass, *vector);
	inertia = Math::BtVector3ToVector3(vector);
	delete vector;
}

Vector3 CollisionShape::CalculateLocalInertia(btScalar mass)
{
	btVector3* vector = new btVector3;
	_collisionShape->calculateLocalInertia(mass, *vector);
	return Math::BtVector3ToVector3(vector);
}

void CollisionShape::CalculateTemporalAabb(Matrix curTrans,
	Vector3 linvel,	Vector3 angvel, btScalar timeStep,
	Vector3% temporalAabbMin, Vector3% temporalAabbMax)
{
	btVector3* tmpTemporalAabbMin = new btVector3;
	btVector3* tmpTemporalAabbMax = new btVector3;
	
	_collisionShape->calculateTemporalAabb(
		*Math::MatrixToBtTransform(curTrans),
		*Math::Vector3ToBtVector3(linvel),
		*Math::Vector3ToBtVector3(angvel),
		timeStep,
		*tmpTemporalAabbMin,
		*tmpTemporalAabbMax
	);

	temporalAabbMin = Math::BtVector3ToVector3(tmpTemporalAabbMin);
	temporalAabbMax = Math::BtVector3ToVector3(tmpTemporalAabbMax);
}

void CollisionShape::GetAabb(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* tmpAabbMin = new btVector3;
	btVector3* tmpAabbMax = new btVector3;
	
	_collisionShape->getAabb(*Math::MatrixToBtTransform(t), *tmpAabbMin, *tmpAabbMax);

	aabbMin = Math::BtVector3ToVector3(tmpAabbMin);
	aabbMax = Math::BtVector3ToVector3(tmpAabbMax);
}

void CollisionShape::GetBoundingSphere(Vector3% center, btScalar% radius)
{
	btVector3* tmpCenter = new btVector3;
	btScalar tmpRadius;
	
	_collisionShape->getBoundingSphere(*tmpCenter, tmpRadius);
	
	center = Math::BtVector3ToVector3(tmpCenter);
	radius = tmpRadius;
}

btScalar CollisionShape::GetContactBreakingThreshold(btScalar defaultContactThreshold)
{
	return _collisionShape->getContactBreakingThreshold(defaultContactThreshold);
}


btScalar CollisionShape::AngularMotionDisc::get()
{
	return _collisionShape->getAngularMotionDisc();
}

bool CollisionShape::IsCompound::get()
{
	return _collisionShape->isCompound();
}

bool CollisionShape::IsConcave::get()
{
	return _collisionShape->isConcave();
}

bool CollisionShape::IsConvex::get()
{
	return _collisionShape->isConvex();
}

bool CollisionShape::IsConvex2d::get()
{
	return _collisionShape->isConvex2d();
}

bool CollisionShape::IsInfinite::get()
{
	return _collisionShape->isInfinite();
}

bool CollisionShape::IsPolyhedral::get()
{
	return _collisionShape->isPolyhedral();
}

bool CollisionShape::IsSoftBody::get()
{
	return _collisionShape->isSoftBody();
}

Vector3 CollisionShape::LocalScaling::get()
{
	return Math::BtVector3ToVector3(&_collisionShape->getLocalScaling());
}
void CollisionShape::LocalScaling::set(Vector3 value)
{
	_collisionShape->setLocalScaling(*Math::Vector3ToBtVector3(value));
}

btScalar CollisionShape::Margin::get()
{
	return _collisionShape->getMargin();
}
void CollisionShape::Margin::set(btScalar margin)
{
	_collisionShape->setMargin(margin);
}

String^ CollisionShape::Name::get()
{
	return StringConv::UnmanagedToManaged(_collisionShape->getName());
}

BroadphaseNativeType CollisionShape::ShapeType::get()
{
	return (BroadphaseNativeType)_collisionShape->getShapeType();
}

Object^ CollisionShape::UserObject::get()
{
	void* obj = _collisionShape->getUserPointer();
	if (obj == nullptr)
		return nullptr;
	return static_cast<Object^>(__VOIDPTR_TO_GCHANDLE(obj).Target);
}

void CollisionShape::UserObject::set(Object^ value)
{
	void* obj = _collisionShape->getUserPointer();
	if (obj != nullptr)
		__VOIDPTR_TO_GCHANDLE(obj).Free();

	GCHandle handle = GCHandle::Alloc(value);
	_collisionShape->setUserPointer(__GCHANDLE_TO_VOIDPTR(handle));
}

btCollisionShape* CollisionShape::UnmanagedPointer::get()
{
	return _collisionShape;
}
