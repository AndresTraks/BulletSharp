#include "StdAfx.h"

#include "CollisionObject.h"
#include "ManifoldPoint.h"
#include "PersistentManifold.h"

#define Native static_cast<btPersistentManifold*>(_native)

PersistentManifold::PersistentManifold(btPersistentManifold* manifold)
: TypedObject(manifold)
{
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
	PersistentManifold::_contactProcessed(gcnew ManifoldPoint(&cp),
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
	return PersistentManifold::_contactProcessed(gcnew ManifoldPoint(&cp),
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

PersistentManifold::PersistentManifold()
: TypedObject(new btPersistentManifold())
{
}

int PersistentManifold::AddManifoldPoint(ManifoldPoint^ newPoint, bool isPredictive)
{
	return Native->addManifoldPoint(*newPoint->_native, isPredictive);
}

int PersistentManifold::AddManifoldPoint(ManifoldPoint^ newPoint)
{
	return Native->addManifoldPoint(*newPoint->_native);
}

void PersistentManifold::ClearManifold()
{
	return Native->clearManifold();
}

void PersistentManifold::ClearUserCache(ManifoldPoint^ pt)
{
	Native->clearUserCache(*pt->_native);
}

#ifdef DEBUG_PERSISTENCY
void PersistentManifold::DebugPersistency()
{
	Native->DebugPersistency();
}
#endif

int PersistentManifold::GetCacheEntry(ManifoldPoint^ newPoint)
{
	return Native->getCacheEntry(*newPoint->_native);
}

ManifoldPoint^ PersistentManifold::GetContactPoint(int index)
{
	return gcnew ManifoldPoint(&Native->getContactPoint(index));
}

void PersistentManifold::RefreshContactPoints(Matrix trA, Matrix trB)
{
	btTransform* trATemp = Math::MatrixToBtTransform(trA);
	btTransform* trBTemp = Math::MatrixToBtTransform(trB);

	Native->refreshContactPoints(*trATemp, *trBTemp);

	ALIGNED_FREE(trATemp);
	ALIGNED_FREE(trBTemp);
}

void PersistentManifold::RemoveContactPoint(int index)
{
	Native->removeContactPoint(index);
}

void PersistentManifold::ReplaceContactPoint(ManifoldPoint^ newPoint, int insertIndex)
{
	Native->replaceContactPoint(*newPoint->_native, insertIndex);
}

bool PersistentManifold::ValidContactDistance(ManifoldPoint^ pt)
{
	return Native->validContactDistance(*pt->_native);
}

Object^ PersistentManifold::Body0::get()
{
	return CollisionObject::GetManaged((btCollisionObject*)Native->getBody0());
}

Object^ PersistentManifold::Body1::get()
{
	return CollisionObject::GetManaged((btCollisionObject*)Native->getBody1());
}

int PersistentManifold::CompanionIDA::get()
{
	return Native->m_companionIdA;
}
void PersistentManifold::CompanionIDA::set(int value)
{
	Native->m_companionIdA = value;
}

int PersistentManifold::CompanionIDB::get()
{
	return Native->m_companionIdB;
}
void PersistentManifold::CompanionIDB::set(int value)
{
	Native->m_companionIdB = value;
}

btScalar PersistentManifold::ContactBreakingThreshold::get()
{
	return Native->getContactBreakingThreshold();
}
void PersistentManifold::ContactBreakingThreshold::set(btScalar value)
{
	Native->setContactBreakingThreshold(value);
}

btScalar PersistentManifold::ContactProcessingThreshold::get()
{
	return Native->getContactProcessingThreshold();
}
void PersistentManifold::ContactProcessingThreshold::set(btScalar value)
{
	Native->setContactProcessingThreshold(value);
}

int PersistentManifold::Index1A::get()
{
	return Native->m_index1a;
}
void PersistentManifold::Index1A::set(int value)
{
	Native->m_index1a = value;
}

int PersistentManifold::NumContacts::get()
{
	return Native->getNumContacts();
}
void PersistentManifold::NumContacts::set(int value)
{
	Native->setNumContacts(value);
}
