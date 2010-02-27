#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "PersistentManifold.h"

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
