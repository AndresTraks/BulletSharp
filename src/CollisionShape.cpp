#include "StdAfx.h"

#include "BoxShape.h"
#include "CapsuleShape.h"
#include "CollisionShape.h"
#include "CompoundShape.h"
#include "ConeShape.h"
#include "ConvexHullShape.h"
#include "ConvexShape.h"
#include "ConvexTriangleMeshShape.h"
#include "CylinderShape.h"
#include "ConvexShape.h"
#include "EmptyShape.h"
//#include "HfFluidBuoyantConvexShape.h"
//#include "HfFluidShape.h"
#include "MultiSphereShape.h"
#include "SphereShape.h"
#include "StaticPlaneShape.h"
#include "StringConv.h"
#include "TriangleMeshShape.h"
#include "UniformScalingShape.h"
#ifndef DISABLE_GIMPACT
#include "GImpactShape.h"
#endif
#include "CollisionShape.h"
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif
#ifndef DISABLE_UNCOMMON
#include "Box2dShape.h"
#include "Convex2DShape.h"
#include "ConvexPointCloudShape.h"
#include "HeightfieldTerrainShape.h"
#include "MinkowskiSumShape.h"
#include "MultimaterialTriangleMeshShape.h"
#include "StringConv.h"
#include "TriangleShape.h"
#endif

CollisionShape::CollisionShape(btCollisionShape* collisionShape)
{
	// UnmanagedPointer may be set later if a child constructor does
	// extra processing, so check for NULL here.
	if (collisionShape)
		UnmanagedPointer = collisionShape;
}

CollisionShape^ CollisionShape::GetManaged(btCollisionShape* collisionShape)
{
	if (collisionShape == 0)
		return nullptr;

	void* userObj = collisionShape->getUserPointer();
	if (userObj)
		return static_cast<CollisionShape^>(VoidPtrToGCHandle(userObj).Target);

	// If we reach here, then collisionShape was created from within unmanaged code,
	// create a wrapper object based on the shape type.
	BroadphaseNativeType type = (BroadphaseNativeType)collisionShape->getShapeType();
	CollisionShape^ shape;
	switch(type)
	{
	case BroadphaseNativeType::BoxShape:
		shape = gcnew BoxShape((btBoxShape*) collisionShape);
		break;
	case BroadphaseNativeType::CapsuleShape:
		shape = gcnew CapsuleShape((btCapsuleShape*) collisionShape);
		break;
	case BroadphaseNativeType::CompoundShape:
		shape = gcnew CompoundShape((btCompoundShape*) collisionShape);
		break;
	case BroadphaseNativeType::ConeShape:
		shape = gcnew ConeShape((btConeShape*) collisionShape);
		break;
	case BroadphaseNativeType::ConvexHullShape:
		shape = gcnew ConvexHullShape((btConvexHullShape*) collisionShape);
		break;
	case BroadphaseNativeType::ConvexShape:
		shape = gcnew ConvexShape((btConvexShape*) collisionShape);
		break;
	case BroadphaseNativeType::ConvexTriangleMeshShape:
		shape = gcnew ConvexTriangleMeshShape((btConvexTriangleMeshShape*) collisionShape);
		break;
	//case BroadphaseNativeType::CustomConcaveShape:
	//	shape = gcnew CustomConcaveShape((btCustomConcaveShape*) collisionShape);
	//	break;
	//case BroadphaseNativeType::CustomPolyhedralShape:
	//	shape = gcnew CustomPolyhedralShape((btCustomPolyhedralShape*) collisionShape);
	//	break;
	case BroadphaseNativeType::CylinderShape:
		shape = gcnew CylinderShape((btCylinderShape*) collisionShape);
		break;
	case BroadphaseNativeType::EmptyShape:
		shape = gcnew EmptyShape((btEmptyShape*) collisionShape);
		break;
	//case BroadphaseNativeType::FastConcaveMesh:
	//	shape = gcnew FastConcaveMesh((btFastConcaveMesh*) collisionShape);
	//	break;
	//case BroadphaseNativeType::HfFluidBuoyantConvexShape:
	//	shape = gcnew HfFluidBuoyantConvexShape((btHfFluidBuoyantConvexShape*) collisionShape);
	//	break;
	//case BroadphaseNativeType::HfFluidShape:
	//	shape = gcnew HfFluidShape((btHfFluidShape*) collisionShape);
	//	break;
	//case BroadphaseNativeType::MinkowskiDifferenceShape:
	//	shape = gcnew MinkowskiDifferenceShape((btMinkowskiDifferenceShape*) collisionShape);
	//	break;
	case BroadphaseNativeType::MultiSphereShape:
		shape = gcnew MultiSphereShape((btMultiSphereShape*) collisionShape);
		break;
	//case BroadphaseNativeType::ScaledTriangleMeshShape:
	//	shape = gcnew ScaledTriangleMeshShape((btScaledTriangleMeshShape*) collisionShape);
	//	break;
	case BroadphaseNativeType::SphereShape:
		shape = gcnew SphereShape((btSphereShape*) collisionShape);
		break;
	case BroadphaseNativeType::StaticPlane:
		shape = gcnew StaticPlaneShape((btStaticPlaneShape*) collisionShape);
		break;
	//case BroadphaseNativeType::TetrahedralShape:
	//	shape = gcnew TetrahedralShape((btTetrahedralShape*) collisionShape);
	//	break;
	case BroadphaseNativeType::UniformScalingShape:
		shape = gcnew UniformScalingShape((btUniformScalingShape*) collisionShape);
		break;

#ifndef DISABLE_GIMPACT
	case BroadphaseNativeType::GImpactShape:
		shape = gcnew GImpactMeshShape((btGImpactMeshShape*) collisionShape);
		break;
#endif

#ifndef DISABLE_UNCOMMON
	case BroadphaseNativeType::Box2dShape:
		shape = gcnew Box2dShape((btBox2dShape*) collisionShape);
		break;
	case BroadphaseNativeType::Convex2DShape:
		shape = gcnew Convex2DShape((btConvex2dShape*) collisionShape);
		break;
	case BroadphaseNativeType::ConvexPointCloudShape:
		shape = gcnew ConvexPointCloudShape((btConvexPointCloudShape*) collisionShape);
		break;
	case BroadphaseNativeType::MinkowskiSumShape:
		shape = gcnew MinkowskiSumShape((btMinkowskiSumShape*) collisionShape);
		break;
	case BroadphaseNativeType::MultiMaterialTriangleMesh:
		shape = gcnew MultimaterialTriangleMeshShape((btMultimaterialTriangleMeshShape*) collisionShape);
		break;
	case BroadphaseNativeType::TerrainShape:
		shape = gcnew HeightfieldTerrainShape((btHeightfieldTerrainShape*) collisionShape);
		break;
	case BroadphaseNativeType::TriangleMeshShape:
		shape = gcnew TriangleMeshShape((btTriangleMeshShape*) collisionShape);
		break;
	case BroadphaseNativeType::TriangleShape:
		shape = gcnew TriangleShape((btTriangleShape*) collisionShape);
		break;
#endif

	default:
		shape = gcnew CollisionShape(collisionShape);
	}

	// Tell the wrapper object we just created not to destroy this collisionShape.
	shape->_flags = 2;

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

	// delete the btCollisionShape only if we are responsible for it
	if (_flags != 2)
	{
		void* userObj = _unmanaged->getUserPointer();
		if (userObj)
			VoidPtrToGCHandle(userObj).Free();
		delete _unmanaged;
	}
	_flags |= 1;

	OnDisposed(this, nullptr);
}

bool CollisionShape::IsDisposed::get()
{
	return _flags & 1;
}

void CollisionShape::CalculateLocalInertia(btScalar mass, [Out] Vector3% inertia)
{
	btVector3* inertiaTemp = new btVector3;
	_unmanaged->calculateLocalInertia(mass, *inertiaTemp);
	Math::BtVector3ToVector3(inertiaTemp, inertia);
	delete inertiaTemp;
}

Vector3 CollisionShape::CalculateLocalInertia(btScalar mass)
{
	btVector3* inertiaTemp = new btVector3;
	_unmanaged->calculateLocalInertia(mass, *inertiaTemp);
	Vector3 inertia = Math::BtVector3ToVector3(inertiaTemp);
	delete inertiaTemp;
	return inertia;
}

void CollisionShape::CalculateTemporalAabb(Matrix curTrans,
	Vector3 linvel,	Vector3 angvel, btScalar timeStep,
	Vector3% temporalAabbMin, Vector3% temporalAabbMax)
{
	btTransform* curTransTemp = Math::MatrixToBtTransform(curTrans);
	btVector3* temporalAabbMinTemp = new btVector3;
	btVector3* temporalAabbMaxTemp = new btVector3;
	VECTOR3_DEF(linvel);
	VECTOR3_DEF(angvel);

	_unmanaged->calculateTemporalAabb(*curTransTemp, VECTOR3_USE(linvel), VECTOR3_USE(angvel),
		timeStep, *temporalAabbMinTemp,	*temporalAabbMaxTemp
	);

	temporalAabbMin = Math::BtVector3ToVector3(temporalAabbMaxTemp);
	temporalAabbMax = Math::BtVector3ToVector3(temporalAabbMaxTemp);

	delete curTransTemp;
	delete temporalAabbMinTemp;
	delete temporalAabbMaxTemp;
	VECTOR3_DEL(linvel);
	VECTOR3_DEL(angvel);
}

void CollisionShape::GetAabb(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	btTransform* tTemp = Math::MatrixToBtTransform(t);
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;
	
	_unmanaged->getAabb(*tTemp, *aabbMinTemp, *aabbMaxTemp);

	aabbMin = Math::BtVector3ToVector3(aabbMinTemp);
	aabbMax = Math::BtVector3ToVector3(aabbMaxTemp);

	delete tTemp;
	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void CollisionShape::GetBoundingSphere(Vector3% center, btScalar% radius)
{
	btVector3* centerTemp = new btVector3;
	btScalar radiusTemp;
	
	_unmanaged->getBoundingSphere(*centerTemp, radiusTemp);
	
	center = Math::BtVector3ToVector3(centerTemp);
	radius = radiusTemp;
	delete centerTemp;
}

btScalar CollisionShape::GetContactBreakingThreshold(btScalar defaultContactThreshold)
{
	return _unmanaged->getContactBreakingThreshold(defaultContactThreshold);
}

#ifndef DISABLE_SERIALIZE
int CollisionShape::CalculateSerializeBufferSize()
{
	return _unmanaged->calculateSerializeBufferSize();
}

String^ CollisionShape::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	const char* name = _unmanaged->serialize(dataBuffer.ToPointer(), serializer->UnmanagedPointer);
	return gcnew String(name);
}

void CollisionShape::SerializeSingleShape(BulletSharp::Serializer^ serializer)
{
	_unmanaged->serializeSingleShape(serializer->UnmanagedPointer);
}
#endif

btScalar CollisionShape::AngularMotionDisc::get()
{
	return _unmanaged->getAngularMotionDisc();
}

#pragma managed(push, off)
void CollisionShape_AnisotropicRollingFrictionDirection(btCollisionShape* shape, btVector3* ret)
{
	*ret = shape->getAnisotropicRollingFrictionDirection();
}
#pragma managed(pop)
Vector3 CollisionShape::AnisotropicRollingFrictionDirection::get()
{
	btVector3* retTemp = new btVector3;
	CollisionShape_AnisotropicRollingFrictionDirection(_unmanaged, retTemp);
	Vector3 ret = Math::BtVector3ToVector3(retTemp);
	delete retTemp;
	return ret;
}

bool CollisionShape::IsCompound::get()
{
	return _unmanaged->isCompound();
}

bool CollisionShape::IsConcave::get()
{
	return _unmanaged->isConcave();
}

bool CollisionShape::IsConvex::get()
{
	return _unmanaged->isConvex();
}

bool CollisionShape::IsConvex2d::get()
{
	return _unmanaged->isConvex2d();
}

bool CollisionShape::IsInfinite::get()
{
	return _unmanaged->isInfinite();
}

bool CollisionShape::IsPolyhedral::get()
{
	return _unmanaged->isPolyhedral();
}

bool CollisionShape::IsSoftBody::get()
{
	return _unmanaged->isSoftBody();
}

Vector3 CollisionShape::LocalScaling::get()
{
	return Math::BtVector3ToVector3(&_unmanaged->getLocalScaling());
}
void CollisionShape::LocalScaling::set(Vector3 value)
{
	VECTOR3_DEF(value);
	_unmanaged->setLocalScaling(VECTOR3_USE(value));
	VECTOR3_DEL(value);
}

btScalar CollisionShape::Margin::get()
{
	return _unmanaged->getMargin();
}
void CollisionShape::Margin::set(btScalar margin)
{
	_unmanaged->setMargin(margin);
}

String^ CollisionShape::Name::get()
{
	return StringConv::UnmanagedToManaged(_unmanaged->getName());
}

BroadphaseNativeType CollisionShape::ShapeType::get()
{
	return _shapeType;
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
	return _unmanaged;
}
void CollisionShape::UnmanagedPointer::set(btCollisionShape* value)
{
	_unmanaged = value;

	if (_unmanaged->getUserPointer() == 0)
	{
		GCHandle handle = GCHandle::Alloc(this);
		void* obj = GCHandleToVoidPtr(handle);
		_unmanaged->setUserPointer(obj);
	}

	_shapeType = (BroadphaseNativeType)_unmanaged->getShapeType();
}
