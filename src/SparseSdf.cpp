#include "StdAfx.h"

#pragma managed(push, off)
#include <BulletSoftBody/btSparseSdf.h>
#pragma managed(pop)

#include "SparseSdf.h"

SparseSdf::SparseSdf(btSparseSdf<3>* sdf)
{
	_sdf = sdf;
}

void SparseSdf::GarbageCollect(int lifetime)
{
	_sdf->GarbageCollect(lifetime);
}

void SparseSdf::GarbageCollect()
{
	_sdf->GarbageCollect();
}

void SparseSdf::Initialize(int hashSize)
{
	_sdf->Initialize(hashSize);
}

void SparseSdf::Initialize()
{
	_sdf->Initialize();
}

void SparseSdf::Reset()
{
	_sdf->Reset();
}

btSparseSdf<3>* SparseSdf::UnmanagedPointer::get()
{
	return _sdf;
}
void SparseSdf::UnmanagedPointer::set(btSparseSdf<3>* value)
{
	_sdf = value;
}
