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
	_unmanaged = new WorldImporterWrapper((btDynamicsWorld*)GetUnmanagedNullable(world), this);
}

Serialize::WorldImporter::WorldImporter()
{
	_unmanaged = new WorldImporterWrapper(0, this);
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

	delete _unmanaged;
	_unmanaged = NULL;

	OnDisposed(this, nullptr);
}

CollisionObject^ Serialize::WorldImporter::CreateCollisionObject(Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	CollisionObject^ ret = CollisionObject::GetManaged(
		_unmanaged->baseCreateCollisionObject(*startTransformTemp, shape->UnmanagedPointer, bodyNameTemp));

	delete startTransformTemp;
	StringConv::FreeUnmanagedString(bodyNameTemp);

	return ret;
}

RigidBody^ Serialize::WorldImporter::CreateRigidBody(bool isDynamic, btScalar mass, Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	RigidBody^ ret = (RigidBody^)CollisionObject::GetManaged(
		_unmanaged->baseCreateRigidBody(isDynamic, mass, *startTransformTemp, shape->UnmanagedPointer, bodyNameTemp));

	delete startTransformTemp;
	StringConv::FreeUnmanagedString(bodyNameTemp);

	return ret;
}

CollisionShape^ Serialize::WorldImporter::CreatePlaneShape(Vector3 planeNormal, btScalar planeConstant)
{
	VECTOR3_DEF(planeNormal);
	CollisionShape^ ret = CollisionShape::GetManaged(_unmanaged->baseCreatePlaneShape(VECTOR3_USE(planeNormal), planeConstant));
	VECTOR3_DEL(planeNormal);
	return ret;

}

CollisionShape^ Serialize::WorldImporter::CreateBoxShape(Vector3 halfExtents)
{
	VECTOR3_DEF(halfExtents);
	CollisionShape^ ret = CollisionShape::GetManaged(_unmanaged->baseCreateBoxShape(VECTOR3_USE(halfExtents)));
	VECTOR3_DEL(halfExtents);
	return ret;
}

CollisionShape^ Serialize::WorldImporter::CreateSphereShape(btScalar radius)
{
	return CollisionShape::GetManaged(_unmanaged->baseCreateSphereShape(radius));
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_unmanaged->baseCreateCapsuleShapeX(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_unmanaged->baseCreateCapsuleShapeY(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_unmanaged->baseCreateCapsuleShapeZ(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_unmanaged->baseCreateCylinderShapeX(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_unmanaged->baseCreateCylinderShapeY(radius, height));
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_unmanaged->baseCreateCylinderShapeZ(radius, height));
}

TriangleIndexVertexArray^ Serialize::WorldImporter::CreateTriangleMeshContainer()
{
	return gcnew TriangleIndexVertexArray(_unmanaged->baseCreateTriangleMeshContainer());
}

#ifndef DISABLE_BVH
BvhTriangleMeshShape^ Serialize::WorldImporter::CreateBvhTriangleMeshShape(StridingMeshInterface^ trimesh, OptimizedBvh^ bvh)
{
	return gcnew BvhTriangleMeshShape(_unmanaged->baseCreateBvhTriangleMeshShape(trimesh->UnmanagedPointer, bvh->UnmanagedPointer));
}
#endif

CollisionShape^ Serialize::WorldImporter::CreateConvexTriangleMeshShape(StridingMeshInterface^ trimesh)
{
	return CollisionShape::GetManaged(_unmanaged->baseCreateConvexTriangleMeshShape(trimesh->UnmanagedPointer));
}

#ifndef DISABLE_GIMPACT
GImpactMeshShape^ Serialize::WorldImporter::CreateGImpactShape(StridingMeshInterface^ trimesh)
{
	return gcnew GImpactMeshShape(_unmanaged->baseCreateGimpactShape(trimesh->UnmanagedPointer));
}
#endif

ConvexHullShape^ Serialize::WorldImporter::CreateConvexHullShape()
{
	return gcnew ConvexHullShape(_unmanaged->baseCreateConvexHullShape());
}

CompoundShape^ Serialize::WorldImporter::CreateCompoundShape()
{
	return gcnew CompoundShape(_unmanaged->baseCreateCompoundShape());
}

#ifndef DISABLE_BVH
ScaledBvhTriangleMeshShape^ Serialize::WorldImporter::CreateScaledTrangleMeshShape(BvhTriangleMeshShape^ meshShape, Vector3 localScaling)
{
	VECTOR3_DEF(localScaling);
	ScaledBvhTriangleMeshShape^ ret = gcnew ScaledBvhTriangleMeshShape(
		_unmanaged->baseCreateScaledTrangleMeshShape(meshShape->UnmanagedPointer, VECTOR3_USE(localScaling)));
	VECTOR3_DEL(localScaling);
	return ret;
}

OptimizedBvh^ Serialize::WorldImporter::CreateOptimizedBvh()
{
	return gcnew OptimizedBvh(_unmanaged->baseCreateOptimizedBvh());
}
#endif

MultiSphereShape^ Serialize::WorldImporter::CreateMultiSphereShape(array<Vector3>^ positions, array<btScalar>^ radi)
{
	int numSpheres = (positions->Length < radi->Length) ? positions->Length : radi->Length;

	btVector3* positionsTemp = Math::Vector3ArrayToUnmanaged(positions);
	btScalar* radiTemp = Math::BtScalarArrayToUnmanaged(radi, numSpheres);

	MultiSphereShape^ ret = gcnew MultiSphereShape(
		_unmanaged->baseCreateMultiSphereShape(positionsTemp, radiTemp, numSpheres));

	delete[] positionsTemp;
	delete[] radiTemp;

	return ret;
}

//TriangleInfoMap^ Serialize::WorldImporter::CreateTriangleInfoMap()
//{
//	return gcnew TriangleInfoMap(_unmanaged->baseCreateTriangleInfoMap());
//}

#ifndef DISABLE_CONSTRAINTS

Point2PointConstraint^ Serialize::WorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 pivotInA, Vector3 pivotInB)
{
	VECTOR3_DEF(pivotInA);
	VECTOR3_DEF(pivotInB);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_unmanaged->baseCreatePoint2PointConstraint(
		*(btRigidBody*)rigidBodyA->_unmanaged, *(btRigidBody*)rigidBodyB->_unmanaged, VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB)));

	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);

	return ret;
}

Point2PointConstraint^ Serialize::WorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA)
{
	VECTOR3_DEF(pivotInA);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_unmanaged->baseCreatePoint2PointConstraint(
		*(btRigidBody*)rigidBodyA->_unmanaged, VECTOR3_USE(pivotInA)));

	VECTOR3_DEL(pivotInA);
	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame, bool useReferenceFrameA)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_unmanaged->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_unmanaged, *(btRigidBody*)rigidBodyB->_unmanaged,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp, useReferenceFrameA));

	delete rigidBodyAFrameTemp;
	delete rigidBodyBFrameTemp;

	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_unmanaged->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_unmanaged, *(btRigidBody*)rigidBodyB->_unmanaged,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp));

	delete rigidBodyAFrameTemp;
	delete rigidBodyBFrameTemp;

	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame, bool useReferenceFrameA)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_unmanaged->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_unmanaged, *rigidBodyAFrameTemp, useReferenceFrameA));

	delete rigidBodyAFrameTemp;
	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_unmanaged->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_unmanaged, *rigidBodyAFrameTemp));

	delete rigidBodyAFrameTemp;
	return ret;
}

ConeTwistConstraint^ Serialize::WorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_unmanaged->baseCreateConeTwistConstraint(
		*(btRigidBody*)rigidBodyA->_unmanaged, *(btRigidBody*)rigidBodyB->_unmanaged,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp));

	delete rigidBodyAFrameTemp;
	delete rigidBodyBFrameTemp;

	return ret;
}

ConeTwistConstraint^ Serialize::WorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_unmanaged->baseCreateConeTwistConstraint(
		*(btRigidBody*)rigidBodyA->_unmanaged, *rigidBodyAFrameTemp));

	delete rigidBodyAFrameTemp;
	return ret;
}

Generic6DofConstraint^ Serialize::WorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_unmanaged->baseCreateGeneric6DofConstraint(
		*(btRigidBody*)rigidBodyA->_unmanaged, *(btRigidBody*)rigidBodyB->_unmanaged,
		*frameInATemp, *frameInBTemp, useLinearReferenceFrameA));

	delete frameInATemp;
	delete frameInBTemp;

	return ret;
}

Generic6DofConstraint^ Serialize::WorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_unmanaged->baseCreateGeneric6DofConstraint(
		*(btRigidBody*)rigidBodyB->_unmanaged, *frameInBTemp, useLinearReferenceFrameB));

	delete frameInBTemp;
	return ret;
}

SliderConstraint^ Serialize::WorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	SliderConstraint^ ret = gcnew SliderConstraint(_unmanaged->baseCreateSliderConstraint(
		*(btRigidBody*)rigidBodyA->_unmanaged, *(btRigidBody*)rigidBodyB->_unmanaged,
		*frameInATemp, *frameInBTemp, useLinearReferenceFrameA));

	delete frameInATemp;
	delete frameInBTemp;

	return ret;
}

SliderConstraint^ Serialize::WorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	SliderConstraint^ ret = gcnew SliderConstraint(_unmanaged->baseCreateSliderConstraint(
		*(btRigidBody*)rigidBodyB->_unmanaged, *frameInBTemp, useLinearReferenceFrameA));
	
	delete frameInBTemp;
	return ret;
}

#endif


void Serialize::WorldImporter::DeleteAllData()
{
	_unmanaged->deleteAllData();
}

CollisionShape^ Serialize::WorldImporter::GetCollisionShapeByIndex(int index)
{
	return CollisionShape::GetManaged(_unmanaged->getCollisionShapeByIndex(index));
}

CollisionObject^ Serialize::WorldImporter::GetRigidBodyByIndex(int index)
{
	return CollisionObject::GetManaged(_unmanaged->getRigidBodyByIndex(index));
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ Serialize::WorldImporter::GetConstraintByIndex(int index)
{
	btTypedConstraint* constraint = _unmanaged->getConstraintByIndex(index);
	return TypedConstraint::Upcast(constraint);
}
#endif

#ifndef DISABLE_BVH
OptimizedBvh^ Serialize::WorldImporter::GetBvhByIndex(int index)
{
	btOptimizedBvh* bvh = _unmanaged->getBvhByIndex(index);
	return bvh ? gcnew OptimizedBvh(bvh) : nullptr;
}
#endif

//TriangleInfoMap^ Serialize::WorldImporter::GetTriangleInfoMapByIndex(int index)
//{
//	return gcnew TriangleInfoMap(_unmanaged->getTriangleInfoMapByIndex(index));
//}

CollisionShape^ Serialize::WorldImporter::GetCollisionShapeByName(String^ name)
{
	btCollisionShape* shape;
	CollisionShape^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	shape = _unmanaged->getCollisionShapeByName(nameTemp);
	ret = CollisionShape::GetManaged(shape);

	StringConv::FreeUnmanagedString(nameTemp);
	return ret;
}

RigidBody^ Serialize::WorldImporter::GetRigidBodyByName(String^ name)
{
	btRigidBody* body;
	RigidBody^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	body = _unmanaged->getRigidBodyByName(nameTemp);
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

	constraint = _unmanaged->getConstraintByName(nameTemp);
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
		pointer = shape->_unmanaged;
		goto returnName;
	}

	CollisionObject^ body = static_cast<CollisionObject^>(obj);
	if (body != nullptr)
	{
		pointer = body->_unmanaged;
		goto returnName;
	}

#ifndef DISABLE_CONSTRAINTS
	TypedConstraint^ constraint = static_cast<TypedConstraint^>(obj);
	if (constraint != nullptr)
	{
		pointer = constraint->UnmanagedPointer;
		goto returnName;
	}
#endif

	return nullptr;

returnName:
	const char* name = _unmanaged->getNameForPointer(pointer);
	return name ? StringConv::UnmanagedToManaged(name) : nullptr;
}

bool Serialize::WorldImporter::IsDisposed::get()
{
	return (_unmanaged == NULL);
}

int Serialize::WorldImporter::BvhCount::get()
{
	return _unmanaged->getNumBvhs();
}

int Serialize::WorldImporter::ConstraintCount::get()
{
	return _unmanaged->getNumConstraints();
}

int Serialize::WorldImporter::CollisionShapeCount::get()
{
	return _unmanaged->getNumCollisionShapes();
}

int Serialize::WorldImporter::RigidBodyCount::get()
{
	return _unmanaged->getNumRigidBodies();
}

int Serialize::WorldImporter::TriangleInfoMapCount::get()
{
	return _unmanaged->getNumTriangleInfoMaps();
}

bool Serialize::WorldImporter::VerboseMode::get()
{
	return _unmanaged->getVerboseMode();
}
void Serialize::WorldImporter::VerboseMode::set(bool value)
{
	_unmanaged->setVerboseMode(value);
}


Serialize::WorldImporterWrapper::WorldImporterWrapper(btDynamicsWorld* world, WorldImporter^ importer)
: btWorldImporter(world)
{
	_unmanaged = importer;
}

btCollisionObject* Serialize::WorldImporterWrapper::createCollisionObject(const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return _unmanaged->CreateCollisionObject(Math::BtTransformToMatrix(&startTransform),
		CollisionShape::GetManaged(shape), StringConv::UnmanagedToManaged(bodyName))->UnmanagedPointer;
}

btRigidBody* Serialize::WorldImporterWrapper::createRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return (btRigidBody*)_unmanaged->CreateRigidBody(isDynamic, mass, Math::BtTransformToMatrix(&startTransform),
		CollisionShape::GetManaged(shape), StringConv::UnmanagedToManaged(bodyName))->_unmanaged;
}

btCollisionShape* Serialize::WorldImporterWrapper::createPlaneShape(const btVector3& planeNormal, btScalar planeConstant)
{
	return _unmanaged->CreatePlaneShape(Math::BtVector3ToVector3(&planeNormal), planeConstant)->UnmanagedPointer;
}

btCollisionShape* Serialize::WorldImporterWrapper::createBoxShape(const btVector3& halfExtents)
{
	return _unmanaged->CreateBoxShape(Math::BtVector3ToVector3(&halfExtents))->UnmanagedPointer;
}

btCollisionShape* Serialize::WorldImporterWrapper::createSphereShape(btScalar radius)
{
	return _unmanaged->CreateSphereShape(radius)->UnmanagedPointer;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeX(btScalar radius, btScalar height)
{
	return _unmanaged->CreateCapsuleShapeX(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeY(btScalar radius, btScalar height)
{
	return _unmanaged->CreateCapsuleShapeY(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeZ(btScalar radius, btScalar height)
{
	return _unmanaged->CreateCapsuleShapeZ(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeX(btScalar radius, btScalar height)
{
	return _unmanaged->CreateCylinderShapeX(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeY(btScalar radius, btScalar height)
{
	return _unmanaged->CreateCylinderShapeY(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeZ(btScalar radius, btScalar height)
{
	return _unmanaged->CreateCylinderShapeZ(radius, height)->UnmanagedPointer;
}

class btTriangleIndexVertexArray* Serialize::WorldImporterWrapper::createTriangleMeshContainer()
{
	return _unmanaged->CreateTriangleMeshContainer()->UnmanagedPointer;
}

#ifndef DISABLE_BVH
btBvhTriangleMeshShape* Serialize::WorldImporterWrapper::createBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	return _unmanaged->CreateBvhTriangleMeshShape(gcnew StridingMeshInterface(trimesh), gcnew OptimizedBvh(bvh))->UnmanagedPointer;
}
#endif

btCollisionShape* Serialize::WorldImporterWrapper::createConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	return _unmanaged->CreateConvexTriangleMeshShape(gcnew StridingMeshInterface(trimesh))->UnmanagedPointer;
}

#ifndef DISABLE_GIMPACT
btGImpactMeshShape* Serialize::WorldImporterWrapper::createGimpactShape(btStridingMeshInterface* trimesh)
{
	return (btGImpactMeshShape*)_unmanaged->CreateGImpactShape(gcnew StridingMeshInterface(trimesh))->_unmanaged;
}
#endif

class btConvexHullShape* Serialize::WorldImporterWrapper::createConvexHullShape()
{
	return (btConvexHullShape*)_unmanaged->CreateConvexHullShape()->_unmanaged;
}

class btCompoundShape* Serialize::WorldImporterWrapper::createCompoundShape()
{
	return (btCompoundShape*)_unmanaged->CreateCompoundShape()->_unmanaged;
}

#ifndef DISABLE_BVH
btOptimizedBvh* Serialize::WorldImporterWrapper::createOptimizedBvh()
{
	return _unmanaged->CreateOptimizedBvh()->UnmanagedPointer;
}
#endif

btTriangleInfoMap* Serialize::WorldImporterWrapper::createTriangleInfoMap()
{
	return baseCreateTriangleInfoMap();
	//return _unmanaged->CreateTriangleInfoMap()->UnmanagedPointer;
}

#ifndef DISABLE_CONSTRAINTS

btPoint2PointConstraint* Serialize::WorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btVector3& pivotInA, const btVector3& pivotInB)
{
	return _unmanaged->CreatePoint2PointConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtVector3ToVector3(&pivotInA), Math::BtVector3ToVector3(&pivotInB))->UnmanagedPointer;
}

btPoint2PointConstraint* Serialize::WorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, const btVector3& pivotInA)
{
	return _unmanaged->CreatePoint2PointConstraint((RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtVector3ToVector3(&pivotInA))->UnmanagedPointer;
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame, bool useReferenceFrameA)
{
	return _unmanaged->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame), useReferenceFrameA)->UnmanagedPointer;
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return _unmanaged->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame))->UnmanagedPointer;
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame, bool useReferenceFrameA)
{
	return _unmanaged->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame), useReferenceFrameA)->UnmanagedPointer;
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return _unmanaged->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame))->UnmanagedPointer;
}

btConeTwistConstraint* Serialize::WorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return _unmanaged->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame))->UnmanagedPointer;
}

btConeTwistConstraint* Serialize::WorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return _unmanaged->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame))->UnmanagedPointer;
}

btGeneric6DofConstraint* Serialize::WorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _unmanaged->CreateGeneric6DofConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
}

btGeneric6DofConstraint* Serialize::WorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameB)
{
	return _unmanaged->CreateGeneric6DofConstraint((RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameB)->UnmanagedPointer;
}

btSliderConstraint* Serialize::WorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _unmanaged->CreateSliderConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
}

btSliderConstraint* Serialize::WorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _unmanaged->CreateSliderConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyB), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
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

#endif

#endif
#endif