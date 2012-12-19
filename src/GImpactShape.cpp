#include "StdAfx.h"

#ifndef DISABLE_GIMPACT

#include "BoxCollision.h"
#include "GImpactShape.h"
#include "StridingMeshInterface.h"
#include "TriangleShapeEx.h"

#define Native static_cast<btTetrahedronShapeEx*>(_native)

TetrahedronShapeEx::TetrahedronShapeEx(btTetrahedronShapeEx* shape)
: BU_Simplex1to4(shape)
{
}

TetrahedronShapeEx::TetrahedronShapeEx()
: BU_Simplex1to4(new btTetrahedronShapeEx())
{
}

void TetrahedronShapeEx::SetVertices(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3)
{
	VECTOR3_DEF(v0);
	VECTOR3_DEF(v1);
	VECTOR3_DEF(v2);
	VECTOR3_DEF(v3);

	Native->setVertices(VECTOR3_USE(v0), VECTOR3_USE(v1), VECTOR3_USE(v2), VECTOR3_USE(v3));

	VECTOR3_DEL(v0);
	VECTOR3_DEL(v1);
	VECTOR3_DEL(v2);
	VECTOR3_DEL(v3);
}


#undef Native
#define Native static_cast<btGImpactShapeInterface*>(_native)

GImpactShapeInterface::GImpactShapeInterface(btGImpactShapeInterface* shapeInterface)
: ConcaveShape(shapeInterface)
{
}

void GImpactShapeInterface::GetBulletTetrahedron(int prim_index, [Out] TetrahedronShapeEx^% tetrahedron)
{
	btTetrahedronShapeEx* tetrahedronTemp = new btTetrahedronShapeEx;
	Native->getBulletTetrahedron(prim_index, *tetrahedronTemp);
	tetrahedron = gcnew TetrahedronShapeEx(tetrahedronTemp);
}

void GImpactShapeInterface::GetBulletTriangle(int prim_index, TriangleShapeEx^ triangle)
{
	Native->getBulletTriangle(prim_index, *(btTriangleShapeEx*)triangle->_native);
}

CollisionShape^ GImpactShapeInterface::GetChildShape(int index)
{
	return CollisionShape::GetManaged(Native->getChildShape(index));
}

#pragma managed(push, off)
btTransform* GImpactShapeInterface_GetChildTransform(btGImpactShapeInterface* shape, int index)
{
	btTransform* transform = new btTransform;
	*transform = shape->getChildTransform(index);
	return transform;
}
#pragma managed(pop)
Matrix GImpactShapeInterface::GetChildTransform(int index)
{
	btTransform* transformTemp = GImpactShapeInterface_GetChildTransform(Native, index);
	Matrix transform = Math::BtTransformToMatrix(transformTemp);
	delete transformTemp;
	return transform;
}

void GImpactShapeInterface::GetPrimitiveTriangle(int prim_index, [Out] PrimitiveTriangle^% triangle)
{
	btPrimitiveTriangle* triangleTemp = new btPrimitiveTriangle();
	Native->getPrimitiveTriangle(prim_index, *triangleTemp);
	triangle = gcnew PrimitiveTriangle(triangleTemp);
}

void GImpactShapeInterface::LockChildShapes()
{
	Native->lockChildShapes();
}

void GImpactShapeInterface::PostUpdate()
{
	Native->postUpdate();
}

void GImpactShapeInterface::ProcessAllTriangles(TriangleCallback^ callback, Vector3 aabbMin, Vector3 aabbMax)
{
	VECTOR3_DEF(aabbMin);
	VECTOR3_DEF(aabbMax);

	Native->processAllTriangles(callback->_native, VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));

	VECTOR3_DEL(aabbMin);
	VECTOR3_DEL(aabbMax);
}

void GImpactShapeInterface::ProcessAllTrianglesRay(TriangleCallback^ callback, Vector3 rayFrom, Vector3 rayTo)
{
	VECTOR3_DEF(rayFrom);
	VECTOR3_DEF(rayTo);

	Native->processAllTrianglesRay(callback->_native, VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo));

	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
}

void GImpactShapeInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, CollisionWorld::RayResultCallback^ resultCallback)
{
	VECTOR3_DEF(rayFrom);
	VECTOR3_DEF(rayTo);

	Native->rayTest(VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo), *resultCallback->_native);

	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
}

void GImpactShapeInterface::SetChildTransform(int index, Matrix transform)
{
	btTransform* transformTemp = Math::MatrixToBtTransform(transform);
	Native->setChildTransform(index, *transformTemp);
	delete transformTemp;
}

void GImpactShapeInterface::UnlockChildShapes()
{
	Native->unlockChildShapes();
}

void GImpactShapeInterface::UpdateBound()
{
	Native->updateBound();
}

#ifndef DISABLE_BVH
GImpactQuantizedBvh^ GImpactShapeInterface::BoxSet::get()
{
	return gcnew GImpactQuantizedBvh(Native->getBoxSet());
}
#endif

bool GImpactShapeInterface::ChildrenHasTransform::get()
{
	return Native->childrenHasTransform();
}

BulletSharp::GImpactShapeType GImpactShapeInterface::GImpactShapeType::get()
{
	return (BulletSharp::GImpactShapeType)Native->getGImpactShapeType();
}

bool GImpactShapeInterface::HasBoxSet::get()
{
	return Native->hasBoxSet();
}

#pragma managed(push, off)
void GImpactShapeInterface_GetLocalBox(btGImpactShapeInterface* shape, btAABB* aabb)
{
	*aabb = shape->getLocalBox();
}
#pragma managed(pop)
Aabb^ GImpactShapeInterface::LocalBox::get()
{
	btAABB* boxTemp = new btAABB();
	GImpactShapeInterface_GetLocalBox(Native, boxTemp);
	return gcnew Aabb(boxTemp);
}

bool GImpactShapeInterface::NeedsRetrieveTetrahedrons::get()
{
	return Native->needsRetrieveTetrahedrons();
}

bool GImpactShapeInterface::NeedsRetrieveTriangles::get()
{
	return Native->needsRetrieveTriangles();
}

int GImpactShapeInterface::NumChildShapes::get()
{
	return Native->getNumChildShapes();
}

#ifndef DISABLE_BVH
PrimitiveManagerBase^ GImpactShapeInterface::PrimitiveManager::get()
{
	return gcnew PrimitiveManagerBase((btPrimitiveManagerBase*)Native->getPrimitiveManager());
}
#endif


#ifndef DISABLE_BVH
GImpactCompoundShape::CompoundPrimitiveManager::CompoundPrimitiveManager(btGImpactCompoundShape::CompoundPrimitiveManager* compound)
: PrimitiveManagerBase(compound)
{
}

GImpactCompoundShape::CompoundPrimitiveManager::CompoundPrimitiveManager(CompoundPrimitiveManager^ compound)
: PrimitiveManagerBase(new btGImpactCompoundShape::CompoundPrimitiveManager(*compound->UnmanagedPointer))
{
}

GImpactCompoundShape::CompoundPrimitiveManager::CompoundPrimitiveManager(GImpactCompoundShape^ compoundShape)
: PrimitiveManagerBase(new btGImpactCompoundShape::CompoundPrimitiveManager(compoundShape->UnmanagedPointer))
{
}

GImpactCompoundShape::CompoundPrimitiveManager::CompoundPrimitiveManager()
: PrimitiveManagerBase(new btGImpactCompoundShape::CompoundPrimitiveManager())
{
}

GImpactCompoundShape^ GImpactCompoundShape::CompoundPrimitiveManager::CompoundShape::get()
{
	return gcnew GImpactCompoundShape(UnmanagedPointer->m_compoundShape);
}

btGImpactCompoundShape::CompoundPrimitiveManager* GImpactCompoundShape::CompoundPrimitiveManager::UnmanagedPointer::get()
{
	return (btGImpactCompoundShape::CompoundPrimitiveManager*)PrimitiveManagerBase::UnmanagedPointer;
}
#endif


#undef Native
#define Native (static_cast<btGImpactCompoundShape*>(_native))

GImpactCompoundShape::GImpactCompoundShape(bool childrenHasTransform)
: GImpactShapeInterface(new btGImpactCompoundShape(childrenHasTransform))
{
}

GImpactCompoundShape::GImpactCompoundShape()
: GImpactShapeInterface(new btGImpactCompoundShape())
{
}

void GImpactCompoundShape::AddChildShape(CollisionShape^ shape)
{
	Native->addChildShape(shape->_native);
}

void GImpactCompoundShape::AddChildShape(Matrix localTransform, CollisionShape^ shape)
{
	btTransform* localTransformTemp = Math::MatrixToBtTransform(localTransform);
	Native->addChildShape(*localTransformTemp, shape->_native);
	delete localTransformTemp;
}

#ifndef DISABLE_BVH
GImpactCompoundShape::CompoundPrimitiveManager^ GImpactCompoundShape::GImpactCompoundPrimitiveManager::get()
{
	return gcnew CompoundPrimitiveManager(Native->getCompoundPrimitiveManager());
}
#endif


#ifndef DISABLE_BVH
GImpactMeshShapePart::TrimeshPrimitiveManager::TrimeshPrimitiveManager(btGImpactMeshShapePart::TrimeshPrimitiveManager* manager)
: PrimitiveManagerBase(manager)
{
}

GImpactMeshShapePart::TrimeshPrimitiveManager::TrimeshPrimitiveManager()
: PrimitiveManagerBase(new btGImpactMeshShapePart::TrimeshPrimitiveManager())
{
}

GImpactMeshShapePart::TrimeshPrimitiveManager::TrimeshPrimitiveManager(TrimeshPrimitiveManager^ manager)
: PrimitiveManagerBase(new btGImpactMeshShapePart::TrimeshPrimitiveManager(*manager->UnmanagedPointer))
{
}

GImpactMeshShapePart::TrimeshPrimitiveManager::TrimeshPrimitiveManager(StridingMeshInterface^ meshInterface, int part)
: PrimitiveManagerBase(new btGImpactMeshShapePart::TrimeshPrimitiveManager(meshInterface->UnmanagedPointer, part))
{
}

void GImpactMeshShapePart::TrimeshPrimitiveManager::GetBulletTriangle(int prim_index, TriangleShapeEx^ triangle)
{
	UnmanagedPointer->get_bullet_triangle(prim_index, *(btTriangleShapeEx*)triangle->_native);
}

void GImpactMeshShapePart::TrimeshPrimitiveManager::GetIndices(int face_index, unsigned int% i0, unsigned int% i1, unsigned int% i2)
{
	unsigned int i0Temp;
	unsigned int i1Temp;
	unsigned int i2Temp;

	UnmanagedPointer->get_indices(face_index, i0Temp, i1Temp, i2Temp);

	i0 = i0Temp;
	i1 = i1Temp;
	i2 = i2Temp;
}

void GImpactMeshShapePart::TrimeshPrimitiveManager::Lock()
{
	UnmanagedPointer->lock();
}

void GImpactMeshShapePart::TrimeshPrimitiveManager::Unlock()
{
	UnmanagedPointer->unlock();
}

IntPtr GImpactMeshShapePart::TrimeshPrimitiveManager::IndexBase::get()
{
	return IntPtr((void*)UnmanagedPointer->indexbase);
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::IndexBase::set(IntPtr value)
{
	UnmanagedPointer->indexbase = (unsigned char*)value.ToPointer();
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::IndexStride::get()
{
	return UnmanagedPointer->indexstride;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::IndexStride::set(int value)
{
	UnmanagedPointer->indexstride = value;
}

PhyScalarType GImpactMeshShapePart::TrimeshPrimitiveManager::IndicesType::get()
{
	return (PhyScalarType)UnmanagedPointer->indicestype;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::IndicesType::set(PhyScalarType value)
{
	UnmanagedPointer->indicestype = (PHY_ScalarType)value;
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::LockCount::get()
{
	return UnmanagedPointer->m_lock_count;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::LockCount::set(int value)
{
	UnmanagedPointer->m_lock_count = value;
}

btScalar GImpactMeshShapePart::TrimeshPrimitiveManager::Margin::get()
{
	return UnmanagedPointer->m_margin;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::Margin::set(btScalar value)
{
	UnmanagedPointer->m_margin = value;
}

StridingMeshInterface^ GImpactMeshShapePart::TrimeshPrimitiveManager::MeshInterface::get()
{
	return StridingMeshInterface::GetManaged(UnmanagedPointer->m_meshInterface);
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::MeshInterface::set(StridingMeshInterface^ value)
{
	UnmanagedPointer->m_meshInterface = value->UnmanagedPointer;
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::NumFaces::get()
{
	return UnmanagedPointer->numfaces;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::NumFaces::set(int value)
{
	UnmanagedPointer->numfaces = value;
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::NumVerts::get()
{
	return UnmanagedPointer->numverts;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::NumVerts::set(int value)
{
	UnmanagedPointer->numverts = value;
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::Part::get()
{
	return UnmanagedPointer->m_part;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::Part::set(int value)
{
	UnmanagedPointer->m_part = value;
}

Vector3 GImpactMeshShapePart::TrimeshPrimitiveManager::Scale::get()
{
	return Math::BtVector3ToVector3(&UnmanagedPointer->m_scale);
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::Scale::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &UnmanagedPointer->m_scale);
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::Stride::get()
{
	return UnmanagedPointer->stride;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::Stride::set(int value)
{
	UnmanagedPointer->stride = value;
}

PhyScalarType GImpactMeshShapePart::TrimeshPrimitiveManager::Type::get()
{
	return (PhyScalarType)UnmanagedPointer->type;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::Type::set(PhyScalarType value)
{
	UnmanagedPointer->type = (PHY_ScalarType)value;
}

IntPtr GImpactMeshShapePart::TrimeshPrimitiveManager::VertexBase::get()
{
	return IntPtr((void*)UnmanagedPointer->vertexbase);
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::VertexBase::set(IntPtr value)
{
	UnmanagedPointer->vertexbase = (unsigned char*)value.ToPointer();
}

btGImpactMeshShapePart::TrimeshPrimitiveManager* GImpactMeshShapePart::TrimeshPrimitiveManager::UnmanagedPointer::get()
{
	return (btGImpactMeshShapePart::TrimeshPrimitiveManager*)PrimitiveManagerBase::UnmanagedPointer;
}
#endif


#undef Native
#define Native static_cast<btGImpactMeshShapePart*>(_native)

GImpactMeshShapePart::GImpactMeshShapePart(btGImpactMeshShapePart* shape)
: GImpactShapeInterface(shape)
{
}

GImpactMeshShapePart::GImpactMeshShapePart()
: GImpactShapeInterface(new btGImpactMeshShapePart())
{
}

GImpactMeshShapePart::GImpactMeshShapePart(StridingMeshInterface^ meshInterface, int part)
: GImpactShapeInterface(new btGImpactMeshShapePart(meshInterface->UnmanagedPointer, part))
{
}

void GImpactMeshShapePart::GetVertex(unsigned int vertexIndex, [Out] Vector3% vertex)
{
	btVector3* vertexTemp = new btVector3;
	Native->getVertex(vertexIndex, *vertexTemp);
	Math::BtVector3ToVector3(vertexTemp, vertex);
	delete vertexTemp;
}

int GImpactMeshShapePart::Part::get()
{
	return Native->getPart();
}

int GImpactMeshShapePart::VertexCount::get()
{
	return Native->getVertexCount();
}

#ifndef DISABLE_BVH
GImpactMeshShapePart::TrimeshPrimitiveManager^ GImpactMeshShapePart::GImpactTrimeshPrimitiveManager::get()
{
	return gcnew TrimeshPrimitiveManager(UnmanagedPointer->getTrimeshPrimitiveManager());
}
#endif


#undef Native
#define Native static_cast<btGImpactMeshShape*>(_native)

GImpactMeshShape::GImpactMeshShape(btGImpactMeshShape* shape)
: GImpactShapeInterface(shape)
{
}

GImpactMeshShape::GImpactMeshShape(StridingMeshInterface^ meshInterface)
: GImpactShapeInterface(new btGImpactMeshShape(meshInterface->UnmanagedPointer))
{
}

GImpactMeshShapePart^ GImpactMeshShape::GetMeshPart(int index)
{
	return gcnew GImpactMeshShapePart(Native->getMeshPart(index));
}

StridingMeshInterface^ GImpactMeshShape::MeshInterface::get()
{
	return gcnew StridingMeshInterface(Native->getMeshInterface());
}

int GImpactMeshShape::MeshPartCount::get()
{
	return Native->getMeshPartCount();
}

#endif
