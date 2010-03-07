#include "StdAfx.h"

#include "StackAlloc.h"

StackAlloc::StackAlloc(btStackAlloc* alloc)
{
	_alloc = alloc;
}

btStackAlloc* StackAlloc::UnmanagedPointer::get()
{
	return _alloc;
}

void StackAlloc::UnmanagedPointer::set(btStackAlloc* value)
{
	_alloc = value;
}
