#include "StdAfx.h"

#if 0
#ifndef DISABLE_SERIALIZE

#include "WorldImporter.h"
#include "CollisionObject.h"
#include "CompoundShape.h"
#include "ConvexHullShape.h"
#include "DynamicsWorld.h"
#include "MultiSphereShape.h"
#include "RigidBody.h"
#include "StridingMeshInterface.h"
#include "StringConv.h"
#include "TriangleIndexVertexArray.h"
#ifndef DISABLE_BVH
#include "BvhTriangleMeshShape.h"
#include "OptimizedBvh.h"
#include "ScaledBvhTriangleMeshShape.h"
#endif
#ifndef DISABLE_CONSTRAINTS
#include "ConeTwistConstraint.h"
#include "GearConstraint.h"
#include "Generic6DofConstraint.h"
#include "HingeConstraint.h"
#include "Point2PointConstraint.h"
#include "SliderConstraint.h"
#include "TypedConstraint.h"
#endif
#ifndef DISABLE_GIMPACT
#include "GImpactShape.h"
#endif

Serialize::WorldImporter::WorldImporter(DynamicsWorld^ world)
{
	_native = new WorldImporterWrapper((btDynamicsWorld*)GetUnmanagedNullable(world), this);
}

Serialize::WorldImporter::WorldImporter()
{
	_native = new WorldImporterWrapper(0, this);
}

Serialize::WorldImporter::~WorldImporter()
{
	this->!WorldImporter();
}

Serialize::WorldImporter::!WorldImporter()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	delete _native;
	_native = NULL;

	OnDisposed(this, nullptr);
}

CollisionObject^ Serialize::WorldImporter::CreateCollisionObject(Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	CollisionObject^ ret = CollisionObject::GetManaged(
		_native->baseCreateCollisionObject(*startTransformTemp, shape->_native, bodyNameTemp));

	ALIGNED_FREE(startTransformTemp);
	StringConv::FreeUnmanagedString(bodyNameTemp);

	return ret;
}

RigidBody^ Serialize::WorldImporter::CreateRigidBody(bool isDynamic, btScalar mass, Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	RigidBody^ ret = (RigidBody^)CollisionObject::GetManaged(
		_native->baseCreateRigidBody(isDynamic, mass, *startTransformTemp, shape->_native, bodyNameTemp));

	ALIGNED_FREE(startTransformTemp);
	StringConv::FreeUnmanagedString(bodyNameTemp);

	return ret;
}

CollisionShape^ Serialize::WorldImporter::CreatePlaneShape(Vector3 planeNormal, btScalar planeConstant)
{
	VECTOR3_DEF(planeNormal);
	CollisionShape^ ret = CollisionShape::GetManaged(_native->baseCreatePlaneShape(VECTOR3_USE(planeNormal), planeConstant));
	VECTOR3_DEL(planeNormal);
	return ret;

}

CollisionShape^ Serialize::WorldImporter::CreateBoxShape(Vector3 halfExtents)
{
	VECTOR3_DEF(halfExtents);
	CollisionShape^ ret = CollisionShape::GetManaged(_native->baseCreateBoxShape(VECTOR3_USE(halfExtents)));
	VECTOR3_DEL(halfExtents);
	return ret;
}

CollisionShape^ Serialize::WorldImporter::CreateSphereShape(btScalar radius)
{
	return CollisionShape::GetManaged(_native->baseCreateSphereShape(radius));
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_native->baseCreateCapsuleShapeX(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_native->baseCreateCapsuleShapeY(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_native->baseCreateCapsuleShapeZ(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_native->baseCreateCylinderShapeX(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_native->baseCreateCylinderShapeY(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_native->baseCreateCylinderShapeZ(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateConeShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_native->baseCreateConeShapeX(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateConeShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_native->baseCreateConeShapeY(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateConeShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_native->baseCreateConeShapeZ(radius, height));
}

TriangleIndexVertexArray^ Serialize::WorldImporter::CreateTriangleMeshContainer()
{
	return gcnew TriangleIndexVertexArray(_native->baseCreateTriangleMeshContainer());
}

#ifndef DISABLE_BVH
BvhTriangleMeshShape^ Serialize::WorldImporter::CreateBvhTriangleMeshShape(StridingMeshInterface^ trimesh, OptimizedBvh^ bvh)
{
	return gcnew BvhTriangleMeshShape(_native->baseCreateBvhTriangleMeshShape(trimesh->_native, bvh->_native));
}
#endif

CollisionShape^ Serialize::WorldImporter::CreateConvexTriangleMeshShape(StridingMeshInterface^ trimesh)
{
	return CollisionShape::GetManaged(_native->baseCreateConvexTriangleMeshShape(trimesh->_native));
}

#ifndef DISABLE_GIMPACT
GImpactMeshShape^ Serialize::WorldImporter::CreateGImpactShape(StridingMeshInterface^ trimesh)
{
	return gcnew GImpactMeshShape(_native->baseCreateGimpactShape(trimesh->_native));
}
#endif

ConvexHullShape^ Serialize::WorldImporter::CreateConvexHullShape()
{
	return gcnew ConvexHullShape(_native->baseCreateConvexHullShape());
}

CompoundShape^ Serialize::WorldImporter::CreateCompoundShape()
{
	return gcnew CompoundShape(_native->baseCreateCompoundShape());
}

#ifndef DISABLE_BVH
ScaledBvhTriangleMeshShape^ Serialize::WorldImporter::CreateScaledTrangleMeshShape(BvhTriangleMeshShape^ meshShape, Vector3 localScaling)
{
	VECTOR3_DEF(localScaling);
	ScaledBvhTriangleMeshShape^ ret = gcnew ScaledBvhTriangleMeshShape(
		_native->baseCreateScaledTrangleMeshShape(meshShape->_native, VECTOR3_USE(localScaling)));
	VECTOR3_DEL(localScaling);
	return ret;
}

OptimizedBvh^ Serialize::WorldImporter::CreateOptimizedBvh()
{
	return gcnew OptimizedBvh(_native->baseCreateOptimizedBvh());
}
#endif

MultiSphereShape^ Serialize::WorldImporter::CreateMultiSphereShape(array<Vector3>^ positions, array<btScalar>^ radi)
{
	int numSpheres = (positions->Length < radi->Length) ? positions->Length : radi->Length;

	btVector3* positionsTemp = Math::Vector3ArrayToUnmanaged(positions);
	btScalar* radiTemp = Math::BtScalarArrayToUnmanaged(radi, numSpheres);

	MultiSphereShape^ ret = gcnew MultiSphereShape(
		_native->baseCreateMultiSphereShape(positionsTemp, radiTemp, numSpheres));

	delete[] positionsTemp;
	delete[] radiTemp;

	return ret;
}

//TriangleInfoMap^ Serialize::WorldImporter::CreateTriangleInfoMap()
//{
//	return gcnew TriangleInfoMap(_native->baseCreateTriangleInfoMap());
//}

#ifndef DISABLE_CONSTRAINTS

Point2PointConstraint^ Serialize::WorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 pivotInA, Vector3 pivotInB)
{
	VECTOR3_DEF(pivotInA);
	VECTOR3_DEF(pivotInB);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_native->baseCreatePoint2PointConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native, VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB)));

	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);

	return ret;
}

Point2PointConstraint^ Serialize::WorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA)
{
	VECTOR3_DEF(pivotInA);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_native->baseCreatePoint2PointConstraint(
		*(btRigidBody*)rigidBodyA->_native, VECTOR3_USE(pivotInA)));

	VECTOR3_DEL(pivotInA);
	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame, bool useReferenceFrameA)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_native->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp, useReferenceFrameA));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	ALIGNED_FREE(rigidBodyBFrameTemp);

	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_native->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	ALIGNED_FREE(rigidBodyBFrameTemp);

	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame, bool useReferenceFrameA)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_native->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp, useReferenceFrameA));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_native->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	return ret;
}

ConeTwistConstraint^ Serialize::WorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_native->baseCreateConeTwistConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	ALIGNED_FREE(rigidBodyBFrameTemp);

	return ret;
}

ConeTwistConstraint^ Serialize::WorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_native->baseCreateConeTwistConstraint(
		*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	return ret;
}

Generic6DofConstraint^ Serialize::WorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_native->baseCreateGeneric6DofConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*frameInATemp, *frameInBTemp, useLinearReferenceFrameA));

	ALIGNED_FREE(frameInATemp);
	ALIGNED_FREE(frameInBTemp);

	return ret;
}

Generic6DofConstraint^ Serialize::WorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_native->baseCreateGeneric6DofConstraint(
		*(btRigidBody*)rigidBodyB->_native, *frameInBTemp, useLinearReferenceFrameB));

	ALIGNED_FREE(frameInBTemp);
	return ret;
}

SliderConstraint^ Serialize::WorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	SliderConstraint^ ret = gcnew SliderConstraint(_native->baseCreateSliderConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*frameInATemp, *frameInBTemp, useLinearReferenceFrameA));

	ALIGNED_FREE(frameInATemp);
	ALIGNED_FREE(frameInBTemp);

	return ret;
}

SliderConstraint^ Serialize::WorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	SliderConstraint^ ret = gcnew SliderConstraint(_native->baseCreateSliderConstraint(
		*(btRigidBody*)rigidBodyB->_native, *frameInBTemp, useLinearReferenceFrameA));
	
	ALIGNED_FREE(frameInBTemp);
	return ret;
}

GearConstraint^ Serialize::WorldImporter::CreateGearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA, Vector3 axisInB, btScalar ratio)
{
	VECTOR3_DEF(axisInA);
	VECTOR3_DEF(axisInB);

	GearConstraint^ ret = gcnew GearConstraint(_importer->baseCreateGearConstraint(*(btRigidBody*)rigidBodyA->_native,
		*(btRigidBody*)rigidBodyB->_native, VECTOR3_USE(axisInA), VECTOR3_USE(axisInB), ratio));
	
	VECTOR3_DEL(axisInA);
	VECTOR3_DEL(axisInB);

	return ret;
}

#endif


void Serialize::WorldImporter::DeleteAllData()
{
	_native->deleteAllData();
}

CollisionShape^ Serialize::WorldImporter::GetCollisionShapeByIndex(int index)
{
	return CollisionShape::GetManaged(_native->getCollisionShapeByIndex(index));
}

CollisionObject^ Serialize::WorldImporter::GetRigidBodyByIndex(int index)
{
	return CollisionObject::GetManaged(_native->getRigidBodyByIndex(index));
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ Serialize::WorldImporter::GetConstraintByIndex(int index)
{
	btTypedConstraint* constraint = _native->getConstraintByIndex(index);
	return TypedConstraint::Upcast(constraint);
}
#endif

#ifndef DISABLE_BVH
OptimizedBvh^ Serialize::WorldImporter::GetBvhByIndex(int index)
{
	btOptimizedBvh* bvh = _native->getBvhByIndex(index);
	return bvh ? gcnew OptimizedBvh(bvh) : nullptr;
}
#endif

//TriangleInfoMap^ Serialize::WorldImporter::GetTriangleInfoMapByIndex(int index)
//{
//	return gcnew TriangleInfoMap(_native->getTriangleInfoMapByIndex(index));
//}

CollisionShape^ Serialize::WorldImporter::GetCollisionShapeByName(String^ name)
{
	btCollisionShape* shape;
	CollisionShape^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	shape = _native->getCollisionShapeByName(nameTemp);
	ret = CollisionShape::GetManaged(shape);

	StringConv::FreeUnmanagedString(nameTemp);
	return ret;
}

RigidBody^ Serialize::WorldImporter::GetRigidBodyByName(String^ name)
{
	btRigidBody* body;
	RigidBody^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	body = _native->getRigidBodyByName(nameTemp);
	ret = (RigidBody^)CollisionObject::GetManaged(body);

	StringConv::FreeUnmanagedString(nameTemp);
	return ret;
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ Serialize::WorldImporter::GetConstraintByName(String^ name)
{
	btTypedConstraint* constraint;
	TypedConstraint^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	constraint = _native->getConstraintByName(nameTemp);
	ret = TypedConstraint::Upcast(constraint);

	StringConv::FreeUnmanagedString(nameTemp);
	return ret;
}
#endif

String^	Serialize::WorldImporter::GetNameForObject(Object^ obj)
{
	const void* pointer = 0;

	CollisionShape^ shape = static_cast<CollisionShape^>(obj);
	if (shape != nullptr)
	{
		pointer = shape->_native;
		goto returnName;
	}

	CollisionObject^ body = static_cast<CollisionObject^>(obj);
	if (body != nullptr)
	{
		pointer = body->_native;
		goto returnName;
	}

#ifndef DISABLE_CONSTRAINTS
	TypedConstraint^ constraint = static_cast<TypedConstraint^>(obj);
	if (constraint != nullptr)
	{
		pointer = constraint->_native;
		goto returnName;
	}
#endif

	return nullptr;

returnName:
	const char* name = _native->getNameForPointer(pointer);
	return name ? StringConv::UnmanagedToManaged(name) : nullptr;
}

bool Serialize::WorldImporter::IsDisposed::get()
{
	return (_native == NULL);
}

int Serialize::WorldImporter::BvhCount::get()
{
	return _native->getNumBvhs();
}

int Serialize::WorldImporter::ConstraintCount::get()
{
	return _native->getNumConstraints();
}

int Serialize::WorldImporter::CollisionShapeCount::get()
{
	return _native->getNumCollisionShapes();
}

int Serialize::WorldImporter::RigidBodyCount::get()
{
	return _native->getNumRigidBodies();
}

int Serialize::WorldImporter::TriangleInfoMapCount::get()
{
	return _native->getNumTriangleInfoMaps();
}

int Serialize::WorldImporter::VerboseMode::get()
{
	return _native->getVerboseMode();
}
void Serialize::WorldImporter::VerboseMode::set(int value)
{
	_native->setVerboseMode(value);
}


Serialize::WorldImporterWrapper::WorldImporterWrapper(btDynamicsWorld* world, WorldImporter^ importer)
: btWorldImporter(world)
{
	_native = importer;
}

btCollisionObject* Serialize::WorldImporterWrapper::createCollisionObject(const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return _native->CreateCollisionObject(Math::BtTransformToMatrix(&startTransform),
		CollisionShape::GetManaged(shape), StringConv::UnmanagedToManaged(bodyName))->_native;
}

btRigidBody* Serialize::WorldImporterWrapper::createRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return (btRigidBody*)_native->CreateRigidBody(isDynamic, mass, Math::BtTransformToMatrix(&startTransform),
		CollisionShape::GetManaged(shape), StringConv::UnmanagedToManaged(bodyName))->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createPlaneShape(const btVector3& planeNormal, btScalar planeConstant)
{
	return _native->CreatePlaneShape(Math::BtVector3ToVector3(&planeNormal), planeConstant)->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createBoxShape(const btVector3& halfExtents)
{
	return _native->CreateBoxShape(Math::BtVector3ToVector3(&halfExtents))->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createSphereShape(btScalar radius)
{
	return _native->CreateSphereShape(radius)->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeX(btScalar radius, btScalar height)
{
	return _native->CreateCapsuleShapeX(radius, height)->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeY(btScalar radius, btScalar height)
{
	return _native->CreateCapsuleShapeY(radius, height)->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeZ(btScalar radius, btScalar height)
{
	return _native->CreateCapsuleShapeZ(radius, height)->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeX(btScalar radius, btScalar height)
{
	return _native->CreateCylinderShapeX(radius, height)->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeY(btScalar radius, btScalar height)
{
	return _native->CreateCylinderShapeY(radius, height)->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeZ(btScalar radius, btScalar height)
{
	return _native->CreateCylinderShapeZ(radius, height)->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createConeShapeX(btScalar radius, btScalar height)
{
	return _native->CreateConeShapeX(radius, height)->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createConeShapeY(btScalar radius, btScalar height)
{
	return _native->CreateConeShapeY(radius, height)->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createConeShapeZ(btScalar radius, btScalar height)
{
	return _native->CreateConeShapeZ(radius, height)->_native;
}

class btTriangleIndexVertexArray* Serialize::WorldImporterWrapper::createTriangleMeshContainer()
{
	return _native->CreateTriangleMeshContainer()->_native;
}

#ifndef DISABLE_BVH
btBvhTriangleMeshShape* Serialize::WorldImporterWrapper::createBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	return _native->CreateBvhTriangleMeshShape(gcnew StridingMeshInterface(trimesh), OptimizedBvh::GetManaged(bvh))->_native;
}
#endif

btCollisionShape* Serialize::WorldImporterWrapper::createConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	return _native->CreateConvexTriangleMeshShape(gcnew StridingMeshInterface(trimesh))->_native;
}

#ifndef DISABLE_GIMPACT
btGImpactMeshShape* Serialize::WorldImporterWrapper::createGimpactShape(btStridingMeshInterface* trimesh)
{
	return (btGImpactMeshShape*)_native->CreateGImpactShape(gcnew StridingMeshInterface(trimesh))->_native;
}
#endif

class btConvexHullShape* Serialize::WorldImporterWrapper::createConvexHullShape()
{
	return (btConvexHullShape*)_native->CreateConvexHullShape()->_native;
}

class btCompoundShape* Serialize::WorldImporterWrapper::createCompoundShape()
{
	return (btCompoundShape*)_native->CreateCompoundShape()->_native;
}

#ifndef DISABLE_BVH
btOptimizedBvh* Serialize::WorldImporterWrapper::createOptimizedBvh()
{
	return _native->CreateOptimizedBvh()->_native;
}
#endif

btTriangleInfoMap* Serialize::WorldImporterWrapper::createTriangleInfoMap()
{
	return baseCreateTriangleInfoMap();
	//return _native->CreateTriangleInfoMap()->_native;
}

#ifndef DISABLE_CONSTRAINTS

btPoint2PointConstraint* Serialize::WorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btVector3& pivotInA, const btVector3& pivotInB)
{
	return _native->CreatePoint2PointConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtVector3ToVector3(&pivotInA), Math::BtVector3ToVector3(&pivotInB))->_native;
}

btPoint2PointConstraint* Serialize::WorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, const btVector3& pivotInA)
{
	return _native->CreatePoint2PointConstraint((RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtVector3ToVector3(&pivotInA))->_native;
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame, bool useReferenceFrameA)
{
	return _native->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame), useReferenceFrameA)->_native;
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return _native->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame))->_native;
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame, bool useReferenceFrameA)
{
	return _native->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame), useReferenceFrameA)->_native;
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return _native->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame))->_native;
}

btConeTwistConstraint* Serialize::WorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return _native->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame))->_native;
}

btConeTwistConstraint* Serialize::WorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return _native->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame))->_native;
}

btGeneric6DofConstraint* Serialize::WorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _native->CreateGeneric6DofConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->_native;
}

btGeneric6DofConstraint* Serialize::WorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameB)
{
	return _native->CreateGeneric6DofConstraint((RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameB)->_native;
}

btSliderConstraint* Serialize::WorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _native->CreateSliderConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->_native;
}

btSliderConstraint* Serialize::WorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _native->CreateSliderConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyB), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->_native;
}

btGearConstraint* Serialize::WorldImporterWrapper::createGearConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
				const btVector3& axisInA, const btVector3& axisInB, btScalar ratio)
{
	return (btGearConstraint*)_importer->CreateGearConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtVector3ToVector3(&axisInA), Math::BtVector3ToVector3(&axisInB), ratio)->_native;
}

#endif


btCollisionObject* Serialize::WorldImporterWrapper::baseCreateCollisionObject(const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return btWorldImporter::createCollisionObject(startTransform, shape, bodyName);
}

btRigidBody* Serialize::WorldImporterWrapper::baseCreateRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return btWorldImporter::createRigidBody(isDynamic, mass, startTransform, shape, bodyName);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreatePlaneShape(const btVector3& planeNormal, btScalar planeConstant)
{
	return btWorldImporter::createPlaneShape(planeNormal, planeConstant);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateBoxShape(const btVector3& halfExtents)
{
	return btWorldImporter::createBoxShape(halfExtents);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateSphereShape(btScalar radius)
{
	return btWorldImporter::createSphereShape(radius);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateCapsuleShapeX(btScalar radius, btScalar height)
{
	return btWorldImporter::createCapsuleShapeX(radius, height);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateCapsuleShapeY(btScalar radius, btScalar height)
{
	return btWorldImporter::createCapsuleShapeY(radius, height);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateCapsuleShapeZ(btScalar radius, btScalar height)
{
	return btWorldImporter::createCapsuleShapeZ(radius, height);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateCylinderShapeX(btScalar radius, btScalar height)
{
	return btWorldImporter::createCylinderShapeX(radius, height);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateCylinderShapeY(btScalar radius, btScalar height)
{
	return btWorldImporter::createCylinderShapeY(radius, height);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateCylinderShapeZ(btScalar radius, btScalar height)
{
	return btWorldImporter::createCylinderShapeZ(radius, height);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateConeShapeX(btScalar radius, btScalar height)
{
	return btWorldImporter::createConeShapeX(radius, height);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateConeShapeY(btScalar radius, btScalar height)
{
	return btWorldImporter::createConeShapeY(radius, height);
}

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateConeShapeZ(btScalar radius, btScalar height)
{
	return btWorldImporter::createConeShapeZ(radius, height);
}

class btTriangleIndexVertexArray* Serialize::WorldImporterWrapper::baseCreateTriangleMeshContainer()
{
	return btWorldImporter::createTriangleMeshContainer();
}

#ifndef DISABLE_BVH
btBvhTriangleMeshShape* Serialize::WorldImporterWrapper::baseCreateBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	return btWorldImporter::createBvhTriangleMeshShape(trimesh, bvh);
}
#endif

btCollisionShape* Serialize::WorldImporterWrapper::baseCreateConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	return btWorldImporter::createConvexTriangleMeshShape(trimesh);
}

#ifndef DISABLE_GIMPACT
btGImpactMeshShape* Serialize::WorldImporterWrapper::baseCreateGimpactShape(btStridingMeshInterface* trimesh)
{
	return btWorldImporter::createGimpactShape(trimesh);
}
#endif

class btConvexHullShape* Serialize::WorldImporterWrapper::baseCreateConvexHullShape()
{
	return btWorldImporter::createConvexHullShape();
}

class btCompoundShape* Serialize::WorldImporterWrapper::baseCreateCompoundShape()
{
	return btWorldImporter::createCompoundShape();
}

#ifndef DISABLE_BVH
btOptimizedBvh* Serialize::WorldImporterWrapper::baseCreateOptimizedBvh()
{
	return btWorldImporter::createOptimizedBvh();
}

btScaledBvhTriangleMeshShape* Serialize::WorldImporterWrapper::baseCreateScaledTrangleMeshShape(btBvhTriangleMeshShape* meshShape,const btVector3& localScalingbtBvhTriangleMeshShape)
{
	return btWorldImporter::createScaledTrangleMeshShape(meshShape, localScalingbtBvhTriangleMeshShape);
}
#endif

btMultiSphereShape* Serialize::WorldImporterWrapper::baseCreateMultiSphereShape(const btVector3* positions, const btScalar* radi, int numSpheres)
{
	return btWorldImporter::createMultiSphereShape(positions, radi, numSpheres);
}

btTriangleInfoMap* Serialize::WorldImporterWrapper::baseCreateTriangleInfoMap()
{
	return btWorldImporter::createTriangleInfoMap();
}

#ifndef DISABLE_CONSTRAINTS

btPoint2PointConstraint* Serialize::WorldImporterWrapper::baseCreatePoint2PointConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btVector3& pivotInA, const btVector3& pivotInB)
{
	return btWorldImporter::createPoint2PointConstraint(rigidBodyA, rigidBodyB, pivotInA, pivotInB);
}

btPoint2PointConstraint* Serialize::WorldImporterWrapper::baseCreatePoint2PointConstraint(btRigidBody& rigidBodyA, const btVector3& pivotInA)
{
	return btWorldImporter::createPoint2PointConstraint(rigidBodyA, pivotInA);
}

btHingeConstraint* Serialize::WorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame, bool useReferenceFrameA)
{
	return btWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame, useReferenceFrameA);
}

btHingeConstraint* Serialize::WorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return btWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame);
}

btHingeConstraint* Serialize::WorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame, bool useReferenceFrameA)
{
	return btWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyAFrame, useReferenceFrameA);
}

btHingeConstraint* Serialize::WorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return btWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyAFrame);
}

btConeTwistConstraint* Serialize::WorldImporterWrapper::baseCreateConeTwistConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return btWorldImporter::createConeTwistConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame);
}

btConeTwistConstraint* Serialize::WorldImporterWrapper::baseCreateConeTwistConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return btWorldImporter::createConeTwistConstraint(rigidBodyA, rigidBodyAFrame);
}

btGeneric6DofConstraint* Serialize::WorldImporterWrapper::baseCreateGeneric6DofConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btWorldImporter::createGeneric6DofConstraint(rigidBodyA, rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
}

btGeneric6DofConstraint* Serialize::WorldImporterWrapper::baseCreateGeneric6DofConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameB)
{
	return btWorldImporter::createGeneric6DofConstraint(rigidBodyB, frameInB, useLinearReferenceFrameB);
}

btSliderConstraint* Serialize::WorldImporterWrapper::baseCreateSliderConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btWorldImporter::createSliderConstraint(rigidBodyA, rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
}

btSliderConstraint* Serialize::WorldImporterWrapper::baseCreateSliderConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btWorldImporter::createSliderConstraint(rigidBodyB, frameInB, useLinearReferenceFrameA);
}

btGearConstraint* Serialize::WorldImporterWrapper::baseCreateGearConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btVector3& axisInA, const btVector3& axisInB, btScalar ratio)
{
	return btWorldImporter::createGearConstraint(rigidBodyA, rigidBodyB, axisInA, axisInB, ratio);
}

#endif

#endif
#endif