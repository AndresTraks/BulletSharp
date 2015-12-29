#include "StdAfx.h"

#include "CollisionShape.h"
#include "StringConv.h"
#include "CollisionShape.h"
#include "TriangleShape.h"
#ifndef DISABLE_GIMPACT
#include "GImpactShape.h"
#endif
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

CollisionShape::CollisionShape(btCollisionShape* native)
{
	// UnmanagedPointer may be set later if a child constructor does
	// extra processing, so check for NULL here.
	if (native)
		UnmanagedPointer = native;
}

CollisionShape^ CollisionShape::GetManaged(btCollisionShape* collisionShape)
{
	if (collisionShape == 0) {
		return nullptr;
	}

	void* userObj = collisionShape->getUserPointer();
	if (userObj)
		return static_cast<CollisionShape^>(VoidPtrToGCHandle(userObj).Target);

	// If we reach here, then collisionShape was created from within unmanaged code,
	// create a wrapper object based on the shape type.
	BroadphaseNativeType type = (BroadphaseNativeType)collisionShape->getShapeType();
	CollisionShape^ shape;
	switch(type)
	{
	case BroadphaseNativeType::TetrahedralShape: // Required for CompoundFromGImpact.Create
		shape = gcnew BuSimplex1To4((btBU_Simplex1to4*) collisionShape);
		break;
	case BroadphaseNativeType::TriangleShape: // Required for ContactCallback from convex-concave algorithm
		shape = gcnew TriangleShape((btTriangleShape*) collisionShape);
		break;
	case BroadphaseNativeType::GImpactShape: // Required for GImpactMeshShape.GetMeshPart
		shape = gcnew GImpactMeshShapePart((btGImpactMeshShapePart*) collisionShape);
		break;
	default:
		throw gcnew NotImplementedException();
		//shape = gcnew CollisionShape(collisionShape);
	}

	shape->_preventDelete = true;
	return shape;
}

CollisionShape::~CollisionShape()
{
	this->!CollisionShape();
}

CollisionShape::!CollisionShape()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	void* userObj = _native->getUserPointer();
	if (userObj)
	{
		VoidPtrToGCHandle(userObj).Free();
	}

	// delete the btCollisionShape only if we are responsible for it
	if (!_preventDelete)
	{
		delete _native;
	}
	_isDisposed = true;

	OnDisposed(this, nullptr);
}

void CollisionShape::CalculateLocalInertia(btScalar mass, [Out] Vector3% inertia)
{
	btVector3* inertiaTemp = ALIGNED_NEW(btVector3);
	_native->calculateLocalInertia(mass, *inertiaTemp);
	Math::BtVector3ToVector3(inertiaTemp, inertia);
	ALIGNED_FREE(inertiaTemp);
}

Vector3 CollisionShape::CalculateLocalInertia(btScalar mass)
{
	btVector3* inertiaTemp = ALIGNED_NEW(btVector3);
	_native->calculateLocalInertia(mass, *inertiaTemp);
	Vector3 inertia = Math::BtVector3ToVector3(inertiaTemp);
	ALIGNED_FREE(inertiaTemp);
	return inertia;
}

#ifndef DISABLE_SERIALIZE
int CollisionShape::CalculateSerializeBufferSize()
{
	return _native->calculateSerializeBufferSize();
}
#endif

void CollisionShape::CalculateTemporalAabb(Matrix% curTrans, Vector3% linvel, Vector3% angvel,
	btScalar timeStep, [Out] Vector3% temporalAabbMin, [Out] Vector3% temporalAabbMax)
{
	TRANSFORM_CONV(curTrans);
	VECTOR3_CONV(linvel);
	VECTOR3_CONV(angvel);
	btVector3* temporalAabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* temporalAabbMaxTemp = ALIGNED_NEW(btVector3);
	_native->calculateTemporalAabb(TRANSFORM_USE(curTrans), VECTOR3_USE(linvel), VECTOR3_USE(angvel),
		timeStep, *temporalAabbMinTemp,	*temporalAabbMaxTemp);
	Math::BtVector3ToVector3(temporalAabbMaxTemp, temporalAabbMin);
	Math::BtVector3ToVector3(temporalAabbMaxTemp, temporalAabbMax);
	TRANSFORM_DEL(curTrans);
	VECTOR3_DEL(linvel);
	VECTOR3_DEL(angvel);
	ALIGNED_FREE(temporalAabbMinTemp);
	ALIGNED_FREE(temporalAabbMaxTemp);
}

void CollisionShape::CalculateTemporalAabb(Matrix curTrans, Vector3 linvel, Vector3 angvel,
	btScalar timeStep, [Out] Vector3% temporalAabbMin, [Out] Vector3% temporalAabbMax)
{
	TRANSFORM_CONV(curTrans);
	VECTOR3_CONV(linvel);
	VECTOR3_CONV(angvel);
	btVector3* temporalAabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* temporalAabbMaxTemp = ALIGNED_NEW(btVector3);
	_native->calculateTemporalAabb(TRANSFORM_USE(curTrans), VECTOR3_USE(linvel), VECTOR3_USE(angvel),
		timeStep, *temporalAabbMinTemp,	*temporalAabbMaxTemp);
	Math::BtVector3ToVector3(temporalAabbMaxTemp, temporalAabbMin);
	Math::BtVector3ToVector3(temporalAabbMaxTemp, temporalAabbMax);
	TRANSFORM_DEL(curTrans);
	VECTOR3_DEL(linvel);
	VECTOR3_DEL(angvel);
	ALIGNED_FREE(temporalAabbMinTemp);
	ALIGNED_FREE(temporalAabbMaxTemp);
}

bool CollisionShape::Equals(Object^ obj)
{
	return Object::ReferenceEquals(this, obj);
}

void CollisionShape::GetAabbRef(Matrix% t, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax)
{
	TRANSFORM_CONV(t);
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	_native->getAabb(TRANSFORM_USE(t), *aabbMinTemp, *aabbMaxTemp);
	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);
	TRANSFORM_DEL(t);
	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

void CollisionShape::GetAabb(Matrix t, [Out] Vector3% aabbMin, [Out] Vector3% aabbMax)
{
	TRANSFORM_CONV(t);
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	_native->getAabb(TRANSFORM_USE(t), *aabbMinTemp, *aabbMaxTemp);
	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);
	TRANSFORM_DEL(t);
	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

void CollisionShape::GetBoundingSphere([Out] Vector3% center, [Out] btScalar% radius)
{
	btVector3* centerTemp = ALIGNED_NEW(btVector3);
	btScalar radiusTemp;
	
	_native->getBoundingSphere(*centerTemp, radiusTemp);
	
	center = Math::BtVector3ToVector3(centerTemp);
	radius = radiusTemp;
	ALIGNED_FREE(centerTemp);
}

btScalar CollisionShape::GetContactBreakingThreshold(btScalar defaultContactThresholdFactor)
{
	return _native->getContactBreakingThreshold(defaultContactThresholdFactor);
}

int CollisionShape::GetHashCode()
{
	return (int)_native;
}

#ifndef DISABLE_SERIALIZE
String^ CollisionShape::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	return gcnew String(_native->serialize(dataBuffer.ToPointer(), serializer->_native));
}

void CollisionShape::SerializeSingleShape(BulletSharp::Serializer^ serializer)
{
	_native->serializeSingleShape(serializer->_native);
}
#endif

btScalar CollisionShape::AngularMotionDisc::get()
{
	return _native->getAngularMotionDisc();
}

#pragma managed(push, off)
void CollisionShape_AnisotropicRollingFrictionDirection(btCollisionShape* shape, btVector3* ret)
{
	*ret = shape->getAnisotropicRollingFrictionDirection();
}
#pragma managed(pop)
Vector3 CollisionShape::AnisotropicRollingFrictionDirection::get()
{
	btVector3* retTemp = ALIGNED_NEW(btVector3);
	CollisionShape_AnisotropicRollingFrictionDirection(_native, retTemp);
	Vector3 ret = Math::BtVector3ToVector3(retTemp);
	ALIGNED_FREE(retTemp);
	return ret;
}

bool CollisionShape::IsCompound::get()
{
	return _native->isCompound();
}

bool CollisionShape::IsConcave::get()
{
	return _native->isConcave();
}

bool CollisionShape::IsConvex::get()
{
	return _native->isConvex();
}

bool CollisionShape::IsConvex2D::get()
{
	return _native->isConvex2d();
}

bool CollisionShape::IsDisposed::get()
{
	return _isDisposed;
}

bool CollisionShape::IsInfinite::get()
{
	return _native->isInfinite();
}

bool CollisionShape::IsNonMoving::get()
{
	return _native->isNonMoving();
}

bool CollisionShape::IsPolyhedral::get()
{
	return _native->isPolyhedral();
}

bool CollisionShape::IsSoftBody::get()
{
	return _native->isSoftBody();
}

Vector3 CollisionShape::LocalScaling::get()
{
	return Math::BtVector3ToVector3(&_native->getLocalScaling());
}
void CollisionShape::LocalScaling::set(Vector3 scaling)
{
	VECTOR3_CONV(scaling);
	_native->setLocalScaling(VECTOR3_USE(scaling));
	VECTOR3_DEL(scaling);
}

btScalar CollisionShape::Margin::get()
{
	return _native->getMargin();
}
void CollisionShape::Margin::set(btScalar margin)
{
	_native->setMargin(margin);
}

String^ CollisionShape::Name::get()
{
	return StringConv::UnmanagedToManaged(_native->getName());
}

BroadphaseNativeType CollisionShape::ShapeType::get()
{
	return _shapeType;
}

int CollisionShape::UserIndex::get()
{
	return _native->getUserIndex();
}
void CollisionShape::UserIndex::set(int index)
{
	_native->setUserIndex(index);
}

Object^ CollisionShape::UserObject::get()
{
	return _userObject;
}

void CollisionShape::UserObject::set(Object^ value)
{
	_userObject = value;
}

btCollisionShape* CollisionShape::UnmanagedPointer::get()
{
	return _native;
}
void CollisionShape::UnmanagedPointer::set(btCollisionShape* value)
{
	_native = value;

	if (_native->getUserPointer() == 0)
	{
		GCHandle handle = GCHandle::Alloc(this, GCHandleType::Weak);
		void* obj = GCHandleToVoidPtr(handle);
		_native->setUserPointer(obj);
	}

	_shapeType = (BroadphaseNativeType)_native->getShapeType();
}
