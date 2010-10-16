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

generic<class T>
AlignedObjectArray<T>::AlignedObjectArray(void* alignedObjectArray)
{
	_alignedObjectArray = alignedObjectArray;
}

generic<class T>
AlignedObjectArray<T>::!AlignedObjectArray()
{
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_alignedObjectArray = NULL;

	OnDisposed( this, nullptr );
}

generic<class T>
AlignedObjectArray<T>::~AlignedObjectArray()
{
	this->!AlignedObjectArray();
}

generic<class T>
IEnumerator^ AlignedObjectArray<T>::GetEnumerator()
{
	return gcnew ListEnumerator<T>(this);
}

generic<class T>
Generic::IEnumerator<T>^ AlignedObjectArray<T>::GetSpecializedEnumerator()
{
	return gcnew ListEnumerator<T>(this);
}

generic<class T>
bool AlignedObjectArray<T>::Contains(T item)
{
	return IndexOf(item) != -1;
}

generic<class T>
int AlignedObjectArray<T>::IndexOf(T item)
{
	/*
	If we're here, it means that the underlying struct type doesn't have
	an equality operator(==). So we use its C# counterpart,
	which does a member-wise comparison.
	*/
	int i;
	for (i=0; i<Count; i++)
	{
		if (this[i]->Equals(item))
			return i;
	}
	return -1;
}

generic<class T>
void AlignedObjectArray<T>::Insert(int index, T item)
{
	throw gcnew NotImplementedException();
	//throw gcnew System::NotSupportedException("Cannot resize collection.");
}

generic<class T>
bool AlignedObjectArray<T>::Remove(T item)
{
	int i = IndexOf(item);
	if (i != -1)
	{
		Swap(i, Count-1);
		PopBack();
		return true;
	}
	return false;
}

generic<class T>
void AlignedObjectArray<T>::RemoveAt(int index)
{
	throw gcnew NotImplementedException();
	//throw gcnew System::NotSupportedException("Cannot resize list.");
}

generic<class T>
bool AlignedObjectArray<T>::IsDisposed::get()
{
	return (_alignedObjectArray == NULL);
}

generic<class T>
bool AlignedObjectArray<T>::IsReadOnly::get()
{
	return false;
}

generic<class T>
void* AlignedObjectArray<T>::UnmanagedPointer::get()
{
	return _alignedObjectArray;
}
generic<class T>
void AlignedObjectArray<T>::UnmanagedPointer::set(void* value)
{
	_alignedObjectArray = value;
}


BroadphasePairArray::BroadphasePairArray(btBroadphasePairArray* pairArray)
: AlignedObjectArray(pairArray)
{
}

BroadphasePairArray::BroadphasePairArray()
: AlignedObjectArray(new btBroadphasePairArray)
{
}

void BroadphasePairArray::Add(BroadphasePair^ pair)
{
	UnmanagedPointer->push_back(*pair->UnmanagedPointer);
}

void BroadphasePairArray::Clear()
{
	UnmanagedPointer->clear();
}

bool BroadphasePairArray::Contains(BroadphasePair^ pair)
{
	return UnmanagedPointer->findLinearSearch(*pair->UnmanagedPointer) != UnmanagedPointer->size();
}

void BroadphasePairArray::CopyTo(array<BroadphasePair^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew BroadphasePair(&(*UnmanagedPointer)[i]);
	}
}

int BroadphasePairArray::IndexOf(BroadphasePair^ pair)
{
	int i = UnmanagedPointer->findLinearSearch(*pair->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void BroadphasePairArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool BroadphasePairArray::Remove(BroadphasePair^ pair)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(*pair->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int BroadphasePairArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BroadphasePairArray::Count::get()
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
ClusterArray::ClusterArray(btSoftBody::tClusterArray* clusterArray)
: AlignedObjectArray(clusterArray)
{
}

ClusterArray::ClusterArray()
: AlignedObjectArray(new btSoftBody::tClusterArray())
{
}

void ClusterArray::Add(Cluster^ cluster)
{
	UnmanagedPointer->push_back(cluster->UnmanagedPointer);
}

void ClusterArray::Clear()
{
	UnmanagedPointer->clear();
}

bool ClusterArray::Contains(Cluster^ cluster)
{
	return UnmanagedPointer->findLinearSearch(cluster->UnmanagedPointer) != UnmanagedPointer->size();
}

void ClusterArray::CopyTo(array<Cluster^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Cluster((*UnmanagedPointer)[i]);
	}
}

int ClusterArray::IndexOf(Cluster^ cluster)
{
	int i = UnmanagedPointer->findLinearSearch(cluster->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void ClusterArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool ClusterArray::Remove(Cluster^ cluster)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(cluster->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

void ClusterArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int ClusterArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int ClusterArray::Count::get()
{
	return UnmanagedPointer->size();
}

BulletSharp::SoftBody::Cluster^ ClusterArray::default::get(int index)
{
	return gcnew Cluster((*UnmanagedPointer)[index]);
}
void ClusterArray::default::set(int index, Cluster^ value)
{
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btSoftBody::tClusterArray* BulletSharp::SoftBody::ClusterArray::UnmanagedPointer::get()
{
	return (btSoftBody::tClusterArray*)AlignedObjectArray::UnmanagedPointer;
}
#endif


CollisionShapeArray::CollisionShapeArray()
: AlignedObjectArray(new btAlignedObjectArray<btCollisionShape*>())
{
}

void CollisionShapeArray::Add(CollisionShape^ shape)
{
	UnmanagedPointer->push_back(shape->UnmanagedPointer);
}

void CollisionShapeArray::Clear()
{
	UnmanagedPointer->clear();
}

bool CollisionShapeArray::Contains(CollisionShape^ shape)
{
	return UnmanagedPointer->findLinearSearch(shape->UnmanagedPointer) != UnmanagedPointer->size();
}

void CollisionShapeArray::CopyTo(array<CollisionShape^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew CollisionShape((*UnmanagedPointer)[i]);
	}
}

int CollisionShapeArray::IndexOf(CollisionShape^ shape)
{
	int i = UnmanagedPointer->findLinearSearch(shape->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void CollisionShapeArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool CollisionShapeArray::Remove(CollisionShape^ collisionShape)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(collisionShape->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

void CollisionShapeArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int CollisionShapeArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int CollisionShapeArray::Count::get()
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

CollisionObjectArray::CollisionObjectArray()
: AlignedObjectArray(new btCollisionObjectArray())
{
}

void CollisionObjectArray::Add(CollisionObject^ obj)
{
	UnmanagedPointer->push_back(obj->UnmanagedPointer);
}

void CollisionObjectArray::Clear()
{
	UnmanagedPointer->clear();
}

bool CollisionObjectArray::Contains(CollisionObject^ obj)
{
	return UnmanagedPointer->findLinearSearch(obj->UnmanagedPointer) != UnmanagedPointer->size();
}

void CollisionObjectArray::CopyTo(array<CollisionObject^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew CollisionObject((*UnmanagedPointer)[i]);
	}
}

int CollisionObjectArray::IndexOf(CollisionObject^ obj)
{
	int i = UnmanagedPointer->findLinearSearch(obj->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void CollisionObjectArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool CollisionObjectArray::Remove(CollisionObject^ obj)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(obj->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

void CollisionObjectArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int CollisionObjectArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int CollisionObjectArray::Count::get()
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


CompoundShapeChildArray::CompoundShapeChildArray(btAlignedObjectArray<btCompoundShapeChild>* compundShapeChildArray)
: AlignedObjectArray(compundShapeChildArray)
{
}

CompoundShapeChildArray::CompoundShapeChildArray()
: AlignedObjectArray(new btAlignedObjectArray<btCompoundShapeChild>)
{
}

void CompoundShapeChildArray::Add(CompoundShapeChild^ compoundShapeChild)
{
	UnmanagedPointer->push_back(*compoundShapeChild->UnmanagedPointer);
}

void CompoundShapeChildArray::Clear()
{
	UnmanagedPointer->clear();
}

bool CompoundShapeChildArray::Contains(CompoundShapeChild^ child)
{
	return UnmanagedPointer->findLinearSearch(*child->UnmanagedPointer) != UnmanagedPointer->size();
}

void CompoundShapeChildArray::CopyTo(array<CompoundShapeChild^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew CompoundShapeChild(&(*UnmanagedPointer)[i]);
	}
}

int CompoundShapeChildArray::IndexOf(CompoundShapeChild^ child)
{
	int i = UnmanagedPointer->findLinearSearch(*child->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void CompoundShapeChildArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool CompoundShapeChildArray::Remove(CompoundShapeChild^ compoundShapeChild)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(*compoundShapeChild->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int CompoundShapeChildArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int CompoundShapeChildArray::Count::get()
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


#ifndef DISABLE_DBVT
DbvtNodeArray::DbvtNodeArray(btAlignedObjectArray<const btDbvtNode*>* nodeArray)
: AlignedObjectArray(nodeArray)
{
}

DbvtNodeArray::DbvtNodeArray()
: AlignedObjectArray(new btAlignedObjectArray<btDbvtNode>)
{
}

void DbvtNodeArray::Add(DbvtNode^ node)
{
	UnmanagedPointer->push_back(node->UnmanagedPointer);
}

void DbvtNodeArray::Clear()
{
	UnmanagedPointer->clear();
}

bool DbvtNodeArray::Contains(DbvtNode^ node)
{
	return UnmanagedPointer->findLinearSearch(node->UnmanagedPointer) != UnmanagedPointer->size();
}

void DbvtNodeArray::CopyTo(array<DbvtNode^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew DbvtNode((btDbvtNode*)(*UnmanagedPointer)[i]);
	}
}

int DbvtNodeArray::IndexOf(DbvtNode^ node)
{
	int i = UnmanagedPointer->findLinearSearch(node->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void DbvtNodeArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool DbvtNodeArray::Remove(DbvtNode^ node)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(node->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int DbvtNodeArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int DbvtNodeArray::Count::get()
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

void StkNnArray::Add(Dbvt::StkNn^ stkNn)
{
	UnmanagedPointer->push_back(*stkNn->UnmanagedPointer);
}

void StkNnArray::Clear()
{
	UnmanagedPointer->clear();
}

void StkNnArray::CopyTo(array<Dbvt::StkNn^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Dbvt::StkNn(&(*UnmanagedPointer)[i]);
	}
}

void StkNnArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void StkNnArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int StkNnArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int StkNnArray::Count::get()
{
	return UnmanagedPointer->size();
}

#pragma managed(push, off)
void StkNnArray_GetDefault(btAlignedObjectArray<btDbvt::sStkNN>* stkNnArray,
	int index, btDbvt::sStkNN* obj)
{
	*obj = (*stkNnArray)[index];
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

void StkNpsArray::Add(Dbvt::StkNps^ stkNps)
{
	UnmanagedPointer->push_back(*stkNps->UnmanagedPointer);
}

void StkNpsArray::Clear()
{
	UnmanagedPointer->clear();
}

void StkNpsArray::CopyTo(array<Dbvt::StkNps^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Dbvt::StkNps(&(*UnmanagedPointer)[i]);
	}
}

void StkNpsArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void StkNpsArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int StkNpsArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int StkNpsArray::Count::get()
{
	return UnmanagedPointer->size();
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

void FaceArray::Add(Face^ face)
{
	UnmanagedPointer->push_back(*face->UnmanagedPointer);
}

void FaceArray::Clear()
{
	UnmanagedPointer->clear();
}

void FaceArray::CopyTo(array<Face^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Face(&(*UnmanagedPointer)[i]);
	}
}

void FaceArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void FaceArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int FaceArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int FaceArray::Count::get()
{
	return UnmanagedPointer->size();
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

void IntArray::Add(int intValue)
{
	UnmanagedPointer->push_back(intValue);
}

void IntArray::Clear()
{
	UnmanagedPointer->clear();
}

bool IntArray::Contains(int integer)
{
	return UnmanagedPointer->findLinearSearch(integer) != UnmanagedPointer->size();
}

void IntArray::CopyTo(array<int>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (*UnmanagedPointer)[i];
	}
}

int IntArray::IndexOf(int integer)
{
	int i = UnmanagedPointer->findLinearSearch(integer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void IntArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool IntArray::Remove(int intValue)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(intValue);
	return sizeBefore != UnmanagedPointer->size();
}

int IntArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int IntArray::Count::get()
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

void ManifoldArray::Add(PersistentManifold^ manifold)
{
	UnmanagedPointer->push_back(manifold->UnmanagedPointer);
}

void ManifoldArray::Clear()
{
	UnmanagedPointer->clear();
}

bool ManifoldArray::Contains(PersistentManifold^ manifold)
{
	return UnmanagedPointer->findLinearSearch(manifold->UnmanagedPointer) != UnmanagedPointer->size();
}

void ManifoldArray::CopyTo(array<PersistentManifold^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew PersistentManifold((*UnmanagedPointer)[i]);
	}
}

int ManifoldArray::IndexOf(PersistentManifold^ manifold)
{
	int i = UnmanagedPointer->findLinearSearch(manifold->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void ManifoldArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool ManifoldArray::Remove(PersistentManifold^ manifold)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(manifold->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int ManifoldArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int ManifoldArray::Count::get()
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

void LinkArray::Add(BulletSharp::SoftBody::Link^ link)
{
	UnmanagedPointer->push_back(*link->UnmanagedPointer);
}

void LinkArray::Clear()
{
	UnmanagedPointer->clear();
}

void LinkArray::CopyTo(array<Link^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Link(&(*UnmanagedPointer)[i]);
	}
}

void LinkArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

int LinkArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int LinkArray::Count::get()
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

MaterialArray::MaterialArray(btSoftBody::tMaterialArray* materialArray)
: AlignedObjectArray(materialArray)
{
}

MaterialArray::MaterialArray()
: AlignedObjectArray(new btSoftBody::tMaterialArray())
{
}

void MaterialArray::Add(BulletSharp::SoftBody::Material^ material)
{
	UnmanagedPointer->push_back(material->UnmanagedPointer);
}

void MaterialArray::Clear()
{
	UnmanagedPointer->clear();
}

bool MaterialArray::Contains(BulletSharp::SoftBody::Material^ material)
{
	return UnmanagedPointer->findLinearSearch(material->UnmanagedPointer) != UnmanagedPointer->size();
}

void MaterialArray::CopyTo(array<BulletSharp::SoftBody::Material^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Material((*UnmanagedPointer)[i]);
	}
}

int MaterialArray::IndexOf(BulletSharp::SoftBody::Material^ material)
{
	int i = UnmanagedPointer->findLinearSearch(material->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void MaterialArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool MaterialArray::Remove(BulletSharp::SoftBody::Material^ material)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(material->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int MaterialArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int MaterialArray::Count::get()
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


// Note: Keep "BulletSharp::SoftBody::" to avoid conflict with NodeArray in btQuantizedBvh.h
BulletSharp::SoftBody::NodeArray::NodeArray(btSoftBody::tNodeArray* nodeArray)
: AlignedObjectArray(nodeArray)
{
}

BulletSharp::SoftBody::NodeArray::NodeArray()
: AlignedObjectArray(new btSoftBody::tNodeArray())
{
}

void BulletSharp::SoftBody::NodeArray::Add(Node^ node)
{
	UnmanagedPointer->push_back(*node->UnmanagedPointer);
}

void BulletSharp::SoftBody::NodeArray::Clear()
{
	UnmanagedPointer->clear();
}

void BulletSharp::SoftBody::NodeArray::CopyTo(array<Node^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Node(&(*UnmanagedPointer)[i]);
	}
}

void BulletSharp::SoftBody::NodeArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

int BulletSharp::SoftBody::NodeArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BulletSharp::SoftBody::NodeArray::Count::get()
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


NodePtrArray::NodePtrArray(btAlignedObjectArray<btSoftBody::Node*>* nodeArray)
: AlignedObjectArray(nodeArray)
{
}

NodePtrArray::NodePtrArray()
: AlignedObjectArray(new btAlignedObjectArray<btSoftBody::Node*>())
{
}

void NodePtrArray::Add(BulletSharp::SoftBody::Node^ node)
{
	UnmanagedPointer->push_back(node->UnmanagedPointer);
}

void NodePtrArray::Clear()
{
	UnmanagedPointer->clear();
}

bool NodePtrArray::Contains(BulletSharp::SoftBody::Node^ node)
{
	return UnmanagedPointer->findLinearSearch(node->UnmanagedPointer) != UnmanagedPointer->size();
}

void NodePtrArray::CopyTo(array<BulletSharp::SoftBody::Node^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Node((*UnmanagedPointer)[i]);
	}
}

int NodePtrArray::IndexOf(BulletSharp::SoftBody::Node^ node)
{
	int i = UnmanagedPointer->findLinearSearch(node->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void NodePtrArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool NodePtrArray::Remove(BulletSharp::SoftBody::Node^ node)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(node->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int NodePtrArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int NodePtrArray::Count::get()
{
	return UnmanagedPointer->size();
}

void NodePtrArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Node^ NodePtrArray::default::get(int index)
{
	return gcnew Node((*UnmanagedPointer)[index]);
}
void NodePtrArray::default::set(int index, BulletSharp::SoftBody::Node^ value)
{
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btAlignedObjectArray<btSoftBody::Node*>* NodePtrArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btSoftBody::Node*>*)AlignedObjectArray::UnmanagedPointer;
}


NoteArray::NoteArray(btSoftBody::tNoteArray* noteArray)
: AlignedObjectArray(noteArray)
{
}

NoteArray::NoteArray()
: AlignedObjectArray(new btSoftBody::tNoteArray())
{
}

void NoteArray::Add(Note^ note)
{
	UnmanagedPointer->push_back(*note->UnmanagedPointer);
}

void NoteArray::Clear()
{
	UnmanagedPointer->clear();
}

void NoteArray::CopyTo(array<Note^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Note(&(*UnmanagedPointer)[i]);
	}
}

void NoteArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

int NoteArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int NoteArray::Count::get()
{
	return UnmanagedPointer->size();
}

void NoteArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Note^ NoteArray::default::get(int index)
{
	return gcnew Note(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void NoteArray_GetDefault(btSoftBody::tNoteArray* noteArray, int index, btSoftBody::Note* note)
{
	(*noteArray)[index] = *note;
}
#pragma managed(pop)
void NoteArray::default::set(int index, Note^ value)
{
	NoteArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btSoftBody::tNoteArray* NoteArray::UnmanagedPointer::get()
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

void ScalarArray::Add(btScalar intValue)
{
	UnmanagedPointer->push_back(intValue);
}

void ScalarArray::Clear()
{
	UnmanagedPointer->clear();
}

bool ScalarArray::Contains(btScalar scalar)
{
	return UnmanagedPointer->findLinearSearch(scalar) != UnmanagedPointer->size();
}

void ScalarArray::CopyTo(array<btScalar>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (*UnmanagedPointer)[i];
	}
}

int ScalarArray::IndexOf(btScalar scalar)
{
	int i = UnmanagedPointer->findLinearSearch(scalar);
	return i != UnmanagedPointer->size() ? i : -1;
}

void ScalarArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool ScalarArray::Remove(btScalar scalar)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(scalar);
	return sizeBefore != UnmanagedPointer->size();
}

int ScalarArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int ScalarArray::Count::get()
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

void BulletSharp::SoftBody::SoftBodyArray::Add(SoftBody^ softBody)
{
	UnmanagedPointer->push_back(softBody->UnmanagedPointer);
}

void BulletSharp::SoftBody::SoftBodyArray::Clear()
{
	UnmanagedPointer->clear();
}

bool BulletSharp::SoftBody::SoftBodyArray::Contains(SoftBody^ softBody)
{
	return UnmanagedPointer->findLinearSearch(softBody->UnmanagedPointer) != UnmanagedPointer->size();
}

void BulletSharp::SoftBody::SoftBodyArray::CopyTo(array<SoftBody^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew SoftBody((*UnmanagedPointer)[i]);
	}
}

int BulletSharp::SoftBody::SoftBodyArray::IndexOf(SoftBody^ softBody)
{
	int i = UnmanagedPointer->findLinearSearch(softBody->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void BulletSharp::SoftBody::SoftBodyArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool BulletSharp::SoftBody::SoftBodyArray::Remove(SoftBody^ softBody)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(softBody->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int BulletSharp::SoftBody::SoftBodyArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BulletSharp::SoftBody::SoftBodyArray::Count::get()
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

void Vector3Array::Add(Vector3 vector3Value)
{
	btVector3* tempVector3Value = Math::Vector3ToBtVector3(vector3Value);
	UnmanagedPointer->push_back(*tempVector3Value);
	delete tempVector3Value;
}

void Vector3Array::Clear()
{
	UnmanagedPointer->clear();
}

bool Vector3Array::Contains(Vector3 vector)
{
	btVector3* vectorTemp = Math::Vector3ToBtVector3(vector);
	int i = UnmanagedPointer->findLinearSearch(*vectorTemp);
	delete vectorTemp;
	return i != UnmanagedPointer->size();
}

void Vector3Array::CopyTo(array<Vector3>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = Math::BtVector3ToVector3(&(*UnmanagedPointer)[i]);
	}
}

int Vector3Array::IndexOf(Vector3 vector)
{
	btVector3* vectorTemp = Math::Vector3ToBtVector3(vector);
	int i = UnmanagedPointer->findLinearSearch(*vectorTemp);
	delete vectorTemp;
	return i != UnmanagedPointer->size() ? i : -1;
}

void Vector3Array::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool Vector3Array::Remove(Vector3 vector)
{
	int sizeBefore = UnmanagedPointer->size();
	btVector3* vectorTemp = Math::Vector3ToBtVector3(vector);
	UnmanagedPointer->remove(*vectorTemp);
	delete vectorTemp;
	return sizeBefore != UnmanagedPointer->size();
}

int Vector3Array::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int Vector3Array::Count::get()
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

void WheelInfoArray::Add(WheelInfo^ wheelInfo)
{
	UnmanagedPointer->push_back(*wheelInfo->UnmanagedPointer);
}

void WheelInfoArray::Clear()
{
	UnmanagedPointer->clear();
}

void WheelInfoArray::CopyTo(array<WheelInfo^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("arrayIndex");

	int size = UnmanagedPointer->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew WheelInfo(&(*UnmanagedPointer)[i]);
	}
}

void WheelInfoArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

int WheelInfoArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int WheelInfoArray::Count::get()
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
