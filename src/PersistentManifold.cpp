#include "StdAfx.h"

#include "CollisionObject.h"
#include "ManifoldPoint.h"
#include "PersistentManifold.h"

PersistentManifold::PersistentManifold(btPersistentManifold* manifold)
: TypedObject(manifold)
{
}

PersistentManifold::PersistentManifold()
: TypedObject(new btPersistentManifold())
{
}

int PersistentManifold::AddManifoldPoint(ManifoldPoint^ newPoint)
{
	return UnmanagedPointer->addManifoldPoint(*newPoint->UnmanagedPointer);
}

void PersistentManifold::ClearManifold()
{
	return UnmanagedPointer->clearManifold();
}

void PersistentManifold::ClearUserCache(ManifoldPoint^ pt)
{
	UnmanagedPointer->clearUserCache(*pt->UnmanagedPointer);
}

#ifdef DEBUG_PERSISTENCY
void PersistentManifold::DebugPersistency()
{
	UnmanagedPointer->DebugPersistency();
}
#endif

int PersistentManifold::GetCacheEntry(ManifoldPoint^ newPoint)
{
	return UnmanagedPointer->getCacheEntry(*newPoint->UnmanagedPointer);
}

ManifoldPoint^ PersistentManifold::GetContactPoint(int index)
{
	return gcnew ManifoldPoint(&UnmanagedPointer->getContactPoint(index));
}

void PersistentManifold::RefreshContactPoints(Matrix trA, Matrix trB)
{
	btTransform* trATemp = Math::MatrixToBtTransform(trA);
	btTransform* trBTemp = Math::MatrixToBtTransform(trB);
	UnmanagedPointer->refreshContactPoints(*trATemp, *trBTemp);
	delete trATemp;
	delete trBTemp;
}

void PersistentManifold::RemoveContactPoint(int index)
{
	UnmanagedPointer->removeContactPoint(index);
}

void PersistentManifold::ReplaceContactPoint(ManifoldPoint^ newPoint, int insertIndex)
{
	UnmanagedPointer->replaceContactPoint(*newPoint->UnmanagedPointer, insertIndex);
}

bool PersistentManifold::ValidContactDistance(ManifoldPoint^ pt)
{
	return UnmanagedPointer->validContactDistance(*pt->UnmanagedPointer);
}

Object^ PersistentManifold::Body0::get()
{
	return CollisionObject::GetManaged((btCollisionObject*)UnmanagedPointer->getBody0());
}

Object^ PersistentManifold::Body1::get()
{
	return CollisionObject::GetManaged((btCollisionObject*)UnmanagedPointer->getBody1());
}

int PersistentManifold::CompanionIDA::get()
{
	return UnmanagedPointer->m_companionIdA;
}
void PersistentManifold::CompanionIDA::set(int value)
{
	UnmanagedPointer->m_companionIdA = value;
}

int PersistentManifold::CompanionIDB::get()
{
	return UnmanagedPointer->m_companionIdB;
}
void PersistentManifold::CompanionIDB::set(int value)
{
	UnmanagedPointer->m_companionIdB = value;
}

float PersistentManifold::ContactBreakingThreshold::get()
{
	return UnmanagedPointer->getContactBreakingThreshold();
}

float PersistentManifold::ContactProcessingThreshold::get()
{
	return UnmanagedPointer->getContactProcessingThreshold();
}

int PersistentManifold::Index1A::get()
{
	return UnmanagedPointer->m_index1a;
}
void PersistentManifold::Index1A::set(int value)
{
	UnmanagedPointer->m_index1a = value;
}

int PersistentManifold::NumContacts::get()
{
	return UnmanagedPointer->getNumContacts();
}

btPersistentManifold* PersistentManifold::UnmanagedPointer::get()
{
	return (btPersistentManifold*)TypedObject::UnmanagedPointer;
}
