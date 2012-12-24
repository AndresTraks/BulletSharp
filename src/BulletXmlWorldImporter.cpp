#include "StdAfx.h"

#ifndef DISABLE_SERIALIZE

#include "BulletXmlWorldImporter.h"
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

Serialize::BulletXmlWorldImporter::BulletXmlWorldImporter(DynamicsWorld^ world)
{
	_importer = new BulletXmlWorldImporterWrapper((btDynamicsWorld*)GetUnmanagedNullable(world), this);
}

Serialize::BulletXmlWorldImporter::BulletXmlWorldImporter()
{
	_importer = new BulletXmlWorldImporterWrapper(0, this);
}

Serialize::BulletXmlWorldImporter::~BulletXmlWorldImporter()
{
	this->!BulletXmlWorldImporter();
}

Serialize::BulletXmlWorldImporter::!BulletXmlWorldImporter()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	delete _importer;
	_importer = NULL;

	OnDisposed(this, nullptr);
}

CollisionObject^ Serialize::BulletXmlWorldImporter::CreateCollisionObject(Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	CollisionObject^ ret = CollisionObject::GetManaged(
		_importer->baseCreateCollisionObject(*startTransformTemp, shape->UnmanagedPointer, bodyNameTemp));

	ALIGNED_FREE(startTransformTemp);
	StringConv::FreeUnmanagedString(bodyNameTemp);

	return ret;
}

RigidBody^ Serialize::BulletXmlWorldImporter::CreateRigidBody(bool isDynamic, btScalar mass, Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	RigidBody^ ret = (RigidBody^)CollisionObject::GetManaged(
		_importer->baseCreateRigidBody(isDynamic, mass, *startTransformTemp, shape->UnmanagedPointer, bodyNameTemp));

	ALIGNED_FREE(startTransformTemp);
	StringConv::FreeUnmanagedString(bodyNameTemp);

	return ret;
}

CollisionShape^ Serialize::BulletXmlWorldImporter::CreatePlaneShape(Vector3 planeNormal, btScalar planeConstant)
{
	VECTOR3_DEF(planeNormal);
	CollisionShape^ ret = CollisionShape::GetManaged(_importer->baseCreatePlaneShape(VECTOR3_USE(planeNormal), planeConstant));
	VECTOR3_DEL(planeNormal);
	return ret;

}

CollisionShape^ Serialize::BulletXmlWorldImporter::CreateBoxShape(Vector3 halfExtents)
{
	VECTOR3_DEF(halfExtents);
	CollisionShape^ ret = CollisionShape::GetManaged(_importer->baseCreateBoxShape(VECTOR3_USE(halfExtents)));
	VECTOR3_DEL(halfExtents);
	return ret;
}

CollisionShape^ Serialize::BulletXmlWorldImporter::CreateSphereShape(btScalar radius)
{
	return CollisionShape::GetManaged(_importer->baseCreateSphereShape(radius));
}

CollisionShape^ Serialize::BulletXmlWorldImporter::CreateCapsuleShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCapsuleShapeX(radius, height));
}

CollisionShape^ Serialize::BulletXmlWorldImporter::CreateCapsuleShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCapsuleShapeY(radius, height));
}

CollisionShape^ Serialize::BulletXmlWorldImporter::CreateCapsuleShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCapsuleShapeZ(radius, height));
}

CollisionShape^ Serialize::BulletXmlWorldImporter::CreateCylinderShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCylinderShapeX(radius, height));
}

CollisionShape^ Serialize::BulletXmlWorldImporter::CreateCylinderShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCylinderShapeY(radius, height));
}

CollisionShape^ Serialize::BulletXmlWorldImporter::CreateCylinderShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCylinderShapeZ(radius, height));
}

TriangleIndexVertexArray^ Serialize::BulletXmlWorldImporter::CreateTriangleMeshContainer()
{
	return gcnew TriangleIndexVertexArray(_importer->baseCreateTriangleMeshContainer());
}

#ifndef DISABLE_BVH
BvhTriangleMeshShape^ Serialize::BulletXmlWorldImporter::CreateBvhTriangleMeshShape(StridingMeshInterface^ trimesh, OptimizedBvh^ bvh)
{
	return gcnew BvhTriangleMeshShape(_importer->baseCreateBvhTriangleMeshShape(trimesh->UnmanagedPointer, bvh->UnmanagedPointer));
}
#endif

CollisionShape^ Serialize::BulletXmlWorldImporter::CreateConvexTriangleMeshShape(StridingMeshInterface^ trimesh)
{
	return CollisionShape::GetManaged(_importer->baseCreateConvexTriangleMeshShape(trimesh->UnmanagedPointer));
}

#ifndef DISABLE_GIMPACT
GImpactMeshShape^ Serialize::BulletXmlWorldImporter::CreateGImpactShape(StridingMeshInterface^ trimesh)
{
	return gcnew GImpactMeshShape(_importer->baseCreateGimpactShape(trimesh->UnmanagedPointer));
}
#endif

ConvexHullShape^ Serialize::BulletXmlWorldImporter::CreateConvexHullShape()
{
	return gcnew ConvexHullShape(_importer->baseCreateConvexHullShape());
}

CompoundShape^ Serialize::BulletXmlWorldImporter::CreateCompoundShape()
{
	return gcnew CompoundShape(_importer->baseCreateCompoundShape());
}

#ifndef DISABLE_BVH
ScaledBvhTriangleMeshShape^ Serialize::BulletXmlWorldImporter::CreateScaledTrangleMeshShape(BvhTriangleMeshShape^ meshShape, Vector3 localScaling)
{
	VECTOR3_DEF(localScaling);
	ScaledBvhTriangleMeshShape^ ret = gcnew ScaledBvhTriangleMeshShape(
		_importer->baseCreateScaledTrangleMeshShape(meshShape->UnmanagedPointer, VECTOR3_USE(localScaling)));
	VECTOR3_DEL(localScaling);
	return ret;
}

OptimizedBvh^ Serialize::BulletXmlWorldImporter::CreateOptimizedBvh()
{
	return gcnew OptimizedBvh(_importer->baseCreateOptimizedBvh());
}
#endif

MultiSphereShape^ Serialize::BulletXmlWorldImporter::CreateMultiSphereShape(array<Vector3>^ positions, array<btScalar>^ radi)
{
	int numSpheres = (positions->Length < radi->Length) ? positions->Length : radi->Length;

	btVector3* positionsTemp = Math::Vector3ArrayToUnmanaged(positions);
	btScalar* radiTemp = Math::BtScalarArrayToUnmanaged(radi, numSpheres);

	MultiSphereShape^ ret = gcnew MultiSphereShape(
		_importer->baseCreateMultiSphereShape(positionsTemp, radiTemp, numSpheres));

	delete[] positionsTemp;
	delete[] radiTemp;

	return ret;
}

//TriangleInfoMap^ Serialize::BulletXmlWorldImporter::CreateTriangleInfoMap()
//{
//	return gcnew TriangleInfoMap(_importer->baseCreateTriangleInfoMap());
//}

#ifndef DISABLE_CONSTRAINTS

Point2PointConstraint^ Serialize::BulletXmlWorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 pivotInA, Vector3 pivotInB)
{
	VECTOR3_DEF(pivotInA);
	VECTOR3_DEF(pivotInB);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_importer->baseCreatePoint2PointConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native, VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB)));

	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);

	return ret;
}

Point2PointConstraint^ Serialize::BulletXmlWorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA)
{
	VECTOR3_DEF(pivotInA);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_importer->baseCreatePoint2PointConstraint(
		*(btRigidBody*)rigidBodyA->_native, VECTOR3_USE(pivotInA)));

	VECTOR3_DEL(pivotInA);
	return ret;
}

HingeConstraint^ Serialize::BulletXmlWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame, bool useReferenceFrameA)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp, useReferenceFrameA));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	ALIGNED_FREE(rigidBodyBFrameTemp);

	return ret;
}

HingeConstraint^ Serialize::BulletXmlWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	ALIGNED_FREE(rigidBodyBFrameTemp);

	return ret;
}

HingeConstraint^ Serialize::BulletXmlWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame, bool useReferenceFrameA)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp, useReferenceFrameA));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	return ret;
}

HingeConstraint^ Serialize::BulletXmlWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	return ret;
}

ConeTwistConstraint^ Serialize::BulletXmlWorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_importer->baseCreateConeTwistConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*rigidBodyAFrameTemp, *rigidBodyBFrameTemp));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	ALIGNED_FREE(rigidBodyBFrameTemp);

	return ret;
}

ConeTwistConstraint^ Serialize::BulletXmlWorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_importer->baseCreateConeTwistConstraint(
		*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	return ret;
}

Generic6DofConstraint^ Serialize::BulletXmlWorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_importer->baseCreateGeneric6DofConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*frameInATemp, *frameInBTemp, useLinearReferenceFrameA));

	ALIGNED_FREE(frameInATemp);
	ALIGNED_FREE(frameInBTemp);

	return ret;
}

Generic6DofConstraint^ Serialize::BulletXmlWorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_importer->baseCreateGeneric6DofConstraint(
		*(btRigidBody*)rigidBodyB->_native, *frameInBTemp, useLinearReferenceFrameB));

	ALIGNED_FREE(frameInBTemp);
	return ret;
}

SliderConstraint^ Serialize::BulletXmlWorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	SliderConstraint^ ret = gcnew SliderConstraint(_importer->baseCreateSliderConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		*frameInATemp, *frameInBTemp, useLinearReferenceFrameA));

	ALIGNED_FREE(frameInATemp);
	ALIGNED_FREE(frameInBTemp);

	return ret;
}

SliderConstraint^ Serialize::BulletXmlWorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	SliderConstraint^ ret = gcnew SliderConstraint(_importer->baseCreateSliderConstraint(
		*(btRigidBody*)rigidBodyB->_native, *frameInBTemp, useLinearReferenceFrameA));
	
	ALIGNED_FREE(frameInBTemp);
	return ret;
}

#endif


void Serialize::BulletXmlWorldImporter::DeleteAllData()
{
	_importer->deleteAllData();
}

bool Serialize::BulletXmlWorldImporter::LoadFile(String^ filename)
{
	const char* filenameTemp = StringConv::ManagedToUnmanaged(filename);
	bool ret = _importer->loadFile(filenameTemp);
	StringConv::FreeUnmanagedString(filenameTemp);
	return ret;
}

CollisionShape^ Serialize::BulletXmlWorldImporter::GetCollisionShapeByIndex(int index)
{
	return CollisionShape::GetManaged(_importer->getCollisionShapeByIndex(index));
}

CollisionObject^ Serialize::BulletXmlWorldImporter::GetRigidBodyByIndex(int index)
{
	return CollisionObject::GetManaged(_importer->getRigidBodyByIndex(index));
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ Serialize::BulletXmlWorldImporter::GetConstraintByIndex(int index)
{
	btTypedConstraint* constraint = _importer->getConstraintByIndex(index);
	return TypedConstraint::Upcast(constraint);
}
#endif

#ifndef DISABLE_BVH
OptimizedBvh^ Serialize::BulletXmlWorldImporter::GetBvhByIndex(int index)
{
	btOptimizedBvh* bvh = _importer->getBvhByIndex(index);
	return bvh ? gcnew OptimizedBvh(bvh) : nullptr;
}
#endif

//TriangleInfoMap^ Serialize::BulletXmlWorldImporter::GetTriangleInfoMapByIndex(int index)
//{
//	return gcnew TriangleInfoMap(_importer->getTriangleInfoMapByIndex(index));
//}

CollisionShape^ Serialize::BulletXmlWorldImporter::GetCollisionShapeByName(String^ name)
{
	btCollisionShape* shape;
	CollisionShape^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	shape = _importer->getCollisionShapeByName(nameTemp);
	ret = CollisionShape::GetManaged(shape);

	StringConv::FreeUnmanagedString(nameTemp);
	return ret;
}

RigidBody^ Serialize::BulletXmlWorldImporter::GetRigidBodyByName(String^ name)
{
	btRigidBody* body;
	RigidBody^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	body = _importer->getRigidBodyByName(nameTemp);
	ret = (RigidBody^)CollisionObject::GetManaged(body);

	StringConv::FreeUnmanagedString(nameTemp);
	return ret;
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ Serialize::BulletXmlWorldImporter::GetConstraintByName(String^ name)
{
	btTypedConstraint* constraint;
	TypedConstraint^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	constraint = _importer->getConstraintByName(nameTemp);
	ret = TypedConstraint::Upcast(constraint);

	StringConv::FreeUnmanagedString(nameTemp);
	return ret;
}
#endif

String^	Serialize::BulletXmlWorldImporter::GetNameForObject(Object^ obj)
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
		pointer = constraint->UnmanagedPointer;
		goto returnName;
	}
#endif

	return nullptr;

returnName:
	const char* name = _importer->getNameForPointer(pointer);
	return name ? StringConv::UnmanagedToManaged(name) : nullptr;
}

bool Serialize::BulletXmlWorldImporter::IsDisposed::get()
{
	return (_importer == NULL);
}

int Serialize::BulletXmlWorldImporter::BvhCount::get()
{
	return _importer->getNumBvhs();
}

int Serialize::BulletXmlWorldImporter::ConstraintCount::get()
{
	return _importer->getNumConstraints();
}

int Serialize::BulletXmlWorldImporter::CollisionShapeCount::get()
{
	return _importer->getNumCollisionShapes();
}

int Serialize::BulletXmlWorldImporter::RigidBodyCount::get()
{
	return _importer->getNumRigidBodies();
}

int Serialize::BulletXmlWorldImporter::TriangleInfoMapCount::get()
{
	return _importer->getNumTriangleInfoMaps();
}

bool Serialize::BulletXmlWorldImporter::VerboseMode::get()
{
	return _importer->getVerboseMode();
}
void Serialize::BulletXmlWorldImporter::VerboseMode::set(bool value)
{
	_importer->setVerboseMode(value);
}


Serialize::BulletXmlWorldImporterWrapper::BulletXmlWorldImporterWrapper(btDynamicsWorld* world, BulletXmlWorldImporter^ importer)
: btBulletXmlWorldImporter(world)
{
	_importer = importer;
}

btCollisionObject* Serialize::BulletXmlWorldImporterWrapper::createCollisionObject(const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return _importer->CreateCollisionObject(Math::BtTransformToMatrix(&startTransform),
		CollisionShape::GetManaged(shape), StringConv::UnmanagedToManaged(bodyName))->UnmanagedPointer;
}

btRigidBody* Serialize::BulletXmlWorldImporterWrapper::createRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return (btRigidBody*)_importer->CreateRigidBody(isDynamic, mass, Math::BtTransformToMatrix(&startTransform),
		CollisionShape::GetManaged(shape), StringConv::UnmanagedToManaged(bodyName))->_native;
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::createPlaneShape(const btVector3& planeNormal, btScalar planeConstant)
{
	return _importer->CreatePlaneShape(Math::BtVector3ToVector3(&planeNormal), planeConstant)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::createBoxShape(const btVector3& halfExtents)
{
	return _importer->CreateBoxShape(Math::BtVector3ToVector3(&halfExtents))->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::createSphereShape(btScalar radius)
{
	return _importer->CreateSphereShape(radius)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::createCapsuleShapeX(btScalar radius, btScalar height)
{
	return _importer->CreateCapsuleShapeX(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::createCapsuleShapeY(btScalar radius, btScalar height)
{
	return _importer->CreateCapsuleShapeY(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::createCapsuleShapeZ(btScalar radius, btScalar height)
{
	return _importer->CreateCapsuleShapeZ(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::createCylinderShapeX(btScalar radius, btScalar height)
{
	return _importer->CreateCylinderShapeX(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::createCylinderShapeY(btScalar radius, btScalar height)
{
	return _importer->CreateCylinderShapeY(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::createCylinderShapeZ(btScalar radius, btScalar height)
{
	return _importer->CreateCylinderShapeZ(radius, height)->UnmanagedPointer;
}

class btTriangleIndexVertexArray* Serialize::BulletXmlWorldImporterWrapper::createTriangleMeshContainer()
{
	return _importer->CreateTriangleMeshContainer()->UnmanagedPointer;
}

#ifndef DISABLE_BVH
btBvhTriangleMeshShape* Serialize::BulletXmlWorldImporterWrapper::createBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	return _importer->CreateBvhTriangleMeshShape(gcnew StridingMeshInterface(trimesh), gcnew OptimizedBvh(bvh))->UnmanagedPointer;
}
#endif

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::createConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	return _importer->CreateConvexTriangleMeshShape(gcnew StridingMeshInterface(trimesh))->UnmanagedPointer;
}

#ifndef DISABLE_GIMPACT
btGImpactMeshShape* Serialize::BulletXmlWorldImporterWrapper::createGimpactShape(btStridingMeshInterface* trimesh)
{
	return (btGImpactMeshShape*)_importer->CreateGImpactShape(gcnew StridingMeshInterface(trimesh))->_native;
}
#endif

class btConvexHullShape* Serialize::BulletXmlWorldImporterWrapper::createConvexHullShape()
{
	return (btConvexHullShape*)_importer->CreateConvexHullShape()->_native;
}

class btCompoundShape* Serialize::BulletXmlWorldImporterWrapper::createCompoundShape()
{
	return (btCompoundShape*)_importer->CreateCompoundShape()->_native;
}

#ifndef DISABLE_BVH
btOptimizedBvh* Serialize::BulletXmlWorldImporterWrapper::createOptimizedBvh()
{
	return _importer->CreateOptimizedBvh()->UnmanagedPointer;
}
#endif

btTriangleInfoMap* Serialize::BulletXmlWorldImporterWrapper::createTriangleInfoMap()
{
	return baseCreateTriangleInfoMap();
	//return _importer->CreateTriangleInfoMap()->UnmanagedPointer;
}

#ifndef DISABLE_CONSTRAINTS

btPoint2PointConstraint* Serialize::BulletXmlWorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btVector3& pivotInA, const btVector3& pivotInB)
{
	return _importer->CreatePoint2PointConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtVector3ToVector3(&pivotInA), Math::BtVector3ToVector3(&pivotInB))->UnmanagedPointer;
}

btPoint2PointConstraint* Serialize::BulletXmlWorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, const btVector3& pivotInA)
{
	return _importer->CreatePoint2PointConstraint((RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtVector3ToVector3(&pivotInA))->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletXmlWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame, bool useReferenceFrameA)
{
	return _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame), useReferenceFrameA)->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletXmlWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame))->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletXmlWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame, bool useReferenceFrameA)
{
	return _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame), useReferenceFrameA)->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletXmlWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame))->UnmanagedPointer;
}

btConeTwistConstraint* Serialize::BulletXmlWorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return _importer->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame))->UnmanagedPointer;
}

btConeTwistConstraint* Serialize::BulletXmlWorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return _importer->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame))->UnmanagedPointer;
}

btGeneric6DofConstraint* Serialize::BulletXmlWorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _importer->CreateGeneric6DofConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
}

btGeneric6DofConstraint* Serialize::BulletXmlWorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameB)
{
	return _importer->CreateGeneric6DofConstraint((RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameB)->UnmanagedPointer;
}

btSliderConstraint* Serialize::BulletXmlWorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _importer->CreateSliderConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
}

btSliderConstraint* Serialize::BulletXmlWorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _importer->CreateSliderConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyB), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
}

#endif


btCollisionObject* Serialize::BulletXmlWorldImporterWrapper::baseCreateCollisionObject(const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return btBulletXmlWorldImporter::createCollisionObject(startTransform, shape, bodyName);
}

btRigidBody* Serialize::BulletXmlWorldImporterWrapper::baseCreateRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return btBulletXmlWorldImporter::createRigidBody(isDynamic, mass, startTransform, shape, bodyName);
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::baseCreatePlaneShape(const btVector3& planeNormal, btScalar planeConstant)
{
	return btBulletXmlWorldImporter::createPlaneShape(planeNormal, planeConstant);
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateBoxShape(const btVector3& halfExtents)
{
	return btBulletXmlWorldImporter::createBoxShape(halfExtents);
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateSphereShape(btScalar radius)
{
	return btBulletXmlWorldImporter::createSphereShape(radius);
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateCapsuleShapeX(btScalar radius, btScalar height)
{
	return btBulletXmlWorldImporter::createCapsuleShapeX(radius, height);
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateCapsuleShapeY(btScalar radius, btScalar height)
{
	return btBulletXmlWorldImporter::createCapsuleShapeY(radius, height);
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateCapsuleShapeZ(btScalar radius, btScalar height)
{
	return btBulletXmlWorldImporter::createCapsuleShapeZ(radius, height);
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateCylinderShapeX(btScalar radius, btScalar height)
{
	return btBulletXmlWorldImporter::createCylinderShapeX(radius, height);
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateCylinderShapeY(btScalar radius, btScalar height)
{
	return btBulletXmlWorldImporter::createCylinderShapeY(radius, height);
}

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateCylinderShapeZ(btScalar radius, btScalar height)
{
	return btBulletXmlWorldImporter::createCylinderShapeZ(radius, height);
}

class btTriangleIndexVertexArray* Serialize::BulletXmlWorldImporterWrapper::baseCreateTriangleMeshContainer()
{
	return btBulletXmlWorldImporter::createTriangleMeshContainer();
}

#ifndef DISABLE_BVH
btBvhTriangleMeshShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	return btBulletXmlWorldImporter::createBvhTriangleMeshShape(trimesh, bvh);
}
#endif

btCollisionShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	return btBulletXmlWorldImporter::createConvexTriangleMeshShape(trimesh);
}

#ifndef DISABLE_GIMPACT
btGImpactMeshShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateGimpactShape(btStridingMeshInterface* trimesh)
{
	return btBulletXmlWorldImporter::createGimpactShape(trimesh);
}
#endif

class btConvexHullShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateConvexHullShape()
{
	return btBulletXmlWorldImporter::createConvexHullShape();
}

class btCompoundShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateCompoundShape()
{
	return btBulletXmlWorldImporter::createCompoundShape();
}

#ifndef DISABLE_BVH
btOptimizedBvh* Serialize::BulletXmlWorldImporterWrapper::baseCreateOptimizedBvh()
{
	return btBulletXmlWorldImporter::createOptimizedBvh();
}

btScaledBvhTriangleMeshShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateScaledTrangleMeshShape(btBvhTriangleMeshShape* meshShape,const btVector3& localScalingbtBvhTriangleMeshShape)
{
	return btBulletXmlWorldImporter::createScaledTrangleMeshShape(meshShape, localScalingbtBvhTriangleMeshShape);
}
#endif

btMultiSphereShape* Serialize::BulletXmlWorldImporterWrapper::baseCreateMultiSphereShape(const btVector3* positions, const btScalar* radi, int numSpheres)
{
	return btBulletXmlWorldImporter::createMultiSphereShape(positions, radi, numSpheres);
}

btTriangleInfoMap* Serialize::BulletXmlWorldImporterWrapper::baseCreateTriangleInfoMap()
{
	return btBulletXmlWorldImporter::createTriangleInfoMap();
}

#ifndef DISABLE_CONSTRAINTS

btPoint2PointConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreatePoint2PointConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btVector3& pivotInA, const btVector3& pivotInB)
{
	return btBulletXmlWorldImporter::createPoint2PointConstraint(rigidBodyA, rigidBodyB, pivotInA, pivotInB);
}

btPoint2PointConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreatePoint2PointConstraint(btRigidBody& rigidBodyA, const btVector3& pivotInA)
{
	return btBulletXmlWorldImporter::createPoint2PointConstraint(rigidBodyA, pivotInA);
}

btHingeConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame, bool useReferenceFrameA)
{
	return btBulletXmlWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame, useReferenceFrameA);
}

btHingeConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return btBulletXmlWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame);
}

btHingeConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame, bool useReferenceFrameA)
{
	return btBulletXmlWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyAFrame, useReferenceFrameA);
}

btHingeConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return btBulletXmlWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyAFrame);
}

btConeTwistConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreateConeTwistConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return btBulletXmlWorldImporter::createConeTwistConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame);
}

btConeTwistConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreateConeTwistConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return btBulletXmlWorldImporter::createConeTwistConstraint(rigidBodyA, rigidBodyAFrame);
}

btGeneric6DofConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreateGeneric6DofConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btBulletXmlWorldImporter::createGeneric6DofConstraint(rigidBodyA, rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
}

btGeneric6DofConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreateGeneric6DofConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameB)
{
	return btBulletXmlWorldImporter::createGeneric6DofConstraint(rigidBodyB, frameInB, useLinearReferenceFrameB);
}

btSliderConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreateSliderConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btBulletXmlWorldImporter::createSliderConstraint(rigidBodyA, rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
}

btSliderConstraint* Serialize::BulletXmlWorldImporterWrapper::baseCreateSliderConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btBulletXmlWorldImporter::createSliderConstraint(rigidBodyB, frameInB, useLinearReferenceFrameA);
}

#endif

#endif
