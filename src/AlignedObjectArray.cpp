#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "BroadphaseProxy.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "CompoundShape.h"
#include "PersistentManifold.h"
#ifndef DISABLE_SOFTBODY
#include "SoftBody.h"
using namespace BulletSharp::SoftBody;
#endif
#ifndef DISABLE_VEHICLE
#include "WheelInfo.h"
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


AlignedBroadphasePairArray::AlignedBroadphasePairArray(btBroadphasePairArray* pairArray)
: AlignedObjectArray(pairArray)
{
}

AlignedBroadphasePairArray::AlignedBroadphasePairArray()
: AlignedObjectArray(new btBroadphasePairArray)
{
}

void AlignedBroadphasePairArray::Add(BroadphasePair^ pair)
{
	UnmanagedPointer->push_back(*pair->UnmanagedPointer);
}

void AlignedBroadphasePairArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedBroadphasePairArray::Contains(BroadphasePair^ pair)
{
	return UnmanagedPointer->findLinearSearch(*pair->UnmanagedPointer) != UnmanagedPointer->size();
}

void AlignedBroadphasePairArray::CopyTo(array<BroadphasePair^>^ array, int arrayIndex)
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

int AlignedBroadphasePairArray::IndexOf(BroadphasePair^ pair)
{
	int i = UnmanagedPointer->findLinearSearch(*pair->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedBroadphasePairArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedBroadphasePairArray::Remove(BroadphasePair^ pair)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(*pair->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int AlignedBroadphasePairArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedBroadphasePairArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedBroadphasePairArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BroadphasePair^ AlignedBroadphasePairArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew BroadphasePair(&(*UnmanagedPointer)[index]);
}
#pragma managed(push, off)
void BroadphasePairList_SetDefault(btBroadphasePairArray* pairArray,
	int index, btBroadphasePair* pair)
{
	(*pairArray)[index] = *pair;
}
#pragma managed(pop)
void AlignedBroadphasePairArray::default::set(int index, BroadphasePair^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	BroadphasePairList_SetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btBroadphasePairArray* AlignedBroadphasePairArray::UnmanagedPointer::get()
{
	return (btBroadphasePairArray*)AlignedObjectArray::UnmanagedPointer;
}


#ifndef DISABLE_SOFTBODY
AlignedClusterArray::AlignedClusterArray(btSoftBody::tClusterArray* clusterArray)
: AlignedObjectArray(clusterArray)
{
}

AlignedClusterArray::AlignedClusterArray()
: AlignedObjectArray(new btSoftBody::tClusterArray())
{
}

void AlignedClusterArray::Add(Cluster^ cluster)
{
	UnmanagedPointer->push_back(cluster->UnmanagedPointer);
}

void AlignedClusterArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedClusterArray::Contains(Cluster^ cluster)
{
	return UnmanagedPointer->findLinearSearch(cluster->UnmanagedPointer) != UnmanagedPointer->size();
}

void AlignedClusterArray::CopyTo(array<Cluster^>^ array, int arrayIndex)
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

int AlignedClusterArray::IndexOf(Cluster^ cluster)
{
	int i = UnmanagedPointer->findLinearSearch(cluster->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedClusterArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedClusterArray::Remove(Cluster^ cluster)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(cluster->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

void AlignedClusterArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int AlignedClusterArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedClusterArray::Count::get()
{
	return UnmanagedPointer->size();
}

BulletSharp::SoftBody::Cluster^ AlignedClusterArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Cluster((*UnmanagedPointer)[index]);
}
void AlignedClusterArray::default::set(int index, Cluster^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btSoftBody::tClusterArray* BulletSharp::SoftBody::AlignedClusterArray::UnmanagedPointer::get()
{
	return (btSoftBody::tClusterArray*)AlignedObjectArray::UnmanagedPointer;
}
#endif


AlignedCollisionShapeArray::AlignedCollisionShapeArray()
: AlignedObjectArray(new btAlignedObjectArray<btCollisionShape*>())
{
}

void AlignedCollisionShapeArray::Add(CollisionShape^ shape)
{
	UnmanagedPointer->push_back(shape->UnmanagedPointer);
}

void AlignedCollisionShapeArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedCollisionShapeArray::Contains(CollisionShape^ shape)
{
	return UnmanagedPointer->findLinearSearch(shape->UnmanagedPointer) != UnmanagedPointer->size();
}

void AlignedCollisionShapeArray::CopyTo(array<CollisionShape^>^ array, int arrayIndex)
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

int AlignedCollisionShapeArray::IndexOf(CollisionShape^ shape)
{
	int i = UnmanagedPointer->findLinearSearch(shape->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedCollisionShapeArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedCollisionShapeArray::Remove(CollisionShape^ collisionShape)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(collisionShape->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

void AlignedCollisionShapeArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int AlignedCollisionShapeArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedCollisionShapeArray::Count::get()
{
	return UnmanagedPointer->size();
}

CollisionShape^ AlignedCollisionShapeArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btCollisionShape* shape = (*UnmanagedPointer)[index];
	if (shape == nullptr)
		return nullptr;
	return gcnew CollisionShape(shape);
}
void AlignedCollisionShapeArray::default::set(int index, CollisionShape^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btAlignedObjectArray<btCollisionShape*>* AlignedCollisionShapeArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btCollisionShape*>*)AlignedObjectArray::UnmanagedPointer;
}


AlignedCollisionObjectArray::AlignedCollisionObjectArray(btCollisionObjectArray* objectArray)
: AlignedObjectArray(objectArray)
{
}

AlignedCollisionObjectArray::AlignedCollisionObjectArray()
: AlignedObjectArray(new btCollisionObjectArray())
{
}

void AlignedCollisionObjectArray::Add(CollisionObject^ obj)
{
	UnmanagedPointer->push_back(obj->UnmanagedPointer);
}

void AlignedCollisionObjectArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedCollisionObjectArray::Contains(CollisionObject^ obj)
{
	return UnmanagedPointer->findLinearSearch(obj->UnmanagedPointer) != UnmanagedPointer->size();
}

void AlignedCollisionObjectArray::CopyTo(array<CollisionObject^>^ array, int arrayIndex)
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

int AlignedCollisionObjectArray::IndexOf(CollisionObject^ obj)
{
	int i = UnmanagedPointer->findLinearSearch(obj->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedCollisionObjectArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedCollisionObjectArray::Remove(CollisionObject^ obj)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(obj->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

void AlignedCollisionObjectArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int AlignedCollisionObjectArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedCollisionObjectArray::Count::get()
{
	return UnmanagedPointer->size();
}

CollisionObject^ AlignedCollisionObjectArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btCollisionObject* obj = (*UnmanagedPointer)[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew CollisionObject(obj);
}
void AlignedCollisionObjectArray::default::set(int index, CollisionObject^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btCollisionObjectArray* AlignedCollisionObjectArray::UnmanagedPointer::get()
{
	return (btCollisionObjectArray*)AlignedObjectArray::UnmanagedPointer;
}


AlignedCompoundShapeChildArray::AlignedCompoundShapeChildArray(btAlignedObjectArray<btCompoundShapeChild>* compundShapeChildArray)
: AlignedObjectArray(compundShapeChildArray)
{
}

AlignedCompoundShapeChildArray::AlignedCompoundShapeChildArray()
: AlignedObjectArray(new btAlignedObjectArray<btCompoundShapeChild>)
{
}

void AlignedCompoundShapeChildArray::Add(CompoundShapeChild^ compoundShapeChild)
{
	UnmanagedPointer->push_back(*compoundShapeChild->UnmanagedPointer);
}

void AlignedCompoundShapeChildArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedCompoundShapeChildArray::Contains(CompoundShapeChild^ child)
{
	return UnmanagedPointer->findLinearSearch(*child->UnmanagedPointer) != UnmanagedPointer->size();
}

void AlignedCompoundShapeChildArray::CopyTo(array<CompoundShapeChild^>^ array, int arrayIndex)
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

int AlignedCompoundShapeChildArray::IndexOf(CompoundShapeChild^ child)
{
	int i = UnmanagedPointer->findLinearSearch(*child->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedCompoundShapeChildArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedCompoundShapeChildArray::Remove(CompoundShapeChild^ compoundShapeChild)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(*compoundShapeChild->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int AlignedCompoundShapeChildArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedCompoundShapeChildArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedCompoundShapeChildArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

CompoundShapeChild^ AlignedCompoundShapeChildArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew CompoundShapeChild(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void CompoundShapeChildArray_GetDefault(btAlignedObjectArray<btCompoundShapeChild>* shapeArray,
	int index, btCompoundShapeChild* node)
{
	(*shapeArray)[index] = *node;
}
#pragma managed(pop)
void AlignedCompoundShapeChildArray::default::set(int index, CompoundShapeChild^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	CompoundShapeChildArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btAlignedObjectArray<btCompoundShapeChild>* AlignedCompoundShapeChildArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btCompoundShapeChild>*)AlignedObjectArray::UnmanagedPointer;
}


#ifndef DISABLE_DBVT
AlignedDbvtNodeArray::AlignedDbvtNodeArray(btAlignedObjectArray<const btDbvtNode*>* AlignedNodeArray)
: AlignedObjectArray(AlignedNodeArray)
{
}

AlignedDbvtNodeArray::AlignedDbvtNodeArray()
: AlignedObjectArray(new btAlignedObjectArray<btDbvtNode>)
{
}

void AlignedDbvtNodeArray::Add(DbvtNode^ node)
{
	UnmanagedPointer->push_back(node->UnmanagedPointer);
}

void AlignedDbvtNodeArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedDbvtNodeArray::Contains(DbvtNode^ node)
{
	return UnmanagedPointer->findLinearSearch(node->UnmanagedPointer) != UnmanagedPointer->size();
}

void AlignedDbvtNodeArray::CopyTo(array<DbvtNode^>^ array, int arrayIndex)
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

int AlignedDbvtNodeArray::IndexOf(DbvtNode^ node)
{
	int i = UnmanagedPointer->findLinearSearch(node->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedDbvtNodeArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedDbvtNodeArray::Remove(DbvtNode^ node)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(node->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int AlignedDbvtNodeArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedDbvtNodeArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedDbvtNodeArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

DbvtNode^ AlignedDbvtNodeArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btDbvtNode* obj = (btDbvtNode*)(*UnmanagedPointer)[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew DbvtNode(obj);
}
void AlignedDbvtNodeArray::default::set(int index, DbvtNode^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btAlignedObjectArray<const btDbvtNode*>* AlignedDbvtNodeArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<const btDbvtNode*>*)AlignedObjectArray::UnmanagedPointer;
}


AlignedStkNnArray::AlignedStkNnArray(btAlignedObjectArray<btDbvt::sStkNN>* stkNnArray)
: AlignedObjectArray(stkNnArray)
{
}

AlignedStkNnArray::AlignedStkNnArray()
: AlignedObjectArray(new btAlignedObjectArray<btDbvt::sStkNN>)
{
}

void AlignedStkNnArray::Add(Dbvt::StkNn^ stkNn)
{
	UnmanagedPointer->push_back(*stkNn->UnmanagedPointer);
}

void AlignedStkNnArray::Clear()
{
	UnmanagedPointer->clear();
}

void AlignedStkNnArray::CopyTo(array<Dbvt::StkNn^>^ array, int arrayIndex)
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

void AlignedStkNnArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void AlignedStkNnArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int AlignedStkNnArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedStkNnArray::Count::get()
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

Dbvt::StkNn^ AlignedStkNnArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btDbvt::sStkNN* obj = new btDbvt::sStkNN;
	StkNnArray_GetDefault(UnmanagedPointer, index, obj);
	return gcnew Dbvt::StkNn(obj);
}

void AlignedStkNnArray::default::set(int index, Dbvt::StkNn^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = *value->UnmanagedPointer;
}

btAlignedObjectArray<btDbvt::sStkNN>* AlignedStkNnArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btDbvt::sStkNN>*)AlignedObjectArray::UnmanagedPointer;
}


AlignedStkNpsArray::AlignedStkNpsArray(btAlignedObjectArray<btDbvt::sStkNPS>* stkNpsArray)
: AlignedObjectArray(stkNpsArray)
{
}

AlignedStkNpsArray::AlignedStkNpsArray()
: AlignedObjectArray(new btAlignedObjectArray<btDbvt::sStkNPS>)
{
}

void AlignedStkNpsArray::Add(Dbvt::StkNps^ stkNps)
{
	UnmanagedPointer->push_back(*stkNps->UnmanagedPointer);
}

void AlignedStkNpsArray::Clear()
{
	UnmanagedPointer->clear();
}

void AlignedStkNpsArray::CopyTo(array<Dbvt::StkNps^>^ array, int arrayIndex)
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

void AlignedStkNpsArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void AlignedStkNpsArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int AlignedStkNpsArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedStkNpsArray::Count::get()
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

Dbvt::StkNps^ AlignedStkNpsArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btDbvt::sStkNPS* obj = new btDbvt::sStkNPS;
	StkNpsArray_GetDefault(UnmanagedPointer, index, obj);
	return gcnew Dbvt::StkNps(obj);
}

void AlignedStkNpsArray::default::set(int index, Dbvt::StkNps^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = *value->UnmanagedPointer;
}

btAlignedObjectArray<btDbvt::sStkNPS>* AlignedStkNpsArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btDbvt::sStkNPS>*)AlignedObjectArray::UnmanagedPointer;
}
#endif


#ifndef DISABLE_SOFTBODY
AlignedFaceArray::AlignedFaceArray(btAlignedObjectArray<btSoftBody::Face>* faceArray)
: AlignedObjectArray(faceArray)
{
}

AlignedFaceArray::AlignedFaceArray()
: AlignedObjectArray(new btAlignedObjectArray<btSoftBody::Face>)
{
}

void AlignedFaceArray::Add(Face^ face)
{
	UnmanagedPointer->push_back(*face->UnmanagedPointer);
}

void AlignedFaceArray::Clear()
{
	UnmanagedPointer->clear();
}

void AlignedFaceArray::CopyTo(array<Face^>^ array, int arrayIndex)
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

void AlignedFaceArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void AlignedFaceArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int AlignedFaceArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedFaceArray::Count::get()
{
	return UnmanagedPointer->size();
}

Face^ AlignedFaceArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Face(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void FaceArray_GetDefault(btAlignedObjectArray<btSoftBody::Face>* faceArray,
	int index, btSoftBody::Face* node)
{
	(*faceArray)[index] = *node;
}
#pragma managed(pop)
void AlignedFaceArray::default::set(int index, Face^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	FaceArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btAlignedObjectArray<btSoftBody::Face>* AlignedFaceArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btSoftBody::Face>*)AlignedObjectArray::UnmanagedPointer;
}
#endif


AlignedIntArray::AlignedIntArray(btAlignedObjectArray<int>* intArray)
: AlignedObjectArray(intArray)
{
}

AlignedIntArray::AlignedIntArray()
: AlignedObjectArray(new btAlignedObjectArray<int>)
{
}

void AlignedIntArray::Add(int intValue)
{
	UnmanagedPointer->push_back(intValue);
}

void AlignedIntArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedIntArray::Contains(int integer)
{
	return UnmanagedPointer->findLinearSearch(integer) != UnmanagedPointer->size();
}

void AlignedIntArray::CopyTo(array<int>^ array, int arrayIndex)
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

int AlignedIntArray::IndexOf(int integer)
{
	int i = UnmanagedPointer->findLinearSearch(integer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedIntArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedIntArray::Remove(int intValue)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(intValue);
	return sizeBefore != UnmanagedPointer->size();
}

int AlignedIntArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedIntArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedIntArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int AlignedIntArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (*UnmanagedPointer)[index];
}
void AlignedIntArray::default::set(int index, int value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = value;
}

btAlignedObjectArray<int>* AlignedIntArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<int>*)AlignedObjectArray::UnmanagedPointer;
}


AlignedManifoldArray::AlignedManifoldArray(btManifoldArray* manifoldArray)
: AlignedObjectArray(manifoldArray)
{
}

AlignedManifoldArray::AlignedManifoldArray()
: AlignedObjectArray(new btCollisionObjectArray())
{
}

void AlignedManifoldArray::Add(PersistentManifold^ manifold)
{
	UnmanagedPointer->push_back(manifold->UnmanagedPointer);
}

void AlignedManifoldArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedManifoldArray::Contains(PersistentManifold^ manifold)
{
	return UnmanagedPointer->findLinearSearch(manifold->UnmanagedPointer) != UnmanagedPointer->size();
}

void AlignedManifoldArray::CopyTo(array<PersistentManifold^>^ array, int arrayIndex)
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

int AlignedManifoldArray::IndexOf(PersistentManifold^ manifold)
{
	int i = UnmanagedPointer->findLinearSearch(manifold->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedManifoldArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedManifoldArray::Remove(PersistentManifold^ manifold)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(manifold->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int AlignedManifoldArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedManifoldArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedManifoldArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

PersistentManifold^ AlignedManifoldArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btPersistentManifold* obj = (*UnmanagedPointer)[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew PersistentManifold(obj);
}
void AlignedManifoldArray::default::set(int index, PersistentManifold^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btManifoldArray* AlignedManifoldArray::UnmanagedPointer::get()
{
	return (btManifoldArray*)AlignedObjectArray::UnmanagedPointer;
}


#ifndef DISABLE_SOFTBODY
AlignedLinkArray::AlignedLinkArray(btSoftBody::tLinkArray* linkArray)
: AlignedObjectArray(linkArray)
{
}

AlignedLinkArray::AlignedLinkArray()
: AlignedObjectArray(new btSoftBody::tLinkArray())
{
}

void AlignedLinkArray::Add(BulletSharp::SoftBody::Link^ link)
{
	UnmanagedPointer->push_back(*link->UnmanagedPointer);
}

void AlignedLinkArray::Clear()
{
	UnmanagedPointer->clear();
}

void AlignedLinkArray::CopyTo(array<Link^>^ array, int arrayIndex)
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

void AlignedLinkArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

int AlignedLinkArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedLinkArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedLinkArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Link^ AlignedLinkArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Link(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void LinkArray_GetDefault(btSoftBody::tLinkArray* linkArray,
	int index, btSoftBody::Link* link)
{
	(*linkArray)[index] = *link;
}
#pragma managed(pop)
void AlignedLinkArray::default::set(int index, BulletSharp::SoftBody::Link^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	LinkArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btSoftBody::tLinkArray* AlignedLinkArray::UnmanagedPointer::get()
{
	return (btSoftBody::tLinkArray*)AlignedObjectArray::UnmanagedPointer;
}


AlignedMaterialArray::AlignedMaterialArray(btSoftBody::tMaterialArray* materialArray)
: AlignedObjectArray(materialArray)
{
}

AlignedMaterialArray::AlignedMaterialArray()
: AlignedObjectArray(new btSoftBody::tMaterialArray())
{
}

void AlignedMaterialArray::Add(BulletSharp::SoftBody::Material^ material)
{
	UnmanagedPointer->push_back(material->UnmanagedPointer);
}

void AlignedMaterialArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedMaterialArray::Contains(BulletSharp::SoftBody::Material^ material)
{
	return UnmanagedPointer->findLinearSearch(material->UnmanagedPointer) != UnmanagedPointer->size();
}

void AlignedMaterialArray::CopyTo(array<BulletSharp::SoftBody::Material^>^ array, int arrayIndex)
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

int AlignedMaterialArray::IndexOf(BulletSharp::SoftBody::Material^ material)
{
	int i = UnmanagedPointer->findLinearSearch(material->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedMaterialArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedMaterialArray::Remove(BulletSharp::SoftBody::Material^ material)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(material->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int AlignedMaterialArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedMaterialArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedMaterialArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Material^ AlignedMaterialArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Material((*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void MaterialArray_GetDefault(btSoftBody::tMaterialArray* materialArray,
	int index, btSoftBody::Material* material)
{
	(*materialArray)[index] = material;
}
#pragma managed(pop)
void AlignedMaterialArray::default::set(int index, BulletSharp::SoftBody::Material^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	MaterialArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btSoftBody::tMaterialArray* AlignedMaterialArray::UnmanagedPointer::get()
{
	return (btSoftBody::tMaterialArray*)AlignedObjectArray::UnmanagedPointer;
}


// Note: Keep "BulletSharp::SoftBody::" to avoid conflict with AlignedNodeArray in btQuantizedBvh.h
BulletSharp::SoftBody::AlignedNodeArray::AlignedNodeArray(btSoftBody::tNodeArray* AlignedNodeArray)
: AlignedObjectArray(AlignedNodeArray)
{
}

BulletSharp::SoftBody::AlignedNodeArray::AlignedNodeArray()
: AlignedObjectArray(new btSoftBody::tNodeArray())
{
}

void BulletSharp::SoftBody::AlignedNodeArray::Add(Node^ node)
{
	UnmanagedPointer->push_back(*node->UnmanagedPointer);
}

void BulletSharp::SoftBody::AlignedNodeArray::Clear()
{
	UnmanagedPointer->clear();
}

void BulletSharp::SoftBody::AlignedNodeArray::CopyTo(array<Node^>^ array, int arrayIndex)
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

void BulletSharp::SoftBody::AlignedNodeArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

int BulletSharp::SoftBody::AlignedNodeArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BulletSharp::SoftBody::AlignedNodeArray::Count::get()
{
	return UnmanagedPointer->size();
}

void BulletSharp::SoftBody::AlignedNodeArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Node^ BulletSharp::SoftBody::AlignedNodeArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Node(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void NodeArray_GetDefault(btSoftBody::tNodeArray* AlignedNodeArray, int index, btSoftBody::Node* node)
{
	(*AlignedNodeArray)[index] = *node;
}
#pragma managed(pop)
void BulletSharp::SoftBody::AlignedNodeArray::default::set(int index, Node^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	NodeArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btSoftBody::tNodeArray* BulletSharp::SoftBody::AlignedNodeArray::UnmanagedPointer::get()
{
	return (btSoftBody::tNodeArray*)AlignedObjectArray::UnmanagedPointer;
}


AlignedNodePtrArray::AlignedNodePtrArray(btAlignedObjectArray<btSoftBody::Node*>* AlignedNodeArray)
: AlignedObjectArray(AlignedNodeArray)
{
}

AlignedNodePtrArray::AlignedNodePtrArray()
: AlignedObjectArray(new btAlignedObjectArray<btSoftBody::Node*>())
{
}

void AlignedNodePtrArray::Add(BulletSharp::SoftBody::Node^ node)
{
	UnmanagedPointer->push_back(node->UnmanagedPointer);
}

void AlignedNodePtrArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedNodePtrArray::Contains(BulletSharp::SoftBody::Node^ node)
{
	return UnmanagedPointer->findLinearSearch(node->UnmanagedPointer) != UnmanagedPointer->size();
}

void AlignedNodePtrArray::CopyTo(array<BulletSharp::SoftBody::Node^>^ array, int arrayIndex)
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

int AlignedNodePtrArray::IndexOf(BulletSharp::SoftBody::Node^ node)
{
	int i = UnmanagedPointer->findLinearSearch(node->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedNodePtrArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedNodePtrArray::Remove(BulletSharp::SoftBody::Node^ node)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(node->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int AlignedNodePtrArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedNodePtrArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedNodePtrArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Node^ AlignedNodePtrArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Node((*UnmanagedPointer)[index]);
}
void AlignedNodePtrArray::default::set(int index, BulletSharp::SoftBody::Node^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = value->UnmanagedPointer;
}

btAlignedObjectArray<btSoftBody::Node*>* AlignedNodePtrArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btSoftBody::Node*>*)AlignedObjectArray::UnmanagedPointer;
}


AlignedNoteArray::AlignedNoteArray(btSoftBody::tNoteArray* noteArray)
: AlignedObjectArray(noteArray)
{
}

AlignedNoteArray::AlignedNoteArray()
: AlignedObjectArray(new btSoftBody::tNoteArray())
{
}

void AlignedNoteArray::Add(Note^ note)
{
	UnmanagedPointer->push_back(*note->UnmanagedPointer);
}

void AlignedNoteArray::Clear()
{
	UnmanagedPointer->clear();
}

void AlignedNoteArray::CopyTo(array<Note^>^ array, int arrayIndex)
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

void AlignedNoteArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

int AlignedNoteArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedNoteArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedNoteArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::Note^ AlignedNoteArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Note(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void NoteArray_GetDefault(btSoftBody::tNoteArray* noteArray, int index, btSoftBody::Note* note)
{
	(*noteArray)[index] = *note;
}
#pragma managed(pop)
void AlignedNoteArray::default::set(int index, Note^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	NoteArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btSoftBody::tNoteArray* AlignedNoteArray::UnmanagedPointer::get()
{
	return (btSoftBody::tNoteArray*)AlignedObjectArray::UnmanagedPointer;
}
#endif


#ifndef DISABLE_SOFTBODY
AlignedPSolverArray::AlignedPSolverArray(btSoftBody::tPSolverArray* pSolverArray)
: AlignedObjectArray(pSolverArray)
{
}

AlignedPSolverArray::AlignedPSolverArray()
: AlignedObjectArray(new btSoftBody::tPSolverArray())
{
}

void AlignedPSolverArray::Add(PSolver solver)
{
	UnmanagedPointer->push_back((btSoftBody::ePSolver::_)solver);
}

void AlignedPSolverArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedPSolverArray::Contains(PSolver solver)
{
	return UnmanagedPointer->findLinearSearch((btSoftBody::ePSolver::_)solver) != UnmanagedPointer->size();
}

void AlignedPSolverArray::CopyTo(array<PSolver>^ array, int arrayIndex)
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
		array[arrayIndex+i] = (PSolver)(*UnmanagedPointer)[i];
	}
}

int AlignedPSolverArray::IndexOf(PSolver solver)
{
	int i = UnmanagedPointer->findLinearSearch((btSoftBody::ePSolver::_)solver);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedPSolverArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedPSolverArray::Remove(PSolver solver)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove((btSoftBody::ePSolver::_)solver);
	return sizeBefore != UnmanagedPointer->size();
}

int AlignedPSolverArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedPSolverArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedPSolverArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

PSolver AlignedPSolverArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (PSolver)(*UnmanagedPointer)[index];
}
void AlignedPSolverArray::default::set(int index, PSolver value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = (btSoftBody::ePSolver::_)value;
}

btSoftBody::tPSolverArray* AlignedPSolverArray::UnmanagedPointer::get()
{
	return (btSoftBody::tPSolverArray*)AlignedObjectArray::UnmanagedPointer;
}
#endif


AlignedScalarArray::AlignedScalarArray(btAlignedObjectArray<btScalar>* btScalarArray)
: AlignedObjectArray(btScalarArray)
{
}

AlignedScalarArray::AlignedScalarArray()
: AlignedObjectArray(new btAlignedObjectArray<btScalar>)
{
}

void AlignedScalarArray::Add(btScalar intValue)
{
	UnmanagedPointer->push_back(intValue);
}

void AlignedScalarArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedScalarArray::Contains(btScalar scalar)
{
	return UnmanagedPointer->findLinearSearch(scalar) != UnmanagedPointer->size();
}

void AlignedScalarArray::CopyTo(array<btScalar>^ array, int arrayIndex)
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

int AlignedScalarArray::IndexOf(btScalar scalar)
{
	int i = UnmanagedPointer->findLinearSearch(scalar);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedScalarArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedScalarArray::Remove(btScalar scalar)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(scalar);
	return sizeBefore != UnmanagedPointer->size();
}

int AlignedScalarArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedScalarArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedScalarArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

btScalar AlignedScalarArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (*UnmanagedPointer)[index];
}
void AlignedScalarArray::default::set(int index, btScalar value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = value;
}

btAlignedObjectArray<btScalar>* AlignedScalarArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btScalar>*)AlignedObjectArray::UnmanagedPointer;
}


#ifndef DISABLE_SOFTBODY
BulletSharp::SoftBody::AlignedSoftBodyArray::AlignedSoftBodyArray(btSoftBody::tSoftBodyArray* softBodyArray)
: AlignedObjectArray(softBodyArray)
{
}

BulletSharp::SoftBody::AlignedSoftBodyArray::AlignedSoftBodyArray()
: AlignedObjectArray(new btSoftBody::tSoftBodyArray())
{
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::Add(SoftBody^ softBody)
{
	UnmanagedPointer->push_back(softBody->UnmanagedPointer);
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::Clear()
{
	UnmanagedPointer->clear();
}

bool BulletSharp::SoftBody::AlignedSoftBodyArray::Contains(SoftBody^ softBody)
{
	return UnmanagedPointer->findLinearSearch(softBody->UnmanagedPointer) != UnmanagedPointer->size();
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::CopyTo(array<SoftBody^>^ array, int arrayIndex)
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

int BulletSharp::SoftBody::AlignedSoftBodyArray::IndexOf(SoftBody^ softBody)
{
	int i = UnmanagedPointer->findLinearSearch(softBody->UnmanagedPointer);
	return i != UnmanagedPointer->size() ? i : -1;
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool BulletSharp::SoftBody::AlignedSoftBodyArray::Remove(SoftBody^ softBody)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove(softBody->UnmanagedPointer);
	return sizeBefore != UnmanagedPointer->size();
}

int BulletSharp::SoftBody::AlignedSoftBodyArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int BulletSharp::SoftBody::AlignedSoftBodyArray::Count::get()
{
	return UnmanagedPointer->size();
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

BulletSharp::SoftBody::SoftBody^ BulletSharp::SoftBody::AlignedSoftBodyArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew SoftBody((*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void SoftBodyArray_GetDefault(btSoftBody::tSoftBodyArray* softBodyArray, int index, btSoftBody* softBody)
{
	(*softBodyArray)[index] = softBody;
}
#pragma managed(pop)
void BulletSharp::SoftBody::AlignedSoftBodyArray::default::set(int index, SoftBody^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	SoftBodyArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btSoftBody::tSoftBodyArray* BulletSharp::SoftBody::AlignedSoftBodyArray::UnmanagedPointer::get()
{
	return (btSoftBody::tSoftBodyArray*)AlignedObjectArray::UnmanagedPointer;
}


AlignedTetraArray::AlignedTetraArray(btAlignedObjectArray<btSoftBody::Tetra>* tetraArray)
: AlignedObjectArray(tetraArray)
{
}

AlignedTetraArray::AlignedTetraArray()
: AlignedObjectArray(new btAlignedObjectArray<btSoftBody::Tetra>)
{
}

void AlignedTetraArray::Add(Tetra^ tetra)
{
	UnmanagedPointer->push_back(*tetra->UnmanagedPointer);
}

void AlignedTetraArray::Clear()
{
	UnmanagedPointer->clear();
}

void AlignedTetraArray::CopyTo(array<Tetra^>^ array, int arrayIndex)
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
		array[arrayIndex+i] = gcnew Tetra(&(*UnmanagedPointer)[i]);
	}
}

void AlignedTetraArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

void AlignedTetraArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

int AlignedTetraArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedTetraArray::Count::get()
{
	return UnmanagedPointer->size();
}

Tetra^ AlignedTetraArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Tetra(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void TetraArray_GetDefault(btAlignedObjectArray<btSoftBody::Tetra>* tetraArray,
	int index, btSoftBody::Tetra* node)
{
	(*tetraArray)[index] = *node;
}
#pragma managed(pop)
void AlignedTetraArray::default::set(int index, Tetra^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	TetraArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btAlignedObjectArray<btSoftBody::Tetra>* AlignedTetraArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btSoftBody::Tetra>*)AlignedObjectArray::UnmanagedPointer;
}
#endif


AlignedVector3Array::AlignedVector3Array(btAlignedObjectArray<btVector3>* vector3Array)
: AlignedObjectArray(vector3Array)
{
}

AlignedVector3Array::AlignedVector3Array()
: AlignedObjectArray(new btAlignedObjectArray<btVector3>)
{
}

void AlignedVector3Array::Add(Vector3 vector3Value)
{
	btVector3* tempVector3Value = Math::Vector3ToBtVector3(vector3Value);
	UnmanagedPointer->push_back(*tempVector3Value);
	delete tempVector3Value;
}

void AlignedVector3Array::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedVector3Array::Contains(Vector3 vector)
{
	btVector3* vectorTemp = Math::Vector3ToBtVector3(vector);
	int i = UnmanagedPointer->findLinearSearch(*vectorTemp);
	delete vectorTemp;
	return i != UnmanagedPointer->size();
}

void AlignedVector3Array::CopyTo(array<Vector3>^ array, int arrayIndex)
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

int AlignedVector3Array::IndexOf(Vector3 vector)
{
	btVector3* vectorTemp = Math::Vector3ToBtVector3(vector);
	int i = UnmanagedPointer->findLinearSearch(*vectorTemp);
	delete vectorTemp;
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedVector3Array::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedVector3Array::Remove(Vector3 vector)
{
	int sizeBefore = UnmanagedPointer->size();
	btVector3* vectorTemp = Math::Vector3ToBtVector3(vector);
	UnmanagedPointer->remove(*vectorTemp);
	delete vectorTemp;
	return sizeBefore != UnmanagedPointer->size();
}

int AlignedVector3Array::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedVector3Array::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedVector3Array::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

Vector3 AlignedVector3Array::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return Math::BtVector3ToVector3(&(*UnmanagedPointer)[index]);
}
void AlignedVector3Array::default::set(int index, Vector3 value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	Math::Vector3ToBtVector3(value, &(*UnmanagedPointer)[index]);
}

btAlignedObjectArray<btVector3>* AlignedVector3Array::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btVector3>*)AlignedObjectArray::UnmanagedPointer;
}


#ifndef DISABLE_SOFTBODY
AlignedVSolverArray::AlignedVSolverArray(btSoftBody::tVSolverArray* vSolverArray)
: AlignedObjectArray(vSolverArray)
{
}

AlignedVSolverArray::AlignedVSolverArray()
: AlignedObjectArray(new btSoftBody::tVSolverArray())
{
}

void AlignedVSolverArray::Add(VSolver solver)
{
	UnmanagedPointer->push_back((btSoftBody::eVSolver::_)solver);
}

void AlignedVSolverArray::Clear()
{
	UnmanagedPointer->clear();
}

bool AlignedVSolverArray::Contains(VSolver solver)
{
	return UnmanagedPointer->findLinearSearch((btSoftBody::eVSolver::_)solver) != UnmanagedPointer->size();
}

void AlignedVSolverArray::CopyTo(array<VSolver>^ array, int arrayIndex)
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
		array[arrayIndex+i] = (VSolver)(*UnmanagedPointer)[i];
	}
}

int AlignedVSolverArray::IndexOf(VSolver solver)
{
	int i = UnmanagedPointer->findLinearSearch((btSoftBody::eVSolver::_)solver);
	return i != UnmanagedPointer->size() ? i : -1;
}

void AlignedVSolverArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

bool AlignedVSolverArray::Remove(VSolver solver)
{
	int sizeBefore = UnmanagedPointer->size();
	UnmanagedPointer->remove((btSoftBody::eVSolver::_)solver);
	return sizeBefore != UnmanagedPointer->size();
}

int AlignedVSolverArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedVSolverArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedVSolverArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

VSolver AlignedVSolverArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (VSolver)(*UnmanagedPointer)[index];
}
void AlignedVSolverArray::default::set(int index, VSolver value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*UnmanagedPointer)[index] = (btSoftBody::eVSolver::_)value;
}

btSoftBody::tVSolverArray* AlignedVSolverArray::UnmanagedPointer::get()
{
	return (btSoftBody::tVSolverArray*)AlignedObjectArray::UnmanagedPointer;
}
#endif


#ifndef DISABLE_VEHICLE
AlignedWheelInfoArray::AlignedWheelInfoArray(btAlignedObjectArray<btWheelInfo>* wheelInfoArray)
: AlignedObjectArray(wheelInfoArray)
{
}

AlignedWheelInfoArray::AlignedWheelInfoArray()
: AlignedObjectArray(new btAlignedObjectArray<btWheelInfo>)
{
}

void AlignedWheelInfoArray::Add(WheelInfo^ wheelInfo)
{
	UnmanagedPointer->push_back(*wheelInfo->UnmanagedPointer);
}

void AlignedWheelInfoArray::Clear()
{
	UnmanagedPointer->clear();
}

void AlignedWheelInfoArray::CopyTo(array<WheelInfo^>^ array, int arrayIndex)
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

void AlignedWheelInfoArray::PopBack()
{
	UnmanagedPointer->pop_back();
}

int AlignedWheelInfoArray::Capacity::get()
{
	return UnmanagedPointer->capacity();
}

int AlignedWheelInfoArray::Count::get()
{
	return UnmanagedPointer->size();
}

void AlignedWheelInfoArray::Swap(int index0, int index1)
{
	UnmanagedPointer->swap(index0, index1);
}

WheelInfo^ AlignedWheelInfoArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew WheelInfo(&(*UnmanagedPointer)[index]);
}

#pragma managed(push, off)
void WheelInfoArray_GetDefault(btAlignedObjectArray<btWheelInfo>* wheelInfoArray,
	int index, btWheelInfo* node)
{
	(*wheelInfoArray)[index] = *node;
}
#pragma managed(pop)
void AlignedWheelInfoArray::default::set(int index, WheelInfo^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	WheelInfoArray_GetDefault(UnmanagedPointer, index, value->UnmanagedPointer);
}

btAlignedObjectArray<btWheelInfo>* AlignedWheelInfoArray::UnmanagedPointer::get()
{
	return (btAlignedObjectArray<btWheelInfo>*)AlignedObjectArray::UnmanagedPointer;
}
#endif
