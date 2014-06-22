#include "StdAfx.h"

#ifndef DISABLE_SERIALIZE

#include "BulletWorldImporter.h"
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

Serialize::BulletWorldImporter::BulletWorldImporter(DynamicsWorld^ world)
{
	_importer = new BulletWorldImporterWrapper((btDynamicsWorld*)GetUnmanagedNullable(world), this);
}

Serialize::BulletWorldImporter::BulletWorldImporter()
{
	_importer = new BulletWorldImporterWrapper(0, this);
}

Serialize::BulletWorldImporter::~BulletWorldImporter()
{
	this->!BulletWorldImporter();
}

Serialize::BulletWorldImporter::!BulletWorldImporter()
{
	if (this->IsDisposed)
		return;

	delete _importer;
	_importer = NULL;
}

CollisionObject^ Serialize::BulletWorldImporter::CreateCollisionObject(Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	CollisionObject^ ret = CollisionObject::GetManaged(
		_importer->baseCreateCollisionObject(*startTransformTemp, shape->_native, bodyNameTemp));

	ALIGNED_FREE(startTransformTemp);
	StringConv::FreeUnmanagedString(bodyNameTemp);

	return ret;
}

RigidBody^ Serialize::BulletWorldImporter::CreateRigidBody(bool isDynamic, btScalar mass, Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	RigidBody^ ret = (RigidBody^)CollisionObject::GetManaged(
		_importer->baseCreateRigidBody(isDynamic, mass, *startTransformTemp, shape->_native, bodyNameTemp));

	ALIGNED_FREE(startTransformTemp);
	StringConv::FreeUnmanagedString(bodyNameTemp);

	return ret;
}

CollisionShape^ Serialize::BulletWorldImporter::CreatePlaneShape(Vector3 planeNormal, btScalar planeConstant)
{
	VECTOR3_DEF(planeNormal);
	CollisionShape^ ret = CollisionShape::GetManaged(_importer->baseCreatePlaneShape(VECTOR3_USE(planeNormal), planeConstant));
	VECTOR3_DEL(planeNormal);
	return ret;

}

CollisionShape^ Serialize::BulletWorldImporter::CreateBoxShape(Vector3 halfExtents)
{
	VECTOR3_DEF(halfExtents);
	CollisionShape^ ret = CollisionShape::GetManaged(_importer->baseCreateBoxShape(VECTOR3_USE(halfExtents)));
	VECTOR3_DEL(halfExtents);
	return ret;
}

CollisionShape^ Serialize::BulletWorldImporter::CreateSphereShape(btScalar radius)
{
	return CollisionShape::GetManaged(_importer->baseCreateSphereShape(radius));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCapsuleShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCapsuleShapeX(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCapsuleShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCapsuleShapeY(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCapsuleShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCapsuleShapeZ(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCylinderShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCylinderShapeX(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCylinderShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCylinderShapeY(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCylinderShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateCylinderShapeZ(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateConeShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateConeShapeX(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateConeShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateConeShapeY(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateConeShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::GetManaged(_importer->baseCreateConeShapeZ(radius, height));
}

TriangleIndexVertexArray^ Serialize::BulletWorldImporter::CreateTriangleMeshContainer()
{
	return gcnew TriangleIndexVertexArray(_importer->baseCreateTriangleMeshContainer());
}

#ifndef DISABLE_BVH
BvhTriangleMeshShape^ Serialize::BulletWorldImporter::CreateBvhTriangleMeshShape(StridingMeshInterface^ trimesh, OptimizedBvh^ bvh)
{
	return gcnew BvhTriangleMeshShape(_importer->baseCreateBvhTriangleMeshShape(trimesh->_native, (btOptimizedBvh*)bvh->_native));
}
#endif

CollisionShape^ Serialize::BulletWorldImporter::CreateConvexTriangleMeshShape(StridingMeshInterface^ trimesh)
{
	return CollisionShape::GetManaged(_importer->baseCreateConvexTriangleMeshShape(trimesh->_native));
}

#ifndef DISABLE_GIMPACT
GImpactMeshShape^ Serialize::BulletWorldImporter::CreateGImpactShape(StridingMeshInterface^ trimesh)
{
	return gcnew GImpactMeshShape(_importer->baseCreateGimpactShape(trimesh->_native));
}
#endif

ConvexHullShape^ Serialize::BulletWorldImporter::CreateConvexHullShape()
{
	return gcnew ConvexHullShape(_importer->baseCreateConvexHullShape());
}

CompoundShape^ Serialize::BulletWorldImporter::CreateCompoundShape()
{
	return gcnew CompoundShape(_importer->baseCreateCompoundShape());
}

#ifndef DISABLE_BVH
ScaledBvhTriangleMeshShape^ Serialize::BulletWorldImporter::CreateScaledTrangleMeshShape(BvhTriangleMeshShape^ meshShape, Vector3 localScaling)
{
	VECTOR3_DEF(localScaling);
	ScaledBvhTriangleMeshShape^ ret = gcnew ScaledBvhTriangleMeshShape(
		_importer->baseCreateScaledTrangleMeshShape((btBvhTriangleMeshShape*)meshShape->_native, VECTOR3_USE(localScaling)));
	VECTOR3_DEL(localScaling);
	return ret;
}

OptimizedBvh^ Serialize::BulletWorldImporter::CreateOptimizedBvh()
{
	return gcnew OptimizedBvh(_importer->baseCreateOptimizedBvh());
}
#endif

MultiSphereShape^ Serialize::BulletWorldImporter::CreateMultiSphereShape(array<Vector3>^ positions, array<btScalar>^ radi)
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

//TriangleInfoMap^ Serialize::BulletWorldImporter::CreateTriangleInfoMap()
//{
//	return gcnew TriangleInfoMap(_importer->baseCreateTriangleInfoMap());
//}

#ifndef DISABLE_CONSTRAINTS

Point2PointConstraint^ Serialize::BulletWorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
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

Point2PointConstraint^ Serialize::BulletWorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA)
{
	VECTOR3_DEF(pivotInA);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_importer->baseCreatePoint2PointConstraint(
		*(btRigidBody*)rigidBodyA->_native, VECTOR3_USE(pivotInA)));

	VECTOR3_DEL(pivotInA);
	return ret;
}

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame, bool useReferenceFrameA)
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

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
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

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame, bool useReferenceFrameA)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp, useReferenceFrameA));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	return ret;
}

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	return ret;
}

ConeTwistConstraint^ Serialize::BulletWorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
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

ConeTwistConstraint^ Serialize::BulletWorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_importer->baseCreateConeTwistConstraint(
		*(btRigidBody*)rigidBodyA->_native, *rigidBodyAFrameTemp));

	ALIGNED_FREE(rigidBodyAFrameTemp);
	return ret;
}

Generic6DofConstraint^ Serialize::BulletWorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
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

Generic6DofConstraint^ Serialize::BulletWorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_importer->baseCreateGeneric6DofConstraint(
		*(btRigidBody*)rigidBodyB->_native, *frameInBTemp, useLinearReferenceFrameB));

	ALIGNED_FREE(frameInBTemp);
	return ret;
}

SliderConstraint^ Serialize::BulletWorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
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

SliderConstraint^ Serialize::BulletWorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	SliderConstraint^ ret = gcnew SliderConstraint(_importer->baseCreateSliderConstraint(
		*(btRigidBody*)rigidBodyB->_native, *frameInBTemp, useLinearReferenceFrameA));
	
	ALIGNED_FREE(frameInBTemp);
	return ret;
}

GearConstraint^ Serialize::BulletWorldImporter::CreateGearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA, Vector3 axisInB, btScalar ratio)
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


void Serialize::BulletWorldImporter::DeleteAllData()
{
	_importer->deleteAllData();
}

bool Serialize::BulletWorldImporter::LoadFile(String^ filename, String^ preSwapFilenameOut)
{
	const char* filenameTemp = StringConv::ManagedToUnmanaged(filename);
	const char* preSwapFilenameOutTemp = StringConv::ManagedToUnmanaged(preSwapFilenameOut);
	bool ret = _importer->loadFile(filenameTemp, preSwapFilenameOutTemp);
	StringConv::FreeUnmanagedString(filenameTemp);
	StringConv::FreeUnmanagedString(preSwapFilenameOutTemp);
	return ret;
}

bool Serialize::BulletWorldImporter::LoadFile(String^ filename)
{
	const char* filenameTemp = StringConv::ManagedToUnmanaged(filename);
	bool ret = _importer->loadFile(filenameTemp);
	StringConv::FreeUnmanagedString(filenameTemp);
	return ret;
}

bool Serialize::BulletWorldImporter::LoadFileFromMemory(array<Byte>^ memoryBuffer)
{
	pin_ptr<Byte> memoryBufferPtr = &memoryBuffer[0];
	return _importer->loadFileFromMemory((char*)memoryBufferPtr, memoryBuffer->Length);
}

CollisionShape^ Serialize::BulletWorldImporter::GetCollisionShapeByIndex(int index)
{
	return CollisionShape::GetManaged(_importer->getCollisionShapeByIndex(index));
}

CollisionObject^ Serialize::BulletWorldImporter::GetRigidBodyByIndex(int index)
{
	return CollisionObject::GetManaged(_importer->getRigidBodyByIndex(index));
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ Serialize::BulletWorldImporter::GetConstraintByIndex(int index)
{
	btTypedConstraint* constraint = _importer->getConstraintByIndex(index);
	return TypedConstraint::GetManaged(constraint);
}
#endif

#ifndef DISABLE_BVH
OptimizedBvh^ Serialize::BulletWorldImporter::GetBvhByIndex(int index)
{
	btOptimizedBvh* bvh = _importer->getBvhByIndex(index);
	return bvh ? gcnew OptimizedBvh(bvh) : nullptr;
}
#endif

//TriangleInfoMap^ Serialize::BulletWorldImporter::GetTriangleInfoMapByIndex(int index)
//{
//	return gcnew TriangleInfoMap(_importer->getTriangleInfoMapByIndex(index));
//}

CollisionShape^ Serialize::BulletWorldImporter::GetCollisionShapeByName(String^ name)
{
	btCollisionShape* shape;
	CollisionShape^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	shape = _importer->getCollisionShapeByName(nameTemp);
	ret = CollisionShape::GetManaged(shape);

	StringConv::FreeUnmanagedString(nameTemp);
	return ret;
}

RigidBody^ Serialize::BulletWorldImporter::GetRigidBodyByName(String^ name)
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
TypedConstraint^ Serialize::BulletWorldImporter::GetConstraintByName(String^ name)
{
	btTypedConstraint* constraint;
	TypedConstraint^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	constraint = _importer->getConstraintByName(nameTemp);
	ret = TypedConstraint::GetManaged(constraint);

	StringConv::FreeUnmanagedString(nameTemp);
	return ret;
}
#endif

String^	Serialize::BulletWorldImporter::GetNameForObject(Object^ obj)
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
	const char* name = _importer->getNameForPointer(pointer);
	return name ? StringConv::UnmanagedToManaged(name) : nullptr;
}

bool Serialize::BulletWorldImporter::IsDisposed::get()
{
	return (_importer == NULL);
}

int Serialize::BulletWorldImporter::BvhCount::get()
{
	return _importer->getNumBvhs();
}

int Serialize::BulletWorldImporter::ConstraintCount::get()
{
	return _importer->getNumConstraints();
}

int Serialize::BulletWorldImporter::CollisionShapeCount::get()
{
	return _importer->getNumCollisionShapes();
}

int Serialize::BulletWorldImporter::RigidBodyCount::get()
{
	return _importer->getNumRigidBodies();
}

int Serialize::BulletWorldImporter::TriangleInfoMapCount::get()
{
	return _importer->getNumTriangleInfoMaps();
}

int Serialize::BulletWorldImporter::VerboseMode::get()
{
	return _importer->getVerboseMode();
}
void Serialize::BulletWorldImporter::VerboseMode::set(int value)
{
	_importer->setVerboseMode(value);
}


Serialize::BulletWorldImporterWrapper::BulletWorldImporterWrapper(btDynamicsWorld* world, BulletWorldImporter^ importer)
: btBulletWorldImporter(world)
{
	_importer = importer;
}

btCollisionObject* Serialize::BulletWorldImporterWrapper::createCollisionObject(const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return _importer->CreateCollisionObject(Math::BtTransformToMatrix(&startTransform),
		CollisionShape::GetManaged(shape), StringConv::UnmanagedToManaged(bodyName))->_native;
}

btRigidBody* Serialize::BulletWorldImporterWrapper::createRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return (btRigidBody*)_importer->CreateRigidBody(isDynamic, mass, Math::BtTransformToMatrix(&startTransform),
		CollisionShape::GetManaged(shape), StringConv::UnmanagedToManaged(bodyName))->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createPlaneShape(const btVector3& planeNormal, btScalar planeConstant)
{
	return _importer->CreatePlaneShape(Math::BtVector3ToVector3(&planeNormal), planeConstant)->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createBoxShape(const btVector3& halfExtents)
{
	return _importer->CreateBoxShape(Math::BtVector3ToVector3(&halfExtents))->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createSphereShape(btScalar radius)
{
	return _importer->CreateSphereShape(radius)->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCapsuleShapeX(btScalar radius, btScalar height)
{
	return _importer->CreateCapsuleShapeX(radius, height)->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCapsuleShapeY(btScalar radius, btScalar height)
{
	return _importer->CreateCapsuleShapeY(radius, height)->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCapsuleShapeZ(btScalar radius, btScalar height)
{
	return _importer->CreateCapsuleShapeZ(radius, height)->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCylinderShapeX(btScalar radius, btScalar height)
{
	return _importer->CreateCylinderShapeX(radius, height)->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCylinderShapeY(btScalar radius, btScalar height)
{
	return _importer->CreateCylinderShapeY(radius, height)->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCylinderShapeZ(btScalar radius, btScalar height)
{
	return _importer->CreateCylinderShapeZ(radius, height)->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createConeShapeX(btScalar radius, btScalar height)
{
	return _importer->CreateConeShapeX(radius, height)->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createConeShapeY(btScalar radius, btScalar height)
{
	return _importer->CreateConeShapeY(radius, height)->_native;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createConeShapeZ(btScalar radius, btScalar height)
{
	return _importer->CreateConeShapeZ(radius, height)->_native;
}

class btTriangleIndexVertexArray* Serialize::BulletWorldImporterWrapper::createTriangleMeshContainer()
{
	return (btTriangleIndexVertexArray*)_importer->CreateTriangleMeshContainer()->_native;
}

#ifndef DISABLE_BVH
btBvhTriangleMeshShape* Serialize::BulletWorldImporterWrapper::createBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	return (btBvhTriangleMeshShape*)_importer->CreateBvhTriangleMeshShape(StridingMeshInterface::GetManaged(trimesh), gcnew OptimizedBvh(bvh))->_native;
}
#endif

btCollisionShape* Serialize::BulletWorldImporterWrapper::createConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	return _importer->CreateConvexTriangleMeshShape(StridingMeshInterface::GetManaged(trimesh))->_native;
}

#ifndef DISABLE_GIMPACT
btGImpactMeshShape* Serialize::BulletWorldImporterWrapper::createGimpactShape(btStridingMeshInterface* trimesh)
{
	return (btGImpactMeshShape*)_importer->CreateGImpactShape(StridingMeshInterface::GetManaged(trimesh))->_native;
}
#endif

class btConvexHullShape* Serialize::BulletWorldImporterWrapper::createConvexHullShape()
{
	return (btConvexHullShape*)_importer->CreateConvexHullShape()->_native;
}

class btCompoundShape* Serialize::BulletWorldImporterWrapper::createCompoundShape()
{
	return (btCompoundShape*)_importer->CreateCompoundShape()->_native;
}

#ifndef DISABLE_BVH
btOptimizedBvh* Serialize::BulletWorldImporterWrapper::createOptimizedBvh()
{
	return (btOptimizedBvh*)_importer->CreateOptimizedBvh()->_native;
}
#endif

btTriangleInfoMap* Serialize::BulletWorldImporterWrapper::createTriangleInfoMap()
{
	return baseCreateTriangleInfoMap();
	//return _importer->CreateTriangleInfoMap()->_native;
}

#ifndef DISABLE_CONSTRAINTS

btPoint2PointConstraint* Serialize::BulletWorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btVector3& pivotInA, const btVector3& pivotInB)
{
	return (btPoint2PointConstraint*)_importer->CreatePoint2PointConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtVector3ToVector3(&pivotInA), Math::BtVector3ToVector3(&pivotInB))->_native;
}

btPoint2PointConstraint* Serialize::BulletWorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, const btVector3& pivotInA)
{
	return (btPoint2PointConstraint*)_importer->CreatePoint2PointConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtVector3ToVector3(&pivotInA))->_native;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame, bool useReferenceFrameA)
{
	return (btHingeConstraint*)_importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame), useReferenceFrameA)->_native;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return (btHingeConstraint*)_importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame))->_native;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame, bool useReferenceFrameA)
{
	return (btHingeConstraint*)_importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame), useReferenceFrameA)->_native;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return (btHingeConstraint*)_importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame))->_native;
}

btConeTwistConstraint* Serialize::BulletWorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return (btConeTwistConstraint*)_importer->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame))->_native;
}

btConeTwistConstraint* Serialize::BulletWorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return (btConeTwistConstraint*)_importer->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame))->_native;
}

btGeneric6DofConstraint* Serialize::BulletWorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return (btGeneric6DofConstraint*)_importer->CreateGeneric6DofConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->_native;
}

btGeneric6DofConstraint* Serialize::BulletWorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameB)
{
	return (btGeneric6DofConstraint*)_importer->CreateGeneric6DofConstraint((RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameB)->_native;
}

btSliderConstraint* Serialize::BulletWorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return (btSliderConstraint*)_importer->CreateSliderConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->_native;
}

btSliderConstraint* Serialize::BulletWorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return (btSliderConstraint*)_importer->CreateSliderConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyB), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->_native;
}

btGearConstraint* Serialize::BulletWorldImporterWrapper::createGearConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
				const btVector3& axisInA, const btVector3& axisInB, btScalar ratio)
{
	return (btGearConstraint*)_importer->CreateGearConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtVector3ToVector3(&axisInA), Math::BtVector3ToVector3(&axisInB), ratio)->_native;
}

#endif


btCollisionObject* Serialize::BulletWorldImporterWrapper::baseCreateCollisionObject(const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return btBulletWorldImporter::createCollisionObject(startTransform, shape, bodyName);
}

btRigidBody* Serialize::BulletWorldImporterWrapper::baseCreateRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return btBulletWorldImporter::createRigidBody(isDynamic, mass, startTransform, shape, bodyName);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreatePlaneShape(const btVector3& planeNormal, btScalar planeConstant)
{
	return btBulletWorldImporter::createPlaneShape(planeNormal, planeConstant);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateBoxShape(const btVector3& halfExtents)
{
	return btBulletWorldImporter::createBoxShape(halfExtents);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateSphereShape(btScalar radius)
{
	return btBulletWorldImporter::createSphereShape(radius);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateCapsuleShapeX(btScalar radius, btScalar height)
{
	return btBulletWorldImporter::createCapsuleShapeX(radius, height);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateCapsuleShapeY(btScalar radius, btScalar height)
{
	return btBulletWorldImporter::createCapsuleShapeY(radius, height);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateCapsuleShapeZ(btScalar radius, btScalar height)
{
	return btBulletWorldImporter::createCapsuleShapeZ(radius, height);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateCylinderShapeX(btScalar radius, btScalar height)
{
	return btBulletWorldImporter::createCylinderShapeX(radius, height);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateCylinderShapeY(btScalar radius, btScalar height)
{
	return btBulletWorldImporter::createCylinderShapeY(radius, height);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateCylinderShapeZ(btScalar radius, btScalar height)
{
	return btBulletWorldImporter::createCylinderShapeZ(radius, height);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateConeShapeX(btScalar radius, btScalar height)
{
	return btBulletWorldImporter::createConeShapeX(radius, height);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateConeShapeY(btScalar radius, btScalar height)
{
	return btBulletWorldImporter::createConeShapeY(radius, height);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateConeShapeZ(btScalar radius, btScalar height)
{
	return btBulletWorldImporter::createConeShapeZ(radius, height);
}

class btTriangleIndexVertexArray* Serialize::BulletWorldImporterWrapper::baseCreateTriangleMeshContainer()
{
	return btBulletWorldImporter::createTriangleMeshContainer();
}

#ifndef DISABLE_BVH
btBvhTriangleMeshShape* Serialize::BulletWorldImporterWrapper::baseCreateBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	return btBulletWorldImporter::createBvhTriangleMeshShape(trimesh, bvh);
}
#endif

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	return btBulletWorldImporter::createConvexTriangleMeshShape(trimesh);
}

#ifndef DISABLE_GIMPACT
btGImpactMeshShape* Serialize::BulletWorldImporterWrapper::baseCreateGimpactShape(btStridingMeshInterface* trimesh)
{
	return btBulletWorldImporter::createGimpactShape(trimesh);
}
#endif

class btConvexHullShape* Serialize::BulletWorldImporterWrapper::baseCreateConvexHullShape()
{
	return btBulletWorldImporter::createConvexHullShape();
}

class btCompoundShape* Serialize::BulletWorldImporterWrapper::baseCreateCompoundShape()
{
	return btBulletWorldImporter::createCompoundShape();
}

#ifndef DISABLE_BVH
btOptimizedBvh* Serialize::BulletWorldImporterWrapper::baseCreateOptimizedBvh()
{
	return btBulletWorldImporter::createOptimizedBvh();
}

btScaledBvhTriangleMeshShape* Serialize::BulletWorldImporterWrapper::baseCreateScaledTrangleMeshShape(btBvhTriangleMeshShape* meshShape,const btVector3& localScalingbtBvhTriangleMeshShape)
{
	return btBulletWorldImporter::createScaledTrangleMeshShape(meshShape, localScalingbtBvhTriangleMeshShape);
}
#endif

btMultiSphereShape* Serialize::BulletWorldImporterWrapper::baseCreateMultiSphereShape(const btVector3* positions, const btScalar* radi, int numSpheres)
{
	return btBulletWorldImporter::createMultiSphereShape(positions, radi, numSpheres);
}

btTriangleInfoMap* Serialize::BulletWorldImporterWrapper::baseCreateTriangleInfoMap()
{
	return btBulletWorldImporter::createTriangleInfoMap();
}

#ifndef DISABLE_CONSTRAINTS

btPoint2PointConstraint* Serialize::BulletWorldImporterWrapper::baseCreatePoint2PointConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btVector3& pivotInA, const btVector3& pivotInB)
{
	return btBulletWorldImporter::createPoint2PointConstraint(rigidBodyA, rigidBodyB, pivotInA, pivotInB);
}

btPoint2PointConstraint* Serialize::BulletWorldImporterWrapper::baseCreatePoint2PointConstraint(btRigidBody& rigidBodyA, const btVector3& pivotInA)
{
	return btBulletWorldImporter::createPoint2PointConstraint(rigidBodyA, pivotInA);
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame, bool useReferenceFrameA)
{
	return btBulletWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame, useReferenceFrameA);
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return btBulletWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame);
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame, bool useReferenceFrameA)
{
	return btBulletWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyAFrame, useReferenceFrameA);
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return btBulletWorldImporter::createHingeConstraint(rigidBodyA, rigidBodyAFrame);
}

btConeTwistConstraint* Serialize::BulletWorldImporterWrapper::baseCreateConeTwistConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return btBulletWorldImporter::createConeTwistConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame);
}

btConeTwistConstraint* Serialize::BulletWorldImporterWrapper::baseCreateConeTwistConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return btBulletWorldImporter::createConeTwistConstraint(rigidBodyA, rigidBodyAFrame);
}

btGeneric6DofConstraint* Serialize::BulletWorldImporterWrapper::baseCreateGeneric6DofConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btBulletWorldImporter::createGeneric6DofConstraint(rigidBodyA, rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
}

btGeneric6DofConstraint* Serialize::BulletWorldImporterWrapper::baseCreateGeneric6DofConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameB)
{
	return btBulletWorldImporter::createGeneric6DofConstraint(rigidBodyB, frameInB, useLinearReferenceFrameB);
}

btSliderConstraint* Serialize::BulletWorldImporterWrapper::baseCreateSliderConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btBulletWorldImporter::createSliderConstraint(rigidBodyA, rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
}

btSliderConstraint* Serialize::BulletWorldImporterWrapper::baseCreateSliderConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btBulletWorldImporter::createSliderConstraint(rigidBodyB, frameInB, useLinearReferenceFrameA);
}

btGearConstraint* Serialize::BulletWorldImporterWrapper::baseCreateGearConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btVector3& axisInA, const btVector3& axisInB, btScalar ratio)
{
	return btBulletWorldImporter::createGearConstraint(rigidBodyA, rigidBodyB, axisInA, axisInB, ratio);
}

#endif

#endif
