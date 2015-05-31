#include "StdAfx.h"

#include "CollisionObject.h"
#include "ManifoldPoint.h"
#include "PersistentManifold.h"

PersistentManifold::PersistentManifold(btPersistentManifold* native)
{
	_native = native;
}

#ifdef BT_CALLBACKS_ARE_EVENTS
bool onContactDestroyed(void* userPersistentData)
{
	PersistentManifold::_contactDestroyed(VoidPtrToGCHandle(userPersistentData).Target);
	VoidPtrToGCHandle(userPersistentData).Free();
	return false;
}

bool onContactProcessed(btManifoldPoint& cp, void* body0, void* body1)
{
	PersistentManifold::_contactProcessed(gcnew ManifoldPoint(&cp, true),
		CollisionObject::GetManaged((btCollisionObject*)body0),
		CollisionObject::GetManaged((btCollisionObject*)body1));
	return false;
}

void PersistentManifold::ContactDestroyed::add(ContactDestroyedEventHandler^ callback)
{
	gContactDestroyedCallback = onContactDestroyed;
	_contactDestroyed += callback;
}
void PersistentManifold::ContactDestroyed::remove(ContactDestroyedEventHandler^ callback)
{
	_contactDestroyed -= callback;
	if (!_contactDestroyed)
	{
		gContactDestroyedCallback = 0;
	}
}

void PersistentManifold::ContactProcessed::add(ContactProcessedEventHandler^ callback)
{
	gContactProcessedCallback = onContactProcessed;
	_contactProcessed += callback;
}
void PersistentManifold::ContactProcessed::remove(ContactProcessedEventHandler^ callback)
{
	_contactProcessed -= callback;
	if (!_contactProcessed)
	{
		gContactProcessedCallback = 0;
	}
}
#else
bool onContactDestroyed(void* userPersistentData)
{
	bool ret = PersistentManifold::_contactDestroyed(VoidPtrToGCHandle(userPersistentData).Target);
	VoidPtrToGCHandle(userPersistentData).Free();
	return ret;
}

bool onContactProcessed(btManifoldPoint& cp, void* body0, void* body1)
{
	return PersistentManifold::_contactProcessed(gcnew ManifoldPoint(&cp, true),
		CollisionObject::GetManaged((btCollisionObject*)body0),
		CollisionObject::GetManaged((btCollisionObject*)body1));
}

ContactDestroyed^ PersistentManifold::ContactDestroyed::get()
{
	return _contactDestroyed;
}
void PersistentManifold::ContactDestroyed::set(::ContactDestroyed^ value)
{
	if (value != nullptr)
	{
		_contactDestroyed = value;
		gContactDestroyedCallback = onContactDestroyed;
	}
	else
	{
		gContactDestroyedCallback = 0;
		_contactDestroyed = nullptr;
	}
}

ContactProcessed^ PersistentManifold::ContactProcessed::get()
{
	return _contactProcessed;
}
void PersistentManifold::ContactProcessed::set(::ContactProcessed^ value)
{
	if (value != nullptr)
	{
		_contactProcessed = value;
		gContactProcessedCallback = onContactProcessed;
	}
	else
	{
		gContactProcessedCallback = 0;
		_contactProcessed = nullptr;
	}
}
#endif
/*
PersistentManifold::PersistentManifold()
	: TypedObject(new btPersistentManifold(), false)	//delete on destruct
{
}

PersistentManifold::PersistentManifold(CollisionObject^ body0, CollisionObject^ body1,
	int __unnamed2, btScalar contactBreakingThreshold, btScalar contactProcessingThreshold)
	: TypedObject(new btPersistentManifold(body0->_native, body1->_native, __unnamed2,
				  contactBreakingThreshold, contactProcessingThreshold), false)	//delete on destruct
{
}
*/
int PersistentManifold::AddManifoldPoint(ManifoldPoint^ newPoint, bool isPredictive)
{
	return _native->addManifoldPoint(*newPoint->_native, isPredictive);
}

int PersistentManifold::AddManifoldPoint(ManifoldPoint^ newPoint)
{
	return _native->addManifoldPoint(*newPoint->_native);
}

void PersistentManifold::ClearManifold()
{
	_native->clearManifold();
}

void PersistentManifold::ClearUserCache(ManifoldPoint^ pt)
{
	_native->clearUserCache(*pt->_native);
}

bool PersistentManifold::Equals(Object^ value)
{
	PersistentManifold^ manifold = safe_cast<PersistentManifold^>(value);
	if (manifold)
	{
        return (_native == manifold->_native);
    }
    return false;
}

int PersistentManifold::GetCacheEntry(ManifoldPoint^ newPoint)
{
	return _native->getCacheEntry(*newPoint->_native);
}

int PersistentManifold::GetHashCode()
{
	return (int)_native;
}

ManifoldPoint^ PersistentManifold::GetContactPoint(int index)
{
	return gcnew ManifoldPoint(&_native->getContactPoint(index), true);
}

void PersistentManifold::RefreshContactPoints(Matrix trA, Matrix trB)
{
	TRANSFORM_CONV(trA);
	TRANSFORM_CONV(trB);
	_native->refreshContactPoints(TRANSFORM_USE(trA), TRANSFORM_USE(trB));
	TRANSFORM_DEL(trA);
	TRANSFORM_DEL(trB);
}

void PersistentManifold::RemoveContactPoint(int index)
{
	_native->removeContactPoint(index);
}

void PersistentManifold::ReplaceContactPoint(ManifoldPoint^ newPoint, int insertIndex)
{
	_native->replaceContactPoint(*newPoint->_native, insertIndex);
}

void PersistentManifold::SetBodies(CollisionObject^ body0, CollisionObject^ body1)
{
	_native->setBodies(body0->_native, body1->_native);
}

bool PersistentManifold::ValidContactDistance(ManifoldPoint^ pt)
{
	return _native->validContactDistance(*pt->_native);
}

bool PersistentManifold::operator== (PersistentManifold value1, PersistentManifold value2)
{
    return value1._native == value2._native;
}

bool PersistentManifold::operator!= (PersistentManifold value1, PersistentManifold value2)
{
    return value1._native != value2._native;
}

CollisionObject^ PersistentManifold::Body0::get()
{
	return CollisionObject::GetManaged((btCollisionObject*)_native->getBody0());
}

CollisionObject^ PersistentManifold::Body1::get()
{
	return CollisionObject::GetManaged((btCollisionObject*)_native->getBody1());
}

int PersistentManifold::CompanionIDA::get()
{
	return _native->m_companionIdA;
}
void PersistentManifold::CompanionIDA::set(int value)
{
	_native->m_companionIdA = value;
}

int PersistentManifold::CompanionIDB::get()
{
	return _native->m_companionIdB;
}
void PersistentManifold::CompanionIDB::set(int value)
{
	_native->m_companionIdB = value;
}

btScalar PersistentManifold::ContactBreakingThreshold::get()
{
	return _native->getContactBreakingThreshold();
}
void PersistentManifold::ContactBreakingThreshold::set(btScalar contactBreakingThreshold)
{
	_native->setContactBreakingThreshold(contactBreakingThreshold);
}

btScalar PersistentManifold::ContactProcessingThreshold::get()
{
	return _native->getContactProcessingThreshold();
}
void PersistentManifold::ContactProcessingThreshold::set(btScalar contactProcessingThreshold)
{
	_native->setContactProcessingThreshold(contactProcessingThreshold);
}

int PersistentManifold::Index1A::get()
{
	return _native->m_index1a;
}
void PersistentManifold::Index1A::set(int value)
{
	_native->m_index1a = value;
}

int PersistentManifold::NumContacts::get()
{
	return _native->getNumContacts();
}
void PersistentManifold::NumContacts::set(int cachedPoints)
{
	_native->setNumContacts(cachedPoints);
}
