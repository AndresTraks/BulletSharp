#include "StdAfx.h"

#include "Box2dShape.h"
#include "BoxShape.h"
#include "CapsuleShape.h"
#include "CollisionShape.h"
#include "CompoundShape.h"
#include "ConeShape.h"
#include "Convex2dShape.h"
#include "ConvexHullShape.h"
#include "ConvexPointCloudShape.h"
#include "ConvexShape.h"
#include "ConvexTriangleMeshShape.h"
#include "CylinderShape.h"
#include "ConvexShape.h"
#include "EmptyShape.h"
//#include "HfFluidBuoyantConvexShape.h"
//#include "HfFluidShape.h"
#include "MinkowskiSumShape.h"
#include "MultimaterialTriangleMeshShape.h"
#include "MultiSphereShape.h"
#include "StaticPlaneShape.h"
#include "StringConv.h"
#include "TriangleMeshShape.h"
#include "TriangleShape.h"
#include "UniformScalingShape.h"
#ifndef DISABLE_GIMPACT
#include "GImpactShape.h"
#endif
#ifndef DISABLE_SERIALIZE
#include "Serializer.h"
#endif

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

CollisionShape^ CollisionShape::UpcastDetect()
{
	switch(ShapeType)
	{
	case BroadphaseNativeType::Box2dShape:
		return gcnew Box2dShape((btBox2dShape*) _collisionShape);
	case BroadphaseNativeType::BoxShape:
		return gcnew BoxShape((btBoxShape*) _collisionShape);
	case BroadphaseNativeType::CapsuleShape:
		return gcnew CapsuleShape((btCapsuleShape*) _collisionShape);
	case BroadphaseNativeType::CompoundShape:
		return gcnew CompoundShape((btCompoundShape*) _collisionShape);
	case BroadphaseNativeType::ConeShape:
		return gcnew ConeShape((btConeShape*) _collisionShape);
	case BroadphaseNativeType::Convex2dShape:
		return gcnew Convex2dShape((btConvex2dShape*) _collisionShape);
	case BroadphaseNativeType::ConvexHullShape:
		return gcnew ConvexHullShape((btConvexHullShape*) _collisionShape);
	case BroadphaseNativeType::ConvexPointCloudShape:
		return gcnew ConvexPointCloudShape((btConvexPointCloudShape*) _collisionShape);
	case BroadphaseNativeType::ConvexShape:
		return gcnew ConvexShape((btConvexShape*) _collisionShape);
	case BroadphaseNativeType::ConvexTriangleMeshShape:
		return gcnew ConvexTriangleMeshShape((btConvexTriangleMeshShape*) _collisionShape);
	//case BroadphaseNativeType::CustomConcaveShape:
	//	return gcnew CustomConcaveShape((btCustomConcaveShape*) _collisionShape);
	//case BroadphaseNativeType::CustomPolyhedralShape:
	//	return gcnew CustomPolyhedralShape((btCustomPolyhedralShape*) _collisionShape);
	case BroadphaseNativeType::CylinderShape:
		return gcnew CylinderShape((btCylinderShape*) _collisionShape);
	case BroadphaseNativeType::EmptyShape:
		return gcnew EmptyShape((btEmptyShape*) _collisionShape);
	//case BroadphaseNativeType::FastConcaveMesh:
	//	return gcnew FastConcaveMesh((btFastConcaveMesh*) _collisionShape);
	//case BroadphaseNativeType::HfFluidBuoyantConvexShape:
	//	return gcnew HfFluidBuoyantConvexShape((btHfFluidBuoyantConvexShape*) _collisionShape);
	//case BroadphaseNativeType::HfFluidShape:
	//	return gcnew HfFluidShape((btHfFluidShape*) _collisionShape);
	//case BroadphaseNativeType::MinkowskiDifferenceShape:
	//	return gcnew MinkowskiDifferenceShape((btMinkowskiDifferenceShape*) _collisionShape);
	case BroadphaseNativeType::MinkowskiSumShape:
		return gcnew MinkowskiSumShape((btMinkowskiSumShape*) _collisionShape);
	case BroadphaseNativeType::MultiSphereShape:
		return gcnew MultiSphereShape((btMultiSphereShape*) _collisionShape);
	//case BroadphaseNativeType::ScaledTriangleMeshShape:
	//	return gcnew ScaledTriangleMeshShape((btScaledTriangleMeshShape*) _collisionShape);
	case BroadphaseNativeType::StaticPlane:
		return gcnew StaticPlaneShape((btStaticPlaneShape*) _collisionShape);
	//case BroadphaseNativeType::SoftBodyShape:
	//	return gcnew SoftBody((btSoftBody*) _collisionShape);
	//case BroadphaseNativeType::TerrainShape:
	//	return gcnew TerrainShape((btTerrainShape*) _collisionShape);
	//case BroadphaseNativeType::TetrahedralShape:
	//	return gcnew TetrahedralShape((btTetrahedralShape*) _collisionShape);
	case BroadphaseNativeType::TriangleShape:
		return gcnew TriangleShape((btTriangleShape*) _collisionShape);
	case BroadphaseNativeType::UniformScalingShape:
		return gcnew UniformScalingShape((btUniformScalingShape*) _collisionShape);

	case BroadphaseNativeType::GImpactShape:
	{
#ifndef DISABLE_GIMPACT
		return gcnew GImpactMeshShape((btGImpactMeshShape*) _collisionShape);
#else
		return this;
#endif
	}

	case BroadphaseNativeType::MultiMaterialTriangleMesh:
		return gcnew MultimaterialTriangleMeshShape((btMultimaterialTriangleMeshShape*) _collisionShape);
	case BroadphaseNativeType::TriangleMeshShape:
		return gcnew TriangleMeshShape((btTriangleMeshShape*) _collisionShape);

	default:
		return this;
	}
}

void CollisionShape::CalculateLocalInertia(btScalar mass, Vector3% inertia)
{
	btVector3* inertiaTemp = new btVector3;
	_collisionShape->calculateLocalInertia(mass, *inertiaTemp);
	inertia = Math::BtVector3ToVector3(inertiaTemp);
	delete inertiaTemp;
}

Vector3 CollisionShape::CalculateLocalInertia(btScalar mass)
{
	btVector3* inertiaTemp = new btVector3;
	_collisionShape->calculateLocalInertia(mass, *inertiaTemp);
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
	btVector3* linvelTemp = Math::Vector3ToBtVector3(linvel);
	btVector3* angvelTemp = Math::Vector3ToBtVector3(angvel);

	_collisionShape->calculateTemporalAabb(*curTransTemp, *linvelTemp, *angvelTemp,
		timeStep, *temporalAabbMinTemp,	*temporalAabbMaxTemp
	);

	temporalAabbMin = Math::BtVector3ToVector3(temporalAabbMaxTemp);
	temporalAabbMax = Math::BtVector3ToVector3(temporalAabbMaxTemp);

	delete curTransTemp;
	delete temporalAabbMinTemp;
	delete temporalAabbMaxTemp;
	delete linvelTemp;
	delete angvelTemp;
}

void CollisionShape::GetAabb(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* aabbMinTemp = new btVector3;
	btVector3* aabbMaxTemp = new btVector3;
	
	_collisionShape->getAabb(*Math::MatrixToBtTransform(t), *aabbMinTemp, *aabbMaxTemp);

	aabbMin = Math::BtVector3ToVector3(aabbMinTemp);
	aabbMax = Math::BtVector3ToVector3(aabbMaxTemp);

	delete aabbMinTemp;
	delete aabbMaxTemp;
}

void CollisionShape::GetBoundingSphere(Vector3% center, btScalar% radius)
{
	btVector3* centerTemp = new btVector3;
	btScalar radiusTemp;
	
	_collisionShape->getBoundingSphere(*centerTemp, radiusTemp);
	
	center = Math::BtVector3ToVector3(centerTemp);
	radius = radiusTemp;
}

btScalar CollisionShape::GetContactBreakingThreshold(btScalar defaultContactThreshold)
{
	return _collisionShape->getContactBreakingThreshold(defaultContactThreshold);
}

#ifndef DISABLE_SERIALIZE
int CollisionShape::CalculateSerializeBufferSize()
{
	return UnmanagedPointer->calculateSerializeBufferSize();
}

String^ CollisionShape::Serialize(IntPtr dataBuffer, BulletSharp::Serializer^ serializer)
{
	const char* name = UnmanagedPointer->serialize(dataBuffer.ToPointer(), serializer->UnmanagedPointer);
	return gcnew String(name);
}

void CollisionShape::SerializeSingleShape(BulletSharp::Serializer^ serializer)
{
	UnmanagedPointer->serializeSingleShape(serializer->UnmanagedPointer);
}
#endif

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
	btVector3* valueTemp = Math::Vector3ToBtVector3(value);
	_collisionShape->setLocalScaling(*valueTemp);
	delete valueTemp;
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
	return static_cast<Object^>(VoidPtrToGCHandle(obj).Target);
}

void CollisionShape::UserObject::set(Object^ value)
{
	void* obj = _collisionShape->getUserPointer();
	if (obj != nullptr)
		VoidPtrToGCHandle(obj).Free();

	GCHandle handle = GCHandle::Alloc(value);
	_collisionShape->setUserPointer(GCHandleToVoidPtr(handle));
}

btCollisionShape* CollisionShape::UnmanagedPointer::get()
{
	return _collisionShape;
}
void CollisionShape::UnmanagedPointer::set(btCollisionShape* value)
{
	_collisionShape = value;
}
