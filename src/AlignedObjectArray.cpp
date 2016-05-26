#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "BroadphaseProxy.h"
#include "Collections.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "CompoundShape.h"
#include "RigidBody.h"
#include "PersistentManifold.h"
#include "SimpleBroadphase.h"
#include "TriangleIndexVertexArray.h"
#include "TriangleMesh.h"
#ifndef DISABLE_DBVT
#include "DbvtBroadphase.h"
#endif
#ifndef DISABLE_SOFTBODY
#include "SoftBody.h"
using namespace BulletSharp::SoftBody;
#endif
#ifndef DISABLE_VEHICLE
#include "WheelInfo.h"
#endif

generic<class T>
AlignedObjectArray<T>::AlignedObjectArray(void* alignedObjectArray, bool ownsObject)
{
	_native = alignedObjectArray;
	_ownsObject = ownsObject;
}

generic<class T>
AlignedObjectArray<T>::AlignedObjectArray(void* alignedObjectArray)
{
	_native = alignedObjectArray;
}

generic<class T>
AlignedObjectArray<T>::!AlignedObjectArray()
{
	if (this->IsDisposed)
		return;

	if (_ownsObject) {
		delete _native;
	}
	_native = NULL;
}

generic<class T>
AlignedObjectArray<T>::~AlignedObjectArray()
{
	this->!AlignedObjectArray();
}

generic<class T>
System::Collections::IEnumerator^ AlignedObjectArray<T>::GetObjectEnumerator()
{
	return gcnew ListEnumerator<T>(this);
}

generic<class T>
IEnumerator<T>^ AlignedObjectArray<T>::GetEnumerator()
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
		// Swap the removed item with the last item and pop it like Bullet does.
		Swap(i, Count-1);
		PopBack();
		return true;
	}
	return false;
}

generic<class T>
void AlignedObjectArray<T>::RemoveAt(int index)
{
	unsigned int count = Count;
	if ((unsigned int)index >= count)
		throw gcnew ArgumentOutOfRangeException("index");

	// Swap the removed item with the last item and pop it like Bullet does.
	Swap(index, count-1);
	PopBack();
}

generic<class T>
bool AlignedObjectArray<T>::IsDisposed::get()
{
	return (_native == NULL);
}

generic<class T>
bool AlignedObjectArray<T>::IsReadOnly::get()
{
	return false;
}


#ifndef DISABLE_SOFTBODY

#define Native (static_cast<btSoftBody::tAnchorArray*>(_native))

AlignedAnchorArray::AlignedAnchorArray(btSoftBody::tAnchorArray* anchorArray)
: AlignedObjectArray(anchorArray)
{
}

AlignedAnchorArray::AlignedAnchorArray()
: AlignedObjectArray(new btSoftBody::tAnchorArray(), true)
{
}

void AlignedAnchorArray::Add(Anchor^ anchor)
{
	Native->push_back(*anchor->_native);
}

void AlignedAnchorArray::Clear()
{
	Native->clear();
}

void AlignedAnchorArray::CopyTo(array<Anchor^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Anchor(&(*Native)[i]);
	}
}

void AlignedAnchorArray::PopBack()
{
	Native->pop_back();
}

void AlignedAnchorArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

int AlignedAnchorArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedAnchorArray::Count::get()
{
	return Native->size();
}

BulletSharp::SoftBody::Anchor^ AlignedAnchorArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Anchor(&Native->at(index));
}

#pragma managed(push, off)
void AlignedAnchorArray_SetDefault(btSoftBody::tAnchorArray* anchorArray,
	int index, btSoftBody::Anchor* anchor)
{
	(*anchorArray)[index] = *anchor;
}
#pragma managed(pop)
void AlignedAnchorArray::default::set(int index, Anchor^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedAnchorArray_SetDefault(Native, index, value->_native);
}
#endif


#undef Native
#define Native (static_cast<btBroadphasePairArray*>(_native))

AlignedBroadphasePairArray::AlignedBroadphasePairArray(btBroadphasePairArray* pairArray)
: AlignedObjectArray(pairArray)
{
}

AlignedBroadphasePairArray::AlignedBroadphasePairArray()
: AlignedObjectArray(new btBroadphasePairArray, true)
{
}

void AlignedBroadphasePairArray::Add(BroadphasePair^ pair)
{
	Native->push_back(*pair->_native);
}

void AlignedBroadphasePairArray::Clear()
{
	Native->clear();
}

bool AlignedBroadphasePairArray::Contains(BroadphasePair^ pair)
{
	return Native->findLinearSearch(*pair->_native) != Native->size();
}

void AlignedBroadphasePairArray::CopyTo(array<BroadphasePair^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew BroadphasePair(&Native->at(i));
	}
}

int AlignedBroadphasePairArray::IndexOf(BroadphasePair^ pair)
{
	int i = Native->findLinearSearch(*pair->_native);
	return i != Native->size() ? i : -1;
}

void AlignedBroadphasePairArray::PopBack()
{
	Native->pop_back();
}

bool AlignedBroadphasePairArray::Remove(BroadphasePair^ pair)
{
	int sizeBefore = Native->size();
	Native->remove(*pair->_native);
	return sizeBefore != Native->size();
}

int AlignedBroadphasePairArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedBroadphasePairArray::Count::get()
{
	return Native->size();
}

void AlignedBroadphasePairArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

BroadphasePair^ AlignedBroadphasePairArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew BroadphasePair(&Native->at(index));
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
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	BroadphasePairList_SetDefault(Native, index, value->_native);
}


#ifndef DISABLE_SOFTBODY

#undef Native
#define Native (static_cast<btSoftBody::tClusterArray*>(_native))

AlignedClusterArray::AlignedClusterArray(btSoftBody::tClusterArray* clusterArray)
: AlignedObjectArray(clusterArray)
{
}

AlignedClusterArray::AlignedClusterArray()
: AlignedObjectArray(new btSoftBody::tClusterArray(), true)
{
}

void AlignedClusterArray::Add(Cluster^ cluster)
{
	btSoftBody::Cluster* clusterTemp = cluster->_native;
	Native->push_back(clusterTemp);
}

void AlignedClusterArray::Clear()
{
	Native->clear();
}

bool AlignedClusterArray::Contains(Cluster^ cluster)
{
	btSoftBody::Cluster* clusterTemp = cluster->_native;
	return Native->findLinearSearch(clusterTemp)
		!= Native->size();
}

void AlignedClusterArray::CopyTo(array<Cluster^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Cluster(Native->at(i));
	}
}

int AlignedClusterArray::IndexOf(Cluster^ cluster)
{
	btSoftBody::Cluster* clusterTemp = cluster->_native;
	int i = Native->findLinearSearch(clusterTemp);
	return i != Native->size() ? i : -1;
}

void AlignedClusterArray::PopBack()
{
	Native->pop_back();
}

bool AlignedClusterArray::Remove(Cluster^ cluster)
{
	int sizeBefore = Native->size();
	btSoftBody::Cluster* clusterTemp = cluster->_native;
	Native->remove(clusterTemp);
	return sizeBefore != Native->size();
}

void AlignedClusterArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

int AlignedClusterArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedClusterArray::Count::get()
{
	return Native->size();
}

BulletSharp::SoftBody::Cluster^ AlignedClusterArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Cluster((*Native)[index]);
}
void AlignedClusterArray::default::set(int index, Cluster^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = GetUnmanagedNullable(value);
}
#endif


#undef Native
#define Native (static_cast<btCollisionObjectArray*>(_native))

AlignedCollisionObjectArray::AlignedCollisionObjectArray(btCollisionObjectArray* objectArray)
: AlignedObjectArray(objectArray)
{
}

AlignedCollisionObjectArray::AlignedCollisionObjectArray(btCollisionObjectArray* objectArray, btCollisionWorld* collisionWorld)
: AlignedObjectArray(objectArray)
{
	if (collisionWorld)
	{
		_collisionWorld = collisionWorld;
		_backingList = gcnew List<CollisionObject^>();
	}
}

void SetBodyBroadphaseHandle(CollisionObject^ item, btBroadphaseInterface* broadphase)
{
#ifndef DISABLE_DBVT
	if (dynamic_cast<btDbvtBroadphase*>(broadphase)) {
		item->BroadphaseHandle = gcnew DbvtProxy((btDbvtProxy*)item->_native->getBroadphaseHandle());
	}
	else
#endif
	// TODO: implement AxisSweep3::Handle
	/*
	if (dynamic_cast<btAxisSweep3*>(broadphase)) {
		item->BroadphaseHandle = gcnew BroadphaseProxy(item->_native->getBroadphaseHandle());
	}
	else if (dynamic_cast<bt32BitAxisSweep3*>(broadphase)) {
		item->BroadphaseHandle = gcnew BroadphaseProxy(item->_native->getBroadphaseHandle());
	}*/
	if (dynamic_cast<btSimpleBroadphase*>(broadphase)) {
		item->BroadphaseHandle = gcnew SimpleBroadphaseProxy((btSimpleBroadphaseProxy*)item->_native->getBroadphaseHandle());
	} else {
		item->BroadphaseHandle = gcnew BroadphaseProxy(item->_native->getBroadphaseHandle());
	}
}

void AlignedCollisionObjectArray::Add(CollisionObject^ item)
{
	btCollisionObject* itemPtr = item->_native;

	if (_collisionWorld)
	{
		switch (itemPtr->getInternalType())
		{
		case btCollisionObject::CO_RIGID_BODY:
			if (item->CollisionShape == nullptr) return;
			static_cast<btDynamicsWorld*>(_collisionWorld)->addRigidBody(static_cast<btRigidBody*>(itemPtr));
			break;
		case btCollisionObject::CO_SOFT_BODY:
			static_cast<btSoftRigidDynamicsWorld*>(_collisionWorld)->addSoftBody(static_cast<btSoftBody*>(itemPtr));
			break;
		default:
			_collisionWorld->addCollisionObject(itemPtr);
			break;
		}

		SetBodyBroadphaseHandle(item, _collisionWorld->getBroadphase());
		_backingList->Add(item);
	}
	else
	{
		Native->push_back(itemPtr);
	}
}

void AlignedCollisionObjectArray::Add(CollisionObject^ item, short collisionFilterGroup, short collisionFilterMask)
{
	btCollisionObject* itemPtr = item->_native;

	switch (itemPtr->getInternalType())
	{
	case btCollisionObject::CO_RIGID_BODY:
		if (item->CollisionShape == nullptr) return;
		static_cast<btDynamicsWorld*>(_collisionWorld)->addRigidBody(static_cast<btRigidBody*>(itemPtr), collisionFilterGroup, collisionFilterMask);
		break;
	case btCollisionObject::CO_SOFT_BODY:
		static_cast<btSoftRigidDynamicsWorld*>(_collisionWorld)->addSoftBody(static_cast<btSoftBody*>(itemPtr), collisionFilterGroup, collisionFilterMask);
		break;
	default:
		_collisionWorld->addCollisionObject(itemPtr, collisionFilterGroup, collisionFilterMask);
		break;
	}

	SetBodyBroadphaseHandle(item, _collisionWorld->getBroadphase());
	_backingList->Add(item);
}

void AlignedCollisionObjectArray::Clear()
{
	if (_backingList) {
		int count = Count;
		while(count != 0) {
			count -= 1;
			RemoveAt(count);
		}
	} else {
		Native->resizeNoInitialize(0);
	}
}

bool AlignedCollisionObjectArray::Contains(CollisionObject^ item)
{
	return Native->findLinearSearch(item->UnmanagedPointer) != Native->size();
}

void AlignedCollisionObjectArray::CopyTo(array<CollisionObject^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	if (_backingList)
	{
		for (i=0; i<size; i++)
		{
			array[arrayIndex+i] = _backingList[i];
		}
	}
	else
	{
		for (i=0; i<size; i++)
		{
			array[arrayIndex+i] = CollisionObject::GetManaged(Native->at(i));
		}
	}
}

System::Collections::IEnumerator^ AlignedCollisionObjectArray::GetObjectEnumerator()
{
	if (_backingList)
	{
		return _backingList->GetEnumerator();
	}
	else
	{
		return gcnew ListEnumerator<CollisionObject^>(this);
	}
}

IEnumerator<CollisionObject^>^ AlignedCollisionObjectArray::GetEnumerator()
{
	if (_backingList)
	{
		return _backingList->GetEnumerator();
	}
	else
	{
		return gcnew ListEnumerator<CollisionObject^>(this);
	}
}

int AlignedCollisionObjectArray::IndexOf(CollisionObject^ item)
{
	btCollisionObject* itemPtr = GetUnmanagedNullable(item);
	int i = Native->findLinearSearch(itemPtr);
	return i != Native->size() ? i : -1;
}

void AlignedCollisionObjectArray::PopBack()
{
	if (_backingList)
	{
		RemoveAt(Count - 1);
	}
	else
	{
		Native->pop_back();
	}
}

bool AlignedCollisionObjectArray::Remove(CollisionObject^ item)
{
	if (_backingList)
	{
		int index = IndexOf(item);
		if (index == -1) return false;
		RemoveAt(index);
		return true;
	}

	int sizeBefore = Native->size();
	btCollisionObject* itemPtr = item->_native;
	Native->remove(itemPtr);
	return sizeBefore != Native->size();
}

void AlignedCollisionObjectArray::RemoveAt(int index)
{
	unsigned int count = Count;

	if (_backingList)
	{
		CollisionObject^ item = _backingList[index];
		btCollisionObject* itemPtr = item->_native;

		switch (itemPtr->getInternalType())
		{
		case btCollisionObject::CO_RIGID_BODY:
			if (item->CollisionShape == nullptr)
			{
				return;
			}
			static_cast<btDynamicsWorld*>(_collisionWorld)->removeRigidBody(static_cast<btRigidBody*>(itemPtr));
			break;
		case btCollisionObject::CO_SOFT_BODY:
			static_cast<btSoftRigidDynamicsWorld*>(_collisionWorld)->removeSoftBody(static_cast<btSoftBody*>(itemPtr));
			break;
		default:
			_collisionWorld->removeCollisionObject(itemPtr);
			break;
		}
		_backingList[index]->BroadphaseHandle = nullptr;

		// Swap the removed item with the last item like Bullet does.
		count--;
		if (index != count)
		{
			_backingList[index] = _backingList[count];
		}
		_backingList->RemoveAt(count);
	}
	else
	{
		if ((unsigned int)index >= count)
			throw gcnew ArgumentOutOfRangeException("index");

		Swap(index, count-1);
		PopBack();
	}
}

void AlignedCollisionObjectArray::Swap(int index0, int index1)
{
	if (_backingList)
	{
		CollisionObject^ temp = _backingList[index0];
		_backingList[index0] = _backingList[index1];
		_backingList[index1] = temp;
	}
	else
	{
		unsigned int count = Count;
		if ((unsigned int)index0 >= count)
			throw gcnew ArgumentOutOfRangeException("index0");
		if ((unsigned int)index1 >= count)
			throw gcnew ArgumentOutOfRangeException("index1");
	}

	Native->swap(index0, index1);
}

int AlignedCollisionObjectArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedCollisionObjectArray::Count::get()
{
	return Native->size();
}

CollisionObject^ AlignedCollisionObjectArray::default::get(int index)
{
	if (_backingList)
	{
		return _backingList[index];
	}

	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");

	return CollisionObject::GetManaged(Native->at(index));
}
void AlignedCollisionObjectArray::default::set(int index, CollisionObject^ value)
{
	if (_backingList)
	{
		// Is there another instance of the existing value
		// tied to the collision world?
		//_backingList[index]->BroadphaseHandle = nullptr;

		_backingList[index] = value;
	}
	else
	{
		if ((unsigned int)index >= (unsigned int)Native->size())
			throw gcnew ArgumentOutOfRangeException("index");
		(*Native)[index] = GetUnmanagedNullable(value);
	}
}


#ifndef DISABLE_DBVT

#undef Native
#define Native (static_cast<btAlignedObjectArray<const btDbvtNode*>*>(_native))

AlignedDbvtNodeArray::AlignedDbvtNodeArray(btAlignedObjectArray<const btDbvtNode*>* AlignedNodeArray)
: AlignedObjectArray(AlignedNodeArray)
{
}

AlignedDbvtNodeArray::AlignedDbvtNodeArray()
: AlignedObjectArray(new btAlignedObjectArray<btDbvtNode>, true)
{
}

void AlignedDbvtNodeArray::Add(DbvtNode^ node)
{
	Native->push_back((const btDbvtNode*)node->_native);
}

void AlignedDbvtNodeArray::Clear()
{
	Native->clear();
}

bool AlignedDbvtNodeArray::Contains(DbvtNode^ node)
{
	return Native->findLinearSearch((const btDbvtNode*)node->_native) != Native->size();
}

void AlignedDbvtNodeArray::CopyTo(array<DbvtNode^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew DbvtNode((btDbvtNode*)(*Native)[i]);
	}
}

int AlignedDbvtNodeArray::IndexOf(DbvtNode^ node)
{
	int i = Native->findLinearSearch((const btDbvtNode*)node->_native);
	return i != Native->size() ? i : -1;
}

void AlignedDbvtNodeArray::PopBack()
{
	Native->pop_back();
}

bool AlignedDbvtNodeArray::Remove(DbvtNode^ node)
{
	int sizeBefore = Native->size();
	Native->remove((const btDbvtNode*)node->_native);
	return sizeBefore != Native->size();
}

int AlignedDbvtNodeArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedDbvtNodeArray::Count::get()
{
	return Native->size();
}

void AlignedDbvtNodeArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

DbvtNode^ AlignedDbvtNodeArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	btDbvtNode* obj = (btDbvtNode*)(*Native)[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew DbvtNode(obj);
}
void AlignedDbvtNodeArray::default::set(int index, DbvtNode^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = GetUnmanagedNullable(value);
}


#undef Native
#define Native (static_cast<btAlignedObjectArray<btDbvt::sStkNN>*>(_native))

AlignedStkNNArray::AlignedStkNNArray(btAlignedObjectArray<btDbvt::sStkNN>* stkNnArray)
: AlignedObjectArray(stkNnArray)
{
}

AlignedStkNNArray::AlignedStkNNArray()
: AlignedObjectArray(new btAlignedObjectArray<btDbvt::sStkNN>, true)
{
}

void AlignedStkNNArray::Add(Dbvt::StkNN^ stkNn)
{
	Native->push_back(*stkNn->_native);
}

void AlignedStkNNArray::Clear()
{
	Native->clear();
}

void AlignedStkNNArray::CopyTo(array<Dbvt::StkNN^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Dbvt::StkNN(&(*Native)[i]);
	}
}

void AlignedStkNNArray::PopBack()
{
	Native->pop_back();
}

void AlignedStkNNArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

int AlignedStkNNArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedStkNNArray::Count::get()
{
	return Native->size();
}

void StkNnArray_GetDefault(btAlignedObjectArray<btDbvt::sStkNN>* stkNnArray,
	int index, btDbvt::sStkNN* obj)
{
	*obj = (*stkNnArray)[index];
}
Dbvt::StkNN^ AlignedStkNNArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	btDbvt::sStkNN* obj = new btDbvt::sStkNN;
	StkNnArray_GetDefault(Native, index, obj);
	return gcnew Dbvt::StkNN(obj);
}

void AlignedStkNNArray::default::set(int index, Dbvt::StkNN^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = *value->_native;
}


#undef Native
#define Native (static_cast<btAlignedObjectArray<btDbvt::sStkNPS>*>(_native))

AlignedStkNpsArray::AlignedStkNpsArray(btAlignedObjectArray<btDbvt::sStkNPS>* stkNpsArray)
: AlignedObjectArray(stkNpsArray)
{
}

AlignedStkNpsArray::AlignedStkNpsArray()
: AlignedObjectArray(new btAlignedObjectArray<btDbvt::sStkNPS>, true)
{
}

void AlignedStkNpsArray::Add(Dbvt::StkNps^ stkNps)
{
	Native->push_back(*stkNps->_native);
}

void AlignedStkNpsArray::Clear()
{
	Native->clear();
}

void AlignedStkNpsArray::CopyTo(array<Dbvt::StkNps^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Dbvt::StkNps(&(*Native)[i]);
	}
}

void AlignedStkNpsArray::PopBack()
{
	Native->pop_back();
}

void AlignedStkNpsArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

int AlignedStkNpsArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedStkNpsArray::Count::get()
{
	return Native->size();
}

void StkNpsArray_GetDefault(btAlignedObjectArray<btDbvt::sStkNPS>* stkNpsArray,
	int index, btDbvt::sStkNPS* obj)
{
	*obj = (*stkNpsArray)[index];
}
Dbvt::StkNps^ AlignedStkNpsArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	btDbvt::sStkNPS* obj = new btDbvt::sStkNPS;
	StkNpsArray_GetDefault(Native, index, obj);
	return gcnew Dbvt::StkNps(obj);
}

void AlignedStkNpsArray::default::set(int index, Dbvt::StkNps^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = *value->_native;
}
#endif


#ifndef DISABLE_SOFTBODY

#undef Native
#define Native (static_cast<btAlignedObjectArray<btSoftBody::Face>*>(_native))

AlignedFaceArray::AlignedFaceArray(btAlignedObjectArray<btSoftBody::Face>* faceArray)
: AlignedObjectArray(faceArray)
{
}

AlignedFaceArray::AlignedFaceArray()
: AlignedObjectArray(new btAlignedObjectArray<btSoftBody::Face>, true)
{
}

void AlignedFaceArray::Add(Face^ face)
{
	Native->push_back((btSoftBody::Face&)*face->_native);
}

void AlignedFaceArray::Clear()
{
	Native->clear();
}

void AlignedFaceArray::CopyTo(array<Face^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Face(&(*Native)[i]);
	}
}

void AlignedFaceArray::PopBack()
{
	Native->pop_back();
}

void AlignedFaceArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

int AlignedFaceArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedFaceArray::Count::get()
{
	return Native->size();
}

Face^ AlignedFaceArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Face(&(*Native)[index]);
}

#pragma managed(push, off)
void FaceArray_SetDefault(btAlignedObjectArray<btSoftBody::Face>* faceArray,
	int index, btSoftBody::Face* node)
{
	(*faceArray)[index] = *node;
}
#pragma managed(pop)
void AlignedFaceArray::default::set(int index, Face^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	FaceArray_SetDefault(Native, index, (btSoftBody::Face*)value->_native);
}
#endif


#undef Native
#define Native (static_cast<btAlignedObjectArray<int>*>(_native))

AlignedIntArray::AlignedIntArray(btAlignedObjectArray<int>* intArray)
: AlignedObjectArray(intArray)
{
}

AlignedIntArray::AlignedIntArray()
: AlignedObjectArray(new btAlignedObjectArray<int>, true)
{
}

void AlignedIntArray::Add(int integer)
{
	Native->push_back(integer);
}

void AlignedIntArray::Clear()
{
	Native->clear();
}

bool AlignedIntArray::Contains(int integer)
{
	return Native->findLinearSearch(integer)
		!= Native->size();
}

void AlignedIntArray::CopyTo(array<int>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (*Native)[i];
	}
}

int AlignedIntArray::IndexOf(int integer)
{
	int i = Native->findLinearSearch(integer);
	return i != Native->size() ? i : -1;
}

void AlignedIntArray::PopBack()
{
	Native->pop_back();
}

bool AlignedIntArray::Remove(int integer)
{
	int sizeBefore = Native->size();
	Native->remove(integer);
	return sizeBefore != Native->size();
}

void AlignedIntArray::Resize(int newSize)
{
	Native->resize(newSize);
}

void AlignedIntArray::Resize(int newSize, int fillData)
{
	Native->resize(newSize, fillData);
}

void AlignedIntArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

int AlignedIntArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedIntArray::Count::get()
{
	return Native->size();
}

int AlignedIntArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return (*Native)[index];
}
void AlignedIntArray::default::set(int index, int value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = value;
}


#ifndef DISABLE_SOFTBODY

#undef Native
#define Native (static_cast<btSoftBody::tJointArray*>(_native))

AlignedJointArray::AlignedJointArray(btSoftBody::tJointArray* jointArray)
: AlignedObjectArray(jointArray)
{
}

AlignedJointArray::AlignedJointArray()
: AlignedObjectArray(new btSoftBody::tLinkArray(), true)
{
}

void AlignedJointArray::Add(BulletSharp::SoftBody::Joint^ joint)
{
	btSoftBody::Joint* jointTemp = joint->_native;
	Native->push_back(jointTemp);
}

void AlignedJointArray::Clear()
{
	Native->clear();
}

bool AlignedJointArray::Contains(Joint^ joint)
{
	btSoftBody::Joint* jointTemp = joint->_native;
	return Native->findLinearSearch(jointTemp)
		!= Native->size();
}

void AlignedJointArray::CopyTo(array<Joint^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
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
	Native->pop_back();
}

int AlignedJointArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedJointArray::Count::get()
{
	return Native->size();
}

int AlignedJointArray::IndexOf(Joint^ joint)
{
	btSoftBody::Joint* jointTemp = joint->_native;
	int i = Native->findLinearSearch(jointTemp);
	return i != Native->size() ? i : -1;
}

bool AlignedJointArray::Remove(Joint^ joint)
{
	int sizeBefore = Native->size();
	btSoftBody::Joint* jointTemp = joint->_native;
	Native->remove(jointTemp);
	return sizeBefore != Native->size();
}

void AlignedJointArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

BulletSharp::SoftBody::Joint^ AlignedJointArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	btSoftBody::Joint* j = (*Native)[index];
	switch(j->Type())
	{
	case btSoftBody::Joint::eType::Linear:
		return gcnew LJoint((btSoftBody::LJoint*)j);
	case btSoftBody::Joint::eType::Angular:
		return gcnew AJoint((btSoftBody::AJoint*)j);
	case btSoftBody::Joint::eType::Contact:
		return gcnew CJoint((btSoftBody::CJoint*)j);
	};
	throw gcnew NotImplementedException();
}

void AlignedJointArray_SetDefault(btSoftBody::tJointArray* jointArray,
	int index, btSoftBody::Joint* link)
{
	(*jointArray)[index] = link;
}
void AlignedJointArray::default::set(int index, BulletSharp::SoftBody::Joint^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedJointArray_SetDefault(Native, index, GetUnmanagedNullable(value));
}
#endif


#undef Native
#define Native (static_cast<btManifoldArray*>(_native))

AlignedManifoldArray::AlignedManifoldArray(btManifoldArray* manifoldArray)
: AlignedObjectArray(manifoldArray)
{
}

AlignedManifoldArray::AlignedManifoldArray()
: AlignedObjectArray(new btCollisionObjectArray(), true)
{
}

void AlignedManifoldArray::Add(PersistentManifold manifold)
{
	Native->push_back(manifold._native);
}

void AlignedManifoldArray::Clear()
{
	Native->clear();
}

bool AlignedManifoldArray::Contains(PersistentManifold manifold)
{
	return Native->findLinearSearch(manifold._native)
		!= Native->size();
}

void AlignedManifoldArray::CopyTo(array<PersistentManifold>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = PersistentManifold((*Native)[i]);
	}
}

int AlignedManifoldArray::IndexOf(PersistentManifold manifold)
{
	int i = Native->findLinearSearch(manifold._native);
	return i != Native->size() ? i : -1;
}

void AlignedManifoldArray::PopBack()
{
	Native->pop_back();
}

bool AlignedManifoldArray::Remove(PersistentManifold manifold)
{
	int sizeBefore = Native->size();
	Native->remove(manifold._native);
	return sizeBefore != Native->size();
}

int AlignedManifoldArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedManifoldArray::Count::get()
{
	return Native->size();
}

void AlignedManifoldArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

PersistentManifold AlignedManifoldArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	btPersistentManifold* obj = (*Native)[index];
	if (obj == nullptr)
		return PersistentManifold::Zero;
	return PersistentManifold(obj);
}
void AlignedManifoldArray::default::set(int index, PersistentManifold value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = value._native;
}


#undef Native
#define Native (static_cast<btAlignedObjectArray<btIndexedMesh>*>(_native))

AlignedIndexedMeshArray::AlignedIndexedMeshArray(btAlignedObjectArray<btIndexedMesh>* indexedMeshArray)
: AlignedObjectArray(indexedMeshArray)
{
}

AlignedIndexedMeshArray::AlignedIndexedMeshArray()
: AlignedObjectArray(new btAlignedObjectArray<btIndexedMesh>(), true)
{
}

void AlignedIndexedMeshArray::Add(IndexedMesh^ indexedMesh)
{
	Native->push_back(*indexedMesh->_native);
}

void AlignedIndexedMeshArray::Clear()
{
	Native->clear();
}

void AlignedIndexedMeshArray::CopyTo(array<IndexedMesh^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew IndexedMesh(&(*Native)[i], true);
	}
}

void AlignedIndexedMeshArray::PopBack()
{
	Native->pop_back();
}

int AlignedIndexedMeshArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedIndexedMeshArray::Count::get()
{
	return Native->size();
}

void AlignedIndexedMeshArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

IndexedMesh^ AlignedIndexedMeshArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	btIndexedMesh* obj = &(*Native)[index];
	if (obj == nullptr)
		return nullptr;
	return gcnew IndexedMesh(obj, true);
}

#pragma managed(push, off)
void AlignedIndexedMeshArray_SetDefault(btAlignedObjectArray<btIndexedMesh>* indexedMeshArray,
	int index, btIndexedMesh* mesh)
{
	(*indexedMeshArray)[index] = *mesh;
}
#pragma managed(pop)
void AlignedIndexedMeshArray::default::set(int index, IndexedMesh^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedIndexedMeshArray_SetDefault(Native, index, value->_native);
}


#ifndef DISABLE_SOFTBODY

#undef Native
#define Native (static_cast<btSoftBody::tLinkArray*>(_native))

AlignedLinkArray::AlignedLinkArray(btSoftBody::tLinkArray* linkArray)
: AlignedObjectArray(linkArray)
{
}

AlignedLinkArray::AlignedLinkArray()
: AlignedObjectArray(new btSoftBody::tLinkArray(), true)
{
}

void AlignedLinkArray::Add(BulletSharp::SoftBody::Link^ link)
{
	Native->push_back((btSoftBody::Link&)*link->_native);
}

void AlignedLinkArray::Clear()
{
	Native->clear();
}

void AlignedLinkArray::CopyTo(array<Link^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Link(&(*Native)[i]);
	}
}

void AlignedLinkArray::PopBack()
{
	Native->pop_back();
}

int AlignedLinkArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedLinkArray::Count::get()
{
	return Native->size();
}

void AlignedLinkArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

BulletSharp::SoftBody::Link^ AlignedLinkArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Link(&(*Native)[index]);
}

#pragma managed(push, off)
void AlignedLinkArray_SetDefault(btSoftBody::tLinkArray* linkArray,
	int index, btSoftBody::Link* link)
{
	(*linkArray)[index] = *link;
}
#pragma managed(pop)
void AlignedLinkArray::default::set(int index, BulletSharp::SoftBody::Link^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedLinkArray_SetDefault(Native, index, (btSoftBody::Link*)GetUnmanagedNullable(value));
}


#undef Native
#define Native (static_cast<btSoftBody::tMaterialArray*>(_native))

AlignedMaterialArray::AlignedMaterialArray(btSoftBody::tMaterialArray* materialArray)
: AlignedObjectArray(materialArray)
{
}

AlignedMaterialArray::AlignedMaterialArray()
: AlignedObjectArray(new btSoftBody::tMaterialArray(), true)
{
}

void AlignedMaterialArray::Add(BulletSharp::SoftBody::Material^ material)
{
	Native->push_back((btSoftBody::Material*)material->_native);
}

void AlignedMaterialArray::Clear()
{
	Native->clear();
}

bool AlignedMaterialArray::Contains(BulletSharp::SoftBody::Material^ material)
{
	return Native->findLinearSearch((btSoftBody::Material*)material->_native)
		!= Native->size();
}

void AlignedMaterialArray::CopyTo(array<BulletSharp::SoftBody::Material^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Material((*Native)[i]);
	}
}

int AlignedMaterialArray::IndexOf(BulletSharp::SoftBody::Material^ material)
{
	int i = Native->findLinearSearch((btSoftBody::Material*)material->_native);
	return i != Native->size() ? i : -1;
}

void AlignedMaterialArray::PopBack()
{
	Native->pop_back();
}

bool AlignedMaterialArray::Remove(BulletSharp::SoftBody::Material^ material)
{
	int sizeBefore = Native->size();
	Native->remove((btSoftBody::Material*)material->_native);
	return sizeBefore != Native->size();
}

int AlignedMaterialArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedMaterialArray::Count::get()
{
	return Native->size();
}

void AlignedMaterialArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

BulletSharp::SoftBody::Material^ AlignedMaterialArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Material((*Native)[index]);
}
void AlignedMaterialArray::default::set(int index, BulletSharp::SoftBody::Material^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = (btSoftBody::Material*)GetUnmanagedNullable(value);
}


#undef Native
#define Native (static_cast<btSoftBody::tNodeArray*>(_native))

// Note: Keep "BulletSharp::SoftBody::" to avoid conflict with AlignedNodeArray in btQuantizedBvh.h
BulletSharp::SoftBody::AlignedNodeArray::AlignedNodeArray(btSoftBody::tNodeArray* AlignedNodeArray)
: AlignedObjectArray(AlignedNodeArray)
{
}

BulletSharp::SoftBody::AlignedNodeArray::AlignedNodeArray()
: AlignedObjectArray(new btSoftBody::tNodeArray(), true)
{
}

void BulletSharp::SoftBody::AlignedNodeArray::Add(Node^ node)
{
	Native->push_back((btSoftBody::Node&)*node->_native);
}

void BulletSharp::SoftBody::AlignedNodeArray::Clear()
{
	Native->clear();
}

void BulletSharp::SoftBody::AlignedNodeArray::CopyTo(array<Node^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Node(&(*Native)[i]);
	}
}

void BulletSharp::SoftBody::AlignedNodeArray::PopBack()
{
	Native->pop_back();
}

int BulletSharp::SoftBody::AlignedNodeArray::Capacity::get()
{
	return Native->capacity();
}

int BulletSharp::SoftBody::AlignedNodeArray::Count::get()
{
	return Native->size();
}

void BulletSharp::SoftBody::AlignedNodeArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

BulletSharp::SoftBody::Node^ BulletSharp::SoftBody::AlignedNodeArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Node(&(*Native)[index]);
}

#pragma managed(push, off)
void NodeArray_SetDefault(btSoftBody::tNodeArray* AlignedNodeArray, int index, btSoftBody::Node* node)
{
	(*AlignedNodeArray)[index] = *node;
}
#pragma managed(pop)
void BulletSharp::SoftBody::AlignedNodeArray::default::set(int index, Node^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	NodeArray_SetDefault(Native, index, (btSoftBody::Node*)value->_native);
}


#undef Native
#define Native (static_cast<btAlignedObjectArray<btSoftBody::Node*>*>(_native))

AlignedNodePtrArray::AlignedNodePtrArray(btAlignedObjectArray<btSoftBody::Node*>* AlignedNodeArray)
: AlignedObjectArray(AlignedNodeArray)
{
}

AlignedNodePtrArray::AlignedNodePtrArray()
: AlignedObjectArray(new btAlignedObjectArray<btSoftBody::Node*>(), true)
{
}

void AlignedNodePtrArray::Add(BulletSharp::SoftBody::Node^ node)
{
	Native->push_back((btSoftBody::Node*)node->_native);
}

void AlignedNodePtrArray::Clear()
{
	Native->clear();
}

bool AlignedNodePtrArray::Contains(BulletSharp::SoftBody::Node^ node)
{
	return Native->findLinearSearch((btSoftBody::Node*)node->_native)
		!= Native->size();
}

void AlignedNodePtrArray::CopyTo(array<BulletSharp::SoftBody::Node^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Node((*Native)[i]);
	}
}

int AlignedNodePtrArray::IndexOf(BulletSharp::SoftBody::Node^ node)
{
	int i = Native->findLinearSearch((btSoftBody::Node*)node->_native);
	return i != Native->size() ? i : -1;
}

void AlignedNodePtrArray::PopBack()
{
	Native->pop_back();
}

bool AlignedNodePtrArray::Remove(BulletSharp::SoftBody::Node^ node)
{
	int sizeBefore = Native->size();
	Native->remove((btSoftBody::Node*)node->_native);
	return sizeBefore != Native->size();
}

int AlignedNodePtrArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedNodePtrArray::Count::get()
{
	return Native->size();
}

void AlignedNodePtrArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

BulletSharp::SoftBody::Node^ AlignedNodePtrArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Node((*Native)[index]);
}
void AlignedNodePtrArray::default::set(int index, BulletSharp::SoftBody::Node^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = (btSoftBody::Node*)GetUnmanagedNullable(value);
}


#undef Native
#define Native (static_cast<btSoftBody::tNoteArray*>(_native))

AlignedNoteArray::AlignedNoteArray(btSoftBody::tNoteArray* noteArray)
: AlignedObjectArray(noteArray)
{
}

AlignedNoteArray::AlignedNoteArray()
: AlignedObjectArray(new btSoftBody::tNoteArray(), true)
{
}

void AlignedNoteArray::Add(Note^ note)
{
	Native->push_back((btSoftBody::Note&)*note->_native);
}

void AlignedNoteArray::Clear()
{
	Native->clear();
}

void AlignedNoteArray::CopyTo(array<Note^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Note(&(*Native)[i]);
	}
}

void AlignedNoteArray::PopBack()
{
	Native->pop_back();
}

int AlignedNoteArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedNoteArray::Count::get()
{
	return Native->size();
}

void AlignedNoteArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

BulletSharp::SoftBody::Note^ AlignedNoteArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Note(&(*Native)[index]);
}

#pragma managed(push, off)
void NoteArray_SetDefault(btSoftBody::tNoteArray* noteArray, int index, btSoftBody::Note* note)
{
	(*noteArray)[index] = *note;
}
#pragma managed(pop)
void AlignedNoteArray::default::set(int index, Note^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	NoteArray_SetDefault(Native, index, (btSoftBody::Note*)GetUnmanagedNullable(value));
}


#undef Native
#define Native (static_cast<btSoftBody::tPSolverArray*>(_native))

AlignedPSolverArray::AlignedPSolverArray(btSoftBody::tPSolverArray* pSolverArray)
: AlignedObjectArray(pSolverArray)
{
}

AlignedPSolverArray::AlignedPSolverArray()
: AlignedObjectArray(new btSoftBody::tPSolverArray(), true)
{
}

void AlignedPSolverArray::Add(PSolver solver)
{
	Native->push_back((btSoftBody::ePSolver::_)solver);
}

void AlignedPSolverArray::Clear()
{
	Native->clear();
}

bool AlignedPSolverArray::Contains(PSolver solver)
{
	return Native->findLinearSearch((btSoftBody::ePSolver::_)solver)
		!= Native->size();
}

void AlignedPSolverArray::CopyTo(array<PSolver>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (PSolver)(*Native)[i];
	}
}

int AlignedPSolverArray::IndexOf(PSolver solver)
{
	int i = Native->findLinearSearch((btSoftBody::ePSolver::_)solver);
	return i != Native->size() ? i : -1;
}

void AlignedPSolverArray::PopBack()
{
	Native->pop_back();
}

bool AlignedPSolverArray::Remove(PSolver solver)
{
	int sizeBefore = Native->size();
	Native->remove((btSoftBody::ePSolver::_)solver);
	return sizeBefore != Native->size();
}

int AlignedPSolverArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedPSolverArray::Count::get()
{
	return Native->size();
}

void AlignedPSolverArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

PSolver AlignedPSolverArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return (PSolver)(*Native)[index];
}
void AlignedPSolverArray::default::set(int index, PSolver value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = (btSoftBody::ePSolver::_)value;
}


#undef Native
#define Native (static_cast<btSoftBody::tRContactArray*>(_native))

AlignedRigidContactArray::AlignedRigidContactArray(btSoftBody::tRContactArray* rigidContactArray)
: AlignedObjectArray(rigidContactArray)
{
}

AlignedRigidContactArray::AlignedRigidContactArray()
: AlignedObjectArray(new btSoftBody::tRContactArray(), true)
{
}

void AlignedRigidContactArray::Add(RigidContact^ rigidContact)
{
	Native->push_back(*rigidContact->_native);
}

void AlignedRigidContactArray::Clear()
{
	Native->clear();
}

void AlignedRigidContactArray::CopyTo(array<RigidContact^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew RigidContact(&(*Native)[i]);
	}
}

void AlignedRigidContactArray::PopBack()
{
	Native->pop_back();
}

void AlignedRigidContactArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

int AlignedRigidContactArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedRigidContactArray::Count::get()
{
	return Native->size();
}

BulletSharp::SoftBody::RigidContact^ AlignedRigidContactArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew RigidContact(&(*Native)[index]);
}

#pragma managed(push, off)
void AlignedRigidContactArray_SetDefault(btSoftBody::tRContactArray* rigidContactArray,
	int index, btSoftBody::RContact* rigidContact)
{
	(*rigidContactArray)[index] = *rigidContact;
}
#pragma managed(pop)
void AlignedRigidContactArray::default::set(int index, RigidContact^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedRigidContactArray_SetDefault(Native, index, value->_native);
}
#endif


#undef Native
#define Native (static_cast<btAlignedObjectArray<btScalar>*>(_native))

AlignedScalarArray::AlignedScalarArray(btAlignedObjectArray<btScalar>* btScalarArray)
: AlignedObjectArray(btScalarArray)
{
}

AlignedScalarArray::AlignedScalarArray()
: AlignedObjectArray(new btAlignedObjectArray<btScalar>, true)
{
}

void AlignedScalarArray::Add(btScalar intValue)
{
	Native->push_back(intValue);
}

void AlignedScalarArray::Clear()
{
	Native->clear();
}

bool AlignedScalarArray::Contains(btScalar scalar)
{
	return Native->findLinearSearch(scalar)
		!= Native->size();
}

void AlignedScalarArray::CopyTo(array<btScalar>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (*Native)[i];
	}
}

int AlignedScalarArray::IndexOf(btScalar scalar)
{
	int i = Native->findLinearSearch(scalar);
	return i != Native->size() ? i : -1;
}

void AlignedScalarArray::PopBack()
{
	Native->pop_back();
}

bool AlignedScalarArray::Remove(btScalar scalar)
{
	int sizeBefore = Native->size();
	Native->remove(scalar);
	return sizeBefore != Native->size();
}

int AlignedScalarArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedScalarArray::Count::get()
{
	return Native->size();
}

void AlignedScalarArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

btScalar AlignedScalarArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return (*Native)[index];
}
void AlignedScalarArray::default::set(int index, btScalar value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = value;
}


#ifndef DISABLE_SOFTBODY

#undef Native
#define Native static_cast<btSoftBody::tSoftBodyArray*>(_native)

BulletSharp::SoftBody::AlignedSoftBodyArray::AlignedSoftBodyArray(btSoftBody::tSoftBodyArray* softBodyArray)
: AlignedObjectArray(softBodyArray)
{
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::Add(SoftBody^ softBody)
{
	Native->push_back((btSoftBody*)softBody->_native);
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::Clear()
{
	Native->clear();
}

bool BulletSharp::SoftBody::AlignedSoftBodyArray::Contains(SoftBody^ softBody)
{
	return Native->findLinearSearch((btSoftBody*)softBody->_native) != Native->size();
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::CopyTo(array<SoftBody^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = dynamic_cast<SoftBody^>(CollisionObject::GetManaged((*Native)[i]));
	}
}

int BulletSharp::SoftBody::AlignedSoftBodyArray::IndexOf(SoftBody^ softBody)
{
	int i = Native->findLinearSearch((btSoftBody*)softBody->_native);
	return i != Native->size() ? i : -1;
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::PopBack()
{
	Native->pop_back();
}

bool BulletSharp::SoftBody::AlignedSoftBodyArray::Remove(SoftBody^ softBody)
{
	int sizeBefore = Native->size();
	Native->remove((btSoftBody*)softBody->_native);
	return sizeBefore != Native->size();
}

int BulletSharp::SoftBody::AlignedSoftBodyArray::Capacity::get()
{
	return Native->capacity();
}

int BulletSharp::SoftBody::AlignedSoftBodyArray::Count::get()
{
	return Native->size();
}

void BulletSharp::SoftBody::AlignedSoftBodyArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

BulletSharp::SoftBody::SoftBody^ BulletSharp::SoftBody::AlignedSoftBodyArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return (SoftBody^)CollisionObject::GetManaged((*Native)[index]);
}
void BulletSharp::SoftBody::AlignedSoftBodyArray::default::set(int index, SoftBody^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = (btSoftBody*)GetUnmanagedNullable(value);
}


#undef Native
#define Native static_cast<btSoftBody::tSContactArray*>(_native)

AlignedSoftContactArray::AlignedSoftContactArray(btSoftBody::tSContactArray* softContactArray)
: AlignedObjectArray(softContactArray)
{
}

AlignedSoftContactArray::AlignedSoftContactArray()
: AlignedObjectArray(new btSoftBody::tSContactArray(), true)
{
}

void AlignedSoftContactArray::Add(SoftContact^ softContact)
{
	Native->push_back(*softContact->_native);
}

void AlignedSoftContactArray::Clear()
{
	Native->clear();
}

void AlignedSoftContactArray::CopyTo(array<SoftContact^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew SoftContact(&(*Native)[i]);
	}
}

void AlignedSoftContactArray::PopBack()
{
	Native->pop_back();
}

void AlignedSoftContactArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

int AlignedSoftContactArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedSoftContactArray::Count::get()
{
	return Native->size();
}

BulletSharp::SoftBody::SoftContact^ AlignedSoftContactArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew SoftContact(&(*Native)[index]);
}

#pragma managed(push, off)
void AlignedSoftContactArray_SetDefault(btSoftBody::tSContactArray* softContactArray,
	int index, btSoftBody::SContact* softContact)
{
	(*softContactArray)[index] = *softContact;
}
#pragma managed(pop)
void AlignedSoftContactArray::default::set(int index, SoftContact^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	AlignedSoftContactArray_SetDefault(Native, index, value->_native);
}


#undef Native
#define Native static_cast<btAlignedObjectArray<btSoftBody::Tetra>*>(_native)

AlignedTetraArray::AlignedTetraArray(btAlignedObjectArray<btSoftBody::Tetra>* tetraArray)
: AlignedObjectArray(tetraArray)
{
}

AlignedTetraArray::AlignedTetraArray()
: AlignedObjectArray(new btAlignedObjectArray<btSoftBody::Tetra>, true)
{
}

void AlignedTetraArray::Add(Tetra^ tetra)
{
	Native->push_back((btSoftBody::Tetra&)*tetra->_native);
}

void AlignedTetraArray::Clear()
{
	Native->clear();
}

void AlignedTetraArray::CopyTo(array<Tetra^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew Tetra(&(*Native)[i]);
	}
}

void AlignedTetraArray::PopBack()
{
	Native->pop_back();
}

void AlignedTetraArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

int AlignedTetraArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedTetraArray::Count::get()
{
	return Native->size();
}

Tetra^ AlignedTetraArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew Tetra(&(*Native)[index]);
}

#pragma managed(push, off)
void TetraArray_SetDefault(btAlignedObjectArray<btSoftBody::Tetra>* tetraArray,
	int index, btSoftBody::Tetra* node)
{
	(*tetraArray)[index] = *node;
}
#pragma managed(pop)
void AlignedTetraArray::default::set(int index, Tetra^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	TetraArray_SetDefault(Native, index, (btSoftBody::Tetra*)value->_native);
}
#endif


#undef Native
#define Native static_cast<btAlignedObjectArray<btTriangleMesh*>*>(_native)

AlignedTriangleMeshArray::AlignedTriangleMeshArray(btAlignedObjectArray<btTriangleMesh*>* triangleMeshArray)
: AlignedObjectArray(triangleMeshArray)
{
}

AlignedTriangleMeshArray::AlignedTriangleMeshArray()
: AlignedObjectArray(new btAlignedObjectArray<btTriangleMesh*>, true)
{
}

void AlignedTriangleMeshArray::Add(TriangleMesh^ triangleMesh)
{
	Native->push_back((btTriangleMesh*)triangleMesh->_native);
}

void AlignedTriangleMeshArray::Clear()
{
	Native->clear();
}

void AlignedTriangleMeshArray::CopyTo(array<TriangleMesh^>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = gcnew TriangleMesh((*Native)[i]);
	}
}

void AlignedTriangleMeshArray::PopBack()
{
	Native->pop_back();
}

int AlignedTriangleMeshArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedTriangleMeshArray::Count::get()
{
	return Native->size();
}

void AlignedTriangleMeshArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

TriangleMesh^ AlignedTriangleMeshArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return gcnew TriangleMesh((*Native)[index]);
}

void AlignedTriangleMeshArray::default::set(int index, TriangleMesh^ value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = (btTriangleMesh*)GetUnmanagedNullable(value);
}


#undef Native
#define Native static_cast<btAlignedObjectArray<btVector3>*>(_native)

AlignedVector3Array::AlignedVector3Array(btAlignedObjectArray<btVector3>* vector3Array)
: AlignedObjectArray(vector3Array)
{
}

AlignedVector3Array::AlignedVector3Array()
: AlignedObjectArray(new btAlignedObjectArray<btVector3>, true)
{
}

void AlignedVector3Array::Add(Vector3 vector3Value)
{
	VECTOR3_CONV(vector3Value);
	Native->push_back(VECTOR3_USE(vector3Value));
	VECTOR3_DEL(vector3Value);
}

void AlignedVector3Array::Add(Vector4 vector4Value)
{
	btVector4* tempVector4Value = Math::Vector4ToBtVector4(vector4Value);
	Native->push_back(*tempVector4Value);
	delete tempVector4Value;
}

void AlignedVector3Array::Clear()
{
	Native->clear();
}

bool AlignedVector3Array::Contains(Vector3 vector)
{
	VECTOR3_CONV(vector);
	int i = Native->findLinearSearch(VECTOR3_USE(vector));
	VECTOR3_DEL(vector);
	return i != Native->size();
}

void AlignedVector3Array::CopyTo(array<Vector3>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		Math::BtVector3ToVector3(&(*Native)[i], array[arrayIndex+i]);
	}
}

int AlignedVector3Array::IndexOf(Vector3 vector)
{
	VECTOR3_CONV(vector);
	int i = Native->findLinearSearch(VECTOR3_USE(vector));
	VECTOR3_DEL(vector);
	return i != Native->size() ? i : -1;
}

void AlignedVector3Array::PopBack()
{
	Native->pop_back();
}

bool AlignedVector3Array::Remove(Vector3 vector)
{
	int sizeBefore = Native->size();
	VECTOR3_CONV(vector);
	Native->remove(VECTOR3_USE(vector));
	VECTOR3_DEL(vector);
	return sizeBefore != Native->size();
}

int AlignedVector3Array::Capacity::get()
{
	return Native->capacity();
}

int AlignedVector3Array::Count::get()
{
	return Native->size();
}

void AlignedVector3Array::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

Vector3 AlignedVector3Array::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return Math::BtVector3ToVector3(&(*Native)[index]);
}
void AlignedVector3Array::default::set(int index, Vector3 value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	Math::Vector3ToBtVector3(value, &(*Native)[index]);
}


#ifndef DISABLE_SOFTBODY

#undef Native
#define Native static_cast<btSoftBody::tVSolverArray*>(_native)

AlignedVSolverArray::AlignedVSolverArray(btSoftBody::tVSolverArray* vSolverArray)
: AlignedObjectArray(vSolverArray)
{
}

AlignedVSolverArray::AlignedVSolverArray()
: AlignedObjectArray(new btSoftBody::tVSolverArray(), true)
{
}

void AlignedVSolverArray::Add(VSolver solver)
{
	Native->push_back((btSoftBody::eVSolver::_)solver);
}

void AlignedVSolverArray::Clear()
{
	Native->clear();
}

bool AlignedVSolverArray::Contains(VSolver solver)
{
	return Native->findLinearSearch((btSoftBody::eVSolver::_)solver)
		!= Native->size();
}

void AlignedVSolverArray::CopyTo(array<VSolver>^ array, int arrayIndex)
{
	if (array == nullptr)
		throw gcnew ArgumentNullException("array");

	if (arrayIndex < 0)
		throw gcnew ArgumentOutOfRangeException("array");

	int size = Native->size();
	if (arrayIndex + size > array->Length)
		throw gcnew ArgumentException("Array too small.", "array");

	int i;
	for (i=0; i<size; i++)
	{
		array[arrayIndex+i] = (VSolver)(*Native)[i];
	}
}

int AlignedVSolverArray::IndexOf(VSolver solver)
{
	int i = Native->findLinearSearch((btSoftBody::eVSolver::_)solver);
	return i != Native->size() ? i : -1;
}

void AlignedVSolverArray::PopBack()
{
	Native->pop_back();
}

bool AlignedVSolverArray::Remove(VSolver solver)
{
	int sizeBefore = Native->size();
	Native->remove((btSoftBody::eVSolver::_)solver);
	return sizeBefore != Native->size();
}

int AlignedVSolverArray::Capacity::get()
{
	return Native->capacity();
}

int AlignedVSolverArray::Count::get()
{
	return Native->size();
}

void AlignedVSolverArray::Swap(int index0, int index1)
{
	Native->swap(index0, index1);
}

VSolver AlignedVSolverArray::default::get(int index)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	return (VSolver)(*Native)[index];
}
void AlignedVSolverArray::default::set(int index, VSolver value)
{
	if ((unsigned int)index >= (unsigned int)Native->size())
		throw gcnew ArgumentOutOfRangeException("index");
	(*Native)[index] = (btSoftBody::eVSolver::_)value;
}
#endif
