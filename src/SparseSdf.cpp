#include "StdAfx.h"

#ifndef DISABLE_SOFTBODY

#include "CollisionShape.h"
#include "SparseSdf.h"

SparseSdf::SparseSdf(btSparseSdf<3>* native)
{
	_native = native;
}

void SparseSdf::GarbageCollect(int lifetime)
{
	_native->GarbageCollect(lifetime);
}

void SparseSdf::GarbageCollect()
{
	_native->GarbageCollect();
}

void SparseSdf::Initialize(int hashSize)
{
	_native->Initialize(hashSize);
}

void SparseSdf::Initialize()
{
	_native->Initialize();
}

int SparseSdf::RemoveReferences(CollisionShape^ pcs)
{
	return _native->RemoveReferences(GetUnmanagedNullable(pcs));
}

void SparseSdf::Reset()
{
	_native->Reset();
}

#endif
