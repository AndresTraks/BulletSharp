#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "BroadphaseProxy.h"
#include "Collections.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "CompoundShape.h"
#include "PersistentManifold.h"
#include "TriangleIndexVertexArray.h"
#include "TriangleMesh.h"
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
	_unmanaged = alignedObjectArray;
}

generic<class T>
AlignedObjectArray<T>::!AlignedObjectArray()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	_unmanaged = NULL;

	OnDisposed(this, nullptr);
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
	return (_unmanaged == NULL);
}

generic<class T>
bool AlignedObjectArray<T>::IsReadOnly::get()
{
	return false;
}


#ifndef DISABLE_SOFTBODY
AlignedAnchorArray::AlignedAnchorArray(btSoftBody::tAnchorArray* anchorArray)
: AlignedObjectArray(anchorArray)
{
}

AlignedAnchorArray::AlignedAnchorArray()
: AlignedObjectArray(new btSoftBody::tAnchorArray())
{
}

void AlignedAnchorArray::Add(Anchor^ anchor)
{
	((btSoftBody::tAnchorArray*)_unmanaged)->push_back(*anchor->UnmanagedPointer);
}

void AlignedAnchorArray::Clear()
{
	((btSoftBody::tAnchorArray*)_unmanaged)->clear();
}

void AlignedAnchorArray::CopyTo(array<Anchor^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tAnchorArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Anchor(&(*((btSoftBody::tAnchorArray*)_unmanaged))[i]);
	}
}

void AlignedAnchorArray::PopBack()
{
	((btSoftBody::tAnchorArray*)_unmanaged)->pop_back();
}

void AlignedAnchorArray::Swap(int index0, int index1)
{
	((btSoftBody::tAnchorArray*)_unmanaged)->swap(index0, index1);
}

int AlignedAnchorArray::Capacity::get()
{
	return ((btSoftBody::tAnchorArray*)_unmanaged)->capacity();
}

int AlignedAnchorArray::Count::get()
{
	return ((btSoftBody::tAnchorArray*)_unmanaged)->size();
}

BulletSharp::SoftBody::Anchor^ AlignedAnchorArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Anchor(&(*(btSoftBody::tAnchorArray*)_unmanaged)[index]);
}

void AlignedAnchorArray_SetDefault(btSoftBody::tAnchorArray* anchorArray,
	int index, btSoftBody::Anchor* anchor)
{
	(*anchorArray)[index] = *anchor;
}
void AlignedAnchorArray::default::set(int index, Anchor^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedAnchorArray_SetDefault(((btSoftBody::tAnchorArray*)_unmanaged), index, value->UnmanagedPointer);
}
#endif


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
	((btBroadphasePairArray*)_unmanaged)->push_back(*pair->UnmanagedPointer);
}

void AlignedBroadphasePairArray::Clear()
{
	((btBroadphasePairArray*)_unmanaged)->clear();
}

bool AlignedBroadphasePairArray::Contains(BroadphasePair^ pair)
{
	return ((btBroadphasePairArray*)_unmanaged)->findLinearSearch(*pair->UnmanagedPointer)
		!= ((btBroadphasePairArray*)_unmanaged)->size();
}

void AlignedBroadphasePairArray::CopyTo(array<BroadphasePair^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btBroadphasePairArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew BroadphasePair(&(*((btBroadphasePairArray*)_unmanaged))[i]);
	}
}

int AlignedBroadphasePairArray::IndexOf(BroadphasePair^ pair)
{
	int i = ((btBroadphasePairArray*)_unmanaged)->findLinearSearch(*pair->UnmanagedPointer);
	return i != ((btBroadphasePairArray*)_unmanaged)->size() ? i : -1;
}

void AlignedBroadphasePairArray::PopBack()
{
	((btBroadphasePairArray*)_unmanaged)->pop_back();
}

bool AlignedBroadphasePairArray::Remove(BroadphasePair^ pair)
{
	int sizeBefore = ((btBroadphasePairArray*)_unmanaged)->size();
	((btBroadphasePairArray*)_unmanaged)->remove(*pair->UnmanagedPointer);
	return sizeBefore != ((btBroadphasePairArray*)_unmanaged)->size();
}

int AlignedBroadphasePairArray::Capacity::get()
{
	return ((btBroadphasePairArray*)_unmanaged)->capacity();
}

int AlignedBroadphasePairArray::Count::get()
{
	return ((btBroadphasePairArray*)_unmanaged)->size();
}

void AlignedBroadphasePairArray::Swap(int index0, int index1)
{
	((btBroadphasePairArray*)_unmanaged)->swap(index0, index1);
}

BroadphasePair^ AlignedBroadphasePairArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew BroadphasePair(&(*((btBroadphasePairArray*)_unmanaged))[index]);
}

void BroadphasePairList_SetDefault(btBroadphasePairArray* pairArray,
	int index, btBroadphasePair* pair)
{
	(*pairArray)[index] = *pair;
}
void AlignedBroadphasePairArray::default::set(int index, BroadphasePair^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	BroadphasePairList_SetDefault(((btBroadphasePairArray*)_unmanaged), index, value->UnmanagedPointer);
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
	((btSoftBody::tClusterArray*)_unmanaged)->push_back(cluster->UnmanagedPointer);
}

void AlignedClusterArray::Clear()
{
	((btSoftBody::tClusterArray*)_unmanaged)->clear();
}

bool AlignedClusterArray::Contains(Cluster^ cluster)
{
	return ((btSoftBody::tClusterArray*)_unmanaged)->findLinearSearch(cluster->UnmanagedPointer)
		!= ((btSoftBody::tClusterArray*)_unmanaged)->size();
}

void AlignedClusterArray::CopyTo(array<Cluster^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tClusterArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Cluster((*((btSoftBody::tClusterArray*)_unmanaged))[i]);
	}
}

int AlignedClusterArray::IndexOf(Cluster^ cluster)
{
	int i = ((btSoftBody::tClusterArray*)_unmanaged)->findLinearSearch(cluster->UnmanagedPointer);
	return i != ((btSoftBody::tClusterArray*)_unmanaged)->size() ? i : -1;
}

void AlignedClusterArray::PopBack()
{
	((btSoftBody::tClusterArray*)_unmanaged)->pop_back();
}

bool AlignedClusterArray::Remove(Cluster^ cluster)
{
	int sizeBefore = ((btSoftBody::tClusterArray*)_unmanaged)->size();
	((btSoftBody::tClusterArray*)_unmanaged)->remove(cluster->UnmanagedPointer);
	return sizeBefore != ((btSoftBody::tClusterArray*)_unmanaged)->size();
}

void AlignedClusterArray::Swap(int index0, int index1)
{
	((btSoftBody::tClusterArray*)_unmanaged)->swap(index0, index1);
}

int AlignedClusterArray::Capacity::get()
{
	return ((btSoftBody::tClusterArray*)_unmanaged)->capacity();
}

int AlignedClusterArray::Count::get()
{
	return ((btSoftBody::tClusterArray*)_unmanaged)->size();
}

BulletSharp::SoftBody::Cluster^ AlignedClusterArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Cluster((*((btSoftBody::tClusterArray*)_unmanaged))[index]);
}
void AlignedClusterArray::default::set(int index, Cluster^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*((btSoftBody::tClusterArray*)_unmanaged))[index] = GetUnmanagedNullable(value);
}
#endif


AlignedCollisionShapeArray::AlignedCollisionShapeArray()
: AlignedObjectArray(new btAlignedObjectArray<btCollisionShape*>())
{
}

void AlignedCollisionShapeArray::Add(CollisionShape^ shape)
{
	((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->push_back(shape->UnmanagedPointer);
}

void AlignedCollisionShapeArray::Clear()
{
	((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->clear();
}

bool AlignedCollisionShapeArray::Contains(CollisionShape^ shape)
{
	return ((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->findLinearSearch(shape->UnmanagedPointer)
		!= ((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->size();
}

void AlignedCollisionShapeArray::CopyTo(array<CollisionShape^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<btCollisionShape>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = CollisionShape::GetManaged(&(*((btAlignedObjectArray<btCollisionShape>*)_unmanaged))[i]);
	}
}

int AlignedCollisionShapeArray::IndexOf(CollisionShape^ shape)
{
	int i = ((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->findLinearSearch(shape->UnmanagedPointer);
	return i != ((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->size() ? i : -1;
}

void AlignedCollisionShapeArray::PopBack()
{
	((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->pop_back();
}

bool AlignedCollisionShapeArray::Remove(CollisionShape^ collisionShape)
{
	int sizeBefore = ((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->size();
	((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->remove(collisionShape->UnmanagedPointer);
	return sizeBefore != ((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->size();
}

void AlignedCollisionShapeArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->swap(index0, index1);
}

int AlignedCollisionShapeArray::Capacity::get()
{
	return ((btAlignedObjectArray<btCollisionShape>*)_unmanaged)->capacity();
}

int AlignedCollisionShapeArray::Count::get()
{
	return ((btAlignedObjectArray<btCollisionShape>*)_unmanaged)->size();
}

CollisionShape^ AlignedCollisionShapeArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");

	return CollisionShape::GetManaged((*((btAlignedObjectArray<btCollisionShape*>*)_unmanaged))[index]);
}
void AlignedCollisionShapeArray::default::set(int index, CollisionShape^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");

	(*((btAlignedObjectArray<btCollisionShape*>*)_unmanaged))[index] = GetUnmanagedNullable(value);
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
	((btCollisionObjectArray*)_unmanaged)->push_back(obj->UnmanagedPointer);
}

void AlignedCollisionObjectArray::Clear()
{
	((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->clear();
}

bool AlignedCollisionObjectArray::Contains(CollisionObject^ obj)
{
	return ((btCollisionObjectArray*)_unmanaged)->findLinearSearch(obj->UnmanagedPointer)
		!= ((btCollisionObjectArray*)_unmanaged)->size();
}

void AlignedCollisionObjectArray::CopyTo(array<CollisionObject^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btCollisionObjectArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = CollisionObject::GetManaged((*((btCollisionObjectArray*)_unmanaged))[i]);
	}
}

int AlignedCollisionObjectArray::IndexOf(CollisionObject^ obj)
{
	int i = ((btCollisionObjectArray*)_unmanaged)->findLinearSearch(obj->UnmanagedPointer);
	return i != ((btCollisionObjectArray*)_unmanaged)->size() ? i : -1;
}

void AlignedCollisionObjectArray::PopBack()
{
	((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->pop_back();
}

bool AlignedCollisionObjectArray::Remove(CollisionObject^ obj)
{
	int sizeBefore = ((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->size();
	((btCollisionObjectArray*)_unmanaged)->remove(obj->UnmanagedPointer);
	return sizeBefore != ((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->size();
}

void AlignedCollisionObjectArray::Swap(int index0, int index1)
{
	((btCollisionObjectArray*)_unmanaged)->swap(index0, index1);
}

int AlignedCollisionObjectArray::Capacity::get()
{
	return ((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->capacity();
}

int AlignedCollisionObjectArray::Count::get()
{
	return ((btAlignedObjectArray<btCollisionShape*>*)_unmanaged)->size();
}

CollisionObject^ AlignedCollisionObjectArray::default::get(int index)
{
	if (index < 0 || index >= ((btCollisionObjectArray*)_unmanaged)->size())
		throw gcnew ArgumentOutOfRangeException("index");

	return CollisionObject::GetManaged((*((btCollisionObjectArray*)_unmanaged))[index]);
}
void AlignedCollisionObjectArray::default::set(int index, CollisionObject^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*(btCollisionObjectArray*)_unmanaged)[index] = GetUnmanagedNullable(value);
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
	((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->push_back(node->UnmanagedPointer);
}

void AlignedDbvtNodeArray::Clear()
{
	((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->clear();
}

bool AlignedDbvtNodeArray::Contains(DbvtNode^ node)
{
	return ((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->findLinearSearch(node->UnmanagedPointer)
		!= ((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->size();
}

void AlignedDbvtNodeArray::CopyTo(array<DbvtNode^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew DbvtNode((btDbvtNode*)(*(btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)[i]);
	}
}

int AlignedDbvtNodeArray::IndexOf(DbvtNode^ node)
{
	int i = ((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->findLinearSearch(node->UnmanagedPointer);
	return i != ((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->size() ? i : -1;
}

void AlignedDbvtNodeArray::PopBack()
{
	((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->pop_back();
}

bool AlignedDbvtNodeArray::Remove(DbvtNode^ node)
{
	int sizeBefore = ((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->size();
	((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->remove(node->UnmanagedPointer);
	return sizeBefore != ((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->size();
}

int AlignedDbvtNodeArray::Capacity::get()
{
	return ((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->capacity();
}

int AlignedDbvtNodeArray::Count::get()
{
	return ((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->size();
}

void AlignedDbvtNodeArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged)->swap(index0, index1);
}

DbvtNode^ AlignedDbvtNodeArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btDbvtNode* obj = (btDbvtNode*)(*((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged))[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew DbvtNode(obj);
}
void AlignedDbvtNodeArray::default::set(int index, DbvtNode^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*((btAlignedObjectArray<const btDbvtNode*>*)_unmanaged))[index] = GetUnmanagedNullable(value);
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
	((btAlignedObjectArray<btDbvt::sStkNN>*)_unmanaged)->push_back(*stkNn->UnmanagedPointer);
}

void AlignedStkNnArray::Clear()
{
	((btAlignedObjectArray<btDbvt::sStkNN>*)_unmanaged)->clear();
}

void AlignedStkNnArray::CopyTo(array<Dbvt::StkNn^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<btDbvt::sStkNN>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Dbvt::StkNn(&(*((btAlignedObjectArray<btDbvt::sStkNN>*)_unmanaged))[i]);
	}
}

void AlignedStkNnArray::PopBack()
{
	((btAlignedObjectArray<btDbvt::sStkNN>*)_unmanaged)->pop_back();
}

void AlignedStkNnArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<btDbvt::sStkNN>*)_unmanaged)->swap(index0, index1);
}

int AlignedStkNnArray::Capacity::get()
{
	return ((btAlignedObjectArray<btDbvt::sStkNN>*)_unmanaged)->capacity();
}

int AlignedStkNnArray::Count::get()
{
	return ((btAlignedObjectArray<btDbvt::sStkNN>*)_unmanaged)->size();
}

void StkNnArray_GetDefault(btAlignedObjectArray<btDbvt::sStkNN>* stkNnArray,
	int index, btDbvt::sStkNN* obj)
{
	*obj = (*stkNnArray)[index];
}
Dbvt::StkNn^ AlignedStkNnArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btDbvt::sStkNN* obj = new btDbvt::sStkNN;
	StkNnArray_GetDefault(((btAlignedObjectArray<btDbvt::sStkNN>*)_unmanaged), index, obj);
	return gcnew Dbvt::StkNn(obj);
}

void AlignedStkNnArray::default::set(int index, Dbvt::StkNn^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*(btAlignedObjectArray<btDbvt::sStkNN>*)_unmanaged)[index] = *value->UnmanagedPointer;
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
	((btAlignedObjectArray<btDbvt::sStkNPS>*)_unmanaged)->push_back(*stkNps->UnmanagedPointer);
}

void AlignedStkNpsArray::Clear()
{
	((btAlignedObjectArray<btDbvt::sStkNPS>*)_unmanaged)->clear();
}

void AlignedStkNpsArray::CopyTo(array<Dbvt::StkNps^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<btDbvt::sStkNPS>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Dbvt::StkNps(&(*((btAlignedObjectArray<btDbvt::sStkNPS>*)_unmanaged))[i]);
	}
}

void AlignedStkNpsArray::PopBack()
{
	((btAlignedObjectArray<btDbvt::sStkNPS>*)_unmanaged)->pop_back();
}

void AlignedStkNpsArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<btDbvt::sStkNPS>*)_unmanaged)->swap(index0, index1);
}

int AlignedStkNpsArray::Capacity::get()
{
	return ((btAlignedObjectArray<btDbvt::sStkNPS>*)_unmanaged)->capacity();
}

int AlignedStkNpsArray::Count::get()
{
	return ((btAlignedObjectArray<btDbvt::sStkNPS>*)_unmanaged)->size();
}

void StkNpsArray_GetDefault(btAlignedObjectArray<btDbvt::sStkNPS>* stkNpsArray,
	int index, btDbvt::sStkNPS* obj)
{
	*obj = (*stkNpsArray)[index];
}
Dbvt::StkNps^ AlignedStkNpsArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btDbvt::sStkNPS* obj = new btDbvt::sStkNPS;
	StkNpsArray_GetDefault(((btAlignedObjectArray<btDbvt::sStkNPS>*)_unmanaged), index, obj);
	return gcnew Dbvt::StkNps(obj);
}

void AlignedStkNpsArray::default::set(int index, Dbvt::StkNps^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*((btAlignedObjectArray<btDbvt::sStkNPS>*)_unmanaged))[index] = *value->UnmanagedPointer;
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
	((btAlignedObjectArray<btSoftBody::Face>*)_unmanaged)->push_back((btSoftBody::Face&)*face->_unmanaged);
}

void AlignedFaceArray::Clear()
{
	((btAlignedObjectArray<btSoftBody::Face>*)_unmanaged)->clear();
}

void AlignedFaceArray::CopyTo(array<Face^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<btSoftBody::Face>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Face(&(*((btAlignedObjectArray<btSoftBody::Face>*)_unmanaged))[i]);
	}
}

void AlignedFaceArray::PopBack()
{
	((btAlignedObjectArray<btSoftBody::Face>*)_unmanaged)->pop_back();
}

void AlignedFaceArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<btSoftBody::Face>*)_unmanaged)->swap(index0, index1);
}

int AlignedFaceArray::Capacity::get()
{
	return ((btAlignedObjectArray<btSoftBody::Face>*)_unmanaged)->capacity();
}

int AlignedFaceArray::Count::get()
{
	return ((btAlignedObjectArray<btSoftBody::Face>*)_unmanaged)->size();
}

Face^ AlignedFaceArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Face(&(*((btAlignedObjectArray<btSoftBody::Face>*)_unmanaged))[index]);
}

void FaceArray_SetDefault(btAlignedObjectArray<btSoftBody::Face>* faceArray,
	int index, btSoftBody::Face* node)
{
	(*faceArray)[index] = *node;
}
void AlignedFaceArray::default::set(int index, Face^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	FaceArray_SetDefault((btAlignedObjectArray<btSoftBody::Face>*)_unmanaged, index, (btSoftBody::Face*)value->_unmanaged);
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

void AlignedIntArray::Add(int integer)
{
	((btAlignedObjectArray<int>*)_unmanaged)->push_back(integer);
}

void AlignedIntArray::Clear()
{
	((btAlignedObjectArray<int>*)_unmanaged)->clear();
}

bool AlignedIntArray::Contains(int integer)
{
	return ((btAlignedObjectArray<int>*)_unmanaged)->findLinearSearch(integer)
		!= ((btAlignedObjectArray<int>*)_unmanaged)->size();
}

void AlignedIntArray::CopyTo(array<int>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<int>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (*((btAlignedObjectArray<int>*)_unmanaged))[i];
	}
}

int AlignedIntArray::IndexOf(int integer)
{
	int i = ((btAlignedObjectArray<int>*)_unmanaged)->findLinearSearch(integer);
	return i != ((btAlignedObjectArray<int>*)_unmanaged)->size() ? i : -1;
}

void AlignedIntArray::PopBack()
{
	((btAlignedObjectArray<int>*)_unmanaged)->pop_back();
}

bool AlignedIntArray::Remove(int integer)
{
	int sizeBefore = ((btAlignedObjectArray<int>*)_unmanaged)->size();
	((btAlignedObjectArray<int>*)_unmanaged)->remove(integer);
	return sizeBefore != ((btAlignedObjectArray<int>*)_unmanaged)->size();
}

void AlignedIntArray::Resize(int newSize)
{
	((btAlignedObjectArray<int>*)_unmanaged)->resize(newSize);
}

void AlignedIntArray::Resize(int newSize, int fillData)
{
	((btAlignedObjectArray<int>*)_unmanaged)->resize(newSize, fillData);
}

void AlignedIntArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<int>*)_unmanaged)->swap(index0, index1);
}

int AlignedIntArray::Capacity::get()
{
	return ((btAlignedObjectArray<int>*)_unmanaged)->capacity();
}

int AlignedIntArray::Count::get()
{
	return ((btAlignedObjectArray<int>*)_unmanaged)->size();
}

int AlignedIntArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (*((btAlignedObjectArray<int>*)_unmanaged))[index];
}
void AlignedIntArray::default::set(int index, int value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*((btAlignedObjectArray<int>*)_unmanaged))[index] = value;
}


#ifndef DISABLE_SOFTBODY
AlignedJointArray::AlignedJointArray(btSoftBody::tJointArray* jointArray)
: AlignedObjectArray(jointArray)
{
}

AlignedJointArray::AlignedJointArray()
: AlignedObjectArray(new btSoftBody::tLinkArray())
{
}

void AlignedJointArray::Add(BulletSharp::SoftBody::Joint^ joint)
{
	((btSoftBody::tJointArray*)_unmanaged)->push_back(joint->UnmanagedPointer);
}

void AlignedJointArray::Clear()
{
	((btSoftBody::tJointArray*)_unmanaged)->clear();
}

bool AlignedJointArray::Contains(Joint^ joint)
{
	return ((btSoftBody::tJointArray*)_unmanaged)->findLinearSearch(joint->UnmanagedPointer)
		!= ((btSoftBody::tJointArray*)_unmanaged)->size();
}

void AlignedJointArray::CopyTo(array<Joint^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tJointArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = default[i];
	}
}

void AlignedJointArray::PopBack()
{
	((btSoftBody::tJointArray*)_unmanaged)->pop_back();
}

int AlignedJointArray::Capacity::get()
{
	return ((btSoftBody::tJointArray*)_unmanaged)->capacity();
}

int AlignedJointArray::Count::get()
{
	return ((btSoftBody::tJointArray*)_unmanaged)->size();
}

int AlignedJointArray::IndexOf(Joint^ joint)
{
	int i = ((btSoftBody::tJointArray*)_unmanaged)->findLinearSearch(joint->UnmanagedPointer);
	return i != ((btSoftBody::tJointArray*)_unmanaged)->size() ? i : -1;
}

bool AlignedJointArray::Remove(Joint^ joint)
{
	int sizeBefore = ((btSoftBody::tJointArray*)_unmanaged)->size();
	((btSoftBody::tJointArray*)_unmanaged)->remove(joint->UnmanagedPointer);
	return sizeBefore != ((btSoftBody::tJointArray*)_unmanaged)->size();
}

void AlignedJointArray::Swap(int index0, int index1)
{
	((btSoftBody::tJointArray*)_unmanaged)->swap(index0, index1);
}

BulletSharp::SoftBody::Joint^ AlignedJointArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btSoftBody::Joint* j = (*((btSoftBody::tJointArray*)_unmanaged))[index];
	switch(j->Type())
	{
	case btSoftBody::Joint::eType::Linear:
		return gcnew LJoint((btSoftBody::LJoint*)j);
	case btSoftBody::Joint::eType::Angular:
		return gcnew AJoint((btSoftBody::AJoint*)j);
	case btSoftBody::Joint::eType::Contact:
		return gcnew CJoint((btSoftBody::CJoint*)j);
	};
	return gcnew Joint(j);
}

void AlignedJointArray_SetDefault(btSoftBody::tJointArray* jointArray,
	int index, btSoftBody::Joint* link)
{
	(*jointArray)[index] = link;
}
void AlignedJointArray::default::set(int index, BulletSharp::SoftBody::Joint^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedJointArray_SetDefault(((btSoftBody::tJointArray*)_unmanaged), index, GetUnmanagedNullable(value));
}
#endif


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
	((btManifoldArray*)_unmanaged)->push_back(manifold->UnmanagedPointer);
}

void AlignedManifoldArray::Clear()
{
	((btManifoldArray*)_unmanaged)->clear();
}

bool AlignedManifoldArray::Contains(PersistentManifold^ manifold)
{
	return ((btManifoldArray*)_unmanaged)->findLinearSearch(manifold->UnmanagedPointer)
		!= ((btManifoldArray*)_unmanaged)->size();
}

void AlignedManifoldArray::CopyTo(array<PersistentManifold^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btManifoldArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew PersistentManifold((*(btManifoldArray*)_unmanaged)[i]);
	}
}

int AlignedManifoldArray::IndexOf(PersistentManifold^ manifold)
{
	int i = ((btManifoldArray*)_unmanaged)->findLinearSearch(manifold->UnmanagedPointer);
	return i != ((btManifoldArray*)_unmanaged)->size() ? i : -1;
}

void AlignedManifoldArray::PopBack()
{
	((btManifoldArray*)_unmanaged)->pop_back();
}

bool AlignedManifoldArray::Remove(PersistentManifold^ manifold)
{
	int sizeBefore = ((btManifoldArray*)_unmanaged)->size();
	((btManifoldArray*)_unmanaged)->remove(manifold->UnmanagedPointer);
	return sizeBefore != ((btManifoldArray*)_unmanaged)->size();
}

int AlignedManifoldArray::Capacity::get()
{
	return ((btManifoldArray*)_unmanaged)->capacity();
}

int AlignedManifoldArray::Count::get()
{
	return ((btManifoldArray*)_unmanaged)->size();
}

void AlignedManifoldArray::Swap(int index0, int index1)
{
	((btManifoldArray*)_unmanaged)->swap(index0, index1);
}

PersistentManifold^ AlignedManifoldArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btPersistentManifold* obj = (*((btManifoldArray*)_unmanaged))[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew PersistentManifold(obj);
}
void AlignedManifoldArray::default::set(int index, PersistentManifold^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*((btManifoldArray*)_unmanaged))[index] = GetUnmanagedNullable(value);
}


AlignedIndexedMeshArray::AlignedIndexedMeshArray(btAlignedObjectArray<btIndexedMesh>* indexedMeshArray)
: AlignedObjectArray(indexedMeshArray)
{
}

AlignedIndexedMeshArray::AlignedIndexedMeshArray()
: AlignedObjectArray(new btAlignedObjectArray<btIndexedMesh>())
{
}

void AlignedIndexedMeshArray::Add(IndexedMesh^ indexedMesh)
{
	((btAlignedObjectArray<btIndexedMesh>*)_unmanaged)->push_back(*indexedMesh->UnmanagedPointer);
}

void AlignedIndexedMeshArray::Clear()
{
	((btAlignedObjectArray<btIndexedMesh>*)_unmanaged)->clear();
}

void AlignedIndexedMeshArray::CopyTo(array<IndexedMesh^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<btIndexedMesh>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew IndexedMesh(&(*((btAlignedObjectArray<btIndexedMesh>*)_unmanaged))[i]);
	}
}

void AlignedIndexedMeshArray::PopBack()
{
	((btAlignedObjectArray<btIndexedMesh>*)_unmanaged)->pop_back();
}

int AlignedIndexedMeshArray::Capacity::get()
{
	return ((btAlignedObjectArray<btIndexedMesh>*)_unmanaged)->capacity();
}

int AlignedIndexedMeshArray::Count::get()
{
	return ((btAlignedObjectArray<btIndexedMesh>*)_unmanaged)->size();
}

void AlignedIndexedMeshArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<btIndexedMesh>*)_unmanaged)->swap(index0, index1);
}

IndexedMesh^ AlignedIndexedMeshArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btIndexedMesh* obj = &(*((btAlignedObjectArray<btIndexedMesh>*)_unmanaged))[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew IndexedMesh(obj);
}

void AlignedIndexedMeshArray_SetDefault(btAlignedObjectArray<btIndexedMesh>* indexedMeshArray,
	int index, btIndexedMesh* mesh)
{
	(*indexedMeshArray)[index] = *mesh;
}
void AlignedIndexedMeshArray::default::set(int index, IndexedMesh^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedIndexedMeshArray_SetDefault(((btAlignedObjectArray<btIndexedMesh>*)_unmanaged), index, value->UnmanagedPointer);
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
	((btSoftBody::tLinkArray*)_unmanaged)->push_back((btSoftBody::Link&)*link->_unmanaged);
}

void AlignedLinkArray::Clear()
{
	((btSoftBody::tLinkArray*)_unmanaged)->clear();
}

void AlignedLinkArray::CopyTo(array<Link^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tLinkArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Link(&(*((btSoftBody::tLinkArray*)_unmanaged))[i]);
	}
}

void AlignedLinkArray::PopBack()
{
	((btSoftBody::tLinkArray*)_unmanaged)->pop_back();
}

int AlignedLinkArray::Capacity::get()
{
	return ((btSoftBody::tLinkArray*)_unmanaged)->capacity();
}

int AlignedLinkArray::Count::get()
{
	return ((btSoftBody::tLinkArray*)_unmanaged)->size();
}

void AlignedLinkArray::Swap(int index0, int index1)
{
	((btSoftBody::tLinkArray*)_unmanaged)->swap(index0, index1);
}

BulletSharp::SoftBody::Link^ AlignedLinkArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Link(&(*((btSoftBody::tLinkArray*)_unmanaged))[index]);
}

void AlignedLinkArray_SetDefault(btSoftBody::tLinkArray* linkArray,
	int index, btSoftBody::Link* link)
{
	(*linkArray)[index] = *link;
}
void AlignedLinkArray::default::set(int index, BulletSharp::SoftBody::Link^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedLinkArray_SetDefault(((btSoftBody::tLinkArray*)_unmanaged), index, (btSoftBody::Link*)GetUnmanagedNullableNew(value));
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
	((btSoftBody::tMaterialArray*)_unmanaged)->push_back((btSoftBody::Material*)material->_unmanaged);
}

void AlignedMaterialArray::Clear()
{
	((btSoftBody::tMaterialArray*)_unmanaged)->clear();
}

bool AlignedMaterialArray::Contains(BulletSharp::SoftBody::Material^ material)
{
	return ((btSoftBody::tMaterialArray*)_unmanaged)->findLinearSearch((btSoftBody::Material*)material->_unmanaged)
		!= ((btSoftBody::tMaterialArray*)_unmanaged)->size();
}

void AlignedMaterialArray::CopyTo(array<BulletSharp::SoftBody::Material^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tMaterialArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Material((*((btSoftBody::tMaterialArray*)_unmanaged))[i]);
	}
}

int AlignedMaterialArray::IndexOf(BulletSharp::SoftBody::Material^ material)
{
	int i = ((btSoftBody::tMaterialArray*)_unmanaged)->findLinearSearch((btSoftBody::Material*)material->_unmanaged);
	return i != ((btSoftBody::tMaterialArray*)_unmanaged)->size() ? i : -1;
}

void AlignedMaterialArray::PopBack()
{
	((btSoftBody::tMaterialArray*)_unmanaged)->pop_back();
}

bool AlignedMaterialArray::Remove(BulletSharp::SoftBody::Material^ material)
{
	int sizeBefore = ((btSoftBody::tMaterialArray*)_unmanaged)->size();
	((btSoftBody::tMaterialArray*)_unmanaged)->remove((btSoftBody::Material*)material->_unmanaged);
	return sizeBefore != ((btSoftBody::tMaterialArray*)_unmanaged)->size();
}

int AlignedMaterialArray::Capacity::get()
{
	return ((btSoftBody::tMaterialArray*)_unmanaged)->capacity();
}

int AlignedMaterialArray::Count::get()
{
	return ((btSoftBody::tMaterialArray*)_unmanaged)->size();
}

void AlignedMaterialArray::Swap(int index0, int index1)
{
	((btSoftBody::tMaterialArray*)_unmanaged)->swap(index0, index1);
}

BulletSharp::SoftBody::Material^ AlignedMaterialArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Material((*((btSoftBody::tMaterialArray*)_unmanaged))[index]);
}
void AlignedMaterialArray::default::set(int index, BulletSharp::SoftBody::Material^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*((btSoftBody::tMaterialArray*)_unmanaged))[index] = (btSoftBody::Material*)GetUnmanagedNullableNew(value);
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
	((btSoftBody::tNodeArray*)_unmanaged)->push_back((btSoftBody::Node&)*node->_unmanaged);
}

void BulletSharp::SoftBody::AlignedNodeArray::Clear()
{
	((btSoftBody::tNodeArray*)_unmanaged)->clear();
}

void BulletSharp::SoftBody::AlignedNodeArray::CopyTo(array<Node^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tNodeArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Node(&(*((btSoftBody::tNodeArray*)_unmanaged))[i]);
	}
}

void BulletSharp::SoftBody::AlignedNodeArray::PopBack()
{
	((btSoftBody::tNodeArray*)_unmanaged)->pop_back();
}

int BulletSharp::SoftBody::AlignedNodeArray::Capacity::get()
{
	return ((btSoftBody::tNodeArray*)_unmanaged)->capacity();
}

int BulletSharp::SoftBody::AlignedNodeArray::Count::get()
{
	return ((btSoftBody::tNodeArray*)_unmanaged)->size();
}

void BulletSharp::SoftBody::AlignedNodeArray::Swap(int index0, int index1)
{
	((btSoftBody::tNodeArray*)_unmanaged)->swap(index0, index1);
}

BulletSharp::SoftBody::Node^ BulletSharp::SoftBody::AlignedNodeArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Node(&(*((btSoftBody::tNodeArray*)_unmanaged))[index]);
}

void NodeArray_SetDefault(btSoftBody::tNodeArray* AlignedNodeArray, int index, btSoftBody::Node* node)
{
	(*AlignedNodeArray)[index] = *node;
}
void BulletSharp::SoftBody::AlignedNodeArray::default::set(int index, Node^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	NodeArray_SetDefault(((btSoftBody::tNodeArray*)_unmanaged), index, (btSoftBody::Node*)value->_unmanaged);
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
	((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->push_back((btSoftBody::Node*)node->_unmanaged);
}

void AlignedNodePtrArray::Clear()
{
	((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->clear();
}

bool AlignedNodePtrArray::Contains(BulletSharp::SoftBody::Node^ node)
{
	return ((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->findLinearSearch((btSoftBody::Node*)node->_unmanaged)
		!= ((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->size();
}

void AlignedNodePtrArray::CopyTo(array<BulletSharp::SoftBody::Node^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Node((*((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged))[i]);
	}
}

int AlignedNodePtrArray::IndexOf(BulletSharp::SoftBody::Node^ node)
{
	int i = ((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->findLinearSearch((btSoftBody::Node*)node->_unmanaged);
	return i != ((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->size() ? i : -1;
}

void AlignedNodePtrArray::PopBack()
{
	((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->pop_back();
}

bool AlignedNodePtrArray::Remove(BulletSharp::SoftBody::Node^ node)
{
	int sizeBefore = ((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->size();
	((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->remove((btSoftBody::Node*)node->_unmanaged);
	return sizeBefore != ((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->size();
}

int AlignedNodePtrArray::Capacity::get()
{
	return ((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->capacity();
}

int AlignedNodePtrArray::Count::get()
{
	return ((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->size();
}

void AlignedNodePtrArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged)->swap(index0, index1);
}

BulletSharp::SoftBody::Node^ AlignedNodePtrArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Node((*((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged))[index]);
}
void AlignedNodePtrArray::default::set(int index, BulletSharp::SoftBody::Node^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*((btAlignedObjectArray<btSoftBody::Node*>*)_unmanaged))[index] = (btSoftBody::Node*)GetUnmanagedNullableNew(value);
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
	((btSoftBody::tNoteArray*)_unmanaged)->push_back((btSoftBody::Note&)*note->_unmanaged);
}

void AlignedNoteArray::Clear()
{
	((btSoftBody::tNoteArray*)_unmanaged)->clear();
}

void AlignedNoteArray::CopyTo(array<Note^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tNoteArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Note(&(*((btSoftBody::tNoteArray*)_unmanaged))[i]);
	}
}

void AlignedNoteArray::PopBack()
{
	((btSoftBody::tNoteArray*)_unmanaged)->pop_back();
}

int AlignedNoteArray::Capacity::get()
{
	return ((btSoftBody::tNoteArray*)_unmanaged)->capacity();
}

int AlignedNoteArray::Count::get()
{
	return ((btSoftBody::tNoteArray*)_unmanaged)->size();
}

void AlignedNoteArray::Swap(int index0, int index1)
{
	((btSoftBody::tNoteArray*)_unmanaged)->swap(index0, index1);
}

BulletSharp::SoftBody::Note^ AlignedNoteArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Note(&(*((btSoftBody::tNoteArray*)_unmanaged))[index]);
}

void NoteArray_SetDefault(btSoftBody::tNoteArray* noteArray, int index, btSoftBody::Note* note)
{
	(*noteArray)[index] = *note;
}
void AlignedNoteArray::default::set(int index, Note^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	NoteArray_SetDefault(((btSoftBody::tNoteArray*)_unmanaged), index, (btSoftBody::Note*)GetUnmanagedNullableNew(value));
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
	((btSoftBody::tPSolverArray*)_unmanaged)->push_back((btSoftBody::ePSolver::_)solver);
}

void AlignedPSolverArray::Clear()
{
	((btSoftBody::tPSolverArray*)_unmanaged)->clear();
}

bool AlignedPSolverArray::Contains(PSolver solver)
{
	return ((btSoftBody::tPSolverArray*)_unmanaged)->findLinearSearch((btSoftBody::ePSolver::_)solver)
		!= ((btSoftBody::tPSolverArray*)_unmanaged)->size();
}

void AlignedPSolverArray::CopyTo(array<PSolver>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tPSolverArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (PSolver)(*((btSoftBody::tPSolverArray*)_unmanaged))[i];
	}
}

int AlignedPSolverArray::IndexOf(PSolver solver)
{
	int i = ((btSoftBody::tPSolverArray*)_unmanaged)->findLinearSearch((btSoftBody::ePSolver::_)solver);
	return i != ((btSoftBody::tPSolverArray*)_unmanaged)->size() ? i : -1;
}

void AlignedPSolverArray::PopBack()
{
	((btSoftBody::tPSolverArray*)_unmanaged)->pop_back();
}

bool AlignedPSolverArray::Remove(PSolver solver)
{
	int sizeBefore = ((btSoftBody::tPSolverArray*)_unmanaged)->size();
	((btSoftBody::tPSolverArray*)_unmanaged)->remove((btSoftBody::ePSolver::_)solver);
	return sizeBefore != ((btSoftBody::tPSolverArray*)_unmanaged)->size();
}

int AlignedPSolverArray::Capacity::get()
{
	return ((btSoftBody::tPSolverArray*)_unmanaged)->capacity();
}

int AlignedPSolverArray::Count::get()
{
	return ((btSoftBody::tPSolverArray*)_unmanaged)->size();
}

void AlignedPSolverArray::Swap(int index0, int index1)
{
	((btSoftBody::tPSolverArray*)_unmanaged)->swap(index0, index1);
}

PSolver AlignedPSolverArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (PSolver)(*((btSoftBody::tPSolverArray*)_unmanaged))[index];
}
void AlignedPSolverArray::default::set(int index, PSolver value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*((btSoftBody::tPSolverArray*)_unmanaged))[index] = (btSoftBody::ePSolver::_)value;
}


AlignedRigidContactArray::AlignedRigidContactArray(btSoftBody::tRContactArray* rigidContactArray)
: AlignedObjectArray(rigidContactArray)
{
}

AlignedRigidContactArray::AlignedRigidContactArray()
: AlignedObjectArray(new btSoftBody::tRContactArray())
{
}

void AlignedRigidContactArray::Add(RigidContact^ rigidContact)
{
	((btSoftBody::tRContactArray*)_unmanaged)->push_back(*rigidContact->UnmanagedPointer);
}

void AlignedRigidContactArray::Clear()
{
	((btSoftBody::tRContactArray*)_unmanaged)->clear();
}

void AlignedRigidContactArray::CopyTo(array<RigidContact^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tRContactArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew RigidContact(&(*((btSoftBody::tRContactArray*)_unmanaged))[i]);
	}
}

void AlignedRigidContactArray::PopBack()
{
	((btSoftBody::tRContactArray*)_unmanaged)->pop_back();
}

void AlignedRigidContactArray::Swap(int index0, int index1)
{
	((btSoftBody::tRContactArray*)_unmanaged)->swap(index0, index1);
}

int AlignedRigidContactArray::Capacity::get()
{
	return ((btSoftBody::tRContactArray*)_unmanaged)->capacity();
}

int AlignedRigidContactArray::Count::get()
{
	return ((btSoftBody::tRContactArray*)_unmanaged)->size();
}

BulletSharp::SoftBody::RigidContact^ AlignedRigidContactArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew RigidContact(&(*((btSoftBody::tRContactArray*)_unmanaged))[index]);
}

void AlignedRigidContactArray_SetDefault(btSoftBody::tRContactArray* rigidContactArray,
	int index, btSoftBody::RContact* rigidContact)
{
	(*rigidContactArray)[index] = *rigidContact;
}
void AlignedRigidContactArray::default::set(int index, RigidContact^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedRigidContactArray_SetDefault(((btSoftBody::tRContactArray*)_unmanaged), index, value->UnmanagedPointer);
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
	((btAlignedObjectArray<btScalar>*)_unmanaged)->push_back(intValue);
}

void AlignedScalarArray::Clear()
{
	((btAlignedObjectArray<btScalar>*)_unmanaged)->clear();
}

bool AlignedScalarArray::Contains(btScalar scalar)
{
	return ((btAlignedObjectArray<btScalar>*)_unmanaged)->findLinearSearch(scalar)
		!= ((btAlignedObjectArray<btScalar>*)_unmanaged)->size();
}

void AlignedScalarArray::CopyTo(array<btScalar>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<btScalar>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (*((btAlignedObjectArray<btScalar>*)_unmanaged))[i];
	}
}

int AlignedScalarArray::IndexOf(btScalar scalar)
{
	int i = ((btAlignedObjectArray<btScalar>*)_unmanaged)->findLinearSearch(scalar);
	return i != ((btAlignedObjectArray<btScalar>*)_unmanaged)->size() ? i : -1;
}

void AlignedScalarArray::PopBack()
{
	((btAlignedObjectArray<btScalar>*)_unmanaged)->pop_back();
}

bool AlignedScalarArray::Remove(btScalar scalar)
{
	int sizeBefore = ((btAlignedObjectArray<btScalar>*)_unmanaged)->size();
	((btAlignedObjectArray<btScalar>*)_unmanaged)->remove(scalar);
	return sizeBefore != ((btAlignedObjectArray<btScalar>*)_unmanaged)->size();
}

int AlignedScalarArray::Capacity::get()
{
	return ((btAlignedObjectArray<btScalar>*)_unmanaged)->capacity();
}

int AlignedScalarArray::Count::get()
{
	return ((btAlignedObjectArray<btScalar>*)_unmanaged)->size();
}

void AlignedScalarArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<btScalar>*)_unmanaged)->swap(index0, index1);
}

btScalar AlignedScalarArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (*((btAlignedObjectArray<btScalar>*)_unmanaged))[index];
}
void AlignedScalarArray::default::set(int index, btScalar value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*((btAlignedObjectArray<btScalar>*)_unmanaged))[index] = value;
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
	((btSoftBody::tSoftBodyArray*)_unmanaged)->push_back(softBody->UnmanagedPointer);
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::Clear()
{
	((btSoftBody::tSoftBodyArray*)_unmanaged)->clear();
}

bool BulletSharp::SoftBody::AlignedSoftBodyArray::Contains(SoftBody^ softBody)
{
	return ((btSoftBody::tSoftBodyArray*)_unmanaged)->findLinearSearch(softBody->UnmanagedPointer)
		!= ((btSoftBody::tSoftBodyArray*)_unmanaged)->size();
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::CopyTo(array<SoftBody^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tSoftBodyArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (SoftBody^)CollisionObject::GetManaged((*((btSoftBody::tSoftBodyArray*)_unmanaged))[i]);
	}
}

int BulletSharp::SoftBody::AlignedSoftBodyArray::IndexOf(SoftBody^ softBody)
{
	int i = ((btSoftBody::tSoftBodyArray*)_unmanaged)->findLinearSearch(softBody->UnmanagedPointer);
	return i != ((btSoftBody::tSoftBodyArray*)_unmanaged)->size() ? i : -1;
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::PopBack()
{
	((btSoftBody::tSoftBodyArray*)_unmanaged)->pop_back();
}

bool BulletSharp::SoftBody::AlignedSoftBodyArray::Remove(SoftBody^ softBody)
{
	int sizeBefore = ((btSoftBody::tSoftBodyArray*)_unmanaged)->size();
	((btSoftBody::tSoftBodyArray*)_unmanaged)->remove(softBody->UnmanagedPointer);
	return sizeBefore != ((btSoftBody::tSoftBodyArray*)_unmanaged)->size();
}

int BulletSharp::SoftBody::AlignedSoftBodyArray::Capacity::get()
{
	return ((btSoftBody::tSoftBodyArray*)_unmanaged)->capacity();
}

int BulletSharp::SoftBody::AlignedSoftBodyArray::Count::get()
{
	return ((btSoftBody::tSoftBodyArray*)_unmanaged)->size();
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::Swap(int index0, int index1)
{
	((btSoftBody::tSoftBodyArray*)_unmanaged)->swap(index0, index1);
}

BulletSharp::SoftBody::SoftBody^ BulletSharp::SoftBody::AlignedSoftBodyArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (SoftBody^)CollisionObject::GetManaged((*((btSoftBody::tSoftBodyArray*)_unmanaged))[index]);
}
void BulletSharp::SoftBody::AlignedSoftBodyArray::default::set(int index, SoftBody^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*((btSoftBody::tSoftBodyArray*)_unmanaged))[index] = GetUnmanagedNullable(value);
}


AlignedSoftContactArray::AlignedSoftContactArray(btSoftBody::tSContactArray* softContactArray)
: AlignedObjectArray(softContactArray)
{
}

AlignedSoftContactArray::AlignedSoftContactArray()
: AlignedObjectArray(new btSoftBody::tSContactArray())
{
}

void AlignedSoftContactArray::Add(SoftContact^ softContact)
{
	((btSoftBody::tSContactArray*)_unmanaged)->push_back(*softContact->UnmanagedPointer);
}

void AlignedSoftContactArray::Clear()
{
	((btSoftBody::tSContactArray*)_unmanaged)->clear();
}

void AlignedSoftContactArray::CopyTo(array<SoftContact^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tSContactArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew SoftContact(&(*(btSoftBody::tSContactArray*)_unmanaged)[i]);
	}
}

void AlignedSoftContactArray::PopBack()
{
	((btSoftBody::tSContactArray*)_unmanaged)->pop_back();
}

void AlignedSoftContactArray::Swap(int index0, int index1)
{
	((btSoftBody::tSContactArray*)_unmanaged)->swap(index0, index1);
}

int AlignedSoftContactArray::Capacity::get()
{
	return ((btSoftBody::tSContactArray*)_unmanaged)->capacity();
}

int AlignedSoftContactArray::Count::get()
{
	return ((btSoftBody::tSContactArray*)_unmanaged)->size();
}

BulletSharp::SoftBody::SoftContact^ AlignedSoftContactArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew SoftContact(&(*(btSoftBody::tSContactArray*)_unmanaged)[index]);
}

void AlignedSoftContactArray_SetDefault(btSoftBody::tSContactArray* softContactArray,
	int index, btSoftBody::SContact* softContact)
{
	(*softContactArray)[index] = *softContact;
}
void AlignedSoftContactArray::default::set(int index, SoftContact^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedSoftContactArray_SetDefault((btSoftBody::tSContactArray*)_unmanaged, index, value->UnmanagedPointer);
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
	((btAlignedObjectArray<btSoftBody::Tetra>*)_unmanaged)->push_back((btSoftBody::Tetra&)*tetra->_unmanaged);
}

void AlignedTetraArray::Clear()
{
	((btAlignedObjectArray<btSoftBody::Tetra>*)_unmanaged)->clear();
}

void AlignedTetraArray::CopyTo(array<Tetra^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<btSoftBody::Tetra>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Tetra(&(*(btAlignedObjectArray<btSoftBody::Tetra>*)_unmanaged)[i]);
	}
}

void AlignedTetraArray::PopBack()
{
	((btAlignedObjectArray<btSoftBody::Tetra>*)_unmanaged)->pop_back();
}

void AlignedTetraArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<btSoftBody::Tetra>*)_unmanaged)->swap(index0, index1);
}

int AlignedTetraArray::Capacity::get()
{
	return ((btAlignedObjectArray<btSoftBody::Tetra>*)_unmanaged)->capacity();
}

int AlignedTetraArray::Count::get()
{
	return ((btAlignedObjectArray<btSoftBody::Tetra>*)_unmanaged)->size();
}

Tetra^ AlignedTetraArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Tetra(&(*(btAlignedObjectArray<btSoftBody::Tetra>*)_unmanaged)[index]);
}

void TetraArray_SetDefault(btAlignedObjectArray<btSoftBody::Tetra>* tetraArray,
	int index, btSoftBody::Tetra* node)
{
	(*tetraArray)[index] = *node;
}
void AlignedTetraArray::default::set(int index, Tetra^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	TetraArray_SetDefault((btAlignedObjectArray<btSoftBody::Tetra>*)_unmanaged, index, (btSoftBody::Tetra*)value->_unmanaged);
}
#endif


AlignedTriangleMeshArray::AlignedTriangleMeshArray(btAlignedObjectArray<btTriangleMesh*>* triangleMeshArray)
: AlignedObjectArray(triangleMeshArray)
{
}

AlignedTriangleMeshArray::AlignedTriangleMeshArray()
: AlignedObjectArray(new btAlignedObjectArray<btTriangleMesh*>)
{
}

void AlignedTriangleMeshArray::Add(TriangleMesh^ triangleMesh)
{
	((btAlignedObjectArray<btTriangleMesh*>*)_unmanaged)->push_back(triangleMesh->UnmanagedPointer);
}

void AlignedTriangleMeshArray::Clear()
{
	((btAlignedObjectArray<btTriangleMesh*>*)_unmanaged)->clear();
}

void AlignedTriangleMeshArray::CopyTo(array<TriangleMesh^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<btTriangleMesh>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew TriangleMesh(&(*(btAlignedObjectArray<btTriangleMesh*>*)_unmanaged)[i]);
	}
}

void AlignedTriangleMeshArray::PopBack()
{
	((btAlignedObjectArray<btTriangleMesh*>*)_unmanaged)->pop_back();
}

int AlignedTriangleMeshArray::Capacity::get()
{
	return ((btAlignedObjectArray<btTriangleMesh*>*)_unmanaged)->capacity();
}

int AlignedTriangleMeshArray::Count::get()
{
	return ((btAlignedObjectArray<btTriangleMesh*>*)_unmanaged)->size();
}

void AlignedTriangleMeshArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<btTriangleMesh*>*)_unmanaged)->swap(index0, index1);
}

TriangleMesh^ AlignedTriangleMeshArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew TriangleMesh(&(*(btAlignedObjectArray<btTriangleMesh>*)_unmanaged)[index]);
}

void AlignedTriangleMeshArray::default::set(int index, TriangleMesh^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*((btAlignedObjectArray<btTriangleMesh*>*)_unmanaged))[index] = GetUnmanagedNullable(value);
}


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
	((btAlignedObjectArray<btVector3>*)_unmanaged)->push_back(*tempVector3Value);
	delete tempVector3Value;
}

void AlignedVector3Array::Add(Vector4 vector4Value)
{
	btVector4* tempVector4Value = Math::Vector4ToBtVector4(vector4Value);
	((btAlignedObjectArray<btVector3>*)_unmanaged)->push_back(*tempVector4Value);
	delete tempVector4Value;
}

void AlignedVector3Array::Clear()
{
	((btAlignedObjectArray<btVector3>*)_unmanaged)->clear();
}

bool AlignedVector3Array::Contains(Vector3 vector)
{
	btVector3* vectorTemp = Math::Vector3ToBtVector3(vector);
	int i = ((btAlignedObjectArray<btVector3>*)_unmanaged)->findLinearSearch(*vectorTemp);
	delete vectorTemp;
	return i != ((btAlignedObjectArray<btVector3>*)_unmanaged)->size();
}

void AlignedVector3Array::CopyTo(array<Vector3>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<btVector3>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		Math::BtVector3ToVector3(&(*(btAlignedObjectArray<btVector3>*)_unmanaged)[i], array[arrayIndex+i]);
	}
}

int AlignedVector3Array::IndexOf(Vector3 vector)
{
	btVector3* vectorTemp = Math::Vector3ToBtVector3(vector);
	int i = ((btAlignedObjectArray<btVector3>*)_unmanaged)->findLinearSearch(*vectorTemp);
	delete vectorTemp;
	return i != ((btAlignedObjectArray<btVector3>*)_unmanaged)->size() ? i : -1;
}

void AlignedVector3Array::PopBack()
{
	((btAlignedObjectArray<btVector3>*)_unmanaged)->pop_back();
}

bool AlignedVector3Array::Remove(Vector3 vector)
{
	int sizeBefore = ((btAlignedObjectArray<btVector3>*)_unmanaged)->size();
	btVector3* vectorTemp = Math::Vector3ToBtVector3(vector);
	((btAlignedObjectArray<btVector3>*)_unmanaged)->remove(*vectorTemp);
	delete vectorTemp;
	return sizeBefore != ((btAlignedObjectArray<btVector3>*)_unmanaged)->size();
}

int AlignedVector3Array::Capacity::get()
{
	return ((btAlignedObjectArray<btVector3>*)_unmanaged)->capacity();
}

int AlignedVector3Array::Count::get()
{
	return ((btAlignedObjectArray<btVector3>*)_unmanaged)->size();
}

void AlignedVector3Array::Swap(int index0, int index1)
{
	((btAlignedObjectArray<btVector3>*)_unmanaged)->swap(index0, index1);
}

Vector3 AlignedVector3Array::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return Math::BtVector3ToVector3(&(*(btAlignedObjectArray<btVector3>*)_unmanaged)[index]);
}
void AlignedVector3Array::default::set(int index, Vector3 value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	Math::Vector3ToBtVector3(value, &(*(btAlignedObjectArray<btVector3>*)_unmanaged)[index]);
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
	((btSoftBody::tVSolverArray*)_unmanaged)->push_back((btSoftBody::eVSolver::_)solver);
}

void AlignedVSolverArray::Clear()
{
	((btSoftBody::tVSolverArray*)_unmanaged)->clear();
}

bool AlignedVSolverArray::Contains(VSolver solver)
{
	return ((btSoftBody::tVSolverArray*)_unmanaged)->findLinearSearch((btSoftBody::eVSolver::_)solver)
		!= ((btSoftBody::tVSolverArray*)_unmanaged)->size();
}

void AlignedVSolverArray::CopyTo(array<VSolver>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btSoftBody::tVSolverArray*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (VSolver)(*(btSoftBody::tVSolverArray*)_unmanaged)[i];
	}
}

int AlignedVSolverArray::IndexOf(VSolver solver)
{
	int i = ((btSoftBody::tVSolverArray*)_unmanaged)->findLinearSearch((btSoftBody::eVSolver::_)solver);
	return i != ((btSoftBody::tVSolverArray*)_unmanaged)->size() ? i : -1;
}

void AlignedVSolverArray::PopBack()
{
	((btSoftBody::tVSolverArray*)_unmanaged)->pop_back();
}

bool AlignedVSolverArray::Remove(VSolver solver)
{
	int sizeBefore = ((btSoftBody::tVSolverArray*)_unmanaged)->size();
	((btSoftBody::tVSolverArray*)_unmanaged)->remove((btSoftBody::eVSolver::_)solver);
	return sizeBefore != ((btSoftBody::tVSolverArray*)_unmanaged)->size();
}

int AlignedVSolverArray::Capacity::get()
{
	return ((btSoftBody::tVSolverArray*)_unmanaged)->capacity();
}

int AlignedVSolverArray::Count::get()
{
	return ((btSoftBody::tVSolverArray*)_unmanaged)->size();
}

void AlignedVSolverArray::Swap(int index0, int index1)
{
	((btSoftBody::tVSolverArray*)_unmanaged)->swap(index0, index1);
}

VSolver AlignedVSolverArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (VSolver)(*(btSoftBody::tVSolverArray*)_unmanaged)[index];
}
void AlignedVSolverArray::default::set(int index, VSolver value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*(btSoftBody::tVSolverArray*)_unmanaged)[index] = (btSoftBody::eVSolver::_)value;
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
	((btAlignedObjectArray<btWheelInfo>*)_unmanaged)->push_back(*wheelInfo->UnmanagedPointer);
}

void AlignedWheelInfoArray::Clear()
{
	((btAlignedObjectArray<btWheelInfo>*)_unmanaged)->clear();
}

void AlignedWheelInfoArray::CopyTo(array<WheelInfo^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = ((btAlignedObjectArray<btWheelInfo>*)_unmanaged)->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew WheelInfo(&(*(btAlignedObjectArray<btWheelInfo>*)_unmanaged)[i]);
	}
}

void AlignedWheelInfoArray::PopBack()
{
	((btAlignedObjectArray<btWheelInfo>*)_unmanaged)->pop_back();
}

int AlignedWheelInfoArray::Capacity::get()
{
	return ((btAlignedObjectArray<btWheelInfo>*)_unmanaged)->capacity();
}

int AlignedWheelInfoArray::Count::get()
{
	return ((btAlignedObjectArray<btWheelInfo>*)_unmanaged)->size();
}

void AlignedWheelInfoArray::Swap(int index0, int index1)
{
	((btAlignedObjectArray<btWheelInfo>*)_unmanaged)->swap(index0, index1);
}

WheelInfo^ AlignedWheelInfoArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew WheelInfo(&(*(btAlignedObjectArray<btWheelInfo>*)_unmanaged)[index]);
}

void WheelInfoArray_SetDefault(btAlignedObjectArray<btWheelInfo>* wheelInfoArray,
	int index, btWheelInfo* node)
{
	(*wheelInfoArray)[index] = *node;
}
void AlignedWheelInfoArray::default::set(int index, WheelInfo^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	WheelInfoArray_SetDefault((btAlignedObjectArray<btWheelInfo>*)_unmanaged, index, value->UnmanagedPointer);
}
#endif
