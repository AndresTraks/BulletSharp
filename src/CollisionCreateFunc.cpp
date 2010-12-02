#include "StdAfx.h"

#include "CollisionAlgorithm.h"
#include "CollisionCreateFunc.h"
#include "CollisionObject.h"

CollisionAlgorithmCreateFunc::CollisionAlgorithmCreateFunc()
{
	_createFunc = new btCollisionAlgorithmCreateFunc();
}

CollisionAlgorithmCreateFunc::CollisionAlgorithmCreateFunc(btCollisionAlgorithmCreateFunc* createFunc)
{
	_createFunc = createFunc;
}

CollisionAlgorithmCreateFunc::~CollisionAlgorithmCreateFunc()
{
	this->!CollisionAlgorithmCreateFunc();
}

CollisionAlgorithmCreateFunc::!CollisionAlgorithmCreateFunc()
{
	if (this->IsDisposed)
		return;
	
	OnDisposing( this, nullptr );
	
	_createFunc = NULL;
	
	OnDisposed( this, nullptr );
}

CollisionAlgorithm^ CollisionAlgorithmCreateFunc::CreateCollisionAlgorithm(
	CollisionAlgorithmConstructionInfo^ info, CollisionObject^ body0, CollisionObject^ body1)
{
	return gcnew CollisionAlgorithm(UnmanagedPointer->CreateCollisionAlgorithm(
		*info->UnmanagedPointer, body0->UnmanagedPointer, body1->UnmanagedPointer));
}

bool CollisionAlgorithmCreateFunc::IsDisposed::get()
{
	return (_createFunc == NULL);
}

bool CollisionAlgorithmCreateFunc::Swapped::get()
{
	return _createFunc->m_swapped;
}
void CollisionAlgorithmCreateFunc::Swapped::set(bool value)
{
	_createFunc->m_swapped = value;
}

btCollisionAlgorithmCreateFunc* CollisionAlgorithmCreateFunc::UnmanagedPointer::get()
{
	return _createFunc;
}
void CollisionAlgorithmCreateFunc::UnmanagedPointer::set(btCollisionAlgorithmCreateFunc* value)
{
	_createFunc = value;
}
