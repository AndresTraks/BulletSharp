#include "StdAfx.h"

#include "CollisionAlgorithm.h"
#include "CollisionCreateFunc.h"
#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"

CollisionAlgorithmCreateFunc::CollisionAlgorithmCreateFunc(btCollisionAlgorithmCreateFunc* native, bool preventDelete)
{
	_native = native;
	_preventDelete = preventDelete;
}

CollisionAlgorithmCreateFunc::~CollisionAlgorithmCreateFunc()
{
	this->!CollisionAlgorithmCreateFunc();
}

CollisionAlgorithmCreateFunc::!CollisionAlgorithmCreateFunc()
{
	if (!_preventDelete)
	{
		delete _native;
	}
	_native = NULL;
}

CollisionAlgorithmCreateFunc::CollisionAlgorithmCreateFunc()
{
	_native = new btCollisionAlgorithmCreateFunc();
}

CollisionAlgorithm^ CollisionAlgorithmCreateFunc::CreateCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ info,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap)
{
	return CollisionAlgorithm::GetManaged(_native->CreateCollisionAlgorithm(
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
