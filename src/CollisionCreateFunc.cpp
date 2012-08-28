#include "StdAfx.h"

#include "CollisionAlgorithm.h"
#include "CollisionCreateFunc.h"
#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"

CollisionAlgorithmCreateFunc::CollisionAlgorithmCreateFunc()
{
	_createFunc = new btCollisionAlgorithmCreateFunc();
	_deleteObject = true;
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
	if (_deleteObject)
	{
		delete _createFunc;
		_createFunc = NULL;
	}
}

CollisionAlgorithm^ CollisionAlgorithmCreateFunc::CreateCollisionAlgorithm(
	CollisionAlgorithmConstructionInfo^ info, CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
{
	return gcnew CollisionAlgorithm(UnmanagedPointer->CreateCollisionAlgorithm(
		*info->_unmanaged, body0Wrap->_unmanaged, body1Wrap->_unmanaged));
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
