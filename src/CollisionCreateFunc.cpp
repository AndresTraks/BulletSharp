#include "StdAfx.h"

#include "CollisionAlgorithm.h"
#include "CollisionCreateFunc.h"
#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"

CollisionAlgorithmCreateFunc::CollisionAlgorithmCreateFunc()
{
	_native = new btCollisionAlgorithmCreateFunc();
	_deleteObject = true;
}

CollisionAlgorithmCreateFunc::CollisionAlgorithmCreateFunc(btCollisionAlgorithmCreateFunc* createFunc)
{
	_native = createFunc;
}

CollisionAlgorithmCreateFunc::~CollisionAlgorithmCreateFunc()
{
	this->!CollisionAlgorithmCreateFunc();
}

CollisionAlgorithmCreateFunc::!CollisionAlgorithmCreateFunc()
{
	if (_deleteObject)
	{
		delete _native;
		_native = NULL;
	}
}

CollisionAlgorithm^ CollisionAlgorithmCreateFunc::CreateCollisionAlgorithm(
	CollisionAlgorithmConstructionInfo^ info, CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
{
	return gcnew CollisionAlgorithm(UnmanagedPointer->CreateCollisionAlgorithm(
		*info->_native, body0Wrap->_native, body1Wrap->_native));
}

bool CollisionAlgorithmCreateFunc::IsDisposed::get()
{
	return (_native == NULL);
}

bool CollisionAlgorithmCreateFunc::Swapped::get()
{
	return _native->m_swapped;
}
void CollisionAlgorithmCreateFunc::Swapped::set(bool value)
{
	_native->m_swapped = value;
}

btCollisionAlgorithmCreateFunc* CollisionAlgorithmCreateFunc::UnmanagedPointer::get()
{
	return _native;
}
void CollisionAlgorithmCreateFunc::UnmanagedPointer::set(btCollisionAlgorithmCreateFunc* value)
{
	_native = value;
}
