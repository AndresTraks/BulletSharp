#include "StdAfx.h"

#ifndef DISABLE_GIMPACT

#include "BoxCollision.h"
#include "GImpactShape.h"
#include "StridingMeshInterface.h"
#include "TriangleShapeEx.h"

#define Native static_cast<btTetrahedronShapeEx*>(_native)

TetrahedronShapeEx::TetrahedronShapeEx(btTetrahedronShapeEx* native)
	: BuSimplex1To4(native)
{
}

TetrahedronShapeEx::TetrahedronShapeEx()
	: BuSimplex1To4(new btTetrahedronShapeEx())
{
}

void TetrahedronShapeEx::SetVertices(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3)
{
	VECTOR3_CONV(v0);
	VECTOR3_CONV(v1);
	VECTOR3_CONV(v2);
	VECTOR3_CONV(v3);
	Native->setVertices(VECTOR3_USE(v0), VECTOR3_USE(v1), VECTOR3_USE(v2), VECTOR3_USE(v3));
	VECTOR3_DEL(v0);
	VECTOR3_DEL(v1);
	VECTOR3_DEL(v2);
	VECTOR3_DEL(v3);
}


#undef Native
#define Native static_cast<btGImpactShapeInterface*>(_native)

GImpactShapeInterface::GImpactShapeInterface(btGImpactShapeInterface* native)
	: ConcaveShape(native)
{
}

void GImpactShapeInterface::GetAabbRef(Matrix% t, Vector3% aabbMin, Vector3% aabbMax)
{
	// Override required because inlined code doesn't work in C++/CLI (btAABB not aligned)
	btAABB* transformedBox = ALIGNED_NEW(btAABB) (Native->getLocalBox());
	TRANSFORM_CONV(t);
	transformedBox->appy_transform(TRANSFORM_USE(t));
	Math::BtVector3ToVector3(&transformedBox->m_min, aabbMin);
	Math::BtVector3ToVector3(&transformedBox->m_max, aabbMax);
	ALIGNED_FREE(transformedBox);
}

void GImpactShapeInterface::GetAabb(Matrix t, Vector3% aabbMin, Vector3% aabbMax)
{
	// Override required because inlined code doesn't work in C++/CLI (btAABB doesn't get aligned)
	btAABB* transformedBox = ALIGNED_NEW(btAABB) (Native->getLocalBox());
	TRANSFORM_CONV(t);
	transformedBox->appy_transform(TRANSFORM_USE(t));
	Math::BtVector3ToVector3(&transformedBox->m_min, aabbMin);
	Math::BtVector3ToVector3(&transformedBox->m_max, aabbMax);
	ALIGNED_FREE(transformedBox);
}

void GImpactShapeInterface::GetBulletTetrahedron(int primIndex, TetrahedronShapeEx^ tetrahedron)
{
	Native->getBulletTetrahedron(primIndex, *(btTetrahedronShapeEx*)tetrahedron->_native);
}

void GImpactShapeInterface::GetBulletTriangle(int primIndex, TriangleShapeEx^ triangle)
{
	Native->getBulletTriangle(primIndex, *(btTriangleShapeEx*)triangle->_native);
}

void GImpactShapeInterface::GetChildAabb(int childIndex, Matrix t, Vector3% aabbMin,
	Vector3% aabbMax)
{
	TRANSFORM_CONV(t);
	btVector3* aabbMinTemp = ALIGNED_NEW(btVector3);
	btVector3* aabbMaxTemp = ALIGNED_NEW(btVector3);
	Native->getChildAabb(childIndex, TRANSFORM_USE(t), VECTOR3_USE(aabbMin), VECTOR3_USE(aabbMax));
	TRANSFORM_DEL(t);
	Math::BtVector3ToVector3(aabbMinTemp, aabbMin);
	Math::BtVector3ToVector3(aabbMaxTemp, aabbMax);
	ALIGNED_FREE(aabbMinTemp);
	ALIGNED_FREE(aabbMaxTemp);
}

CollisionShape^ GImpactShapeInterface::GetChildShape(int index)
{
	return CollisionShape::GetManaged(Native->getChildShape(index));
}

#pragma managed(push, off)
btTransform* GImpactShapeInterface_GetChildTransform(btGImpactShapeInterface* shape, int index)
{
	btTransform* transform = ALIGNED_NEW(btTransform);
	*transform = shape->getChildTransform(index);
	return transform;
}
#pragma managed(pop)
Matrix GImpactShapeInterface::GetChildTransform(int index)
{
	btTransform* transformTemp = GImpactShapeInterface_GetChildTransform(Native, index);
	Matrix transform = Math::BtTransformToMatrix(transformTemp);
	ALIGNED_FREE(transformTemp);
	return transform;
}

void GImpactShapeInterface::GetPrimitiveTriangle(int index, PrimitiveTriangle^ triangle)
{
	Native->getPrimitiveTriangle(index, *triangle->_native);
}

void GImpactShapeInterface::LockChildShapes()
{
	Native->lockChildShapes();
}

void GImpactShapeInterface::PostUpdate()
{
	Native->postUpdate();
}

void GImpactShapeInterface::ProcessAllTrianglesRay(TriangleCallback^ callback, Vector3 rayFrom,
	Vector3 rayTo)
{
	VECTOR3_CONV(rayFrom);
	VECTOR3_CONV(rayTo);
	Native->processAllTrianglesRay(callback->_native, VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo));
	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
}

void GImpactShapeInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, RayResultCallback^ resultCallback)
{
	VECTOR3_CONV(rayFrom);
	VECTOR3_CONV(rayTo);
	Native->rayTest(VECTOR3_USE(rayFrom), VECTOR3_USE(rayTo), *resultCallback->_native);
	VECTOR3_DEL(rayFrom);
	VECTOR3_DEL(rayTo);
}

void GImpactShapeInterface::SetChildTransform(int index, Matrix transform)
{
	TRANSFORM_CONV(transform);
	Native->setChildTransform(index, TRANSFORM_USE(transform));
	TRANSFORM_DEL(transform);
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
	return gcnew GImpactQuantizedBvh((btGImpactBoxSet*)Native->getBoxSet());
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

Aabb^ GImpactShapeInterface::LocalBox::get()
{
	return gcnew Aabb((btAABB*)&Native->getLocalBox(), false);
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

#undef Native
#define Native static_cast<btGImpactCompoundShape::CompoundPrimitiveManager*>(_native)

GImpactCompoundShape::CompoundPrimitiveManager::CompoundPrimitiveManager(btGImpactCompoundShape::CompoundPrimitiveManager* native)
	: PrimitiveManagerBase(native)
{
}

GImpactCompoundShape::CompoundPrimitiveManager::CompoundPrimitiveManager(CompoundPrimitiveManager^ compound)
	: PrimitiveManagerBase(new btGImpactCompoundShape::CompoundPrimitiveManager(*(btGImpactCompoundShape::CompoundPrimitiveManager*)compound->_native))
{
}

GImpactCompoundShape::CompoundPrimitiveManager::CompoundPrimitiveManager(GImpactCompoundShape^ compoundShape)
	: PrimitiveManagerBase(new btGImpactCompoundShape::CompoundPrimitiveManager((btGImpactCompoundShape*)compoundShape->_native))
{
}

GImpactCompoundShape::CompoundPrimitiveManager::CompoundPrimitiveManager()
	: PrimitiveManagerBase(new btGImpactCompoundShape::CompoundPrimitiveManager())
{
}

GImpactCompoundShape^ GImpactCompoundShape::CompoundPrimitiveManager::CompoundShape::get()
{
	return (GImpactCompoundShape^)CollisionShape::GetManaged(Native->m_compoundShape);
}
void GImpactCompoundShape::CompoundPrimitiveManager::CompoundShape::set(GImpactCompoundShape^ value)
{
	Native->m_compoundShape = (btGImpactCompoundShape*)value->_native;
}

#endif


#undef Native
#define Native static_cast<btGImpactCompoundShape*>(_native)

GImpactCompoundShape::GImpactCompoundShape(btGImpactCompoundShape* native)
	: GImpactShapeInterface(native)
{
}

GImpactCompoundShape::GImpactCompoundShape(bool childrenHasTransform)
	: GImpactShapeInterface(new btGImpactCompoundShape(childrenHasTransform))
{
}

GImpactCompoundShape::GImpactCompoundShape()
	: GImpactShapeInterface(new btGImpactCompoundShape())
{
}

void GImpactCompoundShape::AddChildShape(Matrix localTransform, CollisionShape^ shape)
{
	TRANSFORM_CONV(localTransform);
	Native->addChildShape(TRANSFORM_USE(localTransform), shape->_native);
	TRANSFORM_DEL(localTransform);
}

void GImpactCompoundShape::AddChildShape(CollisionShape^ shape)
{
	Native->addChildShape(shape->_native);
}

#ifndef DISABLE_BVH
GImpactCompoundShape::CompoundPrimitiveManager^ GImpactCompoundShape::GImpactCompoundPrimitiveManager::get()
{
	if (_primitiveManagerBase == nullptr) {
		_primitiveManagerBase = gcnew CompoundPrimitiveManager(Native->getCompoundPrimitiveManager());
	}
	return (CompoundPrimitiveManager^)_primitiveManagerBase;
}

PrimitiveManagerBase^ GImpactCompoundShape::PrimitiveManager::get()
{
	return GImpactCompoundPrimitiveManager;
}
#endif


#ifndef DISABLE_BVH

#undef Native
#define Native static_cast<btGImpactMeshShapePart::TrimeshPrimitiveManager*>(_native)

GImpactMeshShapePart::TrimeshPrimitiveManager::TrimeshPrimitiveManager(btGImpactMeshShapePart::TrimeshPrimitiveManager* native)
	: PrimitiveManagerBase(native)
{
}

GImpactMeshShapePart::TrimeshPrimitiveManager::TrimeshPrimitiveManager(StridingMeshInterface^ meshInterface,
	int part)
	: PrimitiveManagerBase(new btGImpactMeshShapePart::TrimeshPrimitiveManager(meshInterface->_native,
		part))
{
	_meshInterface = meshInterface;
}

GImpactMeshShapePart::TrimeshPrimitiveManager::TrimeshPrimitiveManager(TrimeshPrimitiveManager^ manager)
	: PrimitiveManagerBase(new btGImpactMeshShapePart::TrimeshPrimitiveManager(*(btGImpactMeshShapePart::TrimeshPrimitiveManager*)manager->_native))
{
}

GImpactMeshShapePart::TrimeshPrimitiveManager::TrimeshPrimitiveManager()
	: PrimitiveManagerBase(new btGImpactMeshShapePart::TrimeshPrimitiveManager())
{
}

void GImpactMeshShapePart::TrimeshPrimitiveManager::GetBulletTriangle(int primIndex,
	TriangleShapeEx^ triangle)
{
	Native->get_bullet_triangle(primIndex, *(btTriangleShapeEx*)triangle->_native);
}

void GImpactMeshShapePart::TrimeshPrimitiveManager::GetIndices(int faceIndex, unsigned int% i0,
	unsigned int% i1, unsigned int% i2)
{
	unsigned int i0Temp;
	unsigned int i1Temp;
	unsigned int i2Temp;
	Native->get_indices(faceIndex, i0Temp, i1Temp, i2Temp);
	i0 = i0Temp;
	i1 = i1Temp;
	i2 = i2Temp;
}

void GImpactMeshShapePart::TrimeshPrimitiveManager::GetVertex(unsigned int vertexIndex,
	[Out] Vector3% vertex)
{
	btVector3* vertexTemp = ALIGNED_NEW(btVector3);
	Native->get_vertex(vertexIndex, *vertexTemp);
	Math::BtVector3ToVector3(vertexTemp, vertex);
	ALIGNED_FREE(vertexTemp);
}

void GImpactMeshShapePart::TrimeshPrimitiveManager::Lock()
{
	Native->lock();
}

void GImpactMeshShapePart::TrimeshPrimitiveManager::Unlock()
{
	Native->unlock();
}

IntPtr GImpactMeshShapePart::TrimeshPrimitiveManager::IndexBase::get()
{
	return IntPtr((void*)Native->indexbase);
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::IndexBase::set(IntPtr value)
{
	Native->indexbase = (unsigned char*)value.ToPointer();
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::IndexStride::get()
{
	return Native->indexstride;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::IndexStride::set(int value)
{
	Native->indexstride = value;
}

PhyScalarType GImpactMeshShapePart::TrimeshPrimitiveManager::IndicesType::get()
{
	return (PhyScalarType)Native->indicestype;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::IndicesType::set(PhyScalarType value)
{
	Native->indicestype = (PHY_ScalarType)value;
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::LockCount::get()
{
	return Native->m_lock_count;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::LockCount::set(int value)
{
	Native->m_lock_count = value;
}

btScalar GImpactMeshShapePart::TrimeshPrimitiveManager::Margin::get()
{
	return Native->m_margin;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::Margin::set(btScalar value)
{
	Native->m_margin = value;
}

StridingMeshInterface^ GImpactMeshShapePart::TrimeshPrimitiveManager::MeshInterface::get()
{
	return _meshInterface;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::MeshInterface::set(StridingMeshInterface^ value)
{
	Native->m_meshInterface = value->_native;
	_meshInterface = value;
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::NumFaces::get()
{
	return Native->numfaces;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::NumFaces::set(int value)
{
	Native->numfaces = value;
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::NumVerts::get()
{
	return Native->numverts;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::NumVerts::set(int value)
{
	Native->numverts = value;
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::Part::get()
{
	return Native->m_part;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::Part::set(int value)
{
	Native->m_part = value;
}

Vector3 GImpactMeshShapePart::TrimeshPrimitiveManager::Scale::get()
{
	return Math::BtVector3ToVector3(&Native->m_scale);
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::Scale::set(Vector3 value)
{
	Math::Vector3ToBtVector3(value, &Native->m_scale);
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::Stride::get()
{
	return Native->stride;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::Stride::set(int value)
{
	Native->stride = value;
}

PhyScalarType GImpactMeshShapePart::TrimeshPrimitiveManager::Type::get()
{
	return (PhyScalarType)Native->type;
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::Type::set(PhyScalarType value)
{
	Native->type = (PHY_ScalarType)value;
}

IntPtr GImpactMeshShapePart::TrimeshPrimitiveManager::VertexBase::get()
{
	return IntPtr((void*)Native->vertexbase);
}
void GImpactMeshShapePart::TrimeshPrimitiveManager::VertexBase::set(IntPtr value)
{
	Native->vertexbase = (unsigned char*)value.ToPointer();
}

int GImpactMeshShapePart::TrimeshPrimitiveManager::VertexCount::get()
{
	return Native->get_vertex_count();
}

#endif


#undef Native
#define Native static_cast<btGImpactMeshShapePart*>(_native)

GImpactMeshShapePart::GImpactMeshShapePart(btGImpactMeshShapePart* native)
	: GImpactShapeInterface(native)
{
}

GImpactMeshShapePart::GImpactMeshShapePart()
	: GImpactShapeInterface(new btGImpactMeshShapePart())
{
}

GImpactMeshShapePart::GImpactMeshShapePart(StridingMeshInterface^ meshInterface,
	int part)
	: GImpactShapeInterface(new btGImpactMeshShapePart(meshInterface->_native, part))
{
}

void GImpactMeshShapePart::GetVertex(int vertexIndex, [Out] Vector3% vertex)
{
	btVector3* vertexTemp = ALIGNED_NEW(btVector3);
	Native->getVertex(vertexIndex, *vertexTemp);
	Math::BtVector3ToVector3(vertexTemp, vertex);
	ALIGNED_FREE(vertexTemp);
}

#ifndef DISABLE_BVH
GImpactMeshShapePart::TrimeshPrimitiveManager^ GImpactMeshShapePart::GImpactTrimeshPrimitiveManager::get()
{
	if (_primitiveManagerBase == nullptr) {
		_primitiveManagerBase = gcnew TrimeshPrimitiveManager(Native->getTrimeshPrimitiveManager());
	}
	return (TrimeshPrimitiveManager^)_primitiveManagerBase;
}
#endif

int GImpactMeshShapePart::Part::get()
{
	return Native->getPart();
}

#ifndef DISABLE_BVH
PrimitiveManagerBase^ GImpactMeshShapePart::PrimitiveManager::get()
{
	return GImpactTrimeshPrimitiveManager;
}
#endif

int GImpactMeshShapePart::VertexCount::get()
{
	return Native->getVertexCount();
}


#undef Native
#define Native static_cast<btGImpactMeshShape*>(_native)

GImpactMeshShape::GImpactMeshShape(btGImpactMeshShape* native)
	: GImpactShapeInterface(native)
{
}

GImpactMeshShape::GImpactMeshShape(StridingMeshInterface^ meshInterface)
	: GImpactShapeInterface(new btGImpactMeshShape(meshInterface->_native))
{
	_meshInterface = meshInterface;
}

GImpactMeshShapePart^ GImpactMeshShape::GetMeshPart(int index)
{
	if (!_meshParts)
	{
		_meshParts = gcnew array<GImpactMeshShapePart^>(MeshPartCount);
	}
	GImpactMeshShapePart^ meshPart = _meshParts[index];
	if (!meshPart)
	{
		meshPart = (GImpactMeshShapePart^)CollisionShape::GetManaged(Native->getMeshPart(index));
		_meshParts[index] = meshPart;
	}
	return meshPart;
}

StridingMeshInterface^ GImpactMeshShape::MeshInterface::get()
{
	if (_meshInterface == nullptr)
	{
		_meshInterface = StridingMeshInterface::GetManaged(Native->getMeshInterface());
	}
	return _meshInterface;
}

int GImpactMeshShape::MeshPartCount::get()
{
	return Native->getMeshPartCount();
}

#ifndef DISABLE_BVH
PrimitiveManagerBase^ GImpactMeshShape::PrimitiveManager::get()
{
	return nullptr;
}
#endif

#endif
