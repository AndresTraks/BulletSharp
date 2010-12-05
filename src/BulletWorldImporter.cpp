#include "StdAfx.h"

#ifndef DISABLE_SERIALIZE

#include "BulletWorldImporter.h"
#include "StringConv.h"
#ifndef DISABLE_BVH
#include "OptimizedBvh.h"
#endif

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
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	_importer = NULL;

	OnDisposed(this, nullptr);
}

CollisionObject^ Serialize::BulletWorldImporter::CreateCollisionObject(Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	CollisionObject^ ret = CollisionObject::Upcast(
		_importer->baseCreateCollisionObject(*startTransformTemp, shape->UnmanagedPointer, bodyNameTemp));

	delete startTransformTemp;
	StringConv::UnmanagedToManaged(bodyNameTemp);

	return ret;
}

RigidBody^ Serialize::BulletWorldImporter::CreateRigidBody(bool isDynamic, btScalar mass, Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	btTransform* startTransformTemp = Math::MatrixToBtTransform(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	RigidBody^ ret = (RigidBody^)CollisionObject::Upcast(
		_importer->baseCreateRigidBody(isDynamic, mass, *startTransformTemp, shape->UnmanagedPointer, bodyNameTemp));

	delete startTransformTemp;
	StringConv::UnmanagedToManaged(bodyNameTemp);

	return ret;
}

CollisionShape^ Serialize::BulletWorldImporter::CreatePlaneShape(Vector3 planeNormal, btScalar planeConstant)
{
	btVector3* planeNormalTemp = Math::Vector3ToBtVector3(planeNormal);
	CollisionShape^ ret = CollisionShape::Upcast(_importer->baseCreatePlaneShape(*planeNormalTemp, planeConstant));
	delete planeNormalTemp;
	return ret;

}

CollisionShape^ Serialize::BulletWorldImporter::CreateBoxShape(Vector3 halfExtents)
{
	btVector3* halfExtentsTemp = Math::Vector3ToBtVector3(halfExtents);
	CollisionShape^ ret = CollisionShape::Upcast(_importer->baseCreateBoxShape(*halfExtentsTemp));
	delete halfExtentsTemp;
	return ret;
}

CollisionShape^ Serialize::BulletWorldImporter::CreateSphereShape(btScalar radius)
{
	return CollisionShape::Upcast(_importer->baseCreateSphereShape(radius));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCapsuleShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::Upcast(_importer->baseCreateCapsuleShapeX(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCapsuleShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::Upcast(_importer->baseCreateCapsuleShapeY(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCapsuleShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::Upcast(_importer->baseCreateCapsuleShapeZ(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCylinderShapeX(btScalar radius, btScalar height)
{
	return CollisionShape::Upcast(_importer->baseCreateCylinderShapeX(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCylinderShapeY(btScalar radius, btScalar height)
{
	return CollisionShape::Upcast(_importer->baseCreateCylinderShapeY(radius, height));
}

CollisionShape^ Serialize::BulletWorldImporter::CreateCylinderShapeZ(btScalar radius, btScalar height)
{
	return CollisionShape::Upcast(_importer->baseCreateCylinderShapeZ(radius, height));
}

TriangleIndexVertexArray^ Serialize::BulletWorldImporter::CreateTriangleMeshContainer()
{
	return gcnew TriangleIndexVertexArray(_importer->baseCreateTriangleMeshContainer());
}

#ifndef DISABLE_BVH
BvhTriangleMeshShape^ Serialize::BulletWorldImporter::CreateBvhTriangleMeshShape(StridingMeshInterface^ trimesh, OptimizedBvh^ bvh)
{
	return gcnew BvhTriangleMeshShape(_importer->baseCreateBvhTriangleMeshShape(trimesh->UnmanagedPointer, bvh->UnmanagedPointer));
}
#endif

CollisionShape^ Serialize::BulletWorldImporter::CreateConvexTriangleMeshShape(StridingMeshInterface^ trimesh)
{
	return CollisionShape::Upcast(_importer->baseCreateConvexTriangleMeshShape(trimesh->UnmanagedPointer));
}

#ifndef DISABLE_GIMPACT
GImpactMeshShape^ Serialize::BulletWorldImporter::CreateGImpactShape(StridingMeshInterface^ trimesh)
{
	return gcnew GImpactMeshShape(_importer->baseCreateGimpactShape(trimesh->UnmanagedPointer));
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
OptimizedBvh^ Serialize::BulletWorldImporter::CreateOptimizedBvh()
{
	return gcnew OptimizedBvh(_importer->baseCreateOptimizedBvh());
}
#endif

//TriangleInfoMap^ Serialize::BulletWorldImporter::CreateTriangleInfoMap()
//{
//	return gcnew TriangleInfoMap(_importer->baseCreateTriangleInfoMap());
//}

#ifndef DISABLE_CONSTRAINTS

Point2PointConstraint^ Serialize::BulletWorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 pivotInA, Vector3 pivotInB)
{
	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);
	btVector3* pivotInBTemp = Math::Vector3ToBtVector3(pivotInB);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_importer->baseCreatePoint2PointConstraint(
		*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer, *pivotInATemp, *pivotInBTemp));

	delete pivotInATemp;
	delete pivotInBTemp;

	return ret;
}

Point2PointConstraint^ Serialize::BulletWorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA)
{
	btVector3* pivotInATemp = Math::Vector3ToBtVector3(pivotInA);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_importer->baseCreatePoint2PointConstraint(
		*rigidBodyA->UnmanagedPointer, *pivotInATemp));

	delete pivotInATemp;
	return ret;
}

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame, bool useReferenceFrameA)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer, *rigidBodyAFrameTemp, *rigidBodyBFrameTemp, useReferenceFrameA));

	delete rigidBodyAFrameTemp;
	delete rigidBodyBFrameTemp;

	return ret;
}

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer, *rigidBodyAFrameTemp, *rigidBodyBFrameTemp));

	delete rigidBodyAFrameTemp;
	delete rigidBodyBFrameTemp;

	return ret;
}

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame, bool useReferenceFrameA)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*rigidBodyA->UnmanagedPointer, *rigidBodyAFrameTemp, useReferenceFrameA));

	delete rigidBodyAFrameTemp;
	return ret;
}

HingeConstraint^ Serialize::BulletWorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_importer->baseCreateHingeConstraint(
		*rigidBodyA->UnmanagedPointer, *rigidBodyAFrameTemp));

	delete rigidBodyAFrameTemp;
	return ret;
}

ConeTwistConstraint^ Serialize::BulletWorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);
	btTransform* rigidBodyBFrameTemp = Math::MatrixToBtTransform(rigidBodyBFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_importer->baseCreateConeTwistConstraint(
		*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer, *rigidBodyAFrameTemp, *rigidBodyBFrameTemp));

	delete rigidBodyAFrameTemp;
	delete rigidBodyBFrameTemp;

	return ret;
}

ConeTwistConstraint^ Serialize::BulletWorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	btTransform* rigidBodyAFrameTemp = Math::MatrixToBtTransform(rigidBodyAFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_importer->baseCreateConeTwistConstraint(
		*rigidBodyA->UnmanagedPointer, *rigidBodyAFrameTemp));

	delete rigidBodyAFrameTemp;
	return ret;
}

Generic6DofConstraint^ Serialize::BulletWorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_importer->baseCreateGeneric6DofConstraint(
		*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer, *frameInATemp, *frameInBTemp, useLinearReferenceFrameA));

	delete frameInATemp;
	delete frameInBTemp;

	return ret;
}

Generic6DofConstraint^ Serialize::BulletWorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_importer->baseCreateGeneric6DofConstraint(
		*rigidBodyB->UnmanagedPointer, *frameInBTemp, useLinearReferenceFrameB));

	delete frameInBTemp;
	return ret;
}

SliderConstraint^ Serialize::BulletWorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInATemp = Math::MatrixToBtTransform(frameInA);
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	SliderConstraint^ ret = gcnew SliderConstraint(_importer->baseCreateSliderConstraint(
		*rigidBodyA->UnmanagedPointer, *rigidBodyB->UnmanagedPointer,
		*frameInATemp, *frameInBTemp, useLinearReferenceFrameA));

	delete frameInATemp;
	delete frameInBTemp;

	return ret;
}

SliderConstraint^ Serialize::BulletWorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA)
{
	btTransform* frameInBTemp = Math::MatrixToBtTransform(frameInB);

	SliderConstraint^ ret = gcnew SliderConstraint(_importer->baseCreateSliderConstraint(
		*rigidBodyB->UnmanagedPointer,*frameInBTemp, useLinearReferenceFrameA));
	
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
	return CollisionShape::Upcast(_importer->getCollisionShapeByIndex(index));
}

CollisionObject^ Serialize::BulletWorldImporter::GetRigidBodyByIndex(int index)
{
	return CollisionObject::Upcast(_importer->getRigidBodyByIndex(index));
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ Serialize::BulletWorldImporter::GetConstraintByIndex(int index)
{
	btTypedConstraint* constraint = _importer->getConstraintByIndex(index);
	return TypedConstraint::Upcast(constraint);
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
	ret = CollisionShape::Upcast(shape);

	StringConv::UnmanagedToManaged(nameTemp);
	return ret;
}

RigidBody^ Serialize::BulletWorldImporter::GetRigidBodyByName(String^ name)
{
	btRigidBody* body;
	RigidBody^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	body = _importer->getRigidBodyByName(nameTemp);
	ret = (RigidBody^)CollisionObject::Upcast(body);

	StringConv::UnmanagedToManaged(nameTemp);
	return ret;
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ Serialize::BulletWorldImporter::GetConstraintByName(String^ name)
{
	btTypedConstraint* constraint;
	TypedConstraint^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	constraint = _importer->getConstraintByName(nameTemp);
	ret = TypedConstraint::Upcast(constraint);

	StringConv::UnmanagedToManaged(nameTemp);
	return ret;
}
#endif

String^	Serialize::BulletWorldImporter::GetNameForObject(Object^ obj)
{
	const void* pointer = 0;

	CollisionShape^ shape = static_cast<CollisionShape^>(obj);
	if (shape != nullptr)
	{
		pointer = shape->UnmanagedPointer;
		goto returnName;
	}

	CollisionObject^ body = static_cast<CollisionObject^>(obj);
	if (body != nullptr)
	{
		pointer = body->UnmanagedPointer;
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
		CollisionShape::Upcast(shape), StringConv::UnmanagedToManaged(bodyName))->UnmanagedPointer;
}

btRigidBody* Serialize::BulletWorldImporterWrapper::createRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	return _importer->CreateRigidBody(isDynamic, mass, Math::BtTransformToMatrix(&startTransform),
		CollisionShape::Upcast(shape), StringConv::UnmanagedToManaged(bodyName))->UnmanagedPointer;
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

#ifndef DISABLE_BVH
btBvhTriangleMeshShape* Serialize::BulletWorldImporterWrapper::createBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	return _importer->CreateBvhTriangleMeshShape(gcnew StridingMeshInterface(trimesh), gcnew OptimizedBvh(bvh))->UnmanagedPointer;
}
#endif

btCollisionShape* Serialize::BulletWorldImporterWrapper::createConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	return _importer->CreateConvexTriangleMeshShape(gcnew StridingMeshInterface(trimesh))->UnmanagedPointer;
}

#ifndef DISABLE_GIMPACT
btGImpactMeshShape* Serialize::BulletWorldImporterWrapper::createGimpactShape(btStridingMeshInterface* trimesh)
{
	return _importer->CreateGImpactShape(gcnew StridingMeshInterface(trimesh))->UnmanagedPointer;
}
#endif

class btConvexHullShape* Serialize::BulletWorldImporterWrapper::createConvexHullShape()
{
	return _importer->CreateConvexHullShape()->UnmanagedPointer;
}

class btCompoundShape* Serialize::BulletWorldImporterWrapper::createCompoundShape()
{
	return _importer->CreateCompoundShape()->UnmanagedPointer;
}

#ifndef DISABLE_BVH
btOptimizedBvh* Serialize::BulletWorldImporterWrapper::createOptimizedBvh()
{
	return _importer->CreateOptimizedBvh()->UnmanagedPointer;
}
#endif

btTriangleInfoMap* Serialize::BulletWorldImporterWrapper::createTriangleInfoMap()
{
	return baseCreateTriangleInfoMap();
	//return _importer->CreateTriangleInfoMap()->UnmanagedPointer;
}

#ifndef DISABLE_CONSTRAINTS

btPoint2PointConstraint* Serialize::BulletWorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btVector3& pivotInA, const btVector3& pivotInB)
{
	return _importer->CreatePoint2PointConstraint(
		(RigidBody^)CollisionObject::Upcast(&rigidBodyA), (RigidBody^)CollisionObject::Upcast(&rigidBodyB),
		Math::BtVector3ToVector3(&pivotInA), Math::BtVector3ToVector3(&pivotInB))->UnmanagedPointer;
}

btPoint2PointConstraint* Serialize::BulletWorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, const btVector3& pivotInA)
{
	return _importer->CreatePoint2PointConstraint((RigidBody^)CollisionObject::Upcast(&rigidBodyA), Math::BtVector3ToVector3(&pivotInA))->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame, bool useReferenceFrameA)
{
	return _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::Upcast(&rigidBodyA), (RigidBody^)CollisionObject::Upcast(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame), useReferenceFrameA)->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::Upcast(&rigidBodyA), (RigidBody^)CollisionObject::Upcast(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame))->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame, bool useReferenceFrameA)
{
	return _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::Upcast(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame), useReferenceFrameA)->UnmanagedPointer;
}

btHingeConstraint* Serialize::BulletWorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::Upcast(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame))->UnmanagedPointer;
}

btConeTwistConstraint* Serialize::BulletWorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	return _importer->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::Upcast(&rigidBodyA), (RigidBody^)CollisionObject::Upcast(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame))->UnmanagedPointer;
}

btConeTwistConstraint* Serialize::BulletWorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	return _importer->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::Upcast(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame))->UnmanagedPointer;
}

btGeneric6DofConstraint* Serialize::BulletWorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _importer->CreateGeneric6DofConstraint(
		(RigidBody^)CollisionObject::Upcast(&rigidBodyA), (RigidBody^)CollisionObject::Upcast(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
}

btGeneric6DofConstraint* Serialize::BulletWorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameB)
{
	return _importer->CreateGeneric6DofConstraint((RigidBody^)CollisionObject::Upcast(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameB)->UnmanagedPointer;
}

btSliderConstraint* Serialize::BulletWorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _importer->CreateSliderConstraint(
		(RigidBody^)CollisionObject::Upcast(&rigidBodyA), (RigidBody^)CollisionObject::Upcast(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
}

btSliderConstraint* Serialize::BulletWorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return _importer->CreateSliderConstraint(
		(RigidBody^)CollisionObject::Upcast(&rigidBodyB), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA)->UnmanagedPointer;
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
#endif

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

#endif

#endif
