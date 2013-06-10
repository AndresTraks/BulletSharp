#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(btPoolAllocator* allocator)
{
	_native = allocator;
}

PoolAllocator::PoolAllocator(int elemSize, int maxElements)
{
	_native = new btPoolAllocator(elemSize, maxElements);
}

PoolAllocator::~PoolAllocator()
{
	this->!PoolAllocator();
}

PoolAllocator::!PoolAllocator()
{
	if (this->IsDisposed)
		return;

	OnDisposing(this, nullptr);

	_native = NULL;

	OnDisposed(this, nullptr);
}

IntPtr PoolAllocator::Allocate(int size)
{
	return IntPtr(_native->allocate(size));
}

bool PoolAllocator::ValidPtr(IntPtr ptr)
{
	return _native->validPtr(ptr.ToPointer());
}

void PoolAllocator::FreeMemory(IntPtr ptr)
{
	_native->freeMemory(ptr.ToPointer());
}

bool PoolAllocator::IsDisposed::get()
{
	return (_native == NULL);
}

int PoolAllocator::ElementSize::get()
{
	return _native->getElementSize();
}

int PoolAllocator::FreeCount::get()
{
	return _native->getFreeCount();
}

int PoolAllocator::MaxCount::get()
{
	return _native->getMaxCount();
}

#endif
