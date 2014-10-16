#include "StdAfx.h"

#if 0
#ifndef DISABLE_SERIALIZE

#include "BoxShape.h"
#include "WorldImporter.h"
#include "CapsuleShape.h"
#include "CollisionObject.h"
#include "CompoundShape.h"
#include "ConeShape.h"
#include "ConvexHullShape.h"
#include "ConvexTriangleMeshShape.h"
#include "CylinderShape.h"
#include "DynamicsWorld.h"
#include "MultiSphereShape.h"
#include "RigidBody.h"
#include "SphereShape.h"
#include "StaticPlaneShape.h"
#include "StridingMeshInterface.h"
#include "StringConv.h"
#include "TriangleIndexVertexArray.h"
#include "TriangleInfoMap.h"
#ifndef DISABLE_BVH
#include "BvhTriangleMeshShape.h"
#include "OptimizedBvh.h"
#include "ScaledBvhTriangleMeshShape.h"
#endif
#ifndef DISABLE_CONSTRAINTS
#include "ConeTwistConstraint.h"
#include "GearConstraint.h"
#include "Generic6DofConstraint.h"
#include "Generic6DofSpringConstraint.h"
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
	_world = world;
	_allocatedRigidBodies = gcnew System::Collections::Generic::List<CollisionObject^>();
	_allocatedCollisionShapes = gcnew System::Collections::Generic::List<CollisionShape^>();
#ifndef DISABLE_CONSTRAINTS
	_allocatedConstraints = gcnew System::Collections::Generic::List<TypedConstraint^>();
#endif
	_objectNameMap = gcnew System::Collections::Generic::Dictionary<Object^, String^>();
	_nameBodyMap = gcnew System::Collections::Generic::Dictionary<String^, RigidBody^>();
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

	delete _native;
	_native = NULL;
}

CollisionObject^ Serialize::WorldImporter::CreateCollisionObject(Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	TRANSFORM_CONV(startTransform);
	const char* bodyNameTemp = StringConv::ManagedToUnmanaged(bodyName);

	CollisionObject^ obj = CollisionObject::GetManaged(
		_native->baseCreateCollisionObject(TRANSFORM_USE(startTransform), shape->_native, bodyNameTemp));

	TRANSFORM_DEL(startTransform);
	StringConv::FreeUnmanagedString(bodyNameTemp);

	_allocatedRigidBodies->Add(obj);
	return obj;
}

RigidBody^ Serialize::WorldImporter::CreateRigidBody(bool isDynamic, btScalar mass, Matrix startTransform, CollisionShape^ shape, String^ bodyName)
{
	Vector3 localInertia;
	if (mass)
	{
		shape->CalculateLocalInertia(mass, localInertia);
	}
	else
	{
		localInertia = Vector3::Zero;
	}

	RigidBodyConstructionInfo^ info = gcnew RigidBodyConstructionInfo(mass, nullptr, shape, localInertia);
	RigidBody^ body = gcnew RigidBody(info);
	delete info;
	body->WorldTransform = startTransform;

	if (_world)
	{
		_world->AddRigidBody(body);
	}
        
	if (bodyName)
	{
		_objectNameMap->Add(body, bodyName);
		_nameBodyMap->Add(bodyName, body);
	}
	return body;
}

CollisionShape^ Serialize::WorldImporter::CreatePlaneShape(Vector3 planeNormal, btScalar planeConstant)
{
	VECTOR3_CONV(planeNormal);
	CollisionShape^ shape =
		gcnew StaticPlaneShape(static_cast<btStaticPlaneShape*>(_native->baseCreatePlaneShape(VECTOR3_USE(planeNormal), planeConstant)));
	VECTOR3_DEL(planeNormal);
	return shape;
}

CollisionShape^ Serialize::WorldImporter::CreateBoxShape(Vector3 halfExtents)
{
	VECTOR3_CONV(halfExtents);
	CollisionShape^ shape =
		gcnew BoxShape(static_cast<btBoxShape*>(_native->baseCreateBoxShape(VECTOR3_USE(halfExtents))));
	VECTOR3_DEL(halfExtents);
	return shape;
}

CollisionShape^ Serialize::WorldImporter::CreateSphereShape(btScalar radius)
{
	return gcnew SphereShape(static_cast<btSphereShape*>(_native->baseCreateSphereShape(radius)));
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeX(btScalar radius, btScalar height)
{
	return gcnew CapsuleShapeX(static_cast<btCapsuleShapeX*>(_native->baseCreateCapsuleShapeX(radius, height)));
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeY(btScalar radius, btScalar height)
{
	return gcnew CapsuleShape(static_cast<btCapsuleShape*>(_native->baseCreateCapsuleShapeY(radius, height)));
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeZ(btScalar radius, btScalar height)
{
	return gcnew CapsuleShapeZ(static_cast<btCapsuleShapeZ*>(_native->baseCreateCapsuleShapeZ(radius, height)));
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeX(btScalar radius, btScalar height)
{
	return gcnew CylinderShapeX(static_cast<btCylinderShapeX*>(_native->baseCreateCylinderShapeX(radius, height)));
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeY(btScalar radius, btScalar height)
{
	return gcnew CylinderShape(static_cast<btCylinderShape*>(_native->baseCreateCylinderShapeY(radius, height)));
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeZ(btScalar radius, btScalar height)
{
	return gcnew CylinderShapeZ(static_cast<btCylinderShapeZ*>(_native->baseCreateCylinderShapeZ(radius, height)));
}

CollisionShape^ Serialize::WorldImporter::CreateConeShapeX(btScalar radius, btScalar height)
{
	return gcnew ConeShapeX(static_cast<btConeShapeX*>(_native->baseCreateConeShapeX(radius, height)));
}

CollisionShape^ Serialize::WorldImporter::CreateConeShapeY(btScalar radius, btScalar height)
{
	return gcnew ConeShape(static_cast<btConeShape*>(_native->baseCreateConeShapeY(radius, height)));
}

CollisionShape^ Serialize::WorldImporter::CreateConeShapeZ(btScalar radius, btScalar height)
{
	return gcnew ConeShapeZ(static_cast<btConeShapeZ*>(_native->baseCreateConeShapeZ(radius, height)));
}

TriangleIndexVertexArray^ Serialize::WorldImporter::CreateTriangleMeshContainer()
{
	return gcnew TriangleIndexVertexArray(_native->baseCreateTriangleMeshContainer());
}

#ifndef DISABLE_BVH
BvhTriangleMeshShape^ Serialize::WorldImporter::CreateBvhTriangleMeshShape(StridingMeshInterface^ trimesh, OptimizedBvh^ bvh)
{
	return gcnew BvhTriangleMeshShape(_native->baseCreateBvhTriangleMeshShape(trimesh->_native, (btOptimizedBvh*)bvh->_native));
}
#endif

CollisionShape^ Serialize::WorldImporter::CreateConvexTriangleMeshShape(StridingMeshInterface^ trimesh)
{
	return gcnew ConvexTriangleMeshShape(static_cast<btConvexTriangleMeshShape*>(_native->baseCreateConvexTriangleMeshShape(trimesh->_native)));
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
	VECTOR3_CONV(localScaling);
	ScaledBvhTriangleMeshShape^ shape = gcnew ScaledBvhTriangleMeshShape(
		_native->baseCreateScaledTrangleMeshShape((btBvhTriangleMeshShape*)meshShape->_native, VECTOR3_USE(localScaling)));
	VECTOR3_DEL(localScaling);
	return shape;
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

	MultiSphereShape^ shape = gcnew MultiSphereShape(
		_native->baseCreateMultiSphereShape(positionsTemp, radiTemp, numSpheres));

	delete[] positionsTemp;
	delete[] radiTemp;

	return shape;
}

TriangleInfoMap^ Serialize::WorldImporter::CreateTriangleInfoMap()
{
	return gcnew TriangleInfoMap(_native->baseCreateTriangleInfoMap(), true);
}

#ifndef DISABLE_CONSTRAINTS

Point2PointConstraint^ Serialize::WorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 pivotInA, Vector3 pivotInB)
{
	VECTOR3_CONV(pivotInA);
	VECTOR3_CONV(pivotInB);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_native->baseCreatePoint2PointConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native, VECTOR3_USE(pivotInA), VECTOR3_USE(pivotInB)));

	VECTOR3_DEL(pivotInA);
	VECTOR3_DEL(pivotInB);
	return ret;
}

Point2PointConstraint^ Serialize::WorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA)
{
	VECTOR3_CONV(pivotInA);

	Point2PointConstraint^ ret = gcnew Point2PointConstraint(_native->baseCreatePoint2PointConstraint(
		*(btRigidBody*)rigidBodyA->_native, VECTOR3_USE(pivotInA)));

	VECTOR3_DEL(pivotInA);
	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame, bool useReferenceFrameA)
{
	TRANSFORM_CONV(rigidBodyAFrame);
	TRANSFORM_CONV(rigidBodyBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_native->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(rigidBodyAFrame), TRANSFORM_USE(rigidBodyBFrame), useReferenceFrameA));

	TRANSFORM_DEL(rigidBodyAFrame);
	TRANSFORM_DEL(rigidBodyBFrame);
	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	TRANSFORM_CONV(rigidBodyAFrame);
	TRANSFORM_CONV(rigidBodyBFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_native->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(rigidBodyAFrame), TRANSFORM_USE(rigidBodyBFrame)));

	TRANSFORM_DEL(rigidBodyAFrame);
	TRANSFORM_DEL(rigidBodyBFrame);
	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame, bool useReferenceFrameA)
{
	TRANSFORM_CONV(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_native->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, TRANSFORM_USE(rigidBodyAFrame), useReferenceFrameA));

	TRANSFORM_DEL(rigidBodyAFrame);
	return ret;
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	TRANSFORM_CONV(rigidBodyAFrame);

	HingeConstraint^ ret = gcnew HingeConstraint(_native->baseCreateHingeConstraint(
		*(btRigidBody*)rigidBodyA->_native, TRANSFORM_USE(rigidBodyAFrame)));

	TRANSFORM_DEL(rigidBodyAFrame);
	return ret;
}

ConeTwistConstraint^ Serialize::WorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	TRANSFORM_CONV(rigidBodyAFrame);
	TRANSFORM_CONV(rigidBodyBFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_native->baseCreateConeTwistConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(rigidBodyAFrame), TRANSFORM_USE(rigidBodyBFrame)));

	TRANSFORM_DEL(rigidBodyAFrame);
	TRANSFORM_DEL(rigidBodyBFrame);
	return ret;
}

ConeTwistConstraint^ Serialize::WorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	TRANSFORM_CONV(rigidBodyAFrame);

	ConeTwistConstraint^ ret = gcnew ConeTwistConstraint(_native->baseCreateConeTwistConstraint(
		*(btRigidBody*)rigidBodyA->_native, TRANSFORM_USE(rigidBodyAFrame)));

	TRANSFORM_DEL(rigidBodyAFrame);
	return ret;
}

Generic6DofConstraint^ Serialize::WorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	TRANSFORM_CONV(frameInA);
	TRANSFORM_CONV(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_native->baseCreateGeneric6DofConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(frameInA), TRANSFORM_USE(frameInB), useLinearReferenceFrameA));

	TRANSFORM_DEL(frameInA);
	TRANSFORM_DEL(frameInB);
	return ret;
}

Generic6DofConstraint^ Serialize::WorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB)
{
	TRANSFORM_CONV(frameInB);

	Generic6DofConstraint^ ret = gcnew Generic6DofConstraint(_native->baseCreateGeneric6DofConstraint(
		*(btRigidBody*)rigidBodyB->_native, TRANSFORM_USE(frameInB), useLinearReferenceFrameB));

	TRANSFORM_DEL(frameInB);
	return ret;
}

Generic6DofSpringConstraint^ Serialize::WorldImporter::CreateGeneric6DofSpringConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	TRANSFORM_CONV(frameInA);
	TRANSFORM_CONV(frameInB);

	Generic6DofSpringConstraint^ ret = gcnew Generic6DofSpringConstraint(_native->baseCreateGeneric6DofSpringConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(frameInA), TRANSFORM_USE(frameInB), useLinearReferenceFrameA));

	ALIGNED_FREE(frameInATemp);
	ALIGNED_FREE(frameInBTemp);
	return ret;
}

SliderConstraint^ Serialize::WorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	TRANSFORM_CONV(frameInA);
	TRANSFORM_CONV(frameInB);
	SliderConstraint^ ret = gcnew SliderConstraint(_native->baseCreateSliderConstraint(
		*(btRigidBody*)rigidBodyA->_native, *(btRigidBody*)rigidBodyB->_native,
		TRANSFORM_USE(frameInA), TRANSFORM_USE(frameInB), useLinearReferenceFrameA));
	TRANSFORM_DEL(frameInA);
	TRANSFORM_DEL(frameInB);
	return ret;
}

SliderConstraint^ Serialize::WorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA)
{
	TRANSFORM_CONV(frameInB);
	SliderConstraint^ constraint = gcnew SliderConstraint(_native->baseCreateSliderConstraint(
		*(btRigidBody*)rigidBodyB->_native, TRANSFORM_USE(frameInB), useLinearReferenceFrameA));
	TRANSFORM_DEL(frameInB);
	return constraint;
}

GearConstraint^ Serialize::WorldImporter::CreateGearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA, Vector3 axisInB, btScalar ratio)
{
	VECTOR3_CONV(axisInA);
	VECTOR3_CONV(axisInB);

	GearConstraint^ ret = gcnew GearConstraint(_native->baseCreateGearConstraint(*(btRigidBody*)rigidBodyA->_native,
		*(btRigidBody*)rigidBodyB->_native, VECTOR3_USE(axisInA), VECTOR3_USE(axisInB), ratio));
	
	VECTOR3_DEL(axisInA);
	VECTOR3_DEL(axisInB);
	return ret;
}

#endif


void Serialize::WorldImporter::DeleteAllData()
{
#ifndef DISABLE_CONSTRAINTS
	for (int i = 0; i < _allocatedConstraints->Count; i++)
	{
		if (_world)
		{
			_world->RemoveConstraint( _allocatedConstraints[i]);
		}
		delete _allocatedConstraints[i]; // Only frees the weak reference, doesn't delete the native object again
	}
#endif
	for (int i = 0; i < _allocatedRigidBodies->Count; i++)
	{
		if (_world)
		{
			_world->RemoveRigidBody(RigidBody::Upcast(_allocatedRigidBodies[i]));
		}
		delete _allocatedRigidBodies[i];
	}

	for (int i = 0; i < _allocatedCollisionShapes->Count; i++)
	{
		delete _allocatedCollisionShapes[i];
	}
	_allocatedCollisionShapes->Clear();

	_native->deleteAllData();
}

CollisionShape^ Serialize::WorldImporter::GetCollisionShapeByIndex(int index)
{
	return _allocatedCollisionShapes[index];
}

CollisionObject^ Serialize::WorldImporter::GetRigidBodyByIndex(int index)
{
	return _allocatedRigidBodies[index];
	//return CollisionObject::GetManaged(_native->getRigidBodyByIndex(index));
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ Serialize::WorldImporter::GetConstraintByIndex(int index)
{
	return _allocatedConstraints[index];
	//btTypedConstraint* constraint = _native->getConstraintByIndex(index);
	//return TypedConstraint::GetManaged(constraint);
}
#endif

#ifndef DISABLE_BVH
OptimizedBvh^ Serialize::WorldImporter::GetBvhByIndex(int index)
{
	btOptimizedBvh* bvh = _native->getBvhByIndex(index);
	return bvh ? gcnew OptimizedBvh(bvh) : nullptr;
}
#endif

TriangleInfoMap^ Serialize::WorldImporter::GetTriangleInfoMapByIndex(int index)
{
	return gcnew TriangleInfoMap(_native->getTriangleInfoMapByIndex(index), true);
}

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
	RigidBody^ ret;
	if (_nameBodyMap->TryGetValue(name, ret))
	{
		return ret;
	}

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);
	btRigidBody* body = _native->getRigidBodyByName(nameTemp);
	StringConv::FreeUnmanagedString(nameTemp);
	return (RigidBody^)CollisionObject::GetManaged(body);
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ Serialize::WorldImporter::GetConstraintByName(String^ name)
{
	btTypedConstraint* constraint;
	TypedConstraint^ ret;

	const char* nameTemp = StringConv::ManagedToUnmanaged(name);

	constraint = _native->getConstraintByName(nameTemp);
	ret = TypedConstraint::GetManaged(constraint);

	StringConv::FreeUnmanagedString(nameTemp);
	return ret;
}
#endif

String^	Serialize::WorldImporter::GetNameForObject(Object^ obj)
{
	const void* pointer = 0;

	CollisionShape^ shape = dynamic_cast<CollisionShape^>(obj);
	if (shape != nullptr)
	{
		pointer = shape->_native;
		goto returnName;
	}

	CollisionObject^ body = dynamic_cast<CollisionObject^>(obj);
	if (body != nullptr)
	{
		String^ name;
		if (_objectNameMap->TryGetValue(obj, name))
		{
			return name;
		}
		pointer = body->_native;
		goto returnName;
	}

#ifndef DISABLE_CONSTRAINTS
	TypedConstraint^ constraint = dynamic_cast<TypedConstraint^>(obj);
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
	_importer = importer;
}

btCollisionObject* Serialize::WorldImporterWrapper::createCollisionObject(const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	CollisionObject^ obj = _importer->CreateCollisionObject(Math::BtTransformToMatrix(&startTransform),
		CollisionShape::GetManaged(shape), StringConv::UnmanagedToManaged(bodyName));
	obj->_preventDelete = true;
	_importer->_allocatedRigidBodies->Add(obj);
	return static_cast<btCollisionObject*>(obj->_native);
}

btRigidBody* Serialize::WorldImporterWrapper::createRigidBody(bool isDynamic, btScalar mass, const btTransform& startTransform,
	btCollisionShape* shape, const char* bodyName)
{
	RigidBody^ body = _importer->CreateRigidBody(isDynamic, mass, Math::BtTransformToMatrix(&startTransform),
		CollisionShape::GetManaged(shape), StringConv::UnmanagedToManaged(bodyName));
	body->_preventDelete = true;
	_importer->_allocatedRigidBodies->Add(body);
	return static_cast<btRigidBody*>(body->_native);
}

btCollisionShape* Serialize::WorldImporterWrapper::createPlaneShape(const btVector3& planeNormal, btScalar planeConstant)
{
	CollisionShape^ shape = _importer->CreatePlaneShape(Math::BtVector3ToVector3(&planeNormal), planeConstant);
	shape->_preventDelete = true; // btWorldImporter will delete these shapes
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createBoxShape(const btVector3& halfExtents)
{
	CollisionShape^ shape = _importer->CreateBoxShape(Math::BtVector3ToVector3(&halfExtents));
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createSphereShape(btScalar radius)
{
	CollisionShape^ shape = _importer->CreateSphereShape(radius);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeX(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCapsuleShapeX(radius, height);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeY(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCapsuleShapeY(radius, height);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeZ(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCapsuleShapeZ(radius, height);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeX(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCylinderShapeX(radius, height);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeY(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCylinderShapeY(radius, height);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeZ(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCylinderShapeZ(radius, height);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createConeShapeX(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateConeShapeX(radius, height);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createConeShapeY(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateConeShapeY(radius, height);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createConeShapeZ(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateConeShapeZ(radius, height);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

class btTriangleIndexVertexArray* Serialize::WorldImporterWrapper::createTriangleMeshContainer()
{
	return (btTriangleIndexVertexArray*)_importer->CreateTriangleMeshContainer()->_native;
}

#ifndef DISABLE_BVH
btBvhTriangleMeshShape* Serialize::WorldImporterWrapper::createBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	CollisionShape^ shape = _importer->CreateBvhTriangleMeshShape(StridingMeshInterface::GetManaged(trimesh), gcnew OptimizedBvh(bvh));
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btBvhTriangleMeshShape*>(shape->_native);
}
#endif

btCollisionShape* Serialize::WorldImporterWrapper::createConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	CollisionShape^ shape = _importer->CreateConvexTriangleMeshShape(StridingMeshInterface::GetManaged(trimesh));
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

#ifndef DISABLE_GIMPACT
btGImpactMeshShape* Serialize::WorldImporterWrapper::createGimpactShape(btStridingMeshInterface* trimesh)
{
	GImpactMeshShape^ shape = _importer->CreateGImpactShape(StridingMeshInterface::GetManaged(trimesh));
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btGImpactMeshShape*>(shape->_native);
}
#endif

class btConvexHullShape* Serialize::WorldImporterWrapper::createConvexHullShape()
{
	ConvexHullShape^ shape = _importer->CreateConvexHullShape();
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btConvexHullShape*>(shape->_native);
}

class btCompoundShape* Serialize::WorldImporterWrapper::createCompoundShape()
{
	CompoundShape^ shape = _importer->CreateCompoundShape();
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btCompoundShape*>(shape->_native);
}

#ifndef DISABLE_BVH
class btScaledBvhTriangleMeshShape* Serialize::WorldImporterWrapper::createScaledTrangleMeshShape(btBvhTriangleMeshShape* meshShape, const btVector3& localScalingbtBvhTriangleMeshShape)
{
	ScaledBvhTriangleMeshShape^ shape =
		_importer->CreateScaledTrangleMeshShape(
			static_cast<BvhTriangleMeshShape^>(CollisionShape::GetManaged(meshShape)),
			Math::BtVector3ToVector3(&localScalingbtBvhTriangleMeshShape)
		);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btScaledBvhTriangleMeshShape*>(shape->_native);
}
#endif

class btMultiSphereShape* Serialize::WorldImporterWrapper::createMultiSphereShape(const btVector3* positions, const btScalar* radi, int numSpheres)
{
	array<Vector3>^ positionsTemp = gcnew array<Vector3>(numSpheres);
	array<btScalar>^ radiTemp = gcnew array<btScalar>(numSpheres);
	for (int i = 0; i < numSpheres; i++)
	{
		Math::BtVector3ToVector3(&positions[i], positionsTemp[i]);
		radiTemp[i] = radi[i];
	}
	MultiSphereShape^ shape = _importer->CreateMultiSphereShape(positionsTemp, radiTemp);
	shape->_preventDelete = true;
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btMultiSphereShape*>(shape->_native);
}

#ifndef DISABLE_BVH
btOptimizedBvh* Serialize::WorldImporterWrapper::createOptimizedBvh()
{
	return (btOptimizedBvh*)_importer->CreateOptimizedBvh()->_native;
}
#endif

btTriangleInfoMap* Serialize::WorldImporterWrapper::createTriangleInfoMap()
{
	return baseCreateTriangleInfoMap();
	//return _importer->CreateTriangleInfoMap()->_native;
}

#ifndef DISABLE_CONSTRAINTS

btPoint2PointConstraint* Serialize::WorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btVector3& pivotInA, const btVector3& pivotInB)
{
	Point2PointConstraint^ constraint = _importer->CreatePoint2PointConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtVector3ToVector3(&pivotInA), Math::BtVector3ToVector3(&pivotInB));
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btPoint2PointConstraint*>(constraint->_native);
}

btPoint2PointConstraint* Serialize::WorldImporterWrapper::createPoint2PointConstraint(btRigidBody& rigidBodyA, const btVector3& pivotInA)
{
	Point2PointConstraint^ constraint = _importer->CreatePoint2PointConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtVector3ToVector3(&pivotInA));
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btPoint2PointConstraint*>(constraint->_native);
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame, bool useReferenceFrameA)
{
	HingeConstraint^ constraint = _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame), useReferenceFrameA);
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btHingeConstraint*>(constraint->_native);
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA,btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	HingeConstraint^ constraint = _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame));
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btHingeConstraint*>(constraint->_native);
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame, bool useReferenceFrameA)
{
	HingeConstraint^ constraint = _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame), useReferenceFrameA);
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btHingeConstraint*>(constraint->_native);
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	HingeConstraint^ constraint = _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame));
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btHingeConstraint*>(constraint->_native);
}

btConeTwistConstraint* Serialize::WorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame)
{
	ConeTwistConstraint^ constraint = _importer->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame));
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btConeTwistConstraint*>(constraint->_native);
}

btConeTwistConstraint* Serialize::WorldImporterWrapper::createConeTwistConstraint(btRigidBody& rigidBodyA, const btTransform& rigidBodyAFrame)
{
	ConeTwistConstraint^ constraint = _importer->CreateConeTwistConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), Math::BtTransformToMatrix(&rigidBodyAFrame));
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btConeTwistConstraint*>(constraint->_native);
}

btGeneric6DofConstraint* Serialize::WorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	Generic6DofConstraint^ constraint = _importer->CreateGeneric6DofConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA);
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btGeneric6DofConstraint*>(constraint->_native);
}

btGeneric6DofConstraint* Serialize::WorldImporterWrapper::createGeneric6DofConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameB)
{
	Generic6DofConstraint^ constraint = _importer->CreateGeneric6DofConstraint((RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameB);
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btGeneric6DofConstraint*>(constraint->_native);
}

btGeneric6DofSpringConstraint* Serialize::WorldImporterWrapper::createGeneric6DofSpringConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	Generic6DofSpringConstraint^ constraint = _importer->CreateGeneric6DofSpringConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA),
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA),
		Math::BtTransformToMatrix(&frameInB),
		useLinearReferenceFrameA
	);
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btGeneric6DofSpringConstraint*>(constraint->_native);
}

btSliderConstraint* Serialize::WorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	SliderConstraint^ constraint = _importer->CreateSliderConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA), Math::BtTransformToMatrix(&frameInB), useLinearReferenceFrameA);
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btSliderConstraint*>(constraint->_native);
}

btSliderConstraint* Serialize::WorldImporterWrapper::createSliderConstraint(btRigidBody& rigidBodyB,
	const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return (btSliderConstraint*)_importer->CreateSliderConstraint(
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

btGeneric6DofSpringConstraint* Serialize::WorldImporterWrapper::baseCreateGeneric6DofSpringConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, bool useLinearReferenceFrameA)
{
	return btWorldImporter::createGeneric6DofSpringConstraint(rigidBodyA, rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
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