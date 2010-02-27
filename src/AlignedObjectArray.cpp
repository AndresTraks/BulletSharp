#include "StdAfx.h"

#include "AlignedObjectArray.h"
#include "CollisionShape.h"

generic <class T>
AlignedObjectArray<T>::AlignedObjectArray()
{
	_alignedObjectArray = new btAlignedObjectArray<btCollisionShape*>();
}

generic <class T>
AlignedObjectArray<T>::!AlignedObjectArray()
{
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_alignedObjectArray = NULL;

	OnDisposed( this, nullptr );
}

generic <class T>
AlignedObjectArray<T>::~AlignedObjectArray()
{
	this->!AlignedObjectArray();
}

generic <class T>
void AlignedObjectArray<T>::PushBack(CollisionShape^ collisionShape)
{
	_alignedObjectArray->push_back(collisionShape->UnmanagedPointer);
}

generic <class T>
CollisionShape^ AlignedObjectArray<T>::default::get(int index)
{
	return gcnew CollisionShape((*_alignedObjectArray)[index]);
}
generic <class T>
void AlignedObjectArray<T>::default::set(int index, CollisionShape^ value)
{
	(*_alignedObjectArray)[index] = value->UnmanagedPointer;
}

void CollisionObjectArray::PushBack(CollisionObject^ collisionObject)
{
	_alignedObjectArray->push_back(collisionObject->UnmanagedPointer);
}