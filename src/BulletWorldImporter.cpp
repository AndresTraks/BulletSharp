#include "StdAfx.h"

#ifndef DISABLE_SERIALIZE

#pragma managed(push, off)
#include <..\Extras\Serialize\BulletWorldImporter\btBulletWorldImporter.h>
#pragma managed(pop)

#include "BulletWorldImporter.h"
#include "StringConv.h"

Serialize::BulletWorldImporter::BulletWorldImporter(DynamicsWorld^ world)
{
	if (world == nullptr)
		_importer = new BulletWorldImporterWrapper(0, this);
	else
		_importer = new BulletWorldImporterWrapper(world->UnmanagedPointer, this);
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
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_importer = NULL;
	
	OnDisposed( this, nullptr );
}

CollisionObject^ Serialize::BulletWorldImporter::CreateCollisionObject(Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	CollisionObject^ ret = gcnew CollisionObject(
		_importer->baseCreateCollisionObject(*startTransformTemp, shape->UnmanagedPointer, bodyNameTemp));
	
	delete startTransformTemp;
	StringConv::UnmanagedToManaged(bodyNameTemp);

	return ret;
}

RigidBody^ Serialize::BulletWorldImporter::CreateRigidBody(bool isDynamic, btScalar mass, Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	RigidBody^ ret = gcnew RigidBody(
		_importer->baseCreateRigidBody(isDynamic, mass, *startTransformTemp, shape->UnmanagedPointer, bodyNameTemp));
	
	delete startTransformTemp;
	StringConv::UnmanagedToManaged(bodyNameTemp);

	return ret;
}

CollisionShape^ Serialize::BulletWorldImporter::CreatePlaneShape(Vector3 planeNormal, btScalar planeConstant)
{
	btVector3* planeNormalTemp = Math::Vector3ToBtVector3(planeNormal);
	CollisionShape^ ret = gcnew CollisionShape(_importer->baseCreatePlaneShape(*planeNormalTemp, planeConstant));
	delete planeNormalTemp;
	return ret;

}

CollisionShape^ Serialize::BulletWorldImporter::CreateBoxShape(Vector3 halfExtents)
{
	btVector3* halfExtentsTemp = Math::Vector3ToBtVector3(halfExtents);
	CollisionShape^ ret = gcnew CollisionShape(_importer->baseCreateBoxShape(*halfExtentsTemp));
	delete halfExtentsTemp;
	return ret;
}

CollisionShape^ Serialize::BulletWorldImporter::CreateSphereShape(btScalar radius)
{
	return gcnew CollisionShape(_importer->baseCreateSphereShape(radius));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCapsuleShapeX(btScalar radius, btScalar height)
{
	return gcnew CollisionShape(_importer->baseCreateCapsuleShapeX(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCapsuleShapeY(btScalar radius, btScalar height)
{
	return gcnew CollisionShape(_importer->baseCreateCapsuleShapeY(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCapsuleShapeZ(btScalar radius, btScalar height)
{
	return gcnew CollisionShape(_importer->baseCreateCapsuleShapeZ(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCylinderShapeX(btScalar radius, btScalar height)
{
	return gcnew CollisionShape(_importer->baseCreateCylinderShapeX(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCylinderShapeY(btScalar radius, btScalar height)
{
	return gcnew CollisionShape(_importer->baseCreateCylinderShapeY(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCylinderShapeZ(btScalar radius, btScalar height)
{
	return gcnew CollisionShape(_importer->baseCreateCylinderShapeZ(radius, height));
}

TriangleIndexVertexArray^ Serialize::BulletWorldImporter::CreateTriangleMeshContainer()
{
	return gcnew TriangleIndexVertexArray(_importer->baseCreateTriangleMeshContainer());
}

BvhTriangleMeshShape^ Serialize::BulletWorldImporter::CreateBvhTriangleMeshShape(StridingMeshInterface^ trimesh, OptimizedBvh^ bvh)
{
	return gcnew BvhTriangleMeshShape(_importer->baseCreateBvhTriangleMeshShape(trimesh->UnmanagedPointer, bvh->UnmanagedPointer));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateConvexTriangleMeshShape(StridingMeshInterface^ trimesh)
{
	return gcnew CollisionShape(_importer->baseCreateConvexTriangleMeshShape(trimesh->UnmanagedPointer));
}

GImpactMeshShape^ Serialize::BulletWorldImporter::CreateGimpactShape(StridingMeshInterface^ trimesh)
{
	return gcnew GImpactMeshShape(_importer->baseCreateGimpactShape(trimesh->UnmanagedPointer));
}

ConvexHullShape^ Serialize::BulletWorldImporter::CreateConvexHullShape()
{
	return gcnew ConvexHullShape(_importer->baseCreateConvexHullShape());
}

CompoundShape^ Serialize::BulletWorldImporter::CreateCompoundShape()
{
	return gcnew CompoundShape(_importer->baseCreateCompoundShape());
}

OptimizedBvh^ Serialize::BulletWorldImporter::CreateOptimizedBvh()
{
	return gcnew OptimizedBvh(_importer->baseCreateOptimizedBvh());
}

//TriangleInfoMap^ Serialize::BulletWorldImporter::CreateTriangleInfoMap()
//{
//	return gcnew TriangleInfoMap(_importer->baseCreateTriangleInfoMap());
//}

#ifndef DISABLE_CONSTRAINTS

Point2PointConstraint^ Serialize::BulletWorldImporter::CreatePoint2PointConstraint(RigidBody^ rbA, RigidBody^ rbB,
	Vector3 pivotInA, Vector3 pivotInB)
{
	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);
	btVector3* pivotInBTemp = Math::Vector3ToBtVector3(pivotInB);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_importer->baseCreatePoint2PointConstraint(
		*rbA->UnmanagedPointer, *rbB->UnmanagedPointer, *pivotInATemp, *pivotInBTemp));

	delete pivotInATemp;
	delete pivotInBTemp;

	return ret;
}

Point2PointConstraint^ Serialize::BulletWorldImporter::CreatePoint2PointConstraint(RigidBody^ rbA, Vector3 pivotInA)
{
	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_importer->baseCreatePoint2PointConstraint(
		*rbA->UnmanagedPointer, *pivotInATemp));

	delete pivotInATemp;
	return ret;
}

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix rbAFrame, Matrix rbBFrame, bool useReferenceFrameA)
{
	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);
	btTransform* rbBFrameTemp = Math::MatrixToBtTransform(rbBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*rbA->UnmanagedPointer, *rbB->UnmanagedPointer, *rbAFrameTemp, *rbBFrameTemp, useReferenceFrameA));
	
	delete rbAFrameTemp;
	delete rbBFrameTemp;

	return ret;
}

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix rbAFrame, Matrix rbBFrame)
{
	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);
	btTransform* rbBFrameTemp = Math::MatrixToBtTransform(rbBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*rbA->UnmanagedPointer, *rbB->UnmanagedPointer, *rbAFrameTemp, *rbBFrameTemp));
	
	delete rbAFrameTemp;
	delete rbBFrameTemp;

	return ret;
}

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rbA, Matrix rbAFrame, bool useReferenceFrameA)
{
	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*rbA->UnmanagedPointer, *rbAFrameTemp, useReferenceFrameA));
	
	delete rbAFrameTemp;
	return ret;
}

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rbA, Matrix rbAFrame)
{
	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*rbA->UnmanagedPointer, *rbAFrameTemp));
	
	delete rbAFrameTemp;
	return ret;
}

ConeTwistConstraint^ Serialize::BulletWorldImporter::CreateConeTwistConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix rbAFrame, Matrix rbBFrame)
{
	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);
	btTransform* rbBFrameTemp = Math::MatrixToBtTransform(rbBFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_importer->baseCreateConeTwistConstraint(
		*rbA->UnmanagedPointer, *rbB->UnmanagedPointer, *rbAFrameTemp, *rbBFrameTemp));
	
	delete rbAFrameTemp;
	delete rbBFrameTemp;

	return ret;
}

ConeTwistConstraint^ Serialize::BulletWorldImporter::CreateConeTwistConstraint(RigidBody^ rbA, Matrix rbAFrame)
{
	btTransform* rbAFrameTemp = Math::MatrixToBtTransform(rbAFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_importer->baseCreateConeTwistConstraint(
		*rbA->UnmanagedPointer, *rbAFrameTemp));
	
	delete rbAFrameTemp;
	return ret;
}

Generic6DofConstraint^ Serialize::BulletWorldImporter::CreateGeneric6DofConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_importer->baseCreateGeneric6DofConstraint(
		*rbA->UnmanagedPointer, *rbB->UnmanagedPointer, *frameInATemp, *frameInBTemp, useLinearReferenceFrameA));
	
	delete frameInATemp;
	delete frameInBTemp;

	return ret;
}

Generic6DofConstraint^ Serialize::BulletWorldImporter::CreateGeneric6DofConstraint(RigidBody^ rbB, Matrix frameInB, bool useLinearReferenceFrameB)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_importer->baseCreateGeneric6DofConstraint(
		*rbB->UnmanagedPointer, *frameInBTemp, useLinearReferenceFrameB));
	
	delete frameInBTemp;
	return ret;
}

SliderConstraint^ Serialize::BulletWorldImporter::CreateSliderConstraint(RigidBody^ rbA, RigidBody^ rbB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	SliderConstraint^ ret = gcnew SliderConstraint(_importer->baseCreateSliderConstraint(
		*rbA->UnmanagedPointer, *rbB->UnmanagedPointer, *frameInATemp, *frameInBTemp, useLinearReferenceFrameA));
	
	delete frameInATemp;
	delete frameInBTemp;

	return ret;
}

SliderConstraint^ Serialize::BulletWorldImporter::CreateSliderConstraint(RigidBody^ rbB, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	SliderConstraint^ ret = gcnew SliderConstraint(_importer->baseCreateSliderConstraint(
		*rbB->UnmanagedPointer,*frameInBTemp, useLinearReferenceFrameA));
	
	delete frameInBTemp;
	return ret;
}

#endif


void Serialize::BulletWorldImporter::DeleteAllData()
{
	_importer->deleteAllData();
}

bool Serialize::BulletWorldImporter::LoadFile(String^ filename)
{
	const char* filenameTemp = StringConv::ManagedToUnmanaged(filename);
	bool ret = _importer->loadFile(filenameTemp);
	StringConv::FreeUnmanagedString(filenameTemp);
	return ret;
}

CollisionShape^ Serialize::BulletWorldImporter::GetCollisionShapeByIndex(int index)
{
	return gcnew CollisionShape(_importer->getCollisionShapeByIndex(index));
}

CollisionObject^ Serialize::BulletWorldImporter::GetRigidBodyByIndex(int index)
{
	return gcnew CollisionObject(_importer->getRigidBodyByIndex(index));
}

TypedConstraint^ Serialize::BulletWorldImporter::GetConstraintByIndex(int index)
{
	return gcnew TypedConstraint(_importer->getConstraintByIndex(index));
}

OptimizedBvh^ Serialize::BulletWorldImporter::GetBvhByIndex(int index)
{
	return gcnew OptimizedBvh(_importer->getBvhByIndex(index));
}

//TriangleInfoMap^ Serialize::BulletWorldImporter::GetTriangleInfoMapByIndex(int index)
//{
//	return gcnew TriangleInfoMap(_importer->getTriangleInfoMapByIndex(index));
//}

CollisionShape^ Serialize::BulletWorldImporter::GetCollisionShapeByName(String^ name)
{
	const char* nameTemp = StringConv::ManagedToUnmanaged(name);
	
	CollisionShape^ ret = gcnew CollisionShape(_importer->getCollisionShapeByName(nameTemp));
	
	StringConv::UnmanagedToManaged(nameTemp);
	return ret;
}

RigidBody^ Serialize::BulletWorldImporter::GetRigidBodyByName(String^ name)
{
	const char* nameTemp = StringConv::ManagedToUnmanaged(name);
	
	RigidBody^ ret = gcnew RigidBody(_importer->getRigidBodyByName(nameTemp));
	
	StringConv::UnmanagedToManaged(nameTemp);
	return ret;
}

TypedConstraint^ Serialize::BulletWorldImporter::GetConstraintByName(String^ name)
{
	const char* nameTemp = StringConv::ManagedToUnmanaged(name);
	
	TypedConstraint^ ret = gcnew TypedConstraint(_importer->getConstraintByName(nameTemp));
	
	StringConv::UnmanagedToManaged(nameTemp);
	return ret;
}

String^	Serialize::BulletWorldImporter::GetNameForObject(Object^ obj)
{
	CollisionShape^ shape = static_cast<CollisionShape^>(obj);
	if (shape != nullptr)
		return StringConv::UnmanagedToManaged(_importer->getNameForPointer(shape->UnmanagedPointer));

	TypedConstraint^ constraint = static_cast<TypedConstraint^>(obj);
	if (constraint != nullptr)
		return StringConv::UnmanagedToManaged(_importer->getNameForPointer(constraint->UnmanagedPointer));

	CollisionObject^ body = static_cast<RigidBody^>(obj);
	if (body != nullptr)
		return StringConv::UnmanagedToManaged(_importer->getNameForPointer(body->UnmanagedPointer));

	body = static_cast<CollisionObject^>(obj);
	if (body != nullptr)
		return StringConv::UnmanagedToManaged(_importer->getNameForPointer(body->UnmanagedPointer));

	return nullptr;
}

bool Serialize::BulletWorldImporter::IsDisposed::get()
{
	return (_importer == NULL);
}

int Serialize::BulletWorldImporter::NumBvhs::get()
{
	return _importer->getNumBvhs();
}

int Serialize::BulletWorldImporter::NumConstraints::get()
{
	return _importer->getNumConstraints();
}

int Serialize::BulletWorldImporter::NumCollisionShapes::get()
{
	return _importer->getNumCollisionShapes();
}

int Serialize::BulletWorldImporter::NumRigidBodies::get()
{
	return _importer->getNumRigidBodies();
}

int Serialize::BulletWorldImporter::NumTriangleInfoMaps::get()
{
	return _importer->getNumTriangleInfoMaps();
}

bool Serialize::BulletWorldImporter::VerboseMode::get()
{
	return _importer->getVerboseMode();
}
void Serialize::BulletWorldImporter::VerboseMode::set(bool value)
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
		gcnew CollisionShape(shape), StringConv::UnmanagedToManaged(bodyName))->UnmanagedPointer;
}

btRigidBody* Serialize::BulletWorldImporterWrapper::createRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return _importer->CreateRigidBody(isDynamic, mass, Math::BtTransformToMatrix(&startTransform),
		gcnew CollisionShape(shape), StringConv::UnmanagedToManaged(bodyName))->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createPlaneShape(const btVector3& planeNormal, btScalar planeConstant)
{
	return _importer->CreatePlaneShape(Math::BtVector3ToVector3(&planeNormal), planeConstant)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createBoxShape(const btVector3& halfExtents)
{
	return _importer->CreateBoxShape(Math::BtVector3ToVector3(&halfExtents))->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createSphereShape(btScalar radius)
{
	return _importer->CreateSphereShape(radius)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCapsuleShapeX(btScalar radius, btScalar height)
{
	return _importer->CreateCapsuleShapeX(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCapsuleShapeY(btScalar radius, btScalar height)
{
	return _importer->CreateCapsuleShapeY(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCapsuleShapeZ(btScalar radius, btScalar height)
{
	return _importer->CreateCapsuleShapeZ(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCylinderShapeX(btScalar radius, btScalar height)
{
	return _importer->CreateCylinderShapeX(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCylinderShapeY(btScalar radius, btScalar height)
{
	return _importer->CreateCylinderShapeY(radius, height)->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createCylinderShapeZ(btScalar radius, btScalar height)
{
	return _importer->CreateCylinderShapeZ(radius, height)->UnmanagedPointer;
}

class btTriangleIndexVertexArray* Serialize::BulletWorldImporterWrapper::createTriangleMeshContainer()
{
	return _importer->CreateTriangleMeshContainer()->UnmanagedPointer;
}

btBvhTriangleMeshShape* Serialize::BulletWorldImporterWrapper::createBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	return _importer->CreateBvhTriangleMeshShape(gcnew StridingMeshInterface(trimesh), gcnew OptimizedBvh(bvh))->UnmanagedPointer;
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::createConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	return _importer->CreateConvexTriangleMeshShape(gcnew StridingMeshInterface(trimesh))->UnmanagedPointer;
}

btGImpactMeshShape* Serialize::BulletWorldImporterWrapper::createGimpactShape(btStridingMeshInterface* trimesh)
{
	return _importer->CreateGimpactShape(gcnew StridingMeshInterface(trimesh))->UnmanagedPointer;
}

class btConvexHullShape* Serialize::BulletWorldImporterWrapper::createConvexHullShape()
{
	return _importer->CreateConvexHullShape()->UnmanagedPointer;
}

class btCompoundShape* Serialize::BulletWorldImporterWrapper::createCompoundShape()
{
	return _importer->CreateCompoundShape()->UnmanagedPointer;
}

btOptimizedBvh* Serialize::BulletWorldImporterWrapper::createOptimizedBvh()
{
	return _importer->CreateOptimizedBvh()->UnmanagedPointer;
}

btTriangleInfoMap* Serialize::BulletWorldImporterWrapper::createTriangleInfoMap()
{
	return baseCreateTriangleInfoMap();
	//return _importer->CreateTriangleInfoMap()->UnmanagedPointer;
}

#ifndef DISABLE_CONSTRAINTS

btPoint2PointConstraint* Serialize::BulletWorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rbA, btRigidBody& rbB,
	const btVector3& pivotInA, const btVector3& pivotInB)
{
	return _importer->CreatePoint2PointConstraint(gcnew RigidBody(&rbA), gcnew RigidBody(&rbB),
		Math::BtVector3ToVector3(&pivotInA), Math::BtVector3ToVector3(&pivotInB))->UnmanagedPointer;
}

btPoint2PointConstraint* Serialize::BulletWorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rbA, const btVector3& pivotInA)
{
	return _importer->CreatePoint2PointConstraint(gcnew RigidBody(&rbA), Math::BtVector3ToVector3(&pivotInA))->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rbA,btRigidBody& rbB,
	const btTransform& rbAFrame, const btTransform& rbBFrame, bool useReferenceFrameA)
{
	return _importer->CreateHingeConstraint(gcnew RigidBody(&rbA), gcnew RigidBody(&rbB),
		Math::BtTransformToMatrix(&rbAFrame), Math::BtTransformToMatrix(&rbBFrame), useReferenceFrameA)->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rbA,btRigidBody& rbB,
	const btTransform& rbAFrame, const btTransform& rbBFrame)
{
	return _importer->CreateHingeConstraint(gcnew RigidBody(&rbA), gcnew RigidBody(&rbB),
		Math::BtTransformToMatrix(&rbAFrame), Math::BtTransformToMatrix(&rbBFrame))->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rbA, const btTransform& rbAFrame, bool useReferenceFrameA)
{
	return _importer->CreateHingeConstraint(gcnew RigidBody(&rbA), Math::BtTransformToMatrix(&rbAFrame), useReferenceFrameA)->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rbA, const btTransform& rbAFrame)
{
	return _importer->CreateHingeConstraint(gcnew RigidBody(&rbA), Math::BtTransformToMatrix(&rbAFrame))->UnmanagedPointer;
}

btConeTwistConstraint* Serialize::BulletWorldImporterWrapper::createConeTwistConstraint(btRigidBody& rbA, btRigidBody& rbB,
	const btTransform& rbAFrame, const btTransform& rbBFrame)
{
	return _importer->CreateConeTwistConstraint(gcnew RigidBody(&rbA), gcnew RigidBody(&rbB),
		Math::BtTransformToMatrix(&rbAFrame), Math::BtTransformToMatrix(&rbBFrame))->UnmanagedPointer;
}

btConeTwistConstraint* Serialize::BulletWorldImporterWrapper::createConeTwistConstraint(btRigidBody& rbA, const btTransform& rbAFrame)
{
	return _importer->CreateConeTwistConstraint(gcnew RigidBody(&rbA), Math::BtTransformToMatrix(&rbAFrame))->UnmanagedPointer;
}

btGeneric6DofConstraint* Serialize::BulletWorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rbA, btRigidBody& rbB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _importer->CreateGeneric6DofConstraint(gcnew RigidBody(&rbA), gcnew RigidBody(&rbB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
}

btGeneric6DofConstraint* Serialize::BulletWorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rbB,
	const btTransform& frameInB, bool useLinearReferenceFrameB)
{
	return _importer->CreateGeneric6DofConstraint(gcnew RigidBody(&rbB),
		Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameB)->UnmanagedPointer;
}

btSliderConstraint* Serialize::BulletWorldImporterWrapper::createSliderConstraint(btRigidBody& rbA, btRigidBody& rbB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _importer->CreateSliderConstraint(gcnew RigidBody(&rbA), gcnew RigidBody(&rbB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
}

btSliderConstraint* Serialize::BulletWorldImporterWrapper::createSliderConstraint(btRigidBody& rbB,
	const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _importer->CreateSliderConstraint(gcnew RigidBody(&rbB), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
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

class btTriangleIndexVertexArray* Serialize::BulletWorldImporterWrapper::baseCreateTriangleMeshContainer()
{
	return btBulletWorldImporter::createTriangleMeshContainer();
}

btBvhTriangleMeshShape* Serialize::BulletWorldImporterWrapper::baseCreateBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	return btBulletWorldImporter::createBvhTriangleMeshShape(trimesh, bvh);
}

btCollisionShape* Serialize::BulletWorldImporterWrapper::baseCreateConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	return btBulletWorldImporter::createConvexTriangleMeshShape(trimesh);
}

btGImpactMeshShape* Serialize::BulletWorldImporterWrapper::baseCreateGimpactShape(btStridingMeshInterface* trimesh)
{
	return btBulletWorldImporter::createGimpactShape(trimesh);
}

class btConvexHullShape* Serialize::BulletWorldImporterWrapper::baseCreateConvexHullShape()
{
	return btBulletWorldImporter::createConvexHullShape();
}

class btCompoundShape* Serialize::BulletWorldImporterWrapper::baseCreateCompoundShape()
{
	return btBulletWorldImporter::createCompoundShape();
}

btOptimizedBvh* Serialize::BulletWorldImporterWrapper::baseCreateOptimizedBvh()
{
	return btBulletWorldImporter::createOptimizedBvh();
}

btTriangleInfoMap* Serialize::BulletWorldImporterWrapper::baseCreateTriangleInfoMap()
{
	return btBulletWorldImporter::createTriangleInfoMap();
}

#ifndef DISABLE_CONSTRAINTS

btPoint2PointConstraint* Serialize::BulletWorldImporterWrapper::baseCreatePoint2PointConstraint(btRigidBody& rbA, btRigidBody& rbB,
	const btVector3& pivotInA, const btVector3& pivotInB)
{
	return btBulletWorldImporter::createPoint2PointConstraint(rbA, rbB, pivotInA, pivotInB);
}

btPoint2PointConstraint* Serialize::BulletWorldImporterWrapper::baseCreatePoint2PointConstraint(btRigidBody& rbA, const btVector3& pivotInA)
{
	return btBulletWorldImporter::createPoint2PointConstraint(rbA, pivotInA);
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rbA,btRigidBody& rbB,
	const btTransform& rbAFrame, const btTransform& rbBFrame, bool useReferenceFrameA)
{
	return btBulletWorldImporter::createHingeConstraint(rbA, rbB, rbAFrame, rbBFrame, useReferenceFrameA);
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rbA,btRigidBody& rbB,
	const btTransform& rbAFrame, const btTransform& rbBFrame)
{
	return btBulletWorldImporter::createHingeConstraint(rbA, rbB, rbAFrame, rbBFrame);
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rbA, const btTransform& rbAFrame, bool useReferenceFrameA)
{
	return btBulletWorldImporter::createHingeConstraint(rbA, rbAFrame, useReferenceFrameA);
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::baseCreateHingeConstraint(btRigidBody& rbA, const btTransform& rbAFrame)
{
	return btBulletWorldImporter::createHingeConstraint(rbA, rbAFrame);
}

btConeTwistConstraint* Serialize::BulletWorldImporterWrapper::baseCreateConeTwistConstraint(btRigidBody& rbA,btRigidBody& rbB,
	const btTransform& rbAFrame, const btTransform& rbBFrame)
{
	return btBulletWorldImporter::createConeTwistConstraint(rbA, rbB, rbAFrame, rbBFrame);
}

btConeTwistConstraint* Serialize::BulletWorldImporterWrapper::baseCreateConeTwistConstraint(btRigidBody& rbA, const btTransform& rbAFrame)
{
	return btBulletWorldImporter::createConeTwistConstraint(rbA, rbAFrame);
}

btGeneric6DofConstraint* Serialize::BulletWorldImporterWrapper::baseCreateGeneric6DofConstraint(btRigidBody& rbA, btRigidBody& rbB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btBulletWorldImporter::createGeneric6DofConstraint(rbA, rbB, frameInA, frameInB, useLinearReferenceFrameA);
}

btGeneric6DofConstraint* Serialize::BulletWorldImporterWrapper::baseCreateGeneric6DofConstraint(btRigidBody& rbB,
	const btTransform& frameInB, bool useLinearReferenceFrameB)
{
	return btBulletWorldImporter::createGeneric6DofConstraint(rbB, frameInB, useLinearReferenceFrameB);
}

btSliderConstraint* Serialize::BulletWorldImporterWrapper::baseCreateSliderConstraint(btRigidBody& rbA, btRigidBody& rbB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btBulletWorldImporter::createSliderConstraint(rbA, rbB, frameInA, frameInB, useLinearReferenceFrameA);
}

btSliderConstraint* Serialize::BulletWorldImporterWrapper::baseCreateSliderConstraint(btRigidBody& rbB,
	const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btBulletWorldImporter::createSliderConstraint(rbB, frameInB, useLinearReferenceFrameA);
}

#endif

#endif
