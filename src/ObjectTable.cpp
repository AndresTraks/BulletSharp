#include "StdAfx.h"

#include "ObjectTable.h"

static BulletSharp::ObjectTable::ObjectTable()
{
	objectTable = gcnew Dictionary<intptr_t, Object^>();
}

void BulletSharp::ObjectTable::Add(Object^ obj, void* unmanagedPointer)
{
	objectTable->Add((intptr_t)unmanagedPointer, obj);
}

bool BulletSharp::ObjectTable::Contains(intptr_t unmanagedPointer)
{
	return objectTable->ContainsKey(unmanagedPointer);
}

bool BulletSharp::ObjectTable::Contains(Object^ managedObject)
{
	return objectTable->ContainsValue(managedObject);
}

void BulletSharp::ObjectTable::Remove(void* unmanagedPointer)
{
	objectTable->Remove((intptr_t)unmanagedPointer);
}

generic<class T>
T BulletSharp::ObjectTable::GetObject(intptr_t unmanagedPointer)
{
	return (T)objectTable[unmanagedPointer];
}

intptr_t BulletSharp::ObjectTable::GetUnmanagedObject(Object^ unmanagedPointer)
{
	for each(intptr_t key in objectTable->Keys)
		if (objectTable[key] == unmanagedPointer)
			return key;
	return 0;
}
