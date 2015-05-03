#include "StdAfx.h"

#if 0
#ifndef DISABLE_SERIALIZE

#include "BoxShape.h"
#include "WorldImporter.h"
#include "BvhTriangleMeshShape.h"
#include "CapsuleShape.h"
#include "CollisionObject.h"
#include "CompoundShape.h"
#include "ConeShape.h"
#include "ConvexHullShape.h"
#include "ConvexTriangleMeshShape.h"
#include "CylinderShape.h"
#include "DynamicsWorld.h"
#include "MultiSphereShape.h"
#include "OptimizedBvh.h"
#include "RigidBody.h"
#include "SphereShape.h"
#include "ScaledBvhTriangleMeshShape.h"
#include "StaticPlaneShape.h"
#include "StridingMeshInterface.h"
#include "StringConv.h"
#include "TriangleIndexVertexArray.h"
#include "TriangleInfoMap.h"
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
	_allocatedBvhs = gcnew List<OptimizedBvh^>();
	_allocatedBvhsMap = gcnew Dictionary<IntPtr, OptimizedBvh^>();
	_allocatedRigidBodies = gcnew List<CollisionObject^>();
	_allocatedCollisionShapes = gcnew List<CollisionShape^>();
#ifndef DISABLE_CONSTRAINTS
	_allocatedConstraints = gcnew List<TypedConstraint^>();
#endif
	_allocatedTriangleIndexArrays = gcnew List<TriangleIndexVertexArray^>();
	_allocatedTriangleIndexArraysMap = gcnew Dictionary<IntPtr, TriangleIndexVertexArray^>();
	_allocatedTriangleInfoMaps = gcnew List<TriangleInfoMap^>();
	_objectNameMap = gcnew Dictionary<Object^, String^>();
	_nameBodyMap = gcnew Dictionary<String^, RigidBody^>();
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
		localInertia = Vector3_Zero;
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
	return gcnew StaticPlaneShape(planeNormal, planeConstant);
}

CollisionShape^ Serialize::WorldImporter::CreateBoxShape(Vector3 halfExtents)
{
	return gcnew BoxShape(Vector_X(halfExtents), Vector_Y(halfExtents), Vector_Z(halfExtents));
}

CollisionShape^ Serialize::WorldImporter::CreateSphereShape(btScalar radius)
{
	return gcnew SphereShape(radius);
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeX(btScalar radius, btScalar height)
{
	return gcnew CapsuleShapeX(radius, height);
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeY(btScalar radius, btScalar height)
{
	return gcnew CapsuleShape(radius, height);
}

CollisionShape^ Serialize::WorldImporter::CreateCapsuleShapeZ(btScalar radius, btScalar height)
{
	return gcnew CapsuleShapeZ(radius, height);
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeX(btScalar radius, btScalar height)
{
	return gcnew CylinderShapeX(height, radius, radius);
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeY(btScalar radius, btScalar height)
{
	return gcnew CylinderShape(radius, height, radius);
}

CollisionShape^ Serialize::WorldImporter::CreateCylinderShapeZ(btScalar radius, btScalar height)
{
	return gcnew CylinderShapeZ(radius, radius, height);
}

CollisionShape^ Serialize::WorldImporter::CreateConeShapeX(btScalar radius, btScalar height)
{
	return gcnew ConeShapeX(radius, height);
}

CollisionShape^ Serialize::WorldImporter::CreateConeShapeY(btScalar radius, btScalar height)
{
	return gcnew ConeShape(radius, height);
}

CollisionShape^ Serialize::WorldImporter::CreateConeShapeZ(btScalar radius, btScalar height)
{
	return gcnew ConeShapeZ(radius, height);
}

TriangleIndexVertexArray^ Serialize::WorldImporter::CreateTriangleMeshContainer()
{
	return gcnew TriangleIndexVertexArray();
}

BvhTriangleMeshShape^ Serialize::WorldImporter::CreateBvhTriangleMeshShape(StridingMeshInterface^ trimesh, OptimizedBvh^ bvh)
{
	if (bvh)
	{
		BvhTriangleMeshShape^ shape = gcnew BvhTriangleMeshShape(trimesh, bvh->IsQuantized, false);
		shape->OptimizedBvh = bvh;
		return shape;
	}
	return gcnew BvhTriangleMeshShape(trimesh, true);
}

CollisionShape^ Serialize::WorldImporter::CreateConvexTriangleMeshShape(StridingMeshInterface^ trimesh)
{
	return gcnew ConvexTriangleMeshShape(trimesh);
}

#ifndef DISABLE_GIMPACT
GImpactMeshShape^ Serialize::WorldImporter::CreateGImpactShape(StridingMeshInterface^ trimesh)
{
	return gcnew GImpactMeshShape(trimesh);
}
#endif

ConvexHullShape^ Serialize::WorldImporter::CreateConvexHullShape()
{
	return gcnew ConvexHullShape();
}

CompoundShape^ Serialize::WorldImporter::CreateCompoundShape()
{
	return gcnew CompoundShape();
}

ScaledBvhTriangleMeshShape^ Serialize::WorldImporter::CreateScaledTrangleMeshShape(BvhTriangleMeshShape^ meshShape, Vector3 localScaling)
{
	return gcnew ScaledBvhTriangleMeshShape(meshShape, localScaling);
}

OptimizedBvh^ Serialize::WorldImporter::CreateOptimizedBvh()
{
	return gcnew OptimizedBvh();
}

MultiSphereShape^ Serialize::WorldImporter::CreateMultiSphereShape(array<Vector3>^ positions, array<btScalar>^ radi)
{
	return gcnew MultiSphereShape(positions, radi);
}

TriangleInfoMap^ Serialize::WorldImporter::CreateTriangleInfoMap()
{
	return gcnew TriangleInfoMap();
}

#ifndef DISABLE_CONSTRAINTS

Point2PointConstraint^ Serialize::WorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Vector3 pivotInA, Vector3 pivotInB)
{
	return gcnew Point2PointConstraint(rigidBodyA, rigidBodyB, pivotInA, pivotInB);
}

Point2PointConstraint^ Serialize::WorldImporter::CreatePoint2PointConstraint(RigidBody^ rigidBodyA, Vector3 pivotInA)
{
	return gcnew Point2PointConstraint(rigidBodyA, pivotInA);
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Matrix rigidBodyAFrame, Matrix rigidBodyBFrame, bool useReferenceFrameA)
{
	return gcnew HingeConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame, useReferenceFrameA);
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB,
	Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	return gcnew HingeConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame);
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame, bool useReferenceFrameA)
{
	return gcnew HingeConstraint(rigidBodyA, rigidBodyAFrame, useReferenceFrameA);
}

HingeConstraint^ Serialize::WorldImporter::CreateHingeConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	return gcnew HingeConstraint(rigidBodyA, rigidBodyAFrame);
}

ConeTwistConstraint^ Serialize::WorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix rigidBodyAFrame, Matrix rigidBodyBFrame)
{
	return gcnew ConeTwistConstraint(rigidBodyA, rigidBodyB, rigidBodyAFrame, rigidBodyBFrame);
}

ConeTwistConstraint^ Serialize::WorldImporter::CreateConeTwistConstraint(RigidBody^ rigidBodyA, Matrix rigidBodyAFrame)
{
	return gcnew ConeTwistConstraint(rigidBodyA, rigidBodyAFrame);
}

Generic6DofConstraint^ Serialize::WorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	return gcnew Generic6DofConstraint(rigidBodyA, rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
}

Generic6DofConstraint^ Serialize::WorldImporter::CreateGeneric6DofConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameB)
{
	return gcnew Generic6DofConstraint(rigidBodyB, frameInB, useLinearReferenceFrameB);
}

Generic6DofSpringConstraint^ Serialize::WorldImporter::CreateGeneric6DofSpringConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	return gcnew Generic6DofSpringConstraint(rigidBodyA, rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
}

Generic6DofSpring2Constraint^ Serialize::WorldImporter::CreateGeneric6DofSpring2Constraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, BulletSharp::RotateOrder rotateOrder)
{
	return gcnew Generic6DofSpring2Constraint(rigidBodyA, rigidBodyB, frameInA, frameInB, rotateOrder);
}

SliderConstraint^ Serialize::WorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Matrix frameInA, Matrix frameInB, bool useLinearReferenceFrameA)
{
	return gcnew SliderConstraint(rigidBodyA, rigidBodyB, frameInA, frameInB, useLinearReferenceFrameA);
}

SliderConstraint^ Serialize::WorldImporter::CreateSliderConstraint(RigidBody^ rigidBodyB, Matrix frameInB, bool useLinearReferenceFrameA)
{
	return gcnew SliderConstraint(rigidBodyB, frameInB, useLinearReferenceFrameA);
}

GearConstraint^ Serialize::WorldImporter::CreateGearConstraint(RigidBody^ rigidBodyA, RigidBody^ rigidBodyB, Vector3 axisInA, Vector3 axisInB, btScalar ratio)
{
	return gcnew GearConstraint(rigidBodyA, rigidBodyB, axisInA, axisInB, ratio);
}

#endif


void Serialize::WorldImporter::DeleteAllData()
{
	int i;

#ifndef DISABLE_CONSTRAINTS
	for (i = 0; i < _allocatedConstraints->Count; i++)
	{
		if (_world)
		{
			_world->RemoveConstraint( _allocatedConstraints[i]);
		}
		delete _allocatedConstraints[i]; // Only frees the weak reference, doesn't delete the native object again
	}
	_allocatedConstraints->Clear();
#endif

	for (i = 0; i < _allocatedRigidBodies->Count; i++)
	{
		if (_world)
		{
			_world->RemoveRigidBody(RigidBody::Upcast(_allocatedRigidBodies[i]));
		}
		delete _allocatedRigidBodies[i];
	}
	_allocatedRigidBodies->Clear();

	for (i = 0; i < _allocatedCollisionShapes->Count; i++)
	{
		delete _allocatedCollisionShapes[i];
	}
	_allocatedCollisionShapes->Clear();

	for (i = 0; i < _allocatedBvhs->Count; i++)
	{
		delete _allocatedBvhs[i];
	}
	_allocatedBvhs->Clear();

	for (i = 0; i < _allocatedBvhs->Count; i++)
	{
		delete _allocatedBvhs[i];
	}
	_allocatedBvhs->Clear();

	for (i = 0; i < _allocatedTriangleInfoMaps->Count; i++)
	{
		delete _allocatedTriangleInfoMaps[i];
	}
	_allocatedTriangleInfoMaps->Clear();

	for (i = 0; i < _allocatedTriangleIndexArrays->Count; i++)
	{
		delete _allocatedTriangleIndexArrays[i];
	}
	_allocatedTriangleIndexArrays->Clear();

	_native->deleteAllData();
}

CollisionShape^ Serialize::WorldImporter::GetCollisionShapeByIndex(int index)
{
	return _allocatedCollisionShapes[index];
}

CollisionObject^ Serialize::WorldImporter::GetRigidBodyByIndex(int index)
{
	return _allocatedRigidBodies[index];
}

#ifndef DISABLE_CONSTRAINTS
TypedConstraint^ Serialize::WorldImporter::GetConstraintByIndex(int index)
{
	return _allocatedConstraints[index];
}
#endif

OptimizedBvh^ Serialize::WorldImporter::GetBvhByIndex(int index)
{
	return _allocatedBvhs[index];
}

TriangleInfoMap^ Serialize::WorldImporter::GetTriangleInfoMapByIndex(int index)
{
	return _allocatedTriangleInfoMaps[index];
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
	return _allocatedBvhs->Count;
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
	return _allocatedTriangleInfoMaps->Count;
}

int Serialize::WorldImporter::VerboseMode::get()
{
	return _native->getVerboseMode();
}
void Serialize::WorldImporter::VerboseMode::set(int value)
{
	_native->setVerboseMode(value);
}


Serialize::WorldImporterWrapper::WorldImporterWrapper(btDynamicsWorld* world, BulletWorldImporter^ importer)
: btBulletWorldImporter(world)
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
	shape->_preventDelete = true; // btBulletWorldImporter will delete these shapes
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createBoxShape(const btVector3& halfExtents)
{
	CollisionShape^ shape = _importer->CreateBoxShape(Math::BtVector3ToVector3(&halfExtents));
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createSphereShape(btScalar radius)
{
	CollisionShape^ shape = _importer->CreateSphereShape(radius);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeX(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCapsuleShapeX(radius, height);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeY(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCapsuleShapeY(radius, height);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCapsuleShapeZ(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCapsuleShapeZ(radius, height);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeX(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCylinderShapeX(radius, height);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeY(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCylinderShapeY(radius, height);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createCylinderShapeZ(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateCylinderShapeZ(radius, height);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createConeShapeX(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateConeShapeX(radius, height);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createConeShapeY(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateConeShapeY(radius, height);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

btCollisionShape* Serialize::WorldImporterWrapper::createConeShapeZ(btScalar radius, btScalar height)
{
	CollisionShape^ shape = _importer->CreateConeShapeZ(radius, height);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

class btTriangleIndexVertexArray* Serialize::WorldImporterWrapper::createTriangleMeshContainer()
{
	TriangleIndexVertexArray^ container = _importer->CreateTriangleMeshContainer();
	_importer->_allocatedTriangleIndexArrays->Add(container);
	_importer->_allocatedTriangleIndexArraysMap->Add(IntPtr(container->_native), container);
	return static_cast<btTriangleIndexVertexArray*>(container->_native);
}

btBvhTriangleMeshShape* Serialize::WorldImporterWrapper::createBvhTriangleMeshShape(btStridingMeshInterface* trimesh, btOptimizedBvh* bvh)
{
	StridingMeshInterface^ trimeshManaged = _importer->_allocatedTriangleIndexArraysMap[IntPtr(trimesh)];
	OptimizedBvh^ bvhManaged = _importer->_allocatedBvhsMap[IntPtr(bvh)];
	CollisionShape^ shape = _importer->CreateBvhTriangleMeshShape(trimeshManaged, bvhManaged);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btBvhTriangleMeshShape*>(shape->_native);
}

btCollisionShape* Serialize::WorldImporterWrapper::createConvexTriangleMeshShape(btStridingMeshInterface* trimesh)
{
	StridingMeshInterface^ trimeshManaged = _importer->_allocatedTriangleIndexArraysMap[IntPtr(trimesh)];
	CollisionShape^ shape = _importer->CreateConvexTriangleMeshShape(trimeshManaged);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return shape->_native;
}

#ifndef DISABLE_GIMPACT
btGImpactMeshShape* Serialize::WorldImporterWrapper::createGimpactShape(btStridingMeshInterface* trimesh)
{
	StridingMeshInterface^ trimeshManaged = _importer->_allocatedTriangleIndexArraysMap[IntPtr(trimesh)];
	GImpactMeshShape^ shape = _importer->CreateGImpactShape(trimeshManaged);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btGImpactMeshShape*>(shape->_native);
}
#endif

class btConvexHullShape* Serialize::WorldImporterWrapper::createConvexHullShape()
{
	ConvexHullShape^ shape = _importer->CreateConvexHullShape();
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btConvexHullShape*>(shape->_native);
}

class btCompoundShape* Serialize::WorldImporterWrapper::createCompoundShape()
{
	CompoundShape^ shape = _importer->CreateCompoundShape();
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btCompoundShape*>(shape->_native);
}

class btScaledBvhTriangleMeshShape* Serialize::WorldImporterWrapper::createScaledTrangleMeshShape(btBvhTriangleMeshShape* meshShape, const btVector3& localScalingbtBvhTriangleMeshShape)
{
	ScaledBvhTriangleMeshShape^ shape =
		_importer->CreateScaledTrangleMeshShape(
			static_cast<BvhTriangleMeshShape^>(CollisionShape::GetManaged(meshShape)),
			Math::BtVector3ToVector3(&localScalingbtBvhTriangleMeshShape)
		);
	shape->_preventDelete = true;
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btScaledBvhTriangleMeshShape*>(shape->_native);
}

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
	btCollisionShape* shapePtr = shape->_native;
	m_allocatedCollisionShapes.push_back(shapePtr);
	_importer->_allocatedCollisionShapes->Add(shape);
	return static_cast<btMultiSphereShape*>(shape->_native);
}

btOptimizedBvh* Serialize::WorldImporterWrapper::createOptimizedBvh()
{
	OptimizedBvh^ bvh = _importer->CreateOptimizedBvh();
	_importer->_allocatedBvhs->Add(bvh);
	_importer->_allocatedBvhsMap->Add(IntPtr(bvh->_native), bvh);
	return static_cast<btOptimizedBvh*>(bvh->_native);
}

btTriangleInfoMap* Serialize::WorldImporterWrapper::createTriangleInfoMap()
{
	TriangleInfoMap^ triangleInfoMap = _importer->CreateTriangleInfoMap();
	_importer->_allocatedTriangleInfoMaps->Add(triangleInfoMap);
	return triangleInfoMap->_native;
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

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& rigidBodyAFrame, const btTransform& rigidBodyBFrame, bool useReferenceFrameA)
{
	HingeConstraint^ constraint = _importer->CreateHingeConstraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA), (RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&rigidBodyAFrame), Math::BtTransformToMatrix(&rigidBodyBFrame), useReferenceFrameA);
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btHingeConstraint*>(constraint->_native);
}

btHingeConstraint* Serialize::WorldImporterWrapper::createHingeConstraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
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

btGeneric6DofSpring2Constraint* Serialize::WorldImporterWrapper::createGeneric6DofSpring2Constraint(btRigidBody& rigidBodyA, btRigidBody& rigidBodyB,
	const btTransform& frameInA, const btTransform& frameInB, int rotateOrder)
{
	Generic6DofSpring2Constraint^ constraint = _importer->CreateGeneric6DofSpring2Constraint(
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyA),
		(RigidBody^)CollisionObject::GetManaged(&rigidBodyB),
		Math::BtTransformToMatrix(&frameInA),
		Math::BtTransformToMatrix(&frameInB),
		(RotateOrder)rotateOrder
	);
	constraint->_preventDelete = true;
	_importer->_allocatedConstraints->Add(constraint);
	return static_cast<btGeneric6DofSpring2Constraint*>(constraint->_native);
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

#endif

#endif