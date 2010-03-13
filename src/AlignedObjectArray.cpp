#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "BroadphaseProxy.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "PersistentManifold.h"
#ifndef DISABLE_DBVT
#include "Dbvt.h"
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

Object^ CollisionObjectEnumerator::Current::get()
{
	return gcnew CollisionObject((*_objArray->UnmanagedPointer)[i]);
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
BulletSharp::FaceArray::FaceArray(btAlignedObjectArray<btSoftBody::Face>* nodeArray)
: AlignedObjectArray(nodeArray)
{
}

BulletSharp::FaceArray::FaceArray()
: AlignedObjectArray(new btAlignedObjectArray<btSoftBody::Face>)
{
}

void BulletSharp::FaceArray::Clear()
{
	UnmanagedPointer->clear();
}

void BulletSharp::FaceArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void BulletSharp::FaceArray::PushBack(SoftBody::Face^ node)
{
	UnmanagedPointer->push_back(*node->UnmanagedPointer);
}

void BulletSharp::FaceArray::Remove(SoftBody::Face^ node)
{
	// FIXME
	//UnmanagedPointer->remove(*node->UnmanagedPointer);
}

int BulletSharp::FaceArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BulletSharp::FaceArray::Size::get()
{
	return UnmanagedPointer->size();
}

void BulletSharp::FaceArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

SoftBody::Face^ BulletSharp::FaceArray::default::get(int index)
{
	return gcnew SoftBody::Face(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void FaceArray_GetDefault(btAlignedObjectArray<btSoftBody::Face>* nodeArray,
	int index, btSoftBody::Face* node)
{
	(*nodeArray)[index] = *node;
}
#pragma managed(pop)
void BulletSharp::FaceArray::default::set(int index, SoftBody::Face^ value)
{
	FaceArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btAlignedObjectArray<btSoftBody::Face>* BulletSharp::FaceArray::UnmanagedPointer::get()
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

void IntArray::PushBack(int value)
{
	UnmanagedPointer->push_back(value);
}

void IntArray::Remove(int value)
{
	UnmanagedPointer->remove(value);
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
BulletSharp::NodeArray::NodeArray(btAlignedObjectArray<btSoftBody::Node>* nodeArray)
: AlignedObjectArray(nodeArray)
{
}

BulletSharp::NodeArray::NodeArray()
: AlignedObjectArray(new btAlignedObjectArray<btSoftBody::Node>)
{
}

void BulletSharp::NodeArray::Clear()
{
	UnmanagedPointer->clear();
}

void BulletSharp::NodeArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void BulletSharp::NodeArray::PushBack(SoftBody::Node^ node)
{
	UnmanagedPointer->push_back(*node->UnmanagedPointer);
}

void BulletSharp::NodeArray::Remove(SoftBody::Node^ node)
{
	// FIXME
	//UnmanagedPointer->remove(*node->UnmanagedPointer);
}

int BulletSharp::NodeArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BulletSharp::NodeArray::Size::get()
{
	return UnmanagedPointer->size();
}

void BulletSharp::NodeArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

SoftBody::Node^ BulletSharp::NodeArray::default::get(int index)
{
	return gcnew SoftBody::Node(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void NodeArray_GetDefault(btAlignedObjectArray<btSoftBody::Node>* nodeArray,
	int index, btSoftBody::Node* node)
{
	(*nodeArray)[index] = *node;
}
#pragma managed(pop)
void BulletSharp::NodeArray::default::set(int index, SoftBody::Node^ value)
{
	NodeArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btAlignedObjectArray<btSoftBody::Node>* BulletSharp::NodeArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btSoftBody::Node>*)AlignedObjectArray::UnmanagedPointer;
}
#endif
