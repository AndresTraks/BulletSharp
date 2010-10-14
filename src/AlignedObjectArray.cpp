#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "BroadphaseProxy.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "CompoundShape.h"
#include "PersistentManifold.h"
#ifndef DISABLE_DBVT
#include "Dbvt.h"
#endif

#ifndef DISABLE_SOFTBODY
using namespace BulletSharp::SoftBody;
#endif

AlignedObjectArray::AlignedObjectArray(void* alignedObjectArray)
{
	_alignedObjectArray = alignedObjectArray;
}

AlignedObjectArray::!AlignedObjectArray()
{
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_alignedObjectArray = NULL;

	OnDisposed( this, nullptr );
}

AlignedObjectArray::~AlignedObjectArray()
{
	this->!AlignedObjectArray();
}

bool AlignedObjectArray::IsDisposed::get()
{
	return (_alignedObjectArray == NULL);
}

void* AlignedObjectArray::UnmanagedPointer::get()
{
	return _alignedObjectArray;
}
void AlignedObjectArray::UnmanagedPointer::set(void* value)
{
	_alignedObjectArray = value;
}


BroadphasePairArray::BroadphasePairArray(btBroadphasePairArray* stkNnArray)
: AlignedObjectArray(stkNnArray)
{
}

BroadphasePairArray::BroadphasePairArray()
: AlignedObjectArray(new btBroadphasePairArray)
{
}

void BroadphasePairArray::Clear()
{
	UnmanagedPointer->clear();
}

void BroadphasePairArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void BroadphasePairArray::PushBack(BroadphasePair^ pair)
{
	UnmanagedPointer->push_back(*pair->UnmanagedPointer);
}

void BroadphasePairArray::Remove(BroadphasePair^ pair)
{
	UnmanagedPointer->remove(*pair->UnmanagedPointer);
}

int BroadphasePairArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BroadphasePairArray::Size::get()
{
	return UnmanagedPointer->size();
}

void BroadphasePairArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BroadphasePair^ BroadphasePairArray::default::get(int index)
{
	return gcnew BroadphasePair(&(*UnmanagedPointer)[index]);
}
#pragma managed(push, off)
void BroadphasePairArray_SetDefault(btBroadphasePairArray* pairArray,
	int index, btBroadphasePair* pair)
{
	(*pairArray)[index] = *pair;
}
#pragma managed(pop)
void BroadphasePairArray::default::set(int index, BroadphasePair^ value)
{
	BroadphasePairArray_SetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btBroadphasePairArray* BroadphasePairArray::UnmanagedPointer::get()
{
	return (btBroadphasePairArray*)AlignedObjectArray::UnmanagedPointer;
}


#ifndef DISABLE_SOFTBODY
BulletSharp::SoftBody::ClusterArray::ClusterArray(btSoftBody::tClusterArray* clusterArray)
: AlignedObjectArray(clusterArray)
{
}

BulletSharp::SoftBody::ClusterArray::ClusterArray()
: AlignedObjectArray(new btSoftBody::tClusterArray())
{
}

IEnumerator^ ClusterArray::GetEnumerator()
{
	return gcnew ClusterEnumerator(this);
}

void BulletSharp::SoftBody::ClusterArray::Clear()
{
	UnmanagedPointer->clear();
}

void BulletSharp::SoftBody::ClusterArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void BulletSharp::SoftBody::ClusterArray::PushBack(Cluster^ cluster)
{
	UnmanagedPointer->push_back(cluster->UnmanagedPointer);
}

void BulletSharp::SoftBody::ClusterArray::Remove(Cluster^ cluster)
{
	UnmanagedPointer->remove(cluster->UnmanagedPointer);
}

int BulletSharp::SoftBody::ClusterArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BulletSharp::SoftBody::ClusterArray::Size::get()
{
	return UnmanagedPointer->size();
}

void BulletSharp::SoftBody::ClusterArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Cluster^ BulletSharp::SoftBody::ClusterArray::default::get(int index)
{
	return gcnew Cluster((*UnmanagedPointer)[index]);
}
void BulletSharp::SoftBody::ClusterArray::default::set(int index, Cluster^ value)
{
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btSoftBody::tClusterArray* BulletSharp::SoftBody::ClusterArray::UnmanagedPointer::get()
{
	return (btSoftBody::tClusterArray*)AlignedObjectArray::UnmanagedPointer;
}


ClusterEnumerator::ClusterEnumerator(ClusterArray^ clusterArray)
{
	_clusterArray = clusterArray;
	i=-1;
}

Object^ ClusterEnumerator::Current::get()
{
	return gcnew Cluster((*_clusterArray->UnmanagedPointer)[i]);
}

bool ClusterEnumerator::MoveNext()
{
	i++;
	return (i < _clusterArray->UnmanagedPointer->size());
}

void ClusterEnumerator::Reset()
{
	i=-1;
}
#endif


CollisionShapeArray::CollisionShapeArray()
: AlignedObjectArray(new btAlignedObjectArray<btCollisionShape*>())
{
}

void CollisionShapeArray::Clear()
{
	UnmanagedPointer->clear();
}

void CollisionShapeArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void CollisionShapeArray::PushBack(CollisionShape^ collisionShape)
{
	UnmanagedPointer->push_back(collisionShape->UnmanagedPointer);
}

void CollisionShapeArray::Remove(CollisionShape^ collisionShape)
{
	UnmanagedPointer->remove(collisionShape->UnmanagedPointer);
}

void CollisionShapeArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int CollisionShapeArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int CollisionShapeArray::Size::get()
{
	return UnmanagedPointer->size();
}

CollisionShape^ CollisionShapeArray::default::get(int index)
{
	btCollisionShape* shape = (*UnmanagedPointer)[index];
	if (shape == nullptr)
		return nullptr;
	return gcnew CollisionShape(shape);
}
void CollisionShapeArray::default::set(int index, CollisionShape^ value)
{
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btAlignedObjectArray<btCollisionShape*>* CollisionShapeArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btCollisionShape*>*)AlignedObjectArray::UnmanagedPointer;
}


CollisionObjectArray::CollisionObjectArray(btCollisionObjectArray* objectArray)
: AlignedObjectArray(objectArray)
{
}

IEnumerator^ CollisionObjectArray::GetEnumerator()
{
	return gcnew CollisionObjectEnumerator(this);
}

CollisionObjectArray::CollisionObjectArray()
: AlignedObjectArray(new btCollisionObjectArray())
{
}

void CollisionObjectArray::Clear()
{
	UnmanagedPointer->clear();
}

void CollisionObjectArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void CollisionObjectArray::PushBack(CollisionObject^ collisionObject)
{
	UnmanagedPointer->push_back(collisionObject->UnmanagedPointer);
}

void CollisionObjectArray::Remove(CollisionObject^ collisionObject)
{
	UnmanagedPointer->remove(collisionObject->UnmanagedPointer);
}

void CollisionObjectArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int CollisionObjectArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int CollisionObjectArray::Size::get()
{
	return UnmanagedPointer->size();
}

CollisionObject^ CollisionObjectArray::default::get(int index)
{
	btCollisionObject* obj = (*UnmanagedPointer)[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew CollisionObject(obj);
}
void CollisionObjectArray::default::set(int index, CollisionObject^ value)
{
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btCollisionObjectArray* CollisionObjectArray::UnmanagedPointer::get()
{
	return (btCollisionObjectArray*)AlignedObjectArray::UnmanagedPointer;
}


CollisionObjectEnumerator::CollisionObjectEnumerator(CollisionObjectArray^ objArray)
{
	_objArray = objArray;
	i=-1;
}

CollisionObject^ CollisionObjectEnumerator::Current::get()
{
	return gcnew CollisionObject((*_objArray->UnmanagedPointer)[i]);
}

Object^ CollisionObjectEnumerator::CurrentBase::get()
{
	return Current;
}

bool CollisionObjectEnumerator::MoveNext()
{
	i++;
	return (i < _objArray->UnmanagedPointer->size());
}

void CollisionObjectEnumerator::Reset()
{
	i=-1;
}


CompoundShapeChildArray::CompoundShapeChildArray(btAlignedObjectArray<btCompoundShapeChild>* compundShapeChildArray)
: AlignedObjectArray(compundShapeChildArray)
{
}

CompoundShapeChildArray::CompoundShapeChildArray()
: AlignedObjectArray(new btAlignedObjectArray<btCompoundShapeChild>)
{
}

IEnumerator^ CompoundShapeChildArray::GetEnumerator()
{
	return gcnew CompoundShapeChildEnumerator(this);
}

void CompoundShapeChildArray::Clear()
{
	UnmanagedPointer->clear();
}

void CompoundShapeChildArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void CompoundShapeChildArray::PushBack(CompoundShapeChild^ compoundShapeChild)
{
	UnmanagedPointer->push_back(*compoundShapeChild->UnmanagedPointer);
}

void CompoundShapeChildArray::Remove(CompoundShapeChild^ compoundShapeChild)
{
	UnmanagedPointer->remove(*compoundShapeChild->UnmanagedPointer);
}

int CompoundShapeChildArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int CompoundShapeChildArray::Size::get()
{
	return UnmanagedPointer->size();
}

void CompoundShapeChildArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

CompoundShapeChild^ CompoundShapeChildArray::default::get(int index)
{
	return gcnew CompoundShapeChild(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void CompoundShapeChildArray_GetDefault(btAlignedObjectArray<btCompoundShapeChild>* shapeArray,
	int index, btCompoundShapeChild* node)
{
	(*shapeArray)[index] = *node;
}
#pragma managed(pop)
void CompoundShapeChildArray::default::set(int index, CompoundShapeChild^ value)
{
	CompoundShapeChildArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btAlignedObjectArray<btCompoundShapeChild>* CompoundShapeChildArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btCompoundShapeChild>*)AlignedObjectArray::UnmanagedPointer;
}


CompoundShapeChildEnumerator::CompoundShapeChildEnumerator(CompoundShapeChildArray^ shapeArray)
{
	shapeArray = shapeArray;
	i=-1;
}

Object^ CompoundShapeChildEnumerator::Current::get()
{
	return gcnew CompoundShapeChild(&(*_shapeArray->UnmanagedPointer)[i]);
}

bool CompoundShapeChildEnumerator::MoveNext()
{
	i++;
	return (i < _shapeArray->UnmanagedPointer->size());
}

void CompoundShapeChildEnumerator::Reset()
{
	i=-1;
}


#ifndef DISABLE_DBVT
DbvtNodeArray::DbvtNodeArray(btAlignedObjectArray<const btDbvtNode*>* nodeArray)
: AlignedObjectArray(nodeArray)
{
}

DbvtNodeArray::DbvtNodeArray()
: AlignedObjectArray(new btAlignedObjectArray<btDbvtNode>)
{
}

void DbvtNodeArray::Clear()
{
	UnmanagedPointer->clear();
}

void DbvtNodeArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void DbvtNodeArray::PushBack(DbvtNode^ node)
{
	UnmanagedPointer->push_back(node->UnmanagedPointer);
}

void DbvtNodeArray::Remove(DbvtNode^ node)
{
	UnmanagedPointer->remove(node->UnmanagedPointer);
}

int DbvtNodeArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int DbvtNodeArray::Size::get()
{
	return UnmanagedPointer->size();
}

void DbvtNodeArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

DbvtNode^ DbvtNodeArray::default::get(int index)
{
	btDbvtNode* obj = (btDbvtNode*)(*UnmanagedPointer)[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew DbvtNode(obj);
}
void DbvtNodeArray::default::set(int index, DbvtNode^ value)
{
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btAlignedObjectArray<const btDbvtNode*>* DbvtNodeArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<const btDbvtNode*>*)AlignedObjectArray::UnmanagedPointer;
}


StkNnArray::StkNnArray(btAlignedObjectArray<btDbvt::sStkNN>* stkNnArray)
: AlignedObjectArray(stkNnArray)
{
}

StkNnArray::StkNnArray()
: AlignedObjectArray(new btAlignedObjectArray<btDbvt::sStkNN>)
{
}

void StkNnArray::Clear()
{
	UnmanagedPointer->clear();
}

void StkNnArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void StkNnArray::PushBack(Dbvt::StkNn^ stkNn)
{
	UnmanagedPointer->push_back(*stkNn->UnmanagedPointer);
}

void StkNnArray::Remove(Dbvt::StkNn^ stkNn)
{
	// FIXME
	//UnmanagedPointer->remove(*stkNn->UnmanagedPointer);
}

int StkNnArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int StkNnArray::Size::get()
{
	return UnmanagedPointer->size();
}

void StkNnArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

#pragma managed(push, off)
void StkNnArray_GetDefault(btAlignedObjectArray<btDbvt::sStkNN>* stkNpsArray,
	int index, btDbvt::sStkNN* obj)
{
	*obj = (*stkNpsArray)[index];
}
#pragma managed(pop)

Dbvt::StkNn^ StkNnArray::default::get(int index)
{
	btDbvt::sStkNN* obj = new btDbvt::sStkNN;
	StkNnArray_GetDefault(UnmanagedPointer, index, obj);
	return gcnew Dbvt::StkNn(obj);
}

void StkNnArray::default::set(int index, Dbvt::StkNn^ value)
{
	(*UnmanagedPointer)[index] = *value->UnmanagedPointer;
}

btAlignedObjectArray<btDbvt::sStkNN>* StkNnArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btDbvt::sStkNN>*)AlignedObjectArray::UnmanagedPointer;
}


StkNpsArray::StkNpsArray(btAlignedObjectArray<btDbvt::sStkNPS>* stkNpsArray)
: AlignedObjectArray(stkNpsArray)
{
}

StkNpsArray::StkNpsArray()
: AlignedObjectArray(new btAlignedObjectArray<btDbvt::sStkNPS>)
{
}

void StkNpsArray::Clear()
{
	UnmanagedPointer->clear();
}

void StkNpsArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void StkNpsArray::PushBack(Dbvt::StkNps^ stkNps)
{
	UnmanagedPointer->push_back(*stkNps->UnmanagedPointer);
}

void StkNpsArray::Remove(Dbvt::StkNps^ stkNps)
{
	// FIXME
	//UnmanagedPointer->remove(*stkNps->UnmanagedPointer);
}

int StkNpsArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int StkNpsArray::Size::get()
{
	return UnmanagedPointer->size();
}

void StkNpsArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

#pragma managed(push, off)
void StkNpsArray_GetDefault(btAlignedObjectArray<btDbvt::sStkNPS>* stkNpsArray,
	int index, btDbvt::sStkNPS* obj)
{
	*obj = (*stkNpsArray)[index];
}
#pragma managed(pop)

Dbvt::StkNps^ StkNpsArray::default::get(int index)
{
	btDbvt::sStkNPS* obj = new btDbvt::sStkNPS;
	StkNpsArray_GetDefault(UnmanagedPointer, index, obj);
	return gcnew Dbvt::StkNps(obj);
}

void StkNpsArray::default::set(int index, Dbvt::StkNps^ value)
{
	(*UnmanagedPointer)[index] = *value->UnmanagedPointer;
}

btAlignedObjectArray<btDbvt::sStkNPS>* StkNpsArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btDbvt::sStkNPS>*)AlignedObjectArray::UnmanagedPointer;
}
#endif


#ifndef DISABLE_SOFTBODY
FaceArray::FaceArray(btAlignedObjectArray<btSoftBody::Face>* faceArray)
: AlignedObjectArray(faceArray)
{
}

FaceArray::FaceArray()
: AlignedObjectArray(new btAlignedObjectArray<btSoftBody::Face>)
{
}

void FaceArray::Clear()
{
	UnmanagedPointer->clear();
}

void FaceArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void FaceArray::PushBack(Face^ face)
{
	UnmanagedPointer->push_back(*face->UnmanagedPointer);
}

void FaceArray::Remove(Face^ face)
{
	// FIXME
	//UnmanagedPointer->remove(*face->UnmanagedPointer);
}

int FaceArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int FaceArray::Size::get()
{
	return UnmanagedPointer->size();
}

void FaceArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

Face^ FaceArray::default::get(int index)
{
	return gcnew Face(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void FaceArray_GetDefault(btAlignedObjectArray<btSoftBody::Face>* faceArray,
	int index, btSoftBody::Face* node)
{
	(*faceArray)[index] = *node;
}
#pragma managed(pop)
void FaceArray::default::set(int index, Face^ value)
{
	FaceArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btAlignedObjectArray<btSoftBody::Face>* FaceArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btSoftBody::Face>*)AlignedObjectArray::UnmanagedPointer;
}
#endif


IntArray::IntArray(btAlignedObjectArray<int>* intArray)
: AlignedObjectArray(intArray)
{
}

IntArray::IntArray()
: AlignedObjectArray(new btAlignedObjectArray<int>)
{
}

void IntArray::Clear()
{
	UnmanagedPointer->clear();
}

void IntArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void IntArray::PushBack(int intValue)
{
	UnmanagedPointer->push_back(intValue);
}

void IntArray::Remove(int intValue)
{
	UnmanagedPointer->remove(intValue);
}

int IntArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int IntArray::Size::get()
{
	return UnmanagedPointer->size();
}

void IntArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int IntArray::default::get(int index)
{
	return (*UnmanagedPointer)[index];
}
void IntArray::default::set(int index, int value)
{
	(*UnmanagedPointer)[index] = value;
}

btAlignedObjectArray<int>* IntArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<int>*)AlignedObjectArray::UnmanagedPointer;
}


ManifoldArray::ManifoldArray(btManifoldArray* manifoldArray)
: AlignedObjectArray(manifoldArray)
{
}

ManifoldArray::ManifoldArray()
: AlignedObjectArray(new btCollisionObjectArray())
{
}

void ManifoldArray::Clear()
{
	UnmanagedPointer->clear();
}

void ManifoldArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void ManifoldArray::PushBack(PersistentManifold^ manifold)
{
	UnmanagedPointer->push_back(manifold->UnmanagedPointer);
}

void ManifoldArray::Remove(PersistentManifold^ manifold)
{
	UnmanagedPointer->remove(manifold->UnmanagedPointer);
}

int ManifoldArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int ManifoldArray::Size::get()
{
	return UnmanagedPointer->size();
}

void ManifoldArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

PersistentManifold^ ManifoldArray::default::get(int index)
{
	btPersistentManifold* obj = (*UnmanagedPointer)[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew PersistentManifold(obj);
}
void ManifoldArray::default::set(int index, PersistentManifold^ value)
{
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btManifoldArray* ManifoldArray::UnmanagedPointer::get()
{
	return (btManifoldArray*)AlignedObjectArray::UnmanagedPointer;
}


#ifndef DISABLE_SOFTBODY
LinkArray::LinkArray(btSoftBody::tLinkArray* linkArray)
: AlignedObjectArray(linkArray)
{
}

LinkArray::LinkArray()
: AlignedObjectArray(new btSoftBody::tLinkArray())
{
}

IEnumerator^ LinkArray::GetEnumerator()
{
	return gcnew LinkEnumerator(this);
}

void LinkArray::Clear()
{
	UnmanagedPointer->clear();
}

void LinkArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void LinkArray::PushBack(BulletSharp::SoftBody::Link^ link)
{
	UnmanagedPointer->push_back(*link->UnmanagedPointer);
}

void LinkArray::Remove(BulletSharp::SoftBody::Link^ link)
{
	// FIXME
	//UnmanagedPointer->remove((*link->UnmanagedPointer));
}

int LinkArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int LinkArray::Size::get()
{
	return UnmanagedPointer->size();
}

void LinkArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Link^ LinkArray::default::get(int index)
{
	return gcnew Link(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void LinkArray_GetDefault(btSoftBody::tLinkArray* linkArray,
	int index, btSoftBody::Link* link)
{
	(*linkArray)[index] = *link;
}
#pragma managed(pop)
void LinkArray::default::set(int index, BulletSharp::SoftBody::Link^ value)
{
	LinkArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btSoftBody::tLinkArray* LinkArray::UnmanagedPointer::get()
{
	return (btSoftBody::tLinkArray*)AlignedObjectArray::UnmanagedPointer;
}


LinkEnumerator::LinkEnumerator(LinkArray^ linkArray)
{
	_linkArray = linkArray;
	i=-1;
}

Object^ LinkEnumerator::Current::get()
{
	return gcnew Link(&(*_linkArray->UnmanagedPointer)[i]);
}

bool LinkEnumerator::MoveNext()
{
	i++;
	return (i < _linkArray->UnmanagedPointer->size());
}

void LinkEnumerator::Reset()
{
	i=-1;
}


MaterialArray::MaterialArray(btSoftBody::tMaterialArray* materialArray)
: AlignedObjectArray(materialArray)
{
}

MaterialArray::MaterialArray()
: AlignedObjectArray(new btSoftBody::tMaterialArray())
{
}

void MaterialArray::Clear()
{
	UnmanagedPointer->clear();
}

void MaterialArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void MaterialArray::PushBack(BulletSharp::SoftBody::Material^ material)
{
	UnmanagedPointer->push_back(material->UnmanagedPointer);
}

void MaterialArray::Remove(BulletSharp::SoftBody::Material^ material)
{
	UnmanagedPointer->remove(&(*material->UnmanagedPointer));
}

int MaterialArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int MaterialArray::Size::get()
{
	return UnmanagedPointer->size();
}

void MaterialArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Material^ MaterialArray::default::get(int index)
{
	return gcnew Material((*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void MaterialArray_GetDefault(btSoftBody::tMaterialArray* materialArray,
	int index, btSoftBody::Material* material)
{
	(*materialArray)[index] = material;
}
#pragma managed(pop)
void MaterialArray::default::set(int index, BulletSharp::SoftBody::Material^ value)
{
	MaterialArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btSoftBody::tMaterialArray* MaterialArray::UnmanagedPointer::get()
{
	return (btSoftBody::tMaterialArray*)AlignedObjectArray::UnmanagedPointer;
}


BulletSharp::SoftBody::NodeArray::NodeArray(btSoftBody::tNodeArray* nodeArray)
: AlignedObjectArray(nodeArray)
{
}

BulletSharp::SoftBody::NodeArray::NodeArray()
: AlignedObjectArray(new btSoftBody::tNodeArray())
{
}

void BulletSharp::SoftBody::NodeArray::Clear()
{
	UnmanagedPointer->clear();
}

void BulletSharp::SoftBody::NodeArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void BulletSharp::SoftBody::NodeArray::PushBack(Node^ node)
{
	UnmanagedPointer->push_back(*node->UnmanagedPointer);
}

void BulletSharp::SoftBody::NodeArray::Remove(Node^ node)
{
	// FIXME
	//UnmanagedPointer->remove(*node->UnmanagedPointer);
}

int BulletSharp::SoftBody::NodeArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BulletSharp::SoftBody::NodeArray::Size::get()
{
	return UnmanagedPointer->size();
}

void BulletSharp::SoftBody::NodeArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Node^ BulletSharp::SoftBody::NodeArray::default::get(int index)
{
	return gcnew Node(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void NodeArray_GetDefault(btSoftBody::tNodeArray* nodeArray, int index, btSoftBody::Node* node)
{
	(*nodeArray)[index] = *node;
}
#pragma managed(pop)
void BulletSharp::SoftBody::NodeArray::default::set(int index, Node^ value)
{
	NodeArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btSoftBody::tNodeArray* BulletSharp::SoftBody::NodeArray::UnmanagedPointer::get()
{
	return (btSoftBody::tNodeArray*)AlignedObjectArray::UnmanagedPointer;
}


BulletSharp::SoftBody::NodePtrArray::NodePtrArray(btAlignedObjectArray<btSoftBody::Node*>* nodeArray)
: AlignedObjectArray(nodeArray)
{
}

BulletSharp::SoftBody::NodePtrArray::NodePtrArray()
: AlignedObjectArray(new btAlignedObjectArray<btSoftBody::Node*>())
{
}

void BulletSharp::SoftBody::NodePtrArray::Clear()
{
	UnmanagedPointer->clear();
}

void BulletSharp::SoftBody::NodePtrArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void BulletSharp::SoftBody::NodePtrArray::PushBack(Node^ node)
{
	UnmanagedPointer->push_back(node->UnmanagedPointer);
}

void BulletSharp::SoftBody::NodePtrArray::Remove(Node^ node)
{
	UnmanagedPointer->remove(node->UnmanagedPointer);
}

int BulletSharp::SoftBody::NodePtrArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BulletSharp::SoftBody::NodePtrArray::Size::get()
{
	return UnmanagedPointer->size();
}

void BulletSharp::SoftBody::NodePtrArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Node^ BulletSharp::SoftBody::NodePtrArray::default::get(int index)
{
	return gcnew Node((*UnmanagedPointer)[index]);
}
void BulletSharp::SoftBody::NodePtrArray::default::set(int index, Node^ value)
{
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btAlignedObjectArray<btSoftBody::Node*>* BulletSharp::SoftBody::NodePtrArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btSoftBody::Node*>*)AlignedObjectArray::UnmanagedPointer;
}


BulletSharp::SoftBody::NoteArray::NoteArray(btSoftBody::tNoteArray* noteArray)
: AlignedObjectArray(noteArray)
{
}

BulletSharp::SoftBody::NoteArray::NoteArray()
: AlignedObjectArray(new btSoftBody::tNoteArray())
{
}

void BulletSharp::SoftBody::NoteArray::Clear()
{
	UnmanagedPointer->clear();
}

void BulletSharp::SoftBody::NoteArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void BulletSharp::SoftBody::NoteArray::PushBack(Note^ note)
{
	UnmanagedPointer->push_back(*note->UnmanagedPointer);
}

void BulletSharp::SoftBody::NoteArray::Remove(Note^ note)
{
	// FIXME
	//UnmanagedPointer->remove(*note->UnmanagedPointer);
}

int BulletSharp::SoftBody::NoteArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BulletSharp::SoftBody::NoteArray::Size::get()
{
	return UnmanagedPointer->size();
}

void BulletSharp::SoftBody::NoteArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Note^ BulletSharp::SoftBody::NoteArray::default::get(int index)
{
	return gcnew Note(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void NoteArray_GetDefault(btSoftBody::tNoteArray* noteArray, int index, btSoftBody::Note* note)
{
	(*noteArray)[index] = *note;
}
#pragma managed(pop)
void BulletSharp::SoftBody::NoteArray::default::set(int index, Note^ value)
{
	NoteArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btSoftBody::tNoteArray* BulletSharp::SoftBody::NoteArray::UnmanagedPointer::get()
{
	return (btSoftBody::tNoteArray*)AlignedObjectArray::UnmanagedPointer;
}
#endif


ScalarArray::ScalarArray(btAlignedObjectArray<btScalar>* btScalarArray)
: AlignedObjectArray(btScalarArray)
{
}

ScalarArray::ScalarArray()
: AlignedObjectArray(new btAlignedObjectArray<btScalar>)
{
}

void ScalarArray::Clear()
{
	UnmanagedPointer->clear();
}

void ScalarArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void ScalarArray::PushBack(btScalar intValue)
{
	UnmanagedPointer->push_back(intValue);
}

void ScalarArray::Remove(btScalar intValue)
{
	UnmanagedPointer->remove(intValue);
}

int ScalarArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int ScalarArray::Size::get()
{
	return UnmanagedPointer->size();
}

void ScalarArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

btScalar ScalarArray::default::get(int index)
{
	return (*UnmanagedPointer)[index];
}
void ScalarArray::default::set(int index, btScalar value)
{
	(*UnmanagedPointer)[index] = value;
}

btAlignedObjectArray<btScalar>* ScalarArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btScalar>*)AlignedObjectArray::UnmanagedPointer;
}


#ifndef DISABLE_SOFTBODY
BulletSharp::SoftBody::SoftBodyArray::SoftBodyArray(btSoftBody::tSoftBodyArray* softBodyArray)
: AlignedObjectArray(softBodyArray)
{
}

BulletSharp::SoftBody::SoftBodyArray::SoftBodyArray()
: AlignedObjectArray(new btSoftBody::tSoftBodyArray())
{
}

void BulletSharp::SoftBody::SoftBodyArray::Clear()
{
	UnmanagedPointer->clear();
}

void BulletSharp::SoftBody::SoftBodyArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void BulletSharp::SoftBody::SoftBodyArray::PushBack(SoftBody^ softBody)
{
	UnmanagedPointer->push_back(softBody->UnmanagedPointer);
}

void BulletSharp::SoftBody::SoftBodyArray::Remove(SoftBody^ softBody)
{
	UnmanagedPointer->remove(softBody->UnmanagedPointer);
}

int BulletSharp::SoftBody::SoftBodyArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BulletSharp::SoftBody::SoftBodyArray::Size::get()
{
	return UnmanagedPointer->size();
}

void BulletSharp::SoftBody::SoftBodyArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::SoftBody^ BulletSharp::SoftBody::SoftBodyArray::default::get(int index)
{
	return gcnew SoftBody((*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void SoftBodyArray_GetDefault(btSoftBody::tSoftBodyArray* softBodyArray, int index, btSoftBody* softBody)
{
	(*softBodyArray)[index] = softBody;
}
#pragma managed(pop)
void BulletSharp::SoftBody::SoftBodyArray::default::set(int index, SoftBody^ value)
{
	SoftBodyArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btSoftBody::tSoftBodyArray* BulletSharp::SoftBody::SoftBodyArray::UnmanagedPointer::get()
{
	return (btSoftBody::tSoftBodyArray*)AlignedObjectArray::UnmanagedPointer;
}
#endif


Vector3Array::Vector3Array(btAlignedObjectArray<btVector3>* vector3Array)
: AlignedObjectArray(vector3Array)
{
}

Vector3Array::Vector3Array()
: AlignedObjectArray(new btAlignedObjectArray<btVector3>)
{
}

void Vector3Array::Clear()
{
	UnmanagedPointer->clear();
}

void Vector3Array::PopBack()
{
	UnmanagedPointer->pop_back();
}

void Vector3Array::PushBack(Vector3 vector3Value)
{
	btVector3* tempVector3Value = Math::Vector3ToBtVector3(vector3Value);
	UnmanagedPointer->push_back(*tempVector3Value);
	delete tempVector3Value;
}

void Vector3Array::Remove(Vector3 vector3Value)
{
	btVector3* tempVector3Value = Math::Vector3ToBtVector3(vector3Value);
	UnmanagedPointer->remove(*tempVector3Value);
	delete tempVector3Value;
}

int Vector3Array::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int Vector3Array::Size::get()
{
	return UnmanagedPointer->size();
}

void Vector3Array::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

Vector3 Vector3Array::default::get(int index)
{
	return Math::BtVector3ToVector3(&(*UnmanagedPointer)[index]);
}
void Vector3Array::default::set(int index, Vector3 value)
{
	Math::Vector3ToBtVector3(value, &(*UnmanagedPointer)[index]);
}

btAlignedObjectArray<btVector3>* Vector3Array::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btVector3>*)AlignedObjectArray::UnmanagedPointer;
}

#ifndef DISABLE_VEHICLE
WheelInfoArray::WheelInfoArray(btAlignedObjectArray<btWheelInfo>* wheelInfoArray)
: AlignedObjectArray(wheelInfoArray)
{
}

WheelInfoArray::WheelInfoArray()
: AlignedObjectArray(new btAlignedObjectArray<btWheelInfo>)
{
}

void WheelInfoArray::Clear()
{
	UnmanagedPointer->clear();
}

void WheelInfoArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void WheelInfoArray::PushBack(WheelInfo^ wheelInfo)
{
	UnmanagedPointer->push_back(*wheelInfo->UnmanagedPointer);
}

void WheelInfoArray::Remove(WheelInfo^ wheelInfo)
{
	// FIXME
	//UnmanagedPointer->remove(*wheelInfo->UnmanagedPointer);
}

int WheelInfoArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int WheelInfoArray::Size::get()
{
	return UnmanagedPointer->size();
}

void WheelInfoArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

WheelInfo^ WheelInfoArray::default::get(int index)
{
	return gcnew WheelInfo(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void WheelInfoArray_GetDefault(btAlignedObjectArray<btWheelInfo>* wheelInfoArray,
	int index, btWheelInfo* node)
{
	(*wheelInfoArray)[index] = *node;
}
#pragma managed(pop)
void WheelInfoArray::default::set(int index, WheelInfo^ value)
{
	WheelInfoArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btAlignedObjectArray<btWheelInfo>* WheelInfoArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btWheelInfo>*)AlignedObjectArray::UnmanagedPointer;
}
#endif