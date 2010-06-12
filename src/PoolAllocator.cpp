#include "StdAfx.h"

#pragma managed(push, off)
#include <LinearMath/btPoolAllocator.h>
#pragma managed(pop)

#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(btPoolAllocator* allocator)
{
	_allocator = allocator;
}

PoolAllocator::PoolAllocator(int elemSize, int maxElements)
{
	_allocator = new btPoolAllocator(elemSize, maxElements);
}

PoolAllocator::~PoolAllocator()
{
	this->!PoolAllocator();
}

PoolAllocator::!PoolAllocator()
{
	if( this->IsDisposed == true )
		return;

	OnDisposing( this, nullptr );

	_allocator = NULL;

	OnDisposed( this, nullptr );
}

IntPtr PoolAllocator::Allocate(int size)
{
	return IntPtr(_allocator->allocate(size));
}

bool PoolAllocator::ValidPtr(IntPtr ptr)
{
	return _allocator->validPtr(ptr.ToPointer());
}

void PoolAllocator::FreeMemory(IntPtr ptr)
{
	_allocator->freeMemory(ptr.ToPointer());
}

bool PoolAllocator::IsDisposed::get()
{
	return (_allocator == NULL);
}

int PoolAllocator::ElementSize::get()
{
	return _allocator->getElementSize();
}

int PoolAllocator::FreeCount::get()
{
	return _allocator->getFreeCount();
}

btPoolAllocator* PoolAllocator::UnmanagedPointer::get()
{
	return _allocator;
}
void PoolAllocator::UnmanagedPointer::set(btPoolAllocator* value)
{
	_allocator = value;
}
