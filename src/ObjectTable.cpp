#include "StdAfx.h"

#include "ObjectTable.h"

using namespace System::Threading;

static BulletSharp::ObjectTable::ObjectTable()
{
	objectTable = gcnew Dictionary<intptr_t, Object^>();
}

void BulletSharp::ObjectTable::Add(Object^ obj, void* unmanagedPointer)
{
	Monitor::Enter(objectTable);
	try
	{
		if (!objectTable->ContainsKey((intptr_t)unmanagedPointer))
			objectTable->Add((intptr_t)unmanagedPointer, obj);
		else
		{
			//something when wrong here, so inform in debug mode
			Debug::Assert(false, "ObjectTable key already exists.");
			//key already exists.. try to handle this by updating/overwriting key entry to newest value
			//this should protect us against a wrapper that did not unregister from object table, and race conditions that try to write the same key.
			objectTable[(intptr_t)unmanagedPointer] = obj;
		}
	}
	finally{ Monitor::Exit(objectTable); }
}

bool BulletSharp::ObjectTable::Contains(intptr_t unmanagedPointer)
{
	Monitor::Enter(objectTable);
	try
	{
		return objectTable->ContainsKey(unmanagedPointer);
	}
	finally{ Monitor::Exit(objectTable); }
}

bool BulletSharp::ObjectTable::Contains(Object^ managedObject)
{
	Monitor::Enter(objectTable);
	try
	{
		return objectTable->ContainsValue(managedObject);
	}
	finally{ Monitor::Exit(objectTable); }
}

void BulletSharp::ObjectTable::Remove(void* unmanagedPointer)
{
	Monitor::Enter(objectTable);
	try
	{
		objectTable->Remove((intptr_t)unmanagedPointer);
	}
	finally{ Monitor::Exit(objectTable); }
}

generic<class T> T BulletSharp::ObjectTable::GetObject(intptr_t unmanagedPointer)
{
	Monitor::Enter(objectTable);
	try
	{
		return (T)objectTable[unmanagedPointer];
	}
	finally{ Monitor::Exit(objectTable); }
}

intptr_t BulletSharp::ObjectTable::GetUnmanagedObject(Object^ unmanagedPointer)
{
	Monitor::Enter(objectTable);
	try
	{
		for each(intptr_t key in objectTable->Keys)
			if (objectTable[key] == unmanagedPointer)
				return key;
		return 0;
	}
	finally{ Monitor::Exit(objectTable); }
}
