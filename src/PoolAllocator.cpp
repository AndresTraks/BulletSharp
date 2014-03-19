#include "StdAfx.h"

#ifndef DISABLE_UNCOMMON

#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(btPoolAllocator* native)
{
	_native = native;
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

void PoolAllocator::FreeMemory(IntPtr ptr)
{
	_native->freeMemory(ptr.ToPointer());
}

bool PoolAllocator::ValidPtr(IntPtr ptr)
{
	return _native->validPtr(ptr.ToPointer());
}

int PoolAllocator::ElementSize::get()
{
	return _native->getElementSize();
}

int PoolAllocator::FreeCount::get()
{
	return _native->getFreeCount();
}

bool PoolAllocator::IsDisposed::get()
{
	return (_native == NULL);
}

int PoolAllocator::MaxCount::get()
{
	return _native->getMaxCount();
}

IntPtr PoolAllocator::PoolAddress::get()
{
	return IntPtr(_native->getPoolAddress());
}

int PoolAllocator::UsedCount::get()
{
	return _native->getUsedCount();
}

#endif

