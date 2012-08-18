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

#define Unmanaged (static_cast<btSoftBody::tAnchorArray*>(_unmanaged))

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
	Unmanaged->push_back(*anchor->_unmanaged);
}

void AlignedAnchorArray::Clear()
{
	Unmanaged->clear();
}

void AlignedAnchorArray::CopyTo(array<Anchor^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Anchor(&(*Unmanaged)[i]);
	}
}

void AlignedAnchorArray::PopBack()
{
	Unmanaged->pop_back();
}

void AlignedAnchorArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

int AlignedAnchorArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedAnchorArray::Count::get()
{
	return Unmanaged->size();
}

BulletSharp::SoftBody::Anchor^ AlignedAnchorArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Anchor(&Unmanaged->at(index));
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
	AlignedAnchorArray_SetDefault(Unmanaged, index, value->_unmanaged);
}
#endif


#undef Unmanaged
#define Unmanaged (static_cast<btBroadphasePairArray*>(_unmanaged))

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
	Unmanaged->push_back(*pair->UnmanagedPointer);
}

void AlignedBroadphasePairArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedBroadphasePairArray::Contains(BroadphasePair^ pair)
{
	return Unmanaged->findLinearSearch(*pair->UnmanagedPointer)
		!= Unmanaged->size();
}

void AlignedBroadphasePairArray::CopyTo(array<BroadphasePair^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew BroadphasePair(&Unmanaged->at(i));
	}
}

int AlignedBroadphasePairArray::IndexOf(BroadphasePair^ pair)
{
	int i = Unmanaged->findLinearSearch(*pair->UnmanagedPointer);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedBroadphasePairArray::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedBroadphasePairArray::Remove(BroadphasePair^ pair)
{
	int sizeBefore = Unmanaged->size();
	Unmanaged->remove(*pair->UnmanagedPointer);
	return sizeBefore != Unmanaged->size();
}

int AlignedBroadphasePairArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedBroadphasePairArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedBroadphasePairArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

BroadphasePair^ AlignedBroadphasePairArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew BroadphasePair(&Unmanaged->at(index));
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
	BroadphasePairList_SetDefault(Unmanaged, index, value->UnmanagedPointer);
}


#ifndef DISABLE_SOFTBODY

#undef Unmanaged
#define Unmanaged (static_cast<btSoftBody::tClusterArray*>(_unmanaged))

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
	btSoftBody::Cluster* clusterTemp = cluster->_unmanaged;
	Unmanaged->push_back(clusterTemp);
}

void AlignedClusterArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedClusterArray::Contains(Cluster^ cluster)
{
	btSoftBody::Cluster* clusterTemp = cluster->_unmanaged;
	return Unmanaged->findLinearSearch(clusterTemp)
		!= Unmanaged->size();
}

void AlignedClusterArray::CopyTo(array<Cluster^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Cluster(Unmanaged->at(i));
	}
}

int AlignedClusterArray::IndexOf(Cluster^ cluster)
{
	btSoftBody::Cluster* clusterTemp = cluster->_unmanaged;
	int i = Unmanaged->findLinearSearch(clusterTemp);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedClusterArray::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedClusterArray::Remove(Cluster^ cluster)
{
	int sizeBefore = Unmanaged->size();
	btSoftBody::Cluster* clusterTemp = cluster->_unmanaged;
	Unmanaged->remove(clusterTemp);
	return sizeBefore != Unmanaged->size();
}

void AlignedClusterArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

int AlignedClusterArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedClusterArray::Count::get()
{
	return Unmanaged->size();
}

BulletSharp::SoftBody::Cluster^ AlignedClusterArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Cluster((*Unmanaged)[index]);
}
void AlignedClusterArray::default::set(int index, Cluster^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = GetUnmanagedNullable(value);
}
#endif


#undef Unmanaged
#define Unmanaged (static_cast<btAlignedObjectArray<btCollisionShape*>*>(_unmanaged))

AlignedCollisionShapeArray::AlignedCollisionShapeArray()
: AlignedObjectArray(new btAlignedObjectArray<btCollisionShape*>())
{
}

void AlignedCollisionShapeArray::Add(CollisionShape^ shape)
{
	Unmanaged->push_back(shape->UnmanagedPointer);
}

void AlignedCollisionShapeArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedCollisionShapeArray::Contains(CollisionShape^ shape)
{
	return Unmanaged->findLinearSearch(shape->UnmanagedPointer) != Unmanaged->size();
}

void AlignedCollisionShapeArray::CopyTo(array<CollisionShape^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = CollisionShape::GetManaged(Unmanaged->at(i));
	}
}

int AlignedCollisionShapeArray::IndexOf(CollisionShape^ shape)
{
	int i = Unmanaged->findLinearSearch(shape->UnmanagedPointer);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedCollisionShapeArray::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedCollisionShapeArray::Remove(CollisionShape^ collisionShape)
{
	int sizeBefore = Unmanaged->size();
	Unmanaged->remove(collisionShape->UnmanagedPointer);
	return sizeBefore != Unmanaged->size();
}

void AlignedCollisionShapeArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

int AlignedCollisionShapeArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedCollisionShapeArray::Count::get()
{
	return Unmanaged->size();
}

CollisionShape^ AlignedCollisionShapeArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");

	return CollisionShape::GetManaged(Unmanaged->at(index));
}
void AlignedCollisionShapeArray::default::set(int index, CollisionShape^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");

	(*Unmanaged)[index] = GetUnmanagedNullable(value);
}


#undef Unmanaged
#define Unmanaged (static_cast<btCollisionObjectArray*>(_unmanaged))

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
	Unmanaged->push_back(obj->UnmanagedPointer);
}

void AlignedCollisionObjectArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedCollisionObjectArray::Contains(CollisionObject^ obj)
{
	return Unmanaged->findLinearSearch(obj->UnmanagedPointer) != Unmanaged->size();
}

void AlignedCollisionObjectArray::CopyTo(array<CollisionObject^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = CollisionObject::GetManaged(Unmanaged->at(i));
	}
}

int AlignedCollisionObjectArray::IndexOf(CollisionObject^ obj)
{
	int i = Unmanaged->findLinearSearch(obj->UnmanagedPointer);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedCollisionObjectArray::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedCollisionObjectArray::Remove(CollisionObject^ obj)
{
	int sizeBefore = Unmanaged->size();
	Unmanaged->remove(obj->UnmanagedPointer);
	return sizeBefore != Unmanaged->size();
}

void AlignedCollisionObjectArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

int AlignedCollisionObjectArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedCollisionObjectArray::Count::get()
{
	return Unmanaged->size();
}

CollisionObject^ AlignedCollisionObjectArray::default::get(int index)
{
	if (index < 0 || index >= Unmanaged->size())
		throw gcnew ArgumentOutOfRangeException("index");

	return CollisionObject::GetManaged(Unmanaged->at(index));
}
void AlignedCollisionObjectArray::default::set(int index, CollisionObject^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = GetUnmanagedNullable(value);
}


#ifndef DISABLE_DBVT

#undef Unmanaged
#define Unmanaged (static_cast<btAlignedObjectArray<const btDbvtNode*>*>(_unmanaged))

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
	Unmanaged->push_back(node->UnmanagedPointer);
}

void AlignedDbvtNodeArray::Clear()
{
	Unmanaged_unmanaged)->clear();
}

bool AlignedDbvtNodeArray::Contains(DbvtNode^ node)
{
	return Unmanaged->findLinearSearch(node->UnmanagedPointer)
		!= Unmanaged->size();
}

void AlignedDbvtNodeArray::CopyTo(array<DbvtNode^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = (Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew DbvtNode((btDbvtNode*)(*Unmanaged[i]);
	}
}

int AlignedDbvtNodeArray::IndexOf(DbvtNode^ node)
{
	int i = (Unmanaged->findLinearSearch(node->UnmanagedPointer);
	return i != (Unmanaged->size() ? i : -1;
}

void AlignedDbvtNodeArray::PopBack()
{
	(Unmanaged->pop_back();
}

bool AlignedDbvtNodeArray::Remove(DbvtNode^ node)
{
	int sizeBefore = (Unmanaged->size();
	(Unmanaged->remove(node->UnmanagedPointer);
	return sizeBefore != (Unmanaged->size();
}

int AlignedDbvtNodeArray::Capacity::get()
{
	return (Unmanaged->capacity();
}

int AlignedDbvtNodeArray::Count::get()
{
	return (Unmanaged->size();
}

void AlignedDbvtNodeArray::Swap(int index0, int index1)
{
	(Unmanaged->swap(index0, index1);
}

DbvtNode^ AlignedDbvtNodeArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btDbvtNode* obj = (btDbvtNode*)(*(Unmanaged)[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew DbvtNode(obj);
}
void AlignedDbvtNodeArray::default::set(int index, DbvtNode^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*(Unmanaged)[index] = GetUnmanagedNullable(value);
}


#undef Unmanaged
#define Unmanaged (static_cast<btAlignedObjectArray<btDbvt::sStkNN>*>(_unmanaged))

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
	Unmanaged->push_back(*stkNn->UnmanagedPointer);
}

void AlignedStkNnArray::Clear()
{
	Unmanaged->clear();
}

void AlignedStkNnArray::CopyTo(array<Dbvt::StkNn^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Dbvt::StkNn(&(*Unmanaged)[i]);
	}
}

void AlignedStkNnArray::PopBack()
{
	Unmanaged->pop_back();
}

void AlignedStkNnArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

int AlignedStkNnArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedStkNnArray::Count::get()
{
	return Unmanaged->size();
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
	StkNnArray_GetDefault(Unmanaged, index, obj);
	return gcnew Dbvt::StkNn(obj);
}

void AlignedStkNnArray::default::set(int index, Dbvt::StkNn^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*(btAlignedObjectArray<btDbvt::sStkNN>*)_unmanaged)[index] = *value->UnmanagedPointer;
}


#undef Unmanaged
#define Unmanaged (static_cast<btAlignedObjectArray<btDbvt::sStkNPS>*>(_unmanaged))

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
	Unmanaged->push_back(*stkNps->UnmanagedPointer);
}

void AlignedStkNpsArray::Clear()
{
	Unmanaged->clear();
}

void AlignedStkNpsArray::CopyTo(array<Dbvt::StkNps^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Dbvt::StkNps(&(*Unmanaged)[i]);
	}
}

void AlignedStkNpsArray::PopBack()
{
	Unmanaged->pop_back();
}

void AlignedStkNpsArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

int AlignedStkNpsArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedStkNpsArray::Count::get()
{
	return Unmanaged->size();
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
	StkNpsArray_GetDefault(Unmanaged, index, obj);
	return gcnew Dbvt::StkNps(obj);
}

void AlignedStkNpsArray::default::set(int index, Dbvt::StkNps^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = *value->UnmanagedPointer;
}
#endif


#ifndef DISABLE_SOFTBODY

#undef Unmanaged
#define Unmanaged (static_cast<btAlignedObjectArray<btSoftBody::Face>*>(_unmanaged))

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
	Unmanaged->push_back((btSoftBody::Face&)*face->_unmanaged);
}

void AlignedFaceArray::Clear()
{
	Unmanaged->clear();
}

void AlignedFaceArray::CopyTo(array<Face^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Face(&(*Unmanaged)[i]);
	}
}

void AlignedFaceArray::PopBack()
{
	Unmanaged->pop_back();
}

void AlignedFaceArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

int AlignedFaceArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedFaceArray::Count::get()
{
	return Unmanaged->size();
}

Face^ AlignedFaceArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Face(&(*Unmanaged)[index]);
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
	FaceArray_SetDefault(Unmanaged, index, (btSoftBody::Face*)value->_unmanaged);
}
#endif


#undef Unmanaged
#define Unmanaged (static_cast<btAlignedObjectArray<int>*>(_unmanaged))

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
	Unmanaged->push_back(integer);
}

void AlignedIntArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedIntArray::Contains(int integer)
{
	return Unmanaged->findLinearSearch(integer)
		!= Unmanaged->size();
}

void AlignedIntArray::CopyTo(array<int>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (*Unmanaged)[i];
	}
}

int AlignedIntArray::IndexOf(int integer)
{
	int i = Unmanaged->findLinearSearch(integer);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedIntArray::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedIntArray::Remove(int integer)
{
	int sizeBefore = Unmanaged->size();
	Unmanaged->remove(integer);
	return sizeBefore != Unmanaged->size();
}

void AlignedIntArray::Resize(int newSize)
{
	Unmanaged->resize(newSize);
}

void AlignedIntArray::Resize(int newSize, int fillData)
{
	Unmanaged->resize(newSize, fillData);
}

void AlignedIntArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

int AlignedIntArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedIntArray::Count::get()
{
	return Unmanaged->size();
}

int AlignedIntArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (*Unmanaged)[index];
}
void AlignedIntArray::default::set(int index, int value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = value;
}


#ifndef DISABLE_SOFTBODY

#undef Unmanaged
#define Unmanaged (static_cast<btSoftBody::tJointArray*>(_unmanaged))

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
	btSoftBody::Joint* jointTemp = joint->_unmanaged;
	Unmanaged->push_back(jointTemp);
}

void AlignedJointArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedJointArray::Contains(Joint^ joint)
{
	btSoftBody::Joint* jointTemp = joint->_unmanaged;
	return Unmanaged->findLinearSearch(jointTemp)
		!= Unmanaged->size();
}

void AlignedJointArray::CopyTo(array<Joint^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
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
	Unmanaged->pop_back();
}

int AlignedJointArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedJointArray::Count::get()
{
	return Unmanaged->size();
}

int AlignedJointArray::IndexOf(Joint^ joint)
{
	btSoftBody::Joint* jointTemp = joint->_unmanaged;
	int i = Unmanaged->findLinearSearch(jointTemp);
	return i != Unmanaged->size() ? i : -1;
}

bool AlignedJointArray::Remove(Joint^ joint)
{
	int sizeBefore = Unmanaged->size();
	btSoftBody::Joint* jointTemp = joint->_unmanaged;
	Unmanaged->remove(jointTemp);
	return sizeBefore != Unmanaged->size();
}

void AlignedJointArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

BulletSharp::SoftBody::Joint^ AlignedJointArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btSoftBody::Joint* j = (*Unmanaged)[index];
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
	AlignedJointArray_SetDefault(Unmanaged, index, GetUnmanagedNullable(value));
}
#endif


#undef Unmanaged
#define Unmanaged (static_cast<btManifoldArray*>(_unmanaged))

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
	Unmanaged->push_back((btPersistentManifold*)manifold->_unmanaged);
}

void AlignedManifoldArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedManifoldArray::Contains(PersistentManifold^ manifold)
{
	return Unmanaged->findLinearSearch((btPersistentManifold*)manifold->_unmanaged)
		!= Unmanaged->size();
}

void AlignedManifoldArray::CopyTo(array<PersistentManifold^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew PersistentManifold((*Unmanaged)[i]);
	}
}

int AlignedManifoldArray::IndexOf(PersistentManifold^ manifold)
{
	int i = Unmanaged->findLinearSearch((btPersistentManifold*)manifold->_unmanaged);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedManifoldArray::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedManifoldArray::Remove(PersistentManifold^ manifold)
{
	int sizeBefore = Unmanaged->size();
	Unmanaged->remove((btPersistentManifold*)manifold->_unmanaged);
	return sizeBefore != Unmanaged->size();
}

int AlignedManifoldArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedManifoldArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedManifoldArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

PersistentManifold^ AlignedManifoldArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btPersistentManifold* obj = (*Unmanaged)[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew PersistentManifold(obj);
}
void AlignedManifoldArray::default::set(int index, PersistentManifold^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = (btPersistentManifold*)GetUnmanagedNullable(value);
}


#undef Unmanaged
#define Unmanaged (static_cast<btAlignedObjectArray<btIndexedMesh>*>(_unmanaged))

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
	Unmanaged->push_back(*indexedMesh->UnmanagedPointer);
}

void AlignedIndexedMeshArray::Clear()
{
	Unmanaged->clear();
}

void AlignedIndexedMeshArray::CopyTo(array<IndexedMesh^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew IndexedMesh(&(*Unmanaged)[i]);
	}
}

void AlignedIndexedMeshArray::PopBack()
{
	Unmanaged->pop_back();
}

int AlignedIndexedMeshArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedIndexedMeshArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedIndexedMeshArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

IndexedMesh^ AlignedIndexedMeshArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	btIndexedMesh* obj = &(*Unmanaged)[index];
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
	AlignedIndexedMeshArray_SetDefault(Unmanaged, index, value->UnmanagedPointer);
}


#ifndef DISABLE_SOFTBODY

#undef Unmanaged
#define Unmanaged (static_cast<btSoftBody::tLinkArray*>(_unmanaged))

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
	Unmanaged->push_back((btSoftBody::Link&)*link->_unmanaged);
}

void AlignedLinkArray::Clear()
{
	Unmanaged->clear();
}

void AlignedLinkArray::CopyTo(array<Link^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Link(&(*Unmanaged)[i]);
	}
}

void AlignedLinkArray::PopBack()
{
	Unmanaged->pop_back();
}

int AlignedLinkArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedLinkArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedLinkArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

BulletSharp::SoftBody::Link^ AlignedLinkArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Link(&(*Unmanaged)[index]);
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
	AlignedLinkArray_SetDefault(Unmanaged, index, (btSoftBody::Link*)GetUnmanagedNullable(value));
}


#undef Unmanaged
#define Unmanaged (static_cast<btSoftBody::tMaterialArray*>(_unmanaged))

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
	Unmanaged->push_back((btSoftBody::Material*)material->_unmanaged);
}

void AlignedMaterialArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedMaterialArray::Contains(BulletSharp::SoftBody::Material^ material)
{
	return Unmanaged->findLinearSearch((btSoftBody::Material*)material->_unmanaged)
		!= Unmanaged->size();
}

void AlignedMaterialArray::CopyTo(array<BulletSharp::SoftBody::Material^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Material((*Unmanaged)[i]);
	}
}

int AlignedMaterialArray::IndexOf(BulletSharp::SoftBody::Material^ material)
{
	int i = Unmanaged->findLinearSearch((btSoftBody::Material*)material->_unmanaged);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedMaterialArray::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedMaterialArray::Remove(BulletSharp::SoftBody::Material^ material)
{
	int sizeBefore = Unmanaged->size();
	Unmanaged->remove((btSoftBody::Material*)material->_unmanaged);
	return sizeBefore != Unmanaged->size();
}

int AlignedMaterialArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedMaterialArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedMaterialArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

BulletSharp::SoftBody::Material^ AlignedMaterialArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Material((*Unmanaged)[index]);
}
void AlignedMaterialArray::default::set(int index, BulletSharp::SoftBody::Material^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = (btSoftBody::Material*)GetUnmanagedNullable(value);
}


#undef Unmanaged
#define Unmanaged (static_cast<btSoftBody::tNodeArray*>(_unmanaged))

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
	Unmanaged->push_back((btSoftBody::Node&)*node->_unmanaged);
}

void BulletSharp::SoftBody::AlignedNodeArray::Clear()
{
	Unmanaged->clear();
}

void BulletSharp::SoftBody::AlignedNodeArray::CopyTo(array<Node^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Node(&(*Unmanaged)[i]);
	}
}

void BulletSharp::SoftBody::AlignedNodeArray::PopBack()
{
	Unmanaged->pop_back();
}

int BulletSharp::SoftBody::AlignedNodeArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int BulletSharp::SoftBody::AlignedNodeArray::Count::get()
{
	return Unmanaged->size();
}

void BulletSharp::SoftBody::AlignedNodeArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

BulletSharp::SoftBody::Node^ BulletSharp::SoftBody::AlignedNodeArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Node(&(*Unmanaged)[index]);
}

void NodeArray_SetDefault(btSoftBody::tNodeArray* AlignedNodeArray, int index, btSoftBody::Node* node)
{
	(*AlignedNodeArray)[index] = *node;
}
void BulletSharp::SoftBody::AlignedNodeArray::default::set(int index, Node^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	NodeArray_SetDefault(Unmanaged, index, (btSoftBody::Node*)value->_unmanaged);
}


#undef Unmanaged
#define Unmanaged (static_cast<btAlignedObjectArray<btSoftBody::Node*>*>(_unmanaged))

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
	Unmanaged->push_back((btSoftBody::Node*)node->_unmanaged);
}

void AlignedNodePtrArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedNodePtrArray::Contains(BulletSharp::SoftBody::Node^ node)
{
	return Unmanaged->findLinearSearch((btSoftBody::Node*)node->_unmanaged)
		!= Unmanaged->size();
}

void AlignedNodePtrArray::CopyTo(array<BulletSharp::SoftBody::Node^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Node((*Unmanaged)[i]);
	}
}

int AlignedNodePtrArray::IndexOf(BulletSharp::SoftBody::Node^ node)
{
	int i = Unmanaged->findLinearSearch((btSoftBody::Node*)node->_unmanaged);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedNodePtrArray::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedNodePtrArray::Remove(BulletSharp::SoftBody::Node^ node)
{
	int sizeBefore = Unmanaged->size();
	Unmanaged->remove((btSoftBody::Node*)node->_unmanaged);
	return sizeBefore != Unmanaged->size();
}

int AlignedNodePtrArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedNodePtrArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedNodePtrArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

BulletSharp::SoftBody::Node^ AlignedNodePtrArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Node((*Unmanaged)[index]);
}
void AlignedNodePtrArray::default::set(int index, BulletSharp::SoftBody::Node^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = (btSoftBody::Node*)GetUnmanagedNullable(value);
}


#undef Unmanaged
#define Unmanaged (static_cast<btSoftBody::tNoteArray*>(_unmanaged))

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
	Unmanaged->push_back((btSoftBody::Note&)*note->_unmanaged);
}

void AlignedNoteArray::Clear()
{
	Unmanaged->clear();
}

void AlignedNoteArray::CopyTo(array<Note^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Note(&(*Unmanaged)[i]);
	}
}

void AlignedNoteArray::PopBack()
{
	Unmanaged->pop_back();
}

int AlignedNoteArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedNoteArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedNoteArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

BulletSharp::SoftBody::Note^ AlignedNoteArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Note(&(*Unmanaged)[index]);
}

void NoteArray_SetDefault(btSoftBody::tNoteArray* noteArray, int index, btSoftBody::Note* note)
{
	(*noteArray)[index] = *note;
}
void AlignedNoteArray::default::set(int index, Note^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	NoteArray_SetDefault(Unmanaged, index, (btSoftBody::Note*)GetUnmanagedNullable(value));
}


#undef Unmanaged
#define Unmanaged (static_cast<btSoftBody::tPSolverArray*>(_unmanaged))

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
	Unmanaged->push_back((btSoftBody::ePSolver::_)solver);
}

void AlignedPSolverArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedPSolverArray::Contains(PSolver solver)
{
	return Unmanaged->findLinearSearch((btSoftBody::ePSolver::_)solver)
		!= Unmanaged->size();
}

void AlignedPSolverArray::CopyTo(array<PSolver>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (PSolver)(*Unmanaged)[i];
	}
}

int AlignedPSolverArray::IndexOf(PSolver solver)
{
	int i = Unmanaged->findLinearSearch((btSoftBody::ePSolver::_)solver);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedPSolverArray::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedPSolverArray::Remove(PSolver solver)
{
	int sizeBefore = Unmanaged->size();
	Unmanaged->remove((btSoftBody::ePSolver::_)solver);
	return sizeBefore != Unmanaged->size();
}

int AlignedPSolverArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedPSolverArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedPSolverArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

PSolver AlignedPSolverArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (PSolver)(*Unmanaged)[index];
}
void AlignedPSolverArray::default::set(int index, PSolver value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = (btSoftBody::ePSolver::_)value;
}


#undef Unmanaged
#define Unmanaged (static_cast<btSoftBody::tRContactArray*>(_unmanaged))

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
	Unmanaged->push_back(*rigidContact->UnmanagedPointer);
}

void AlignedRigidContactArray::Clear()
{
	Unmanaged->clear();
}

void AlignedRigidContactArray::CopyTo(array<RigidContact^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew RigidContact(&(*Unmanaged)[i]);
	}
}

void AlignedRigidContactArray::PopBack()
{
	Unmanaged->pop_back();
}

void AlignedRigidContactArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

int AlignedRigidContactArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedRigidContactArray::Count::get()
{
	return Unmanaged->size();
}

BulletSharp::SoftBody::RigidContact^ AlignedRigidContactArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew RigidContact(&(*Unmanaged)[index]);
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
	AlignedRigidContactArray_SetDefault(Unmanaged, index, value->UnmanagedPointer);
}
#endif


#undef Unmanaged
#define Unmanaged (static_cast<btAlignedObjectArray<btScalar>*>(_unmanaged))

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
	Unmanaged->push_back(intValue);
}

void AlignedScalarArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedScalarArray::Contains(btScalar scalar)
{
	return Unmanaged->findLinearSearch(scalar)
		!= Unmanaged->size();
}

void AlignedScalarArray::CopyTo(array<btScalar>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (*Unmanaged)[i];
	}
}

int AlignedScalarArray::IndexOf(btScalar scalar)
{
	int i = Unmanaged->findLinearSearch(scalar);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedScalarArray::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedScalarArray::Remove(btScalar scalar)
{
	int sizeBefore = Unmanaged->size();
	Unmanaged->remove(scalar);
	return sizeBefore != Unmanaged->size();
}

int AlignedScalarArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedScalarArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedScalarArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

btScalar AlignedScalarArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (*Unmanaged)[index];
}
void AlignedScalarArray::default::set(int index, btScalar value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = value;
}


#ifndef DISABLE_SOFTBODY

#undef Unmanaged
#define Unmanaged static_cast<btSoftBody::tSoftBodyArray*>(_unmanaged)

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
	Unmanaged->push_back(softBody->UnmanagedPointer);
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::Clear()
{
	Unmanaged->clear();
}

bool BulletSharp::SoftBody::AlignedSoftBodyArray::Contains(SoftBody^ softBody)
{
	return Unmanaged->findLinearSearch(softBody->UnmanagedPointer) != Unmanaged->size();
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::CopyTo(array<SoftBody^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (SoftBody^)CollisionObject::GetManaged((*Unmanaged)[i]);
	}
}

int BulletSharp::SoftBody::AlignedSoftBodyArray::IndexOf(SoftBody^ softBody)
{
	int i = Unmanaged->findLinearSearch(softBody->UnmanagedPointer);
	return i != Unmanaged->size() ? i : -1;
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::PopBack()
{
	Unmanaged->pop_back();
}

bool BulletSharp::SoftBody::AlignedSoftBodyArray::Remove(SoftBody^ softBody)
{
	int sizeBefore = Unmanaged->size();
	Unmanaged->remove(softBody->UnmanagedPointer);
	return sizeBefore != Unmanaged->size();
}

int BulletSharp::SoftBody::AlignedSoftBodyArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int BulletSharp::SoftBody::AlignedSoftBodyArray::Count::get()
{
	return Unmanaged->size();
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

BulletSharp::SoftBody::SoftBody^ BulletSharp::SoftBody::AlignedSoftBodyArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (SoftBody^)CollisionObject::GetManaged((*Unmanaged)[index]);
}
void BulletSharp::SoftBody::AlignedSoftBodyArray::default::set(int index, SoftBody^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = (btSoftBody*)GetUnmanagedNullable(value);
}


#undef Unmanaged
#define Unmanaged static_cast<btSoftBody::tSContactArray*>(_unmanaged)

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
	Unmanaged->push_back(*softContact->UnmanagedPointer);
}

void AlignedSoftContactArray::Clear()
{
	Unmanaged->clear();
}

void AlignedSoftContactArray::CopyTo(array<SoftContact^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew SoftContact(&(*Unmanaged)[i]);
	}
}

void AlignedSoftContactArray::PopBack()
{
	Unmanaged->pop_back();
}

void AlignedSoftContactArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

int AlignedSoftContactArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedSoftContactArray::Count::get()
{
	return Unmanaged->size();
}

BulletSharp::SoftBody::SoftContact^ AlignedSoftContactArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew SoftContact(&(*Unmanaged)[index]);
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
	AlignedSoftContactArray_SetDefault(Unmanaged, index, value->UnmanagedPointer);
}


#undef Unmanaged
#define Unmanaged static_cast<btAlignedObjectArray<btSoftBody::Tetra>*>(_unmanaged)

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
	Unmanaged->push_back((btSoftBody::Tetra&)*tetra->_unmanaged);
}

void AlignedTetraArray::Clear()
{
	Unmanaged->clear();
}

void AlignedTetraArray::CopyTo(array<Tetra^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Tetra(&(*Unmanaged)[i]);
	}
}

void AlignedTetraArray::PopBack()
{
	Unmanaged->pop_back();
}

void AlignedTetraArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

int AlignedTetraArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedTetraArray::Count::get()
{
	return Unmanaged->size();
}

Tetra^ AlignedTetraArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Tetra(&(*Unmanaged)[index]);
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
	TetraArray_SetDefault(Unmanaged, index, (btSoftBody::Tetra*)value->_unmanaged);
}
#endif


#undef Unmanaged
#define Unmanaged static_cast<btAlignedObjectArray<btTriangleMesh*>*>(_unmanaged)

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
	Unmanaged->push_back(triangleMesh->UnmanagedPointer);
}

void AlignedTriangleMeshArray::Clear()
{
	Unmanaged->clear();
}

void AlignedTriangleMeshArray::CopyTo(array<TriangleMesh^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew TriangleMesh(&(*Unmanaged)[i]);
	}
}

void AlignedTriangleMeshArray::PopBack()
{
	Unmanaged->pop_back();
}

int AlignedTriangleMeshArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedTriangleMeshArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedTriangleMeshArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

TriangleMesh^ AlignedTriangleMeshArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew TriangleMesh(&(*Unmanaged)[index]);
}

void AlignedTriangleMeshArray::default::set(int index, TriangleMesh^ value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = (btTriangleMesh*)GetUnmanagedNullable(value);
}


#undef Unmanaged
#define Unmanaged static_cast<btAlignedObjectArray<btVector3>*>(_unmanaged)

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
	VECTOR3_DEF(vector3Value);
	Unmanaged->push_back(VECTOR3_USE(vector3Value));
	VECTOR3_DEL(vector3Value);
}

void AlignedVector3Array::Add(Vector4 vector4Value)
{
	btVector4* tempVector4Value = Math::Vector4ToBtVector4(vector4Value);
	Unmanaged->push_back(*tempVector4Value);
	delete tempVector4Value;
}

void AlignedVector3Array::Clear()
{
	Unmanaged->clear();
}

bool AlignedVector3Array::Contains(Vector3 vector)
{
	VECTOR3_DEF(vector);
	int i = Unmanaged->findLinearSearch(VECTOR3_USE(vector));
	VECTOR3_DEL(vector);
	return i != Unmanaged->size();
}

void AlignedVector3Array::CopyTo(array<Vector3>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		Math::BtVector3ToVector3(&(*Unmanaged)[i], array[arrayIndex+i]);
	}
}

int AlignedVector3Array::IndexOf(Vector3 vector)
{
	VECTOR3_DEF(vector);
	int i = Unmanaged->findLinearSearch(VECTOR3_USE(vector));
	VECTOR3_DEL(vector);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedVector3Array::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedVector3Array::Remove(Vector3 vector)
{
	int sizeBefore = Unmanaged->size();
	VECTOR3_DEF(vector);
	Unmanaged->remove(VECTOR3_USE(vector));
	VECTOR3_DEL(vector);
	return sizeBefore != Unmanaged->size();
}

int AlignedVector3Array::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedVector3Array::Count::get()
{
	return Unmanaged->size();
}

void AlignedVector3Array::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

Vector3 AlignedVector3Array::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return Math::BtVector3ToVector3(&(*Unmanaged)[index]);
}
void AlignedVector3Array::default::set(int index, Vector3 value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	Math::Vector3ToBtVector3(value, &(*Unmanaged)[index]);
}


#ifndef DISABLE_SOFTBODY

#undef Unmanaged
#define Unmanaged static_cast<btSoftBody::tVSolverArray*>(_unmanaged)

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
	Unmanaged->push_back((btSoftBody::eVSolver::_)solver);
}

void AlignedVSolverArray::Clear()
{
	Unmanaged->clear();
}

bool AlignedVSolverArray::Contains(VSolver solver)
{
	return Unmanaged->findLinearSearch((btSoftBody::eVSolver::_)solver)
		!= Unmanaged->size();
}

void AlignedVSolverArray::CopyTo(array<VSolver>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (VSolver)(*Unmanaged)[i];
	}
}

int AlignedVSolverArray::IndexOf(VSolver solver)
{
	int i = Unmanaged->findLinearSearch((btSoftBody::eVSolver::_)solver);
	return i != Unmanaged->size() ? i : -1;
}

void AlignedVSolverArray::PopBack()
{
	Unmanaged->pop_back();
}

bool AlignedVSolverArray::Remove(VSolver solver)
{
	int sizeBefore = Unmanaged->size();
	Unmanaged->remove((btSoftBody::eVSolver::_)solver);
	return sizeBefore != Unmanaged->size();
}

int AlignedVSolverArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedVSolverArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedVSolverArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

VSolver AlignedVSolverArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return (VSolver)(*Unmanaged)[index];
}
void AlignedVSolverArray::default::set(int index, VSolver value)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	(*Unmanaged)[index] = (btSoftBody::eVSolver::_)value;
}
#endif


#ifndef DISABLE_VEHICLE

#undef Unmanaged
#define Unmanaged static_cast<btAlignedObjectArray<btWheelInfo>*>(_unmanaged)

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
	Unmanaged->push_back(*wheelInfo->UnmanagedPointer);
}

void AlignedWheelInfoArray::Clear()
{
	Unmanaged->clear();
}

void AlignedWheelInfoArray::CopyTo(array<WheelInfo^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Unmanaged->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew WheelInfo(&(*Unmanaged)[i]);
	}
}

void AlignedWheelInfoArray::PopBack()
{
	Unmanaged->pop_back();
}

int AlignedWheelInfoArray::Capacity::get()
{
	return Unmanaged->capacity();
}

int AlignedWheelInfoArray::Count::get()
{
	return Unmanaged->size();
}

void AlignedWheelInfoArray::Swap(int index0, int index1)
{
	Unmanaged->swap(index0, index1);
}

WheelInfo^ AlignedWheelInfoArray::default::get(int index)
{
	if (index < 0 || index >= Count)
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew WheelInfo(&(*Unmanaged)[index]);
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
	WheelInfoArray_SetDefault(Unmanaged, index, value->UnmanagedPointer);
}
#endif
