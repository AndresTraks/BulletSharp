#include "StdAfx.h"

#ifndef DISABLE_COLLISION_ALGORITHMS

#include "CollisionShape.h"
#include "CollisionObject.h"
#include "CollisionObjectWrapper.h"
#include "CompoundCollisionAlgorithm.h"
#include "PersistentManifold.h"

CompoundCollisionAlgorithm::CreateFunc::CreateFunc()
: CollisionAlgorithmCreateFunc(new btCompoundCollisionAlgorithm::CreateFunc())
{
}

CompoundCollisionAlgorithm::SwappedCreateFunc::SwappedCreateFunc()
: CollisionAlgorithmCreateFunc(new btCompoundCollisionAlgorithm::SwappedCreateFunc())
{
}

#define Native static_cast<btCompoundCollisionAlgorithm*>(_native)

bool compoundChildShapePairCallback(const btCollisionShape* pShape0, const btCollisionShape* pShape1)
{
	return CompoundCollisionAlgorithm::_compoundChildShapePairCallback(
		CollisionShape::GetManaged((btCollisionShape*)pShape0),
		CollisionShape::GetManaged((btCollisionShape*)pShape1));
}

CompoundChildShapePairCallback^ CompoundCollisionAlgorithm::CompoundChildShapePairCallback::get()
{
	return _compoundChildShapePairCallback;
}
void CompoundCollisionAlgorithm::CompoundChildShapePairCallback::set(::CompoundChildShapePairCallback^ value)
{
	if (value != nullptr)
	{
		_compoundChildShapePairCallback = value;
		gCompoundChildShapePairCallback = compoundChildShapePairCallback;
	}
	else
	{
		gCompoundChildShapePairCallback = 0;
		_compoundChildShapePairCallback = nullptr;
	}
}

CompoundCollisionAlgorithm::CompoundCollisionAlgorithm(CollisionAlgorithmConstructionInfo^ ci,
	CollisionObjectWrapper^ body0Wrap, CollisionObjectWrapper^ body1Wrap, bool isSwapped)
: ActivatingCollisionAlgorithm(new btCompoundCollisionAlgorithm(*ci->_native,
	body0Wrap->_native, body1Wrap->_native, isSwapped))
{
}

CollisionAlgorithm^ CompoundCollisionAlgorithm::GetChildAlgorithm (int n)
{
	return gcnew CollisionAlgorithm(Native->getChildAlgorithm(n));
}

#endif
