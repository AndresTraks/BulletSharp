#include "StdAfx.h"

#include "CollisionObject.h"
#include "ManifoldPoint.h"
#include "PersistentManifold.h"

#define Unmanaged static_cast<btPersistentManifold*>(_unmanaged)

PersistentManifold::PersistentManifold(btPersistentManifold* manifold)
: TypedObject(manifold)
{
}

PersistentManifold::PersistentManifold()
: TypedObject(new btPersistentManifold())
{
}

int PersistentManifold::AddManifoldPoint(ManifoldPoint^ newPoint, bool isPredictive)
{
	return Unmanaged->addManifoldPoint(*newPoint->_unmanaged, isPredictive);
}

int PersistentManifold::AddManifoldPoint(ManifoldPoint^ newPoint)
{
	return Unmanaged->addManifoldPoint(*newPoint->_unmanaged);
}

void PersistentManifold::ClearManifold()
{
	return Unmanaged->clearManifold();
}

void PersistentManifold::ClearUserCache(ManifoldPoint^ pt)
{
	Unmanaged->clearUserCache(*pt->UnmanagedPointer);
}

#ifdef DEBUG_PERSISTENCY
void PersistentManifold::DebugPersistency()
{
	Unmanaged->DebugPersistency();
}
#endif

int PersistentManifold::GetCacheEntry(ManifoldPoint^ newPoint)
{
	return Unmanaged->getCacheEntry(*newPoint->UnmanagedPointer);
}

ManifoldPoint^ PersistentManifold::GetContactPoint(int index)
{
	return gcnew ManifoldPoint(&Unmanaged->getContactPoint(index));
}

void PersistentManifold::RefreshContactPoints(Matrix trA, Matrix trB)
{
	btTransform* trATemp = Math::MatrixToBtTransform(trA);
	btTransform* trBTemp = Math::MatrixToBtTransform(trB);

	Unmanaged->refreshContactPoints(*trATemp, *trBTemp);

	delete trATemp;
	delete trBTemp;
}

void PersistentManifold::RemoveContactPoint(int index)
{
	Unmanaged->removeContactPoint(index);
}

void PersistentManifold::ReplaceContactPoint(ManifoldPoint^ newPoint, int insertIndex)
{
	Unmanaged->replaceContactPoint(*newPoint->UnmanagedPointer, insertIndex);
}

bool PersistentManifold::ValidContactDistance(ManifoldPoint^ pt)
{
	return Unmanaged->validContactDistance(*pt->UnmanagedPointer);
}

Object^ PersistentManifold::Body0::get()
{
	return CollisionObject::GetManaged((btCollisionObject*)Unmanaged->getBody0());
}

Object^ PersistentManifold::Body1::get()
{
	return CollisionObject::GetManaged((btCollisionObject*)Unmanaged->getBody1());
}

int PersistentManifold::CompanionIDA::get()
{
	return Unmanaged->m_companionIdA;
}
void PersistentManifold::CompanionIDA::set(int value)
{
	Unmanaged->m_companionIdA = value;
}

int PersistentManifold::CompanionIDB::get()
{
	return Unmanaged->m_companionIdB;
}
void PersistentManifold::CompanionIDB::set(int value)
{
	Unmanaged->m_companionIdB = value;
}

btScalar PersistentManifold::ContactBreakingThreshold::get()
{
	return Unmanaged->getContactBreakingThreshold();
}
void PersistentManifold::ContactBreakingThreshold::set(btScalar value)
{
	Unmanaged->setContactBreakingThreshold(value);
}

float PersistentManifold::ContactProcessingThreshold::get()
{
	return Unmanaged->getContactProcessingThreshold();
}
void PersistentManifold::ContactProcessingThreshold::set(btScalar value)
{
	Unmanaged->setContactProcessingThreshold(value);
}

int PersistentManifold::Index1A::get()
{
	return Unmanaged->m_index1a;
}
void PersistentManifold::Index1A::set(int value)
{
	Unmanaged->m_index1a = value;
}

int PersistentManifold::NumContacts::get()
{
	return Unmanaged->getNumContacts();
}
void PersistentManifold::NumContacts::set(int value)
{
	Unmanaged->setNumContacts(value);
}
